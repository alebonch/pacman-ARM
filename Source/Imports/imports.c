#include "imports.h"
#include "../TouchPanel/TouchPanel.h"
#include "../GLCD/GLCD.h"
#include "stdio.h"
#include "CAN/CAN.h"

		char directions[4][2] = {
    {0, -1}, // LEFT
    {0, 1},  // RIGHT
    {-1, 0}, // UP
    {1, 0}   // DOWN
		};
		char ghost[8][8]= {
        {0, 0, 0, 1, 1, 0, 0, 0}, // Top row
        {0, 0, 1, 1, 1, 1, 0, 0}, 
        {0, 1, 1, 1, 1, 1, 1, 0}, 
        {0, 1, 1, 1, 1, 1, 1, 0}, 
        {0, 1, 1, 1, 1, 1, 1, 0}, 
        {0, 1, 1, 1, 1, 1, 1, 0}, // Legs (teeth-like pattern)
        {0, 1, 1, 1, 1, 1, 1, 0}, 
        {0, 1, 0, 1, 1, 0, 1, 0}  // Bottom row (teeth)
    };
		char eye_sprite[8][8] = {
        {0, 0, 0, 0, 0, 0, 0, 0}, 
        {0, 0, 0, 0, 0, 0, 0, 0}, 
        {0, 0, 1, 0, 0, 1, 0, 0}, 
        {0, 0, 1, 0, 0, 1, 0, 0}, 
        {0, 0, 0, 0, 0, 0, 0, 0}, 
        {0, 0, 0, 0, 0, 0, 0, 0}, 
        {0, 0, 0, 0, 0, 0, 0, 0}, 
        {0, 0, 0, 0, 0, 0, 0, 0}
    };
	char rowDirs[] = {0, 0, -1, 1}; // X: Lateralità
	char colDirs[] = {-1, 1, 0, 0}; // Y: Verticalità
	char life, startup, direction, stateOfGame, timeToExpel, respawn, step, paused, kills;
	char escapeRoute[6]= {UP, UP, RIGHT, RIGHT, UP, UP};
		/*
 0: Vuoto
 1: Muro
 2: Point
 3: Special Point
 4: TP-Left
 5: TP-Right
*/
		char board[HEIGHT][LENGTH] = {
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, 
        {1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1},
        {1, 2, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 2, 1, 1, 2, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 2, 1},
        {1, 2, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 2, 1, 1, 2, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 2, 1},
        {1, 2, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 2, 1, 1, 2, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 2, 1},
        {1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1},
        {1, 2, 1, 1, 1, 1, 2, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 2, 1, 1, 1, 1, 2, 1},
        {1, 2, 1, 1, 1, 1, 2, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 2, 1, 1, 1, 1, 2, 1},
        {1, 2, 2, 2, 2, 2, 2, 1, 1, 2, 2, 2, 2, 1, 1, 2, 2, 2, 2, 1, 1, 2, 2, 2, 2, 2, 2, 1},
        {1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 2, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 2, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 2, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 2, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1},
				{4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5},
        {1, 1, 1, 1, 1, 1, 2, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1}, 
        {1, 1, 1, 1, 1, 1, 2, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 2, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 2, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 2, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 2, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 2, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 2, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 2, 1, 1, 1, 1, 1, 1},
        {1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1},
        {1, 2, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 2, 1, 1, 2, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 2, 1},
        {1, 2, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 2, 1, 1, 2, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 2, 1},
        {1, 2, 2, 2, 1, 1, 2, 2, 2, 2, 2, 2, 2, 0, 2, 2, 2, 2, 2, 2, 2, 2, 1, 1, 2, 2, 2, 1},
        {1, 1, 1, 2, 1, 1, 2, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 2, 1, 1, 2, 1, 1, 1},
        {1, 1, 1, 2, 1, 1, 2, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 2, 1, 1, 2, 1, 1, 1},
        {1, 2, 2, 2, 2, 2, 2, 1, 1, 2, 2, 2, 2, 1, 1, 2, 2, 2, 2, 1, 1, 2, 2, 2, 2, 2, 2, 1},
        {1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1},
        {1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1},
        {1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
    };
		struct pg pacman, blinky;
		uint8_t elapsed_time = 0;
		uint8_t wait = 0;
		uint16_t punteggio;
		char buffer[100];
void InitializeGame(){
 pacman.posX = pacmanStartingX;
 pacman.posY = pacmanStartingY;
 blinky.posX = blinkyStartingX;
 blinky.posY = blinkyStartingY;
 direction=0;
 punteggio=0;
 paused=0;
 kills=0;
 step=0;
 life = 1;
 stateOfGame=0;
 Draw_Map();
 //Generate_Power_Pills_Coord();
 init_timer(3, 0x001C4B40); 						    
 init_timer(1, 0x17D7840); //0x17D7840
 //init_timer(2, 0x17D7840);
 startup = 1;
 elapsed_time = 1;
 PauseHandler();
}
void Draw_Map(){
 int i, j, current_value;
	
 LCD_DrawLine(90, 114, 110, 114, Blue);
 LCD_DrawLine(90, 114, 90, 150, Blue);
 LCD_DrawLine(90, 150, 150, 150, Blue);
 LCD_DrawLine(150, 114, 150, 150, Blue);
 LCD_DrawLine(150, 114, 130, 114, Blue);
 LCD_DrawLine(130, 114, 130, 118, Blue);
 LCD_DrawLine(130, 118, 146, 118, Blue);
 LCD_DrawLine(146, 118, 146, 146, Blue);
 LCD_DrawLine(94, 146, 146, 146, Blue);
 LCD_DrawLine(94, 146, 94, 118, Blue);
 LCD_DrawLine(94, 118, 110, 118, Blue);
 LCD_DrawLine(90, 114, 110, 114, Blue);
 LCD_DrawLine(110, 114, 110, 118, Blue);
 
 
 
 LCD_DrawLine(226, 22, 226, 90, Blue);
 LCD_DrawLine(232, 16, 232, 126, Blue);
 LCD_DrawLine(232, 126, 186, 126, Blue);
 LCD_DrawLine(186, 126, 186, 90, Blue);
 LCD_DrawLine(186, 90, 226, 90, Blue);
 LCD_DrawLine(8, 16, 232, 16, Blue);
 LCD_DrawLine(8,16, 8, 126, Blue);
 LCD_DrawLine(8,126, 54, 126, Blue);
 LCD_DrawLine(54, 126, 54, 90, Blue);
 LCD_DrawLine(54, 90, 14, 90, Blue);
 LCD_DrawLine(14, 90, 14, 22, Blue);
 LCD_DrawLine(14, 22, 114, 22, Blue);
 LCD_DrawLine(114, 22, 114, 54, Blue);
 LCD_DrawLine(126, 22, 226, 22, Blue);
 LCD_DrawLine(126, 22, 126, 54, Blue);
 LCD_DrawLine(126, 54, 114, 54, Blue);
 
 
 
 
 LCD_DrawLine(14, 258, 226, 258, Blue);
 LCD_DrawLine(8, 264, 232, 264, Blue);
 LCD_DrawLine(8, 264, 8, 138, Blue);
 LCD_DrawLine(8, 138, 54, 138, Blue);
 LCD_DrawLine(54, 138, 54, 174, Blue);
 LCD_DrawLine(14, 174, 54, 174, Blue);
 LCD_DrawLine(14, 174, 14, 210, Blue);
 LCD_DrawLine(14, 210, 30, 210, Blue);
 LCD_DrawLine(30, 222, 30, 210, Blue);
 LCD_DrawLine(30, 222, 14, 222, Blue);
 LCD_DrawLine(14, 258, 14, 222, Blue);
 
 
 LCD_DrawLine(232, 264, 232, 138, Blue);
 LCD_DrawLine(232, 138, 186, 138, Blue);
 LCD_DrawLine(186, 138, 186, 174, Blue);
 LCD_DrawLine(186, 174, 226, 174, Blue);
 LCD_DrawLine(226, 174, 226, 210, Blue);
 LCD_DrawLine(210, 210, 226, 210, Blue);
 LCD_DrawLine(210, 222, 210, 210, Blue);
 LCD_DrawLine(210, 222, 226, 222, Blue);
 LCD_DrawLine(226, 258, 226, 222, Blue);
 
 
 LCD_DrawLine(26, 34, 54, 34, Blue);
 LCD_DrawLine(26, 34, 26, 54, Blue);
 LCD_DrawLine(54, 34, 54, 54, Blue);
 LCD_DrawLine(26, 54, 54, 54, Blue);
 
 LCD_DrawLine(214, 34, 186, 34, Blue);
 LCD_DrawLine(214, 34, 214, 54, Blue);
 LCD_DrawLine(186, 34, 186, 54, Blue);
 LCD_DrawLine(214, 54, 186, 54, Blue);
 
 LCD_DrawLine(66, 34, 102, 34, Blue);
 LCD_DrawLine(66, 34, 66, 54, Blue);
 LCD_DrawLine(102, 34, 102, 54, Blue);
 LCD_DrawLine(66, 54, 102, 54, Blue);
 
 LCD_DrawLine(174, 34, 138, 34, Blue);
 LCD_DrawLine(174, 34, 174, 54, Blue);
 LCD_DrawLine(138, 34, 138, 54, Blue);
 LCD_DrawLine(174, 54, 138, 54, Blue);
 
  LCD_DrawLine(26, 66, 54, 66, Blue);
 LCD_DrawLine(26, 66, 26, 78, Blue);
 LCD_DrawLine(54, 66, 54, 78, Blue);
 LCD_DrawLine(26, 78, 54, 78, Blue);
 
 LCD_DrawLine(214, 66, 186, 66, Blue);
 LCD_DrawLine(214, 66, 214, 78, Blue);
 LCD_DrawLine(186, 66, 186, 78, Blue);
 LCD_DrawLine(214, 78, 186, 78, Blue);
 
 LCD_DrawLine(174, 66, 174, 126, Blue);
 LCD_DrawLine(174, 126, 162, 126, Blue);
 LCD_DrawLine(162, 126, 162, 102, Blue);
 LCD_DrawLine(162, 102, 138, 102, Blue);
 LCD_DrawLine(174, 66, 162, 66, Blue);
 LCD_DrawLine(162, 66, 162, 90, Blue);
 LCD_DrawLine(162, 90, 138, 90, Blue);
 LCD_DrawLine(138, 90, 138, 102, Blue);
 
 LCD_DrawLine(66, 66, 66, 126, Blue);
 LCD_DrawLine(66, 126, 78, 126, Blue);
 LCD_DrawLine(78, 126, 78, 102, Blue);
 LCD_DrawLine(78, 102, 102, 102, Blue);
 LCD_DrawLine(66, 66, 78, 66, Blue);
 LCD_DrawLine(78, 66, 78, 90, Blue);
 LCD_DrawLine(78, 90, 102, 90, Blue);
 LCD_DrawLine(102, 90, 102, 102, Blue);
 
 LCD_DrawLine(114, 102, 126, 102, Blue);
 LCD_DrawLine(114, 102, 114, 78, Blue);
 LCD_DrawLine(90, 78, 114, 78, Blue);
 LCD_DrawLine(90, 78, 90, 66, Blue);
 LCD_DrawLine(126, 102, 126, 78, Blue);
 LCD_DrawLine(126, 78, 150, 78, Blue);
 LCD_DrawLine(150, 66, 150, 78, Blue);
 LCD_DrawLine(90, 66, 150, 66, Blue);
 
 LCD_DrawLine(114, 198, 126, 198, Blue);
 LCD_DrawLine(114, 198, 114, 174, Blue);
 LCD_DrawLine(90, 174, 114, 174, Blue);
 LCD_DrawLine(90, 174, 90, 162, Blue);
 LCD_DrawLine(126, 198, 126, 174, Blue);
 LCD_DrawLine(126, 174, 150, 174, Blue);
 LCD_DrawLine(150, 162, 150, 174, Blue);
 LCD_DrawLine(90, 162, 150, 162, Blue);

 LCD_DrawLine(114, 246, 126, 246, Blue);
 LCD_DrawLine(114, 246, 114, 222, Blue);
 LCD_DrawLine(90, 222, 114, 222, Blue);
 LCD_DrawLine(90, 222, 90, 210, Blue);
 LCD_DrawLine(126, 246, 126, 222, Blue);
 LCD_DrawLine(126, 222, 150, 222, Blue);
 LCD_DrawLine(150, 210, 150, 222, Blue);
 LCD_DrawLine(90, 210, 150, 210, Blue);
 
 LCD_DrawLine(102, 246, 26, 246, Blue);
 LCD_DrawLine(102, 246, 102, 234, Blue);
 LCD_DrawLine(102, 234, 78, 234, Blue);
 LCD_DrawLine(78, 210, 78, 234, Blue);
 LCD_DrawLine(78, 210, 66, 210, Blue);
 LCD_DrawLine(66, 234, 66, 210, Blue);
 LCD_DrawLine(66, 234, 26, 234, Blue);
 LCD_DrawLine(26, 234, 26, 246, Blue);
 
 LCD_DrawLine(138, 246, 214, 246, Blue);
 LCD_DrawLine(138, 246, 138, 234, Blue);
 LCD_DrawLine(138, 234, 162, 234, Blue);
 LCD_DrawLine(162, 210, 162, 234, Blue);
 LCD_DrawLine(162, 210, 174, 210, Blue);
 LCD_DrawLine(174, 234, 174, 210, Blue);
 LCD_DrawLine(174, 234, 214, 234, Blue);
 LCD_DrawLine(214, 234, 214, 246, Blue);
 
 LCD_DrawLine(66, 138, 78, 138, Blue);
 LCD_DrawLine(78, 174, 78, 138, Blue);
 LCD_DrawLine(66, 138, 66, 174, Blue);
 LCD_DrawLine(66, 174, 78, 174, Blue);
 
 LCD_DrawLine(66, 186, 102, 186, Blue);
 LCD_DrawLine(66, 198, 66, 186, Blue);
 LCD_DrawLine(66, 198, 102, 198, Blue);
 LCD_DrawLine(102, 186, 102, 198, Blue);
 
 LCD_DrawLine(54, 186, 26, 186, Blue);
 LCD_DrawLine(54, 186, 54, 222, Blue);
 LCD_DrawLine(54, 222, 42, 222, Blue);
 LCD_DrawLine(42, 222, 42, 198, Blue);
 LCD_DrawLine(26, 198, 42, 198, Blue);
 LCD_DrawLine(26, 198, 26, 186, Blue);
 
 LCD_DrawLine(174, 138, 162, 138, Blue);
 LCD_DrawLine(174, 138, 174, 174, Blue);
 LCD_DrawLine(174, 174, 162, 174, Blue);
 LCD_DrawLine(162, 138, 162, 174, Blue);
 
 LCD_DrawLine(174, 186, 138, 186, Blue);
 LCD_DrawLine(174, 198, 174, 186, Blue);
 LCD_DrawLine(174, 198, 138, 198, Blue);
 LCD_DrawLine(138, 186, 138, 198, Blue);
 
 LCD_DrawLine(186, 186, 214, 186, Blue);
 LCD_DrawLine(186, 186, 186, 222, Blue);
 LCD_DrawLine(198, 222, 186, 222, Blue);
 LCD_DrawLine(198, 222, 198, 198, Blue);
 LCD_DrawLine(214, 198, 198, 198, Blue);
 LCD_DrawLine(214, 198, 214, 186, Blue); 
  for(i = 0; i < HEIGHT; i++){
  for(j = 0; j < LENGTH; j++){
   current_value = board[i][j];
   
   switch(current_value){ 
    case 1:
     //Draw_Wall((j * RATIO) + xPadding, (i * RATIO) + yPadding, Blue, RATIO, RATIO);
			//Draw_Brick((j * RATIO) + xPadding, (i * RATIO) + yPadding, Blue, RATIO);
     break;
		 case 2:
     Draw_Point((j * RATIO) + xPadding, (i * RATIO) + yPadding);
    default:
     break;
   }
  }
 }
 
 Draw_Circle(pacman.posX, pacman.posY, Yellow, RATIO); // (23*8)+16=25*8
 Draw_Ghost(blinky.posX , blinky.posY , Red);
 GUI_Text(0, 0, (uint8_t *) "SCORE:", Red, Black);
 sprintf(buffer, "%d", punteggio);
 GUI_Text(52, 0, (uint8_t *) buffer, Red, Black);
 GUI_Text(160, 0, (uint8_t *) "TIME: ", Red, Black);
 sprintf(buffer, "%d", elapsed_time);
 GUI_Text(208, 0, (uint8_t *) buffer, Red, Black);
 DrawLife();
 sprintf(buffer, "%d", life);
 GUI_Text(16,300,(uint8_t *) buffer, Red, Black);
 GUI_Text(24,300,(uint8_t *) "X", Red, Black);
}
void Draw_Wall(int current_X, int current_Y, int color, int ratio1, int ratio2){
 int i, j;
 
 for(i = 0; i < ratio1; i++){
  for(j = 0; j < ratio2; j++){
   LCD_SetPoint(current_X + i, current_Y + j, color);
  }
 }
}

void Draw_Point(int current_X, int current_Y){
 int i, j;
 
 LCD_SetPoint(current_X + halfcellPadding, current_Y + halfcellPadding, Magenta);
}
void Draw_Circle(int current_X, int current_Y ,int color, int radius){
	int r = radius / 2; 
  int x, y;

    for (x = -r; x <= r; x++) { 
        for (y = -r; y <= r; y++) { 
            int dx = x;
            int dy = y;
            if (dx * dx + dy * dy <= r * r) {
                int mouth = 0;
                if (direction == 0) { // Sinistra
                    mouth = (dx < 0 && dy > dx && dy < -dx);
                } else if (direction == 1) { // Destra
										mouth = (dx > 0 && dy > -dx && dy < dx);
                } else if (direction == 2) { // Su
										mouth = (dy < 0 && dx > dy && dx < -dy);
										
                } else if (direction == 3) { // Giù
                    mouth = (dy > 0 && dx > -dy && dx < dy);
                }

								if (!(dy == -r || dy == r || dx == -r || dx == r || 
                      (direction == 0 && dx == -r) || (direction == 1 && (dy == r || dx == r || dx == -r)) || 
                      (direction == 2 && dx == r) || (direction == 3 && (dy == -r || dx == r || dx == -r))) && !mouth) {
                    LCD_SetPoint((current_X * RATIO + xPadding) + x + r, (current_Y * RATIO + yPadding) + y + r, color);
                }
            }
        }
    }
}
void Draw_Ghost(int current_X, int current_Y, int color) {
	int x,y;
     for (y = 0; y < RATIO; y++) {
        for (x = 0; x < RATIO; x++) {
            if (ghost[y][x]) {
                LCD_SetPoint((current_X * RATIO + xPadding) + x, (current_Y * RATIO + yPadding) + y, color);
            }
        }
    }

    // Draw the eyes (white pixels)
    for (y = 0; y < RATIO; y++) {
        for (x = 0; x < RATIO; x++) {
            if (eye_sprite[y][x]) {
                LCD_SetPoint((current_X * RATIO + xPadding) + x, (current_Y * RATIO + yPadding) + y, White);
            }
        }
    }
}


void Move_Pacman(){
	/*
		3 down
		2 up
		1 right
		0 left
		*/
	static int checkpoint = 1000;
	Draw_Wall((pacman.posX*RATIO)+xPadding, (pacman.posY*RATIO) +yPadding, Black, RATIO, RATIO);
	switch(direction){
		case LEFT:
			if(board[pacman.posY][pacman.posX-1]==4){
				pacman.posX=26;  //teleport
			}
			if(board[pacman.posY][pacman.posX-1]!=1){
				pacman.posX--;
			}
			break;
		case RIGHT:
			if(board[pacman.posY][pacman.posX+1]==5){
				pacman.posX=1;  //teleport
			}
			if(board[pacman.posY][pacman.posX+1]!=1){
				pacman.posX++;
			}
			break;
			
		case UP:
			if(board[pacman.posY-1][pacman.posX]!=1){
				pacman.posY--;
			}
			break;
		case DOWN:
			if(board[pacman.posY+1][pacman.posX]!=1){
				pacman.posY++;
			}
			break;
	}
		Draw_Circle(pacman.posX, pacman.posY, Yellow, RATIO);
		if(board[pacman.posY][pacman.posX]==2){
						board[pacman.posY][pacman.posX]=0;
						punteggio+=smallPillScore;
					}
		if(board[pacman.posY][pacman.posX]==3 && stateOfGame!=0 && stateOfGame!=4){
						board[pacman.posY][pacman.posX]=0;
						punteggio+=powerPillScore;
						if (stateOfGame!=0){
							stateOfGame = 2;
								timeToExpel=elapsed_time+10;}
					}
		if(punteggio>=checkpoint){
						life++;
						checkpoint += 1000;
		}
		//UpdateGameStatus(punteggio, life, GAME_DURATION - elapsed_time);
		//sprintf(buffer, "%d", punteggio);
		//GUI_Text(52, 0, (uint8_t *) buffer, Red, Black);
			
		if(punteggio==MAXSCORE + kills * 100)
			Victory();
}


void PauseHandler(){
	if(paused){
				if(startup){
				startup=0;
				wait = elapsed_time % MAX_WAIT;
				if(wait<MIN_WAIT)
					wait=MIN_WAIT;
				disable_timer(1);
				elapsed_time=0;
				}
				Draw_Wall(96, 120, Black, 48, 24);
				paused=0;
				enable_timer(1);
	      //enable_timer(2);
				}
	else{
					disable_timer(1);
					//disable_timer(2);
					paused=1;
					GUI_Text(100, 124, (uint8_t *) "PAUSE", Red, White);
				if(startup){
						enable_timer(1);
						enable_timer(3);}
				}
}

void GameOver(){
			disable_timer(3);
			disable_timer(1);
			//disable_timer(2);
			init_RIT(0xFFFFFFF);
			GUI_Text(84, 124, (uint8_t *) "GAME OVER", Red, White);}
void Victory(){
			disable_timer(3);
			disable_timer(1);
			init_RIT(0xFFFFFFF);
			GUI_Text(88, 124, (uint8_t *) "VICTORY!", Blue, Red);}

void DrawLife(){
    int r = RATIO; // Use RATIO as the size of the heart
    float scale = 1.5 / r; // Scale factor to fit the heart within RATIO
    int x, y;

    // Loop through the bounding box
   for (x = 0; x < RATIO * 2; x++) {
        for (y = 0; y < RATIO * 2; y++) {
            // Map pixel coordinates to heart formula space
            float fx = (x - r) * scale;
            float fy = (r - y) * scale;

            // Heart equation: (x^2 + y^2 - 1)^3 - x^2 * y^3 <= 0
            float fx2 = fx * fx;         // fx^2
            float fy2 = fy * fy;         // fy^2
            float fy3 = fy2 * fy;        // fy^3
            float left = (fx2 + fy2 - 1); 
            float left3 = left * left * left; // (fx^2 + fy^2 - 1)^3
            float right = fx2 * fy3;    // fx^2 * fy^3

            if (left3 - right <= 0) {
                LCD_SetPoint(x, 300 + y, Red);
            }
        }
    }
}
void Generate_Power_Pills_Coord(){
	int i = 0, x, y;
	do{
		x = rand() % punteggio;
		y = x % HEIGHT;
		x = x % LENGTH;		
		if(board[y][x] == 2){
			board[y][x] = 3;
			i++;
			Draw_PowerPills(x*RATIO + xPadding,y*RATIO + yPadding,Magenta);
		}
	} while(i < POWER_PILL_SLOTS);
}

void Draw_PowerPills(int current_X, int current_Y, int color) {
    int r = RATIO / 3;  // Raggio del cerchio
    int x, y;

    // Calcoliamo il centro del quadrato
    int x_center = current_X + RATIO / 2;
    int y_center = current_Y + RATIO / 2;

    // Ciclo per ogni punto nella griglia (di dimensione RATIO x RATIO)
    for (x = 0; x < RATIO; x++) {
        for (y = 0; y < RATIO; y++) {
            // Calcoliamo la distanza (dx, dy) dal centro del cerchio
            int dx = x - r;  // Distanza orizzontale dal centro del cerchio
            int dy = y - r;  // Distanza verticale dal centro del cerchio
            
            // Verifica se il punto (x, y) è all'interno del cerchio
            if (dx * dx + dy * dy <= r * r) {
                // Disegnare il punto, centrando il cerchio in (x_center, y_center)
                LCD_SetPoint(x_center + dx, y_center + dy, color);
            }
        }
    }
}

void Draw_Brick(int current_X, int current_Y, int color, int ratio){
	LCD_DrawLine(current_X, current_Y , current_X + ratio - 1, current_Y, color);
	LCD_DrawLine(current_X, current_Y , current_X, current_Y + ratio - 1, color);
	LCD_DrawLine(current_X + ratio - 1, current_Y + ratio - 1, current_X, current_Y + ratio - 1, color);
	LCD_DrawLine(current_X + ratio - 1, current_Y + ratio - 1, current_X + ratio - 1, current_Y , color);
}


void MoveBlinky(){
	int direction,color;
	
	Draw_Wall((blinky.posX*RATIO)+xPadding, (blinky.posY*RATIO) +yPadding, Black, RATIO, RATIO);
	switch(board[blinky.posY][blinky.posX]){

		case 2:
     Draw_Point((blinky.posX * RATIO) + xPadding, (blinky.posY * RATIO) + yPadding);
		break;
		case 3:
			Draw_PowerPills((blinky.posX * RATIO) + xPadding, (blinky.posY * RATIO) + yPadding,Magenta);
		break;
	}
	switch(stateOfGame){
		case outOfBox:
			direction = escapeRoute[step];
			step++;
			if(step==6){
				stateOfGame=1;
				LCD_DrawLine(112, 116, 128, 116, Magenta);
			}
			color=Red;
			break;
		case chase:
			direction = chaseMode();
			color=Red;
			break;
		case frieghtened:
			direction = frightenedMode();
			color=Blue;
	}
	switch(direction){
		case LEFT:
			blinky.posX --;
			break;
		case RIGHT:
			blinky.posX++;
			break;
		case UP:
			blinky.posY --;
			break;
		case DOWN:
			blinky.posY++;
			break;
	}
	Draw_Ghost(blinky.posX, blinky.posY, color);
}

char frightenedMode(){ char distX, distY, rndm;
		static char lastMove = 4;
    distX = pacman.posX - blinky.posX;
    distY = pacman.posY - blinky.posY;

    if (distX < 0)
        distX *= -1;

    if (distY < 0)
        distY *= -1;
		if( blinky.posX== 27 || blinky.posX==0){
			lastMove = blinky.posX==0 ? RIGHT : LEFT;
			return lastMove;
		} else{
			if (distY > distX) {
					if (blinky.posY < pacman.posY && board[blinky.posY - 1][blinky.posX] != 1 && lastMove != DOWN){
							lastMove=UP;
							return UP;}
					else if (blinky.posY > pacman.posY && board[blinky.posY + 1][blinky.posX] != 1 && lastMove != UP){
							lastMove=DOWN;
							return DOWN;}
					else if (blinky.posX < pacman.posX && board[blinky.posY][blinky.posX - 1] != 1 && lastMove != RIGHT){
							return LEFT;}
					else if (blinky.posX > pacman.posX && board[blinky.posY][blinky.posX + 1] != 1 && lastMove != LEFT){
							return RIGHT;}
			} else {
					if (blinky.posX < pacman.posX && board[blinky.posY][blinky.posX - 1] != 1 && lastMove != RIGHT){
						lastMove=LEFT;
							return LEFT;}
					else if (blinky.posX > pacman.posX && board[blinky.posY][blinky.posX + 1] != 1 && lastMove != LEFT){
						lastMove=RIGHT;
							return RIGHT;}
					if (blinky.posY < pacman.posY && board[blinky.posY - 1][blinky.posX] != 1 && lastMove != DOWN){
							lastMove=UP;
							return UP;}
					else if (blinky.posY > pacman.posY && board[blinky.posY + 1][blinky.posX] != 1 && lastMove != UP){
						lastMove=DOWN;
							return DOWN;}
			}}

			if (board[blinky.posY - 1][blinky.posX] != 1  && lastMove != DOWN){
						lastMove=UP;
            return UP;}
				else if (board[blinky.posY][blinky.posX - 1] != 1  && lastMove != RIGHT){
					lastMove=LEFT;
            return LEFT;}
        else if ( board[blinky.posY + 1][blinky.posX] != 1  && lastMove != UP){
					lastMove=DOWN;
            return DOWN;}
        else if (board[blinky.posY][blinky.posX + 1] != 1 && lastMove != LEFT){
					lastMove=RIGHT;
            return RIGHT;}
    return -1;}
char chaseMode() {
    char distX, distY, rndm;
		static char lastMove = 4;
    distX = pacman.posX - blinky.posX;
    distY = pacman.posY - blinky.posY;
		
    if (distX < 0)
        distX *= -1;

    if (distY < 0)
        distY *= -1;
if( blinky.posX== 27 || blinky.posX==0){
			lastMove = blinky.posX==0 ? RIGHT : LEFT;
			return lastMove;
		} else{
    if (distY > distX) {
        if (blinky.posY > pacman.posY && board[blinky.posY - 1][blinky.posX] != 1 && lastMove != DOWN){
						lastMove=UP;
            return UP;}
        else if (blinky.posY < pacman.posY && board[blinky.posY + 1][blinky.posX] != 1 && lastMove != UP){
						lastMove=DOWN;
            return DOWN;}
        else if (blinky.posX > pacman.posX && board[blinky.posY][blinky.posX - 1] != 1 && lastMove != RIGHT){
            return LEFT;}
        else if (blinky.posX < pacman.posX && board[blinky.posY][blinky.posX + 1] != 1 && lastMove != LEFT){
            return RIGHT;}
    } else {
        if (blinky.posX > pacman.posX && board[blinky.posY][blinky.posX - 1] != 1 && lastMove != RIGHT){
					lastMove=LEFT;
            return LEFT;}
        else if (blinky.posX < pacman.posX && board[blinky.posY][blinky.posX + 1] != 1 && lastMove != LEFT){
					lastMove=RIGHT;
            return RIGHT;}
        if (blinky.posY > pacman.posY && board[blinky.posY - 1][blinky.posX] != 1 && lastMove != DOWN){
						lastMove=UP;
            return UP;}
        else if (blinky.posY < pacman.posY && board[blinky.posY + 1][blinky.posX] != 1 && lastMove != UP){
					lastMove=DOWN;
            return DOWN;}
    }}

				if (board[blinky.posY - 1][blinky.posX] != 1  && lastMove != DOWN){
						lastMove=UP;
            return UP;}
				else if (board[blinky.posY][blinky.posX - 1] != 1  && lastMove != RIGHT){
					lastMove=LEFT;
            return LEFT;}
        else if ( board[blinky.posY + 1][blinky.posX] != 1  && lastMove != UP){
					lastMove=DOWN;
            return DOWN;}
        else if (board[blinky.posY][blinky.posX + 1] != 1 && lastMove != LEFT){
					lastMove=RIGHT;
            return RIGHT;}
    return -1;
}
void sendResults(){
	CAN_TxMsg.data[0] = ((punteggio) & 0xFF00) >> 8;
	CAN_TxMsg.data[1] = punteggio & 0xFF;
	CAN_TxMsg.data[2] = life;
	uint8_t tempo;
	tempo = GAME_DURATION-elapsed_time;
	CAN_TxMsg.data[3] = tempo;
	CAN_TxMsg.len=4;
	CAN_TxMsg.id=2;
	CAN_TxMsg.format=STANDARD_FORMAT;
	CAN_TxMsg.type=DATA_FRAME;
	CAN_wrMsg (1, &CAN_TxMsg);
	
}
void respawnBlinky(){
stateOfGame=0;
step=0;
//enable_timer(2);
	}

void UpdateGameStatus(int score, char vite, char time){
	 sprintf(buffer, "%d", score);
	 GUI_Text(52, 0, (uint8_t *) buffer, Red, Black);
	 sprintf(buffer, "%d", time);
	if(time<10){
		Draw_Wall(216,0,Black,8,16);}
		GUI_Text(208, 0, (uint8_t *) buffer, Red, Black);
	 sprintf(buffer, "%d", vite);
	 GUI_Text(16,300,(uint8_t *) buffer, Red, Black);
}
void collisionManager(){
	switch(stateOfGame){
				case 1:
					if(blinky.posX==pacman.posX && blinky.posY == pacman.posY){
						life--;
						Draw_Wall(life*RATIO*2+80, 300, Black, RATIO*2,RATIO*2);
						if(life==0)	GameOver();
						Draw_Wall((pacman.posX*RATIO)+xPadding, (pacman.posY*RATIO) +yPadding, Black, RATIO, RATIO);
						pacman.posX=pacmanStartingX;
						pacman.posY=pacmanStartingY;
						Draw_Circle(pacman.posX, pacman.posY, Yellow, RATIO);}
					break;
				case 2:
					if(blinky.posX==pacman.posX && blinky.posY == pacman.posY){
						stateOfGame=4;
						respawn=elapsed_time+3;
						punteggio += powerPillScore;
						kills++;
						blinky.posX=blinkyStartingX;
						blinky.posY=blinkyStartingY;}
					break;
						default:
							break;
}}