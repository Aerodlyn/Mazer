# Mazer - An attempt at Maze (Dungeon-esqe) Generation

Mazer is a relatively simple game that generates a random imperfect maze, stylized in the idea of exploring a dungeon in a retro RPG. The game uses C and Allegro for the majority of its logic and entirely for graphics. However, I wanted to implement some logic in another language. Initially I thought about using Assembly (NASM) but I quickly decided that would be more trouble than it would be worth. So, I decided I would either use Fortran or Lua. I chose Fortran as I was more curious about working with it then Lua, given that I have some previous experience with Lua.

## Compiling
To compile Mazer, you will need GCC (which includes gfortran), Make, and Allegro 5 (and by extension pkg-config). Once the repository is cloned or downloaded, navigate to the parent directory (../Path/To/Mazer/, i.e. the directory that contains Makefile, Sources/, and Headers/). Run `make` and an executable named `Mazer` will be generated in the parent directory.

Please report any errors that you get. If you receive errors from pkg-config, you may need to point `PKG_CONFIG_PATH` to where Allegro installed its pkg-config files to (e.g. allegro-5*.pc).

## Note
Mazer seems to compile just fine on my two Linux machines, but has issues on my OSX machine. Initially gcc would complain about unused linker options, and if you recompiled it wouldn't. But, occasionally upon running the game, the system would experience a kernel panic. I currently have no idea whether or not this issue is simply my computer, Allegro, or my programming is at fault (which I doubt would cause the entire system to shut down).

So if you are going to compile Mazer on OSX, be warned that bad things may happen so I wouldn't run the program if you have other applications open.
