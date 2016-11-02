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

#include "LFGMgr.h"
#include "ObjectMgr.h"
#include "Group.h"
#include "Player.h"
#include "Opcodes.h"
#include "WorldPacket.h"
#include "WorldSession.h"

void BuildPlayerLockDungeonBlock(WorldPacket& data, lfg::LfgLockMap const& lock)
{
    data << uint32(lock.size());                           // Size of lock dungeons
    for (lfg::LfgLockMap::const_iterator it = lock.begin(); it != lock.end(); ++it)
    {
        data << uint32(it->first);                         // Dungeon entry (id + type)
        data << uint32(0);                                 // Required itemLevel
        data << uint32(it->second);                        // Lock status
        data << uint32(0);                                 // Current itemLevel
    }
}

void BuildPartyLockDungeonBlock(WorldPacket& data, lfg::LfgLockPartyMap const& lockMap)
{
    data << uint8(lockMap.size());
    for (lfg::LfgLockPartyMap::const_iterator it = lockMap.begin(); it != lockMap.end(); ++it)
    {
        data << uint64(it->first);                         // Player guid
        BuildPlayerLockDungeonBlock(data, it->second);
    }
}

void BuildQuestReward(WorldPacket& data, Quest const* quest, Player* player)
{
    uint8 rewCount = quest->GetRewItemsCount() + quest->GetRewCurrencyCount();

    data << uint32(quest->GetRewMoney());
    data << uint32(quest->XPValue(player));
    data << uint8(rewCount);
    if (rewCount)
    {
        for (uint8 i = 0; i < QUEST_REWARD_CURRENCY_COUNT; ++i)
        {
            if (uint32 currencyId = quest->RewardCurrencyId[i])
            {
                data << uint32(currencyId);
                data << uint32(0);
                data << uint32(quest->RewardCurrencyCount[i]);
                data << uint8(1);                                           // Is currency
            }
        }

        for (uint8 i = 0; i < QUEST_REWARDS_COUNT; ++i)
        {
            if (uint32 itemId = quest->RewardItemId[i])
            {
                ItemTemplate const* item = sObjectMgr->GetItemTemplate(itemId);
                data << uint32(itemId);
                data << uint32(item ? item->DisplayInfoID : 0);
                data << uint32(quest->RewardItemIdCount[i]);
                data << uint8(0);                                           // Is currency
            }
        }
    }
}

void WorldSession::HandleLfgJoinOpcode(WorldPacket& recvData)
{
    if (!sLFGMgr->isOptionEnabled(lfg::LFG_OPTION_ENABLE_DUNGEON_FINDER | lfg::LFG_OPTION_ENABLE_RAID_BROWSER) ||
        (GetPlayer()->GetGroup() && GetPlayer()->GetGroup()->GetLeaderGUID() != GetPlayer()->GetGUID() &&
        (GetPlayer()->GetGroup()->GetMembersCount() == MAXGROUPSIZE || !GetPlayer()->GetGroup()->isLFGGroup())))
    {
        recvData.rfinish();
        return;
	    }
        uint32 dungeon;
        uint32 roles;
        uint8 unk8;
        bool queueAsGroup = false;

    recvData >> unk8;
    for (int32 i = 0; i < 3; ++i)
        recvData.read_skip<uint32>();
    recvData >> roles;
    uint32 numDungeons = recvData.ReadBits(22);
    uint32 commentLen = recvData.ReadBits(8);
    queueAsGroup = recvData.ReadBit();

    recvData.FlushBits();

    if (!numDungeons)
    {
        TC_LOG_DEBUG("lfg", "CMSG_LFG_JOIN %s no dungeons selected", GetPlayerInfo().c_str());
        recvData.rfinish();
        return;
    }

    std::string comment = recvData.ReadString(commentLen);

    lfg::LfgDungeonSet newDungeons;
    for (uint32 i = 0; i < numDungeons; ++i)
    {
        recvData >> dungeon;
        dungeon &= 0xFFFFFF;
        newDungeons.insert(dungeon);        // remove the type from the dungeon entry
    }

    TC_LOG_DEBUG("lfg", "CMSG_LFG_JOIN %s roles: %u, Dungeons: %u, Comment: %s",
        GetPlayerInfo().c_str(), roles, uint8(newDungeons.size()), comment.c_str());

    sLFGMgr->JoinLfg(GetPlayer(), uint8(roles), newDungeons, comment);
}

