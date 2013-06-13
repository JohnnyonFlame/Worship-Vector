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

extern void InitGameCore(void);
extern void GameCoreTick(void);
extern void ShutDownCore(void);

extern void PlayMusic(unsigned char itrack);
extern void PlaySound(unsigned char ibank, signed char pan);
extern void PlaySoundEx(unsigned char ibank, signed char pan);
extern void SetVolume(unsigned char volume);
extern void LoadSound(void);
void FreeSound(void);

extern Sint8 olddpad;
