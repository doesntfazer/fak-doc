#include "ch55x.h"
#include "keyboard.h"
#include "spi.h"
#include "time.h"

#ifdef SPLIT_SIDE_CENTRAL
#include "usb.h"

void USB_interrupt();
void USB_ISR() __interrupt(INT_NO_USB) {
    USB_interrupt();
}
#endif

void TMR0_interrupt();
void TMR0_ISR() __interrupt(INT_NO_TMR0) {
    TMR0_interrupt();
}

#if defined(SPLIT_ENABLE) && !defined(SPLIT_SOFT_SERIAL_PIN)
#ifdef SPLIT_SIDE_PERIPHERAL
void UART0_interrupt();
void UART0_ISR() __interrupt(INT_NO_UART0) {
    UART0_interrupt();
}
#endif

static void UART0_init() {
    // UART0 @ Timer1, 750k bps
    SM0 = 0;
    SM1 = 1;
    PCON |= SMOD;

    TMOD = TMOD & ~bT1_GATE & ~bT1_CT & ~MASK_T1_MOD | bT1_M1;
    T2MOD |= bTMR_CLK | bT1_CLK;
#if CH55X == 2
    TH1 = 254;
#elif CH55X == 9
    TH1 = 255;
#endif
    TR1 = 1;
    TI = 1;
}
#endif

static void main() {
    CLK_init();
#if defined(SPLIT_ENABLE) && !defined(SPLIT_SOFT_SERIAL_PIN)
    UART0_init();
#endif
#ifdef SPLIT_SIDE_CENTRAL
    TMR0_init();
    USB_init();
#endif
    SPI_init();  // Add this line
    keyboard_init();
}