void WorldSession::HandleLfgLeaveOpcode(WorldPacket& recvData)
{
    ObjectGuid leaveGuid;
    Group* group = GetPlayer()->GetGroup();
    uint64 guid = GetPlayer()->GetGUID();
    uint64 gguid = group ? group->GetGUID() : guid;

    recvData.read_skip<uint32>();                          // Always 8
    recvData.read_skip<uint32>();                          // Join date
    recvData.read_skip<uint32>();                          // Always 3
    recvData.read_skip<uint32>();                          // Queue Id

    recvData.ReadGuidMask(leaveGuid, 0, 1, 6, 7, 3, 5, 2, 4);

    recvData.ReadGuidBytes(leaveGuid, 1, 5, 6, 7, 4, 2, 3, 0);

    TC_LOG_DEBUG("lfg", "CMSG_LFG_LEAVE %s in group: %u sent guid " UI64FMTD ".",
        GetPlayerInfo().c_str(), group ? 1 : 0, uint64(leaveGuid));

    // Check cheating - only leader can leave the queue
    if (!group || group->GetLeaderGUID() == guid)
        sLFGMgr->LeaveLfg(gguid);
}

void WorldSession::HandleLfgProposalResultOpcode(WorldPacket& recvData)
{
    uint32 proposalID;  // Proposal ID
    bool accept;

    ObjectGuid guid1;
    ObjectGuid guid2;

    recvData >> proposalID;
    recvData.read_skip<uint32>();
    recvData.read_skip<uint32>();
    recvData.read_skip<uint32>();

    recvData.ReadGuidMask(guid2, 4, 5, 0, 6, 2, 7, 1, 3);

    recvData.ReadGuidBytes(guid2, 7, 4, 3, 2, 6, 0, 1, 5);

    guid1[7] = recvData.ReadBit();
    accept =  recvData.ReadBit();
    recvData.ReadGuidMask(guid1, 1, 3, 0, 5, 4, 6, 2);

    recvData.ReadGuidBytes(guid1, 7, 1, 5, 6, 3, 4, 0, 2);

    TC_LOG_DEBUG("lfg", "CMSG_LFG_PROPOSAL_RESULT %s proposal: %u accept: %u",
        GetPlayerInfo().c_str(), proposalID, accept ? 1 : 0);
    sLFGMgr->UpdateProposal(proposalID, GetPlayer()->GetGUID(), accept);
}

void WorldSession::HandleLfgSetRolesOpcode(WorldPacket& recvData)
{
    uint8 roles;
    recvData >> roles;                                     // Player Group Roles
    uint64 guid = GetPlayer()->GetGUID();
    Group* group = GetPlayer()->GetGroup();
    if (!group)
    {
        TC_LOG_DEBUG("lfg", "CMSG_LFG_SET_ROLES %s Not in group",
            GetPlayerInfo().c_str());
        return;
    }
    uint64 gguid = group->GetGUID();
    TC_LOG_DEBUG("lfg", "CMSG_LFG_SET_ROLES: Group %u, Player %s, Roles: %u",
        GUID_LOPART(gguid), GetPlayerInfo().c_str(), roles);
    sLFGMgr->UpdateRoleCheck(gguid, guid, roles);
}

void WorldSession::HandleLfgSetCommentOpcode(WorldPacket&  recvData)
{
    std::string comment;
    recvData >> comment;

    TC_LOG_DEBUG("lfg", "CMSG_LFG_SET_COMMENT %s comment: %s",
        GetPlayerInfo().c_str(), comment.c_str());

    sLFGMgr->SetComment(GetPlayer()->GetGUID(), comment);
}

void WorldSession::HandleLfgSetBootVoteOpcode(WorldPacket& recvData)
{
    bool agree;                                            // Agree to kick player
    recvData >> agree;

    uint64 guid = GetPlayer()->GetGUID();
    TC_LOG_DEBUG("lfg", "CMSG_LFG_SET_BOOT_VOTE %s agree: %u",
        GetPlayerInfo().c_str(), agree ? 1 : 0);
    sLFGMgr->UpdateBoot(guid, agree);
}

void WorldSession::HandleLfgTeleportOpcode(WorldPacket& recvData)
{
    bool out;
    recvData >> out;

    TC_LOG_DEBUG("lfg", "CMSG_LFG_TELEPORT %s out: %u",
        GetPlayerInfo().c_str(), out ? 1 : 0);
    sLFGMgr->TeleportPlayer(GetPlayer(), out, true);
}

void WorldSession::HandleLfgGetLockInfoOpcode(WorldPacket& recvData)
{
    uint8 value;
    recvData >> value;
    bool forPlayer = recvData.ReadBit();
    TC_LOG_DEBUG("lfg", "CMSG_LFG_LOCK_INFO_REQUEST %s for %s", GetPlayerInfo().c_str(), (forPlayer ? "player" : "party"));

    if (forPlayer)
        SendLfgPlayerLockInfo();
    else
        SendLfgPartyLockInfo();
}

