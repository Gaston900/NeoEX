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
SOUNDS["CDDA"] = true -- CPS3

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
MACHINES["INPUT_MERGER"] = true --NEOGEO CD


--------------------------------------------------
-- specify available bus cores
--------------------------------------------------
BUSES["NSCSI"] = true -- CPS3
BUSES["NEOGEO_CTRL"] = true -- NEOGEO

--------------------------------------------------
-- this is the list of driver libraries that
-- comprise MAME plus mamedriv.o which contains
-- the list of drivers
--------------------------------------------------

function linkProjects_mame_arcade(_target, _subtarget)
	links {
		"capcom",
		"neogeo",
		"snk",
	}
end

function createMAMEProjects(_target, _subtarget, _name)
	project (_name)
	targetsubdir(_target .."_" .. _subtarget)
	kind (LIBTYPE)
	uuid (os.uuid("drv-" .. _target .."_" .. _subtarget .. "_" .._name))
	addprojectflags()
	precompiledheaders()

	includedirs {
		MAME_DIR .. "src/osd",
		MAME_DIR .. "src/emu",
		MAME_DIR .. "src/devices",
		MAME_DIR .. "src/hbmame/includes",
		MAME_DIR .. "src/hbmame",
		MAME_DIR .. "src/mame",
		MAME_DIR .. "src/mame/shared",
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
-- manufacturer-specific groupings for drivers
--------------------------------------------------

createMAMEProjects(_target, _subtarget, "capcom")
files {
	MAME_DIR .. "src/hbmame/drivers/1942hc.cpp",
	MAME_DIR .. "src/mame/capcom/1942.h",
	MAME_DIR .. "src/mame/capcom/1942_v.cpp",
	MAME_DIR .. "src/hbmame/drivers/1943hc.cpp",
	MAME_DIR .. "src/mame/capcom/1943.h",
	MAME_DIR .. "src/mame/capcom/1943_v.cpp",
	MAME_DIR .. "src/mame/capcom/alien.cpp",
	MAME_DIR .. "src/mame/capcom/bionicc.cpp",
	MAME_DIR .. "src/hbmame/drivers/blktigerhc.cpp",
	MAME_DIR .. "src/mame/capcom/blktiger_ms.cpp",
	MAME_DIR .. "src/mame/capcom/cbasebal.cpp",
	MAME_DIR .. "src/mame/capcom/chakumelo.cpp",
	MAME_DIR .. "src/mame/capcom/commando.cpp",
	MAME_DIR .. "src/hbmame/drivers/cps1.cpp",
	MAME_DIR .. "src/hbmame/video/cps1.cpp",
	MAME_DIR .. "src/hbmame/drivers/cps1bl_5205.cpp",
	MAME_DIR .. "src/hbmame/drivers/cps1bl_pic.cpp",
	MAME_DIR .. "src/hbmame/drivers/cps2.cpp",
	MAME_DIR .. "src/hbmame/video/cps2.cpp",
	MAME_DIR .. "src/hbmame/drivers/cps3hc.cpp",
	MAME_DIR .. "src/mame/capcom/cps3.h",
	MAME_DIR .. "src/mame/capcom/cps3_a.cpp",
	MAME_DIR .. "src/mame/capcom/cps3_a.h",
	MAME_DIR .. "src/mame/capcom/egghunt.cpp",
	MAME_DIR .. "src/mame/capcom/exedexes.cpp",
	MAME_DIR .. "src/hbmame/drivers/fcrash.cpp",
	MAME_DIR .. "src/hbmame/drivers/gnghc.cpp",
	MAME_DIR .. "src/mame/capcom/gunsmoke.cpp",
	MAME_DIR .. "src/mame/capcom/higemaru.cpp",
	MAME_DIR .. "src/mame/capcom/instantm.cpp",
	MAME_DIR .. "src/mame/capcom/kabuki.cpp",
	MAME_DIR .. "src/mame/capcom/kabuki.h",
	MAME_DIR .. "src/mame/capcom/kenseim.cpp",
	MAME_DIR .. "src/mame/capcom/lastduel.cpp",
	MAME_DIR .. "src/mame/capcom/lastduel_ms.cpp",
	MAME_DIR .. "src/mame/capcom/lwings.cpp",
	MAME_DIR .. "src/hbmame/drivers/mitchellhc.cpp",
	MAME_DIR .. "src/mame/capcom/miteshin.cpp",
	MAME_DIR .. "src/mame/capcom/nl_1942.cpp",
	MAME_DIR .. "src/mame/capcom/nl_1942.h",
--	MAME_DIR .. "src/mame/capcom/psrockman.cpp",
	MAME_DIR .. "src/mame/capcom/sf.cpp",
	MAME_DIR .. "src/mame/capcom/sidearms.cpp",
	MAME_DIR .. "src/mame/capcom/sidearms.h",
	MAME_DIR .. "src/mame/capcom/sidearms_v.cpp",
	MAME_DIR .. "src/hbmame/drivers/sonsonhc.cpp",
	MAME_DIR .. "src/mame/capcom/srumbler.cpp",
	MAME_DIR .. "src/mame/capcom/supduck.cpp",
	MAME_DIR .. "src/mame/capcom/tigeroad.cpp",
	MAME_DIR .. "src/mame/capcom/tigeroad.h",
	MAME_DIR .. "src/mame/capcom/tigeroad_m.cpp",
	MAME_DIR .. "src/mame/capcom/tigeroad_spr.cpp",
	MAME_DIR .. "src/mame/capcom/tigeroad_spr.h",
	MAME_DIR .. "src/mame/capcom/tigeroad_v.cpp",
--	MAME_DIR .. "src/mame/capcom/tvcapcom.cpp",
	MAME_DIR .. "src/mame/capcom/vulgus.cpp",
}

createMAMEProjects(_target, _subtarget, "neogeo")
files {
	MAME_DIR .. "src/hbmame/drivers/neogeo.cpp",
	MAME_DIR .. "src/hbmame/drivers/neogeo_noslot.cpp",
	MAME_DIR .. "src/hbmame/video/neogeo.cpp",
	MAME_DIR .. "src/hbmame/video/neogeo_spr.cpp",
	MAME_DIR .. "src/hbmame/machine/nghb_memcard.cpp",
	MAME_DIR .. "src/hbmame/bus/neogeo/prot.cpp",
	MAME_DIR .. "src/hbmame/bus/neogeo/banked_cart.cpp",
}

createMAMEProjects(_target, _subtarget, "snk")
files {
	MAME_DIR .. "src/hbmame/drivers/neogeocd.cpp",
	MAME_DIR .. "src/mame/snk/neogeo_spr.cpp",
	MAME_DIR .. "src/mame/snk/neogeo.cpp",
	MAME_DIR .. "src/mame/snk/neogeo_v.cpp",
	MAME_DIR .. "src/mame/snk/ng_memcard.cpp",
-- DEVICES
	MAME_DIR .. "src/mame/shared/megacdcd.cpp",
	MAME_DIR .. "src/devices/bus/neogeo/slot.cpp",
}

end
