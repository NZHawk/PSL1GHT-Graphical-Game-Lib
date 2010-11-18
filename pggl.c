/*
    PSL1GHT Graphical Game Lib  
    Author Darkhacker, NZHawk

    Graphical output must be on a white screen
    Unless you change the color of the fonts being
    Used in NUMBER folder

    Change FOLDER LOCATIONS to the location where your
    Number and ALPHA folders located.
*/

#include <psl1ght/lv2.h>
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <assert.h>
#include <unistd.h>
#include <sysutil/video.h>
#include <rsx/gcm.h>
#include <rsx/reality.h>
#include <stdlib.h>
#include <sysmodule/sysmodule.h>
#include <pngdec/pngdec.h>
#include <pngdec/loadpng.h>

#define NUMERALLOCATION "/dev_usb001/BOMBERMAN/USRDIR/FONT/numerals/"
#define UPPERCASELOCATION "/dev_usb001/BOMBERMAN/USRDIR/FONT/upperCase/"
#define LOWERCASELOCATION "/dev_usb001/BOMBERMAN/USRDIR/FONT/lowerCase/"
#define CHARWIDTH 80  //In PX - Width of character PNG
#define CHARHEIGHT 80 //In PX - Height of character PNG

PngDatas num0, num1, num2, num3, num4, num5, num6, num7, num8, num9, alphaA, alphaB, alphaC, alphaD, alphaE, alphaF, alphaG, alphaH, alphaI, alphaJ, alphaK, alphaL, alphaM, alphaN, alphaO, alphaP, alphaQ, alphaR, alphaS, alphaT, alphaU, alphaV, alphaW, alphaX, alphaY, alphaZ, alphaa, alphab, alphac, alphad, alphae, alphaf, alphag, alphah, alphai, alphaj, alphak, alphal, alpham, alphan, alphao, alphap, alphaq, alphar, alphas, alphat, alphau, alphav, alphaw, alphax, alphay, alphaz, ddot;

