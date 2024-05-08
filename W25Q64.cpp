#include "W25Q64.h"
#include <Arduino.h>

void W25Q64SPI::SPI_Init()
{
    pinMode(W25Q64_CS, OUTPUT);
    pinMode(W25Q64_DO, INPUT);
    pinMode(W25Q64_DI, OUTPUT);
    pinMode(W25Q64_CLK, OUTPUT);

    // Ensure chip select is deactivated initially
    digitalWrite(W25Q64_CS, HIGH);
}

void W25Q64SPI::SPI_W_SS(uint8_t BitValue)
{
    digitalWrite(W25Q64_CS, BitValue ? LOW : HIGH);
}

void W25Q64SPI::SPI_W_SCK(uint8_t BitValue)
{
    digitalWrite(W25Q64_CLK, BitValue ? HIGH : LOW);
}

void W25Q64SPI::SPI_W_MOSI(uint8_t BitValue)
{
    digitalWrite(W25Q64_DI, BitValue ? HIGH : LOW);
}

uint8_t W25Q64SPI::SPI_R_MISO()
{
    return digitalRead(W25Q64_DO);
}

void W25Q64SPI::MySPI_Start()
{
    SPI_W_SS(0);
}

void W25Q64SPI::MySPI_Stop()
{
    SPI_W_SS(1);
}

uint8_t W25Q64SPI::MySPI_ExchangeByte(uint8_t pdata)
{
    uint8_t i;
    uint8_t Data_Receive = 0x00;
    for (i = 0; i < 8; i++)
    {
        Data_Receive <<= 1;
        SPI_W_MOSI(pdata & (0x80 >> i));
        SPI_W_SCK(1);
        Data_Receive |= SPI_R_MISO();
        SPI_W_SCK(0);
    }
    return Data_Receive;
}

void W25Q64SPI::W25Q64_ReadID(uint8_t *MID, uint16_t *DID)
{
    MySPI_ExchangeByte(W25Q64_JEDEC_ID);
    *MID = MySPI_ExchangeByte(W25Q64_DUMMY_BYTE);
    *DID = MySPI_ExchangeByte(W25Q64_DUMMY_BYTE);
    *DID <<= 8;
    *DID |= MySPI_ExchangeByte(W25Q64_DUMMY_BYTE);
}

void W25Q64SPI::W25Q64_WriteEnable()
{
    MySPI_ExchangeByte(W25Q64_WRITE_ENABLE);
}

void W25Q64SPI::W25Q64_WaitBusy()
{
    uint8_t busy = 0;
    uint32_t time = 10000;
    MySPI_ExchangeByte(W25Q64_READ_STATUS_REGISTER_1);
    busy = MySPI_ExchangeByte(W25Q64_DUMMY_BYTE) & 0x01;
    while (busy && time)
    {
        time--;
        busy = MySPI_ExchangeByte(W25Q64_DUMMY_BYTE) & 0x01;
    }
}

void W25Q64SPI::W25Q64_PageProgram(uint32_t AddressWrite, uint8_t *DataWrite, uint16_t count)
{
    uint16_t i;
    W25Q64_WriteEnable();
    MySPI_ExchangeByte(W25Q64_PAGE_PROGRAM);
    MySPI_ExchangeByte(AddressWrite >> 16);
    MySPI_ExchangeByte(AddressWrite >> 8);
    MySPI_ExchangeByte(AddressWrite);
    for (i = 0; i < count; i++)
    {
        MySPI_ExchangeByte(*(DataWrite + i));
    }
    W25Q64_WaitBusy();
}

void W25Q64SPI::W25Q64_ReadData(uint32_t AddressRead, uint8_t *DataRead, uint16_t count)
{
    uint32_t i;
    MySPI_ExchangeByte(W25Q64_READ_DATA);
    MySPI_ExchangeByte(AddressRead >> 16);
    MySPI_ExchangeByte(AddressRead >> 8);
    MySPI_ExchangeByte(AddressRead);
    for (i = 0; i < count; i++)
    {
        *(DataRead + i) = MySPI_ExchangeByte(W25Q64_DUMMY_BYTE);
    }
}

void W25Q64SPI::W25Q64_SectorErase(uint32_t AddressErase)
{
    W25Q64_WriteEnable();
    MySPI_Start();
    MySPI_ExchangeByte(W25Q64_SECTOR_ERASE_4KB);
    MySPI_ExchangeByte(AddressErase >> 16);
    MySPI_ExchangeByte(AddressErase >> 8);
    MySPI_ExchangeByte(AddressErase);
    MySPI_Stop();
    W25Q64_WaitBusy();
}