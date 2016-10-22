# Copyright (C) 2013-2016 JadeCore <https://www.jadecore.tk/>
# Copyright (C) 2008-2016 TrinityCore <http://www.trinitycore.org/>
# Copyright (C) 2011-2016 Project SkyFire <http://www.projectskyfire.org/>
# Copyright (C) 2005-2009 MaNGOS <http://getmangos.com/>
# Copyright (C) 2006-2009 ScriptDev2 <https://scriptdev2.svn.sourceforge.net/>
#
# This program is free software; you can redistribute it and/or modify it
# under the terms of the GNU General Public License as published by the
# Free Software Foundation; either version 2 of the License, or (at your
# option) any later version.
#
# This program is distributed in the hope that it will be useful, but WITHOUT
# ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
# FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
# more details.
#
# You should have received a copy of the GNU General Public License along
# with this program. If not, see <http://www.gnu.org/licenses/>.

set(scripts_STAT_SRCS
  ${scripts_STAT_SRCS}
  Pet/pet_dk.cpp
  Pet/pet_generic.cpp
  Pet/pet_hunter.cpp
  Pet/pet_mage.cpp
  Pet/pet_monk.cpp
  Pet/pet_priest.cpp
  Pet/pet_shaman.cpp
  Pet/pet_warlock.cpp
  Pet/pet_paladin.cpp
)

message("  -> Prepared: Pet")
