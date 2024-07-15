#ifndef SPI_H
#define SPI_H

void SPI_init();
void SPI_send(uint8_t data);
uint8_t SPI_receive();

#endif // SPI_H