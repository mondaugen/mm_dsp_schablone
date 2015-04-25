#ifndef MIDI_HW_H
#define MIDI_HW_H 

#include "mm_midimsg.h" 

/* The type
 * midi_hw_err_t
 * must be defined by the hardware implementation.
 */

/* This function processes a MIDIMsg provided by midi_hw_process_byte. This is
 * where you get the midi into your program so you can do stuff with it. */
extern void midi_hw_process_msg(MIDIMsg *msg);

/* Defined in midi_hw.c. Calls a method midi_hw_process_msg(MIDIMsg *msg) which
 * must be defined by the application. */
void midi_hw_process_byte(char byte);

/* This must be defined by the current hardware implementation and provide bytes
 * by calling midi_hw_process_byte(byte). This can be called from either the
 * application or the hardware implementation. */
extern void midi_hw_process_input(midi_hw_process_t *params);

/* This initializes the midi_hw processes and must be called either within or
 * after midi_hw_setup() */
void midi_hw_init(void);

/* midi_hw_setup must be defined by the hardware implementation to set up the
 * hardware providing MIDI with data. It should call midi_hw_init if it is not
 * called afterward. It should also be called by the application to set up the
 * MIDI. */
extern midi_hw_err_t midi_hw_setup(midi_hw_setup_t *params);

/* midi_hw_cleanup must be defined by the hardware implementation to clean up
 * the hardware when shutting down */
extern midi_hw_err_t midi_hw_cleanup(midi_hw_cleanup_t *params);

#endif /* MIDI_HW_H */
