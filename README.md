# NeoEX
What is NeoEX?

It focuses on compiling everything about the Neo Geo MVS/AES and Capcom system, and preserving all types of ROMs that have existed, including Bootleg, HomeBrew, and Hacks.

Version 0.289 [[HBMAME](https://github.com/Robbbert/hbmame)] is being used as the base system.

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
