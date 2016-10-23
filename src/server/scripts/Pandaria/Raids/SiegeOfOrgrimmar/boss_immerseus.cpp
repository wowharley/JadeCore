/*
 * Copyright (C) 2013-2016 JadeCore <https://www.jadecore.tk/>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include "GameObjectAI.h"
#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "siege_of_orgrimmar.h"  

enum eSpells
{
	// Split
	SPELL_SPLIT_DUMMY               = 143020,
	SPELL_SPLIT_SHA_PUDDLE          = 143022,
	SPELL_SPLIT_CONTAMINATED_PUDDLE = 143024,

	// Seeping Sha
	SPELL_SEEPING_SHA_VISUAL        = 143281,
	SPELL_SEEPING_SHA_DAMAGE        = 143286,
};

enum eEvents
{
	EVENT_SPLIT = 1,
};

enum eActions
{

};

enum ePhase
{
	// TODO
};

Position immersus_chest = {1440.66f, 817.257f, 246.835f, 4.679507f};

Position circleposition[6] =
{
	{ 1447.89f, 828.258f, 246.835f },
	{ 1384.38f, 799.616f, 246.784f },
	{ 1366.21f, 726.288f, 246.834f },
	{ 1482.72f, 682.118f, 246.836f },
	{ 1513.86f, 780.797f, 246.835f },
	{ 1447.89f, 828.258f, 246.835f },
};

Position immersusfrontdoor = { 1442.74f, 861.203f, 248.994f, 3.519956f };
Position immersusbackdoor2 = { 1442.74f, 861.203f, 248.994f, 3.519956f };

#define MAX_PUDDLES 12

void DespawnCreaturesInArea(uint32 entry, WorldObject* object)
{
	std::list<Creature*> creatures;
	GetCreatureListWithEntryInGrid(creatures, object, entry, 300.0f);
	if (creatures.empty())
		return;

	for (std::list<Creature*>::iterator iter = creatures.begin(); iter != creatures.end(); ++iter)
		(*iter)->DespawnOrUnsummon();
}

// Immerseus - 71543
class boss_immerseus : public CreatureScript
{
public:
    boss_immerseus() : CreatureScript("boss_immerseus") { }

    struct boss_immerseusAI : public BossAI
    {
        boss_immerseusAI(Creature* creature) : BossAI(creature, DATA_IMMERSUS)
        {
            pInstance = creature->GetInstanceScript();
        }

        InstanceScript* pInstance;

        void Reset()
        {
            _Reset();
            events.Reset();
            summons.DespawnAll();

            me->SetDisplayId(49056);
            me->RemoveAllAuras();

            me->AddUnitMovementFlag(MOVEMENTFLAG_ROOT);
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_DISABLE_MOVE);

            me->SetMaxPower(POWER_ENERGY, 100);
            me->SetInt32Value(UNIT_FIELD_MAX_POWER, 100);
            me->SetPower(POWER_ENERGY, 100);
            me->SetInt32Value(UNIT_FIELD_POWER, 100);
            me->RemoveFlag(UNIT_FIELD_FLAGS2, UNIT_FLAG2_REGENERATE_POWER);

            me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_SELECTABLE);

            switch (me->GetMap()->GetDifficulty())
            {
				case RAID_DIFFICULTY_10MAN_HEROIC:
					me->SetMaxHealth(87000000);
					break;
				case RAID_DIFFICULTY_25MAN_HEROIC:
					me->SetMaxHealth(212000000);
					break;
				case RAID_DIFFICULTY_25MAN_NORMAL:
					me->SetMaxHealth(250000000);
					break;
				case RAID_DIFFICULTY_10MAN_NORMAL:
					me->SetMaxHealth(62000000);
					break;
            }
        }

        void MoveInLineOfSight(Unit* who)
        {

        }

        void JustReachedHome()
        {
            _JustReachedHome();
            summons.DespawnAll();

            instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);;
            instance->SetBossState(DATA_IMMERSUS, FAIL);

            DespawnCreaturesInArea(CREATURE_LESSER_SHA_PUDDLE, me);
            DespawnCreaturesInArea(CREATURE_CONTAMINATED_PUDDLE, me);
        }

        void EnterCombat(Unit* attacker)
        {
            if (pInstance)
            {
                pInstance->SendEncounterUnit(ENCOUNTER_FRAME_ENGAGE, me);
                DoZoneInCombat();
            }

            DespawnCreaturesInArea(CREATURE_LESSER_SHA_PUDDLE, me);
            DespawnCreaturesInArea(CREATURE_CONTAMINATED_PUDDLE, me);

            me->SetMaxPower(POWER_ENERGY, 100);
            me->SetInt32Value(UNIT_FIELD_MAX_POWER, 100);
            me->SetPower(POWER_ENERGY, 100);
            me->SetInt32Value(UNIT_FIELD_POWER, 100);

			DoCast(me, SPELL_SEEPING_SHA_VISUAL);
        }

        void JustSummoned(Creature* summon)
        {
            summons.Summon(summon);
        }

        void DamageTaken(Unit* /*attacker*/, uint32& /*damage*/)
        {
            if (!me->IsInCombat())
                return;
        }

        void SummonedCreatureDespawn(Creature* summon)
        {
            summons.Despawn(summon);
        }

        void JustDied(Unit* /*killer*/)
        {

        }

        void DoAction(int32 /*action*/)
        {
            
        }

        void UpdateAI(uint32 diff) override
        {
            if (!UpdateVictim())
                return;

            if (me->HasUnitState(UNIT_STATE_CASTING))
                return;

            events.Update(diff);
            
			while (uint32 eventId = events.ExecuteEvent())
			{
				switch (eventId)
				{
					case EVENT_SPLIT:
					{
						DoCast(me, SPELL_SPLIT_DUMMY);
						break;
					}
				}
			}

            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new boss_immerseusAI(creature);
    }
};

