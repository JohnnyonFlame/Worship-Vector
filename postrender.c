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
#include "zmath.h"

#include "sblit.h"
#include "gpu3d.h"

void PostRender(void) {
	U32 x, y, i;
	zlclearscene();

	if (volumedelay) {
	}

	if (screenblend == 0)
		for (i = 0; i < 76800; i++) {
			scrbuf[i] = 0;
		}

	else
		for (i = 0; i < 76800; i++) {
			scrbuf[i] = NextColor0[scrbuf[i]];
		}

}
