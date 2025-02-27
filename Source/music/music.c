#include "music.h"
#include "LPC17xx.h"
#include "../timer/timer.h"

void playNote(NOTE note)
{
	if(note.freq != pause)
	{
		reset_timer(0);
		init_timer(0, note.freq);
		enable_timer(0);
	}
	reset_timer(2);
	init_timer(2, note.duration);
	enable_timer(2);
}

BOOL isNotePlaying(void)
{
	return ((LPC_TIM0->TCR != 0));
}