void init_pggl() {
	LoadPNG(&num0, NUMERALLOCATION"0.png");
	LoadPNG(&num1, NUMERALLOCATION"1.png");
	LoadPNG(&num2, NUMERALLOCATION"2.png");
	LoadPNG(&num3, NUMERALLOCATION"3.png");
	LoadPNG(&num4, NUMERALLOCATION"4.png");
	LoadPNG(&num5, NUMERALLOCATION"5.png");
	LoadPNG(&num6, NUMERALLOCATION"6.png");
	LoadPNG(&num7, NUMERALLOCATION"7.png");
	LoadPNG(&num8, NUMERALLOCATION"8.png");
	LoadPNG(&num9, NUMERALLOCATION"9.png");

	LoadPNG(&alphaA, UPPERCASELOCATION"a.png");
	LoadPNG(&alphaB, UPPERCASELOCATION"b.png");
	LoadPNG(&alphaC, UPPERCASELOCATION"c.png");
	LoadPNG(&alphaD, UPPERCASELOCATION"d.png");
	LoadPNG(&alphaE, UPPERCASELOCATION"e.png");
	LoadPNG(&alphaF, UPPERCASELOCATION"f.png");
	LoadPNG(&alphaG, UPPERCASELOCATION"g.png");
	LoadPNG(&alphaH, UPPERCASELOCATION"h.png");
	LoadPNG(&alphaI, UPPERCASELOCATION"i.png");
	LoadPNG(&alphaJ, UPPERCASELOCATION"j.png");
	LoadPNG(&alphaK, UPPERCASELOCATION"k.png");
	LoadPNG(&alphaL, UPPERCASELOCATION"l.png");
	LoadPNG(&alphaM, UPPERCASELOCATION"m.png");
	LoadPNG(&alphaN, UPPERCASELOCATION"n.png");
	LoadPNG(&alphaO, UPPERCASELOCATION"o.png");
	LoadPNG(&alphaP, UPPERCASELOCATION"p.png");
	LoadPNG(&alphaQ, UPPERCASELOCATION"q.png");
	LoadPNG(&alphaR, UPPERCASELOCATION"r.png");
	LoadPNG(&alphaS, UPPERCASELOCATION"s.png");
	LoadPNG(&alphaT, UPPERCASELOCATION"t.png");
	LoadPNG(&alphaU, UPPERCASELOCATION"u.png");
	LoadPNG(&alphaV, UPPERCASELOCATION"v.png");
	LoadPNG(&alphaW, UPPERCASELOCATION"w.png");
	LoadPNG(&alphaX, UPPERCASELOCATION"x.png");
	LoadPNG(&alphaY, UPPERCASELOCATION"y.png");
	LoadPNG(&alphaZ, UPPERCASELOCATION"z.png");

	LoadPNG(&alphaa, LOWERCASELOCATION"a.png");
	LoadPNG(&alphab, LOWERCASELOCATION"b.png");
	LoadPNG(&alphac, LOWERCASELOCATION"c.png");
	LoadPNG(&alphad, LOWERCASELOCATION"d.png");
	LoadPNG(&alphae, LOWERCASELOCATION"e.png");
	LoadPNG(&alphaf, LOWERCASELOCATION"f.png");
	LoadPNG(&alphag, LOWERCASELOCATION"g.png");
	LoadPNG(&alphah, LOWERCASELOCATION"h.png");
	LoadPNG(&alphai, LOWERCASELOCATION"i.png");
	LoadPNG(&alphaj, LOWERCASELOCATION"j.png");
	LoadPNG(&alphak, LOWERCASELOCATION"k.png");
	LoadPNG(&alphal, LOWERCASELOCATION"l.png");
	LoadPNG(&alpham, LOWERCASELOCATION"m.png");
	LoadPNG(&alphan, LOWERCASELOCATION"n.png");
	LoadPNG(&alphao, LOWERCASELOCATION"o.png");
	LoadPNG(&alphap, LOWERCASELOCATION"p.png");
	LoadPNG(&alphaq, LOWERCASELOCATION"q.png");
	LoadPNG(&alphar, LOWERCASELOCATION"r.png");
	LoadPNG(&alphas, LOWERCASELOCATION"s.png");
	LoadPNG(&alphat, LOWERCASELOCATION"t.png");
	LoadPNG(&alphau, LOWERCASELOCATION"u.png");
	LoadPNG(&alphav, LOWERCASELOCATION"v.png");
	LoadPNG(&alphaw, LOWERCASELOCATION"w.png");
	LoadPNG(&alphax, LOWERCASELOCATION"z.png");
	LoadPNG(&alphay, LOWERCASELOCATION"y.png");
	LoadPNG(&alphaz, LOWERCASELOCATION"z.png");
	LoadPNG(&ddot, LOWERCASELOCATION"ddot.png");
}

