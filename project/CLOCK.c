#include "CLOCK.h"

void SetCoreClockPLL(uint32 Frequency)
{
    uint8 Multiply;
    switch (Frequency)
    {
        case FREQUENCY48MHZ:
        {
            Multiply = 0;
            break;
        }
        case FREQUENCY60MHZ:
        {
            Multiply = 6;
            break;
        }
        case FREQUENCY72MHZ:
        {
            Multiply = 12;
            break;
        }
        case FREQUENCY96MHZ:
        {
            Multiply = 24;
            break;
        }
        default:
        {
            Multiply = 0;
            break;
        }
    }
    MCG->C2 |= MCG_C2_RANGE(1); /* khoang tan so thach anh la 8MHz */
    MCG->C2 |= MCG_C2_EREFS(1); /* chon thach anh thay vi clock ngoai tu chan chip */
    MCG->C5 |= MCG_C5_PRDIV0(3); /* chon bo chia 4 cho PLL */
    MCG->C6 |= MCG_C6_VDIV0(Multiply);  /* Chon bo nhan cho PLL */
    MCG->C5 |= MCG_C5_PLLCLKEN0_MASK;  /* enable MCGPLLCLK */
    MCG->C1 &= ~MCG_C1_CLKS_MASK; /* Select PLL or FLL as Core Clock */
    MCG->C6 |= MCG_C6_PLLS_MASK; /* Select PLL */
}
