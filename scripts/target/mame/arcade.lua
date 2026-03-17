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
CPUS["M37710"] = true -- NAMCONA1
CPUS["UPD7725"] = true -- SEGAS32
CPUS["V60"] = true -- SEGAS32
CPUS["H8"] = true -- SETA2
CPUS["V810"] = true -- SSV
CPUS["SCUDSP"] = true -- STV
CPUS["ES5510"] = true -- TAITO_F3
CPUS["E1"] = true -- VAMPHALF
CPUS["DSP16"] = true -- ZN
CPUS["FR"] = true -- ZN
CPUS["MN10200"] = true -- ZN
CPUS["PSX"] = true -- ZN
CPUS["MB88XX"] = true -- GALAGA
CPUS["SM510"] = true -- NES
CPUS["G65816"] = true -- SNES
CPUS["LR35902"] = true -- SNES
CPUS["SPC700"] = true -- SNES
CPUS["SUPERFX"] = true -- SNES
CPUS["SSP1601"] = true -- MEGADRIVE
CPUS["F8"] = true -- CHANNELF
CPUS["TLCS900"] = true -- NGP
CPUS["IE15"] = true -- SG1000
CPUS["CCPU"] = true -- CINEMAT
CPUS["I8085"] = true -- PHOENIX
CPUS["MB86233"] = true -- MODEL1
CPUS["I960"] = true -- MODEL2
CPUS["MB86235"] = true -- MODEL2
CPUS["ADSP21062"] = true -- MODEL2
CPUS["Z8000"] = true -- POLEPOS

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
SOUNDS["MPEG_AUDIO"] = true -- PGM2
SOUNDS["YMZ770"] = true -- PGM2
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
SOUNDS["NAMCO"] = true -- MAPPY
SOUNDS["C140"] = true -- NAMCONA1
SOUNDS["K005289"] = true -- NEMESIS
SOUNDS["K051649"] = true -- NEMESIS
SOUNDS["VLM5030"] = true -- NEMESIS
SOUNDS["K007232"] = true -- NEMESIS
SOUNDS["ICS2115"] = true -- PGM
SOUNDS["I5000_SND"] = true -- RABBIT
SOUNDS["CDDA"] = true -- SEGAS32
SOUNDS["MULTIPCM"] = true -- SEGAS32
SOUNDS["RF5C68"] = true -- SEGAS32 
SOUNDS["X1_010"] = true -- SETA
SOUNDS["OKIM9810"] = true -- SETA2
SOUNDS["ES5506"] = true -- SSV
SOUNDS["SCSP"] = true -- STV
SOUNDS["ESQPUMP"] = true -- TAITO_F3
SOUNDS["K053260"] = true -- TMNT
SOUNDS["QS1000"] = true -- VAMPHALF
SOUNDS["SPU"] = true -- ZN
SOUNDS["YMF271"] = true -- ZN
SOUNDS["ZSG2"] = true -- ZN
SOUNDS["NAMCO_163"] = true -- NES
SOUNDS["RP2C33_SOUND"] = true -- NES
SOUNDS["VRC6"] = true -- NES
SOUNDS["GB_SOUND"] = true -- SNES
SOUNDS["S_DSP"] = true -- SNES
SOUNDS["T6W28"] = true -- NGP
SOUNDS["BEEP"] = true -- SG1000
SOUNDS["SEGAPCM"] = true -- SEGAORUN
SOUNDS["ASTROCADE"] = true -- ASTROCDE
SOUNDS["TMS36XX"] = true -- PHOENIX
SOUNDS["NAMCO_63701X"] = true -- NAMCOS86
SOUNDS["SN76477"] = true -- SNK6502
SOUNDS["TC8830F"] = true -- TIMEPLT

--------------------------------------------------
-- specify available video cores
--------------------------------------------------

VIDEOS["BUFSPRITE"] = true -- M92
VIDEOS["PPU2C0X"] = true -- VSNES
VIDEOS["PSX"] = true -- ZN
VIDEOS["GB_LCD"] = true -- SNES
VIDEOS["SNES_PPU"] = true -- SNES
VIDEOS["GBA_LCD"] = true -- GBA
VIDEOS["SEGA315_5124"] = true -- MEGADRIVE
VIDEOS["SEGA315_5313"] = true -- MEGADRIVE
VIDEOS["TMS9928A"] = true -- COLECO
VIDEOS["HUC6202"] = true -- NEC
VIDEOS["HUC6260"] = true -- NEC
VIDEOS["HUC6270"] = true -- NEC
VIDEOS["MOS6566"] = true -- SG1000
VIDEOS["MC6845"] = true -- SG1000
VIDEOS["HD44780"] = true -- MODEL1
VIDEOS["TLC34076"] = true -- ITECH8
VIDEOS["TMS34061"] = true -- ITECH8
VIDEOS["EPIC12"] = true -- CV1K

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
MACHINES["K054321"] = true -- MYSTWARR
MACHINES["MSM6242"] = true -- NAMCONA1
MACHINES["ADC0804"] = true -- NEMESIS
MACHINES["V3021"] = true -- PGM
MACHINES["CXD1095"] = true -- SEGAS16B
MACHINES["MB89352"] = true -- SEGAS32
MACHINES["MSM6253"] = true -- SEGAS32
MACHINES["OUTPUT_LATCH"] = true -- SEGAS32
MACHINES["ACIA6850"] = true -- SETA
MACHINES["PIT8253"] = true -- SETA
MACHINES["TICKET"] = true -- SETA
MACHINES["TMP68301"] = true -- SETA
MACHINES["UPD4992"] = true -- SETA
MACHINES["INTELFLASH"] = true -- SETA2
MACHINES["MCF5206E"] = true -- SETA2
MACHINES["ADC0808"] = true -- SSV
MACHINES["UPD7001"] = true -- SSV
MACHINES["SEGA_SCU"] = true -- STV
MACHINES["SMPC"] = true -- STV
MACHINES["STVCD"] = true -- STV
MACHINES["Z80PIO"] = true -- SYSTEM1
MACHINES["RP5C01"] = true -- TAITO_F2
MACHINES["TE7750"] = true -- TAITO_F2
MACHINES["MB87078"] = true -- TAITO_F3
MACHINES["68681"] = true -- TAITO_F3
MACHINES["TC0091LVC"] = true -- TAITO_L
MACHINES["7200FIFO"] = true -- ZN
MACHINES["AT28C16"] = true -- ZN
MACHINES["IDECTRL"] = true -- ZN
MACHINES["ER2055"] = true -- GALAGA
MACHINES["I2CMEM"] = true -- NES
MACHINES["S_SMP"] = true -- SNES
MACHINES["LC89510"] = true -- MEGADRIVE
MACHINES["BITMAP_PRINTER"] = true -- SG1000
MACHINES["CHESSMACHINE"] = true -- SG1000
MACHINES["E05A03"] = true -- SG1000
MACHINES["E05A30"] = true -- SG1000
MACHINES["FDC_PLL"] = true -- SG1000
MACHINES["I8251"] = true -- SG1000
MACHINES["IE15"] = true -- SG1000
MACHINES["INS8250"] = true -- SG1000
MACHINES["SENSORBOARD"] = true -- SG1000
MACHINES["TASC_SB30"] = true -- SG1000
MACHINES["STEPPERS"] = true -- SG1000
MACHINES["SWTPC8212"] = true -- SG1000
MACHINES["UPD765"] = true -- SG1000
MACHINES["Z80CTC"] = true -- ASTROCDE
MACHINES["RP5H01"] = true -- PLAYCH10
MACHINES["6522VIA"] = true -- ATARISY1
MACHINES["AM9517A"] = true -- MODEL1
MACHINES["GEN_FIFO"] = true -- MODEL1
MACHINES["MB89374"] = true -- MODEL1
MACHINES["Z80SIO"] = true -- MODEL1
MACHINES["RTC9701"] = true -- CV1K
MACHINES["SERFLASH"] = true -- CV1K
MACHINES["TMS1024"] = true -- DOCASTLE