void WorldSession::SendLfgPlayerLockInfo()
{
    uint64 guid = GetPlayer()->GetGUID();

    // Get Random dungeons that can be done at a certain level and expansion
    uint8 level = GetPlayer()->getLevel();
    lfg::LfgDungeonSet const& randomDungeons =
        sLFGMgr->GetRandomAndSeasonalDungeons(level, GetPlayer()->GetSession()->Expansion());

    // Get player locked Dungeons
    lfg::LfgLockMap const& lock = sLFGMgr->GetLockedDungeons(guid);
    uint32 rsize = uint32(randomDungeons.size());
    uint32 lsize = uint32(lock.size());

    TC_LOG_DEBUG("lfg", "SMSG_LFG_PLAYER_INFO %s", GetPlayerInfo().c_str());
    WorldPacket data(SMSG_LFG_PLAYER_INFO, 1 + rsize * (4 + 1 + 4 + 4 + 4 + 4 + 1 + 4 + 4 + 4) + 4 + lsize * (1 + 4 + 4 + 4 + 4 + 1 + 4 + 4 + 4));

    bool hasGuid = true;
    data.WriteBits(lock.size(), 20);
    data.WriteBit(hasGuid);
    data.WriteBits(randomDungeons.size(), 17);                  // Random Dungeon count

    for (lfg::LfgDungeonSet::const_iterator it = randomDungeons.begin(); it != randomDungeons.end(); ++it)
    {
        lfg::LfgReward const* reward = sLFGMgr->GetRandomDungeonReward(*it, level);
        Quest const* quest = NULL;
        bool done = false;
        if (reward)
        {
            quest = sObjectMgr->GetQuestTemplate(reward->firstQuest);
            if (quest)
            {
                done = !GetPlayer()->CanRewardQuest(quest, false);
                if (done)
                    quest = sObjectMgr->GetQuestTemplate(reward->otherQuest);
            }
        }

        data.WriteBit(!done);
        data.WriteBit(true); // true

        data.WriteBits(0, 21); // Unk count
        data.WriteBits(0, 19); // Unk count 2 - related to call to Arms
        data.WriteBits(quest ? quest->GetRewItemsCount() : 0, 20);
        data.WriteBits(quest ? quest->GetRewCurrencyCount() : 0, 21);
    }

    if (hasGuid)
    {
        uint8 bitOrder[8] = { 5, 1, 2, 7, 3, 0, 6, 4 };
        data.WriteBitInOrder(guid, bitOrder);

        uint8 byteOrder[8] = { 7, 2, 3, 0, 4, 5, 6, 1 };
        data.WriteBytesSeq(guid, byteOrder);
    }

    for (lfg::LfgDungeonSet::const_iterator it = randomDungeons.begin(); it != randomDungeons.end(); ++it)
    {
        lfg::LfgReward const* reward = sLFGMgr->GetRandomDungeonReward(*it, level);
        Quest const* quest = NULL;
        uint8 done = 0;
        if (reward)
        {
            quest = sObjectMgr->GetQuestTemplate(reward->firstQuest);
            if (quest)
            {
                done = !GetPlayer()->CanRewardQuest(quest, false);
                if (done)
                    quest = sObjectMgr->GetQuestTemplate(reward->otherQuest);
            }
        }

        data << uint32(0); // 11
        data << uint32(0); // 12

        data << uint32(0); // 15
        data << uint32(0); // 16
        data << uint32(0); // 17

        if (quest)
        {
            data << uint32(0); // unk108
            data << uint32(0); // unk40
            data << uint32(0); // unk68
            data << uint32(0); // unk104

            if (quest->GetRewItemsCount())
            {
                ItemTemplate const* iProto = NULL;
                for (uint8 i = 0; i < QUEST_REWARDS_COUNT; ++i)
                {
                    if (!quest->RewardItemId[i])
                        continue;

                    iProto = sObjectMgr->GetItemTemplate(quest->RewardItemId[i]);

                    data << uint32(quest->RewardItemIdCount[i]);
                    data << uint32(quest->RewardItemId[i]);
                    data << uint32(iProto ? iProto->DisplayInfoID : 0);
                }
            }

            data << uint32(0); // unk48
            data << uint32(0); // unk56
            data << uint32(0); // unk52
            data << uint32(0); // unk72
            data << uint32(0); // unk36
            data << uint32(*it);

            if (quest->GetRewCurrencyCount())
            {
                for (uint8 i = 0; i < QUEST_REWARDS_COUNT; ++i)
                {
                    if (!quest->RewardCurrencyId[i])
                        continue;

                    data << uint32(quest->RewardCurrencyId[i]);
                    data << uint32(quest->RewardCurrencyCount[i]);
                }
            }

            data << uint32(0); // unk60
            data << uint32(0); // unk100
            data << uint32(0); // unk64
            data << uint32(0); // unk32
            data << uint32(0); // unk44
            data << uint32(0); // unk76
            data << uint32(0); // unk28
        }
        else
        {
            data << uint32(0); // unk108
            data << uint32(0); // unk40
            data << uint32(0); // unk68
            data << uint32(0); // unk104
            data << uint32(0); // unk48
            data << uint32(0); // unk56
            data << uint32(0); // unk52
            data << uint32(0); // unk72
            data << uint32(0); // unk36
            data << uint32(0); // unk40
            data << uint32(0); // unk60
            data << uint32(0); // unk100
            data << uint32(0); // unk64
            data << uint32(0); // unk32
            data << uint32(0); // unk44
            data << uint32(0); // unk76
            data << uint32(0); // unk28

        }
    }

    for (lfg::LfgLockMap::const_iterator it = lock.begin(); it != lock.end(); ++it)
    {
        data << uint32(it->first);                         // Dungeon entry (id + type)
        data << uint32(0);                                 // Required itemLevel
        data << uint32(it->second);                        // Lock status
        data << uint32(0);                                 // Current itemLevel
    }
    BuildPlayerLockDungeonBlock(data, lock);
    SendPacket(&data);
}

