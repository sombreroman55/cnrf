/* slip.c
 * Implementation of SLIP packet encoding/decoding functions
 */
#include "slip.h"
#include "errors.h"

return_code_t slip_encode (uint8_t* input_buffer, uint32_t input_len, uint8_t* output_buffer, uint32_t* output_len)
{
    if (input_buffer == NULL || output_buffer == NULL || output_len == NULL)
    {
        return CNRF_ERROR_NULL;
    }

    *output_len = 0;
    uint32_t i;
    for (i = 0; i < input_len; i++)
    {
        switch (input_buffer[i])
        {
            case SLIP_BYTE_END:
                output_buffer[(*output_len)++] = SLIP_BYTE_ESC;
                output_buffer[(*output_len)++] = SLIP_BYTE_ESC_END;
                break;
            case SLIP_BYTE_ESC:
                output_buffer[(*output_len)++] = SLIP_BYTE_ESC;
                output_buffer[(*output_len)++] = SLIP_BYTE_ESC_ESC;
                break;
            default:
                output_buffer[(*output_len)++] = input_buffer[i];
        }
    }
    output_buffer[(*output_len)++] = SLIP_BYTE_END;
    return CNRF_SUCCESS;
}

return_code_t slip_decode_byte (slip_t* slip_packet, uint8_t byte)
{
    if (slip_packet == NULL)
    {
        return CNRF_ERROR_NULL;
    }

    if (slip_packet->current_index == slip_packet->buffer_size)
    {
        return CNRF_ERROR_NO_MEM;
    }

    switch (slip_packet->state)
    {
        case SLIP_STATE_DECODING:
            switch (c)
            {
                case SLIP_BYTE_END:
                    /* Packet decoded */
                    return CRNF_SUCCESS;
                case SLIP_BYTE_ESC:
                    slip_packet->state = SLIP_STATE_ESC_RECEIVED;
                    break;
                default:
                    slip_packet->slip_buffer[slip_packet->current_index++] = byte;
                    break;
            }
            break;

        case SLIP_STATE_ESC_RECEIVED:
             switch (c)
            {
                case SLIP_BYTE_ESC_END:
                    slip_packet->slip_buffer[slip_packet->current_index++] = SLIP_BYTE_END;
                    slip_packet->state = SLIP_STATE_DECODING;
                    break;
                case SLIP_BYTE_ESC:
                    slip_packet->slip_buffer[slip_packet->current_index++] = SLIP_BYTE_ESC;
                    slip_packet->state = SLIP_STATE_DECODING;
                    break;
                default:
                    /* Protocol violation! */
                    slip_packet->state = SLIP_STATE_CLEARING_INVALID_PACKET;
                    return CNRF_ERROR_INVALID_DATA;
            }
            break;           

        case SLIP_STATE_CLEARING_INVALID_PACKET:
            if (c == SLIP_BYTE_END)
            {
                slip_packet->state = SLIP_STATE_DECODING;
                slip_packet->current_index = 0;
            }
            break;
    }
    return CRNF_ERROR_BUSY;
}
