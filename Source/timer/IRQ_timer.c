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

extern char direction;
extern char buffer[100];
extern uint8_t elapsed_time;
extern uint8_t wait;
void TIMER0_IRQHandler (void)
{
 static int up = 0, down = 0, left = 0, right = 0;
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
	sprintf(buffer, "%d", GAME_DURATION-elapsed_time);
		if(elapsed_time==GAME_DURATION){
			GameOver();
		}
	if(elapsed_time>50){
		Draw_Wall(216,0,Black,8,16);}
	GUI_Text(208, 0, (uint8_t *) buffer, Red, Black);
	if(elapsed_time == wait) Place_Power_Pills();
  LPC_TIM1->IR = 1;   /* clear interrupt flag */
  return;
}

/******************************************************************************
**                            End Of File
******************************************************************************/