void WorldSession::SendLfgPartyLockInfo()
{
    uint64 guid = GetPlayer()->GetGUID();
    Group* group = GetPlayer()->GetGroup();
    if (!group)
        return;

    // Get the locked dungeons of the other party members
    lfg::LfgLockPartyMap lockMap;
    for (GroupReference* itr = group->GetFirstMember(); itr != NULL; itr = itr->next())
    {
        Player* plrg = itr->GetSource();
        if (!plrg)
            continue;

        uint64 pguid = plrg->GetGUID();
        if (pguid == guid)
            continue;

        lockMap[pguid] = sLFGMgr->GetLockedDungeons(pguid);
    }

    uint32 size = 0;
    for (lfg::LfgLockPartyMap::const_iterator it = lockMap.begin(); it != lockMap.end(); ++it)
        size += 8 + 4 + uint32(it->second.size()) * (4 + 4 + 4 + 4);

    TC_LOG_DEBUG("lfg", "SMSG_LFG_PARTY_INFO %s", GetPlayerInfo().c_str());
    WorldPacket data(SMSG_LFG_PARTY_INFO, 1 + size);
    BuildPartyLockDungeonBlock(data, lockMap);
    SendPacket(&data);
}

void WorldSession::HandleLfrJoinOpcode(WorldPacket& recvData)
{
    uint32 entry;                                          // Raid id to search
    recvData >> entry;
    TC_LOG_DEBUG("lfg", "CMSG_LFG_LFR_JOIN %s dungeon entry: %u",
        GetPlayerInfo().c_str(), entry);
    //SendLfrUpdateListOpcode(entry);
}

void WorldSession::HandleLfrLeaveOpcode(WorldPacket& recvData)
{
    uint32 dungeonId;                                      // Raid id queue to leave
    recvData >> dungeonId;
    TC_LOG_DEBUG("lfg", "CMSG_LFG_LFR_LEAVE %s dungeonId: %u",
        GetPlayerInfo().c_str(), dungeonId);
    //sLFGMgr->LeaveLfr(GetPlayer(), dungeonId);
}

void WorldSession::HandleLfgGetStatus(WorldPacket& /*recvData*/)
{
    TC_LOG_DEBUG("lfg", "CMSG_LFG_GET_STATUS %s", GetPlayerInfo().c_str());

    if (!GetPlayer()->isUsingLfg())
        return;

    uint64 guid = GetPlayer()->GetGUID();
    lfg::LfgUpdateData updateData = sLFGMgr->GetLfgStatus(guid);

    if (GetPlayer()->GetGroup())
    {
        SendLfgUpdateStatus(updateData, true);
        updateData.dungeons.clear();
        SendLfgUpdateStatus(updateData, false);
    }
    else
    {
        SendLfgUpdateStatus(updateData, false);
        updateData.dungeons.clear();
        SendLfgUpdateStatus(updateData, true);
    }
}

