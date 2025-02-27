/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           IRQ_RIT.c
** Last modified Date:  2014-09-25
** Last Version:        V1.00
** Descriptions:        functions to manage T0 and T1 interrupts
** Correlated files:    RIT.h
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
#include "LPC17xx.h"
#include "RIT.h"
#include "timer.h"
#include "Imports/imports.h"
#include 	"../GLCD/GLCD.h"

/******************************************************************************
** Function name:		RIT_IRQHandler
**
** Descriptions:		REPETITIVE INTERRUPT TIMER handler
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/
NOTE song[] = {
    // First measure (Intro theme)
    {b4, time_croma},        // B4 eighth
    {f4, time_croma},        // F4 eighth
    {d5, time_croma},        // D5 eighth
    {b4, time_croma},        // B4 eighth
    {c5, time_croma},        // C5 eighth
    {g4, time_croma},        // G4 eighth

    // Second measure
    {e4, time_croma},        // E4 eighth
    {g4, time_croma},        // G4 eighth
    {f4, time_croma},        // F4 eighth
    {d4, time_croma},        // D4 eighth
    {b3, time_croma},        // B3 eighth
    {f3, time_croma},        // F3 eighth

    // Third measure (Chase theme)
    {g4, time_croma},        // G4 eighth
    {a4, time_croma},        // A4 eighth
    {b4, time_croma},        // B4 eighth
    {c5, time_croma},        // C5 eighth
    {d5, time_croma},        // D5 eighth
    {f5, time_croma},        // F5 eighth

    // Fourth measure
    {e5, time_croma},        // E5 eighth
    {d5, time_croma},        // D5 eighth
    {c5, time_croma},        // C5 eighth
    {b4, time_croma},        // B4 eighth
    {a4, time_croma},        // A4 eighth
    {g4, time_croma},        // G4 eighth

    // Fifth measure (Power pellet theme)
    {b4, time_croma},        // B4 eighth
    {f4, time_croma},        // F4 eighth
    {g4, time_croma},        // G4 eighth
    {a4, time_croma},        // A4 eighth
    {b4, time_croma},        // B4 eighth
    {c5, time_croma},        // C5 eighth

    // Sixth measure
    {d5, time_croma},        // D5 eighth
    {e5, time_croma},        // E5 eighth
    {f5, time_croma},        // F5 eighth
    {g5, time_croma},        // G5 eighth
    {a5, time_croma},        // A5 eighth
    {b5, time_croma},        // B5 eighth

    // Seventh measure (Ending jingle)
    {f5, time_croma},        // F5 eighth
    {e5, time_croma},        // E5 eighth
    {d5, time_croma},        // D5 eighth
    {c5, time_croma},        // C5 eighth
    {b4, time_croma},        // B4 eighth
    {pause, time_semiminima},// Pause (final note)
};

extern uint8_t button_down;
int currentNote = 0;
int ticks = 0;

void RIT_IRQHandler (void)
{			
			if((LPC_PINCON->PINSEL4 & (1 << 20)) == 0){
				button_down++;
				if((LPC_GPIO2->FIOPIN & (1<<10)) == 0){ 
					
					
					switch(button_down){
						case 1:
							PauseHandler();
							break;
						default:
							break;
					}
				}
				else{    /* button released */
					button_down = 0;
					disable_RIT();
					reset_RIT();
					enable_RIT();
					NVIC_EnableIRQ(EINT0_IRQn);                           
					LPC_PINCON->PINSEL4    |= (1 << 20);     
				}
			}

	if(!isNotePlaying())
	{
		++ticks;
		if(ticks == 1)
		{
			ticks = 0;
			playNote(song[currentNote++]);
		}
	}
	
	if(currentNote == (sizeof(song) / sizeof(song[0])))
	{
		currentNote=0;
	}
	
  LPC_RIT->RICTRL |= 0x1;	/* clear interrupt flag */
	
  return;
}

/******************************************************************************
**                            End Of File
******************************************************************************/
