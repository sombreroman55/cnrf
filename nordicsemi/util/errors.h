/* errors.h
 * Global error codes 
 *
 *
 */

#ifndef _ERRORS_H_
#define _ERRORS_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define CNRF_SUCCESS                        0x00
#define CNRF_ERROR_SVC_HANDLER_MISSING      0x01
#define CNRF_ERROR_SOFTDEVICE_NOT_ENABLED   0x02
#define CNRF_ERROR_INTERNAL                 0x03
#define CNRF_ERROR_NO_MEM                   0x04
#define CNRF_ERROR_NOT_FOUND                0x05
#define CNRF_ERROR_NOT_SUPPORTED            0x06
#define CNRF_ERROR_INVALID_PARAM            0x07
#define CNRF_ERROR_INVALID_STATE            0x08
#define CNRF_ERROR_INVALID_LENGTH           0x09
#define CNRF_ERROR_INVALID_FLAGS            0x0A
#define CNRF_ERROR_INVALID_DATA             0x0B
#define CNRF_ERROR_DATA_SIZE                0x0C
#define CNRF_ERROR_TIMEOUT                  0x0D
#define CNRF_ERROR_NULL                     0x0E
#define CNRF_ERROR_FORBIDDEN                0x0F
#define CNRF_ERROR_INVALID_ADDR             0x10
#define CNRF_ERROR_BUSY                     0x11
#define CNRF_ERROR_CONN_COUNT               0x12
#define CNRF_ERROR_RESOURCES                0x13

typedef uint32_t return_code_t;

#ifdef __cplusplus
}
#endif

#endif  /* _ERRORS_H_ */