void WorldSession::SendLfgUpdateStatus(lfg::LfgUpdateData const& updateData, bool party)
{
    bool join = false;
    bool queued = false;
    bool quit = false;
    uint8 size = uint8(updateData.dungeons.size());
    lfg::LfgQueueInfo* info = NULL;
    ObjectGuid guid = _player->GetGUID();
    time_t joinTime = sLFGMgr->GetQueueJoinTime(_player->GetGUID());
    uint32 queueId = sLFGMgr->GetQueueId(_player->GetGUID());

    switch (updateData.updateType)
    {
        case lfg::LFG_UPDATETYPE_JOIN_QUEUE:            // Joined queue outside the dungeon
            queued = true;
        case lfg::LFG_UPDATETYPE_ADDED_TO_QUEUE:                // Rolecheck Success
            join = true;
            break;
        case lfg::LFG_UPDATETYPE_UPDATE_STATUS:
            join = true;
            queued = true;
            break;
        case lfg::LFG_UPDATETYPE_PROPOSAL_BEGIN:
            quit = false;
            break;
        default:
            break;
    }

    TC_LOG_DEBUG("lfg", "SMSG_LFG_UPDATE_STATUS %s updatetype: %u, party %s",
        GetPlayerInfo().c_str(), updateData.updateType, party ? "true" : "false");

    WorldPacket data(SMSG_LFG_UPDATE_STATUS, 1 + 8 + 3 + 2 + 1 + updateData.comment.length() + 4 + 4 + 1 + 1 + 1 + 4 + size);
    data.WriteBits(updateData.comment.length(), 8);

    data.WriteBit(party);
    data.WriteBit(true);
    data.WriteBits(updateData.dungeons.size(), 22);
    data.WriteBit(guid[2]);
    data.WriteBit(guid[3]);
    data.WriteBit(guid[1]);
    data.WriteBit(join);
    data.WriteBit(guid[7]);
    data.WriteBit(guid[6]);
    data.WriteBit(guid[0]);
    data.WriteBit(0);
    data.WriteBit(quit);

    data.WriteBits(size, 24);
    data.WriteBit(guid[5]);

    data.WriteBit(guid[4]);

    data.WriteByteSeq(guid[3]);

    for (int i = 0; i < 3; ++i)
            data << uint8(0);

    data.WriteByteSeq(guid[4]);

    data.WriteByteSeq(guid[6]);

    data << uint8(updateData.updateType);
    data << uint32(info->roles[_player->GetGUID()]); // sure
    data << uint32(_player->GetTeam());              // Queue Id

    data.WriteByteSeq(guid[5]);

    data.WriteString(updateData.comment);

    data.WriteByteSeq(guid[2]);

    for (auto i = updateData.dungeons.begin(); i != updateData.dungeons.end(); ++i)
    {
        LFGDungeonEntry const* dungeon = sLFGDungeonStore.LookupEntry(*i);
        data << uint32(dungeon ? dungeon->Entry() : 0); // Dungeon
    }

    data.WriteByteSeq(guid[0]);
    data.WriteByteSeq(guid[1]);

    data << uint32(info->joinTime); // Join date
    data << uint8(info->category);
    data << uint32(3); // Flags

    data.WriteByteSeq(guid[7]);

    SendPacket(&data);
}

void WorldSession::SendLfgRoleChosen(uint64 guid, uint8 roles)
{
    TC_LOG_DEBUG("lfg", "SMSG_LFG_ROLE_CHOSEN %s guid: %u roles: %u",
        GetPlayerInfo().c_str(), GUID_LOPART(guid), roles);

    WorldPacket data(SMSG_LFG_ROLE_CHOSEN, 8 + 1 + 4);
    data << uint64(guid);                                  // Guid
    data << uint8(roles > 0);                              // Ready
    data << uint32(roles);                                 // Roles
    SendPacket(&data);
}

void WorldSession::SendLfgRoleCheckUpdate(lfg::LfgRoleCheck const& roleCheck)
{
    lfg::LfgDungeonSet dungeons;
    if (roleCheck.rDungeonId)
        dungeons.insert(roleCheck.rDungeonId);
    else
        dungeons = roleCheck.dungeons;

    TC_LOG_DEBUG("lfg", "SMSG_LFG_ROLE_CHECK_UPDATE %s", GetPlayerInfo().c_str());
    WorldPacket data(SMSG_LFG_ROLE_CHECK_UPDATE, 4 + 1 + 1 + dungeons.size() * 4 + 1 + roleCheck.roles.size() * (8 + 1 + 4 + 1));

    data << uint32(roleCheck.state);                       // Check result
    data << uint8(roleCheck.state == lfg::LFG_ROLECHECK_INITIALITING);
    data << uint8(dungeons.size());                        // Number of dungeons
    if (!dungeons.empty())
        for (lfg::LfgDungeonSet::iterator it = dungeons.begin(); it != dungeons.end(); ++it)
            data << uint32(sLFGMgr->GetLFGDungeonEntry(*it)); // Dungeon

    data << uint8(roleCheck.roles.size());                 // Players in group
    if (!roleCheck.roles.empty())
    {
        // Leader info MUST be sent 1st :S
        uint64 guid = roleCheck.leader;
        uint8 roles = roleCheck.roles.find(guid)->second;
        Player* player = ObjectAccessor::FindPlayer(guid);
        data << uint64(guid);                              // Guid
        data << uint8(roles > 0);                          // Ready
        data << uint32(roles);                             // Roles
        data << uint8(player ? player->getLevel() : 0);    // Level

        for (lfg::LfgRolesMap::const_iterator it = roleCheck.roles.begin(); it != roleCheck.roles.end(); ++it)
        {
            if (it->first == roleCheck.leader)
                continue;

            guid = it->first;
            roles = it->second;
            player = ObjectAccessor::FindPlayer(guid);
            data << uint64(guid);                          // Guid
            data << uint8(roles > 0);                      // Ready
            data << uint32(roles);                         // Roles
            data << uint8(player ? player->getLevel() : 0);// Level
        }
    }
    SendPacket(&data);
}