--------------------------------------------------
-- specify available bus cores
--------------------------------------------------
BUSES["NSCSI"] = true -- CPS3
BUSES["SCSI"] = true -- SEGAS32
BUSES["GENERIC"] = true -- STV
BUSES["SAT_CTRL"] = true -- STV
BUSES["SATURN"] = true -- STV
BUSES["NES_CTRL"] = true -- VSNES
BUSES["ATA"] = true -- ZN
BUSES["MIDI"] = true -- NES
BUSES["NES"] = true -- NES
BUSES["SNES_CTRL"] = true -- NES
BUSES["GAMEBOY"] = true -- SNES
BUSES["SNES"] = true -- SNES
BUSES["GBA"] = true -- GBA
BUSES["MEGADRIVE"] = true -- MEGADRIVE
BUSES["GAMEGEAR"] = true -- SMS
BUSES["SEGA8"] = true -- SMS
BUSES["SG1000_EXP"] = true -- SMS
BUSES["SMS_CTRL"] = true -- SMS
BUSES["SMS_EXP"] = true -- SMS
BUSES["CHANNELF"] = true -- CHANNELF
BUSES["COLECO_CART"] = true -- COLECO
BUSES["PCE"] = true -- NEC
BUSES["PCE_CTRL"] = true -- NEC
BUSES["CENTRONICS"] = true -- SG1000
BUSES["RS232"] = true -- SG1000
BUSES["SUNKBD"] = true -- SG1000

--------------------------------------------------
-- specify used file formats
--------------------------------------------------
FORMATS["BASICDSK"] = true -- NES
FORMATS["NES_DSK"] = true -- NES
FORMATS["SC3000_BIT"] = true -- SMS
FORMATS["TZX_CAS"] = true -- SMS
FORMATS["SF7000_DSK"] = true -- SG1000

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
		"cinemat",
		"cave",
		"coleco",
		"exidy",
		"fairch",
		"fuuki",
		"gottlieb",
		"igs",
		"irem",
		"itech",
		"jaleco",
		"kaneko",
		"konami",
		"metro",
		"midway",
		"namco",
		"nec",
		"neogeo",
		"nintendo",
		"nmk",
		"pacman",
		"phoenix",
		"psikyo",
		"seibu",
		"seta",
		"sega",
		"snk",
		"sony",
		"taito",
		"technos",
		"tehkan",
		"toaplan",
		"unico",
		"univers",
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
	MAME_DIR .. "src/hbmame/drivers/mhavoc_hb.cpp",
	MAME_DIR .. "src/hbmame/machine/mhavoc_hb.cpp",
	MAME_DIR .. "src/mame/drivers/mhavoc.cpp",
	MAME_DIR .. "src/mame/machine/mhavoc.cpp",
	MAME_DIR .. "src/hbmame/drivers/tempest.cpp",
	MAME_DIR .. "src/mame/machine/mathbox.cpp",
	MAME_DIR .. "src/mame/machine/mathbox.h",
	MAME_DIR .. "src/mame/video/avgdvg.cpp",
	MAME_DIR .. "src/mame/video/avgdvg.h",
	MAME_DIR .. "src/hbmame/drivers/centiped.cpp",
	MAME_DIR .. "src/mame/includes/centiped.h",
	MAME_DIR .. "src/mame/video/centiped.cpp",
	MAME_DIR .. "src/hbmame/drivers/atarisy1.cpp",
	MAME_DIR .. "src/mame/includes/atarisy1.h",
	MAME_DIR .. "src/mame/video/atarisy1.cpp",
	MAME_DIR .. "src/hbmame/drivers/atarigt.cpp",
	MAME_DIR .. "src/mame/includes/atarigt.h",
	MAME_DIR .. "src/mame/video/atarigt.cpp",
	MAME_DIR .. "src/mame/machine/atarigen.cpp",
	MAME_DIR .. "src/mame/machine/atarigen.h",
	MAME_DIR .. "src/mame/video/atarirle.cpp",
	MAME_DIR .. "src/mame/video/atarirle.h",
	MAME_DIR .. "src/hbmame/drivers/gauntlet.cpp",
	MAME_DIR .. "src/mame/includes/gauntlet.h",
	MAME_DIR .. "src/mame/video/gauntlet.cpp",
	MAME_DIR .. "src/mame/machine/slapstic.cpp",
	MAME_DIR .. "src/mame/machine/slapstic.h",
	MAME_DIR .. "src/mame/video/atarimo.cpp",
	MAME_DIR .. "src/mame/video/atarimo.h",
}

