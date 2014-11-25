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

char tower_name[6][32] = { "MINIGUN", "ANTIAIR", "ARTILER", "SLOWRAY",
		"SNIPER ", "PLANT  "

};
char speed_text[4][16] = { "FASTEST", "   FAST", " MEDIUM", "   SLOW" };
char onoff_text[2][8] = { "OFF", " ON" };
char menu_item[8][32] = { "   Return to Game   ", "   Game Speed       ",
		"   Sound Effects    ", "   Music Enabled    ", "   Screen Blending  ",
		"   Restart Game     ", "   Quit to Main Menu", "   Quit to OS       " };

char cmc[5][5] = { "SCAN", "BUY", "SELL", " MAP", "MENU" };

Sint32 dr[4] = { 160, 120, 160, 120 }; //Dark rect
Sint32 dr1[4] = { 160, 120, 160, 120 };

Uint8 drc[5] = { 0, 15, 15, 0, 0 };
Uint8 drc1[5] = { 255, 15, 0, 255, 15 };

Sint32 cm_dr[5][4] = { { 240, 50, 310, 120 }, { 230, 50, 310, 180 }, { 50, 46,
		210, 66 }, { 20, 40, 200, 200 }, { 10, 50, 309, 214 } };

Sint32 cm_dr1[5][4] = { { 244, 54, 306, 116 }, { 40, 190, 260, 210 }, { 60, 48,
		200, 64 }, { 30, 50, 190, 190 }, { 50, 70, 250, 202 } };

Uint8 mapcolor[20] = { 2, 1, 6, 11, 9, 14, 4, 0, 0, 12, 8, 7, 15, 15, 15, 15,
		15, 15, 15, 15 };

void RenderMap4(Sint16 x0, Sint16 y0, Sint16 x1, Sint16 y1) {
	Sint16 x, y, cx, cy, ix, iy, rx, ry;
	Uint8 c, i;

	cx = (x1 + x0) / 2;
	cy = (y1 + y0) / 2;

	Sint32 ii;

	for (y = y0; y < y1; y++) {
		ii = x0 + y * 320;
		for (x = x0; x < x1; x++) {
			c = 0;

			rx = ((x - cx + 4 * cursorx / 65536) / 4);
			ry = ((y - cy + 4 * cursory / 65536) / 4);
			if (rx >= 0)
				if (ry >= 0)
					if (rx < 64)
						if (ry < 64)
							if (mapunlock[rx / 8][ry / 8] <= wave) {
								c = mapcolor[map[rx][ry]];
							}

			scrbuf[ii] = c;
			ii++;
		}
	}
	for (i = 0; i < 128; i++)
		if (mob[i][0] > 0) {
			rx = cx + (mob[i][4] - cursorx) * 4 / 65536;
			ry = cy + (mob[i][5] - cursory) * 4 / 65536;
			if (rx > x0)
				if (ry > y0)
					if (rx < x1)
						if (ry < y1) {
							ii = rx + 320 * ry;
							c = mob[i][1];
							scrbuf[ii + 321] = c;
							scrbuf[ii + 320] = c;
							scrbuf[ii + 319] = c;
							scrbuf[ii + 1] = c;
							scrbuf[ii - 1] = c;
							scrbuf[ii - 321] = c;
							scrbuf[ii - 320] = c;
							scrbuf[ii - 319] = c;

						}
		}
}

void ProcMainMenu(void) {
	if (dpadi == 1) {
		if (dpad == 0)
			if (menuitem > 0) {
				PlaySound(0, 0);
				menuitem--;
				zl_vibro = 40;
			}

		if (dpad == 4)
			if (menuitem < 7) {
				PlaySound(0, 0);
				menuitem++;
				zl_vibro = 40;
			}
	}

	if (menuitem == 1)
		if (dpadi == 1) {
			PlaySound(0, 0);
			if (dpad == 2)
				gamespeed = (gamespeed + 1) % 4;
			else if (dpad == 6)
				if (gamespeed > 0)
					gamespeed--;
				else
					gamespeed = 3;
		}

	if ((vbutton[0] == 1) | (vbutton[2] == 1))
		switch (menuitem) {
		case 0: //return
			cursormode = 0;
			zl_vibro = 125;
			break;
		case 1: //gamespeed
			gamespeed = (gamespeed + 1) % 4;
			zl_vibro = 125;
			break;
		case 2: //Sound
			soundon = (soundon + 1) % 2;
			zl_vibro = 125;
			break;
		case 3: //music
			musicon = (musicon + 1) % 2;
			if (musicon == 0)
				PlayMusic(128);
			else if (wave)
				PlayMusic(1 + (wave / 10) % 2);

			zl_vibro = 125;
			break;
		case 4: //Shader
			screenblend = (screenblend + 1) % 2;
			zl_vibro = 125;
			break;

		case 5: //Shader
			PlayMusic(128);
			cursormode = 0;
			ResetMap();
			zl_vibro = 125;
			break;

		case 6:
			PlayMusic(0);
			NextGameMode = 4;
			zl_vibro = 125;
			break;
		case 7: //Shut Down
			NextGameMode = 6;
			zl_vibro = 125;
			break;

		}

}