void WorldSession::SendLfgJoinResult(lfg::LfgJoinResultData const& joinData)
{
    uint32 size = 0;
    ObjectGuid guid = GetPlayer()->GetGUID();
    uint32 queueId = sLFGMgr->GetQueueId(_player->GetGUID());
    for (lfg::LfgLockPartyMap::const_iterator it = joinData.lockmap.begin(); it != joinData.lockmap.end(); ++it)
        size += 8 + 4 + uint32(it->second.size()) * (4 + 4 + 4 + 4);

    TC_LOG_DEBUG("lfg", "SMSG_LFG_JOIN_RESULT %s checkResult: %u checkValue: %u",
        GetPlayerInfo().c_str(), joinData.result, joinData.state);

    WorldPacket data(SMSG_LFG_JOIN_RESULT, 4 + 4 + size);

    data.WriteBit(guid[7]);
    data.WriteBit(guid[6]);
    data.WriteBit(guid[3]);
    data.WriteBit(guid[0]);
    data.WriteBits(joinData.lockmap.size(), 22);

    for (lfg::LfgLockPartyMap::const_iterator it = joinData.lockmap.begin(); it != joinData.lockmap.end(); ++it)
    {
        ObjectGuid playerGuid = it->first;
        data.WriteBit(playerGuid[3]);
        data.WriteBits(it->second.size(), 20);
        data.WriteBit(playerGuid[6]);
        data.WriteBit(playerGuid[1]);
        data.WriteBit(playerGuid[4]);
        data.WriteBit(playerGuid[7]);
        data.WriteBit(playerGuid[2]);
        data.WriteBit(playerGuid[0]);
        data.WriteBit(playerGuid[5]);

    }

    data.WriteBit(guid[5]);
    data.WriteBit(guid[1]);
    data.WriteBit(guid[4]);
    data.WriteBit(guid[2]);

    data << uint8(joinData.result);                        // Check Result

    for (lfg::LfgLockPartyMap::const_iterator it = joinData.lockmap.begin(); it != joinData.lockmap.end(); ++it)
    {
        ObjectGuid playerGuid = it->first;
        data.WriteByteSeq(playerGuid[4]);
        for (lfg::LfgLockMap::const_iterator itr = it->second.begin(); itr != it->second.end(); ++itr)
        {
            data << uint32(0);                                 // Current itemLevel
            data << uint32(itr->second);                       // Lock status
            data << uint32(itr->first);                        // Dungeon entry (id + type)
            data << uint32(0);                                 // Required itemLevel
        }

        data.WriteByteSeq(playerGuid[1]);
        data.WriteByteSeq(playerGuid[0]);
        data.WriteByteSeq(playerGuid[5]);
        data.WriteByteSeq(playerGuid[7]);
        data.WriteByteSeq(playerGuid[3]);
        data.WriteByteSeq(playerGuid[6]);
        data.WriteByteSeq(playerGuid[2]);
    }

    data << uint8(joinData.state);
    data.WriteByteSeq(guid[2]);
    data << uint32(queueId);                               // Queue Id
    data << uint32(time(NULL));                            // Join date
    data << uint32(3);	                                   // flags
    data.WriteByteSeq(guid[6]);
    data.WriteByteSeq(guid[4]);
    data.WriteByteSeq(guid[1]);
    data.WriteByteSeq(guid[0]);
    data.WriteByteSeq(guid[5]);
    data.WriteByteSeq(guid[7]);
    data.WriteByteSeq(guid[3]);
    
    SendPacket(&data);
}

void WorldSession::SendLfgQueueStatus(lfg::LfgQueueStatusData const& queueData)
{
    TC_LOG_DEBUG("lfg", "SMSG_LFG_QUEUE_STATUS %s dungeon: %u, waitTime: %d, "
        "avgWaitTime: %d, waitTimeTanks: %d, waitTimeHealer: %d, waitTimeDps: %d, "
        "queuedTime: %u, tanks: %u, healers: %u, dps: %u",
        GetPlayerInfo().c_str(), queueData.dungeonId, queueData.waitTime, queueData.waitTimeAvg,
        queueData.waitTimeTank, queueData.waitTimeHealer, queueData.waitTimeDps,
        queueData.queuedTime, queueData.tanks, queueData.healers, queueData.dps);

    ObjectGuid guid = _player->GetGUID();
    WorldPacket data(SMSG_LFG_QUEUE_STATUS, 4 + 4 + 4 + 4 + 4 + 4 + 1 + 1 + 1 + 4 + 4 + 4 + 4 + 8);
    data.WriteGuidMask(guid, 4, 3, 5, 1, 2, 0, 6, 7);

    data << uint32(3);
    data.WriteByteSeq(guid[0]);
    data << uint32(queueData.queuedTime);                  // Player wait time in queue
    data.WriteByteSeq(guid[4]);
    data << int32(queueData.waitTime);                     // Wait Time
    data << int32(queueData.waitTimeTank);                 // Wait Tanks
    data << uint8(queueData.tanks);                        // Tanks needed
    data << int32(queueData.waitTimeHealer);               // Wait Healers
    data << uint8(queueData.healers);                      // Healers needed
    data << int32(queueData.waitTimeDps);                  // Wait Dps
    data << uint8(queueData.dps);                          // Dps needed
    data << uint32(queueData.joinTime);                    // Join time
    data << uint32(queueData.queueId);                     // Queue Id
    data.WriteByteSeq(guid[1]);
    data << int32(queueData.waitTimeAvg);                  // Average Wait time
    data.WriteByteSeq(guid[7]);
    data.WriteByteSeq(guid[2]);
    data << uint32(queueData.dungeonId);                   // Dungeon
    data.WriteByteSeq(guid[5]);
    data.WriteByteSeq(guid[3]);
    data.WriteByteSeq(guid[6]);
    data << uint32(3);

    SendPacket(&data);
}

