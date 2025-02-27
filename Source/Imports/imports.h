#define LENGTH      28
#define HEIGHT     31
#define RATIO      8
#define	MAX_WAIT					10
#define MIN_WAIT					6
#define GAME_DURATION 		60
#define POWER_PILL_SLOTS 	6
#define xPadding		8
#define yPadding		16
#define halfcellPadding			4
#define pacmanStartingX		13
#define pacmanStartingY		23
#define blinkyStartingX		11
#define blinkyStartingY		15
#define smallPillScore		10
#define powerPillScore 		50
#define MAXSCORE		powerPillScore*6+smallPillScore*234
#define LEFT 0
#define RIGHT 1
#define UP 2
#define DOWN 3
#define timervalue 0x400
#define DEAD 4
#define chase	1
#define outOfBox 0
#define frieghtened 2

struct pg{
	int posX;
	int posY;
};

typedef struct {
    int row;
    int col;
    int distance;
} Cell;

void InitializeGame();
void Draw_Wall(int current_X, int current_Y, int color, int ratio1, int ratio2);
void Draw_Point(int current_X, int current_Y);
void Draw_Circle(int current_X, int current_Y, int color, int radius);
void Move_Pacman();
void PauseHandler();
void Victory();
void GameOver();
void DrawLife();
void Generate_Power_Pills_Coord();
void Draw_PowerPills(int current_X, int current_Y, int color);
void Draw_Map();
void Draw_Brick(int current_X, int current_Y, int color, int ratio);
void Draw_Ghost(int current_X, int current_Y, int color);
int is_valid(int x, int y, char board[HEIGHT][LENGTH], int visited[HEIGHT][LENGTH]);
void MoveBlinky();
char chaseMode();
char frightenedMode();
void respawnBlinky();
void UpdateGameStatus(int score, char vite, char time);
void sendResults();
void collisionManager();