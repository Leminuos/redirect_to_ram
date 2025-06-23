#ifndef __HAL_SPI__
#define __HAL_SPI__

#include <stdint.h>
#include "stm32f103.h"
#include "stm32_hal_util.h"

typedef enum {
   NSS_HARDWARE = 0x00,
   NSS_SOFT = 0x01,
} SPI_NSS;

/* If the SPI peripheral, that microcontroller is getting 50MHz of a peripheral clock, then the
   maximum speed of a peripheral clock is 25Mbps. Because the maximum speed of the peripheral clock is
   divided by 2 (fPCLK/2). Hence, SPI works over a shorter distance but at a higher data rate or higher speed. */

typedef enum {
   FPCLK2   = 0x00,
   FPCLK4   = 0x01,
   FPCLK8   = 0x02,
   FPCLK16  = 0x03,
   FPCLK32  = 0x04,
   FPCLK64  = 0x05,
   FPCLK128 = 0x06,
   FPCLK256 = 0x07,
} SPI_Baudrate;

typedef enum {
   MODE0    = 0x00,
   MODE1    = 0x01,
   MODE2    = 0x02,
   MODE3    = 0x03,
} SPI_ClockMode;

typedef enum {
   DATA8BIT_MSB_FIRST   = 0x0000,
   DATA8BIT_LSB_FIRST   = 0x0080,
   DATA16BIT_MSB_FIRST  = 0x0800,
   DATA16BIT_LSB_FIRST  = 0x0880,
} SPI_FrameFormat;

typedef enum {
   SPI_DIRECTION_FULLDUPLEX                  ,     // BIDIMODE=0 and RXONLY=0
   SPI_DIRECTION_RECEIVE_ONLY                ,     // BIDIMODE=0 and RXONLY=1
   SPI_DIRECTION_HALFDUPLEX_RECEIVE_ONLY     ,     // BIDIMODE=1 and BIDIOE=0
   SPI_DIRECTION_HALFDUPLEX_TRANSMIT_ONLY    ,     // BIDIMODE=1 and BIDIOE=1
} SPI_Direction;

#define SPI_FLAG_RXNE                        BIT0
#define SPI_FLAG_TXE                         BIT1
#define SPI_FLAG_CHSIDE                      BIT2
#define SPI_FLAG_UDR                         BIT3
#define SPI_FLAG_CRCERR                      BIT4
#define SPI_FLAG_MODF                        BIT5
#define SPI_FLAG_OVR                         BIT6
#define SPI_FLAG_BSY                         BIT7

#define SPI_CHK_FLAG(__INSTANCE__, __FLAG__) ((((__INSTANCE__)->SR.REG & (__FLAG__)) == (__FLAG__)) ? SET : RESET)

/* SPE (SPI Enable): Bật hoặc tắt SPI
   + SPE = 0: SPI tắt.
   + SPE = 1: SPI bật. */
#define SPI_PERIPHERAL_ENABLE(__INSTANCE__)  ((__INSTANCE__)->CR1.BITS.SPE = SET)
#define SPI_PERIPHERAL_DISABLE(__INSTANCE__) ((__INSTANCE__)->CR1.BITS.SPE = RESET)

/* CRCEN (Hardware CRC Enable): Bật chế độ kiểm tra CRC dùng để kiểm tra lỗi trong giao tiếp SPI.
   + CRCEN = 0: Không dùng CRC.
   + CRCEN = 1: Bật kiểm tra CRC. */
#define SPI_CRC_ENABLE(__INSTANCE__)         ((__INSTANCE__)->CR1.BITS.CRCEN = SET)
#define SPI_CRC_DISABLE(__INSTANCE__)        ((__INSTANCE__)->CR1.BITS.CRCEN = RESET)

/* MSTR (Master Selection): Chọn chế độ Master hoặc Slave
+ MSTR = 0: Chế độ Slave.
+ MSTR = 1: Chế độ Master.*/
#define SPI_SLAVE_SELECTION(__INSTANCE__)    ((__INSTANCE__)->CR1.BITS.MSTR = RESET)
#define SPI_MASTER_SELECTION(__INSTANCE__)         \
do {                                       \
   ((__INSTANCE__)->CR1.BITS.MSTR = SET);  \
   ((__INSTANCE__)->CR1.BITS.SSI = SET);   \
} while(0)                                 \

#define SPI_SOFTWARE_NSS(__INSTANCE__)       ((__INSTANCE__)->CR1.BITS.SSM = SET)
#define SPI_HARDWARE_NSS(__INSTANCE__)       ((__INSTANCE__)->CR1.BITS.SSM = RESET)
#define SPI_SELECT_SLAVE(__INSTANCE__)       ((__INSTANCE__)->CR1.BITS.SSI = RESET)
#define SPI_DESELECT_SLAVE(__INSTANCE__)     ((__INSTANCE__)->CR1.BITS.SSI = SET)
#define SPI_ACTIVE(__INSTANCE__)             ((__INSTANCE__)->I2SCFGR.BITS.I2SMOD = RESET)

uint8_t SPI_ReadByte(SPI_Typedef* xSpi);
void SPI_SendByte(SPI_Typedef* xSpi, uint8_t data);
void SPI_SetupNSS(SPI_Typedef* xSpi, SPI_NSS Config);
void SPI_CRC_Polynomial(SPI_Typedef* xSpi, uint16_t val);
void SPI_SetupBaudrate(SPI_Typedef* xSpi, SPI_Baudrate Baudrate);
void SPI_SetupClockMode(SPI_Typedef* xSpi, SPI_ClockMode Mode);
void SPI_SetupFrameFormat(SPI_Typedef* xSpi, SPI_FrameFormat Format);

#endif /* __HAL_SPI__ */