void WorldSession::SendLfgPlayerReward(lfg::LfgPlayerRewardData const& rewardData)
{
    if (!rewardData.rdungeonEntry || !rewardData.sdungeonEntry || !rewardData.quest)
        return;

    TC_LOG_DEBUG("lfg", "SMSG_LFG_PLAYER_REWARD %s rdungeonEntry: %u, sdungeonEntry: %u, done: %u",
        GetPlayerInfo().c_str(), rewardData.rdungeonEntry, rewardData.sdungeonEntry, rewardData.done);

    uint8 itemNum = rewardData.quest->GetRewItemsCount() + rewardData.quest->GetRewCurrencyCount();

    WorldPacket data(SMSG_LFG_PLAYER_REWARD, 4 + 4 + 1 + 4 + 4 + 4 + 4 + 4 + 1 + itemNum * (4 + 4 + 4));
    data << uint32(rewardData.rdungeonEntry);                               // Random Dungeon Finished
    data << uint32(rewardData.sdungeonEntry);                               // Dungeon Finished
    BuildQuestReward(data, rewardData.quest, GetPlayer());
    SendPacket(&data);
}

void WorldSession::SendLfgBootProposalUpdate(lfg::LfgPlayerBoot const& boot)
{
    uint64 guid = GetPlayer()->GetGUID();
    lfg::LfgAnswer playerVote = boot.votes.find(guid)->second;
    uint8 votesNum = 0;
    uint8 agreeNum = 0;
    uint32 secsleft = uint8((boot.cancelTime - time(NULL)) / 1000);
    for (lfg::LfgAnswerContainer::const_iterator it = boot.votes.begin(); it != boot.votes.end(); ++it)
    {
        if (it->second != lfg::LFG_ANSWER_PENDING)
        {
            ++votesNum;
            if (it->second == lfg::LFG_ANSWER_AGREE)
                ++agreeNum;
        }
    }
    TC_LOG_DEBUG("lfg", "SMSG_LFG_BOOT_PROPOSAL_UPDATE %s inProgress: %u - "
        "didVote: %u - agree: %u - victim: %u votes: %u - agrees: %u - left: %u - "
        "needed: %u - reason %s",
        GetPlayerInfo().c_str(), uint8(boot.inProgress), uint8(playerVote != lfg::LFG_ANSWER_PENDING),
        uint8(playerVote == lfg::LFG_ANSWER_AGREE), GUID_LOPART(boot.victim), votesNum, agreeNum,
        secsleft, lfg::LFG_GROUP_KICK_VOTES_NEEDED, boot.reason.c_str());
    WorldPacket data(SMSG_LFG_BOOT_PROPOSAL_UPDATE, 1 + 1 + 1 + 1 + 8 + 4 + 4 + 4 + 4 + boot.reason.length());
    data << uint8(boot.inProgress);                                 // Vote in progress
    data << uint8(agreeNum >= lfg::LFG_GROUP_KICK_VOTES_NEEDED);    // Did succeed
    data << uint8(playerVote != lfg::LFG_ANSWER_PENDING);           // Did Vote
    data << uint8(playerVote == lfg::LFG_ANSWER_AGREE);             // Agree
    data << uint64(boot.victim);                                    // Victim GUID
    data << uint32(votesNum);                                       // Total Votes
    data << uint32(agreeNum);                                       // Agree Count
    data << uint32(secsleft);                                       // Time Left
    data << uint32(lfg::LFG_GROUP_KICK_VOTES_NEEDED);               // Needed Votes
    data << boot.reason.c_str();                                    // Kick reason
    SendPacket(&data);
}

