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

extern void zlpoint(Sint32 vx, Sint32 vy, Sint32 vz);
extern void zlrotatex(Sint32 alpha);
extern void zlrotatey(Sint32 alpha);
extern void zlrotatez(Sint32 alpha);
extern void zltranslate(Sint32 x, Sint32 y, Sint32 z);
extern void zlpushmatrix(void);
extern void zlpopmatrix(void);
extern void zlclearscene(void);
