-- Working for Gnomes Starting Zone
-- By Bodeguero for JadeCore.

UPDATE `quest_template` SET `Method`='0' WHERE `Id`='26205';
UPDATE `gameobject_template` SET `ScriptName`='go_detonator' WHERE `entry`='204042';
REPLACE INTO `item_script_names` (`Id`, `ScriptName`) VALUES ('58203', 'item_paint');
REPLACE INTO `item_script_names` (`Id`, `ScriptName`) VALUES ('58200', 'item_techno_granade');
UPDATE `creature_template` SET `ScriptName`='npc_repaired_mechano_tank' WHERE `entry`='42224';
UPDATE `gameobject_template` SET `ScriptName`='go_makeshift_cage' WHERE `entry`='204019';
REPLACE INTO `item_script_names` (`Id`, `ScriptName`) VALUES ('58253', 'item_orbit');
DELETE FROM `creature_queststarter` WHERE (`id`='42224') AND (`quest`='26333');
DELETE FROM creature WHERE id=42860;
DELETE FROM creature WHERE guid=146246;
UPDATE `creature_template` SET `faction_A`='7', `faction_H`='7' WHERE (`entry`='42860');
DELETE FROM gameobject WHERE id=204042;
DELETE FROM  smart_scripts WHERE entryorguid=42563;
INSERT INTO `smart_scripts` VALUES (42563, 0, 1, 0, 1, 0, 100, 0, 0, 0, 0, 0, 33, 42563, 0, 0, 0, 0, 0, 21, 15, 0, 0, 0, 0, 0, 0,'Credit quest 26205');
UPDATE `creature_template` SET `AIName`='SmartAI' WHERE (`entry`='42563');
DELETE FROM creature_template WHERE entry IN (46185,42849,37177,1117,42598,45966,42366,42553,41398,41539);
DELETE FROM `smart_scripts` WHERE `entryorguid` = 1117 AND `source_type` = 0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(1117, '0', '0', '0', '0', '0', '100', '0', '5000', '8000', '19000', '27000', '11', '5164', '0', '0', '0', '0', '0', '2', '0', '0', '0', '0', '0', '0', '0', 'Rockjaw Bonesnapper - In Combat - Cast \'Knockdown\' (No Repeat)');
DELETE FROM `smart_scripts` WHERE `entryorguid` = 42598 AND `source_type` = 0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(42598, '0', '0', '1', '8', '0', '100', '0', '79416', '0', '15000', '17000', '1', '0', '0', '0', '0', '0', '0', '1', '0', '0', '0', '0', '0', '0', '0', 'On Dummy Spell hit Talk'),
(42598, '0', '1', '2', '61', '0', '100', '0', '0', '0', '0', '0', '11', '79424', '2', '0', '0', '0', '0', '1', '0', '0', '0', '0', '0', '0', '0', 'Cast Cleanup Toxic Pool'),
(42598, '0', '2', '0', '61', '0', '100', '0', '0', '0', '0', '0', '11', '79422', '2', '0', '0', '0', '0', '1', '0', '0', '0', '0', '0', '0', '0', 'Cast Toxic Pool Credit to Master');
DELETE FROM `creature_template_addon` WHERE `entry` = '42553';
INSERT INTO `creature_template_addon` (`entry`, `path_id`, `mount`, `bytes1`, `bytes2`, `emote`, `auras`) VALUES ('42553', '0', '0', '0', '257', '0', '');
DELETE FROM `creature_text` WHERE `entry` = 42553;
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`) VALUES
(42553, '0', '0', 'Time to put the finishing touches on my bot.', '12', '0', '100', '0', '0', '0', ''),
(42553, '1', '0', 'At last, it\'s finished.', '12', '0', '100', '0', '0', '0', ''),
(42553, '2', '0', 'Arise my, uh... what shall I call you? How about \'multi-bot\'? Arise, my multi-bot!', '12', '0', '100', '0', '0', '0', ''),
(42553, '3', '0', 'Uh... a couple more tweaks should do it, I think...', '12', '0', '100', '0', '0', '0', '');
DELETE FROM `creature_template_addon` WHERE `entry` = '41398';
INSERT INTO `creature_template_addon` (`entry`, `path_id`, `mount`, `bytes1`, `bytes2`, `emote`, `auras`) VALUES ('41398', '0', '0', '0', '1', '0', '80381');
DELETE FROM `npc_spellclick_spells` WHERE `npc_entry` = 41398;
INSERT INTO `npc_spellclick_spells` (`npc_entry`, `spell_id`, `cast_flags`, `user_type`) VALUES
(41398, '77393', '1', '0');
DELETE FROM `creature_text` WHERE `entry` = 42598;
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`) VALUES
(42598, '0', '0', 'Initiating cleanup ... ...', '12', '0', '100', '0', '0', '0', '');
DELETE FROM `creature_text` WHERE `entry` = 45966;
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`) VALUES
(45966, '0', '0', 'We have to break through those mindless leper gnomes if we want to get out of here alive!', '12', '0', '100', '0', '0', '0', '');
DELETE FROM `creature_text` WHERE `entry` = 42366;
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`) VALUES
(42366, '0', '0', 'We\'re going to have a hard time handling this one alone. I sent a message to the dwarven capital of Ironforge asking for their support.', '12', '0', '100', '0', '0', '0', '');
DELETE FROM `npc_spellclick_spells` WHERE `npc_entry` = 46185;
INSERT INTO `npc_spellclick_spells` (`npc_entry`, `spell_id`, `cast_flags`, `user_type`) VALUES
(46185, '86106', '1', '0');
DELETE FROM `creature_template_addon` WHERE `entry` = '42849';
INSERT INTO `creature_template_addon` (`entry`, `path_id`, `mount`, `bytes1`, `bytes2`, `emote`, `auras`) VALUES ('42849', '0', '31692', '0', '1', '0', '');
DELETE FROM `creature_template_addon` WHERE `entry` = '37177';
INSERT INTO `creature_template_addon` (`entry`, `path_id`, `mount`, `bytes1`, `bytes2`, `emote`, `auras`) VALUES ('37177', '0', '0', '0', '257', '0', '');
DELETE FROM `smart_scripts` WHERE `entryorguid` = 37177 AND `source_type` = 0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(37177, '0', '0', '1', '4', '0', '100', '1', '0', '0', '0', '0', '21', '0', '0', '0', '0', '0', '0', '1', '0', '0', '0', '0', '0', '0', '0', 'Stop Moving on Aggro'),
(37177, '0', '1', '2', '61', '0', '100', '1', '0', '0', '0', '0', '11', '6660', '0', '0', '0', '0', '0', '2', '0', '0', '0', '0', '0', '0', '0', 'Cast Shoot on Aggro'),
(37177, '0', '2', '3', '61', '0', '100', '1', '0', '0', '0', '0', '20', '0', '0', '0', '0', '0', '0', '1', '0', '0', '0', '0', '0', '0', '0', 'Stop Melee Attack on Aggro'),
(37177, '0', '3', '0', '61', '0', '100', '1', '0', '0', '0', '0', '22', '1', '0', '0', '0', '0', '0', '1', '0', '0', '0', '0', '0', '0', '0', 'Set Phase 1 on Aggro'),
(37177, '0', '4', '5', '9', '1', '100', '0', '5', '30', '2300', '3900', '11', '6660', '0', '0', '0', '0', '0', '2', '0', '0', '0', '0', '0', '0', '0', 'Cast Shoot'),
(37177, '0', '5', '0', '61', '1', '100', '0', '0', '0', '0', '0', '40', '2', '0', '0', '0', '0', '0', '1', '0', '0', '0', '0', '0', '0', '0', 'Set Ranged Weapon Model'),
(37177, '0', '6', '7', '9', '1', '100', '0', '30', '80', '0', '0', '21', '1', '0', '0', '0', '0', '0', '1', '0', '0', '0', '0', '0', '0', '0', 'Start Moving when not in Shoot Range'),
(37177, '0', '7', '0', '61', '1', '100', '0', '0', '0', '0', '0', '20', '1', '0', '0', '0', '0', '0', '1', '0', '0', '0', '0', '0', '0', '0', 'Start Melee Attack when not in Shoot Range'),
(37177, '0', '8', '9', '9', '1', '100', '0', '0', '10', '0', '0', '21', '1', '0', '0', '0', '0', '0', '1', '0', '0', '0', '0', '0', '0', '0', 'Start Moving when not in Shoot Range'),
(37177, '0', '9', '10', '61', '1', '100', '0', '0', '0', '0', '0', '40', '1', '0', '0', '0', '0', '0', '1', '0', '0', '0', '0', '0', '0', '0', 'Set Melee Weapon Model when not in Shoot Range'),
(37177, '0', '10', '0', '61', '1', '100', '0', '0', '0', '0', '0', '20', '1', '0', '0', '0', '0', '0', '1', '0', '0', '0', '0', '0', '0', '0', 'Start Melee Attack when not in Shoot Range'),
(37177, '0', '11', '12', '9', '1', '100', '0', '11', '25', '0', '0', '21', '0', '0', '0', '0', '0', '0', '1', '0', '0', '0', '0', '0', '0', '0', 'Stop Moving at 25 Yards'),
(37177, '0', '12', '13', '61', '1', '100', '0', '0', '0', '0', '0', '20', '0', '0', '0', '0', '0', '0', '1', '0', '0', '0', '0', '0', '0', '0', 'Stop Melee Attack at 25 Yards'),
(37177, '0', '13', '0', '61', '1', '100', '0', '0', '0', '0', '0', '40', '2', '0', '0', '0', '0', '0', '1', '0', '0', '0', '0', '0', '0', '0', 'Set Ranged Weapon Model at 25 Yards'),
(37177, '0', '14', '15', '7', '1', '100', '1', '0', '0', '0', '0', '40', '1', '0', '0', '0', '0', '0', '1', '0', '0', '0', '0', '0', '0', '0', 'Set Melee Weapon Model on Evade'),
(37177, '0', '15', '0', '61', '1', '100', '1', '0', '0', '0', '0', '22', '0', '0', '0', '0', '0', '0', '1', '0', '0', '0', '0', '0', '0', '0', 'Reset on Evade');
DELETE FROM  gossip_menu_option WHERE menu_id=11662;
INSERT INTO `gossip_menu_option` (`menu_id`, `id`, `option_icon`, `option_text`, `option_id`, `npc_option_npcflag`, `action_menu_id`, `action_poi_id`, `box_coded`, `box_money`, `box_text`) VALUES (11662, 0, 0, 'I\'m ready to start the assault', 0, 0, 0, 0, 0, 0, NULL);
UPDATE `creature_template` SET `AIName`='' WHERE (`entry`='37177');

