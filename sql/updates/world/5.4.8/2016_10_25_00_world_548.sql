SET @LSW_ENTRY = 10181;
SET @BB_ENTRY = 36648;
SET @GH_ENTRY = 39605;
SET @FW_ENTRY = 42131;
SET @MB_ENTRY = 42928;
SET @PV_ENTRY = 17468;
SET @TW_ENTRY = 7999;
SET @KVW_ENTRY = 29611;

UPDATE `creature_template` SET `AIName`="", `scriptname`="boss_lady_sylvanas_windrunner" WHERE `entry`=@LSW_ENTRY;
UPDATE `creature_template` SET `AIName`="", `scriptname`="boss_baine_bloodhoof" WHERE `entry`=@BB_ENTRY;
UPDATE `creature_template` SET `AIName`="", `scriptname`="boss_garrosh_hellscream" WHERE `entry`=@GH_ENTRY;
UPDATE `creature_template` SET `AIName`="", `scriptname`="boss_falstad_wildhammer" WHERE `entry`=@FW_ENTRY;
UPDATE `creature_template` SET `AIName`="", `scriptname`="boss_muradin_bronzebeard" WHERE `entry`=@MB_ENTRY;
UPDATE `creature_template` SET `AIName`="", `scriptname`="boss_prophet_velen" WHERE `entry`=@PV_ENTRY;
UPDATE `creature_template` SET `AIName`="", `scriptname`="boss_tyrande_whisperwind" WHERE `entry`=@TW_ENTRY;
UPDATE `creature_template` SET `AIName`="", `scriptname`="boss_varian_wrynn" WHERE `entry`=@KVW_ENTRY;

DELETE FROM `smart_scripts` WHERE `entryorguid` IN (@LSW_ENTRY, @BB_ENTRY, @GH_ENTRY, @FW_ENTRY, @MB_ENTRY, @PV_ENTRY, @TW_ENTRY, @KVW_ENTRY) AND `source_type`=0;

DELETE FROM `creature_text` WHERE `entry` IN (@TW_ENTRY, @KVW_ENTRY);
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`) VALUES
(@TW_ENTRY, 0, 0, 'Glory to the Alliance!', 14, 0, 50, 0, 0, 0, 'Tyrande Whisperwind'),
(@TW_ENTRY, 1, 0, 'Oh no...', 14, 0, 50, 0, 0, 0, 'Tyrande Whisperwind'),
(@KVW_ENTRY, 0, 0, 'Protect my son against the, $c.', 14, 0, 50, 0, 0, 0, 'Varian Wrynn'),
(@KVW_ENTRY, 0, 1, 'Glory to the Alliance! People of Stormwind! Citizens of the Alliance! Your king speaks!', 14, 0, 50, 0, 0, 0, 'Varian Wrynn'),
(@KVW_ENTRY, 1, 0, 'Guards! Guards! Kill the, $r.', 14, 0, 50, 0, 0, 0, 'Varian Wrynn'),
(@KVW_ENTRY, 1, 1, 'Not in my kingdom, $r.', 14, 0, 50, 0, 0, 0, 'Varian Wrynn'),
(@KVW_ENTRY, 2, 0, 'You will welcome these former heroes of the Alliance and treat them with the respect that you would give to any ally of Stormwind!', 14, 0, 50, 0, 0, 0, 'Varian Wrynn');
