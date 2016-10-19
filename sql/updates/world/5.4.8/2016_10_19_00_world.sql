-- Single-Minded Fury
DELETE FROM `spell_script_names` WHERE `spell_id` = 81099;
DELETE FROM `spell_script_names` WHERE `ScriptName` = 'spell_warr_single_minded_furry';

INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES (81099, 'spell_warr_single_minded_furry');
