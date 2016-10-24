-- Immerseus Script Names

UPDATE `creature_template` SET `ScriptName` = 'boss_immerseus' WHERE `entry` = 71543;
UPDATE `creature_template` SET `ScriptName` = 'mob_sha_puddle' WHERE `entry` = 71603;
UPDATE `creature_template` SET `ScriptName` = 'mob_contaminated_puddle' WHERE `entry` = 71604;
UPDATE `creature_template` SET `ScriptName` = 'mob_sha_pool' WHERE `entry` = 71544;
UPDATE `creature_template` SET `ScriptName` = 'mob_swirl_target' WHERE `entry` = 71550;
UPDATE `creature_template` SET `ScriptName` = 'mob_swirl_zone' WHERE `entry` = 71548;

DELETE FROM `spell_script_names` WHERE `ScriptName` = 'spell_seeping_sha_damage';
DELETE FROM `spell_script_names` WHERE `ScriptName` = 'spell_split';
DELETE FROM `spell_script_names` WHERE `ScriptName` = 'spell_swirl';
DELETE FROM `spell_script_names` WHERE `ScriptName` = 'spell_swirl_damage';
DELETE FROM `spell_script_names` WHERE `ScriptName` = 'spell_sha_bolt_missile';

INSERT INTO `spell_script_names` VALUES (143281, 'spell_seeping_sha_damage'),
(143020, 'spell_split'),
(143309, 'spell_swirl'),
(143412, 'spell_swirl_damage'),
(129067, 'spell_sha_bolt_missile'),
