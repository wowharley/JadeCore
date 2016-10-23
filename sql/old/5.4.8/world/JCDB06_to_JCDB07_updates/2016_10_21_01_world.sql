--  SAI
SET @ENTRY := 1117;
UPDATE `creature_template` SET `AIName`="" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
-- Actionlist SAI
SET @ENTRY := 2398200;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=9;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,9,0,0,0,0,100,1,0,0,0,0,17,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Remove work emote"),
(@ENTRY,9,1,0,0,0,100,1,0,0,0,0,28,17743,0,0,0,0,0,1,0,0,0,0,0,0,0,"Remove Sleep Spell (just in case)"),
(@ENTRY,9,3,0,0,0,100,1,2400,2400,0,0,66,0,0,0,0,0,0,8,0,0,0,0,0,0,3.06,"At woodpile, face woodpile"),
(@ENTRY,9,4,0,0,0,100,1,100,100,0,0,11,68442,2,0,0,0,0,1,0,0,0,0,0,0,0,"At woodpile, kneel"),
(@ENTRY,9,5,0,0,0,100,1,5000,5000,0,0,28,68442,0,0,0,0,0,1,0,0,0,0,0,0,0,"Remove kneel aura"),
(@ENTRY,9,7,0,0,0,100,1,2400,2400,0,0,1,1,0,0,0,0,0,1,0,0,0,0,0,0,0,"At tree, say 'Work, Work'"),
(@ENTRY,9,8,0,0,0,100,1,0,0,0,0,17,234,0,0,0,0,0,1,0,0,0,0,0,0,0,"At tree, set work emote"),
(@ENTRY,9,9,0,0,0,100,1,20000,20000,0,0,17,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Remove Work Aura"),
(@ENTRY,9,11,0,0,0,100,1,2400,2400,0,0,66,0,0,0,0,0,0,8,0,0,0,0,0,0,3.06,"At woodpile, face woodpile"),
(@ENTRY,9,12,0,0,0,100,1,100,100,0,0,11,68442,2,0,0,0,0,1,0,0,0,0,0,0,0,"At woodpile, kneel"),
(@ENTRY,9,13,0,0,0,100,1,5000,5000,0,0,28,68442,0,0,0,0,0,1,0,0,0,0,0,0,0,"Remove kneel aura"),
(@ENTRY,9,15,0,0,0,100,1,2400,2400,0,0,1,1,0,0,0,0,0,1,0,0,0,0,0,0,0,"At tree, say 'Work, Work'"),
(@ENTRY,9,16,0,0,0,100,1,0,0,0,0,17,234,0,0,0,0,0,1,0,0,0,0,0,0,0,"At tree, set work emote"),
(@ENTRY,9,17,0,0,0,100,1,20000,20000,0,0,17,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Remove Work Aura"),
(@ENTRY,9,19,0,0,0,100,1,2400,2400,0,0,66,0,0,0,0,0,0,8,0,0,0,0,0,0,3.06,"At woodpile, face woodpile"),
(@ENTRY,9,20,0,0,0,100,1,100,100,0,0,11,68442,2,0,0,0,0,1,0,0,0,0,0,0,0,"At woodpile, kneel"),
(@ENTRY,9,23,0,0,0,100,1,2400,2400,0,0,1,1,0,0,0,0,0,1,0,0,0,0,0,0,0,"At tree, say 'Work, Work'"),
(@ENTRY,9,24,0,0,0,100,1,0,0,0,0,17,234,0,0,0,0,0,1,0,0,0,0,0,0,0,"At tree, set work emote");
--  SAI
SET @ENTRY := 37177;
UPDATE `creature_template` SET `AIName`="" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
--  SAI
SET @ENTRY := 37070;
UPDATE `creature_template` SET `AIName`="" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
-- Gnomeregan Stealth Fighter SAI
SET @ENTRY := 39039;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,64,0,100,0,0,0,0,0,10,1,3,5,6,0,0,1,0,0,0,0,0,0,0,"on gossip set emote"),
(@ENTRY,0,1,0,5,0,100,1,0,0,0,39039,41,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"On die force despawn self");
--  SAI
SET @ENTRY := 42563;
UPDATE `creature_template` SET `AIName`="" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
--  SAI
SET @ENTRY := 42598;
UPDATE `creature_template` SET `AIName`="" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
-- Scarlet Corpse SAI
SET @ENTRY := 49340;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,1,8,0,100,0,91942,0,0,0,45,0,3,0,0,0,0,19,49337,10,0,0,0,0,0,"on spellhit 91942 set data 3 to darnell"),
(@ENTRY,0,2,0,61,0,100,0,0,0,0,0,11,46598,0,0,0,0,0,19,49337,0,0,0,0,0,0,"Jump on darnell"),
(@ENTRY,0,2,3,61,0,100,0,0,0,0,0,11,46598,0,0,0,0,0,19,49337,0,0,0,0,0,0,"Jump on darnell"),
(@ENTRY,0,3,0,61,0,100,1,0,0,0,0,41,1000,0,0,0,0,0,1,0,0,0,0,0,0,0,"delete corpse");
-- Rivett Clutchpop SAI
SET @ENTRY := 55146;
UPDATE `creature_template` SET `AIName`="" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
-- Henze Faulk SAI
SET @ENTRY := 6172;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,1,11,0,100,0,0,0,0,0,11,29266,0,0,0,0,0,1,0,0,0,0,0,0,0,"Henze Faulk - On spawn - add aura"),
(@ENTRY,0,1,0,61,0,100,0,0,0,0,0,22,1,0,0,0,0,0,1,0,0,0,0,0,0,0,"Henze Faulk - On spawn - set phase 1"),
(@ENTRY,0,2,0,8,1,100,0,8593,0,0,0,80,@ENTRY*100+00,0,0,0,0,0,1,0,0,0,0,0,0,0,"Henze Faulk - On spellhit - run script (phase 1)");
DELETE FROM `creature_template_addon` WHERE (`entry`=42218);
DELETE FROM `creature_template_addon` WHERE (`entry`=1642);
-- Faction Chosen Credit SAI
SET @ENTRY := 64594;
UPDATE `creature_template` SET `AIName`="" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
-- Challenger Torch Lit Credit SAI
SET @ENTRY := 56048;
UPDATE `creature_template` SET `AIName`="" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
-- Speak with Shen-zin Su Credit SAI
SET @ENTRY := 55939;
UPDATE `creature_template` SET `AIName`="" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
-- Board Hot Air Balloon Credit SAI
SET @ENTRY := 56378;
UPDATE `creature_template` SET `AIName`="" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
-- Planting Stave Credit SAI
SET @ENTRY := 56688;
UPDATE `creature_template` SET `AIName`="" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
-- Explosion Triggered Credit SAI
SET @ENTRY := 60727;
UPDATE `creature_template` SET `AIName`="" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
-- Sergeant Gorrok SAI
SET @ENTRY := 55162;
UPDATE `creature_template` SET `AIName`="" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
-- Shokia SAI
SET @ENTRY := 55170;
UPDATE `creature_template` SET `AIName`="" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
-- Shademaster Kiryn SAI
SET @ENTRY := 55141;
UPDATE `creature_template` SET `AIName`="" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
-- Balance Pole Bell Credit SAI
SET @ENTRY := 55077;
UPDATE `creature_template` SET `AIName`="" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
-- Shu SAI
SET @ENTRY := 55212;
UPDATE `creature_template` SET `AIName`="" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
-- Quest - Jade Forest (Lay of the Land Kill Credit 01) - JSB SAI
SET @ENTRY := 63058;
UPDATE `creature_template` SET `AIName`="" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
-- Quest - Jade Forest (Lay of the Land Kill Credit 02) - JSB SAI
SET @ENTRY := 63059;
UPDATE `creature_template` SET `AIName`="" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
-- Actionlist SAI
SET @ENTRY := 2398200;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=9;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,9,0,0,0,0,100,1,0,0,0,0,17,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Remove work emote"),
(@ENTRY,9,1,0,0,0,100,1,0,0,0,0,28,17743,0,0,0,0,0,1,0,0,0,0,0,0,0,"Remove Sleep Spell (just in case)"),
(@ENTRY,9,3,0,0,0,100,1,2400,2400,0,0,66,0,0,0,0,0,0,8,0,0,0,0,0,0,3.06,"At woodpile, face woodpile"),
(@ENTRY,9,4,0,0,0,100,1,100,100,0,0,11,68442,2,0,0,0,0,1,0,0,0,0,0,0,0,"At woodpile, kneel"),
(@ENTRY,9,5,0,0,0,100,1,5000,5000,0,0,28,68442,0,0,0,0,0,1,0,0,0,0,0,0,0,"Remove kneel aura"),
(@ENTRY,9,7,0,0,0,100,1,2400,2400,0,0,1,1,0,0,0,0,0,1,0,0,0,0,0,0,0,"At tree, say 'Work, Work'"),
(@ENTRY,9,8,0,0,0,100,1,0,0,0,0,17,234,0,0,0,0,0,1,0,0,0,0,0,0,0,"At tree, set work emote"),
(@ENTRY,9,9,0,0,0,100,1,20000,20000,0,0,17,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Remove Work Aura"),
(@ENTRY,9,11,0,0,0,100,1,2400,2400,0,0,66,0,0,0,0,0,0,8,0,0,0,0,0,0,3.06,"At woodpile, face woodpile"),
(@ENTRY,9,12,0,0,0,100,1,100,100,0,0,11,68442,2,0,0,0,0,1,0,0,0,0,0,0,0,"At woodpile, kneel"),
(@ENTRY,9,13,0,0,0,100,1,5000,5000,0,0,28,68442,0,0,0,0,0,1,0,0,0,0,0,0,0,"Remove kneel aura"),
(@ENTRY,9,15,0,0,0,100,1,2400,2400,0,0,1,1,0,0,0,0,0,1,0,0,0,0,0,0,0,"At tree, say 'Work, Work'"),
(@ENTRY,9,16,0,0,0,100,1,0,0,0,0,17,234,0,0,0,0,0,1,0,0,0,0,0,0,0,"At tree, set work emote"),
(@ENTRY,9,17,0,0,0,100,1,20000,20000,0,0,17,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Remove Work Aura"),
(@ENTRY,9,19,0,0,0,100,1,2400,2400,0,0,66,0,0,0,0,0,0,8,0,0,0,0,0,0,3.06,"At woodpile, face woodpile"),
(@ENTRY,9,20,0,0,0,100,1,100,100,0,0,11,68442,2,0,0,0,0,1,0,0,0,0,0,0,0,"At woodpile, kneel"),
(@ENTRY,9,23,0,0,0,100,1,2400,2400,0,0,1,1,0,0,0,0,0,1,0,0,0,0,0,0,0,"At tree, say 'Work, Work'"),
(@ENTRY,9,24,0,0,0,100,1,0,0,0,0,17,234,0,0,0,0,0,1,0,0,0,0,0,0,0,"At tree, set work emote");
-- Actionlist SAI
SET @ENTRY := 2414100;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=9;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,9,0,0,0,0,100,1,0,0,0,0,17,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Remove work emote"),
(@ENTRY,9,1,0,0,0,100,1,0,0,0,0,28,17743,0,0,0,0,0,1,0,0,0,0,0,0,0,"Remove Sleep Spell (just in case)"),
(@ENTRY,9,3,0,0,0,100,1,2000,2000,0,0,66,0,0,0,0,0,0,8,0,0,0,0,0,0,6.18,"At woodpile, face woodpile"),
(@ENTRY,9,4,0,0,0,100,1,100,100,0,0,11,68442,2,0,0,0,0,1,0,0,0,0,0,0,0,"At woodpile, kneel"),
(@ENTRY,9,5,0,0,0,100,1,5000,5000,0,0,28,68442,0,0,0,0,0,1,0,0,0,0,0,0,0,"Remove kneel aura"),
(@ENTRY,9,7,0,0,0,100,1,2000,2000,0,0,1,1,0,0,0,0,0,1,0,0,0,0,0,0,0,"At tree, say 'Work, Work'"),
(@ENTRY,9,8,0,0,0,100,1,0,0,0,0,17,234,0,0,0,0,0,1,0,0,0,0,0,0,0,"At tree, set work emote"),
(@ENTRY,9,9,0,0,0,100,1,20000,20000,0,0,17,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Remove Work Aura"),
(@ENTRY,9,11,0,0,0,100,1,2000,2000,0,0,66,0,0,0,0,0,0,8,0,0,0,0,0,0,6.18,"At woodpile, face woodpile"),
(@ENTRY,9,12,0,0,0,100,1,100,100,0,0,11,68442,2,0,0,0,0,1,0,0,0,0,0,0,0,"At woodpile, kneel"),
(@ENTRY,9,13,0,0,0,100,1,5000,5000,0,0,28,68442,0,0,0,0,0,1,0,0,0,0,0,0,0,"Remove kneel aura"),
(@ENTRY,9,15,0,0,0,100,1,2000,2000,0,0,1,1,0,0,0,0,0,1,0,0,0,0,0,0,0,"At tree, say 'Work, Work'"),
(@ENTRY,9,16,0,0,0,100,1,0,0,0,0,17,234,0,0,0,0,0,1,0,0,0,0,0,0,0,"At tree, set work emote"),
(@ENTRY,9,17,0,0,0,100,1,20000,20000,0,0,17,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Remove Work Aura"),
(@ENTRY,9,19,0,0,0,100,1,2000,2000,0,0,66,0,0,0,0,0,0,8,0,0,0,0,0,0,6.18,"At woodpile, face woodpile"),
(@ENTRY,9,20,0,0,0,100,1,100,100,0,0,11,68442,2,0,0,0,0,1,0,0,0,0,0,0,0,"At woodpile, kneel"),
(@ENTRY,9,21,0,0,0,100,1,5000,5000,0,0,28,68442,0,0,0,0,0,1,0,0,0,0,0,0,0,"Remove kneel aura"),
(@ENTRY,9,23,0,0,0,100,1,2000,2000,0,0,1,1,0,0,0,0,0,1,0,0,0,0,0,0,0,"At tree, say 'Work, Work'"),
(@ENTRY,9,24,0,0,0,100,1,0,0,0,0,17,234,0,0,0,0,0,1,0,0,0,0,0,0,0,"At tree, set work emote");
-- Actionlist SAI
SET @ENTRY := 2415020;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=9;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,9,0,0,0,0,100,1,0,0,0,0,17,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Remove work emote"),
(@ENTRY,9,1,0,0,0,100,1,0,0,0,0,28,17743,0,0,0,0,0,1,0,0,0,0,0,0,0,"Remove Sleep Spell (just in case)"),
(@ENTRY,9,3,0,0,0,100,1,3000,3000,0,0,66,0,0,0,0,0,0,8,0,0,0,0,0,0,2.2,"At woodpile, face woodpile"),
(@ENTRY,9,4,0,0,0,100,1,100,100,0,0,11,68442,2,0,0,0,0,1,0,0,0,0,0,0,0,"At woodpile, kneel"),
(@ENTRY,9,5,0,0,0,100,1,5000,5000,0,0,28,68442,0,0,0,0,0,1,0,0,0,0,0,0,0,"Remove kneel aura"),
(@ENTRY,9,7,0,0,0,100,1,3000,3000,0,0,1,1,0,0,0,0,0,1,0,0,0,0,0,0,0,"At tree, say 'Work, Work'"),
(@ENTRY,9,8,0,0,0,100,1,0,0,0,0,17,234,0,0,0,0,0,1,0,0,0,0,0,0,0,"At tree, set work emote"),
(@ENTRY,9,9,0,0,0,100,1,20000,20000,0,0,17,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Remove Work Aura"),
(@ENTRY,9,11,0,0,0,100,1,3000,3000,0,0,66,0,0,0,0,0,0,8,0,0,0,0,0,0,2.2,"At woodpile, face woodpile"),
(@ENTRY,9,12,0,0,0,100,1,100,100,0,0,11,68442,2,0,0,0,0,1,0,0,0,0,0,0,0,"At woodpile, kneel"),
(@ENTRY,9,13,0,0,0,100,1,5000,5000,0,0,28,68442,0,0,0,0,0,1,0,0,0,0,0,0,0,"Remove kneel aura"),
(@ENTRY,9,15,0,0,0,100,1,3000,3000,0,0,1,1,0,0,0,0,0,1,0,0,0,0,0,0,0,"At tree, say 'Work, Work'"),
(@ENTRY,9,16,0,0,0,100,1,0,0,0,0,17,234,0,0,0,0,0,1,0,0,0,0,0,0,0,"At tree, set work emote"),
(@ENTRY,9,17,0,0,0,100,1,20000,20000,0,0,17,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Remove Work Aura"),
(@ENTRY,9,19,0,0,0,100,1,3000,3000,0,0,66,0,0,0,0,0,0,8,0,0,0,0,0,0,2.2,"At woodpile, face woodpile"),
(@ENTRY,9,20,0,0,0,100,1,100,100,0,0,11,68442,2,0,0,0,0,1,0,0,0,0,0,0,0,"At woodpile, kneel"),
(@ENTRY,9,21,0,0,0,100,1,5000,5000,0,0,28,68442,0,0,0,0,0,1,0,0,0,0,0,0,0,"Remove kneel aura"),
(@ENTRY,9,23,0,0,0,100,1,3000,3000,0,0,1,1,0,0,0,0,0,1,0,0,0,0,0,0,0,"At tree, say 'Work, Work'"),
(@ENTRY,9,24,0,0,0,100,1,0,0,0,0,17,234,0,0,0,0,0,1,0,0,0,0,0,0,0,"At tree, set work emote");

-- Actionlist SAI
SET @ENTRY := 2425620;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=9;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,9,0,0,0,0,100,1,0,0,0,0,17,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Remove work emote"),
(@ENTRY,9,1,0,0,0,100,1,0,0,0,0,28,17743,0,0,0,0,0,1,0,0,0,0,0,0,0,"Remove Sleep Spell (just in case)"),
(@ENTRY,9,3,0,0,0,100,1,4500,4500,0,0,66,0,0,0,0,0,0,8,0,0,0,0,0,0,2.2,"At woodpile, face woodpile"),
(@ENTRY,9,4,0,0,0,100,1,100,100,0,0,11,68442,2,0,0,0,0,1,0,0,0,0,0,0,0,"At woodpile, kneel"),
(@ENTRY,9,5,0,0,0,100,1,5000,5000,0,0,28,68442,0,0,0,0,0,1,0,0,0,0,0,0,0,"Remove kneel aura"),
(@ENTRY,9,7,0,0,0,100,1,4500,4500,0,0,1,1,0,0,0,0,0,1,0,0,0,0,0,0,0,"At tree, say 'Work, Work'"),
(@ENTRY,9,8,0,0,0,100,1,0,0,0,0,17,234,0,0,0,0,0,1,0,0,0,0,0,0,0,"At tree, set work emote"),
(@ENTRY,9,9,0,0,0,100,1,20000,20000,0,0,17,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Remove Work Aura"),
(@ENTRY,9,11,0,0,0,100,1,4500,4500,0,0,66,0,0,0,0,0,0,8,0,0,0,0,0,0,2.2,"At woodpile, face woodpile"),
(@ENTRY,9,12,0,0,0,100,1,100,100,0,0,11,68442,2,0,0,0,0,1,0,0,0,0,0,0,0,"At woodpile, kneel"),
(@ENTRY,9,13,0,0,0,100,1,5000,5000,0,0,28,68442,0,0,0,0,0,1,0,0,0,0,0,0,0,"Remove kneel aura"),
(@ENTRY,9,15,0,0,0,100,1,4500,4500,0,0,1,1,0,0,0,0,0,1,0,0,0,0,0,0,0,"At tree, say 'Work, Work'"),
(@ENTRY,9,16,0,0,0,100,1,0,0,0,0,17,234,0,0,0,0,0,1,0,0,0,0,0,0,0,"At tree, set work emote"),
(@ENTRY,9,17,0,0,0,100,1,20000,20000,0,0,17,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Remove Work Aura"),
(@ENTRY,9,19,0,0,0,100,1,4500,4500,0,0,66,0,0,0,0,0,0,8,0,0,0,0,0,0,2.2,"At woodpile, face woodpile"),
(@ENTRY,9,20,0,0,0,100,1,100,100,0,0,11,68442,2,0,0,0,0,1,0,0,0,0,0,0,0,"At woodpile, kneel"),
(@ENTRY,9,21,0,0,0,100,1,5000,5000,0,0,28,68442,0,0,0,0,0,1,0,0,0,0,0,0,0,"Remove kneel aura"),
(@ENTRY,9,23,0,0,0,100,1,4500,4500,0,0,1,1,0,0,0,0,0,1,0,0,0,0,0,0,0,"At tree, say 'Work, Work'"),
(@ENTRY,9,24,0,0,0,100,1,0,0,0,0,17,234,0,0,0,0,0,1,0,0,0,0,0,0,0,"At tree, set work emote");

