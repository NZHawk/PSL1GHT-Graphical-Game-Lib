/*
  Header file for pggl.c
*/

// User options for PGGL
#define NUMERALLOCATION "/dev_usb000/FONT/numerals/"
#define UPPERCASELOCATION "/dev_usb000/FONT/upperCase/"
#define LOWERCASELOCATION "/dev_usb000/FONT/lowerCase/"
#define CHARWIDTH 80  //In PX - Width of character PNG
#define CHARHEIGHT 80 //In PX - Height of character PNG


void init_pggl();
void draw(char input[], int posx, int posy);
void drawInt(int number, int posx, int posy);
void drawButton(PngDatas buttonDown, PngDatas buttonUp, int state, int posx, int poy);