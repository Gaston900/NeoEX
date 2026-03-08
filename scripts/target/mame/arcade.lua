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
CPUS["ADSP21XX"] = true -- MIDTUNIT
CPUS["M6800"] = true -- MIDTUNIT
CPUS["M6809"] = true -- MIDTUNIT
CPUS["TMS340X0"] = true -- MIDTUNIT
CPUS["TMS32031"] = true -- MIDWUNIT
CPUS["NEC"] = true -- M92
CPUS["TLCS90"] = true -- POWERINS
CPUS["ARM7"] = true -- PGM2
CPUS["MCS51"] = true -- 1943
CPUS["M6805"] = true -- ARKANOID
CPUS["UPD7810"] = true -- ASUKA
CPUS["Z180"] = true -- ASUKA
CPUS["MCS48"] = true -- BUBLBOBL
CPUS["H6280"] = true -- DEC0
CPUS["M6502"] = true -- DEC0
CPUS["ARM"] = true -- DECO_MLC
CPUS["SH"] = true -- DECO_MLC
CPUS["TMS32010"] = true -- DECO32
CPUS["S2650"] = true -- DKONG
CPUS["I86"] = true -- GOTTLIEB
CPUS["TMS57002"] = true -- KONAMIGX


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
SOUNDS["DMADAC"] = true -- MIDTUNIT
SOUNDS["HC55516"] = true -- MIDTUNIT
SOUNDS["DAC"] = true -- MIDTUNIT
SOUNDS["YMZ280B"] = true -- CAVE
SOUNDS["IREMGA20"] = true -- M92
SOUNDS["YM3812"] = true -- POWERINS
SOUNDS["MPEG_AUDIO"] = true --PGM2
SOUNDS["YMZ770"] = true --PGM2
SOUNDS["UPD7759"] = true -- AEROFGT
SOUNDS["C6280"] = true -- DEC0
SOUNDS["BSMT2000"] = true -- DECO32
SOUNDS["LC7535"] = true -- DECO32
SOUNDS["DISCRETE"] = true -- DKONG
SOUNDS["NES_APU"] = true -- DKONG
SOUNDS["TMS5110"] = true -- DKONG
SOUNDS["MSM5232"] = true -- FLSTORY
SOUNDS["TA7630"] = true -- FLSTORY
SOUNDS["DIGITALKER"] = true -- GALAXIAN
SOUNDS["SN76496"] = true -- GALAXIAN
SOUNDS["SP0250"] = true -- GALAXIAN
SOUNDS["POKEY"] = true -- GAUNTLET
SOUNDS["TMS5220"] = true  -- GAUNTLET
SOUNDS["VOTRAX"] = true -- GOTTLIEB
SOUNDS["K054539"] = true -- KONAMIGX
SOUNDS["K056800"] = true -- KONAMIGX

--------------------------------------------------
-- specify available video cores
--------------------------------------------------

VIDEOS["BUFSPRITE"] = true -- M92

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
MACHINES["6821PIA"] = true -- MIDTUNIT
MACHINES["BANKDEV"] = true -- MIDTUNIT
MACHINES["ADC0844"] = true -- MIDYUNIT
MACHINES["PIC8259"] = true -- M92
MACHINES["ARM_AIC"] = true -- PGM2
MACHINES["NETLIST"] = true -- 1942
MACHINES["MB3773"] = true -- AEROFGT
MACHINES["TTL74157"] = true -- ASUKA
MACHINES["INPUT_MERGER"] = true -- BUBLBOBL
MACHINES["K053252"] = true -- DBZ
MACHINES["MB8421"] = true -- DEC0
MACHINES["UPD4701"] = true -- DEC0
MACHINES["I8257"] = true -- DKONG
MACHINES["LATCH8"] = true -- DKONG
MACHINES["TMS6100"] = true -- DKONG
MACHINES["Z80DMA"] = true -- DKONG
MACHINES["I8255"] = true -- GALAXIAN
MACHINES["TTL74259"] = true -- GAUNTLET
MACHINES["6840PTM"] = true -- GINGANIN
MACHINES["RIOT6532"] = true -- GOTTLIEB
MACHINES["LDPR8210"] = true -- GOTTLIEB
MACHINES["MIOT6530"] = true -- GOTTLIEB
MACHINES["ADC083X"] = true -- KONAMIGX



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
		"atari",
		"dataeast",
		"capcom",
		"cave",
		"fuuki",
		"gottlieb",
		"igs",
		"irem",
		"jaleco",
		"kaneko",
		"konami",
		"midway",
		"namco",
		"neogeo",
		"nintendo",
		"nmk",
		"taito",
		"tehkan",
		"vsystem",
		"misc",
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

