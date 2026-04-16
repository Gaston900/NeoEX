-- license:BSD-3-Clause
-- copyright-holders:Gaston90
---------------------------------------------------
--   NEOEX target makefile
---------------------------------------------------

---------------------------------------------------
-- specify available CPU cores
---------------------------------------------------

CPUS["Z80"] = true -- NEOGEO
CPUS["M680X0"] = true -- NEOGEO
CPUS["DSP16"] = true -- CPS1
CPUS["I386"] = true -- CPS1
CPUS["PIC16C5X"] = true -- CPS1
CPUS["SH"] = true -- CPS3
CPUS["MCS51"] = true -- 1943
CPUS["M6809"] = true -- GNG
CPUS["M6805"] = true -- TIGEROAD

--------------------------------------------------
-- specify available sound cores
--------------------------------------------------

SOUNDS["SPEAKER"] = true -- NEOGEO
SOUNDS["YM2610"] = true -- NEOGEO
SOUNDS["AY8910"] = true -- CPS1
SOUNDS["MSM5205"] = true -- CPS1
SOUNDS["OKIM6295"] = true -- CPS1
SOUNDS["QSOUND"] = true -- CPS1
SOUNDS["YM2151"] = true -- CPS1
SOUNDS["SN76496"] = true -- EXEDEXES
SOUNDS["YM3812"] = true -- MITCHELL

--------------------------------------------------
-- specify available video cores
--------------------------------------------------

VIDEOS["BUFSPRITE"] = true -- BIONICC

--------------------------------------------------
-- specify available machine cores
--------------------------------------------------

MACHINES["ALPHA_8921"] = true -- NEOGEO
MACHINES["GEN_LATCH"] = true -- NEOGEO
MACHINES["UPD1990A"] = true -- NEOGEO
MACHINES["WATCHDOG"] = true -- NEOGEO
MACHINES["Z80DAISY"] = true -- NEOGEO
MACHINES["TTL74157"] = true -- CPS1
MACHINES["EEPROMDEV"] = true -- CPS1
MACHINES["TIMEKPR"] = true -- CPS1
MACHINES["UPD4701"] = true -- CPS1
MACHINES["INTELFLASH"] = true -- CPS3
MACHINES["NSCSI"] = true -- CPS3
MACHINES["WD33C9X"] = true -- CPS3
MACHINES["NETLIST"] = true -- 1942
MACHINES["I8255"] = true -- KENSEIM
MACHINES["Z80CTC"] = true -- KENSEIM
MACHINES["TTL74259"] = true -- SONSON

--------------------------------------------------
-- specify available bus cores
--------------------------------------------------
BUSES["NSCSI"] = true -- CPS3

--------------------------------------------------
-- this is the list of driver libraries that
-- comprise MAME plus mamedriv.o which contains
-- the list of drivers
--------------------------------------------------

function linkProjects_mame_arcade(_target, _subtarget)
	links {
		"capcom",
		"neogeo",
	}
end

function createMAMEProjects(_target, _subtarget, _name)
	project (_name)
	targetsubdir(_target .."_" .. _subtarget)
	kind (LIBTYPE)
	uuid (os.uuid("drv-" .. _target .."_" .. _subtarget .. "_" .._name))
	addprojectflags()
	precompiledheaders_novs()

	includedirs {
		MAME_DIR .. "src/osd",
		MAME_DIR .. "src/emu",
		MAME_DIR .. "src/devices",
		MAME_DIR .. "src/hbmame/includes",
		MAME_DIR .. "src/hbmame",
		MAME_DIR .. "src/mame",
		MAME_DIR .. "src/lib",
		MAME_DIR .. "src/lib/util",
		MAME_DIR .. "src/lib/netlist",
		MAME_DIR .. "3rdparty",
		MAME_DIR .. "3rdparty/zlib",
		GEN_DIR  .. "mame/layout",
--		GEN_DIR  .. "hbmame/layout",
	}
	includedirs {
		ext_includedir("flac"),
		ext_includedir("glm"),
		ext_includedir("jpeg"),
		ext_includedir("rapidjson"),
	}
end

function createProjects_mame_arcade(_target, _subtarget)
--------------------------------------------------
-- the following files are general components and
-- shared across a number of drivers
--------------------------------------------------

