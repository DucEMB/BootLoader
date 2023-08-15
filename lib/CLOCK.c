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
    MCG->C2 |= MCG_C2_RANGE(1); /* Select the range of OSC frequency as 8MHz */
    MCG->C2 |= MCG_C2_EREFS(1); /* Select the OSC */
    MCG->C5 |= MCG_C5_PRDIV0(3); /* Select the amount to divide of the PLL is 4 */
    MCG->C6 |= MCG_C6_VDIV0(Multiply);  /* Select the amount to multiply of the PLL */
    MCG->C5 |= MCG_C5_PLLCLKEN0_MASK;  /* enable MCGPLLCLK */
    MCG->C1 &= ~MCG_C1_CLKS_MASK; /* Select PLL or FLL as Core Clock */
    MCG->C6 |= MCG_C6_PLLS_MASK; /* Select PLL */
}
/************************** Brief *********************************************
*
    Input: Frequency want to configure in the unsigned long type
    Funtion calculate and configre the PLL to be the core clock with the frequency
    that the user want
    Default is set as 48MHz
**
*******************************************************************************/
