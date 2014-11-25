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

#include <SDL_mixer.h>
#include <string.h>
#include <SDL.h>

#include "vars.h"
#include "ssystem.h"
#include "palette.h"
#include "zmath.h"

#ifdef GP2X
#include "zlext.h"
#include "sys/mman.h"
#include "fcntl.h"

volatile unsigned short *MEM_REG;
unsigned long gp2x_dev=0;

void RamHack(void) //I't me! RamHack!
{
}
#endif
void Terminate(void) {
	FreeSound();
	Mix_CloseAudio();
	SDL_Quit();
#ifdef GP2X
	chdir("/usr/gp2x");
	execl("/usr/gp2x/gp2xmenu", "/usr/gp2x/gp2xmenu", NULL);
#endif
}

SDL_Surface *screen = NULL;
SDL_Joystick *joy = NULL;

Uint8 d_sound_count = 0;
int audio_channels = 1;
int audio_rate = 22050;

Uint16 audio_format;
int audio_buffers;

void InitGameCore(void) {
	InitMath();
	atexit(Terminate);

#ifdef GP2X
	RamHack();
#endif

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_JOYSTICK) < 0) {
		fprintf(stderr, "Couldn't initialize SDL: %s\n", SDL_GetError());
		exit(1);
	}

	if (Mix_QuerySpec(&audio_rate, &audio_format, &audio_channels)) {
		printf("Mix_QuerySpec: %s\n", Mix_GetError());
	}

	if (Mix_OpenAudio(audio_rate, audio_format, audio_channels,
			audio_buffers)) {
		printf("Unable to open audio!\n");
		exit(1);
	}

#ifdef GP2X
	SDL_ShowCursor(SDL_DISABLE);
	screen = SDL_SetVideoMode (320, 240, 8, SDL_HWSURFACE | SDL_DOUBLEBUF);
#endif

#if defined(WIN32) || defined(GCW) || defined(LINUX)
	SDL_ShowCursor(SDL_DISABLE);
	screen = SDL_SetVideoMode (320, 240, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
	//screen = SDL_SetVideoMode (640 ,480, 32, SDL_HWSURFACE | SDL_FULLSCREEN);
#endif
	InitPalette();
#ifdef GP2X
	Uint16 i;
	for (i=0;i<256;i++)
	{
		screen->format->palette->colors[i].r=palette[i][0];
		screen->format->palette->colors[i].g=palette[i][1];
		screen->format->palette->colors[i].b=palette[i][2];
	}
	SDL_SetColors(screen,screen->format->palette->colors,0,256);
#endif

	/* Check and open joystick device */
	if (SDL_NumJoysticks() > 0) {
		joy = SDL_JoystickOpen(0);
		if (!joy) {
			fprintf(stderr, "Couldn't open joystick 0: %s\n", SDL_GetError());
		}
	}
	LoadSound();
	SetVolume(volume);
#ifdef GP2X
	zlExtInit();
#endif
}

#define AXIS_DEADZONE 7000
static const Sint8 angle_detection[9] = { 7, 0, 1, 6, -1, 2, 5, 4, 3 };
int i_keyb[23];
static const SDLKey sd_keyb[23] = { SDLK_KP8, SDLK_KP9, SDLK_KP6, SDLK_KP3,
		SDLK_KP2, SDLK_KP1, SDLK_KP4, SDLK_KP7, SDLK_LCTRL, SDLK_LALT,
		SDLK_LSHIFT, SDLK_SPACE, SDLK_TAB, SDLK_BACKSPACE, SDLK_MINUS,
		SDLK_EQUALS, SDLK_ESCAPE, SDLK_1, SDLK_t, SDLK_UP, SDLK_RIGHT,
		SDLK_DOWN, SDLK_LEFT };
/*static const SDLKey sd_keyb[23]={SDLK_KP8,SDLK_KP9,SDLK_KP6,SDLK_KP3,SDLK_KP2,SDLK_KP1,SDLK_KP4,SDLK_KP7,
 * SDLK_SPACE,SDLK_q,SDLK_c,SDLK_a,SDLK_z,SDLK_x,SDLK_MINUS,SDLK_EQUALS,SDLK_ESCAPE,SDLK_TAB,SDLK_t,SDLK_UP,SDLK_RIGHT,SDLK_DOWN,SDLK_LEFT
 * };
 */

static const int sd_key_ref[11] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

