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

void ProcLines(void) {

}
extern void SpawnLine(void) {
	Uint8 i = 0, k;
	while ((i < 128) & (vline[i][0] > 0))
		i++;
	if (i == 128)
		i = random128();

	for (k = 0; k < 16; k++)
		vline[i][k] = newvline[k];

}
extern void ProcBullets(void) {

}
extern void SpawnBullet(void) {

}
