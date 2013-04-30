#ifndef SPO2_H
#define SPO2_H

/* MEDLAB MARKER BYTES */
#define WAVE_MARKER              0xF8 
#define SPO2_MARKER              0xF9
#define PULSE_MARKER             0xFA
#define INFO_MARKER              0xFB
#define QUALITY_PERFUSION_MARKER 0xFC
/* aliases for markers */
#define WAVE 0xF8
#define SPO2 0xF9
#define PULSE 0xFA
#define INFO 0xFB
#define QP 0xFC

/* MEDLAB INFO BYTES */
#define OK                 0x00
#define SENSOR_DISCONNECT  0x01
#define NO_FINGER          0x02
#define LOW_PERFUSION      0x03
#define SELFTEST_ERROR     0x45

#define PERFUSION_VAL(X) ((X) & 0x70)
#define QUALITY_VAL(X)   ((X) & 0x0F)

#define SPO2_INDEX(SIG) ((SIG) - WAVE_MARKER)

/* states */
#define IDLE 0x00
#define UPDATE_DATA 0x01

#endif