// Seeping Sha - 143281
class spell_seeping_sha_damage : public SpellScriptLoader
{
	public:
		spell_seeping_sha_damage() : SpellScriptLoader("spell_seeping_sha_damage") { }

		class spell_seeping_sha_damage_AuraScript : public AuraScript
		{
			PrepareAuraScript(spell_seeping_sha_damage_AuraScript);

			void OnUpdate(uint32 diff, AuraEffect* aurEff)
			{
				if (Unit* caster = GetCaster())
				{
					std::list<Player*> pl_list;
					caster->GetPlayerListInGrid(pl_list, 15.0f);
					if (pl_list.empty())
						return;

					for (auto itr : pl_list)
						caster->CastSpell(itr, SPELL_SEEPING_SHA_DAMAGE);
				}
			}

			void Register() override
			{
				OnEffectUpdate += AuraEffectUpdateFn(spell_seeping_sha_damage_AuraScript::OnUpdate, EFFECT_1, SPELL_AURA_DUMMY);
			}
		};

		AuraScript* GetAuraScript() const override
		{
			return new spell_seeping_sha_damage_AuraScript();
		}
};

// Split - 143020
class spell_split : public SpellScriptLoader
{
	public:
		spell_split() : SpellScriptLoader("spell_split") { }

		class spell_split_SpellScript : public SpellScript
		{
			PrepareSpellScript(spell_split_SpellScript);

			void HandleOnCast()
			{
				SpellEffIndex effIndex;
				PreventHitDefaultEffect(effIndex);

				if (Unit* caster = GetCaster())
				{
					for (int i = 0; i <= MAX_PUDDLES; i++)
					{
						caster->CastSpell(caster, SPELL_SPLIT_SHA_PUDDLE);
						caster->CastSpell(caster, SPELL_SPLIT_CONTAMINATED_PUDDLE);
					}
				}
			}

			void HandleScript(SpellEffIndex effIndex)
			{
				PreventHitDefaultEffect(effIndex);

				if (!GetCaster())
					return;
			}

			void Register() override
			{
				OnCast += SpellCastFn(spell_split_SpellScript::HandleOnCast);
				OnEffectHitTarget += SpellEffectFn(spell_split_SpellScript::HandleScript, EFFECT_1, SPELL_EFFECT_SCRIPT_EFFECT);
			}
		};

		SpellScript* GetSpellScript() const override
		{
			return new spell_split_SpellScript();
		}
};

void AddSC_boss_Immerseus()
{
	// Boss
	new boss_immerseus();

	// Spells
	new spell_seeping_sha_damage();
	new spell_split();
}
