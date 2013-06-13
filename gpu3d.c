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

#define FPMUL(x,y)	((((x)>>6)*((y)>>6))>>4)
#define FPDIV(x,y)	((((x)<<6)/((y)>>6))>>4) 

Sint32 matrix[16], matrix2[16], mmatrix[16], matrixstack[16];
Sint32 dist = 95500, dist0 = 90000;

void matrixmul(void) {
	int x, y, i;
	for (y = 0; y < 4; y++)
		for (x = 0; x < 4; x++) {
			mmatrix[x + y * 4] = 0;
			for (i = 0; i < 4; i++)
				mmatrix[x + y * 4] += FPMUL(matrix[i+y*4],matrix2[x+i*4]);
		}
	for (i = 0; i < 16; i++)
		matrix[i] = mmatrix[i];

}

void zlrotatey(Sint32 alpha) {
	Sint32 t = alpha;
	t = t & 4095;
	if (t < 0)
		t = 4095 - t;

	Sint32 sy = f_sin[t];
	Sint32 cy = f_cos[t];

	matrix2[0] = cy;
	matrix2[1] = 0;
	matrix2[2] = -sy;
	matrix2[3] = 0;
	matrix2[4] = 0;
	matrix2[5] = 65536;
	matrix2[6] = 0;
	matrix2[7] = 0;
	matrix2[8] = sy;
	matrix2[9] = 0;
	matrix2[10] = cy;
	matrix2[11] = 0;
	matrix2[12] = 0;
	matrix2[13] = 0;
	matrix2[14] = 0;
	matrix2[15] = 65536;

	matrixmul();
}

void zlrotatex(Sint32 alpha) {
	Sint32 t = alpha;
	t = t & 4095;
	if (t < 0)
		t = 4095 - t;

	Sint32 sy = f_sin[t];
	Sint32 cy = f_cos[t];

	matrix2[0] = 65536;
	matrix2[1] = 0;
	matrix2[2] = -0;
	matrix2[3] = 0;
	matrix2[4] = 0;
	matrix2[5] = cy;
	matrix2[6] = -sy;
	matrix2[7] = 0;
	matrix2[8] = 0;
	matrix2[9] = sy;
	matrix2[10] = cy;
	matrix2[11] = 0;
	matrix2[12] = 0;
	matrix2[13] = 0;
	matrix2[14] = 0;
	matrix2[15] = 65536;

	matrixmul();
}
void zlrotatez(Sint32 alpha) {
	Sint32 t = alpha;
	t = t & 4095;
	if (t < 0)
		t = 4095 - t;

	Sint32 sy = f_sin[t];
	Sint32 cy = f_cos[t];

	matrix2[0] = cy;
	matrix2[1] = -sy;
	matrix2[2] = 0;
	matrix2[3] = 0;
	matrix2[4] = sy;
	matrix2[5] = cy;
	matrix2[6] = 0;
	matrix2[7] = 0;
	matrix2[8] = 0;
	matrix2[9] = 0;
	matrix2[10] = 65536;
	matrix2[11] = 0;
	matrix2[12] = 0;
	matrix2[13] = 0;
	matrix2[14] = 0;
	matrix2[15] = 65536;

	matrixmul();
}

void zltranslate(Sint32 x, Sint32 y, Sint32 z) {
	matrix2[0] = 65536;
	matrix2[1] = 0;
	matrix2[2] = 0;
	matrix2[3] = x;
	matrix2[4] = 0;
	matrix2[5] = 65536;
	matrix2[6] = 0;
	matrix2[7] = y;
	matrix2[8] = 0;
	matrix2[9] = 0;
	matrix2[10] = 65536;
	matrix2[11] = z;
	matrix2[12] = 0;
	matrix2[13] = 0;
	matrix2[14] = 0;
	matrix2[15] = 65536;

	matrixmul();
}
void zlpushmatrix(void) {
	Uint8 i;
	for (i = 0; i < 16; i++)
		matrixstack[i] = matrix[i];
}
void zlpopmatrix(void) {
	Uint8 i;
	for (i = 0; i < 16; i++)
		matrix[i] = matrixstack[i];
}

void zlpoint(Sint32 vx, Sint32 vy, Sint32 vz) {
	Sint32 x, y, t;
	Sint32 v[4], v1[4];

	v[0] = vx;
	v[1] = vy;
	v[2] = vz;
	v[3] = 65536;
	for (t = 0; t < 4; t++) {
		v1[t] = 0;
		for (x = 0; x < 4; x++)
			v1[t] += FPMUL(v[x],matrix[x+t*4]);
	}

	t = v1[2] + dist;
	if (t != 0)

		if (v1[2] > -dist0) {
			vvis[zlvertex] = 1;
			vbufferx[zlvertex] = 140 + FPDIV(FPMUL(v1[0],dist),t);
			vbuffery[zlvertex] = 120 - FPDIV(FPMUL(v1[1],dist),t);
			vbufferz[zlvertex] = v1[2];
		} else
			vvis[zlvertex] = 0;
}

void zlclearscene(void) {
	matrix[0] = 65536;
	matrix[1] = 0;
	matrix[2] = 0;
	matrix[3] = 0;
	matrix[4] = 0;
	matrix[5] = 65536;
	matrix[6] = 0;
	matrix[7] = 0;
	matrix[8] = 0;
	matrix[9] = 0;
	matrix[10] = 65536;
	matrix[11] = 0;
	matrix[12] = 0;
	matrix[13] = 0;
	matrix[14] = 0;
	matrix[15] = 65536;

	zlrotatex(tcamera[3]);
	zlrotatey(tcamera[4]);
	zlrotatez(tcamera[5]);
	zltranslate(-tcamera[0], -tcamera[1], -tcamera[2]);

	tcamera[0] = tcamera[0] + (camera[0] - tcamera[0]) / 4;
	tcamera[1] = tcamera[1] + (camera[1] - tcamera[1]) / 4;
	tcamera[2] = tcamera[2] + (camera[2] - tcamera[2]) / 4;

	Uint8 i;
	Sint32 de;
	for (i = 3; i < 6; i++) {
		camera[i] = camera[i] & 4095;
		if (camera[i] < 0)
			camera[i] = 4095 - camera[i];
		tcamera[i] = tcamera[i] & 4095;
		if (tcamera[i] < 0)
			tcamera[i] = 4095 - tcamera[i];

		de = (camera[i] - tcamera[i]);
		if (de > 2048)
			de = -4096 + de;
		else if (de < -2048)
			de = 4096 + de;
		tcamera[i] += de / 8;
	}

}