createMAMEProjects(_target, _subtarget, "atari")
files {
	MAME_DIR .. "src/mame/drivers/gauntlet.cpp",
	MAME_DIR .. "src/mame/includes/gauntlet.h",
	MAME_DIR .. "src/mame/video/gauntlet.cpp",
	MAME_DIR .. "src/mame/machine/slapstic.cpp",
	MAME_DIR .. "src/mame/machine/slapstic.h",
	MAME_DIR .. "src/mame/video/atarimo.cpp",
	MAME_DIR .. "src/mame/video/atarimo.h",
}

createMAMEProjects(_target, _subtarget, "dataeast")
files {
	MAME_DIR .. "src/mame/audio/decobsmt.cpp",
	MAME_DIR .. "src/mame/audio/decobsmt.h",
	MAME_DIR .. "src/mame/drivers/deco32.cpp",
	MAME_DIR .. "src/mame/includes/deco32.h",
	MAME_DIR .. "src/mame/video/deco32.cpp",
	MAME_DIR .. "src/mame/machine/deco104.cpp",
	MAME_DIR .. "src/mame/machine/deco104.h",
	MAME_DIR .. "src/mame/machine/deco_irq.cpp",
	MAME_DIR .. "src/mame/machine/deco_irq.h",
	MAME_DIR .. "src/mame/machine/decocrpt.cpp",
	MAME_DIR .. "src/mame/machine/decocrpt.h",
	MAME_DIR .. "src/mame/video/deco16ic.cpp",
	MAME_DIR .. "src/mame/video/deco16ic.h",
	MAME_DIR .. "src/mame/video/deco_ace.cpp",
	MAME_DIR .. "src/mame/video/deco_ace.h",
	MAME_DIR .. "src/mame/video/decospr.cpp",
	MAME_DIR .. "src/mame/video/decospr.h",
	MAME_DIR .. "src/mame/video/namco_c355spr.cpp",
	MAME_DIR .. "src/mame/video/namco_c355spr.h",
	MAME_DIR .. "src/mame/drivers/deco_mlc.cpp",
	MAME_DIR .. "src/mame/includes/deco_mlc.h",
	MAME_DIR .. "src/mame/video/deco_mlc.cpp",
	MAME_DIR .. "src/mame/machine/deco146.cpp",
	MAME_DIR .. "src/mame/machine/deco146.h",
	MAME_DIR .. "src/mame/machine/deco156.cpp",
	MAME_DIR .. "src/mame/machine/deco156.h",
	MAME_DIR .. "src/mame/drivers/dec0.cpp",
	MAME_DIR .. "src/mame/includes/dec0.h",
	MAME_DIR .. "src/mame/machine/dec0.cpp",
	MAME_DIR .. "src/mame/video/dec0.cpp",
	MAME_DIR .. "src/mame/video/decbac06.cpp",
	MAME_DIR .. "src/mame/video/decbac06.h",
	MAME_DIR .. "src/mame/video/decmxc06.cpp",
	MAME_DIR .. "src/mame/video/decmxc06.h",
}

createMAMEProjects(_target, _subtarget, "capcom")
files {
	MAME_DIR .. "src/mame/drivers/1942.cpp",
	MAME_DIR .. "src/mame/includes/1942.h",
	MAME_DIR .. "src/mame/video/1942.cpp",
	MAME_DIR .. "src/mame/audio/nl_1942.cpp",
	MAME_DIR .. "src/mame/audio/nl_1942.h",
	MAME_DIR .. "src/mame/drivers/1943.cpp",
	MAME_DIR .. "src/mame/includes/1943.h",
	MAME_DIR .. "src/mame/video/1943.cpp",
	MAME_DIR .. "src/mame/drivers/blktiger.cpp",
	MAME_DIR .. "src/hbmame/drivers/cps1.cpp",
	MAME_DIR .. "src/hbmame/video/cps1.cpp",
	MAME_DIR .. "src/hbmame/drivers/cps1bl_5205.cpp",
	MAME_DIR .. "src/hbmame/drivers/cps1bl_pic.cpp",
	MAME_DIR .. "src/hbmame/drivers/cps2.cpp",
	MAME_DIR .. "src/hbmame/video/cps2.cpp",
	MAME_DIR .. "src/hbmame/drivers/cps3hb.cpp",
	MAME_DIR .. "src/mame/audio/cps3.cpp",
	MAME_DIR .. "src/hbmame/drivers/fcrash.cpp",
	MAME_DIR .. "src/mame/machine/kabuki.cpp",
}

