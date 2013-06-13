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

#include <SDL.h>
#include "types.h"

extern Uint8 scrbuf[76800];
extern Uint8 palette[256][3];
extern Uint8 button[12], vbutton[12], buttonpressed;
extern Sint8 dpad, dpadi;
extern Uint32 count;

extern Sint32 f_sin[4096], f_cos[4096];

extern Uint8 GameLoopEnabled;

extern Uint8 volume, volumedelay, volumepower;

extern Uint8 MusicPlaying, voiceon;

extern Uint8 NextColor0[256], NextColor2[256];
extern Sint8 zl_vibro;
extern Sint32 zl_gsensor[6];

extern Uint32 GameMode, NextGameMode, GameModeEndCount;

extern Sint32 zlvertex, vbufferx[1024], vbuffery[1024], vbufferz[1024],
		vvis[1024];

extern Sint32 camera[6], tcamera[6];

extern Sint32 cursorx, cursory, cursormodecount;
extern Uint8 cursormode;

extern Uint8 map[64][64], mapunlock[8][8];
extern Sint8 mapz[65][65];
extern Sint32 turret0[64][64], turret1[64][64];
extern Uint8 wave;
extern Sint32 funds;

extern char s_textstring[128];
extern Sint8 l_textstring;
extern Uint8 dpadpower;

extern Uint8 cursorvisual, menuitem, towermenu;
extern Sint32 funds, cost, gamespeed;

extern Sint32 aimap[32][32], dirmap[32][32], spawnx, spawny;
extern Sint32 bullet[128][16], vline[128][16], mob[128][16], newvline[16],
		newbullet[16];

extern Uint8 soundon, musicon, screenblend;

extern Uint16 wavedelay, mobdelay, wavemobleft;
extern Sint32 iwavedata[100][8];

extern Uint8 lives;

extern Sint32 debug_v[16];
