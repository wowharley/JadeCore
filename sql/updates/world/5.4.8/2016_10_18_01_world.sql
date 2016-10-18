-- Update ScriptName.
-- By Bodeguero for JadeCore.

DELETE FROM `spell_script_names` WHERE `ScriptName` = 'spell_raging_blow';
DELETE FROM `spell_script_names` WHERE `ScriptName` = 'spell_raging_blow_proc';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES (12880, 'spell_raging_blow_proc');
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES (85288, 'spell_raging_blow');