/*
  Header file for pggl.c
*/

void init_pggl();
//void drawPNG(PngDatas pngIn, int posx, int posy);
void draw(char input[], int posx, int posy);
void drawInt(int number, int posx, int posy);
void drawButton(PngDatas buttonDown, PngDatas buttonUp, int state, int posx, int poy);
