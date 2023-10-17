# R-Type

R-type is a multiplayer 2D shoot'em up game. The game is separated in two part: the client that display the game to the user, and the server who handle connections and running the game.

# Downloading
There is two ways to get each part of the game:

## Get the release
Go to the latest release, you can download the archive for either the server or the client depending of your platform and architecture

### On Linux
Extract the archive then run the install script as this:
```bash
$> cd [extracted folder]/[client or server]
$> ./install.sh
```
Note: if you change shell, you'll have to repeat this step.

After restarting the shell you can then run the client with `r-type_client` and/or the server with `r-type_server`

### On Windows
Extract the archive then go to the extracted folder and double-click on the `install.bat` file

## Build from source

### On Linux

**Requirements**:
 - freetype
 - x11
 - xrandr
 - udev
 - opengl
 - flac
 - ogg
 - vorbis
 - vorbisenc
 - vorbisfile
 - openal
 - pthread
 - cmake
 - a make program
 - a C++ compiler

You should have this installed beforehand.

To build from source, you'll have to download the source code from either a release or in the `Code` menu on the repository Github page.

Then you'll have to go the folder and execute the `build_unix.sh` script like this:
```bash
$> ./build_unix.sh
```

You'll then have the corresponding binary in the R-Type folder for the client and the R-Type-folder for the server.

### On Windows

**Requiremants**:
 - cmake
 - a C++ compiler

You should have this installed beforehand.

To build from source, you'll have to download the source code from either a release or in the `Code` menu on the repository Github page.

Then you'll have to go the folder and execute the `build_win.bat` script by double-clicking on it.

You'll then have the corresponding binary in the R-Type folder for the client and the R-Type-folder for the server.

# Usage
**Important**: Always run the executable alongside the .dll files on windows. For Linux, you should run the binary with the .so files alongside it or as is if you're building from source.

## Linux
### Server
```bash
$> ./r-type_server [port (default: 8080)]
```
### Client
You should always run from a folder containing the `R-Type/assets` folder.
```bash
$> ./r-type_client [ip (default: 127.0.0.1)] [port (default: 8080)]
```

## Windows
### Server
```cmd
.\r-type_server.exe [port (default: 8080)]
```
You can also double clicking on the executable, however you'll only use the default parameters this way.
### Client
You should always run from a folder containing the `R-Type/assets` folder.
```cmd
./r-type_client.exe [ip (default: 127.0.0.1)] [port (default: 8080)]
```
You can also double clicking on the executable, however you'll only use the default parameters this way.