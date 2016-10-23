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
    // 1ST phase 
    SPELL_SHA_BOLT_COSMETIC          = 129067,
    SPELL_SHA_BOLT_DUMMY             = 143290,
    SPELL_SHA_BOLT_MISSILE           = 143293,
    SPELL_SHA_BOLT_POOL              = 143295,

    SPELL_SWIRL_DUMMY                = 143309,
    SPELL_SWIRL_DAMAGE               = 143412,
    SPELL_CORROSIVE_BLAST            = 143436,

    SPELL_SEEPING_SHA_CIRCLE         = 143281,

    // 2ND PHASE
    SPELL_SHA_RESIUDE                = 143459,
    SPELL_CONGEALING                 = 143540,
    SPELL_PURIFIED_RESIDUE           = 143524,

    SPELL_SEEPING_SHA_VISUAL         = 143281,
    SPELL_SEEPING_SHA_DAMAGE         = 143286,

    SPELL_ERUPTING_SHA               = 143498,

    SPELL_SWIRL_CIRCLE_DUMMY         = 143410,
    SPELL_SWIRL_CIRCLE_DAMAGE        = 143413,

    SPELL_SPLIT_DUMMY                = 143020,
    SPELL_SPLIT_SHA_PUDDLE_THROW     = 143022,
    SPELL_SPLIT_CONTEMPLATED_THROW   = 143024,

    // HEROIC
    SPELL_SWELLING_CORRUPTION_AURA   = 143574,
    SPELL_SWELLING_CORRUPTION_SCRIPT = 143578,
    SPELL_SWELLING_CORRUPTION_SUMMON = 143581,
    
    SPELL_CORRUPTION_DOT             = 143579,

    // 2ND PHASE HC
    SPELL_SHA_POOL_EFFECT            = 143462,
    SPELL_SHA_POOL_AURA              = 143462,
    SPELL_SHA_POOL_PERIODIC_DAMAGE   = 143460,
};

enum eEvents
{
    EVENT_SHA_BOLT       = 1,
    EVENT_SWIRL          = 2,
    EVENT_CORRSIVE_BLAST = 3,
    EVENT_SPLIT_PHASE    = 4,
};

enum eActions
{
    ACTION_COUNT_SPLIT_PHASE = 1,
    ACTION_REMOVE_ENERGY     = 2,
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
            


            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new boss_immerseusAI(creature);
    }
};

void AddSC_boss_Immerseus()
{
	// boss
	new boss_immerseus();
}
