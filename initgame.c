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

#include <stdio.h>

#include "vars.h"
#include "mapdata.h"

void InitGame(void) {

	Uint16 i;
	for (i = 0; i < 256; i++) {
		if (i < 240)
			NextColor0[i] = i + 16;
		else
			NextColor0[i] = i;

	}
	for (i = 0; i < 256; i++)
		NextColor2[i] = NextColor0[NextColor0[NextColor0[i]]];

	ResetMap();
}
