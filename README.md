# NeoEX
What is NeoEX?

It is a project that implements all the features of the [SLUGNEO](https://github.com/Gaston900/SlugNeo) emulator, dedicated to preserving the entire NeoGeo "MVS/AES" system (Predecrypted, Decrypted, HomeBrew, Earlier, Bootleg, Multi Game Doctor 2, CD Conversion, Darksoft, NeoSD And Hack)

Version 0.245 [[HBMAME](https://github.com/Robbbert/hbmame)] is being used as the base system.

I am only supporting the operating systems, Windows 7, Windows 8, Windows 10 and Windows 11.

How to compile
--------------
In order to compile this version we will need the source code, for this we will locate it in the folder docs / Source Code [HBMame] / hbmame-tag232.7z. 001, once located we will begin to unzip the files, it will take a few minutes, once unzipped we will have a folder with the name hbmame-tag232.7z, we will rename it to “src”, Now we will get the latest source code of this Github container once downloaded we will begin to unzip and once finished unzipping we will select the files that we had left in the folder “scripts, src and makefile” we will copy them into the src folder, the system will ask us to replace it we will say yes.

And we will apply this command to start the compilation, this command is for Windows 64-Bit system:
```
make PTR64=1 SUBTARGET=arcade OSD=winui NOWERROR=1 STRIP_SYMBOLS=1
```
The compilation [TOOL](https://github.com/mamedev/buildtools/releases) is suggested to be version msys64 2022-01-11.

Open Source Software Projects
------------------------------
Although the source code is free to use, please note that the use of this code for any commercial exploitation or use of the project for fundraising purposes is prohibited.
