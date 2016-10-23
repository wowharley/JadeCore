-- Thalnos the Soulrender Script Names

UPDATE `creature_template` SET `ScriptName` = 'boss_thalnos_the_soulrender' WHERE `entry` = 59789;
UPDATE `creature_template` SET `ScriptName` = 'mob_evicted_soul' WHERE `entry` = 59974;
UPDATE `creature_template` SET `ScriptName` = 'mob_fallen_crusader' WHERE `entry` = 59884;
UPDATE `creature_template` SET `ScriptName` = 'mob_empowered_spirit' WHERE `entry` = 59893;
UPDATE `creature_template` SET `ScriptName` = 'mob_empowered_zombie' WHERE `entry` = 59930;

DELETE FROM `spell_script_names` WHERE `ScriptName` = 'spell_spirit_gale';
DELETE FROM `spell_script_names` WHERE `ScriptName` = 'spell_spirit_gale_dot_damage';
DELETE FROM `spell_script_names` WHERE `ScriptName` = 'spell_evict_soul';

INSERT INTO `spell_script_names` VALUES (115289, 'spell_spirit_gale');
INSERT INTO `spell_script_names` VALUES (115291, 'spell_spirit_gale_dot_damage');
INSERT INTO `spell_script_names` VALUES (115297, 'spell_evict_soul');

DELETE FROM `creature_text` WHERE `entry` = 59789;
INSERT INTO `creature_text` VALUES (59789, 0, 0, 'We hunger for vengeance!', 14, 0, 100, 0, 0, 27829, 'Thalnost the Soulrender AGGRO'),
(59789, 1, 0, 'Can this be... the end, at last...?', 14, 0, 100, 0, 0, 27830, 'Thalnost the Soulrender DEATH'),
(59789, 2, 0, 'More... More souls!', 14, 0, 100, 0, 0, 27833, 'Thalnost the Soulrender KILL'),
(59789, 3, 0, 'No rest...for the angry dead!', 14, 0, 100, 0, 0, 27831, 'Thalnost the Soulrender FALLEN CRUSADER'),
(59789, 4, 0, 'Seek out a vessel...and return!', 14, 0, 100, 0, 0, 27834, 'Thalnost the Soulrender EVICTED SOUL'),
(59789, 5, 0, 'Claim a body, and wreak terrible vengeance!', 14, 0, 100, 0, 0, 27835, 'Thalnost the Soulrender EMPOWERING SPIRIT'),
(59789, 6, 0, 'My endless agony shall be yours, as well!', 14, 0, 100, 0, 0, 27832, 'Thalnost the Soulrender INTRO');
