-- Some Fix
-- By Bodeguero for JadeCore.

DELETE FROM `vehicle_template_accessory` WHERE `entry` = 61463;
INSERT INTO `vehicle_template_accessory` (`entry`, `accessory_entry`, `seat_id`, `minion`, `description`, `summontype`, `summontimer`) VALUES
(61463, 61800, 0, 1, 'Slagmaw', 6, 1000);
DELETE FROM `npc_spellclick_spells` WHERE `npc_entry` = 61463;
INSERT INTO `npc_spellclick_spells` (`npc_entry`, `spell_id`, `cast_flags`, `user_type`) VALUES
(61463, 88066, 1, 0);


