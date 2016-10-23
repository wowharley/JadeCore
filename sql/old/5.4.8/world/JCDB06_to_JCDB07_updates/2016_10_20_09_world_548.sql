-- Working for Pandaren Starting Zone
-- By Bodeguero for JadeCore.

UPDATE `creature_template` SET `ScriptName`='mob_shu_water_spirit' WHERE `entry`='55212';
UPDATE `creature_template` SET `ScriptName`='npc_li_fei' WHERE `entry`='54135';
UPDATE `creature_template` SET `ScriptName`='boss_li_fei_fight' WHERE `entry`='54734';
DELETE FROM `creature` WHERE `id`='54734';
UPDATE `quest_template` SET `Method`='2' WHERE `Id`='29679';
UPDATE `quest_template` SET `RequiredNpcOrGoCount1`='5' WHERE `Id`='29679';
DELETE FROM `creature` where `id` = '65493' and `guid` != '295874';
UPDATE `creature_template` SET `AIName`='SmartAI' WHERE entry IN (59591,53566);
DELETE FROM smart_scripts WHERE entryorguid In (59591,53566);
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES (53566, 0, 0, 0, 19, 0, 100, 0, 0, 0, 0, 0, 85, 114611, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 'Master Shang Xi - Quest accepted - Cast Spell on player spell that give item required');
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES (59591, 0, 0, 0, 19, 0, 100, 0, 0, 0, 0, 0, 85, 114746, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 'The Master Flame - On quest accepted - Cast Spell on player spell of animation');
UPDATE `quest_template` SET `RequiredNpcOrGo1`='0' WHERE (`Id`='29679');
UPDATE `gameobject_template` SET `data2`='0', `data3`='0', `data5`='0' WHERE entry  IN (209575,20576,209577);
UPDATE `gameobject_template` SET `data2`='3000' WHERE (`entry`='209971');
UPDATE creature_template SET MovementType=1 WHERE entry=57797;
UPDATE `creature` SET `MovementType`='1', `spawndist`='6' WHERE id=57797;
UPDATE creature_template SET MovementType=1 WHERE entry=57205;
UPDATE `creature` SET `MovementType`='1', `spawndist`='5' WHERE id=57205;
DELETE FROM creature_model_info WHERE modelid IN (18035,20770,20870,41424);
UPDATE creature SET phaseMask=1 WHERE phaseMask=0;
UPDATE gameobject SET phaseMask=1 WHERE phaseMask=0;
UPDATE creature SET equipment_id=0 WHERE equipment_id=69296;
