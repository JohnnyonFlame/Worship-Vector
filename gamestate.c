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
#include "ssystem.h"

#include "gamestep.h"

#include "mainmenu.h"

void ProcGameState(void) {

	switch (GameMode) {
	case 0: // Logo

		break;
	case 1: //

		break;
	case 2: //

		break;
	case 3: //

		break;
	case 4: //Main menu
		ProcGameMainMenu();
		break;
	case 5: //Epic GamePlay
		GameStep();
		break;
	case 6:
		if (count / 20 % 2 == 0) {
			l_textstring = sprintf(s_textstring, "THANKS FOR PLAYING");
			s_drawtext(80, 120, 15);
		}

		l_textstring = sprintf(s_textstring, "PRESS ANY KEY TO EXIT...");
		s_drawtext(120, 222, 15);

		l_textstring = sprintf(s_textstring, "WORSHIP VECTOR       by Quasist");
		s_drawtext(32, 6, 15);
		DrawRect(0, 0, 320, 30, 15);

		DrawRect(60, 100, 260, 150, 15);

		if (buttonpressed == 1)
			GameLoopEnabled = 0;

		break;
	case 7:

		break;

	}
	GameMode = NextGameMode;
}