createMAMEProjects(_target, _subtarget, "dataeast")
files {
	MAME_DIR .. "src/hbmame/drivers/rohga.cpp",
	MAME_DIR .. "src/mame/includes/rohga.h",
	MAME_DIR .. "src/mame/video/rohga.cpp",
	MAME_DIR .. "src/mame/video/decocomn.cpp",
	MAME_DIR .. "src/mame/video/decocomn.h",
	MAME_DIR .. "src/hbmame/drivers/btime.cpp",
	MAME_DIR .. "src/mame/includes/btime.h",
	MAME_DIR .. "src/mame/machine/btime.cpp",
	MAME_DIR .. "src/mame/video/btime.cpp",
	MAME_DIR .. "src/mame/machine/decocpu7.cpp",
	MAME_DIR .. "src/mame/machine/decocpu7.h",
	MAME_DIR .. "src/hbmame/drivers/pcktgal.cpp",
	MAME_DIR .. "src/mame/machine/deco222.cpp",
	MAME_DIR .. "src/mame/machine/deco222.h",
	MAME_DIR .. "src/mame/audio/decobsmt.cpp",
	MAME_DIR .. "src/mame/audio/decobsmt.h",
	MAME_DIR .. "src/hbmame/drivers/deco32.cpp",
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
	MAME_DIR .. "src/hbmame/drivers/deco_mlc.cpp",
	MAME_DIR .. "src/mame/includes/deco_mlc.h",
	MAME_DIR .. "src/mame/video/deco_mlc.cpp",
	MAME_DIR .. "src/mame/machine/deco146.cpp",
	MAME_DIR .. "src/mame/machine/deco146.h",
	MAME_DIR .. "src/mame/machine/deco156.cpp",
	MAME_DIR .. "src/mame/machine/deco156.h",
	MAME_DIR .. "src/hbmame/drivers/dec0.cpp",
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
	MAME_DIR .. "src/hbmame/drivers/mitchell.cpp",
	MAME_DIR .. "src/hbmame/drivers/sonson.cpp",
	MAME_DIR .. "src/mame/includes/sonson.h",
	MAME_DIR .. "src/mame/video/sonson.cpp",
	MAME_DIR .. "src/hbmame/drivers/1942.cpp",
	MAME_DIR .. "src/mame/includes/1942.h",
	MAME_DIR .. "src/mame/video/1942.cpp",
	MAME_DIR .. "src/mame/audio/nl_1942.cpp",
	MAME_DIR .. "src/mame/audio/nl_1942.h",
	MAME_DIR .. "src/hbmame/drivers/1943.cpp",
	MAME_DIR .. "src/mame/includes/1943.h",
	MAME_DIR .. "src/mame/video/1943.cpp",
	MAME_DIR .. "src/hbmame/drivers/blktiger.cpp",
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

createMAMEProjects(_target, _subtarget, "cinemat")
files {
	MAME_DIR .. "src/hbmame/drivers/cinemat.cpp",
	MAME_DIR .. "src/mame/includes/cinemat.h",
	MAME_DIR .. "src/mame/audio/cinemat.cpp",
	MAME_DIR .. "src/mame/audio/cinemat.h",
	MAME_DIR .. "src/mame/video/cinemat.cpp",
	MAME_DIR .. "src/mame/audio/nl_armora.cpp",
	MAME_DIR .. "src/mame/audio/nl_armora.h",
	MAME_DIR .. "src/mame/audio/nl_barrier.cpp",
	MAME_DIR .. "src/mame/audio/nl_barrier.h",
	MAME_DIR .. "src/mame/audio/nl_boxingb.cpp",
	MAME_DIR .. "src/mame/audio/nl_boxingb.h",
	MAME_DIR .. "src/mame/audio/nl_cinemat_common.h",
	MAME_DIR .. "src/mame/audio/nl_ripoff.cpp",
	MAME_DIR .. "src/mame/audio/nl_ripoff.h",
	MAME_DIR .. "src/mame/audio/nl_solarq.cpp",
	MAME_DIR .. "src/mame/audio/nl_solarq.h",
	MAME_DIR .. "src/mame/audio/nl_spacewar.cpp",
	MAME_DIR .. "src/mame/audio/nl_spacewar.h",
	MAME_DIR .. "src/mame/audio/nl_speedfrk.cpp",
	MAME_DIR .. "src/mame/audio/nl_speedfrk.h",
	MAME_DIR .. "src/mame/audio/nl_starcas.cpp",
	MAME_DIR .. "src/mame/audio/nl_starcas.h",
	MAME_DIR .. "src/mame/audio/nl_starhawk.cpp",
	MAME_DIR .. "src/mame/audio/nl_starhawk.h",
	MAME_DIR .. "src/mame/audio/nl_sundance.cpp",
	MAME_DIR .. "src/mame/audio/nl_sundance.h",
	MAME_DIR .. "src/mame/audio/nl_tailg.cpp",
	MAME_DIR .. "src/mame/audio/nl_tailg.h",
	MAME_DIR .. "src/mame/audio/nl_warrior.cpp",
	MAME_DIR .. "src/mame/audio/nl_warrior.h",
}

createMAMEProjects(_target, _subtarget, "cave")
files {
	MAME_DIR .. "src/hbmame/drivers/cv1k.cpp",
	MAME_DIR .. "src/hbmame/drivers/cave.cpp",
	MAME_DIR .. "src/mame/video/cave.cpp",
	MAME_DIR .. "src/mame/machine/nmk112.cpp",
	MAME_DIR .. "src/mame/video/tmap038.cpp",
}

createMAMEProjects(_target, _subtarget, "coleco")
files {
	MAME_DIR .. "src/mame/drivers/coleco.cpp",
	MAME_DIR .. "src/mame/includes/coleco.h",
	MAME_DIR .. "src/mame/machine/coleco.cpp",
	MAME_DIR .. "src/mame/machine/coleco.h",
}

createMAMEProjects(_target, _subtarget, "exidy")
files {
	MAME_DIR .. "src/hbmame/drivers/exidy.cpp",
	MAME_DIR .. "src/mame/audio/exidy.cpp",
	MAME_DIR .. "src/mame/audio/exidy.h",
	MAME_DIR .. "src/mame/includes/victory.h",
	MAME_DIR .. "src/mame/video/victory.cpp",
}

createMAMEProjects(_target, _subtarget, "fairch")
files {
	MAME_DIR .. "src/mame/drivers/channelf.cpp",
	MAME_DIR .. "src/mame/includes/channelf.h",
	MAME_DIR .. "src/mame/audio/channelf.cpp",
	MAME_DIR .. "src/mame/audio/channelf.h",
	MAME_DIR .. "src/mame/video/channelf.cpp",
}

createMAMEProjects(_target, _subtarget, "fuuki")
files {
	MAME_DIR .. "src/hbmame/drivers/fuukifg3.cpp",
	MAME_DIR .. "src/mame/includes/fuukifg3.h",
	MAME_DIR .. "src/mame/video/fuukifg3.cpp",
	MAME_DIR .. "src/mame/video/fuukifg.cpp",
	MAME_DIR .. "src/mame/video/fuukifg.h",
}

createMAMEProjects(_target, _subtarget, "gottlieb")
files {
	MAME_DIR .. "src/hbmame/drivers/gottlieb.cpp",
	MAME_DIR .. "src/mame/includes/gottlieb.h",
	MAME_DIR .. "src/mame/audio/gottlieb.cpp",
	MAME_DIR .. "src/mame/audio/gottlieb.h",
	MAME_DIR .. "src/mame/video/gottlieb.cpp",
}

createMAMEProjects(_target, _subtarget, "igs")
files {
	MAME_DIR .. "src/hbmame/drivers/lordgun.cpp",
	MAME_DIR .. "src/mame/includes/lordgun.h",
	MAME_DIR .. "src/mame/video/lordgun.cpp",
	MAME_DIR .. "src/hbmame/drivers/pgm.cpp",
	MAME_DIR .. "src/mame/includes/pgm.h",
	MAME_DIR .. "src/mame/video/pgm.cpp",
	MAME_DIR .. "src/mame/machine/pgmcrypt.cpp",
	MAME_DIR .. "src/mame/machine/pgmcrypt.h",
	MAME_DIR .. "src/mame/machine/pgmprot_igs027a_type1.cpp",
	MAME_DIR .. "src/mame/machine/pgmprot_igs027a_type1.h",
	MAME_DIR .. "src/mame/machine/pgmprot_igs027a_type2.cpp",
	MAME_DIR .. "src/mame/machine/pgmprot_igs027a_type2.h",
	MAME_DIR .. "src/mame/machine/pgmprot_igs027a_type3.cpp",
	MAME_DIR .. "src/mame/machine/pgmprot_igs027a_type3.h",
	MAME_DIR .. "src/mame/machine/pgmprot_igs025_igs012.cpp",
	MAME_DIR .. "src/mame/machine/pgmprot_igs025_igs012.h",
	MAME_DIR .. "src/mame/machine/pgmprot_igs025_igs022.cpp",
	MAME_DIR .. "src/mame/machine/pgmprot_igs025_igs022.h",
	MAME_DIR .. "src/mame/machine/pgmprot_igs025_igs028.cpp",
	MAME_DIR .. "src/mame/machine/pgmprot_igs025_igs028.h",
	MAME_DIR .. "src/mame/machine/pgmprot_orlegend.cpp",
	MAME_DIR .. "src/mame/machine/pgmprot_orlegend.h",
	MAME_DIR .. "src/mame/machine/igs025.cpp",
	MAME_DIR .. "src/mame/machine/igs025.h",
	MAME_DIR .. "src/mame/machine/igs022.cpp",
	MAME_DIR .. "src/mame/machine/igs022.h",
	MAME_DIR .. "src/mame/machine/igs028.cpp",
	MAME_DIR .. "src/mame/machine/igs028.h",
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
	MAME_DIR .. "src/hbmame/drivers/m92.cpp",
	MAME_DIR .. "src/mame/video/m92.cpp",
	MAME_DIR .. "src/mame/machine/irem_cpu.cpp",
}

createMAMEProjects(_target, _subtarget, "itech")
files {
	MAME_DIR .. "src/hbmame/drivers/itech8.cpp",
	MAME_DIR .. "src/mame/includes/itech8.h",
	MAME_DIR .. "src/mame/machine/itech8.cpp",
	MAME_DIR .. "src/mame/video/itech8.cpp",
}

createMAMEProjects(_target, _subtarget, "jaleco")
files {
	MAME_DIR .. "src/hbmame/drivers/ginganin.cpp",
	MAME_DIR .. "src/mame/includes/ginganin.h",
	MAME_DIR .. "src/mame/video/ginganin.cpp",
	MAME_DIR .. "src/hbmame/drivers/exerion.cpp",
	MAME_DIR .. "src/mame/includes/exerion.h",
	MAME_DIR .. "src/mame/video/exerion.cpp",
}

createMAMEProjects(_target, _subtarget, "kaneko")
files {
	MAME_DIR .. "src/hbmame/drivers/kaneko16.cpp",
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
	MAME_DIR .. "src/hbmame/drivers/yiear.cpp",
	MAME_DIR .. "src/mame/includes/yiear.h",
	MAME_DIR .. "src/mame/video/yiear.cpp",
	MAME_DIR .. "src/hbmame/drivers/timeplt.cpp",
	MAME_DIR .. "src/mame/includes/timeplt.h",
	MAME_DIR .. "src/mame/audio/timeplt.cpp",
	MAME_DIR .. "src/mame/audio/timeplt.h",
	MAME_DIR .. "src/mame/video/timeplt.cpp",
	MAME_DIR .. "src/hbmame/drivers/shaolins.cpp",
	MAME_DIR .. "src/mame/includes/shaolins.h",
	MAME_DIR .. "src/mame/video/shaolins.cpp",
	MAME_DIR .. "src/hbmame/drivers/blockhl.cpp",
	MAME_DIR .. "src/hbmame/drivers/gradius3.cpp",
	MAME_DIR .. "src/mame/includes/gradius3.h",
	MAME_DIR .. "src/mame/video/gradius3.cpp",
	MAME_DIR .. "src/hbmame/drivers/hyperspt.cpp",
	MAME_DIR .. "src/mame/includes/hyperspt.h",
	MAME_DIR .. "src/mame/video/hyperspt.cpp",
	MAME_DIR .. "src/hbmame/drivers/trackfld.cpp",
	MAME_DIR .. "src/mame/includes/trackfld.h",
	MAME_DIR .. "src/mame/audio/trackfld.cpp",
	MAME_DIR .. "src/mame/audio/trackfld.h",
	MAME_DIR .. "src/mame/video/trackfld.cpp",
	MAME_DIR .. "src/mame/audio/hyprolyb.cpp",
	MAME_DIR .. "src/mame/audio/hyprolyb.h",
	MAME_DIR .. "src/hbmame/drivers/pooyan.cpp",
	MAME_DIR .. "src/mame/includes/pooyan.h",
	MAME_DIR .. "src/mame/video/pooyan.cpp",
	MAME_DIR .. "src/mame/audio/timeplt.cpp",
	MAME_DIR .. "src/mame/audio/timeplt.h",
	MAME_DIR .. "src/hbmame/drivers/gyruss.cpp",
	MAME_DIR .. "src/mame/includes/gyruss.h",
	MAME_DIR .. "src/mame/video/gyruss.cpp",
	MAME_DIR .. "src/mame/machine/konami1.cpp",
	MAME_DIR .. "src/mame/machine/konami1.h",
	MAME_DIR .. "src/hbmame/drivers/twin16.cpp",
	MAME_DIR .. "src/mame/includes/twin16.h",
	MAME_DIR .. "src/mame/video/twin16.cpp",
	MAME_DIR .. "src/hbmame/drivers/tmnt.cpp",
	MAME_DIR .. "src/mame/includes/tmnt.h",
	MAME_DIR .. "src/mame/video/tmnt.cpp",
	MAME_DIR .. "src/mame/video/k053244_k053245.cpp",
	MAME_DIR .. "src/mame/video/k053244_k053245.h",
	MAME_DIR .. "src/mame/video/k052109.cpp",
	MAME_DIR .. "src/mame/video/k052109.h",
	MAME_DIR .. "src/mame/video/k051960.cpp",
	MAME_DIR .. "src/mame/video/k051960.h",
	MAME_DIR .. "src/mame/audio/timeplt.cpp",
	MAME_DIR .. "src/mame/audio/timeplt.h",
	MAME_DIR .. "src/hbmame/drivers/rallyx.cpp",
	MAME_DIR .. "src/mame/includes/rallyx.h",
	MAME_DIR .. "src/mame/video/rallyx.cpp",
	MAME_DIR .. "src/hbmame/drivers/nemesis.cpp",
	MAME_DIR .. "src/mame/includes/nemesis.h",
	MAME_DIR .. "src/mame/video/nemesis.cpp",
	MAME_DIR .. "src/hbmame/drivers/mystwarr.cpp",
	MAME_DIR .. "src/mame/includes/mystwarr.h",
	MAME_DIR .. "src/mame/video/mystwarr.cpp",
	MAME_DIR .. "src/mame/video/k054000.cpp",
	MAME_DIR .. "src/mame/video/k054000.h",
	MAME_DIR .. "src/hbmame/drivers/konamigx.cpp",
	MAME_DIR .. "src/mame/includes/konamigx.h",
	MAME_DIR .. "src/mame/machine/konamigx.cpp",
	MAME_DIR .. "src/mame/video/konamigx.cpp",
	MAME_DIR .. "src/mame/video/k053250.cpp",
	MAME_DIR .. "src/mame/video/k053250.h",
	MAME_DIR .. "src/mame/video/k054338.cpp",
	MAME_DIR .. "src/mame/video/k054338.h",
	MAME_DIR .. "src/hbmame/drivers/dbz.cpp",
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
	MAME_DIR .. "src/hbmame/drivers/contra.cpp",
	MAME_DIR .. "src/mame/machine/k007452.cpp",
	MAME_DIR .. "src/mame/machine/k007452.h",
	MAME_DIR .. "src/mame/video/k007121.cpp",
	MAME_DIR .. "src/mame/video/k007121.h",
	MAME_DIR .. "src/mame/video/konami_helper.cpp",
	MAME_DIR .. "src/mame/video/konami_helper.h",
}

createMAMEProjects(_target, _subtarget, "metro")
files {
	MAME_DIR .. "src/hbmame/drivers/rabbit.cpp",
}

createMAMEProjects(_target, _subtarget, "midway")
files {
	MAME_DIR .. "src/hbmame/drivers/mcr.cpp",
	MAME_DIR .. "src/mame/includes/mcr.h",
	MAME_DIR .. "src/mame/machine/mcr.cpp",
	MAME_DIR .. "src/mame/video/mcr.cpp",
	MAME_DIR .. "src/hbmame/drivers/astrocde.cpp",
	MAME_DIR .. "src/mame/includes/astrocde.h",
	MAME_DIR .. "src/mame/video/astrocde.cpp",
	MAME_DIR .. "src/hbmame/drivers/midtunit.cpp",
	MAME_DIR .. "src/mame/machine/midtunit.cpp",
	MAME_DIR .. "src/mame/video/midtunit.cpp",
	MAME_DIR .. "src/hbmame/drivers/midwunit.cpp",
	MAME_DIR .. "src/mame/machine/midwunit.cpp",
	MAME_DIR .. "src/hbmame/drivers/midyunit.cpp",
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
	MAME_DIR .. "src/hbmame/drivers/polepos.cpp",
	MAME_DIR .. "src/mame/includes/polepos.h",
	MAME_DIR .. "src/mame/audio/polepos.cpp",
	MAME_DIR .. "src/mame/audio/polepos.h",
	MAME_DIR .. "src/mame/video/polepos.cpp",
	MAME_DIR .. "src/hbmame/drivers/namcos86.cpp",
	MAME_DIR .. "src/mame/includes/namcos86.h",
	MAME_DIR .. "src/mame/video/namcos86.cpp",
	MAME_DIR .. "src/hbmame/drivers/pacland.cpp",
	MAME_DIR .. "src/hbmame/drivers/galaga.cpp",
	MAME_DIR .. "src/hbmame/includes/galaga.h",
	MAME_DIR .. "src/mame/audio/galaga.cpp",
	MAME_DIR .. "src/mame/video/galaga.cpp",
	MAME_DIR .. "src/mame/audio/namco52.cpp",
	MAME_DIR .. "src/mame/audio/namco52.h",
	MAME_DIR .. "src/mame/audio/namco54.cpp",
	MAME_DIR .. "src/mame/audio/namco54.h",
	MAME_DIR .. "src/mame/machine/namco06.cpp",
	MAME_DIR .. "src/mame/machine/namco06.h",
	MAME_DIR .. "src/mame/machine/namco50.cpp",
	MAME_DIR .. "src/mame/machine/namco50.h",
	MAME_DIR .. "src/mame/machine/namco51.cpp",
	MAME_DIR .. "src/mame/machine/namco51.h",
	MAME_DIR .. "src/mame/machine/namco53.cpp",
	MAME_DIR .. "src/mame/machine/namco53.h",
	MAME_DIR .. "src/mame/machine/xevious.cpp",
	MAME_DIR .. "src/mame/includes/xevious.h",
	MAME_DIR .. "src/mame/video/xevious.cpp",
	MAME_DIR .. "src/mame/video/bosco.cpp",
	MAME_DIR .. "src/mame/includes/bosco.h",
	MAME_DIR .. "src/mame/video/digdug.cpp",
	MAME_DIR .. "src/mame/includes/digdug.h",
	MAME_DIR .. "src/mame/video/starfield_05xx.cpp",
	MAME_DIR .. "src/mame/video/starfield_05xx.h",
	MAME_DIR .. "src/hbmame/drivers/namcos2.cpp",
	MAME_DIR .. "src/mame/includes/namcos2.h",
	MAME_DIR .. "src/mame/machine/namcos2.cpp",
	MAME_DIR .. "src/mame/video/namcos2.cpp",
	MAME_DIR .. "src/mame/machine/namco65.cpp",
	MAME_DIR .. "src/mame/machine/namco65.h",
	MAME_DIR .. "src/mame/machine/namco68.cpp",
	MAME_DIR .. "src/mame/machine/namco68.h",
	MAME_DIR .. "src/mame/machine/namco_c148.cpp",
	MAME_DIR .. "src/mame/machine/namco_c148.h",
	MAME_DIR .. "src/mame/machine/namco_c139.cpp",
	MAME_DIR .. "src/mame/machine/namco_c139.h",
	MAME_DIR .. "src/mame/video/namco_c116.cpp",
	MAME_DIR .. "src/mame/video/namco_c116.h",
	MAME_DIR .. "src/mame/video/namco_c123tmap.cpp",
	MAME_DIR .. "src/mame/video/namco_c123tmap.h",
	MAME_DIR .. "src/mame/video/namco_c45road.cpp",
	MAME_DIR .. "src/mame/video/namco_c45road.h",
	MAME_DIR .. "src/mame/video/namco_c169roz.cpp",
	MAME_DIR .. "src/mame/video/namco_c169roz.h",
	MAME_DIR .. "src/mame/video/namcos2_roz.cpp",
	MAME_DIR .. "src/mame/video/namcos2_roz.h",
	MAME_DIR .. "src/mame/video/namcos2_sprite.cpp",
	MAME_DIR .. "src/mame/video/namcos2_sprite.h",
	MAME_DIR .. "src/hbmame/drivers/namcona1.cpp",
	MAME_DIR .. "src/mame/includes/namcona1.h",
	MAME_DIR .. "src/mame/video/namcona1.cpp",
	MAME_DIR .. "src/mame/machine/namcomcu.cpp",
	MAME_DIR .. "src/mame/machine/namcomcu.h",
	MAME_DIR .. "src/hbmame/drivers/mappy.cpp",
	MAME_DIR .. "src/mame/includes/mappy.h",
	MAME_DIR .. "src/mame/video/mappy.cpp",
	MAME_DIR .. "src/mame/machine/namcoio.cpp",
	MAME_DIR .. "src/mame/machine/namcoio.h",
	MAME_DIR .. "src/mame/audio/cclimber.cpp",
	MAME_DIR .. "src/mame/audio/cclimber.h",
	MAME_DIR .. "src/hbmame/drivers/galaxian.cpp",
	MAME_DIR .. "src/hbmame/includes/galaxian.h",
	MAME_DIR .. "src/mame/audio/galaxian.cpp",
	MAME_DIR .. "src/mame/audio/galaxian.h",
	MAME_DIR .. "src/mame/video/galaxian.cpp",
	MAME_DIR .. "src/mame/audio/nl_konami.h",
	MAME_DIR .. "src/mame/audio/nl_konami.cpp",
	MAME_DIR .. "src/hbmame/machine/galser.cpp",
}

createMAMEProjects(_target, _subtarget, "nec")
files {
	MAME_DIR .. "src/mame/drivers/pce.cpp",
	MAME_DIR .. "src/mame/includes/pce.h",
	MAME_DIR .. "src/mame/machine/pce.cpp",
	MAME_DIR .. "src/mame/machine/pce_cd.cpp",
	MAME_DIR .. "src/mame/machine/pce_cd.h",
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
	MAME_DIR .. "src/hbmame/drivers/playch10.cpp",
	MAME_DIR .. "src/mame/includes/playch10.h",
	MAME_DIR .. "src/mame/machine/playch10.cpp",
	MAME_DIR .. "src/mame/video/playch10.cpp",
	MAME_DIR .. "src/hbmame/drivers/mario.cpp",
	MAME_DIR .. "src/mame/includes/mario.h",
	MAME_DIR .. "src/mame/audio/nl_mario.cpp",
	MAME_DIR .. "src/mame/audio/nl_mario.h",
	MAME_DIR .. "src/mame/audio/mario.cpp",
	MAME_DIR .. "src/mame/video/mario.cpp",
	MAME_DIR .. "src/mame/drivers/gb.cpp",
	MAME_DIR .. "src/mame/includes/gb.h",
	MAME_DIR .. "src/mame/machine/gb.cpp",
	MAME_DIR .. "src/mame/drivers/gba.cpp",
	MAME_DIR .. "src/mame/includes/gba.h",
	MAME_DIR .. "src/mame/drivers/snes.cpp",
	MAME_DIR .. "src/mame/includes/snes.h",
	MAME_DIR .. "src/mame/machine/snes.cpp",
	MAME_DIR .. "src/mame/machine/snescx4.cpp",
	MAME_DIR .. "src/mame/machine/snescx4.h",
	MAME_DIR .. "src/mame/machine/cx4data.hxx",
	MAME_DIR .. "src/mame/machine/cx4fn.hxx",
	MAME_DIR .. "src/mame/machine/cx4oam.hxx",
	MAME_DIR .. "src/mame/machine/cx4ops.hxx",
	MAME_DIR .. "src/mame/drivers/nes.cpp",
	MAME_DIR .. "src/mame/includes/nes.h",
	MAME_DIR .. "src/mame/machine/nes.cpp",
	MAME_DIR .. "src/mame/video/nes.cpp",
	MAME_DIR .. "src/hbmame/drivers/vsnes.cpp",
	MAME_DIR .. "src/mame/includes/vsnes.h",
	MAME_DIR .. "src/mame/machine/vsnes.cpp",
	MAME_DIR .. "src/hbmame/drivers/dkong.cpp",
	MAME_DIR .. "src/mame/includes/dkong.h",
	MAME_DIR .. "src/mame/audio/dkong.cpp",
	MAME_DIR .. "src/mame/video/dkong.cpp",
}

createMAMEProjects(_target, _subtarget, "nmk")
files {
	MAME_DIR .. "src/hbmame/drivers/powerins.cpp",
	MAME_DIR .. "src/mame/video/powerins.cpp",
	MAME_DIR .. "src/mame/drivers/nmk16.cpp",
	MAME_DIR .. "src/mame/video/nmk16.cpp",
	MAME_DIR .. "src/mame/video/nmk16spr.cpp",
	MAME_DIR .. "src/mame/machine/nmk004.cpp",
	MAME_DIR .. "src/mame/audio/seibu.cpp",
}

createMAMEProjects(_target, _subtarget, "pacman")
files {
	MAME_DIR .. "src/hbmame/drivers/puckman.cpp",
	MAME_DIR .. "src/hbmame/video/puckman.cpp",
}

createMAMEProjects(_target, _subtarget, "phoenix")
files {
	MAME_DIR .. "src/hbmame/drivers/phoenix.cpp",
	MAME_DIR .. "src/mame/includes/phoenix.h",
	MAME_DIR .. "src/mame/audio/phoenix.cpp",
	MAME_DIR .. "src/mame/audio/phoenix.h",
	MAME_DIR .. "src/mame/video/phoenix.cpp",
	MAME_DIR .. "src/mame/audio/pleiads.cpp",
	MAME_DIR .. "src/mame/audio/pleiads.h",
}

createMAMEProjects(_target, _subtarget, "psikyo")
files {
	MAME_DIR .. "src/hbmame/drivers/psikyo.cpp",
	MAME_DIR .. "src/mame/includes/psikyo.h",
	MAME_DIR .. "src/mame/video/psikyo.cpp",
	MAME_DIR .. "src/hbmame/drivers/psikyosh.cpp",
	MAME_DIR .. "src/mame/includes/psikyosh.h",
	MAME_DIR .. "src/mame/video/psikyosh.cpp",
}

createMAMEProjects(_target, _subtarget, "seibu")
files {
	MAME_DIR .. "src/hbmame/drivers/toki.cpp",
	MAME_DIR .. "src/mame/includes/toki.h",
	MAME_DIR .. "src/mame/video/toki.cpp",
	MAME_DIR .. "src/hbmame/drivers/legionna.cpp",
	MAME_DIR .. "src/mame/includes/legionna.h",
	MAME_DIR .. "src/mame/video/legionna.cpp",
	MAME_DIR .. "src/hbmame/drivers/r2dx_v33.cpp",
	MAME_DIR .. "src/hbmame/drivers/raiden2.cpp",
	MAME_DIR .. "src/mame/includes/raiden2.h",
	MAME_DIR .. "src/mame/video/raiden2.cpp",
	MAME_DIR .. "src/mame/machine/r2crypt.cpp",
	MAME_DIR .. "src/mame/machine/r2crypt.h",
	MAME_DIR .. "src/mame/machine/seibucop.cpp",
	MAME_DIR .. "src/mame/machine/seibucop.h",
	MAME_DIR .. "src/mame/machine/seibucop_dma.hxx",
	MAME_DIR .. "src/mame/machine/seibucop_cmd.hxx",
	MAME_DIR .. "src/mame/machine/seibuspi.cpp",
	MAME_DIR .. "src/mame/machine/seibuspi.h",
	MAME_DIR .. "src/mame/video/seibu_crtc.cpp",
	MAME_DIR .. "src/mame/video/seibu_crtc.h",
}

createMAMEProjects(_target, _subtarget, "seta")
files {
	MAME_DIR .. "src/hbmame/drivers/ssv.cpp",
	MAME_DIR .. "src/mame/includes/ssv.h",
	MAME_DIR .. "src/mame/video/ssv.cpp",
	MAME_DIR .. "src/mame/video/st0020.cpp",
	MAME_DIR .. "src/mame/video/st0020.h",
	MAME_DIR .. "src/hbmame/drivers/seta2.cpp",
	MAME_DIR .. "src/mame/includes/seta2.h",
	MAME_DIR .. "src/mame/video/seta2.cpp",
	MAME_DIR .. "src/hbmame/drivers/seta.cpp",
	MAME_DIR .. "src/mame/includes/seta.h",
	MAME_DIR .. "src/mame/video/seta.cpp",
	MAME_DIR .. "src/mame/video/seta001.cpp",
	MAME_DIR .. "src/mame/video/seta001.h",
	MAME_DIR .. "src/mame/video/x1_012.cpp",
	MAME_DIR .. "src/mame/video/x1_012.h",
}

createMAMEProjects(_target, _subtarget, "sega")
files {
	MAME_DIR .. "src/hbmame/drivers/system16.cpp",
	MAME_DIR .. "src/mame/includes/system16.h",
	MAME_DIR .. "src/mame/video/system16.cpp",
	MAME_DIR .. "src/hbmame/drivers/model2.cpp",
	MAME_DIR .. "src/mame/machine/model2.cpp",
	MAME_DIR .. "src/mame/includes/model2.h",
	MAME_DIR .. "src/mame/video/model2rd.hxx",
	MAME_DIR .. "src/mame/video/model2.cpp",
	MAME_DIR .. "src/mame/machine/315_5649.cpp",
	MAME_DIR .. "src/mame/machine/315_5649.h",
	MAME_DIR .. "src/mame/machine/m2comm.cpp",
	MAME_DIR .. "src/mame/machine/m2comm.h",
	MAME_DIR .. "src/hbmame/drivers/model1.cpp",
	MAME_DIR .. "src/mame/includes/model1.h",
	MAME_DIR .. "src/mame/machine/model1.cpp",
	MAME_DIR .. "src/mame/video/model1.cpp",
	MAME_DIR .. "src/mame/audio/dsbz80.cpp",
	MAME_DIR .. "src/mame/audio/dsbz80.h",
	MAME_DIR .. "src/mame/audio/segam1audio.cpp",
	MAME_DIR .. "src/mame/audio/segam1audio.h",
	MAME_DIR .. "src/mame/machine/m1comm.cpp",
	MAME_DIR .. "src/mame/machine/m1comm.h",
	MAME_DIR .. "src/mame/machine/model1io.cpp",
	MAME_DIR .. "src/mame/machine/model1io.h",
	MAME_DIR .. "src/mame/machine/model1io2.cpp",
	MAME_DIR .. "src/mame/machine/model1io2.h",
	MAME_DIR .. "src/mame/video/segaic24.cpp",
	MAME_DIR .. "src/mame/video/segaic24.h",
	MAME_DIR .. "src/hbmame/drivers/segaxbd.cpp",
	MAME_DIR .. "src/mame/includes/segaxbd.h",
	MAME_DIR .. "src/mame/video/segaxbd.cpp",
	MAME_DIR .. "src/hbmame/drivers/segaorun.cpp",
	MAME_DIR .. "src/mame/includes/segaorun.h",
	MAME_DIR .. "src/mame/video/segaorun.cpp",
	MAME_DIR .. "src/mame/video/segaic16_road.cpp",
	MAME_DIR .. "src/mame/video/segaic16_road.h",
	MAME_DIR .. "src/hbmame/drivers/segac2.cpp",
	MAME_DIR .. "src/mame/drivers/sg1000.cpp",
	MAME_DIR .. "src/mame/includes/sg1000.h",
	MAME_DIR .. "src/mame/drivers/sms.cpp",
	MAME_DIR .. "src/mame/includes/sms.h",
	MAME_DIR .. "src/mame/machine/sms.cpp",
	MAME_DIR .. "src/mame/drivers/megadriv.cpp",
	MAME_DIR .. "src/mame/includes/megadriv.h",
	MAME_DIR .. "src/mame/machine/megadriv.cpp",
	MAME_DIR .. "src/mame/machine/mega32x.cpp",
	MAME_DIR .. "src/mame/machine/mega32x.h",
	MAME_DIR .. "src/mame/machine/megacd.cpp",
	MAME_DIR .. "src/mame/machine/megacd.h",
	MAME_DIR .. "src/mame/machine/megacdcd.cpp",
	MAME_DIR .. "src/mame/machine/megacdcd.h",
	MAME_DIR .. "src/hbmame/drivers/system1.cpp",
	MAME_DIR .. "src/mame/includes/system1.h",
	MAME_DIR .. "src/mame/machine/segacrpt_device.cpp",
	MAME_DIR .. "src/mame/machine/segacrpt_device.h",
	MAME_DIR .. "src/mame/machine/segacrp2_device.cpp",
	MAME_DIR .. "src/mame/machine/segacrp2_device.h",
	MAME_DIR .. "src/mame/video/system1.cpp",
	MAME_DIR .. "src/mame/audio/rax.cpp",
	MAME_DIR .. "src/mame/audio/rax.h",
	MAME_DIR .. "src/hbmame/drivers/stv.cpp",
	MAME_DIR .. "src/mame/includes/saturn.h",
	MAME_DIR .. "src/mame/drivers/saturn.cpp",
	MAME_DIR .. "src/mame/machine/saturn.cpp",
	MAME_DIR .. "src/mame/video/saturn.cpp",
	MAME_DIR .. "src/mame/machine/315-5838_317-0229_comp.cpp",
	MAME_DIR .. "src/mame/machine/315-5838_317-0229_comp.h",
	MAME_DIR .. "src/mame/machine/315-5881_crypt.cpp",
	MAME_DIR .. "src/mame/machine/315-5881_crypt.h",
	MAME_DIR .. "src/mame/machine/315_5338a.cpp",
	MAME_DIR .. "src/mame/machine/315_5338a.h",
	MAME_DIR .. "src/mame/machine/saturn_cdb.cpp",
	MAME_DIR .. "src/mame/machine/saturn_cdb.h",
	MAME_DIR .. "src/mame/machine/segabill.cpp",
	MAME_DIR .. "src/mame/machine/segabill.h",
	MAME_DIR .. "src/hbmame/drivers/segas32.cpp",
	MAME_DIR .. "src/mame/includes/segas32.h",
	MAME_DIR .. "src/mame/machine/segas32.cpp",
	MAME_DIR .. "src/mame/video/segas32.cpp",
	MAME_DIR .. "src/mame/machine/315_5296.cpp",
	MAME_DIR .. "src/mame/machine/315_5296.h",
	MAME_DIR .. "src/mame/machine/s32comm.cpp",
	MAME_DIR .. "src/mame/machine/s32comm.h",
	MAME_DIR .. "src/mame/audio/nl_segas16b.cpp",
	MAME_DIR .. "src/mame/audio/nl_segas16b.h",
	MAME_DIR .. "src/hbmame/drivers/segas16b.cpp",
	MAME_DIR .. "src/mame/includes/segas16b.h",
	MAME_DIR .. "src/mame/video/segas16b.cpp",
	MAME_DIR .. "src/mame/machine/315_5195.cpp",
	MAME_DIR .. "src/mame/machine/315_5195.h",
	MAME_DIR .. "src/mame/machine/fd1089.cpp",
	MAME_DIR .. "src/mame/machine/fd1089.h",
	MAME_DIR .. "src/mame/machine/fd1094.cpp",
	MAME_DIR .. "src/mame/machine/fd1094.h",
	MAME_DIR .. "src/mame/machine/mc8123.cpp",
	MAME_DIR .. "src/mame/machine/mc8123.h",
	MAME_DIR .. "src/mame/machine/segaic16.cpp",
	MAME_DIR .. "src/mame/machine/segaic16.h",
	MAME_DIR .. "src/mame/video/sega16sp.cpp",
	MAME_DIR .. "src/mame/video/sega16sp.h",
	MAME_DIR .. "src/mame/video/segaic16.cpp",
	MAME_DIR .. "src/mame/video/segaic16.h",
}

createMAMEProjects(_target, _subtarget, "snk")
files {
	MAME_DIR .. "src/hbmame/drivers/snk6502.cpp",
	MAME_DIR .. "src/mame/includes/snk6502.h",
	MAME_DIR .. "src/mame/audio/snk6502.cpp",
	MAME_DIR .. "src/mame/audio/snk6502.h",
	MAME_DIR .. "src/mame/video/snk6502.cpp",
	MAME_DIR .. "src/mame/drivers/ngp.cpp",
	MAME_DIR .. "src/mame/video/k1ge.cpp",
	MAME_DIR .. "src/mame/video/k1ge.h",
}

createMAMEProjects(_target, _subtarget, "sony")
files {
	MAME_DIR .. "src/mame/audio/taito_zm.cpp",
	MAME_DIR .. "src/mame/audio/taito_zm.h",
	MAME_DIR .. "src/hbmame/drivers/zn.cpp",
	MAME_DIR .. "src/mame/includes/zn.h",
	MAME_DIR .. "src/mame/machine/znmcu.cpp",
	MAME_DIR .. "src/mame/machine/znmcu.h",
	MAME_DIR .. "src/mame/machine/cat702.cpp",
	MAME_DIR .. "src/mame/machine/cat702.h",
}

createMAMEProjects(_target, _subtarget, "taito")
files {
	MAME_DIR .. "src/hbmame/drivers/retofinv.cpp",
	MAME_DIR .. "src/mame/includes/retofinv.h",
	MAME_DIR .. "src/mame/video/retofinv.cpp",
	MAME_DIR .. "src/hbmame/drivers/volfied.cpp",
	MAME_DIR .. "src/mame/includes/volfied.h",
	MAME_DIR .. "src/mame/video/volfied.cpp",
	MAME_DIR .. "src/hbmame/drivers/tnzs.cpp",
	MAME_DIR .. "src/mame/includes/tnzs.h",
	MAME_DIR .. "src/mame/machine/tnzs.cpp",
	MAME_DIR .. "src/mame/video/tnzs.cpp",
	MAME_DIR .. "src/hbmame/drivers/taotaido.cpp",
	MAME_DIR .. "src/mame/includes/taotaido.h",
	MAME_DIR .. "src/mame/video/taotaido.cpp",
	MAME_DIR .. "src/hbmame/drivers/taitosj.cpp",
	MAME_DIR .. "src/mame/includes/taitosj.h",
	MAME_DIR .. "src/mame/machine/taitosj.cpp",
	MAME_DIR .. "src/mame/video/taitosj.cpp",
	MAME_DIR .. "src/mame/machine/taitosjsec.cpp",
	MAME_DIR .. "src/mame/machine/taitosjsec.h",
	MAME_DIR .. "src/hbmame/drivers/taito_l.cpp",
	MAME_DIR .. "src/mame/includes/taito_l.h",
	MAME_DIR .. "src/mame/video/taito_l.cpp",
	MAME_DIR .. "src/mame/audio/taito_en.cpp",
	MAME_DIR .. "src/mame/audio/taito_en.h",
	MAME_DIR .. "src/hbmame/drivers/taito_f3.cpp",
	MAME_DIR .. "src/mame/includes/taito_f3.h",
	MAME_DIR .. "src/mame/video/taito_f3.cpp",
	MAME_DIR .. "src/hbmame/drivers/taito_f2.cpp",
	MAME_DIR .. "src/mame/includes/taito_f2.h",
	MAME_DIR .. "src/mame/video/taito_f2.cpp",
	MAME_DIR .. "src/mame/video/tc0280grd.cpp",
	MAME_DIR .. "src/mame/video/tc0280grd.h",
	MAME_DIR .. "src/mame/video/tc0360pri.cpp",
	MAME_DIR .. "src/mame/video/tc0360pri.h",
	MAME_DIR .. "src/mame/video/tc0480scp.cpp",
	MAME_DIR .. "src/mame/video/tc0480scp.h",
	MAME_DIR .. "src/hbmame/drivers/rastan.cpp",
	MAME_DIR .. "src/mame/video/pc080sn.cpp",
	MAME_DIR .. "src/mame/video/pc080sn.h",
	MAME_DIR .. "src/mame/video/taito_helper.cpp",
	MAME_DIR .. "src/mame/video/taito_helper.h",
	MAME_DIR .. "src/hbmame/drivers/lkage.cpp",
	MAME_DIR .. "src/mame/includes/lkage.h",
	MAME_DIR .. "src/mame/video/lkage.cpp",
	MAME_DIR .. "src/hbmame/drivers/kikikai.cpp",
	MAME_DIR .. "src/mame/includes/kikikai.h",
	MAME_DIR .. "src/mame/machine/kikikai.cpp",
	MAME_DIR .. "src/mame/video/kikikai.cpp",
	MAME_DIR .. "src/hbmame/drivers/flstory.cpp",
	MAME_DIR .. "src/mame/includes/flstory.h",
	MAME_DIR .. "src/mame/video/flstory.cpp",
	MAME_DIR .. "src/hbmame/drivers/bublbobl.cpp",
	MAME_DIR .. "src/mame/includes/bublbobl.h",
	MAME_DIR .. "src/mame/machine/bublbobl.cpp",
	MAME_DIR .. "src/mame/video/bublbobl.cpp",
	MAME_DIR .. "src/hbmame/drivers/asuka.cpp",
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
	MAME_DIR .. "src/hbmame/drivers/arkanoid.cpp",
	MAME_DIR .. "src/mame/includes/arkanoid.h",
	MAME_DIR .. "src/mame/machine/arkanoid.cpp",
	MAME_DIR .. "src/mame/video/arkanoid.cpp",
	MAME_DIR .. "src/mame/machine/taito68705interface.cpp",
	MAME_DIR .. "src/mame/machine/taito68705interface.h",
}

createMAMEProjects(_target, _subtarget, "technos")
files {
	MAME_DIR .. "src/hbmame/drivers/shadfrce.cpp",
	MAME_DIR .. "src/mame/includes/shadfrce.h",
	MAME_DIR .. "src/mame/video/shadfrce.cpp",
}

createMAMEProjects(_target, _subtarget, "tehkan")
files {
	MAME_DIR .. "src/hbmame/drivers/tehkanwc.cpp",
	MAME_DIR .. "src/mame/includes/tehkanwc.h",
	MAME_DIR .. "src/mame/video/tehkanwc.cpp",
	MAME_DIR .. "src/hbmame/drivers/tecmosys.cpp",
	MAME_DIR .. "src/mame/includes/tecmosys.h",
	MAME_DIR .. "src/mame/machine/tecmosys.cpp",
	MAME_DIR .. "src/mame/video/tecmosys.cpp",
	MAME_DIR .. "src/hbmame/drivers/tecmo16.cpp",
	MAME_DIR .. "src/mame/includes/tecmo16.h",
	MAME_DIR .. "src/mame/video/tecmo16.cpp",
	MAME_DIR .. "src/mame/video/tecmo_mix.cpp",
	MAME_DIR .. "src/mame/video/tecmo_mix.h",
	MAME_DIR .. "src/hbmame/drivers/tecmo.cpp",
	MAME_DIR .. "src/mame/includes/tecmo.h",
	MAME_DIR .. "src/mame/video/tecmo.cpp",
	MAME_DIR .. "src/mame/video/tecmo_spr.cpp",
	MAME_DIR .. "src/mame/video/tecmo_spr.h",
	MAME_DIR .. "src/hbmame/drivers/solomon.cpp",
	MAME_DIR .. "src/mame/includes/solomon.h",
	MAME_DIR .. "src/mame/video/solomon.cpp",
	MAME_DIR .. "src/hbmame/drivers/bombjack.cpp",
	MAME_DIR .. "src/mame/includes/bombjack.h",
	MAME_DIR .. "src/mame/video/bombjack.cpp",
}

createMAMEProjects(_target, _subtarget, "toaplan")
files {
	MAME_DIR .. "src/hbmame/drivers/twincobr.cpp",
	MAME_DIR .. "src/mame/includes/twincobr.h",
	MAME_DIR .. "src/mame/machine/twincobr.cpp",
	MAME_DIR .. "src/mame/video/twincobr.cpp",
	MAME_DIR .. "src/mame/video/toaplan_scu.cpp",
	MAME_DIR .. "src/mame/video/toaplan_scu.h",
	MAME_DIR .. "src/hbmame/drivers/toaplan2.cpp",
	MAME_DIR .. "src/mame/includes/toaplan2.h",
	MAME_DIR .. "src/mame/video/toaplan2.cpp",
	MAME_DIR .. "src/mame/video/gp9001.cpp",
	MAME_DIR .. "src/mame/video/gp9001.h",
	MAME_DIR .. "src/hbmame/drivers/snowbros.cpp",
	MAME_DIR .. "src/mame/includes/snowbros.h",
	MAME_DIR .. "src/mame/video/snowbros.cpp",
	MAME_DIR .. "src/mame/video/kan_pand.cpp",
	MAME_DIR .. "src/mame/video/kan_pand.h",
}

createMAMEProjects(_target, _subtarget, "unico")
files {
	MAME_DIR .. "src/hbmame/drivers/silkroad.cpp",
	MAME_DIR .. "src/mame/includes/silkroad.h",
	MAME_DIR .. "src/mame/video/silkroad.cpp",
}

createMAMEProjects(_target, _subtarget, "univers")
files {
	MAME_DIR .. "src/hbmame/drivers/docastle.cpp",
	MAME_DIR .. "src/mame/includes/docastle.h",
	MAME_DIR .. "src/mame/machine/docastle.cpp",
	MAME_DIR .. "src/mame/video/docastle.cpp",
	MAME_DIR .. "src/hbmame/drivers/mrdo.cpp",
	MAME_DIR .. "src/mame/includes/mrdo.h",
	MAME_DIR .. "src/mame/video/mrdo.cpp",
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
	MAME_DIR .. "src/hbmame/drivers/aerofgt.cpp",
	MAME_DIR .. "src/mame/includes/aerofgt.h",
	MAME_DIR .. "src/mame/video/aerofgt.cpp",
}

--------------------------------------------------
-- remaining drivers
--------------------------------------------------

createMAMEProjects(_target, _subtarget, "misc")
files {
	MAME_DIR .. "src/hbmame/drivers/monaco.cpp",
	MAME_DIR .. "src/hbmame/drivers/vamphalf.cpp",
	MAME_DIR .. "src/hbmame/drivers/kyugo.cpp",
	MAME_DIR .. "src/mame/includes/kyugo.h",
	MAME_DIR .. "src/mame/video/kyugo.cpp",
}
end
