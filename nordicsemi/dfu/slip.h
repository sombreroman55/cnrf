/* slip.h
 * Header for SLIP packet structures as well as encoding/decoding
 */
#ifndef _SLIP_H_
#define _SLIP_H_

#include <stdint.h>
#include "errors.h"

#ifdef __cplusplus
extern "C" {
#endif

/* SLIP protocol special characters */
#define SLIP_BYTE_END       0300
#define SLIP_BYTE_ESC       0333
#define SLIP_BYTE_ESC_END   0334
#define SLIP_BYTE_ESC_ESC   0335

typedef enum
{
    SLIP_STATE_DECODING,                /* Ready to receive next byte */
    SLIP_STATE_ESC_RECEIVED,            /* Escape byte received */
    SLIP_STATE_CLEARING_INVALID_PACKET  /* Protocol violation occured */
} slip_state_t;

/* Struct representation of SLIP packet */
typedef struct
{
    slip_state_t state = SLIP_STATE_DECODING; /* Initial state should be set to DECODING */
    uint8_t*     slip_buffer;
    uint32_t     current_index;
    uint32_t     buffer_size;
} slip_t;

return_code_t slip_encode (uint8_t* input_buffer, uint32_t input_len, uint8_t* output_buffer, uint32_t* output_len);
return_code_t slip_decode_byte (slip_t* slip_packet, uint8_t byte);

#ifdef __cplusplus
}
#endif

#endif /* _SLIP_H_ */
