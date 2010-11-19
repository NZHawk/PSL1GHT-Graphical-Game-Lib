/*
  Header file for pggl.c
*/

// User options for PGGL --modded for PKG
#define NUMERALLOCATION "/dev_hdd0/game/PGGL00000/USRDIR/FONT/numerals/"
#define UPPERCASELOCATION "/dev_hdd0/game/PGGL00000/USRDIR/FONT/upperCase/"
#define LOWERCASELOCATION "/dev_hdd0/game/PGGL00000/USRDIR/FONT/lowerCase/"
#define CHARWIDTH 80  //In PX - Width of character PNG
#define CHARHEIGHT 80 //In PX - Height of character PNG

void init_pggl();
void draw(char input[], int posx, int posy);
void drawInt(int number, int posx, int posy);
void drawButton(PngDatas buttonDown, PngDatas buttonUp, int state, int posx, int poy);
