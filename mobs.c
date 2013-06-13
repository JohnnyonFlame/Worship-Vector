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

void SpawnMob(void) {

	Uint8 i = 0;

	while ((mob[i][0] > 0) & (i < 128))
		i++;
	if (i < 128) {
		mob[i][0] = iwavedata[wave][1]; //hp
		mob[i][1] = iwavedata[wave][3]; //color
		mob[i][2] = iwavedata[wave][2]; //model
		mob[i][3] = iwavedata[wave][4]; //speed
		mob[i][4] = spawnx;
		mob[i][5] = spawny;
		mob[i][6] = iwavedata[wave][6]; //z
		mob[i][7] = 1024 * dirmap[spawnx / 65536 / 2][spawny / 65536 / 2]; // turn

		mob[i][10] = 0; //hurt

	}
	zl_vibro = 10;

}

void MobModel(Uint8 i) {
	Uint8 model = mob[i][2];
	Uint8 c = mob[i][1];

	if (mob[i][10]) {
		mob[i][10] = 0;
		c = 15;
	}

	switch (model) {
	case 0:
		zlvertex = 0;
		zlpoint(32768, 25000, -32768);
		zlvertex = 1;
		zlpoint(-32768, 25000, -32768);
		zlvertex = 2;
		zlpoint(0, 15000, 65536);
		if (vbufferz[0] > 20000)
			if (vvis[0]) {
				DrawLine2(vbufferx[0], vbuffery[0], vbufferx[1], vbuffery[1],
						c);
				DrawLine2(vbufferx[2], vbuffery[2], vbufferx[1], vbuffery[1],
						c);
				DrawLine2(vbufferx[2], vbuffery[2], vbufferx[0], vbuffery[0],
						c);
			}

		break;
	case 1:
		zlvertex = 0;
		zlpoint(32768, 000, 0);
		zlvertex = 1;
		zlpoint(-32768, 000, 0);
		zlvertex = 2;
		zlpoint(0, 60000, 0);
		if (vbufferz[0] > 20000)
			if (vvis[0]) {
				DrawLine2(vbufferx[0], vbuffery[0], vbufferx[1], vbuffery[1],
						c);
				DrawLine2(vbufferx[2], vbuffery[2], vbufferx[1], vbuffery[1],
						c);
				DrawLine2(vbufferx[2], vbuffery[2], vbufferx[0], vbuffery[0],
						c);
			}

		break;
	case 2:
		zlvertex = 0;
		zlpoint(32768, 0, -32768);
		zlvertex = 1;
		zlpoint(-32768, 0, -32768);
		zlvertex = 2;
		zlpoint(-32768, 0, 32768);
		zlvertex = 3;
		zlpoint(32768, 0, 32768);
		if (vbufferz[0] > 20000)
			if (vvis[0]) {
				DrawLine2(vbufferx[0], vbuffery[0], vbufferx[1], vbuffery[1],
						c);
				DrawLine2(vbufferx[2], vbuffery[2], vbufferx[1], vbuffery[1],
						c);
				DrawLine2(vbufferx[2], vbuffery[2], vbufferx[3], vbuffery[3],
						c);
				DrawLine2(vbufferx[3], vbuffery[3], vbufferx[0], vbuffery[0],
						c);
			}

		break;

	}

}

void RenderMobs(void) {
	Uint8 i, c;
	for (i = 0; i < 128; i++)
		if (mob[i][0] > 0)
			if (zabs(mob[i][4] - cursorx) < 7 * 65536)
				if (zabs(mob[i][5] - cursory) < 5 * 65536) {
					zlpushmatrix();
					zltranslate(mob[i][4], mob[i][6], -mob[i][5]);
					zlrotatey(-mob[i][7]);
					MobModel(i);
					zlpopmatrix();
				}
}