createMAMEProjects(_target, _subtarget, "cave")
files {
	MAME_DIR .. "src/hbmame/drivers/cavehb.cpp",
	MAME_DIR .. "src/mame/video/cave.cpp",
	MAME_DIR .. "src/mame/machine/nmk112.cpp",
	MAME_DIR .. "src/mame/video/tmap038.cpp",
}

createMAMEProjects(_target, _subtarget, "fuuki")
files {
	MAME_DIR .. "src/mame/drivers/fuukifg3.cpp",
	MAME_DIR .. "src/mame/includes/fuukifg3.h",
	MAME_DIR .. "src/mame/video/fuukifg3.cpp",
	MAME_DIR .. "src/mame/video/fuukifg.cpp",
	MAME_DIR .. "src/mame/video/fuukifg.h",
}

createMAMEProjects(_target, _subtarget, "gottlieb")
files {
	MAME_DIR .. "src/mame/drivers/gottlieb.cpp",
	MAME_DIR .. "src/mame/includes/gottlieb.h",
	MAME_DIR .. "src/mame/audio/gottlieb.cpp",
	MAME_DIR .. "src/mame/audio/gottlieb.h",
	MAME_DIR .. "src/mame/video/gottlieb.cpp",
}

createMAMEProjects(_target, _subtarget, "igs")
files {
	MAME_DIR .. "src/mame/drivers/pgm2.cpp",
	MAME_DIR .. "src/mame/video/pgm2.cpp",
	MAME_DIR .. "src/mame/includes/pgm2.h",
	MAME_DIR .. "src/mame/machine/pgm2_memcard.cpp",
	MAME_DIR .. "src/mame/machine/pgm2_memcard.h",
	MAME_DIR .. "src/mame/machine/igs036crypt.cpp",
	MAME_DIR .. "src/mame/machine/igs036crypt.h",
}

createMAMEProjects(_target, _subtarget, "irem")
files {
	MAME_DIR .. "src/hbmame/drivers/m92hb.cpp",
	MAME_DIR .. "src/mame/video/m92.cpp",
	MAME_DIR .. "src/mame/machine/irem_cpu.cpp",
}

createMAMEProjects(_target, _subtarget, "jaleco")
files {
	MAME_DIR .. "src/mame/drivers/ginganin.cpp",
	MAME_DIR .. "src/mame/includes/ginganin.h",
	MAME_DIR .. "src/mame/video/ginganin.cpp",
	MAME_DIR .. "src/mame/drivers/exerion.cpp",
	MAME_DIR .. "src/mame/includes/exerion.h",
	MAME_DIR .. "src/mame/video/exerion.cpp",
}

createMAMEProjects(_target, _subtarget, "kaneko")
files {
	MAME_DIR .. "src/mame/drivers/kaneko16.cpp",
	MAME_DIR .. "src/mame/includes/kaneko16.h",
	MAME_DIR .. "src/mame/video/kaneko16.cpp",
	MAME_DIR .. "src/mame/machine/kaneko_calc3.cpp",
	MAME_DIR .. "src/mame/machine/kaneko_calc3.h",
	MAME_DIR .. "src/mame/machine/kaneko_hit.cpp",
	MAME_DIR .. "src/mame/machine/kaneko_hit.h",
	MAME_DIR .. "src/mame/machine/kaneko_toybox.cpp",
	MAME_DIR .. "src/mame/machine/kaneko_toybox.h",
	MAME_DIR .. "src/mame/video/kaneko_tmap.cpp",
	MAME_DIR .. "src/mame/video/kaneko_tmap.h",
	MAME_DIR .. "src/mame/video/kaneko_spr.cpp",
	MAME_DIR .. "src/mame/video/kaneko_spr.h",
}

