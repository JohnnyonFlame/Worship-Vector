#ifndef __POLLUX_SIMPLE_ISA1200_H__
#define __POLLUX_SIMPLE_ISA1200_H__

#define VIB_STRENGTH_MIN	(-126)
#define VIB_STRENGTH_MAX	(126)

struct _vibration_act {
	short time_line;					//millisecond base...
	short vib_strength;					
}__attribute__ ((packed)) ;

typedef struct _vibration_act vibration_act_t;

#define MAX_VIB_ACTION_NR	(120)
struct _pattern_data {
   	int act_number;						//include finish sequence... 
	vibration_act_t vib_act_array[MAX_VIB_ACTION_NR];
};
typedef struct _pattern_data pattern_data_t;
typedef enum {JOB_STATUS_IDLE, JOB_STATUS_BUSY} job_status_t;
typedef enum {VIB_LEVEL_OFF, VIB_LEVEL_WEAK, VIB_LEVEL_NORMAL, VIB_LEVEL_MAX} vibration_level_t;

#define HAPTIC_IOCTL_MAGIC	'I'

//ioctl() commands... 
/* dummy command for old version compatibillity */
#define IOCTL_MOTOR_DRV_ENABLE	_IO(HAPTIC_IOCTL_MAGIC, 0) 
#define IOCTL_MOTOR_DRV_DISABLE	_IO(HAPTIC_IOCTL_MAGIC, 1) 

/* user application interface */
#define IOCTL_FFLUSH_JOB		_IO(HAPTIC_IOCTL_MAGIC, 2)
#define IOCTL_JOB_STATUS		_IOR(HAPTIC_IOCTL_MAGIC, 3, job_status_t)
#define IOCTL_PLAY_PATTERN		_IOW(HAPTIC_IOCTL_MAGIC, 4, pattern_data_t)

//added command for hardware test by lars 2010-06-18...
#define IOCTL_INDIVIDUAL_MODE   _IOW(HAPTIC_IOCTL_MAGIC, 5, unsigned int)	// 1:enable 0:disable
#define IOCTL_ISA1200A_ENABLE   _IO(HAPTIC_IOCTL_MAGIC, 6)
#define IOCTL_ISA1200B_ENABLE   _IO(HAPTIC_IOCTL_MAGIC, 7)
/* Vibration Level Related Commands  */
#define IOCTL_GET_VIB_LEVEL		_IOR(HAPTIC_IOCTL_MAGIC, 8, vibration_level_t)
#define IOCTL_SET_VIB_LEVEL		_IOW(HAPTIC_IOCTL_MAGIC, 9, vibration_level_t)
#define IOCTL_HAPTIC_MAXNR		10	

#endif /* __POLLUX_SIMPLE_ISA1200_H__ */

