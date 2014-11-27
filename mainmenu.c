/*
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "vars.h"
#include "sblit.h"
//#include "ssystem.h"

char mmtt[6][32] = {
		"BEGIN NEW GAME  ",
		"  o/  ---   \\o  ",
		" /O   -  -   O> ",
		" / >  ----  / \\ ",
		"GAME SPEED      ",
		"EXIT TO SHELL   " };

Uint8 mmitem = 0;

Uint8 cbrd[32] = { 20, 30, 32, 15, 15, 45, 14, 14, 25, 90, 90, 95, 60, 34, 24,
		24, 77, 77, 54, 54, 23, 18, 18, 40, 20, 30, 60, 75, 25, 30, 32, 20 };

Uint8 cbrd1[32] = { 14, 8, 2, 9, 40, 56, 56, 20, 33, 38, 38, 20, 22, 15, 50, 16,
		45, 120, 120, 66, 44, 48, 23, 30, 14, 30, 30, 35, 40, 40, 25, 14

};

Sint8 olddpad2 = -1;

void ProcGameMainMenu(void) {
	Sint32 x, y, i, xx, yy, k, l;

	for (i = 1; i < 16; i++) {
		x = 1;
		y = 20 + (count + i * 15) % 210;
		xx = 318;
		yy = 10 + (count * 3 + i * 11) % 200;
		DrawLine2(x, y, xx, yy, 7);
	}

	i = count % 1024;

	y = cbrd[0];
	k = count;
	l = 40 * f_sin[(count * 10) % 2096] / 65536;
	for (x = 0; x < 320; x++) {
		i = (((x + k) / 20) + 1) % 32;
		if (y < cbrd[i] + l)
			y++;
		else if (y > cbrd[i] + l)
			y--;

		xx = y * 320 + x;
		for (yy = y; yy > 0; yy--) {
			scrbuf[xx] = 14;
			scrbuf[76799 - xx] = 8;
			xx -= 320;
		}
	}

	y = cbrd1[0];
	k = count * 2;
	for (x = 0; x < 320; x++) {
		i = (((x + k) / 20) + 1) % 32;
		if (y < cbrd1[i])
			y++;
		else if (y > cbrd1[i])
			y--;

		xx = y * 320 + x;
		for (yy = y; yy > 0; yy--) {
			scrbuf[xx] = 0;
			scrbuf[76799 - xx] = 0;
			xx -= 320;
		}
	}
	Uint8 c;
	if ((count / 16) % 2 == 0)
		c = count / 4 % 4;
	else
		c = 4 - count / 4 % 4;

	DarkRect(160 - c, 100 - c, 310 + c, 200 + c);
	DarkRect(0, 0, 320, 30);
	DarkRect(0, 220, 320, 239);

	DrawRect(160 - c, 100 - c, 310 + c, 200 + c, 15);
	DrawRect(0, 0, 320, 30, 15);
	DrawRect(0, 220, 320, 239, 15);

//l_textstring=sprintf(s_textstring,"CAANOO version  26-nov-2010");
#if defined(GCW)
	l_textstring = sprintf(s_textstring, "GCW Zero version "__BUILDDATE);
#else
	l_textstring = sprintf(s_textstring, "Linux version    "__BUILDDATE);
#endif
	s_drawtext(32, 222, 15);

	l_textstring = sprintf(s_textstring, "WORSHIP VECTOR       by Quasist");
	s_drawtext(32, 6, 15);

	DarkRect(0, 104 + mmitem * 16, 319, 120 + mmitem * 16);

	for (i = 0; i < 6; i++) {
		l_textstring = sprintf(s_textstring, "%s", mmtt[i]);
		s_drawtext(170, 104 + i * 16, 15);
	}

	switch (gamespeed) {
	case 0:
		l_textstring = sprintf(s_textstring, "++++");
		break;
	case 1:
		l_textstring = sprintf(s_textstring, "+++.");
		break;
	case 2:
		l_textstring = sprintf(s_textstring, "++..");
		break;
	case 3:
		l_textstring = sprintf(s_textstring, "+...");
		break;
	}

	s_drawtext(258, 168, 14);

	DrawRect(162 - c, 104 + mmitem * 16, 308 + c, 120 + mmitem * 16, 14);

	dpadi = 0;
	if (olddpad2 != dpad) {
		if (dpad >= 0) {
			dpadi = 1;
		}
	} else {
		dpadi = 2;
	}
	olddpad2 = dpad;

	if (dpadi == 1) {
		if ((dpad == 4)) {
			mmitem = (mmitem + 1) % 6;
			PlaySound(0, 0);
			zl_vibro = 64;
		} else {
			if ((dpad == 0)) {
				if (mmitem) {
					mmitem = (mmitem - 1);
				} else {
					mmitem = 5;
				}

				PlaySound(0, 0);
				zl_vibro = 64;
			}
		}
	}

	if ((vbutton[0] == 1) | (vbutton[2] == 1) | (vbutton[8] == 1))
		switch (mmitem) {
		case 0:
			NextGameMode = 5;
			ResetMap();
			cursormode = 0;
			break;
		case 4:
			gamespeed = (gamespeed + 1) % 4;
			break;
		case 5:
			NextGameMode = 6;
			break;

		}
	/*
	 for (i=0;i<6;i++)
	 {
	 l_textstring=sprintf(s_textstring,"%i",zl_gsensor[i]);
	 s_drawtext(311-8*l_textstring,11+15*i,0);
	 s_drawtext(310-8*l_textstring,10+15*i,15);
	 }
	 */
}
