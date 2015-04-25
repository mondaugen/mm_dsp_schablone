#include "mm_midimsgbuilder.h" 

static MIDIMsgBuilder midiMsgBuilder;

void midi_hw_process_byte(char byte)
{
    switch (MIDIMsgBuilder_update(&midiMsgBuilder,byte)) {
        case MIDIMsgBuilder_State_WAIT_STATUS:
            break;
        case MIDIMsgBuilder_State_WAIT_DATA:
            break;
        case MIDIMsgBuilder_State_COMPLETE:
            midi_hw_process_msg(midiMsgBuilder.msg);
            MIDIMsgBuilder_init(&midiMsgBuilder); /* reset builder */
            break;
        default:
            break;
    }
}

void midi_hw_init(void)
{
    MIDIMsgBuilder_init(&midiMsgBuilder);
}
