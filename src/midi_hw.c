#include "mm_midimsgbuilder.h" 

extern void midi_hw_process_msg(MIDIMsg *msg);
extern void midi_hw_signal_sysex_start(char byte);
extern void midi_hw_send_sysex_byte(char byte);
extern void midi_hw_send_sysex_end(char byte);

static MIDIMsgBuilder midiMsgBuilder;

void midi_hw_process_byte(char byte)
{
    switch (MIDIMsgBuilder_update(&midiMsgBuilder,byte)) {
        case MIDIMsgBuilder_Action_NONE:
            break;
        case MIDIMsgBuilder_Action_RCVD_SYSEX_START:
            midi_hw_signal_sysex_start(byte);
            break;
        case MIDIMsgBuilder_Action_RCVD_SYSEX_DATUM:
            midi_hw_send_sysex_byte(byte);
            break;
        case MIDIMsgBuilder_Action_RCVD_SYSEX_END:
            midi_hw_send_sysex_end(byte);
            break;
        case MIDIMsgBuilder_Action_MSG_COMPLETE:
            midi_hw_process_msg(midiMsgBuilder.msg);
            /* The message is not dynamically allocated and so doesn't need to
             * be freed */
            break;
    }
}

void midi_hw_init(void)
{
    MIDIMsgBuilder_init(&midiMsgBuilder);
}
