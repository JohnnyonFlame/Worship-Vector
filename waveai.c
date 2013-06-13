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
#include "mobs.h"

void NewWave(void) {
	PlaySound(3, 0);
	wavedelay = 0;
	if (wave % 10 == 0)
		PlayMusic(1 + (wave / 10) % 2);
	wave++;

	wavemobleft = iwavedata[wave][0];
	mobdelay = iwavedata[wave][7];

	Uint8 x, y, n, i;

	for (y = 0; y < 64; y++)
		for (x = 0; x < 64; x++)
			if (map[x][y] == 17)
				funds += 5;

	for (y = 0; y < 32; y++)
		for (x = 0; x < 32; x++)
			if (mapunlock[x / 4][y / 4] > wave)
				aimap[x][y] = 9999;
			else if (map[x * 2][y * 2] == 9) {
				aimap[x][y] = 0;
				spawnx = x;
				spawny = y;
			} else if (map[x * 2][y * 2] == 10)
				aimap[x][y] = 2254;
			else
				aimap[x][y] = 9999;
	n = 0;
	i = 1;

	while (i > 0) {
		i = 0;
		for (y = 1; y < 31; y++)
			for (x = 1; x < 31; x++)
				if (aimap[x][y] == n) {
					if (aimap[x - 1][y] == 2254) {
						dirmap[x - 1][y] = 1;
						aimap[x - 1][y] = n + 1;
						spawnx = x - 1;
						spawny = y;
						i++;
					}
					if (aimap[x + 1][y] == 2254) {
						dirmap[x + 1][y] = 3;
						aimap[x + 1][y] = n + 1;
						spawnx = x + 1;
						spawny = y;
						i++;
					}
					if (aimap[x][y - 1] == 2254) {
						dirmap[x][y - 1] = 2;
						aimap[x][y - 1] = n + 1;
						spawnx = x;
						spawny = y - 1;
						i++;
					}
					if (aimap[x][y + 1] == 2254) {
						dirmap[x][y + 1] = 0;
						aimap[x][y + 1] = n + 1;
						spawnx = x;
						spawny = y + 1;
						i++;
					}
				}
		n = n + 1;
	}

	spawnx = (2 * spawnx + 1) * 65536;
	spawny = (2 * spawny + 1) * 65536;

//cursorx=spawnx;cursory=spawny;

}

void TrySpawn(void) {
	Sint32 ccx = spawnx, ccy = spawny;

	if (wavemobleft)
		if (mobdelay) {
			mobdelay--;
		} else {
			wavemobleft--;
			mobdelay = iwavedata[wave][7];
			newvline[0] = 20;
			newvline[1] = 4;
			newvline[2] = ccx - 32768;
			newvline[3] = 1000;
			newvline[4] = ccy;
			newvline[5] = ccx;
			newvline[6] = 1000;
			newvline[7] = ccy + 32768;
			newvline[8] = -8000;
			newvline[9] = 2000;
			newvline[10] = 000;
			newvline[11] = 000;
			newvline[12] = 2000;
			newvline[13] = 8000;
			SpawnLine();

			newvline[0] = 20;
			newvline[1] = 4;
			newvline[2] = ccx + 32768;
			newvline[3] = 1000;
			newvline[4] = ccy;
			newvline[5] = ccx;
			newvline[6] = 1000;
			newvline[7] = ccy + 32768;
			newvline[8] = +8000;
			newvline[9] = 2000;
			newvline[10] = 000;
			newvline[11] = 000;
			newvline[12] = 2000;
			newvline[13] = 8000;
			SpawnLine();

			newvline[0] = 20;
			newvline[1] = 4;
			newvline[2] = ccx - 32768;
			newvline[3] = 1000;
			newvline[4] = ccy;
			newvline[5] = ccx;
			newvline[6] = 1000;
			newvline[7] = ccy - 32768;
			newvline[8] = -8000;
			newvline[9] = 2000;
			newvline[10] = 000;
			newvline[11] = 000;
			newvline[12] = 2000;
			newvline[13] = -8000;
			SpawnLine();

			newvline[0] = 20;
			newvline[1] = 4;
			newvline[2] = ccx + 32768;
			newvline[3] = 1000;
			newvline[4] = ccy;
			newvline[5] = ccx;
			newvline[6] = 1000;
			newvline[7] = ccy - 32768;
			newvline[8] = +8000;
			newvline[9] = 2000;
			newvline[10] = 000;
			newvline[11] = 000;
			newvline[12] = 2000;
			newvline[13] = -8000;
			SpawnLine();

			SpawnMob();
		}
}

