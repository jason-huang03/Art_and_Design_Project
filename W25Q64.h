#ifndef W25Q64SPI_H
#define W25Q64SPI_H

#include <Arduino.h>

// W25Q64: software SPI
// CS: 3, D0: 4, D1: 5, SLK: 6
#define W25Q64_CS 3
#define W25Q64_DO 4
#define W25Q64_DI 5
#define W25Q64_CLK 6

#define W25Q64_WRITE_ENABLE							0x06
#define W25Q64_WRITE_DISABLE						0x04
#define W25Q64_READ_STATUS_REGISTER_1				0x05
#define W25Q64_READ_STATUS_REGISTER_2				0x35
#define W25Q64_WRITE_STATUS_REGISTER				0x01
#define W25Q64_PAGE_PROGRAM							0x02
#define W25Q64_QUAD_PAGE_PROGRAM					0x32
#define W25Q64_BLOCK_ERASE_64KB						0xD8
#define W25Q64_BLOCK_ERASE_32KB						0x52
#define W25Q64_SECTOR_ERASE_4KB						0x20
#define W25Q64_CHIP_ERASE							0xC7
#define W25Q64_ERASE_SUSPEND						0x75
#define W25Q64_ERASE_RESUME							0x7A
#define W25Q64_POWER_DOWN							0xB9
#define W25Q64_HIGH_PERFORMANCE_MODE				0xA3
#define W25Q64_CONTINUOUS_READ_MODE_RESET			0xFF
#define W25Q64_RELEASE_POWER_DOWN_HPM_DEVICE_ID		0xAB
#define W25Q64_MANUFACTURER_DEVICE_ID				0x90
#define W25Q64_READ_UNIQUE_ID						0x4B
#define W25Q64_JEDEC_ID								0x9F
#define W25Q64_READ_DATA							0x03
#define W25Q64_FAST_READ							0x0B
#define W25Q64_FAST_READ_DUAL_OUTPUT				0x3B
#define W25Q64_FAST_READ_DUAL_IO					0xBB
#define W25Q64_FAST_READ_QUAD_OUTPUT				0x6B
#define W25Q64_FAST_READ_QUAD_IO					0xEB
#define W25Q64_OCTAL_WORD_READ_QUAD_IO				0xE3
#define W25Q64_DUMMY_BYTE							0xFF

class W25Q64SPI {
public:
    W25Q64SPI() {};
    void SPI_Init();
    void SPI_W_SS(uint8_t BitValue);
    void SPI_W_SCK(uint8_t BitValue);
    void SPI_W_MOSI(uint8_t BitValue);
    uint8_t SPI_R_MISO();
    void MySPI_Start();
    void MySPI_Stop();
    uint8_t MySPI_ExchangeByte(uint8_t pdata);
    void W25Q64_SectorErase(uint32_t AddressErase);
    void W25Q64_ReadID(uint8_t *MID, uint16_t *DID);
    void W25Q64_WriteEnable();
    void W25Q64_WaitBusy();
    void W25Q64_PageProgram(uint32_t AddressWrite, uint8_t *DataWrite, uint16_t count);
    void W25Q64_ReadData(uint32_t AddressRead, uint8_t *DataRead, uint16_t count);
};

#endif