#ifdef GP2X// GP2X button mapping
enum MAP_KEY
{
	VK_UP , // 0
	VK_UP_LEFT ,// 1
	VK_LEFT ,// 2
	VK_DOWN_LEFT ,// 3
	VK_DOWN ,// 4
	VK_DOWN_RIGHT ,// 5
	VK_RIGHT ,// 6
	VK_UP_RIGHT ,// 7
	VK_START ,// 8
	VK_SELECT ,// 9
	VK_FL ,// 10
	VK_FR ,// 11
	VK_FA ,// 12
	VK_FB ,// 13
	VK_FX ,// 14
	VK_FY ,// 15
	VK_VOL_UP ,// 16
	VK_VOL_DOWN ,// 17
	VK_FZ// 18 :)
};
#endif
#if defined(WIN32) || defined(GCW) || defined(LINUX)// WIN button mapping
enum MAP_KEY
{
	VK_FA , // 0
	VK_FX ,// 1
	VK_FB ,// 2
	VK_FY ,// 3
	VK_VOL_DOWN ,// 4
	VK_VOL_UP ,// 5
	VK_FL ,// 6
	VK_FR ,// 7
	VK_SELECT ,// 8
	VK_START ,// 9
	VK_FZ// 10
};
#endif

Sint8 olddpad = -1;

