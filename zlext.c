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

//Vibration

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <unistd.h>

#include "zlext/simple_isa1200if.h"

#define DEVICE_FILENAME "/dev/isa1200"
int fd;
void zlInitVibe(void) {
	fd = open(DEVICE_FILENAME, O_RDWR | O_NDELAY);
	ioctl(fd, IOCTL_MOTOR_DRV_ENABLE);
//ioctl(fd, IOCTL_SET_VIB_LEVEL, VIB_LEVEL_MAX);
}
pattern_data_t vibedata = { .act_number = 4, .vib_act_array = { { 0, 126 }, {
		10, 126 }, { 20, 126 }, { 30, -126 } } };
void zlProcVibe(void) {
	if (zl_vibro > -64)
		zl_vibro -= 20;
	if (zl_vibro > -64) {
		vibedata.vib_act_array[0].vib_strength = zl_vibro;
		vibedata.vib_act_array[1].vib_strength = zl_vibro;
		vibedata.vib_act_array[2].vib_strength = zl_vibro;
		ioctl(fd, IOCTL_PLAY_PATTERN, &(vibedata));
	}
}

void zlShutDownVibe(void) {
	ioctl(fd, IOCTL_MOTOR_DRV_DISABLE);
	close(fd);
}

// G-SENSOR

#include "zlext/te9_tf9_hybrid_driver.h"
//#include "zlext/te9_tf9_main.h"
#include "zlext/te9_tf9_regs.h"
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

#include <sys/wait.h>
#include <sys/poll.h>
#include <signal.h>
#include <errno.h>

int accel_fd;
struct sigaction sigact, oldact;
int exitIrqChecker = 0;

static void irqChecker_sigHandler(int signo) {
	switch (signo) {
	case SIGIO:
		KIONIX_ACCEL_service_interrupt();
		break;
	case SIGINT:
	case SIGQUIT:
		exitIrqChecker = 1;
		break;
	}
	return;
}

void zlInitGSensor() {
	accel_fd = open("/dev/accel", O_RDWR);
	int oflag;
	/*

	 sigact.sa_handler = irqChecker_sigHandler;
	 sigemptyset(&sigact.sa_mask);
	 sigact.sa_flags=SA_INTERRUPT;
	 sigaction(SIGIO,&sigact,&oldact);
	 */
	fcntl(accel_fd, F_SETOWN, getpid());
	oflag = fcntl(accel_fd, F_GETFL);
	fcntl(accel_fd, F_SETFL, oflag | FASYNC);

	KIONIX_ACCEL_init();
}

void zlProcGSensor() {
	static ACCEL_XYZ accel_val;

	KIONIX_ACCEL_enable_outputs();
	/*
	 KIONIX_ACCEL_read_LPF_cnt(&accel_val.x, &accel_val.y, &accel_val.z);
	 debug_v[0]=accel_val.x;
	 debug_v[1]=accel_val.y;
	 debug_v[2]=accel_val.z;
	 */
	int x, y, z, ix, iy, iz;

	KIONIX_ACCEL_read_LPF_g(&x, &y, &z);

	ix = x - zl_gsensor[0];
	iy = y - zl_gsensor[1];
	iz = z - zl_gsensor[2];

	zl_gsensor[0] = x;
	zl_gsensor[1] = y;
	zl_gsensor[2] = z;

	int gsensor_filter = 40;

	if (abs(ix) < gsensor_filter)
		ix = 0;
	if (abs(iy) < gsensor_filter)
		iy = 0;
	if (abs(iz) < gsensor_filter)
		iz = 0;

	zl_gsensor[3] = zl_gsensor[3] + (ix - zl_gsensor[3]) / 4;
	zl_gsensor[4] = zl_gsensor[4] + (iy - zl_gsensor[4]) / 4;
	zl_gsensor[5] = zl_gsensor[5] + (iz - zl_gsensor[5]) / 4;

	int gsensor_filter0 = 5;

	if (abs(zl_gsensor[3]) < gsensor_filter0)
		zl_gsensor[3] = 0;
	if (abs(zl_gsensor[4]) < gsensor_filter0)
		zl_gsensor[4] = 0;
	if (abs(zl_gsensor[5]) < gsensor_filter0)
		zl_gsensor[5] = 0;

}
void zlShutDownGSensor() {
	KIONIX_ACCEL_deinit();
	close(accel_fd);
}

//

void zlExtInit(void) {
	zlInitVibe();
	zlInitGSensor();
}
void zlExtFrame(void) {
	zlProcGSensor();
	zlProcVibe();
}

void zlExtShutDown(void) {
	zlShutDownVibe();
	zlShutDownGSensor();
}
