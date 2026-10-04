# NeoEX
What is NeoEX?

It focuses on compiling everything related to NeoGeo CD, Neo Geo MVS/AES, and Capcom systems, as well as preserving all types of existing ROMs—including Bootleg, Translation, CD Conversion, Darksoft, Decrypted C, Earlier, MGD2, NeoSD, Homebrew and Hack versions.

All source code used to create the base system::

Robert [[HBMAME](https://github.com/Robbbert/hbmame)], Dirstac [[Arcade Extended](https://github.com/Dirstac/ArcadeUI-CHS)] y Kaze [[EKMAME](https://github.com/WOOSEOK99/EKMAME)].

It runs on Windows 10 build 1607, 64-bit or later.

How to compile
--------------
To compile this version, we need the source code; you can find it in the folder “docs / Source Code [HBMame] / abcdefg-tag289.7z.001”. Once located, begin extracting the files (a process that will take a few minutes); upon completion, you will have a folder named “abcdefg-tag289.7z”, which you should rename to "src". Next, obtain the latest version of the source code from my GitHub repository; once downloaded, extract it and select the files corresponding to the "3rdparty, scripts, src, and makefile" folders, then copy them into the "src" folder. When the system asks to confirm file replacement, accept the operation.

The version used is msys64 15.0.2; if you do not have it, you can find it in the folder “docs / Build Tools / msys64-15.0.2.7z.001”.

And we will apply this command to start the compilation:
```
make OSD=winui PTR64=1 SUBTARGET=arcade SYMBOLS=0 NO_SYMBOLS=1 DEPRECATED=0
```

Open Source Software Projects
------------------------------
Although the source code is free to use, please note that the use of this code for any commercial exploitation or use of the project for fundraising purposes is prohibited.