void CoreProcInput(void) {
	int i;
	SDL_JoystickUpdate();
	/*
	 * button[0]=SDL_JoystickGetButton(joy,VK_FA);
	 * button[1]=SDL_JoystickGetButton(joy,VK_FX);
	 * button[2]=SDL_JoystickGetButton(joy,VK_FB);
	 * button[3]=SDL_JoystickGetButton(joy,VK_FY);
	 * button[4]=SDL_JoystickGetButton(joy,VK_FL);
	 * button[5]=SDL_JoystickGetButton(joy,VK_FR);
	 * button[6]=SDL_JoystickGetButton(joy,VK_VOL_DOWN);
	 * button[7]=SDL_JoystickGetButton(joy,VK_VOL_UP);
	 * button[8]=SDL_JoystickGetButton(joy,VK_START);
	 * button[9]=SDL_JoystickGetButton(joy,VK_SELECT);
	 */
	//AXBYLR-+SS
	button[0] = SDL_JoystickGetButton(joy, 0);
	button[1] = SDL_JoystickGetButton(joy, 1);
	button[2] = SDL_JoystickGetButton(joy, 2);
	button[3] = SDL_JoystickGetButton(joy, 3);
	button[4] = SDL_JoystickGetButton(joy, 4);
	button[5] = SDL_JoystickGetButton(joy, 5);
	//button[6]=SDL_JoystickGetButton(joy,VK_VOL_DOWN);
	//button[7]=SDL_JoystickGetButton(joy,VK_VOL_UP);
	button[8] = SDL_JoystickGetButton(joy, 6);
	//button[9]=SDL_JoystickGetButton(joy,VK_SELECT);

	dpad = -1;
	Sint16 axis = SDL_JoystickGetAxis(joy, 0);

	Uint8 x = 1;
	if (axis < -AXIS_DEADZONE)
		x = 0;
	else if (axis > AXIS_DEADZONE)
		x = 2;
	axis = SDL_JoystickGetAxis(joy, 1);
	Uint8 y = 1;
	if (axis < -AXIS_DEADZONE)
		y = 0;
	else if (axis > AXIS_DEADZONE)
		y = 2;

	dpad = angle_detection[x + y * 3];

#if defined(WIN32) || defined(GCW) || defined(LINUX)
	//Keyboard
	SDL_Event event;

	while (SDL_PollEvent (&event))
	{
		switch (event.type)
		{
			case SDL_QUIT:
			GameLoopEnabled=0;
			break;
			case SDL_KEYDOWN:
			for (i=0;i<23;i++)
			if (event.key.keysym.sym==sd_keyb[i])
			i_keyb[i]=1;
			break;
			case SDL_KEYUP:
			for (i=0;i<23;i++)
			if (event.key.keysym.sym==sd_keyb[i])
			i_keyb[i]=0;
			break;

		}
	}
	for (i=0;i<8;i++)
	if (i_keyb[i]) dpad=i;

	if ((i_keyb[0]) & (i_keyb[2])) dpad=1;
	if ((i_keyb[2]) & (i_keyb[4])) dpad=3;
	if ((i_keyb[4]) & (i_keyb[6])) dpad=5;
	if ((i_keyb[6]) & (i_keyb[0])) dpad=7;
	if (i_keyb[19] | i_keyb[20] | i_keyb[21] | i_keyb[22])
	{
		if ((i_keyb[19])&(i_keyb[21]==0)&(i_keyb[20]==0)&(i_keyb[22]==0)) dpad=0;
		else
		if ((i_keyb[20])&(i_keyb[21]==0)&(i_keyb[22]==0)&(i_keyb[19]==0)) dpad=2;
		else
		if ((i_keyb[21])&(i_keyb[22]==0)&(i_keyb[20]==0)&(i_keyb[19]==0)) dpad=4;
		else
		if ((i_keyb[22])&(i_keyb[21]==0)&(i_keyb[20]==0)&(i_keyb[19]==0)) dpad=6;
		else
		if (i_keyb[19] & i_keyb[20]) dpad=1; else
		if (i_keyb[20] & i_keyb[21]) dpad=3; else
		if (i_keyb[21] & i_keyb[22]) dpad=5; else
		if (i_keyb[22] & i_keyb[19]) dpad=7;

	}

	for (i=8;i<19;i++)
	if (i_keyb[i]) button[i-8]=1;

	//printf("key: %i\n",dpadi);

#endif
	/*
	 * #ifdef GP2X
	 * if (SDL_JoystickGetButton(joy,VK_UP)) dpad=0;
	 * else
	 * if (SDL_JoystickGetButton(joy,VK_UP_RIGHT)) dpad=1;
	 * else
	 * if (SDL_JoystickGetButton(joy,VK_RIGHT)) dpad=2;
	 * else
	 * if (SDL_JoystickGetButton(joy,VK_DOWN_RIGHT)) dpad=3;
	 * else
	 * if (SDL_JoystickGetButton(joy,VK_DOWN)) dpad=4;
	 * else
	 * if (SDL_JoystickGetButton(joy,VK_DOWN_LEFT)) dpad=5;
	 * else
	 * if (SDL_JoystickGetButton(joy,VK_LEFT)) dpad=6;
	 * else
	 * if (SDL_JoystickGetButton(joy,VK_UP_LEFT)) dpad=7;
	 * 
	 * 
	 * if ((SDL_JoystickGetButton(joy,VK_UP))&(SDL_JoystickGetButton(joy,VK_RIGHT))) dpad=1;
	 * else
	 * if ((SDL_JoystickGetButton(joy,VK_DOWN))&(SDL_JoystickGetButton(joy,VK_RIGHT))) dpad=3;
	 * else
	 * if ((SDL_JoystickGetButton(joy,VK_DOWN))&(SDL_JoystickGetButton(joy,VK_LEFT))) dpad=5;
	 * else
	 * if ((SDL_JoystickGetButton(joy,VK_UP))&(SDL_JoystickGetButton(joy,VK_LEFT))) dpad=7;
	 * 
	 * #endif
	 */
	//volume control
	if (volumedelay)
		volumedelay--;
	if (button[7]) {
		if (volume + volumepower < 127)
			SetVolume(volume + volumepower);
		else
			SetVolume(127);
		volumedelay = 20;
	} else if (button[6]) {
		if (volume - volumepower > 0)
			SetVolume(volume - volumepower);
		else
			SetVolume(0);
		volumedelay = 20;
	}

	//no more volume control
	dpadi = 0;
	if (olddpad != dpad) {
		if (dpad >= 0)
			dpadi = 1;
	} else
		dpadi = 2;

	olddpad = dpad;

	buttonpressed = 0;
	for (i = 0; i < 12; i++)
		if ((i != 6) & (i != 7)) // ignore volume buttons
				{
			if (button[i] == 0)
				vbutton[i] = 0;
			else if (vbutton[i] < 2)
				vbutton[i]++;
			if (vbutton[i] > buttonpressed)
				buttonpressed = vbutton[i];
		}

// here
//printf("state %i dir:%i\n",dpadi,dpad);
//printf("v:%d, s:%d, m:%d\n", volume, soundon, musicon);

}

#if defined(WIN32) || defined(GCW) || defined(LINUX)
U32 scrbuf2[1228800/4];
#endif