createMAMEProjects(_target, _subtarget, "konami")
files {
	MAME_DIR .. "src/mame/drivers/konamigx.cpp",
	MAME_DIR .. "src/mame/includes/konamigx.h",
	MAME_DIR .. "src/mame/machine/konamigx.cpp",
	MAME_DIR .. "src/mame/video/konamigx.cpp",
	MAME_DIR .. "src/mame/video/k053250.cpp",
	MAME_DIR .. "src/mame/video/k053250.h",
	MAME_DIR .. "src/mame/video/k054338.cpp",
	MAME_DIR .. "src/mame/video/k054338.h",
	MAME_DIR .. "src/mame/drivers/dbz.cpp",
	MAME_DIR .. "src/mame/includes/dbz.h",
	MAME_DIR .. "src/mame/video/dbz.cpp",
	MAME_DIR .. "src/mame/video/k053246_k053247_k055673.cpp",
	MAME_DIR .. "src/mame/video/k053246_k053247_k055673.h",
	MAME_DIR .. "src/mame/video/k053251.cpp",
	MAME_DIR .. "src/mame/video/k053251.h",
	MAME_DIR .. "src/mame/video/k053936.cpp",
	MAME_DIR .. "src/mame/video/k053936.h",
	MAME_DIR .. "src/mame/video/k054156_k054157_k056832.cpp",
	MAME_DIR .. "src/mame/video/k054156_k054157_k056832.h",
	MAME_DIR .. "src/mame/video/k055555.cpp",
	MAME_DIR .. "src/mame/video/k055555.h",
	MAME_DIR .. "src/mame/drivers/contra.cpp",
	MAME_DIR .. "src/mame/machine/k007452.cpp",
	MAME_DIR .. "src/mame/machine/k007452.h",
	MAME_DIR .. "src/mame/video/k007121.cpp",
	MAME_DIR .. "src/mame/video/k007121.h",
	MAME_DIR .. "src/mame/video/konami_helper.cpp",
	MAME_DIR .. "src/mame/video/konami_helper.h",
}

createMAMEProjects(_target, _subtarget, "midway")
files {
	MAME_DIR .. "src/hbmame/drivers/midtunithb.cpp",
	MAME_DIR .. "src/mame/machine/midtunit.cpp",
	MAME_DIR .. "src/mame/video/midtunit.cpp",
	MAME_DIR .. "src/hbmame/drivers/midwunithb.cpp",
	MAME_DIR .. "src/mame/machine/midwunit.cpp",
	MAME_DIR .. "src/mame/drivers/midyunit.cpp",
	MAME_DIR .. "src/mame/machine/midyunit.cpp",
	MAME_DIR .. "src/mame/video/midyunit.cpp",
	MAME_DIR .. "src/mame/machine/midwayic.cpp",
	MAME_DIR .. "src/mame/audio/midway.cpp",
	MAME_DIR .. "src/mame/audio/williams.cpp",
	MAME_DIR .. "src/mame/audio/cage.cpp",
	MAME_DIR .. "src/mame/audio/dcs.cpp",
	MAME_DIR .. "src/mame/audio/csd.cpp",
	MAME_DIR .. "src/mame/audio/bally.cpp",
}

createMAMEProjects(_target, _subtarget, "namco")
files {
	MAME_DIR .. "src/mame/audio/cclimber.cpp",
	MAME_DIR .. "src/mame/audio/cclimber.h",
	MAME_DIR .. "src/mame/drivers/galaxian.cpp",
	MAME_DIR .. "src/mame/includes/galaxian.h",
	MAME_DIR .. "src/mame/audio/galaxian.cpp",
	MAME_DIR .. "src/mame/audio/galaxian.h",
	MAME_DIR .. "src/mame/video/galaxian.cpp",
	MAME_DIR .. "src/mame/audio/nl_konami.h",
	MAME_DIR .. "src/mame/audio/nl_konami.cpp",
}

