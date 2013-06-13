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
U32 color[16];

void InitPalette(void) {
	U16 i, colors = 256;

	color[0] = 0x000000;
	color[1] = 0x0000AA;
	color[2] = 0x00AA00;
	color[3] = 0x00AAAA;
	color[4] = 0xAA0000;
	color[5] = 0xAA00AA;
	color[6] = 0xAA5500;
	color[7] = 0xAAAAAA;
	color[8] = 0x555555;
	color[9] = 0x5555FF;
	color[10] = 0x55FF55;
	color[11] = 0x55FFFF;
	color[12] = 0xFF5555;
	color[13] = 0xFF55FF;
	color[14] = 0xFFFF55;
	color[15] = 0xFFFFFF;

	for (i = 0; i < 16; i++) {
		palette[i][0] = (color[i] / 65536);
		palette[i][1] = (color[i] / 256) % 256;
		palette[i][2] = (color[i]) % 256;
	}

	for (i = 16; i < 256; i++) {
		palette[i][0] = palette[i - 16][0] * 8 / 10;
		palette[i][1] = palette[i - 16][1] * 8 / 10;
		palette[i][2] = palette[i - 16][2] * 8 / 10;
	}

}
