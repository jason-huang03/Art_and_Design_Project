#include "W25Q64_cp.h"
#include "wire.h"

void W25Q64SPI_cp::W25Q64_Init()
{
    SPI.begin();
    SPI.setClockDivider(SPI_CLOCK_DIV2);
    SPI.setBitOrder(MSBFIRST);
    SPI.setDataMode(SPI_MODE0);
}

void W25Q64SPI_cp::W25Q64_Busy()
{
    uint8_t status;
    CS_LOW;
    SPI.transfer(W25Q64_READ_STATUS_REGISTER_1);
    status = SPI.transfer(W25Q64_DUMMY_BYTE);
    CS_HIGH;
    while (status & 0x01)
    {
        CS_LOW;
        SPI.transfer(W25Q64_READ_STATUS_REGISTER_1);
        status = SPI.transfer(W25Q64_DUMMY_BYTE);
        CS_HIGH;
    }
}

void W25Q64SPI_cp::W25Q64_WriteEnable()
{
    W25Q64_Busy();
    CS_LOW;
    SPI.transfer(W25Q64_WRITE_ENABLE);
    CS_HIGH;
}

void W25Q64SPI_cp::W25Q64_SectorErase(uint32_t SectorNum)
{
    W25Q64_Busy();
    W25Q64_WriteEnable();
    CS_LOW;
    SPI.transfer(W25Q64_SECTOR_ERASE_4KB);
    SPI.transfer((SectorNum & 0xFF0000) >> 16);
    SPI.transfer((SectorNum & 0xFF00) >> 8);
    SPI.transfer(SectorNum & 0xFF);
    CS_HIGH;
}

void W25Q64SPI_cp::W25Q64_WritePage(uint8_t *date, uint32_t PageNum)
{
    W25Q64_Busy();
    W25Q64_WriteEnable();
    Serial.print("1");
    CS_LOW;
    SPI.transfer(W25Q64_PAGE_PROGRAM);
    Serial.print("2");
    SPI.transfer((PageNum & 0xFF0000) >> 16);
    SPI.transfer((PageNum & 0xFF00) >> 8);
    SPI.transfer(PageNum & 0xFF);
    Serial.print("3");
    for (uint8_t i = 0; i < 10; i++)
    {
        SPI.transfer(date[i]);
        Serial.print("send");
        Serial.print(date[i]);
        Serial.println();
    }
    CS_HIGH;
}

void W25Q64SPI_cp::W25Q64_ReadData(uint8_t *rdate, uint32_t addr, uint32_t len)
{
    W25Q64_Busy();
    CS_LOW;
    SPI.transfer(W25Q64_READ_DATA);
    SPI.transfer((addr & 0xFF0000) >> 16);
    SPI.transfer((addr & 0xFF00) >> 8);
    SPI.transfer(addr & 0xFF);
    for (uint32_t i = 0; i < len; i++)
    {
        rdate[i] = SPI.transfer(W25Q64_DUMMY_BYTE);
    }
    CS_HIGH;
}