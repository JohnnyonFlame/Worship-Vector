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

void RenderCursor(void) {
	Sint32 x = cursorx / 65536;
	Sint32 y = cursory / 65536;
	Uint8 c;
	Sint32 anim;
	switch (cursorvisual) {
	case 1: //red cross
		zlvertex = 0;
		zlpoint((x) * 65536, 25000 + mapz[x][y] * 10000, -(y) * 65536);
		zlvertex = 1;
		zlpoint((x + 1) * 65536, 25000 + mapz[x + 1][y] * 10000, -(y) * 65536);
		zlvertex = 2;
		zlpoint((x + 1) * 65536, 25000 + mapz[x + 1][y + 1] * 10000,
				-(y + 1) * 65536);
		zlvertex = 3;
		zlpoint((x) * 65536, 25000 + mapz[x][y + 1] * 10000, -(y + 1) * 65536);

		zlvertex = 4;
		zlpoint((x) * 65536, 5000 + mapz[x][y] * 10000, -(y) * 65536);
		zlvertex = 5;
		zlpoint((x + 1) * 65536, 5000 + mapz[x + 1][y] * 10000, -(y) * 65536);
		zlvertex = 6;
		zlpoint((x + 1) * 65536, 5000 + mapz[x + 1][y + 1] * 10000,
				-(y + 1) * 65536);
		zlvertex = 7;
		zlpoint((x) * 65536, 5000 + mapz[x][y + 1] * 10000, -(y + 1) * 65536);
		c = 4;
		DrawLine2(vbufferx[1], vbuffery[1], vbufferx[3], vbuffery[3], c);
		DrawLine2(vbufferx[0], vbuffery[0], vbufferx[2], vbuffery[2], c);

		DrawLine2(vbufferx[5], vbuffery[5], vbufferx[7], vbuffery[7], c);
		DrawLine2(vbufferx[4], vbuffery[4], vbufferx[6], vbuffery[6], c);
		break;
	case 2: //cultivate
		anim = (count * 899) % 10000;

		zlvertex = 0;
		zlpoint((x) * 65536 - anim, 25000 + mapz[x][y] * 10000,
				-(y) * 65536 + anim);
		zlvertex = 1;
		zlpoint((x + 1) * 65536 + anim, 25000 + mapz[x + 1][y] * 10000,
				-(y) * 65536 + anim);
		zlvertex = 2;
		zlpoint((x + 1) * 65536 + anim, 25000 + mapz[x + 1][y + 1] * 10000,
				-(y + 1) * 65536 - anim);
		zlvertex = 3;
		zlpoint((x) * 65536 - anim, 25000 + mapz[x][y + 1] * 10000,
				-(y + 1) * 65536 - anim);

		c = 14;
		DrawLine2(vbufferx[0], vbuffery[0], vbufferx[1], vbuffery[1], c);
		DrawLine2(vbufferx[1], vbuffery[1], vbufferx[2], vbuffery[2], c);
		DrawLine2(vbufferx[2], vbuffery[2], vbufferx[3], vbuffery[3], c);
		DrawLine2(vbufferx[3], vbuffery[3], vbufferx[0], vbuffery[0], c);

		DrawLine2(vbufferx[0], vbuffery[0], vbufferx[2], vbuffery[2], 15);
		DrawLine2(vbufferx[1], vbuffery[1], vbufferx[3], vbuffery[3], 15);

		break;
	case 3: //tower

		anim = (count * 899) % 10000;

		zlvertex = 0;
		zlpoint((x) * 65536 - anim, 25000 + mapz[x][y] * 10000,
				-(y) * 65536 + anim);
		zlvertex = 1;
		zlpoint((x + 1) * 65536 + anim, 25000 + mapz[x + 1][y] * 10000,
				-(y) * 65536 + anim);
		zlvertex = 2;
		zlpoint((x + 1) * 65536 + anim, 25000 + mapz[x + 1][y + 1] * 10000,
				-(y + 1) * 65536 - anim);
		zlvertex = 3;
		zlpoint((x) * 65536 - anim, 25000 + mapz[x][y + 1] * 10000,
				-(y + 1) * 65536 - anim);

		anim = 10000 + (count * 999) % 10000;

		zlvertex = 4;
		zlpoint((x) * 65536 - anim, 5000 + mapz[x][y] * 10000,
				-(y) * 65536 + anim);
		zlvertex = 5;
		zlpoint((x + 1) * 65536 + anim, 5000 + mapz[x + 1][y] * 10000,
				-(y) * 65536 + anim);
		zlvertex = 6;
		zlpoint((x + 1) * 65536 + anim, 5000 + mapz[x + 1][y + 1] * 10000,
				-(y + 1) * 65536 - anim);
		zlvertex = 7;
		zlpoint((x) * 65536 - anim, 5000 + mapz[x][y + 1] * 10000,
				-(y + 1) * 65536 - anim);

		c = 14;
		DrawLine2(vbufferx[0], vbuffery[0], vbufferx[1], vbuffery[1], c);
		DrawLine2(vbufferx[1], vbuffery[1], vbufferx[2], vbuffery[2], c);
		DrawLine2(vbufferx[2], vbuffery[2], vbufferx[3], vbuffery[3], c);
		DrawLine2(vbufferx[3], vbuffery[3], vbufferx[0], vbuffery[0], c);

		c = 15;
		DrawLine2(vbufferx[4], vbuffery[4], vbufferx[5], vbuffery[5], c);
		DrawLine2(vbufferx[5], vbuffery[5], vbufferx[6], vbuffery[6], c);
		DrawLine2(vbufferx[6], vbuffery[6], vbufferx[7], vbuffery[7], c);
		DrawLine2(vbufferx[7], vbuffery[7], vbufferx[4], vbuffery[4], c);

		break;
	case 4: //sell

		zlvertex = 0;
		zlpoint((x) * 65536, 25000 + mapz[x][y] * 10000, -(y) * 65536);
		zlvertex = 1;
		zlpoint((x + 1) * 65536, 25000 + mapz[x + 1][y] * 10000, -(y) * 65536);
		zlvertex = 2;
		zlpoint((x + 1) * 65536, 25000 + mapz[x + 1][y + 1] * 10000,
				-(y + 1) * 65536);
		zlvertex = 3;
		zlpoint((x) * 65536, 25000 + mapz[x][y + 1] * 10000, -(y + 1) * 65536);

		c = 14;
		anim = (count / 3) % 4;

		DrawLine2(vbufferx[anim], vbuffery[anim], vbufferx[(anim + 1) % 4],
				vbuffery[(anim + 1) % 4], c);

		break;

	} //switch    
}

void RenderLines(void) {
	Uint8 i, k;
	for (i = 0; i < 128; i++)
		if (vline[i][0] > 0) {
			zlvertex = 0;
			zlpoint(vline[i][2], vline[i][3], -vline[i][4]);
			zlvertex = 1;
			zlpoint(vline[i][5], vline[i][6], -vline[i][7]);
			if (vbufferz[0] > 0)
				if (vbufferz[1] > 0)
					if (vvis[0])
						if (vvis[1])
							DrawLine2(vbufferx[0], vbuffery[0], vbufferx[1],
									vbuffery[1], vline[i][1]);

			for (k = 2; k < 8; k++)
				vline[i][k] += vline[i][k + 6];

			vline[i][0]--;
		}

}

void RenderObjects(void) {
	RenderMobs();
	RenderLines();

}