createMAMEProjects(_target, _subtarget, "capcom")
files {
	MAME_DIR .. "src/hbmame/drivers/1942.cpp",
	MAME_DIR .. "src/mame/includes/1942.h",
	MAME_DIR .. "src/mame/video/1942.cpp",
	MAME_DIR .. "src/mame/audio/nl_1942.cpp",
	MAME_DIR .. "src/mame/audio/nl_1942.h",
	MAME_DIR .. "src/hbmame/drivers/1943.cpp",
	MAME_DIR .. "src/mame/includes/1943.h",
	MAME_DIR .. "src/mame/video/1943.cpp",
	MAME_DIR .. "src/mame/drivers/bionicc.cpp",
	MAME_DIR .. "src/mame/drivers/supduck.cpp",
	MAME_DIR .. "src/mame/video/tigeroad_spr.cpp",
	MAME_DIR .. "src/mame/video/tigeroad_spr.h",
	MAME_DIR .. "src/hbmame/drivers/blktiger.cpp",
	MAME_DIR .. "src/mame/drivers/cbasebal.cpp",
	MAME_DIR .. "src/mame/drivers/commando.cpp",
	MAME_DIR .. "src/mame/includes/commando.h",
	MAME_DIR .. "src/mame/video/commando.cpp",
	MAME_DIR .. "src/hbmame/drivers/cps1.cpp",
--	MAME_DIR .. "src/hbmame/includes/cps1.h",
	MAME_DIR .. "src/hbmame/video/cps1.cpp",
	MAME_DIR .. "src/hbmame/drivers/cps1bl_5205.cpp",
	MAME_DIR .. "src/hbmame/drivers/cps1bl_pic.cpp",
	MAME_DIR .. "src/mame/drivers/kenseim.cpp",
	MAME_DIR .. "src/hbmame/drivers/cps2.cpp",
	MAME_DIR .. "src/hbmame/video/cps2.cpp",
	MAME_DIR .. "src/hbmame/drivers/cps3hb.cpp",
	MAME_DIR .. "src/mame/includes/cps3.h",
	MAME_DIR .. "src/mame/audio/cps3.cpp",
	MAME_DIR .. "src/mame/audio/cps3.h",
	MAME_DIR .. "src/mame/drivers/egghunt.cpp",
	MAME_DIR .. "src/mame/drivers/exedexes.cpp",
	MAME_DIR .. "src/mame/includes/exedexes.h",
	MAME_DIR .. "src/mame/video/exedexes.cpp",
	MAME_DIR .. "src/hbmame/drivers/fcrash.cpp",
--	MAME_DIR .. "src/hbmame/includes/fcrash.h",
	MAME_DIR .. "src/hbmame/drivers/gng.cpp",
	MAME_DIR .. "src/mame/drivers/gunsmoke.cpp",
	MAME_DIR .. "src/mame/drivers/higemaru.cpp",
	MAME_DIR .. "src/mame/includes/higemaru.h",
	MAME_DIR .. "src/mame/video/higemaru.cpp",
	MAME_DIR .. "src/mame/drivers/lastduel.cpp",
	MAME_DIR .. "src/mame/includes/lastduel.h",
	MAME_DIR .. "src/mame/video/lastduel.cpp",
	MAME_DIR .. "src/mame/drivers/lwings.cpp",
	MAME_DIR .. "src/mame/includes/lwings.h",
	MAME_DIR .. "src/mame/video/lwings.cpp",
	MAME_DIR .. "src/hbmame/drivers/mitchell.cpp",
	MAME_DIR .. "src/mame/drivers/sf.cpp",
	MAME_DIR .. "src/mame/drivers/sidearms.cpp",
	MAME_DIR .. "src/mame/includes/sidearms.h",
	MAME_DIR .. "src/mame/video/sidearms.cpp",
	MAME_DIR .. "src/hbmame/drivers/sonson.cpp",
	MAME_DIR .. "src/mame/includes/sonson.h",
	MAME_DIR .. "src/mame/video/sonson.cpp",
	MAME_DIR .. "src/mame/drivers/srumbler.cpp",
	MAME_DIR .. "src/mame/includes/srumbler.h",
	MAME_DIR .. "src/mame/video/srumbler.cpp",
	MAME_DIR .. "src/mame/drivers/tigeroad.cpp",
	MAME_DIR .. "src/mame/includes/tigeroad.h",
	MAME_DIR .. "src/mame/video/tigeroad.cpp",
	MAME_DIR .. "src/mame/machine/tigeroad.cpp",
	MAME_DIR .. "src/mame/drivers/vulgus.cpp",
	MAME_DIR .. "src/mame/includes/vulgus.h",
	MAME_DIR .. "src/mame/video/vulgus.cpp",
	MAME_DIR .. "src/mame/machine/kabuki.cpp",
	MAME_DIR .. "src/mame/machine/kabuki.h",
}

createMAMEProjects(_target, _subtarget, "neogeo")
files {
	MAME_DIR .. "src/hbmame/drivers/neogeo.cpp",
	MAME_DIR .. "src/hbmame/drivers/neogeo_noslot.cpp",
	MAME_DIR .. "src/hbmame/video/neogeo.cpp",
	MAME_DIR .. "src/hbmame/video/neogeo_spr.cpp",
	MAME_DIR .. "src/hbmame/machine/ng_memcard.cpp",
	MAME_DIR .. "src/hbmame/bus/neogeo/prot.cpp",
	MAME_DIR .. "src/hbmame/bus/neogeo/banked_cart.cpp",
	MAME_DIR .. "src/hbmame/bus/neogeo_ctrl/ctrl.cpp",
	MAME_DIR .. "src/hbmame/bus/neogeo_ctrl/joystick.cpp",
	MAME_DIR .. "src/hbmame/bus/neogeo_ctrl/mahjong.cpp",
	MAME_DIR .. "src/hbmame/bus/neogeo_ctrl/dial.cpp",
	MAME_DIR .. "src/hbmame/bus/neogeo_ctrl/irrmaze.cpp",
	MAME_DIR .. "src/hbmame/bus/neogeo_ctrl/kizuna4p.cpp",
}

end