createMAMEProjects(_target, _subtarget, "neogeo")
files {
	MAME_DIR .. "src/hbmame/drivers/neogeo.cpp",
	MAME_DIR .. "src/hbmame/drivers/neogeo_noslot.cpp",
	MAME_DIR .. "src/hbmame/drivers/neogeo_noslothb.cpp",
	MAME_DIR .. "src/hbmame/drivers/neogeo_noslotdd.cpp",
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

createMAMEProjects(_target, _subtarget, "nintendo")
files {
	MAME_DIR .. "src/mame/drivers/dkong.cpp",
	MAME_DIR .. "src/mame/includes/dkong.h",
	MAME_DIR .. "src/mame/audio/dkong.cpp",
	MAME_DIR .. "src/mame/video/dkong.cpp",
}

createMAMEProjects(_target, _subtarget, "nmk")
files {
	MAME_DIR .. "src/hbmame/drivers/powerinshb.cpp",
	MAME_DIR .. "src/mame/video/powerins.cpp",
	MAME_DIR .. "src/mame/drivers/nmk16.cpp",
	MAME_DIR .. "src/mame/video/nmk16.cpp",
	MAME_DIR .. "src/mame/video/nmk16spr.cpp",
	MAME_DIR .. "src/mame/machine/nmk004.cpp",
	MAME_DIR .. "src/mame/audio/seibu.cpp",
}

createMAMEProjects(_target, _subtarget, "taito")
files {
	MAME_DIR .. "src/mame/drivers/lkage.cpp",
	MAME_DIR .. "src/mame/includes/lkage.h",
	MAME_DIR .. "src/mame/video/lkage.cpp",
	MAME_DIR .. "src/mame/drivers/kikikai.cpp",
	MAME_DIR .. "src/mame/includes/kikikai.h",
	MAME_DIR .. "src/mame/machine/kikikai.cpp",
	MAME_DIR .. "src/mame/video/kikikai.cpp",
	MAME_DIR .. "src/mame/drivers/flstory.cpp",
	MAME_DIR .. "src/mame/includes/flstory.h",
	MAME_DIR .. "src/mame/video/flstory.cpp",
	MAME_DIR .. "src/mame/drivers/bublbobl.cpp",
	MAME_DIR .. "src/mame/includes/bublbobl.h",
	MAME_DIR .. "src/mame/machine/bublbobl.cpp",
	MAME_DIR .. "src/mame/video/bublbobl.cpp",
	MAME_DIR .. "src/mame/drivers/asuka.cpp",
	MAME_DIR .. "src/mame/audio/taitosnd.cpp",
	MAME_DIR .. "src/mame/audio/taitosnd.h",
	MAME_DIR .. "src/mame/machine/taitocchip.cpp",
	MAME_DIR .. "src/mame/machine/taitocchip.h",
	MAME_DIR .. "src/mame/machine/taitoio.cpp",
	MAME_DIR .. "src/mame/machine/taitoio.h",
	MAME_DIR .. "src/mame/video/pc090oj.cpp",
	MAME_DIR .. "src/mame/video/pc090oj.h",
	MAME_DIR .. "src/mame/video/tc0100scn.cpp",
	MAME_DIR .. "src/mame/video/tc0100scn.h",
	MAME_DIR .. "src/mame/video/tc0110pcr.cpp",
	MAME_DIR .. "src/mame/video/tc0110pcr.h",
	MAME_DIR .. "src/mame/drivers/arkanoid.cpp",
	MAME_DIR .. "src/mame/includes/arkanoid.h",
	MAME_DIR .. "src/mame/machine/arkanoid.cpp",
	MAME_DIR .. "src/mame/video/arkanoid.cpp",
	MAME_DIR .. "src/mame/machine/taito68705interface.cpp",
	MAME_DIR .. "src/mame/machine/taito68705interface.h",
}

createMAMEProjects(_target, _subtarget, "tehkan")
files {
	MAME_DIR .. "src/mame/drivers/bombjack.cpp",
	MAME_DIR .. "src/mame/includes/bombjack.h",
	MAME_DIR .. "src/mame/video/bombjack.cpp",
}

createMAMEProjects(_target, _subtarget, "vsystem")
files {
	MAME_DIR .. "src/mame/machine/vs9209.cpp",
	MAME_DIR .. "src/mame/machine/vs9209.h",
	MAME_DIR .. "src/mame/video/vsystem_gga.cpp",
	MAME_DIR .. "src/mame/video/vsystem_gga.h",
	MAME_DIR .. "src/mame/video/vsystem_spr.cpp",
	MAME_DIR .. "src/mame/video/vsystem_spr.h",
	MAME_DIR .. "src/mame/video/vsystem_spr2.cpp",
	MAME_DIR .. "src/mame/video/vsystem_spr2.h",
	MAME_DIR .. "src/mame/drivers/aerofgt.cpp",
	MAME_DIR .. "src/mame/includes/aerofgt.h",
	MAME_DIR .. "src/mame/video/aerofgt.cpp",
}

--------------------------------------------------
-- remaining drivers
--------------------------------------------------

createMAMEProjects(_target, _subtarget, "misc")
files {
	MAME_DIR .. "src/mame/drivers/kyugo.cpp",
	MAME_DIR .. "src/mame/includes/kyugo.h",
	MAME_DIR .. "src/mame/video/kyugo.cpp",
}
end
