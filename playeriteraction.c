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

#include "vlines.h"
#include "waveai.h"

Uint16 tower_cost[6] = { 20, 30, 40, 50, 250, 50 };

Uint16 sell_cost[7] = { 5, 16, 24, 32, 40, 200, 25 };

Sint32 cm_cam[5][6] = { { 0, 585536, -200000, -812, 0, 0 }, //scan
		{ 0, 385536, -220000, -612, 0, 0 }, //buy
		{ 0, 345536, -250000, -512, 0, 0 }, //sell
		{ -30000, 485536, 10000, -1024, 0, 200 }, //map
		{ -200000, 285536, -400000, -412, 400, 0 } //menu

};
Sint32 cm_speed[5] = { 10000, 8000, 8000, 20000, 0 };
Uint8 lastcursormode;

Sint8 cx, cy; //global

void RaiseLand(Sint8 x, Sint8 y) {
	if (x >= 0)
		if (x < 64)
			if (y >= 0)
				if (y < 64) {
					if (map[x][y] == 1)
						map[x][y] = 2;
					if (map[x][y] == 4)
						map[x][y] = 3;
					if (map[x][y] == 6)
						map[x][y] = 5;

				}

}

void PlayerAction(void) {
	cost = 0;
	Sint32 ccx, ccy;
	if (cursorvisual == 2) { //cultivate
		if (map[cx][cy] == 0)
			cost = 10;
		else if (map[cx][cy] == 1)
			cost = 50;
		else if (map[cx][cy] == 2)
			cost = 15;
		else if (map[cx][cy] == 3)
			cost = 30;
		else if (map[cx][cy] == 4)
			cost = 50;
		else if (map[cx][cy] == 5)
			cost = 40;
		else if (map[cx][cy] == 6)
			cost = 50;

		if ((vbutton[0] == 1) | (vbutton[2] == 1))
			if (funds >= cost) {
				funds -= cost;
				map[cx][cy] = 11;
				mapz[cx][cy] = 0;
				mapz[cx + 1][cy] = 0;
				mapz[cx + 1][cy + 1] = 0;
				mapz[cx][cy + 1] = 0;
				RaiseLand(cx - 1, cy - 1);
				RaiseLand(cx, cy - 1);
				RaiseLand(cx + 1, cy - 1);
				RaiseLand(cx + 1, cy);

				RaiseLand(cx + 1, cy + 1);
				RaiseLand(cx, cy + 1);
				RaiseLand(cx - 1, cy + 1);
				RaiseLand(cx - 1, cy);

				ccx = cx * 65536 + 32768;
				ccy = cy * 65536 + 32768;

				newvline[0] = 20;
				newvline[1] = 14;
				newvline[2] = ccx - 32768;
				newvline[3] = 1000;
				newvline[4] = ccy - 32768;
				newvline[5] = ccx + 32768;
				newvline[6] = 1000;
				newvline[7] = ccy - 32768;
				newvline[8] = -8000;
				newvline[9] = 2000;
				newvline[10] = -8000;
				newvline[11] = 8000;
				newvline[12] = 2000;
				newvline[13] = -8000;
				SpawnLine();

				newvline[0] = 20;
				newvline[1] = 14;
				newvline[2] = ccx - 32768;
				newvline[3] = 1000;
				newvline[4] = ccy + 32768;
				newvline[5] = ccx + 32768;
				newvline[6] = 1000;
				newvline[7] = ccy + 32768;
				newvline[8] = -8000;
				newvline[9] = 2000;
				newvline[10] = 8000;
				newvline[11] = 8000;
				newvline[12] = 2000;
				newvline[13] = 8000;
				SpawnLine();

				newvline[0] = 20;
				newvline[1] = 14;
				newvline[2] = ccx - 32768;
				newvline[3] = 1000;
				newvline[4] = ccy + 32768;
				newvline[5] = ccx - 32768;
				newvline[6] = 1000;
				newvline[7] = ccy - 32768;
				newvline[8] = -8000;
				newvline[9] = 2000;
				newvline[10] = 8000;
				newvline[11] = -8000;
				newvline[12] = 2000;
				newvline[13] = -8000;
				SpawnLine();

				newvline[0] = 20;
				newvline[1] = 14;
				newvline[2] = ccx + 32768;
				newvline[3] = 1000;
				newvline[4] = ccy + 32768;
				newvline[5] = ccx + 32768;
				newvline[6] = 1000;
				newvline[7] = ccy - 32768;
				newvline[8] = 8000;
				newvline[9] = 2000;
				newvline[10] = 8000;
				newvline[11] = 8000;
				newvline[12] = 2000;
				newvline[13] = -8000;
				SpawnLine();
				PlaySound(2, 0);
				zl_vibro = 126;

			}
	} else if (cursorvisual == 3) {
		cost = tower_cost[towermenu];
		if ((vbutton[0] == 1) | (vbutton[2] == 1))
			if (funds >= cost) {
				funds -= cost;
				map[cx][cy] = 12 + towermenu;

				ccx = cx * 65536 + 32768;
				ccy = cy * 65536 + 32768;

				newvline[0] = 20;
				newvline[1] = 15;
				newvline[2] = ccx - 32768;
				newvline[3] = 1000;
				newvline[4] = ccy - 32768;
				newvline[5] = ccx + 32768;
				newvline[6] = 1000;
				newvline[7] = ccy - 32768;
				newvline[8] = -8000;
				newvline[9] = 2000;
				newvline[10] = -8000;
				newvline[11] = 8000;
				newvline[12] = 2000;
				newvline[13] = -8000;
				SpawnLine();

				newvline[0] = 20;
				newvline[1] = 15;
				newvline[2] = ccx - 32768;
				newvline[3] = 1000;
				newvline[4] = ccy + 32768;
				newvline[5] = ccx + 32768;
				newvline[6] = 1000;
				newvline[7] = ccy + 32768;
				newvline[8] = -8000;
				newvline[9] = 2000;
				newvline[10] = 8000;
				newvline[11] = 8000;
				newvline[12] = 2000;
				newvline[13] = 8000;
				SpawnLine();

				newvline[0] = 20;
				newvline[1] = 15;
				newvline[2] = ccx - 32768;
				newvline[3] = 1000;
				newvline[4] = ccy + 32768;
				newvline[5] = ccx - 32768;
				newvline[6] = 1000;
				newvline[7] = ccy - 32768;
				newvline[8] = -8000;
				newvline[9] = 2000;
				newvline[10] = 8000;
				newvline[11] = -8000;
				newvline[12] = 2000;
				newvline[13] = -8000;
				SpawnLine();

				newvline[0] = 20;
				newvline[1] = 15;
				newvline[2] = ccx + 32768;
				newvline[3] = 1000;
				newvline[4] = ccy + 32768;
				newvline[5] = ccx + 32768;
				newvline[6] = 1000;
				newvline[7] = ccy - 32768;
				newvline[8] = 8000;
				newvline[9] = 2000;
				newvline[10] = 8000;
				newvline[11] = 8000;
				newvline[12] = 2000;
				newvline[13] = -8000;
				SpawnLine();
				PlaySound(2, 0);
				zl_vibro = 126;

			}
	}

	if (cursorvisual == 4) {
		cost = sell_cost[map[cx][cy] - 11];

		if ((vbutton[0] == 1) | (vbutton[2] == 1)) {
			PlaySound(1, 0);
			funds += cost;
			if (map[cx][cy] == 11)
				map[cx][cy] = 2;
			else
				map[cx][cy] = 11;

			ccx = cx * 65536 + 32768;
			ccy = cy * 65536 + 32768;

			newvline[0] = 20;
			newvline[1] = 4;
			newvline[2] = ccx - 32768;
			newvline[3] = 1000;
			newvline[4] = ccy - 32768;
			newvline[5] = ccx + 32768;
			newvline[6] = 1000;
			newvline[7] = ccy - 32768;
			newvline[8] = -8000;
			newvline[9] = 2000;
			newvline[10] = -8000;
			newvline[11] = 8000;
			newvline[12] = 2000;
			newvline[13] = -8000;
			SpawnLine();

			newvline[0] = 20;
			newvline[1] = 4;
			newvline[2] = ccx - 32768;
			newvline[3] = 1000;
			newvline[4] = ccy + 32768;
			newvline[5] = ccx + 32768;
			newvline[6] = 1000;
			newvline[7] = ccy + 32768;
			newvline[8] = -8000;
			newvline[9] = 2000;
			newvline[10] = 8000;
			newvline[11] = 8000;
			newvline[12] = 2000;
			newvline[13] = 8000;
			SpawnLine();

			newvline[0] = 20;
			newvline[1] = 4;
			newvline[2] = ccx - 32768;
			newvline[3] = 1000;
			newvline[4] = ccy + 32768;
			newvline[5] = ccx - 32768;
			newvline[6] = 1000;
			newvline[7] = ccy - 32768;
			newvline[8] = -8000;
			newvline[9] = 2000;
			newvline[10] = 8000;
			newvline[11] = -8000;
			newvline[12] = 2000;
			newvline[13] = -8000;
			SpawnLine();

			newvline[0] = 20;
			newvline[1] = 4;
			newvline[2] = ccx + 32768;
			newvline[3] = 1000;
			newvline[4] = ccy + 32768;
			newvline[5] = ccx + 32768;
			newvline[6] = 1000;
			newvline[7] = ccy - 32768;
			newvline[8] = 8000;
			newvline[9] = 2000;
			newvline[10] = 8000;
			newvline[11] = 8000;
			newvline[12] = 2000;
			newvline[13] = -8000;
			SpawnLine();
			zl_vibro = 126;

		}
	}

}

