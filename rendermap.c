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
#include "gpu3d.h"
#include "sblit.h"

#define FPMUL(x,y)	((((x)>>6)*((y)>>6))>>4)

void RenderCell(Sint8 x, Sint8 y) {
	Uint8 c, m;
	Sint32 wwx;
	m = 99;
	if ((x >= 0) & (x < 64) & (y >= 0) & (y < 64)) {

		m = map[x][y];
		if (mapunlock[x / 8][y / 8] > wave + 1)
			m = 100;
		else if (mapunlock[x / 8][y / 8] > wave)
			if (map[x][y] == 10)
				m = 97;
			else
				m = 98;

	}
	switch (m) {
	case 0: //grass
		zlvertex = 0;
		zlpoint((x) * 65536, -5000 + mapz[x][y] * 10000, -(y) * 65536);
		zlvertex = 1;
		zlpoint((x + 1) * 65536, -5000 + mapz[x + 1][y] * 10000, -(y) * 65536);
		zlvertex = 2;
		zlpoint((x + 1) * 65536, -5000 + mapz[x + 1][y + 1] * 10000,
				-(y + 1) * 65536);
		zlvertex = 3;
		zlpoint((x) * 65536, -5000 + mapz[x][y + 1] * 10000, -(y + 1) * 65536);
		if (vbufferz[2] > 0) {
			c = 2;
			DrawLine2(vbufferx[0], vbuffery[0], vbufferx[1], vbuffery[1], c);
			DrawLine2(vbufferx[2], vbuffery[2], vbufferx[1], vbuffery[1], c);
			DrawLine2(vbufferx[2], vbuffery[2], vbufferx[3], vbuffery[3], c);
			DrawLine2(vbufferx[0], vbuffery[0], vbufferx[3], vbuffery[3], c);

			DrawLine2(vbufferx[0], vbuffery[0], vbufferx[2], vbuffery[2], c);

		}
		break;
	case 1: // water

		wwx = (count * 2555) & 65535;

		zlvertex = 0;
		zlpoint((x) * 65536, -10000 + mapz[x][y] * 10000, -(y) * 65536 - wwx);
		zlvertex = 1;
		zlpoint((x + 1) * 65536, -10000 + mapz[x + 1][y] * 10000,
				-(y) * 65536 - wwx);
		zlvertex = 2;
		zlpoint((x) * 65536 + wwx, -10000 + mapz[x + 1][y + 1] * 10000,
				-(y) * 65536);
		zlvertex = 3;
		zlpoint((x) * 65536 + wwx, -10000 + mapz[x][y + 1] * 10000,
				-(y + 1) * 65536);

		if (vbufferz[2] > 0) {
			c = 1;
			DrawLine2(vbufferx[0], vbuffery[0], vbufferx[1], vbuffery[1], c);
			DrawLine2(vbufferx[2], vbuffery[2], vbufferx[3], vbuffery[3], c);

		}
		break;
	case 2: //dirt
		zlvertex = 0;
		zlpoint((x) * 65536, -5000 + mapz[x][y] * 10000, -(y) * 65536);
		zlvertex = 1;
		zlpoint((x + 1) * 65536, -5000 + mapz[x + 1][y] * 10000, -(y) * 65536);
		zlvertex = 2;
		zlpoint((x + 1) * 65536, -5000 + mapz[x + 1][y + 1] * 10000,
				-(y + 1) * 65536);
		zlvertex = 3;
		zlpoint((x) * 65536, -5000 + mapz[x][y + 1] * 10000, -(y + 1) * 65536);
		if (vbufferz[2] > 0) {
			c = 6;
			DrawLine2(vbufferx[0], vbuffery[0], vbufferx[1], vbuffery[1], c);
			DrawLine2(vbufferx[2], vbuffery[2], vbufferx[1], vbuffery[1], c);
			DrawLine2(vbufferx[2], vbuffery[2], vbufferx[3], vbuffery[3], c);
			DrawLine2(vbufferx[0], vbuffery[0], vbufferx[3], vbuffery[3], c);

			DrawLine2(vbufferx[1], vbuffery[1], vbufferx[3], vbuffery[3], c);

		}
		break;
	case 3: // ice
		zlvertex = 0;
		zlpoint((x) * 65536, -5000 + mapz[x][y] * 10000, -(y) * 65536);
		zlvertex = 1;
		zlpoint((x + 1) * 65536, -5000 + mapz[x + 1][y] * 10000, -(y) * 65536);
		zlvertex = 2;
		zlpoint((x + 1) * 65536, -5000 + mapz[x + 1][y + 1] * 10000,
				-(y + 1) * 65536);
		zlvertex = 3;
		zlpoint((x) * 65536, -5000 + mapz[x][y + 1] * 10000, -(y + 1) * 65536);
		if (vbufferz[2] > 0) {
			Uint8 c = 11;
			DrawLine2(vbufferx[0], vbuffery[0], vbufferx[1], vbuffery[1], c);
			DrawLine2(vbufferx[2], vbuffery[2], vbufferx[1], vbuffery[1], c);
			DrawLine2(vbufferx[2], vbuffery[2], vbufferx[3], vbuffery[3], c);
			DrawLine2(vbufferx[0], vbuffery[0], vbufferx[3], vbuffery[3], c);
			DrawLine2(vbufferx[0], vbuffery[0], vbufferx[2], vbuffery[2], c);
		}
		break;
	case 4: // ice water

		wwx = (count * 1555) & 65535;

		zlvertex = 0;
		zlpoint((x) * 65536, -10000 + mapz[x][y] * 10000, -(y) * 65536 - wwx);
		zlvertex = 1;
		zlpoint((x + 1) * 65536, -10000 + mapz[x + 1][y] * 10000,
				-(y) * 65536 - wwx);
		zlvertex = 2;
		zlpoint((x) * 65536 + wwx, -10000 + mapz[x + 1][y + 1] * 10000,
				-(y) * 65536);
		zlvertex = 3;
		zlpoint((x) * 65536 + wwx, -10000 + mapz[x][y + 1] * 10000,
				-(y + 1) * 65536);

		if (vbufferz[2] > 0) {
			c = 9;
			DrawLine2(vbufferx[0], vbuffery[0], vbufferx[1], vbuffery[1], c);
			DrawLine2(vbufferx[2], vbuffery[2], vbufferx[3], vbuffery[3], c);

		}
		break;
	case 5: // sand
		zlvertex = 0;
		zlpoint((x) * 65536, -5000 + mapz[x][y] * 10000, -(y) * 65536);
		zlvertex = 1;
		zlpoint((x + 1) * 65536, -5000 + mapz[x + 1][y] * 10000, -(y) * 65536);
		zlvertex = 2;
		zlpoint((x + 1) * 65536, -5000 + mapz[x + 1][y + 1] * 10000,
				-(y + 1) * 65536);
		zlvertex = 3;
		zlpoint((x) * 65536, -5000 + mapz[x][y + 1] * 10000, -(y + 1) * 65536);
		if (vbufferz[2] > 0) {
			Uint8 c = 14;
			DrawLine2(vbufferx[0], vbuffery[0], vbufferx[1], vbuffery[1], c);
			DrawLine2(vbufferx[2], vbuffery[2], vbufferx[1], vbuffery[1], c);
			DrawLine2(vbufferx[2], vbuffery[2], vbufferx[3], vbuffery[3], c);
			DrawLine2(vbufferx[0], vbuffery[0], vbufferx[3], vbuffery[3], c);
			DrawLine2(vbufferx[0], vbuffery[0], vbufferx[2], vbuffery[2], c);
		}
		break;
	case 6: // lava

		wwx = 65535 - (count * 3555) & 65535;

		zlvertex = 0;
		zlpoint((x) * 65536, -10000 + mapz[x][y] * 10000, -(y) * 65536 - wwx);
		zlvertex = 1;
		zlpoint((x + 1) * 65536, -10000 + mapz[x + 1][y] * 10000,
				-(y) * 65536 - wwx);
		zlvertex = 2;
		zlpoint((x) * 65536 + wwx, -10000 + mapz[x + 1][y + 1] * 10000,
				-(y) * 65536);
		zlvertex = 3;
		zlpoint((x) * 65536 + wwx, -10000 + mapz[x][y + 1] * 10000,
				-(y + 1) * 65536);

		if (vbufferz[2] > 0) {
			c = 4;
			DrawLine2(vbufferx[0], vbuffery[0], vbufferx[1], vbuffery[1], c);
			DrawLine2(vbufferx[2], vbuffery[2], vbufferx[3], vbuffery[3], c);

		}
		break;

	case 9: //player's base
		zlvertex = 0;
		zlpoint((x) * 65536, 9000, -(y) * 65536);
		zlvertex = 1;
		zlpoint((x + 1) * 65536, 9000, -(y) * 65536);
		zlvertex = 2;
		zlpoint((x + 1) * 65536, 9000, -(y + 1) * 65536);
		zlvertex = 3;
		zlpoint((x) * 65536, 9000, -(y + 1) * 65536);

		zlvertex = 4;
		zlpoint((x) * 65536, -29000, -(y) * 65536);
		zlvertex = 5;
		zlpoint((x + 1) * 65536, -29000, -(y) * 65536);
		zlvertex = 6;
		zlpoint((x + 1) * 65536, -29000, -(y + 1) * 65536);
		zlvertex = 7;
		zlpoint((x) * 65536, -29000, -(y + 1) * 65536);

		if (vbufferz[2] > 0) {
			c = 12;
			if (y & 1)
				DrawLine2(vbufferx[2], vbuffery[2], vbufferx[3], vbuffery[3],
						c);
			else
				DrawLine2(vbufferx[0], vbuffery[0], vbufferx[1], vbuffery[1],
						c);

			if (x & 1)
				DrawLine2(vbufferx[1], vbuffery[1], vbufferx[2], vbuffery[2],
						c);
			else
				DrawLine2(vbufferx[3], vbuffery[3], vbufferx[0], vbuffery[0],
						c);

			if (y & 1)
				DrawLine2(vbufferx[6], vbuffery[6], vbufferx[7], vbuffery[7],
						c);
			else
				DrawLine2(vbufferx[4], vbuffery[4], vbufferx[5], vbuffery[5],
						c);

			if (x & 1)
				DrawLine2(vbufferx[5], vbuffery[5], vbufferx[6], vbuffery[6],
						c);
			else
				DrawLine2(vbufferx[7], vbuffery[7], vbufferx[4], vbuffery[4],
						c);

			DrawLine2(vbufferx[4], vbuffery[4], vbufferx[6], vbuffery[6], c);
			DrawLine2(vbufferx[7], vbuffery[7], vbufferx[5], vbuffery[5], c);

		}
		break;

	case 10: //road of enemy
		zlvertex = 0;
		zlpoint((x) * 65536, -9000 + mapz[x][y] * 10000, -(y) * 65536);
		zlvertex = 1;
		zlpoint((x + 1) * 65536, -9000 + mapz[x + 1][y] * 10000, -(y) * 65536);
		zlvertex = 2;
		zlpoint((x + 1) * 65536, -9000 + mapz[x + 1][y + 1] * 10000,
				-(y + 1) * 65536);
		zlvertex = 3;
		zlpoint((x) * 65536, -9000 + mapz[x][y + 1] * 10000, -(y + 1) * 65536);
		if (vbufferz[2] > 0) {
			c = 8;
			if (y & 1)
				DrawLine2(vbufferx[2], vbuffery[2], vbufferx[3], vbuffery[3],
						c);
			else
				DrawLine2(vbufferx[0], vbuffery[0], vbufferx[1], vbuffery[1],
						c);

			if (x & 1)
				DrawLine2(vbufferx[1], vbuffery[1], vbufferx[2], vbuffery[2],
						c);
			else
				DrawLine2(vbufferx[3], vbuffery[3], vbufferx[0], vbuffery[0],
						c);

//     DrawLine2(vbufferx[2],vbuffery[2],vbufferx[1],vbuffery[1],c);                                  
//     DrawLine2(vbufferx[2],vbuffery[2],vbufferx[3],vbuffery[3],c);                                  
//     DrawLine2(vbufferx[0],vbuffery[0],vbufferx[3],vbuffery[3],c);                                  

		}
		break;
	case 11: //plate
		zlvertex = 0;
		zlpoint(5000 + (x) * 65536, 5000, -5000 - (y) * 65536);
		zlvertex = 1;
		zlpoint(-5000 + (x + 1) * 65536, 5000, -5000 - (y) * 65536);
		zlvertex = 2;
		zlpoint(-5000 + (x + 1) * 65536, 5000, 5000 - (y + 1) * 65536);
		zlvertex = 3;
		zlpoint(5000 + (x) * 65536, 5000, 5000 - (y + 1) * 65536);
		if (vbufferz[2] > 0) {
			c = 7;
			DrawLine2(vbufferx[0], vbuffery[0], vbufferx[1], vbuffery[1], c);
			DrawLine2(vbufferx[2], vbuffery[2], vbufferx[1], vbuffery[1], c);
			DrawLine2(vbufferx[2], vbuffery[2], vbufferx[3], vbuffery[3], c);
			DrawLine2(vbufferx[0], vbuffery[0], vbufferx[3], vbuffery[3], c);
		}
		break;
	case 12: //minigun

		zlvertex = 0;
		zlpoint(5000 + (x) * 65536, 10000, -5000 - (y) * 65536);
		zlvertex = 1;
		zlpoint(-5000 + (x + 1) * 65536, 10000, -5000 - (y) * 65536);
		zlvertex = 2;
		zlpoint(-5000 + (x + 1) * 65536, 10000, 5000 - (y + 1) * 65536);
		zlvertex = 3;
		zlpoint(5000 + (x) * 65536, 10000, 5000 - (y + 1) * 65536);

		zlvertex = 4;
		zlpoint(10000 + (x) * 65536, 30000, -15000 - (y) * 65536);
		zlvertex = 5;
		zlpoint(-10000 + (x + 1) * 65536, 30000, -15000 - (y) * 65536);
		zlvertex = 6;
		zlpoint(-10000 + (x + 1) * 65536, 30000, 15000 - (y + 1) * 65536);
		zlvertex = 7;
		zlpoint(10000 + (x) * 65536, 30000, 15000 - (y + 1) * 65536);

		if (vbufferz[2] > 0) {
			c = 8;
			DrawLine2(vbufferx[0], vbuffery[0], vbufferx[1], vbuffery[1], c);
			DrawLine2(vbufferx[2], vbuffery[2], vbufferx[1], vbuffery[1], c);
			DrawLine2(vbufferx[2], vbuffery[2], vbufferx[3], vbuffery[3], c);
			DrawLine2(vbufferx[0], vbuffery[0], vbufferx[3], vbuffery[3], c);
			c = 7;
			DrawLine2(vbufferx[0], vbuffery[0], vbufferx[4], vbuffery[4], c);
			DrawLine2(vbufferx[1], vbuffery[1], vbufferx[5], vbuffery[5], c);
			DrawLine2(vbufferx[2], vbuffery[2], vbufferx[6], vbuffery[6], c);
			DrawLine2(vbufferx[3], vbuffery[3], vbufferx[7], vbuffery[7], c);
			c = 15;
			DrawLine2(vbufferx[4], vbuffery[4], vbufferx[5], vbuffery[5], c);
			DrawLine2(vbufferx[6], vbuffery[6], vbufferx[5], vbuffery[5], c);
			DrawLine2(vbufferx[6], vbuffery[6], vbufferx[7], vbuffery[7], c);
			DrawLine2(vbufferx[4], vbuffery[4], vbufferx[7], vbuffery[7], c);

		}
		break;
	case 13: //anti air

		zlvertex = 0;
		zlpoint(5000 + (x) * 65536, 10000, -5000 - (y) * 65536);
		zlvertex = 1;
		zlpoint(-5000 + (x + 1) * 65536, 10000, -5000 - (y) * 65536);
		zlvertex = 2;
		zlpoint(-5000 + (x + 1) * 65536, 10000, 5000 - (y + 1) * 65536);
		zlvertex = 3;
		zlpoint(5000 + (x) * 65536, 10000, 5000 - (y + 1) * 65536);

		zlvertex = 4;
		zlpoint(20000 + (x) * 65536, 45000, -20000 - (y) * 65536);
		zlvertex = 5;
		zlpoint(-20000 + (x + 1) * 65536, 45000, -20000 - (y) * 65536);
		zlvertex = 6;
		zlpoint(-20000 + (x + 1) * 65536, 45000, 20000 - (y + 1) * 65536);
		zlvertex = 7;
		zlpoint(20000 + (x) * 65536, 45000, 20000 - (y + 1) * 65536);

		if (vbufferz[2] > 0) {
			c = 7;
			DrawLine2(vbufferx[0], vbuffery[0], vbufferx[1], vbuffery[1], c);
			DrawLine2(vbufferx[2], vbuffery[2], vbufferx[1], vbuffery[1], c);
			DrawLine2(vbufferx[2], vbuffery[2], vbufferx[3], vbuffery[3], c);
			DrawLine2(vbufferx[0], vbuffery[0], vbufferx[3], vbuffery[3], c);
			c = 8;
			DrawLine2(vbufferx[0], vbuffery[0], vbufferx[4], vbuffery[4], c);
			DrawLine2(vbufferx[1], vbuffery[1], vbufferx[5], vbuffery[5], c);
			DrawLine2(vbufferx[2], vbuffery[2], vbufferx[6], vbuffery[6], c);
			DrawLine2(vbufferx[3], vbuffery[3], vbufferx[7], vbuffery[7], c);
			c = 12;
			DrawLine2(vbufferx[4], vbuffery[4], vbufferx[5], vbuffery[5], c);
			DrawLine2(vbufferx[6], vbuffery[6], vbufferx[5], vbuffery[5], c);
			DrawLine2(vbufferx[6], vbuffery[6], vbufferx[7], vbuffery[7], c);
			DrawLine2(vbufferx[4], vbuffery[4], vbufferx[7], vbuffery[7], c);

		}
		break;
	case 14: //artilery

		zlvertex = 0;
		zlpoint(20000 + (x) * 65536, 10000, -20000 - (y) * 65536);
		zlvertex = 1;
		zlpoint(-20000 + (x + 1) * 65536, 10000, -20000 - (y) * 65536);
		zlvertex = 2;
		zlpoint(-20000 + (x + 1) * 65536, 10000, 20000 - (y + 1) * 65536);
		zlvertex = 3;
		zlpoint(20000 + (x) * 65536, 10000, 20000 - (y + 1) * 65536);

		zlvertex = 4;
		zlpoint(5000 + (x) * 65536, 30000, -5000 - (y) * 65536);
		zlvertex = 5;
		zlpoint(-5000 + (x + 1) * 65536, 30000, -5000 - (y) * 65536);
		zlvertex = 6;
		zlpoint(-5000 + (x + 1) * 65536, 30000, 5000 - (y + 1) * 65536);
		zlvertex = 7;
		zlpoint(5000 + (x) * 65536, 30000, 5000 - (y + 1) * 65536);

		if (vbufferz[2] > 0) {
			c = 8;
			DrawLine2(vbufferx[0], vbuffery[0], vbufferx[1], vbuffery[1], c);
			DrawLine2(vbufferx[2], vbuffery[2], vbufferx[1], vbuffery[1], c);
			DrawLine2(vbufferx[2], vbuffery[2], vbufferx[3], vbuffery[3], c);
			DrawLine2(vbufferx[0], vbuffery[0], vbufferx[3], vbuffery[3], c);
			c = 7;
			DrawLine2(vbufferx[0], vbuffery[0], vbufferx[4], vbuffery[4], c);
			DrawLine2(vbufferx[1], vbuffery[1], vbufferx[5], vbuffery[5], c);
			DrawLine2(vbufferx[2], vbuffery[2], vbufferx[6], vbuffery[6], c);
			DrawLine2(vbufferx[3], vbuffery[3], vbufferx[7], vbuffery[7], c);
			c = 15;
			DrawLine2(vbufferx[4], vbuffery[4], vbufferx[5], vbuffery[5], c);
			DrawLine2(vbufferx[6], vbuffery[6], vbufferx[5], vbuffery[5], c);
			DrawLine2(vbufferx[6], vbuffery[6], vbufferx[7], vbuffery[7], c);
			DrawLine2(vbufferx[4], vbuffery[4], vbufferx[7], vbuffery[7], c);

		}
		break;
	case 15: //slowray

		zlvertex = 0;
		zlpoint(5000 + (x) * 65536, 10000, -5000 - (y) * 65536);
		zlvertex = 1;
		zlpoint(-5000 + (x + 1) * 65536, 10000, -5000 - (y) * 65536);
		zlvertex = 2;
		zlpoint(-5000 + (x + 1) * 65536, 10000, 5000 - (y + 1) * 65536);
		zlvertex = 3;
		zlpoint(5000 + (x) * 65536, 10000, 5000 - (y + 1) * 65536);

		zlvertex = 4;
		zlpoint(32768 + (x) * 65536, 30000, -32768 - (y) * 65536);

		if (vbufferz[2] > 0) {
			c = 5;
			DrawLine2(vbufferx[0], vbuffery[0], vbufferx[1], vbuffery[1], c);
			DrawLine2(vbufferx[2], vbuffery[2], vbufferx[1], vbuffery[1], c);
			DrawLine2(vbufferx[2], vbuffery[2], vbufferx[3], vbuffery[3], c);
			DrawLine2(vbufferx[0], vbuffery[0], vbufferx[3], vbuffery[3], c);
			c = 9;
			DrawLine2(vbufferx[0], vbuffery[0], vbufferx[4], vbuffery[4], c);
			DrawLine2(vbufferx[1], vbuffery[1], vbufferx[4], vbuffery[4], c);
			DrawLine2(vbufferx[2], vbuffery[2], vbufferx[4], vbuffery[4], c);
			DrawLine2(vbufferx[3], vbuffery[3], vbufferx[4], vbuffery[4], c);

		}
		break;
	case 16: //sniper

		zlvertex = 0;
		zlpoint(5000 + (x) * 65536, 10000, -5000 - (y) * 65536);
		zlvertex = 1;
		zlpoint(-5000 + (x + 1) * 65536, 10000, -5000 - (y) * 65536);
		zlvertex = 2;
		zlpoint(-5000 + (x + 1) * 65536, 10000, 5000 - (y + 1) * 65536);
		zlvertex = 3;
		zlpoint(5000 + (x) * 65536, 10000, 5000 - (y + 1) * 65536);

		zlvertex = 4;
		zlpoint(25000 + (x) * 65536, 90000, -25000 - (y) * 65536);
		zlvertex = 5;
		zlpoint(-25000 + (x + 1) * 65536, 90000, -25000 - (y) * 65536);
		zlvertex = 6;
		zlpoint(-25000 + (x + 1) * 65536, 90000, 25000 - (y + 1) * 65536);
		zlvertex = 7;
		zlpoint(25000 + (x) * 65536, 90000, 25000 - (y + 1) * 65536);

		if (vbufferz[2] > 0) {
			c = 7;
			DrawLine2(vbufferx[0], vbuffery[0], vbufferx[1], vbuffery[1], c);
			DrawLine2(vbufferx[2], vbuffery[2], vbufferx[1], vbuffery[1], c);
			DrawLine2(vbufferx[2], vbuffery[2], vbufferx[3], vbuffery[3], c);
			DrawLine2(vbufferx[0], vbuffery[0], vbufferx[3], vbuffery[3], c);
			c = 15;
			DrawLine2(vbufferx[0], vbuffery[0], vbufferx[4], vbuffery[4], c);
			DrawLine2(vbufferx[1], vbuffery[1], vbufferx[5], vbuffery[5], c);
			DrawLine2(vbufferx[2], vbuffery[2], vbufferx[6], vbuffery[6], c);
			DrawLine2(vbufferx[3], vbuffery[3], vbufferx[7], vbuffery[7], c);
			c = 10;
			DrawLine2(vbufferx[4], vbuffery[4], vbufferx[5], vbuffery[5], c);
			DrawLine2(vbufferx[6], vbuffery[6], vbufferx[5], vbuffery[5], c);
			DrawLine2(vbufferx[6], vbuffery[6], vbufferx[7], vbuffery[7], c);
			DrawLine2(vbufferx[4], vbuffery[4], vbufferx[7], vbuffery[7], c);

		}
		break;
	case 17: //plant

		zlvertex = 0;
		zlpoint(5000 + (x) * 65536, 10000, -5000 - (y) * 65536);
		zlvertex = 1;
		zlpoint(-5000 + (x + 1) * 65536, 10000, -5000 - (y) * 65536);
		zlvertex = 2;
		zlpoint(-5000 + (x + 1) * 65536, 10000, 5000 - (y + 1) * 65536);
		zlvertex = 3;
		zlpoint(5000 + (x) * 65536, 10000, 5000 - (y + 1) * 65536);

		zlvertex = 4;
		zlpoint(15000 + (x) * 65536, 50000, -15000 - (y) * 65536);
		zlvertex = 5;
		zlpoint(-15000 + (x + 1) * 65536, 50000, -15000 - (y) * 65536);
		zlvertex = 6;
		zlpoint(-15000 + (x + 1) * 65536, 50000, 15000 - (y + 1) * 65536);
		zlvertex = 7;
		zlpoint(15000 + (x) * 65536, 50000, 15000 - (y + 1) * 65536);

		if (vbufferz[2] > 0) {
			c = 5;
			DrawLine2(vbufferx[0], vbuffery[0], vbufferx[1], vbuffery[1], c);
			DrawLine2(vbufferx[2], vbuffery[2], vbufferx[1], vbuffery[1], c);
			DrawLine2(vbufferx[2], vbuffery[2], vbufferx[3], vbuffery[3], c);
			DrawLine2(vbufferx[0], vbuffery[0], vbufferx[3], vbuffery[3], c);
			c = 5;
			DrawLine2(vbufferx[0], vbuffery[0], vbufferx[4], vbuffery[4], c);
			DrawLine2(vbufferx[1], vbuffery[1], vbufferx[5], vbuffery[5], c);
			DrawLine2(vbufferx[2], vbuffery[2], vbufferx[6], vbuffery[6], c);
			DrawLine2(vbufferx[3], vbuffery[3], vbufferx[7], vbuffery[7], c);
			c = 13;
			DrawLine2(vbufferx[4], vbuffery[4], vbufferx[5], vbuffery[5], c);
			DrawLine2(vbufferx[6], vbuffery[6], vbufferx[5], vbuffery[5], c);
			DrawLine2(vbufferx[6], vbuffery[6], vbufferx[7], vbuffery[7], c);
			DrawLine2(vbufferx[4], vbuffery[4], vbufferx[7], vbuffery[7], c);

		}
		break;

	case 97: //new road of enemy
		zlvertex = 0;
		zlpoint((x) * 65536, -9000 + mapz[x][y] * 10000, -(y) * 65536);
		zlvertex = 1;
		zlpoint((x + 1) * 65536, -9000 + mapz[x + 1][y] * 10000, -(y) * 65536);
		zlvertex = 2;
		zlpoint((x + 1) * 65536, -9000 + mapz[x + 1][y + 1] * 10000,
				-(y + 1) * 65536);
		zlvertex = 3;
		zlpoint((x) * 65536, -9000 + mapz[x][y + 1] * 10000, -(y + 1) * 65536);
		if (vbufferz[2] > 0) {
			c = 3;
			if (y & 1)
				DrawLine2(vbufferx[2], vbuffery[2], vbufferx[3], vbuffery[3],
						c);
			else
				DrawLine2(vbufferx[0], vbuffery[0], vbufferx[1], vbuffery[1],
						c);

			if (x & 1)
				DrawLine2(vbufferx[1], vbuffery[1], vbufferx[2], vbuffery[2],
						c);
			else
				DrawLine2(vbufferx[3], vbuffery[3], vbufferx[0], vbuffery[0],
						c);

		}
		break;
	case 98: //will be open soon
		zlvertex = 0;
		zlpoint((x) * 65536, -5000 + mapz[x][y] * 10000, -(y) * 65536);
		zlvertex = 1;
		zlpoint((x + 1) * 65536, -5000 + mapz[x + 1][y] * 10000, -(y) * 65536);
		zlvertex = 2;
		zlpoint((x + 1) * 65536, -5000 + mapz[x + 1][y + 1] * 10000,
				-(y + 1) * 65536);
		zlvertex = 3;
		zlpoint((x) * 65536, -5000 + mapz[x][y + 1] * 10000, -(y + 1) * 65536);
		if (vbufferz[2] > 0) {
			c = 3;
			DrawLine2(vbufferx[0], vbuffery[0], vbufferx[1], vbuffery[1], c);
			DrawLine2(vbufferx[2], vbuffery[2], vbufferx[1], vbuffery[1], c);
			DrawLine2(vbufferx[2], vbuffery[2], vbufferx[3], vbuffery[3], c);
			DrawLine2(vbufferx[0], vbuffery[0], vbufferx[3], vbuffery[3], c);

		}
		break;

	case 99: //off limit
		zlvertex = 0;
		zlpoint((x) * 65536, -15000, -(y) * 65536);
		zlvertex = 1;
		zlpoint((x + 1) * 65536, -15000, -(y) * 65536);
		zlvertex = 2;
		zlpoint((x + 1) * 65536, -15000, -(y + 1) * 65536);
		zlvertex = 3;
		zlpoint((x) * 65536, -15000, -(y + 1) * 65536);
		if (vbufferz[2] > 0) {
			c = 8;
			DrawLine2(vbufferx[3], vbuffery[3], vbufferx[1], vbuffery[1], c);
			DrawLine2(vbufferx[0], vbuffery[0], vbufferx[2], vbuffery[2], c);

		}
		break;

	} //switch
}

void RenderMap(void) {
	Sint32 x, y, cx, cy;
	cx = cursorx / 65536;
	cy = cursory / 65536;
	for (y = -6; y <= 5; y++) {
		for (x = -7; x < 0; x++) {
			RenderCell(cx + x, cy + y);
			RenderCell(cx - x, cy + y);
		}
		RenderCell(cx, cy + y);

	}

}