void RenderGameGUI(void) {
	Sint32 i, x, y, ii;
	for (x = 0; x < 6400; x++) {
		scrbuf[x] = NextColor2[scrbuf[x]];
	}
	for (y = 20; y < 40; y++) {
		i = y * 320 + 190 + y;
		ii = y * 320 + 320;
		for (x = i; x < ii; x++)
			scrbuf[x] = NextColor2[scrbuf[x]];

	}

	for (y = 220; y < 240; y++) {
		i = y * 320 + 240 - y;
		ii = y * 320 + 300 + y - 220;
		for (x = i; x < ii; x++)
			scrbuf[x] = NextColor2[scrbuf[x]];

	}
	Uint8 GUIc = 14 + 16 * (dpadpower);

	ii = 20 * 320;
	for (x = 0; x < 210; x++) {
		scrbuf[ii - 640] = 0;
		scrbuf[ii] = 0;
		scrbuf[ii + 320] = GUIc;
		ii++;
	}
	for (x = 210; x < 230; x++) {
		scrbuf[ii - 640] = 0;
		scrbuf[ii] = 0;
		scrbuf[ii + 320] = GUIc;
		ii += 321;
	}
	for (x = 230; x < 320; x++) {
		scrbuf[ii - 640] = 0;
		scrbuf[ii] = 0;
		scrbuf[ii + 320] = GUIc;
		ii++;
	}

	ii = 239 * 320;
	for (x = 0; x < 20; x++) {
		scrbuf[ii] = 0;
		scrbuf[ii - 320] = GUIc;
		ii -= 319;
	}
	ii += 320;
	for (x = 20; x < 300; x++) {
		scrbuf[ii] = 0;
		scrbuf[ii - 320] = GUIc;
		ii++;
	}
	for (x = 300; x < 320; x++) {
		scrbuf[ii] = 0;
		scrbuf[ii - 320] = GUIc;
		ii += 321;
	}

//////
	for (x = 0; x < 20; x++) {
		ii = 240 + x;
		for (y = 0; y <= x; y++) {
			scrbuf[ii] = 0;
			ii += 320;
		}
	}
	for (y = 0; y < 20; y++) {
		ii = 260 + y * 320;
		for (x = 260; x < 320; x++)
			scrbuf[ii++] = 0;
	}

	for (x = 0; x < 5; x++) {
		l_textstring = sprintf(s_textstring, "%s", cmc[x]);
		if (cursormode == x)
			s_drawtext(10 + 40 * x, 2, 14);
		else
			s_drawtext(10 + 40 * x, 4, 8);
	}
	DrawRect(10 + 40 * cursormode, 2, 50 + 40 * cursormode, 18, 15);

	l_textstring = sprintf(s_textstring, "Funds");
	s_drawtext(310 - l_textstring * 8, 6, GUIc);
	l_textstring = sprintf(s_textstring, "%i", funds);
	s_drawtext(310 - l_textstring * 8, 22, 14);

	l_textstring = sprintf(s_textstring, "Wave %i", wave);
	s_drawtext(30, 222, GUIc - 1);

	if (wavedelay) {
		l_textstring = sprintf(s_textstring, "Next wave in %i",
				1 + wavedelay / 30);
		s_drawtext(16, 24, 15);

	}

	l_textstring = sprintf(s_textstring, "%i Lives", lives);
	s_drawtext(290 - l_textstring * 8, 222, GUIc - 10);

	for (x = 0; x < 4; x++) {
		dr[x] = dr[x] + (cm_dr[cursormode][x] - dr[x]) / 2;
		dr1[x] = dr1[x] + (cm_dr1[cursormode][x] - dr1[x]) / 2;

	}
	DarkRect(dr[0], dr[1], dr[2], dr[3]);
	DarkRect(dr1[0], dr1[1], dr1[2], dr1[3]);

	if (drc[cursormode] < 255)
		DrawRect(dr[0], dr[1], dr[2], dr[3], drc[cursormode]);
	if (drc1[cursormode] < 255)
		DrawRect(dr1[0], dr1[1], dr1[2], dr1[3], drc1[cursormode]);

	switch (cursormode) {
	case 0: //scan
		RenderMap4(dr1[0] + 2, dr1[1] + 2, dr1[2] - 2, dr1[3] - 2);

		break;
	case 1: //build
		for (i = 0; i < 6; i++)
			if (cursormodecount > 5 + i) {
				l_textstring = sprintf(s_textstring, "%s", tower_name[i]);
				if (i == towermenu)
					s_drawtext(dr[0] + 2, dr[1] + 18 + i * 16, 15);
				else
					s_drawtext(dr[0] + 2, dr[1] + 18 + i * 16, 8);
			}

		if (cost > 0) {
			l_textstring = sprintf(s_textstring, "%i GP", cost);
			s_drawtext(dr1[2] - 8 - l_textstring * 8, dr1[1] + 2, 14);

			if (cursorvisual == 2)
				l_textstring = sprintf(s_textstring, "Turret Mount", cost);
			else
				l_textstring = sprintf(s_textstring, "%s",
						tower_name[towermenu]);

			s_drawtext(dr1[0] + 8, dr1[1] + 2, 14);

		}

		if (vbutton[3] == 1)
			if (towermenu > 0) {
				towermenu--;
				PlaySound(0, 0);
				zl_vibro = 100;
			}

		if (vbutton[1] == 1)
			if (towermenu < 5) {
				towermenu++;
				PlaySound(0, 0);
				zl_vibro = 100;
			}

		if (cursorvisual == 3) {

			DrawRect(dr[0] + 2, dr[1] + 18 + towermenu * 16, dr[2] - 2,
					dr[1] + 34 + towermenu * 16, 14);

			if (towermenu > 0) {
				l_textstring = sprintf(s_textstring, "Y");
				s_drawtext(dr[2] - 16, dr[1] + 2, 14);
			}
			if (towermenu < 5) {
				l_textstring = sprintf(s_textstring, "B");
				s_drawtext(dr[2] - 16, dr[3] - 18, 14);
			}
		}

		break;
	case 2: //sell
		if (cost) {
			l_textstring = sprintf(s_textstring, "SELL FOR");
			s_drawtext(dr1[0] + 8, dr1[1] + 2, 14);

			l_textstring = sprintf(s_textstring, "%i GP", cost);
			s_drawtext(dr1[2] - 8 - l_textstring * 8, dr1[1] + 2, 14);
		} else if (count / 10 % 2) {
			l_textstring = sprintf(s_textstring, "Incorrect Object");
			s_drawtext(dr1[0] + 8, dr1[1] + 2, 4);
		}

		break;
	case 3: //map
		RenderMap4(dr1[0] + 4, dr1[1] + 4, dr1[2] - 4, dr1[3] - 4);
		x = (dr1[0] + dr1[2]) / 2;
		y = (dr1[1] + dr1[3]) / 2;

		DrawRect(x - 20, y - 15, x + 20, y + 15, 15);
		break;
	case 4: //Menu
		for (i = 0; i < 8; i++)
			if (cursormodecount > 5 + i) {
				l_textstring = sprintf(s_textstring, "%s", menu_item[i]);
				if (i == menuitem)
					s_drawtext(dr1[0] + 2, dr1[1] + 2 + i * 16, 15);
				else
					s_drawtext(dr1[0] + 2, dr1[1] + 2 + i * 16, 8);

			}
		if (cursormodecount > 15) {
			DrawRect(dr1[0] + 2, dr1[1] + 2 + menuitem * 16, dr1[2] - 2,
					dr1[1] + 18 + menuitem * 16, 14);

			l_textstring = sprintf(s_textstring, "%s", speed_text[gamespeed]);
			s_drawtext(dr1[1] + 110, dr1[1] + 18, 9);

			l_textstring = sprintf(s_textstring, "%s", onoff_text[soundon]);
			s_drawtext(dr1[1] + 140, dr1[1] + 34, 9);

			l_textstring = sprintf(s_textstring, "%s", onoff_text[musicon]);
			s_drawtext(dr1[1] + 140, dr1[1] + 50, 9);

			l_textstring = sprintf(s_textstring, "%s", onoff_text[screenblend]);
			s_drawtext(dr1[1] + 140, dr1[1] + 66, 9);

		}
		ProcMainMenu();

		break;

	}

}