void GameCoreTick(void) {
	CoreProcInput();
#ifdef GP2X
	zlExtFrame();
#endif

	SDL_LockSurface(screen);

#ifdef GP2X
	memcpy(screen->pixels,scrbuf,76800);
#endif

#if defined(WIN32) || defined(GCW) || defined(LINUX)
#if 0
	U32 x,y,i,ii,col;
	U8 c,r,b,g;
	i=0;ii=0;

	for (y=0;y<240;y++)
	{
		for (x=0;x<320;x++)
		{
			c=scrbuf[i++];
			r=palette[c][2];
			g=palette[c][1];
			b=palette[c][0];
			col=b<<16;
			col+=+g<<8;
			col+=r;
			scrbuf2[ii]=col;
			ii++;
		}
	}
	memcpy(screen->pixels,scrbuf2,76800*4);
#endif

	int i, j;
	Uint32 *dest = screen->pixels;
	Uint8  *src  = &scrbuf;
	int t;
	for (j=0; j<240; j++)
		for (i=0; i<320; i++)
		{
			t = *src++;
			*dest++ = palette[t][2] + (palette[t][1]<<8) + (palette[t][0]<<16);
		}
	/*
	 * for (y=0;y<240;y++)
	 * {
	 * for (x=0;x<320;x++)
	 * {
	 * c=scrbuf[i++];
	 * r=palette[c][2];
	 * g=palette[c][1];
	 * b=palette[c][0];
	 * col=b<<16;
	 * col+=+g<<8;
	 * col+=r;
	 * scrbuf2[ii]=col;
	 * scrbuf2[ii+1]=col;
	 * scrbuf2[ii+640]=col;
	 * scrbuf2[ii+641]=col;
	 * 
	 * ii+=2;
	 }
	 ii+=640;
	 }
	 memcpy(screen->pixels,scrbuf2,1228800);
	 */

#endif

	SDL_UnlockSurface(screen);

	SDL_Flip(screen);

	if (gamespeed > 0)
		SDL_Delay(gamespeed * 10);

	voiceon = 0;
	if (Mix_Playing(0)) {
		//printf("Channel 0 is playing\n");
		voiceon = 1;
	} else {
		//printf("Channel 0 not playing\n");
	}
}

void ShutDownCore(void) {
#ifdef GP2X
	zlExtShutDown();
#endif
}

// SOUND SYSTEM
char spath[128];
Mix_Music *music = NULL;
Mix_Chunk *d_sound[4];
//Mix_Chunk *d_sound[8];
Mix_Chunk *e_sound;

void LoadSound(void) {
	int i;

	d_sound[0] = Mix_LoadWAV("Click.wav");
	d_sound[1] = Mix_LoadWAV("Beep.wav");
	d_sound[2] = Mix_LoadWAV("Order.wav");
	d_sound[3] = Mix_LoadWAV("Victory.wav");

	/*
	 * d_sound[4]=Mix_LoadWAV("data/s4.wav");
	 * d_sound[5]=Mix_LoadWAV("data/s5.wav");
	 * d_sound[6]=Mix_LoadWAV("data/s6.wav");
	 * d_sound[7]=Mix_LoadWAV("data/s7.wav");
	 */

	for (i = 0; i < 4; i++) {
		if (d_sound[i] == NULL) {
			//printf("Sfx %d is NULL!\n", i);
		}
	}

	PlayMusic(0);
}

void FreeSound(void) {
	int i;

	for (i = 0; i < 4; i++) {
		Mix_FreeChunk(d_sound[i]);
		d_sound[i] = NULL;
	}

	if (music != NULL) {
		Mix_FreeMusic(music);
		music = NULL;
	}

	e_sound = NULL;
}

void PlayMusic(unsigned char itrack) {
	if (itrack == 128)
		Mix_PauseMusic();
	else {
		switch (itrack) {
		case 0:
			sprintf(spath, "MainControl.ogg", itrack);
			break;
		case 1:
			sprintf(spath, "DataSmasher.ogg", itrack);
			break;
		case 2:
			sprintf(spath, "Defense.ogg", itrack);
			break;

		}
		if (musicon) {
			if (music != NULL) {
				Mix_FreeMusic(music);
			}
			music = Mix_LoadMUS(spath);
			if (music == NULL) {
				printf("File not found: %s\n", spath);
			}

			if (Mix_PlayMusic(music, -1)) {
				//printf("Music error\n");
			}
		}
	}
	MusicPlaying = itrack;
}
void PlaySound(unsigned char ibank, signed char pan) {
	if (soundon) {
		//	Mix_SetPanning(0,127,127); // according to SDL doc, this works only for 2 channels, not 1 channel like we use
		//	/*
		if (Mix_PlayChannel(-1, d_sound[ibank], 0) == -1) {
			//printf("Sfx error\n");
		}
		//	*/
		//printf("Played %d\n", ibank);
	}
}
void PlaySoundEx(unsigned char ibank, signed char pan) {
	//sprintf(spath,"%i.wav",ibank);
	sprintf(spath, "data/e%i.wav", ibank);
	Mix_SetPanning(0, 127, 127);
	e_sound = Mix_LoadWAV(spath);
	Mix_PlayChannel(-1, e_sound, 0);
}

void SetVolume(unsigned char ivolume) {
	volume = ivolume;
	//printf("sfx %d\n", Mix_Volume(0, -1));
	//Mix_Volume(0,volume);
	//Mix_VolumeMusic(volume);
}
