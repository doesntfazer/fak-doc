#include "spi.h"
#include "ch55x.h"

void SPI_init() {
    // Set up SPI peripheral
    // Configure SPI pins, SPI clock rate, etc.
    // Example setup for CH55x
    // Set pins for SPI
    P1_DIR_PU &= ~0x80;  // Set P1.7 as SCK
    P1_DIR_PU &= ~0x40;  // Set P1.6 as MISO
    P1_DIR_PU &= ~0x20;  // Set P1.5 as MOSI
    P1_DIR_PU &= ~0x10;  // Set P1.4 as SS

    // Configure SPI control register
    SPCON = 0x50;  // Example configuration: Master mode, Fosc/4
}

void SPI_send(uint8_t data) {
    SPDAT = data;
    while (!(SPSTAT & 0x80));  // Wait for transmission to complete
    SPSTAT = 0x80;  // Clear the SPIF flag
}

uint8_t SPI_receive() {
    SPI_send(0xFF);  // Send dummy data to receive
    while (!(SPSTAT & 0x80));  // Wait for reception to complete
    SPSTAT = 0x80;  // Clear the SPIF flag
    return SPDAT;
}