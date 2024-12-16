#define LENGTH      28
#define HEIGTH     31
#define RATIO      8
#define	MAX_WAIT					10
#define GAME_DURATION 		60
#define POWER_PILL_SLOTS 	6
#define xPadding		8
#define yPadding		16
#define halfcellPadding			4
#define pacmanStartingX		13
#define pacmanStartingY		23
#define smallPillScore		10
#define powerPillScore 		50
#define MAXSCORE		powerPillScore*6+smallPillScore*234
struct pg{
	int posX;
	int posY;
};


void InitializeGame();
void Draw_Wall(int current_X, int current_Y, int color, int ratio1, int ratio2);
void Draw_Point(int current_X, int current_Y);
void Draw_Circle(int color, int radius);
void Move_Pacman();
void PauseHandler();
void Victory();
void GameOver();
void DrawLife();
void Place_Power_Pills();
void Generate_Power_Pills_Coord();
void Draw_PowerPills(int current_X, int current_Y, int color);
void Draw_Map();
void Draw_Brick(int current_X, int current_Y, int color, int ratio);