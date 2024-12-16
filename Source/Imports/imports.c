#include "imports.h"
#include "../TouchPanel/TouchPanel.h"
#include "../GLCD/GLCD.h"
#include "stdio.h"
#include "time.h"

/*
 0: Vuoto
 1: Muro
 2: Point
 3: Special Point
 4: TP-Left
 5: TP-Right
*/
		char board[HEIGTH][LENGTH] = {
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
        {1, 1, 1, 1, 1, 1, 2, 1, 1, 0, 1, 1, 1, 0, 0, 1, 1, 1, 0, 1, 1, 2, 1, 1, 1, 1, 1, 1},
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
		struct pg pacman;
		uint8_t elapsed_time = 0;
		uint8_t wait = 0;
		char direction;
		int punteggio;
		char buffer[100];
		char life;
		struct pg power_pills_coord[6];
		
//13, 23 pacman starting point
void InitializeGame(){
 pacman.posX = pacmanStartingX;
 pacman.posY = pacmanStartingY;
 direction=0;
 punteggio=0;
 life = 1;
 Draw_Map();
 Generate_Power_Pills_Coord();
 init_timer(0, 0x001C4B40); 						    /* 8us * 25MHz = 200 ~= 0xC8 */
 init_timer(1, 0x17D7840);
 PauseHandler();
}
void Draw_Map(){
 int i, j, current_value;
	/*
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
 LCD_DrawLine(214, 198, 214, 186, Blue); */
  for(i = 0; i < HEIGTH; i++){
  for(j = 0; j < LENGTH; j++){
   current_value = board[i][j];
   
   switch(current_value){ 
    case 1:
     //Draw_Wall((j * RATIO) + xPadding, (i * RATIO) + yPadding, Blue, RATIO, RATIO);
			Draw_Brick((j * RATIO) + xPadding, (i * RATIO) + yPadding, Blue, RATIO);
     break;
		 case 2:
     Draw_Point((j * RATIO) + xPadding, (i * RATIO) + yPadding);
    default:
     break;
   }
  }
 }
 
 Draw_Circle(Yellow, RATIO); // (23*8)+16=25*8
 GUI_Text(0, 0, (uint8_t *) "SCORE:", Red, Black);
 sprintf(buffer, "%d", punteggio);
 GUI_Text(52, 0, (uint8_t *) buffer, Red, Black);
 GUI_Text(160, 0, (uint8_t *) "TIME: ", Red, Black);
 sprintf(buffer, "%d", elapsed_time);
 GUI_Text(208, 0, (uint8_t *) buffer, Red, Black);
 GUI_Text(0, 300, (uint8_t *) "LIFE COUNT: ", Red, Black);
 DrawLife();
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
void Draw_Circle(int color, int radius){
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
                    LCD_SetPoint((pacman.posX * RATIO + xPadding) + x + r, (pacman.posY * RATIO + yPadding) + y + r, color);
                }
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
		case 0:
			if(board[pacman.posY][pacman.posX-1]==4){
				pacman.posX=26;  //teleport
			}
			if(board[pacman.posY][pacman.posX-1]!=1){
				pacman.posX--;
			}
			break;
		case 1:
			if(board[pacman.posY][pacman.posX+1]==5){
				pacman.posX=1;  //teleport
			}
			if(board[pacman.posY][pacman.posX+1]!=1){
				pacman.posX++;
			}
			break;
			
		case 2:
			if(board[pacman.posY-1][pacman.posX]!=1){
				pacman.posY--;
			}
			break;
		case 3:
			if(board[pacman.posY+1][pacman.posX]!=1){
				pacman.posY++;
			}
			break;
	}
		Draw_Circle(Yellow, RATIO);
		if(board[pacman.posY][pacman.posX]==2){
						board[pacman.posY][pacman.posX]=0;
						punteggio+=smallPillScore;
					}
		if(board[pacman.posY][pacman.posX]==3){
						board[pacman.posY][pacman.posX]=0;
						punteggio+=powerPillScore;
					}
		if(punteggio>=checkpoint){
						life++;
						DrawLife();
						checkpoint += 1000;
		}
		sprintf(buffer, "%d", punteggio);
		GUI_Text(52, 0, (uint8_t *) buffer, Red, Black);	
		if(punteggio==MAXSCORE)
			Victory();
}


void PauseHandler(){
	static char pause = 0;
	if(pause){
				Draw_Wall(96, 120, Black, 48, 24);
				pause=0;
				enable_timer(0);
				enable_timer(1);}
	else{
					disable_timer(0);
					disable_timer(1);
					pause=1;
					GUI_Text(100, 124, (uint8_t *) "PAUSE", Red, White);
				}
}

void GameOver(){
			disable_timer(0);
			disable_timer(1);
			init_RIT(0xFFFFFFF);
			GUI_Text(84, 124, (uint8_t *) "GAME OVER", Red, White);}
void Victory(){
			disable_timer(0);
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
                LCD_SetPoint(life * 16 + x + 80, 300 + y, Red);
            }
        }
    }
}
void Generate_Power_Pills_Coord(){
	time_t t;
	int i = 0, x, y;
	
	srand((unsigned)time(&t));
	wait = rand() % MAX_WAIT;
	do{
		x = rand() % LENGTH;
		y = rand() % HEIGTH;
		
		if(board[y][x] == 2){
			board[y][x] = 0;
			power_pills_coord[i].posX = x;
			power_pills_coord[i].posY = y;
			i++;
		}
	} while(i < POWER_PILL_SLOTS);
}

void Place_Power_Pills(){
	int i;
	
	for(i = 0; i < POWER_PILL_SLOTS; i++){
		board[power_pills_coord[i].posY][power_pills_coord[i].posX] = 3;
		Draw_PowerPills((power_pills_coord[i].posX * RATIO) + xPadding, (power_pills_coord[i].posY * RATIO) + yPadding, Magenta);
	}
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
	
/* In larghezza 8:1, in altezza 8:1*/