void PlayerIteraction(void) {
	Sint32 i;
	camera[0] = cursorx + cm_cam[cursormode][0];
	camera[2] = -cursory + cm_cam[cursormode][2];
	camera[1] = +cm_cam[cursormode][1];

	camera[3] = +cm_cam[cursormode][3];
	camera[4] = +cm_cam[cursormode][4];
	camera[5] = +cm_cam[cursormode][5];

	camera[5] += 2 * zl_gsensor[3];
//camera[4]+=2*zl_gsensor[5];
	camera[3] += 2 * zl_gsensor[4];

	Sint32 icx = 0, icy = 0, cspeed = cm_speed[cursormode];

	if (dpad > -1) {
		if (cursormode < 4)
			if (dpadpower < 15)
				dpadpower++;
	} else if (dpadpower > 0)
		dpadpower--;

	if ((dpad > 0) & (dpad < 4))
		icx += cspeed;
	if ((dpad > 4) & (dpad < 8))
		icx -= cspeed;

	if ((dpad == 0) | (dpad == 1) | (dpad == 7))
		icy -= cspeed;
	if ((dpad > 2) & (dpad < 6))
		icy += cspeed;

	if (cursormode < 3) {
		camera[4] += icx / 250;
		camera[3] += icy / 250;

	}

	lastcursormode = cursormode;
	if (vbutton[5] == 1) {
		PlaySound(0, 0);
		cursormode = (cursormode + 1) % 5;
		zl_vibro = 100;
	}
	if (vbutton[4] == 1)
		if (cursormode > 0) {
			PlaySound(0, 0);
			cursormode--;
			zl_vibro = 100;
		} else {
			cursormode = 4;
			PlaySound(0, 0);
		}
	if (vbutton[8] == 1) {
		PlaySound(0, 0);
		cursormode = 4;
		lastcursormode = 0;
	} //Debug exit

	if (lastcursormode != cursormode) {
		for (i = 0; i < 76800; i++)
			scrbuf[i] = 15;
		cursormodecount = 0;
	} else
		cursormodecount++;
	if (cursorx + icx > 0)
		if (cursorx + icx < 64 * 65536)
			if (mapunlock[(cursorx + icx) / (65536 * 8)][cursory / (8 * 65536)]
					<= wave)
				cursorx += icx;

	if (cursory + icy > 0)
		if (cursory + icy < 64 * 65536)
			if (mapunlock[(cursorx) / (65536 * 8)][(cursory + icy) / (8 * 65536)]
					<= wave)
				cursory += icy;

	cx = cursorx >> 16;
	cy = cursory >> 16;

	cursorvisual = 0;

	if (cursormode == 1) {
		cursorvisual = 1;
		if (map[cx][cy] < 9)
			cursorvisual = 2;
		else if (map[cx][cy] == 11)
			cursorvisual = 3;
	} else if (cursormode == 2) {
		cursorvisual = 1;
		if (map[cx][cy] > 10)
			if (map[cx][cy] < 20)
				cursorvisual = 4;

	}

	PlayerAction();

//if (vbutton[9]==1) NewWave();

	ProcAi();
}
