#ifndef AL_USART
#define AL_USART

#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#include "stm32f4xx.h"

#include "AL_System.h"

/* Defines */
#define BUFFERSIZE  (128)

/* Typedefs */
typedef struct
{
    uint8_t inPtr;
    uint8_t outPtr;
    uint8_t buffer[BUFFERSIZE];
} USART_BUFFER_t;

typedef enum
{
    USART_ENABLE = 0,
    USART_DISABLE
} USART_MODE_t;

typedef enum
{
    NO_PARITY = 0,
    EVEN_PARITY,
    ODD_PARITY
} USART_PARITY;

typedef enum
{
    LEN_8BIT = 0,
    LEN_9BIT
} USART_WORDLEN;

typedef enum
{
    HALF_BIT        = 0,
    HALF_STOP       = 0,
    ONE_BIT         = 1,
    ONE_STOP        = 1,
    ONE_DOT_FIVE    = 2,
    TWO_BIT         = 3,
    TWO_STOP        = 3
} USART_STOPBITS;

typedef enum
{
    OVER16 = 0,
    OVER8
} USART_OVER;

typedef enum
{
    RECEIVER_OFF = 0,
    RECEIVER_ON
} USART_RX;

typedef enum
{
    TRANSMITTER_OFF = 0,
    TRANSMITTER_ON
} USART_TX;

typedef enum
{
    OFF = 0,
    ON
} USART_IRQ_MODE;

typedef enum
{
    USART_IRQ_TXEIE = 0,
    USART_IRQ_CTSIE,
    USART_IRQ_TCIE,
    USART_IRQ_RXNEIE,
    USART_IRQ_IDLE,
    USART_IRQ_PEIE,
    USART_IRQ_LBDIE,
    USART_IRQ_EIE
} USART_IRQ_TYPES;

typedef enum
{
    USART_CTS_FLG,
    USART_LBD_FLG,
    USART_TC_FLG,
    USART_RXNE_FLG
} USART_IRQ_FLAG_t;

typedef enum
{
    DMA_TRANSMIT_OFF,
    DMA_TRANSMIT_ON
} USART_DMA_TXMODE_t;

typedef enum
{
    DMA_RECEIVE_OFF,
    DMA_RECEIVE_ON
} USART_DMA_RXMode_t;

/* Variables */
USART_BUFFER_t  *receiveBuffer;
USART_BUFFER_t  *transmitBuffer;

/* Function prototypes */

/* General UART/USART activities */
extern void AL_usartSelectUsart(USART_TypeDef *usart);
extern void AL_usartDeselectUsart(USART_TypeDef *usart);
extern void AL_usartEnableUsart(USART_TypeDef *usart);
extern void AL_usartDisableUsart(USART_TypeDef *usart);

/* USART buffer */
extern void AL_usartInitBuffer(void);
extern void AL_usartSendString(USART_TypeDef *usart, char *data);

/* Communication parameters */
extern void AL_usartSetCommParams(USART_TypeDef *usart, uint32_t baudrate,
                               USART_PARITY parity, USART_WORDLEN len,
                               USART_STOPBITS stop);
extern void AL_usartSetBaudrate(USART_TypeDef *usart, uint32_t baudrate);
extern void AL_usartSetWordlength(USART_TypeDef *usart, USART_WORDLEN len);
extern void AL_usartSetParity(USART_TypeDef *usart, USART_PARITY parity);
extern void AL_usartSetNumStopBits(USART_TypeDef *usart, USART_STOPBITS num);
extern void AL_usartSetOversampling(USART_TypeDef *usart, USART_OVER over);
extern void AL_usartEnableReceiver(USART_TypeDef *usart, USART_RX enable);
extern void AL_usartEnableTransmitter(USART_TypeDef *usart, USART_TX enable);

/* Sending and receiving data */
extern void AL_usartGetByte(USART_TypeDef *usart, uint16_t byte);

/* Interrupts */
extern void AL_usartEnableIrqList(USART_TypeDef *usart, USART_IRQ_TYPES *irqList);
extern void AL_usartEnableIrq(USART_TypeDef *usart, USART_IRQ_TYPES irqType);
extern void AL_usartDisableIrq(USART_TypeDef *usart, USART_IRQ_TYPES irqType);
extern void AL_usartResetIrqFlag(USART_TypeDef *usart, USART_IRQ_FLAG_t irqFlag);

/* DMA */
extern void AL_usartSetDmaTxMode(USART_TypeDef *usart, USART_DMA_TXMODE_t dmaMode);
extern void AL_usartSetDmaRxMode(USART_TypeDef *usart, USART_DMA_RXMode_t dmaMode);

#endif