void WorldSession::SendLfgUpdateProposal(lfg::LfgProposal const& proposal)
{
    uint64 guid = GetPlayer()->GetGUID();
    uint64 gguid = proposal.players.find(guid)->second.group;
    bool silent = !proposal.isNew && gguid == proposal.group;
    uint32 dungeonEntry = proposal.dungeonId;
    uint32 queueId = sLFGMgr->GetQueueId(_player->GetGUID());
    time_t joinTime = sLFGMgr->GetQueueJoinTime(_player->GetGUID());

    TC_LOG_DEBUG("lfg", "SMSG_LFG_PROPOSAL_UPDATE %s state: %u",
        GetPlayerInfo().c_str(), proposal.state);

    // show random dungeon if player selected random dungeon and it's not lfg group
    if (!silent)
    {
        lfg::LfgDungeonSet const& playerDungeons = sLFGMgr->GetSelectedDungeons(guid);
        if (playerDungeons.find(proposal.dungeonId) == playerDungeons.end())
            dungeonEntry = (*playerDungeons.begin());
    }

    dungeonEntry = sLFGMgr->GetLFGDungeonEntry(dungeonEntry);

    WorldPacket data(SMSG_LFG_PROPOSAL_UPDATE, 4 + 1 + 4 + 4 + 1 + 1 + proposal.players.size() * (4 + 1 + 1 + 1 + 1 +1));
    data << uint32(joinTime);
    data << uint32(proposal.encounters);                   // Encounters done
    data << uint32(queueId);                               // Queue Id
    data << uint32(3);                                     // Always 3
    data << uint32(dungeonEntry);                          // Dungeon
    data << uint32(proposal.id);                           // Proposal Id
    data << uint8(proposal.state);                         // State

    ObjectGuid guid1 = guid;
    ObjectGuid guid2 = gguid;

    data.WriteBit(guid2[4]);
    data.WriteGuidMask(guid1, 3, 7, 0);
    data.WriteBit(guid2[1]);
    data.WriteBit(silent);
    data.WriteGuidMask(guid1, 4, 5);
    data.WriteBit(guid2[3]);
    data.WriteBits(proposal.players.size(), 23);
    data.WriteBit(guid2[7]);

    for (lfg::LfgProposalPlayerContainer::const_iterator it = proposal.players.begin(); it != proposal.players.end(); ++it)
    {
        lfg::LfgProposalPlayer const& player = it->second;

        if (!player.group)
        {
            data.WriteBit(0);
            data.WriteBit(0);
        }
        else
        {
            data.WriteBit(player.group == proposal.group);      // Is group in dungeon
            data.WriteBit(player.group == gguid);               // Same group as the player
        }

        data.WriteBit(player.accept == lfg::LFG_ANSWER_AGREE);
        data.WriteBit(player.accept != lfg::LFG_ANSWER_PENDING);
        data.WriteBit(it->first == guid);
    }

    data.WriteBit(guid2[5]);
    data.WriteBit(guid1[6]);
    data.WriteGuidMask(guid2, 2, 6);
    data.WriteGuidMask(guid1, 2, 1);
    data.WriteBit(guid2[0]);

    data.WriteByteSeq(guid1[5]);
    data.WriteGuidBytes(guid2, 3, 6);
    data.WriteGuidBytes(guid1, 6, 0);
    data.WriteByteSeq(guid2[5]);
    data.WriteByteSeq(guid1[1]);

    for (lfg::LfgProposalPlayerContainer::const_iterator it = proposal.players.begin(); it != proposal.players.end(); ++it)
    {
        lfg::LfgProposalPlayer const& player = it->second;
        data << uint32(player.role);
    }

    data.WriteByteSeq(guid2[7]);
    data.WriteByteSeq(guid1[4]);
    data.WriteGuidBytes(guid2, 0, 1);
    data.WriteGuidBytes(guid1, 2, 7);
    data.WriteByteSeq(guid2[2]);
    data.WriteByteSeq(guid1[3]);
    data.WriteByteSeq(guid2[4]);

    SendPacket(&data);
}

void WorldSession::SendLfgLfrList(bool update)
{
    TC_LOG_DEBUG("lfg", "SMSG_LFG_LFR_LIST %s update: %u",
        GetPlayerInfo().c_str(), update ? 1 : 0);
    WorldPacket data(SMSG_LFG_UPDATE_SEARCH, 1);
    data << uint8(update);                                 // In Lfg Queue?
    SendPacket(&data);
}

void WorldSession::SendLfgDisabled()
{
    TC_LOG_DEBUG("lfg", "SMSG_LFG_DISABLED %s", GetPlayerInfo().c_str());
    WorldPacket data(SMSG_LFG_DISABLED, 0);
    SendPacket(&data);
}

void WorldSession::SendLfgOfferContinue(uint32 dungeonEntry)
{
    TC_LOG_DEBUG("lfg", "SMSG_LFG_OFFER_CONTINUE %s dungeon entry: %u",
        GetPlayerInfo().c_str(), dungeonEntry);
    WorldPacket data(SMSG_LFG_OFFER_CONTINUE, 4);
    data << uint32(dungeonEntry);
    SendPacket(&data);
}

void WorldSession::SendLfgTeleportError(uint8 err)
{
    TC_LOG_DEBUG("lfg", "SMSG_LFG_TELEPORT_DENIED %s reason: %u",
        GetPlayerInfo().c_str(), err);
    WorldPacket data(SMSG_LFG_TELEPORT_DENIED, 4);
    data << uint32(err);                                   // Error
    SendPacket(&data);
}

/*
void WorldSession::SendLfrUpdateListOpcode(uint32 dungeonEntry)
{
    TC_LOG_DEBUG("network", "SMSG_LFG_UPDATE_LIST %s dungeon entry: %u",
        GetPlayerInfo().c_str(), dungeonEntry);
    WorldPacket data(SMSG_LFG_UPDATE_LIST);
    SendPacket(&data);
}
*/
