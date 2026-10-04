# NeoEX
What is NeoEX?

It focuses on compiling everything related to NeoGeo CD, Neo Geo MVS/AES, and Capcom systems, as well as preserving all types of existing ROMs—including Bootleg, Translation, CD Conversion, Darksoft, Decrypted C, Earlier, MGD2, NeoSD, Homebrew and Hack versions.

All source code used to create the base system:

The GitHub container: Robert [[HBMAME](https://github.com/Robbbert/hbmame)]

The GitHub container: Dirstac [[Arcade Extended](https://github.com/Dirstac/ArcadeUI-CHS)]

The GitHub container: Kaze [[EKMAME](https://github.com/WOOSEOK99/EKMAME)]

It runs on Windows 10 build 1607, 64-bit or later.

How to compile
--------------
In order to compile this version we will need the source code, for this we will place it in the folder "docs/Source Code[HBMame]/abcdefg-tag289.7z.001", once located we will begin to unzip the files it will take a few minutes, once unzipped we will have a folder with the name "abcdefg-tag289.7z", we will rename it to “src”. Now we will get the latest source code from this Github container once downloaded we will start to unzip and once finished unzipping we will select the files that we had left in the folder “3rdparty, scripts, src and makefile” folders, then copy them into the "src" folder. When the system asks to confirm file replacement, accept the operation.

The version used is msys64 15.0.2; if you do not have it, you can find it in the folder “docs / Build Tools / msys64-15.0.2.7z.001”.

And we will apply this command to start the compilation:
```
make OSD=winui PTR64=1 SUBTARGET=arcade SYMBOLS=0 NO_SYMBOLS=1 DEPRECATED=0
```

Open Source Software Projects
------------------------------
Although the source code is free to use, please note that the use of this code for any commercial exploitation or use of the project for fundraising purposes is prohibited.
