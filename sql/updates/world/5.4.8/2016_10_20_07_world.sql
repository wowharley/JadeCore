-- Working for Orc Zone
-- By Bodeguero for JadeCore.

DELETE FROM creature_addon WHERE guid IN (142952 ,142949 ,142950 ,142958 ,142959 ,142944 ,142942 ,142912 ,142914 ,142948 ,297728);
INSERT INTO `creature_addon` (`guid`, `emote`) VALUES ('142952', '1');
INSERT INTO `creature_addon` (`guid`, `emote`) VALUES ('142949', '1');
INSERT INTO `creature_addon` (`guid`, `emote`) VALUES ('142950', '1');
INSERT INTO `creature_addon` (`guid`, `emote`) VALUES ('142958', '1');
INSERT INTO `creature_addon` (`guid`, `emote`) VALUES ('142959', '1');
INSERT INTO `creature_addon` (`guid`, `emote`) VALUES ('142944', '1');
INSERT INTO `creature_addon` (`guid`, `emote`) VALUES ('142942', '1');
INSERT INTO `creature_addon` (`guid`, `emote`) VALUES ('142912', '1');
INSERT INTO `creature_addon` (`guid`, `emote`) VALUES ('142914', '1');
INSERT INTO `creature_addon` (`guid`, `emote`) VALUES ('142948', '1');
INSERT INTO `creature_addon` (`guid`, `emote`) VALUES ('297728', '1');
DELETE FROM creature_template_addon WHERE entry IN (3160,3161,3159,63296,3155,3157,39206,12776,3156,11378,3145);
UPDATE `creature_template` SET `minlevel`='1', `maxlevel`='1', `mindmg`='1', `rangeattacktime`='2000', `unit_flags2`='248', `dynamicflags`='0', `minrangedmg`='1', `InhabitType`='1' WHERE (`entry`='49743');
