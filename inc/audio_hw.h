#ifndef AUDIO_HW_H
#define AUDIO_HW_H 
/* Declarations for hardware implementation of audio input and output. */

/* The following types must be defined in a header coming before this one:
 * audio_hw_sample_t
 * audio_hw_setup_t
 * audio_hw_err_t
 */
typedef struct __audio_hw_io_t {
    audio_hw_sample_t *in;
    audio_hw_sample_t *out;
    int                length;
    int                nchans_in;
    int                nchans_out;
} audio_hw_io_t;

/* This must be implemented in the application.
 * It should read length*nchans_in values from params->in as input,
 * write values length*nchans_out to params->out.
 * A function, such as an interrupt, should call this function, filling the
 * fields of the audio_hw_io_t struct and passing this struct.
 */
extern void audio_hw_io(audio_hw_io_t *params);

/* This must be implemented by a low level driver and then called by the
 * application to setup the processing of audio.
 */
extern audio_hw_err_t audio_hw_setup(audio_hw_setup_t *params);

/* This must be implemented by a low level driver and start the audio running */
extern audio_hw_err_t audio_hw_start(audio_hw_setup_t *params);

/* This must be implemented and return the sample rate */
unsigned int audio_hw_get_sample_rate(void *data);

/* This must be implemented and return the block size in frames
 * (block_size*nchannels = buffer size) */
unsigned int audio_hw_get_block_size(void *data);

/* This must return the number of input channels */
unsigned int audio_hw_get_num_input_channels(void *data);

/* This must return the number of output channels */
unsigned int audio_hw_get_num_output_channels(void *data);

#endif /* AUDIO_HW_H */
