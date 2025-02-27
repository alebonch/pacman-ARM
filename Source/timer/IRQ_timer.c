/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           IRQ_timer.c
** Last modified Date:  2014-09-25
** Last Version:        V1.00
** Descriptions:        functions to manage T0 and T1 interrupts
** Correlated files:    timer.h
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
#include <string.h>
#include "LPC17xx.h"
#include "timer.h"
#include "../GLCD/GLCD.h" 
#include "../TouchPanel/TouchPanel.h"
#include "../Imports//imports.h"
#include <stdio.h> 

/******************************************************************************
** Function name:  Timer0_IRQHandler
**
** Descriptions:  Timer/Counter 0 interrupt handler
**
** parameters:   None
** Returned value:  None
**
******************************************************************************/

extern char direction, startup, timeToExpel, stateOfGame, respawn, step, paused;
extern char buffer[100];
char state;
extern uint8_t elapsed_time, button_down;
extern uint8_t wait;
	
int frequencies_pacman[45] = {410, 467, 523, 576, 627, 673, 714, 749, 778,
    799, 813, 819, 817, 807, 789, 764, 732, 694, 
    650, 602, 550, 495, 438, 381, 324, 270, 217,
    169, 125, 87 , 55 , 30 , 12 , 2  , 0  , 6  ,   
    20 , 41 , 70 , 105, 146, 193, 243, 297, 353} ;
void TIMER0_IRQHandler (void)
{
	static int i = 0;
		int currentValue;
		currentValue = frequencies_pacman[i];
		currentValue -= 410;
		currentValue /= 1;
		currentValue += 410;
		LPC_DAC->DACR = frequencies_pacman[i] <<6;
		i++;
		if(i==45) i=0;
		state=0;
  LPC_TIM0->IR = 1;   /* clear interrupt flag */
  return;
}


/******************************************************************************
** Function name:  Timer1_IRQHandler
**
** Descriptions:  Timer/Counter 1 interrupt handler
**
** parameters:   None
** Returned value:  None
**
******************************************************************************/
void TIMER1_IRQHandler (void)
{
	elapsed_time++;
	if(!startup){
		if(elapsed_time==GAME_DURATION){
			sprintf(buffer, "%d", elapsed_time);
			GUI_Text(208, 0, (uint8_t *) buffer, Red, Black);
			GameOver();
		}
	if(stateOfGame==2 && elapsed_time ==timeToExpel){
	stateOfGame=1;
	}
	if(elapsed_time==respawn){
	respawnBlinky();
	}
	if(elapsed_time == wait) Generate_Power_Pills_Coord();
	}
	LPC_TIM1->IR = 1;   /* clear interrupt flag */
  return;
}
void TIMER2_IRQHandler (void)
{
	
	disable_timer(0);
	
	LPC_TIM2->IR = 1;   /* clear interrupt flag */
  return;
}

void TIMER3_IRQHandler (void){
	static int up = 0, down = 0, left = 0, right = 0, counter = 0;
	uint8_t treshhold;
		
	if(!paused){
	if(stateOfGame!=DEAD){
	if(stateOfGame ==chase){
		if (elapsed_time >= 0 && elapsed_time < 20){
					treshhold = 2;
				}
				else{
					treshhold = 1;
				}
			}
			else{
				treshhold = 3;
			}
	if (counter >= treshhold & stateOfGame!=4) {
				MoveBlinky();
				counter = 0; 
			}
			else{
				counter++;
			}
		}
	collisionManager();
 if((LPC_GPIO1->FIOPIN & (1<<29)) == 0){ 
  /* Joytick UP pressed */
  up++;
  switch(up){
   case 1:
    direction = 2;
		
    break;
   /*
   case 60: //3sec = 3000ms/50ms = 60
    LED_Off(position);
    LED_On(7);
    position = 7;
    break;
   */
   default:
    break;
  }
 }
 else{
   up=0;
 }
 
 if((LPC_GPIO1->FIOPIN & (1<<28)) == 0){ 
  /* Joytick right pressed */
  right++;
  switch(right){
   case 1:
    direction = 1;
    break;
   /*
   case 60: //3sec = 3000ms/50ms = 60
    LED_Off(position);
    LED_On(7);
    position = 7;
    break;
   */
   default:
    break;
  }
 }
 else{
   right=0;
 }
 
 if((LPC_GPIO1->FIOPIN & (1<<27)) == 0){ 
  /* Joytick UP pressed */
  left++;
  switch(left){
   case 1:
    direction = 0;
    break;
   /*
   case 60: //3sec = 3000ms/50ms = 60
    LED_Off(position);
    LED_On(7);
    position = 7;
    break;
   */
   default:
    break;
  }
 }
 else{
   left=0;
 }
 
 if((LPC_GPIO1->FIOPIN & (1<<26)) == 0){ 
  /* Joytick UP pressed */
  down++;
  switch(down){
   case 1:
    direction = 3;
    break;
   /*
   case 60: //3sec = 3000ms/50ms = 60
    LED_Off(position);
    LED_On(7);
    position = 7;
    break;
   */
   default:
    break;
  }
 }
 else{
   down=0;
 }
 
 Move_Pacman();
 sendResults();
 collisionManager();
}
	LPC_TIM3->IR = 1;
  return;
}
/******************************************************************************
**                            End Of File
******************************************************************************/