--Single-Minded Fury--
DELETE FROM `spell_script_names` WHERE `spell_id` = 100130;
DELETE FROM `spell_script_names` WHERE `ScriptName` = 'spell_warr_wild_strike';

INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES (100130, spell_warr_wild_strike);