void draw(char input[], int posx, int posy) {
	int x, y;
	x = posx;
	y = posy;
	for(int i = 0; i < strlen(input); i++){
		x += CHARWIDTH;
		switch(input[i])
		{
			// Numbers
			case '0':
				drawPNG(num0, x, y);
	            break;
			case '1':
				drawPNG(num1, x, y);
				break;
			case '2':
				drawPNG(num2, x, y);
				break;
			case '3':
				drawPNG(num3, x, y);
				break;
			case '4':
				drawPNG(num4, x, y);
				break;
			case '5':
				drawPNG(num5, x, y);
				break;
			case '6':
				drawPNG(num6, x, y);
				break;
			case '7':
				drawPNG(num7, x, y);
				break;
			case '8':
				drawPNG(num8, x, y);
				break;
			case '9':
				drawPNG(num9, x, y);
				break;
			// Characters
			case 'A':
				drawPNG(alphaA, x, y);
				break;
			case 'a':
				drawPNG(alphaa, x, y);
				break;
			case 'B':
				drawPNG(alphaB, x, y);
				break;
			case 'b':
				drawPNG(alphab, x, y);
				break;
			case 'C':
				drawPNG(alphaC, x, y);
				break;
			case 'c':
				drawPNG(alphac, x, y);
				break;
			case 'D':
				drawPNG(alphaD, x, y);
				break;
			case 'd':
				drawPNG(alphad, x, y);
				break;
			case 'E':
				drawPNG(alphaE, x, y);
				break;
			case 'e':
				drawPNG(alphae, x, y);
				break;
			case 'F':
				drawPNG(alphaF, x, y);
				break;
			case 'f':
				drawPNG(alphaf, x, y);
				break;
			case 'G':
				drawPNG(alphaG, x, y);
				break;
			case 'g':
				drawPNG(alphag, x, y);
				break;
			case 'H':
				drawPNG(alphaH, x, y);
				break;
			case 'h':
				drawPNG(alphah, x, y);
				break;
			case 'I':
				drawPNG(alphaI, x, y);
				break;
			case 'i':
				drawPNG(alphai, x, y);
				break;
			case 'J':
				drawPNG(alphaJ, x, y);
				break;
			case 'j':
				drawPNG(alphaj, x, y);
				break;
			case 'K':
				drawPNG(alphaK, x, y);
				break;
			case 'k':
				drawPNG(alphak, x, y);
				break;
			case 'L':
				drawPNG(alphaL, x, y);
				break;
			case 'l':
				drawPNG(alphal, x, y);
				break;
			case 'M':
				drawPNG(alphaM, x, y);
				break;
			case 'm':
				drawPNG(alpham, x, y);
				break;
			case 'N':
				drawPNG(alphaN, x, y);
				break;
			case 'n':
				drawPNG(alphan, x, y);
				break;
			case 'O':
				drawPNG(alphaO, x, y);
				break;
			case 'o':
				drawPNG(alphao, x, y);
				break;
			case 'P':
				drawPNG(alphaP, x, y);
				break;
			case 'p':
				drawPNG(alphap, x, y);
				break;
			case 'Q':
				drawPNG(alphaQ, x, y);
				break;
			case 'q':
				drawPNG(alphaq, x, y);
				break;
			case 'R':
				drawPNG(alphaR, x, y);
				break;
			case 'r':
				drawPNG(alphar, x, y);
				break;
			case 'S':
				drawPNG(alphaS, x, y);
				break;
			case 's':
				drawPNG(alphas, x, y);
				break;
			case 'T':
				drawPNG(alphaT, x, y);
				break;
			case 't':
				drawPNG(alphat, x, y);
				break;
			case 'U':
				drawPNG(alphaU, x, y);
				break;
			case 'u':
				drawPNG(alphau, x, y);
				break;
			case 'V':
				drawPNG(alphaV, x, y);
				break;
			case 'v':
				drawPNG(alphav, x, y);
				break;
			case 'W':
				drawPNG(alphaW, x, y);
				break;
			case 'w':
				drawPNG(alphaw, x, y);
				break;
			case 'X':
				drawPNG(alphaX, x, y);
				break;
			case 'x':
				drawPNG(alphax, x, y);
				break;
			case 'Y':
				drawPNG(alphaY, x, y);
				break;
			case 'y':
				drawPNG(alphay, x, y);
				break;
			case 'Z':
				drawPNG(alphaZ, x, y);
				break;
			case 'z':
				drawPNG(alphaz, x, y);
				break;
			// Other
			case ':':
				drawPNG(ddot, x, y);
				break;
			case '\n':
				y += CHARHEIGHT;
				break;
			case ' ':
				x += CHARWIDTH;
				break;
		}
	}
}

void drawInt(int inumber, int posx, int posy) {
	char num[18]; //9999999999999999 = max int
	sprintf(num, "%i", inumber);
	int x = posx;
	for(int i = 0; i < strlen(num); i++){
		x += CHARWIDTH;
		switch(num[i])
		{
			case '0':
				drawPNG(num0, x, posy);
				break;
			case '1':
				drawPNG(num1, x, posy);
				break;
			case '2':
				drawPNG(num2, x, posy);
				break;
			case '3':
				drawPNG(num3, x, posy);
				break;
			case '4':
				drawPNG(num4, x, posy);
				break;
			case '5':
				drawPNG(num5, x, posy);
				break;
			case '6':
				drawPNG(num6, x, posy);
				break;
			case '7':
				drawPNG(num7, x, posy);
				break;
			case '8':
				drawPNG(num8, x, posy);
				break;
			case '9':
				drawPNG(num9, x, posy);
				break;
		}
	}
}

void drawButton(PngDatas buttonDown, PngDatas buttonUp, int state, int posx, int posy) {
   switch(state)
   {
      case(0):
          drawPNG(buttonUp, posx, posy);
          break;
      case(1):
          drawPNG(buttonDown, posx, posy);
          break;
   }
}
