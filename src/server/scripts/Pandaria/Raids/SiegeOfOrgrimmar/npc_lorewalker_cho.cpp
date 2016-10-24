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

#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "siege_of_orgrimmar.h"

enum eTalks
{
	TALK_ONE = 1,
	TALK_TWO = 2,
};

enum eEvents
{
	EVENT_ONE = 1,
};

enum eActions
{
	ACTION_ONE = 1,
};

class npc_lorewalker_cho_SoO : public CreatureScript
{
	public:
		npc_lorewalker_cho_SoO() : CreatureScript("npc_lorewalker_cho_SoO") { }
		
		struct npc_lorewalker_cho_SoO_AI : public BossAI
		{
			npc_lorewalker_cho_SoO_AI(Creature* creature) : BossAI(creature, DATA_LOREWALKER_CHO)
			{
				pInstance = creature->GetInstanceScript();
			}
			
			InstanceScript* pInstance;
			
			void DoAction(int32 action)
			{
				switch (action)
				{
					case ACTION_ONE:
					{
						Talk(TALK_ONE);
						break;
					}
				}
			}
			
			void UpdateAI(uint32 diff) override
			{
				events.Update(diff);

				while (uint8 eventId = events.ExecuteEvent())
				{
					switch (eventId)
					{
						case EVENT_ONE:
						{
							Talk(TALK_TWO);
							break;
						}
					}
				}
			}
		};
		
		CreatureAI* GetAI(Creature* creature) const override
		{
			return new npc_lorewalker_cho_SoO_AI(creature);
		}
};

void AddSC_npc_lorewalker_cho()
{
	// Lorewalker Cho
	new npc_lorewalker_cho_SoO();
}
