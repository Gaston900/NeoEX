# NeoEX
What is NeoEX?

It focuses on compiling everything about the Neo Geo MVS/AES and Capcom system, and preserving all types of ROMs that have existed, including Bootleg, HomeBrew, and Hacks.

Version 0.245 [[HBMAME](https://github.com/Robbbert/hbmame)] is being used as the base system.

I am only supporting the operating systems 64x bits, Windows 7, Windows 8, Windows 10 and Windows 11.

What has been optimized in this version?
---------------------------------------

Players 1 and 2 use this controller by default:

* To move, use the arrow keys "Up, Down, Left, Right."
* To perform actions, use the "A, S, D, Z, X, C, Q, W, E" keys.

The M68000 CPU core has been modified to be compatible with all current types of hack ROMs.

Support for extending adpcma files (NeoGeo) (By Robert)

Added custom buttons and autofire.

Removed the black border on NeoGeo systems, now has full screen.

Removed warning screen, startups, Loading, Decryption screen texts.

Removed the following annoying messages: “WRONG LENGTH”, “NO_DUMP”, “WRONG CHECKSUMS”, “BAD_DUMP” And “THE PARENT FILE DOES NOT EXIST”.

Added movement optimization V.4 for all fighting games (By GSC2007).

The Arcade64 "GUI" EKMAME source code has been implemented (By KAZE).

It is already pre-configured, enforce aspect ratio is disabled, full screen mode and tricks are already enabled by default.

The cheat reference function, if the cloned game does not have a cheat file, it will reference the cheat file of the main ROM.

Supports game list language files and multilingual title display (By 缘来是你).

Supports Skip CRC/IPS Check (By 缘来是你).

NEOGEO, driver supports key combination settings (By KAZE).

Two new folder sections called “config” and “support” were added that independently group the configurations and extra content, so that everything is kept in order in a single folder.

In the Config folders it is incorporated by:

Bgfx, Cfg, Comments, Crosshair, Diff, Docs, Folders, Glsl, Gui, Hash, Hlsl, Ini, Inp, Language, Nvram, Plugins, Share, Sta.

In the support folders it is incorporated by:

Artpreview, Artwork, Bosses, Cabinets, Cheat, Cpanel, Ctrlr, Flyers, Gameover, Howto, Icons,
Logo, Manuals, Marquees, Pcb, Roms, Samples, Scores, Select, Snap, Titles, Versus, Video, Cheat.7z, Command.dat, Gameinit.dat, Hiscore.dat, History.dat, Mameinfo.dat, Story. dat and Sysinfo.dat

How to compile
--------------
In order to compile this version we will need the source code, for this we will locate it in the folder docs / Source Code [HBMame] / hbmame-tag232.7z. 001, once located we will begin to unzip the files, it will take a few minutes, once unzipped we will have a folder with the name hbmame-tag245.7z, we will rename it to “src”, Now we will get the latest source code of this Github container once downloaded we will begin to unzip and once finished unzipping we will select the files that we had left in the folder “scripts, src and makefile” we will copy them into the src folder, the system will ask us to replace it we will say yes.

And we will apply this command to start the compilation, this command is for Windows 64-Bit system:
```
make PTR64=1 SUBTARGET=arcade OSD=winui NOWERROR=1 STRIP_SYMBOLS=1
```
The compilation [TOOL](https://github.com/mamedev/buildtools/releases) is suggested to be version msys64 2022-01-11.

Open Source Software Projects
------------------------------
Although the source code is free to use, please note that the use of this code for any commercial exploitation or use of the project for fundraising purposes is prohibited.