Uint8 rangetower[5] = { 3, 4, 4, 4, 5 };
void MobAi(void) {
	Uint8 i, c, slowed;
	Sint32 aix, aiy, cx, cy, speed, de, x0, y0, x1, y1, ii, x, y, tx, ty, rx,
			ry, r, damage;

	for (i = 0; i < 128; i++)
		if (mob[i][0] > 0) {
			aix = mob[i][4] / 65536 / 2;
			aiy = mob[i][5] / 65536 / 2;
			cx = mob[i][4] / 65536;
			cy = mob[i][5] / 65536;

			if (aimap[aix][aiy] == 0) { //BASE DAMAGE
				mob[i][0] = 0;
				for (ii = 0; ii < 76800; ii++)
					scrbuf[ii] = 4;
				zl_vibro = 125;

				PlaySound(1, 0);
				lives--;
				if (lives == 0) {
					PlayMusic(0);
					NextGameMode = 4;
				}
			}

			de = (dirmap[aix][aiy] * 1024 - mob[i][7]);
			if (de > 2048)
				de = -4096 + de;
			else if (de < -2048)
				de = 4096 + de;
			mob[i][7] += de / 8;

			speed = mob[i][3];
			slowed = 0;
			damage = 0;
//TOOOOOOOOOOWERZ
			x0 = cx - 5;
			x1 = cx + 5;
			y0 = cy - 5;
			y1 = cy + 5;
			if (x0 < 0)
				x0 = 0;
			if (x1 > 63)
				x1 = 63;
			if (y0 < 0)
				y0 = 0;
			if (y1 > 63)
				y1 = 63;

			for (y = y0; y < y1; y++)
				for (x = x0; x < x1; x++) {
					c = map[x][y];

					if (c > 11)
						if (c < 17) {
							c = c - 12;
							rx = zabs(x - cx);
							ry = zabs(y - cy);
							if (rx > ry)
								r = rx;
							else
								r = ry;

							if (r < rangetower[c])
								switch (c) {
								case 0: //minigun
									if (count - turret0[x][y] > 10) {
										turret0[x][y] = count;
										tx = x * 65536 + 32768;
										ty = y * 65536 + 32768;

										rx = mob[i][4] - tx;
										ry = mob[i][5] - ty;

										newvline[0] = 4;
										newvline[1] = 14;
										newvline[2] = mob[i][4];
										newvline[3] = mob[i][6];
										newvline[4] = mob[i][5];
										newvline[5] = tx;
										newvline[6] = 30000;
										newvline[7] = ty;
										newvline[8] = 0;
										newvline[9] = 0;
										newvline[10] = 0;
										newvline[11] = rx / 7;
										newvline[12] = 0;
										newvline[13] = ry / 7;
										SpawnLine();
										damage += 1;
									}
									break;
								case 1: //antiair
									if (count - turret0[x][y] > 20)
										if (mob[i][6] > 5000) {
											turret0[x][y] = count;
											tx = x * 65536 + 32768;
											ty = y * 65536 + 32768;

											rx = mob[i][4] - tx;
											ry = mob[i][5] - ty;

											newvline[0] = 4;
											newvline[1] = 14;
											newvline[2] = mob[i][4];
											newvline[3] = mob[i][6];
											newvline[4] = mob[i][5];
											newvline[5] = tx;
											newvline[6] = 30000;
											newvline[7] = ty;
											newvline[8] = rx / 6;
											newvline[9] = 0;
											newvline[10] = ry / 6;
											newvline[11] = rx / 7;
											newvline[12] = 0;
											newvline[13] = ry / 7;
											SpawnLine();
											damage += 5;
										}
									break;
								case 2: //altilery
									if (count - turret0[x][y] > 50)
										if (mob[i][6] < 5000) {
											turret0[x][y] = count;
											tx = x * 65536 + 32768;
											ty = y * 65536 + 32768;

											rx = mob[i][4] - tx;
											ry = mob[i][5] - ty;

											newvline[0] = 4;
											newvline[1] = 14;
											newvline[2] = mob[i][4];
											newvline[3] = mob[i][6];
											newvline[4] = mob[i][5];
											newvline[5] = tx;
											newvline[6] = 30000;
											newvline[7] = ty;
											newvline[8] = 0;
											newvline[9] = 0;
											newvline[10] = 0;
											newvline[11] = rx / 7;
											newvline[12] = 0;
											newvline[13] = ry / 7;
											SpawnLine();

											newvline[0] = 5;
											newvline[1] = 14;
											newvline[2] = mob[i][4] - 10000;
											newvline[3] = mob[i][6];
											newvline[4] = mob[i][5];
											newvline[5] = mob[i][4];
											newvline[6] = mob[i][6];
											newvline[7] = mob[i][5] - 10000;
											newvline[8] = -20000;
											newvline[9] = 0;
											newvline[10] = 0;
											newvline[11] = 0;
											newvline[12] = 4000;
											newvline[13] = -10000;
											SpawnLine();

											newvline[0] = 5;
											newvline[1] = 14;
											newvline[2] = mob[i][4] + 10000;
											newvline[3] = mob[i][6];
											newvline[4] = mob[i][5];
											newvline[5] = mob[i][4];
											newvline[6] = mob[i][6];
											newvline[7] = mob[i][5] - 10000;
											newvline[8] = 20000;
											newvline[9] = 0;
											newvline[10] = 0;
											newvline[11] = 0;
											newvline[12] = 4000;
											newvline[13] = -10000;
											SpawnLine();

											newvline[0] = 5;
											newvline[1] = 14;
											newvline[2] = mob[i][4] - 10000;
											newvline[3] = mob[i][6];
											newvline[4] = mob[i][5];
											newvline[5] = mob[i][4];
											newvline[6] = mob[i][6];
											newvline[7] = mob[i][5] + 10000;
											newvline[8] = -20000;
											newvline[9] = 0;
											newvline[10] = 0;
											newvline[11] = 0;
											newvline[12] = 4000;
											newvline[13] = 10000;
											SpawnLine();

											newvline[0] = 5;
											newvline[1] = 14;
											newvline[2] = mob[i][4] + 10000;
											newvline[3] = mob[i][6];
											newvline[4] = mob[i][5];
											newvline[5] = mob[i][4];
											newvline[6] = mob[i][6];
											newvline[7] = mob[i][5] + 10000;
											newvline[8] = 20000;
											newvline[9] = 0;
											newvline[10] = 0;
											newvline[11] = 0;
											newvline[12] = 4000;
											newvline[13] = 10000;
											SpawnLine();

											damage += 10;
										}
									break;
								case 3: //slow
									tx = x * 65536 + 32768;
									ty = y * 65536 + 32768;

									newvline[0] = 1;
									newvline[1] = 5;
									newvline[2] = mob[i][4];
									newvline[3] = mob[i][6];
									newvline[4] = mob[i][5];
									newvline[5] = tx;
									newvline[6] = 30000;
									newvline[7] = ty;
									newvline[8] = 0;
									newvline[9] = 0;
									newvline[10] = 0;
									newvline[11] = 0;
									newvline[12] = 0;
									newvline[13] = 0;
									SpawnLine();
									slowed = 1;
									break;
								case 4: //sniper
									if (count - turret0[x][y] > 80) {
										turret0[x][y] = count;
										tx = x * 65536 + 32768;
										ty = y * 65536 + 32768;

										rx = mob[i][4] - tx;
										ry = mob[i][5] - ty;

										newvline[0] = 4;
										newvline[1] = 15;
										newvline[2] = mob[i][4];
										newvline[3] = mob[i][6];
										newvline[4] = mob[i][5];
										newvline[5] = tx;
										newvline[6] = 80000;
										newvline[7] = ty;
										newvline[8] = 0;
										newvline[9] = 0;
										newvline[10] = 0;
										newvline[11] = rx / 7;
										newvline[12] = 0;
										newvline[13] = ry / 7;
										SpawnLine();
										damage += 30;
									}
									break;

								} //switch

						}

				}

			if (damage) {
				mob[i][10] = 1;

				mob[i][0] -= damage;
				if (mob[i][0] <= 0) {
					mob[i][0] = 0;
					funds += iwavedata[wave][5];
//DIEEEEEEEEEE
					zl_vibro = 125;

					newvline[0] = 20;
					newvline[1] = mob[i][1];
					newvline[2] = mob[i][4] - 32768;
					newvline[3] = mob[i][6];
					newvline[4] = mob[i][5];
					newvline[5] = mob[i][4];
					newvline[6] = mob[i][6];
					newvline[7] = mob[i][5] + 32768;
					newvline[8] = -8000;
					newvline[9] = 2000;
					newvline[10] = 000;
					newvline[11] = 000;
					newvline[12] = 2000;
					newvline[13] = 8000;
					SpawnLine();

					newvline[0] = 20;
					newvline[1] = mob[i][1];
					newvline[2] = mob[i][4] + 32768;
					newvline[3] = mob[i][6];
					newvline[4] = mob[i][5];
					newvline[5] = mob[i][4];
					newvline[6] = mob[i][6];
					newvline[7] = mob[i][5] + 32768;
					newvline[8] = +8000;
					newvline[9] = 2000;
					newvline[10] = 000;
					newvline[11] = 000;
					newvline[12] = 2000;
					newvline[13] = 8000;
					SpawnLine();

					newvline[0] = 20;
					newvline[1] = mob[i][1];
					newvline[2] = mob[i][4] - 32768;
					newvline[3] = mob[i][6];
					newvline[4] = mob[i][5];
					newvline[5] = mob[i][4];
					newvline[6] = mob[i][6];
					newvline[7] = mob[i][5] - 32768;
					newvline[8] = -8000;
					newvline[9] = 2000;
					newvline[10] = 000;
					newvline[11] = 000;
					newvline[12] = 2000;
					newvline[13] = -8000;
					SpawnLine();

					newvline[0] = 20;
					newvline[1] = mob[i][1];
					newvline[2] = mob[i][4] + 32768;
					newvline[3] = mob[i][6];
					newvline[4] = mob[i][5];
					newvline[5] = mob[i][4];
					newvline[6] = mob[i][6];
					newvline[7] = mob[i][5] - 32768;
					newvline[8] = +8000;
					newvline[9] = 2000;
					newvline[10] = 000;
					newvline[11] = 000;
					newvline[12] = 2000;
					newvline[13] = -8000;
					SpawnLine();

//DIEEEEEEEEE end
				}
			}

			if (slowed)
				speed = speed / 2;
//TOOOOOOOOOOWERZ end
			switch (dirmap[aix][aiy]) {
			case 0:
				mob[i][5] -= speed;
				mob[i][4] = mob[i][4]
						+ (((cx & 254) + 1) * 65536 - mob[i][4]) / 6;
				break;
			case 1:
				mob[i][4] += speed;
				mob[i][5] = mob[i][5]
						+ (((cy & 254) + 1) * 65536 - mob[i][5]) / 6;
				break;
			case 2:
				mob[i][5] += speed;
				mob[i][4] = mob[i][4]
						+ (((cx & 254) + 1) * 65536 - mob[i][4]) / 6;
				break;
			case 3:
				mob[i][4] -= speed;
				mob[i][5] = mob[i][5]
						+ (((cy & 254) + 1) * 65536 - mob[i][5]) / 6;
				break;
			} //switch

		}

}

void ProcAi(void) {
	if (wave > 0)
		TrySpawn();

	MobAi();

	if (wavedelay) {
		wavedelay--;
		if (wavedelay == 0)
			NewWave();
	} else if (wave > 0) {
		Uint8 i, mobs = 0;
		for (i = 0; i < 128; i++)
			if (mob[i][0] > 0)
				mobs++;
		if (mobs + wavemobleft == 0)
			wavedelay = 100;

	}

}
