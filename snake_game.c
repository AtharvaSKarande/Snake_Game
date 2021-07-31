/*		* This project is created by :- Atharva Sunil Karande.
		* Under the guidance of :- Mrs. Jaee Chavan.
		* College name :- Indian Institute of Information Technology, Pune.
		* Course Name :- F.Y.B.Tech.
		* Branch :- Computer Science Engineering.
		* MIS No. :- 111915020
		* Semester :- 1st semester.
		* Project Name :-  " Mini Snake Game " .
*/
	
// Header files. 
#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<windows.h>

// Functions used.
void hide_cursor(void);
void gotoxy(int,int);
void start(void);
void table(int,int,int,int);
void clear_gbox(int,int,int,int);
void print_characters(void);
void instructions(void);
void screen(void);
void input(void);
void logic(void);
void setup(void);
void message(void);
void record(void);

// Global variables used.
int score = 0,lives = 3;
int snake_x,snake_y,food_x,food_y;			// X,Y coordinates of snake & food.
int GameOver=1,direction,i,j,k,n=0;
int segment_x[100],segment_y[100];			// X,Y coordinates of each segment of snake.

int main()
{
	printf("Press any key to continue....");
	getch();		
	system("color 34");
	hide_cursor();			// Cursor is made invisible.
	instructions();			// Instructions of Game.
	start();				// Loading screen.
	while(lives>=0)			// Program will run till lives become zero.
	{	
		setup();
		system("cls");
		table(15,6,102,32);			// External box.
		table(17,7,70,30);			// Game box.
		table(90,7,25,30);			// Information box.			
		while(GameOver)		// Program will run till game doesn't over.
		{
			screen();
			input();
			print_characters();		// Characters will be printed until game doesn't over.
			logic();
		}
		message();
	}
	record();
	return 0;
}

void hide_cursor(void)
{
	// This function will hide the blinking of cursor.
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO CursoInfo;	// 'CONSOLE_CURSOR_INFO' is a predefined structure.
	CursoInfo.dwSize = 1;			
	CursoInfo.bVisible = 0;			// visibility = 0  i.e. no cursor blink.
	SetConsoleCursorInfo(hConsole,&CursoInfo);
}

void gotoxy(int x,int y)
{
	// This function is used for moving the cursor to desired x-y coordinates.
	// (0,0) is situated at left top.
    COORD coord;		// COORD is the predefined structure in header file 'windows.h'.
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void print_characters(void)
{
	// This function will print the snake's head, it's segments, it's food.
	gotoxy(snake_x,snake_y);
	switch(direction)
	{			// Prints head.
		case 1:
			printf("<");
			break;
		case 2:
			printf("^");
			break;
		case 3:
			printf(">");
			break;
		case 4:
			printf("v");
			break;
	}
	gotoxy(food_x,food_y);			// Prints food of snake.
	printf("#");
	// Segment(s) of snake,
	for(k=0;k<score;k++)
	{
		gotoxy(segment_x[k],segment_y[k]);
		printf("O");
	}
}

void table(int x,int y,int l,int b)
{
	// This function will print the rectangle of dimensions 'l' x 'b' at coordinates (x,y).
	gotoxy(x,y);
	printf("%c",218);			// Top left corner.
	for(i=0;i<l;i++)
	{
		printf("%c",196);		// Top border.
	}
	printf("%c",191);			// Top right corner.
	
	for(j=1;j<b;j++)
	{
		gotoxy(x,++y);
		printf("%c",179);		// Left side border.
		gotoxy(x+l+1,y);
		printf("%c",179);		// Right side border.
	}
	gotoxy(x,++y);
	printf("%c",192);			// Lower left cornner. 
	for(i=0;i<l;i++)
	{
		printf("%c",196);		// Lower border. 
	}
	printf("%c",217);			// Lower right corner.
}

void instructions()
{
	// This function will print Instructions of game.
    system("cls");
    table(70,7,20,2);
    gotoxy(71,8);
    printf(" Game instructions ");
    printf("\n\n\n\n      1]. Use A - S - D - W to move the snake.");
	printf("\n\n      2]. You will be provided food at the several coordinates of the screen which you have to eat.");
	printf("\n\n      3]. Everytime you eat a food the length of the snake will be increased by 1 element and thus the score.");
	printf("\n\n      4]. Here you are provided with THREE lives. Your life will decrease as you hit the wall or snake's body.");
	printf("\n\n      5]. If you want to pause the game press 'X'. To start again, press any key.");
	printf("\n\n      6].  If you want to exit press Esc. \n");
    printf("\n\nPress any key to play game...");
    if(getch()==27)
    exit(0);
}

void start()
{
	// This is loading screen of game.
	system("cls");
	system("COLOR 5E");
	gotoxy(70,17);
	printf("Welcome to SNAKE GAME.");
	gotoxy(70,25);
	printf("     Loading.....");
	table(40,26,80,2);					// Border of loading bar.
	for(i=1;i<79;i++)
	{
		gotoxy(80,27);
		printf("%d",100*i/78);			// To print percentage of completion.
		gotoxy(41+i,27);
		for(j=0;j<5000000;j++);		// To print loading bar slowly.
		printf("%c",177);
	}
}

void setup()
{
	// This function will decide the Initial cooordinares of snake and it's food.
	// Initial coordinates of food.
	snake_x=50;
	snake_y=20;
	
	Generator:
	// The function 'rand()' will generate large number randomly.
	food_x=rand()%70;			// To generate food coordinates less than boundry.			
	food_y=rand()%30;
	if(food_x == 0 || food_y == 0)
	{
		goto Generator;
	}							// To ensure that food will not pop up on boundry.
	// To take food inside the boundry.
	food_x += 17;
	food_y += 5;
}

void clear_gbox(int x,int y,int l,int b)
{
	//This function will clear the part is screen by printing ' ' (space) character.
	n++;
	if(n%2)
	{
		for(i=0;i<b;i++)
		{
			gotoxy(x,y++);
			for(j=0;j<l;j++)
			{
				printf(" ");
			}
		}
	}
	else
	{
		y += 28;
		for(i=b;i>0;i--)
		{
			gotoxy(x,y--);
			for(j=l;j>=0;j--)
			{
				printf(" ");
			}
		}
	}
	if(n>10000)
	{
		n=0;
	}
}

void screen()
{
	// This function will design actual game window.
	clear_gbox(18,8,69,29);
	system("color 0A");
	gotoxy(98,10);
	printf("Score : %d",score);
	gotoxy(98,13);
	printf("Lives : %d",lives);
	gotoxy(98,20);
	printf("A - Left");
	gotoxy(98,22);
	printf("W - Up");
	gotoxy(98,24);
	printf("D - Right");
	gotoxy(98,26);
	printf("S - Down");
	gotoxy(50,42);
	printf(" Press A/W/S/D to start & play.");
}

void input()
{
	// This function will take input from user and desides value of 'direction'.
	if(kbhit())
	{
		switch(getch())
		{
			case 'a':		// Left.
			case 75:
			case 'A':
				direction = 1;
				break;
			case 'w': 		// Up.
			case 72:
			case 'W':
				direction = 2;
				break;
			case 'd':		// Right.
			case 77:
			case 'D':
				direction = 3;
				break;
			case 's':		// Down.
			case 80:
			case 'S':
				direction = 4;
				break;
			case 'x':		// Pause the game.
			case 'X':
				getch();
				break;
			case 27:		// Escape.
				record();
				exit(0);
			default:
				printf("\a");	// Beep.
		}
	}
}

void logic()
{
	int tempx1,tempy1,tempx2,tempy2;
	// This function will make logic of moves of the snake.
	tempx1 = snake_x;			// Snake's coordinates are copied to a temporary variables.
	tempy1 = snake_y;
	switch(direction)
	{
		case 1:				// Left.
			snake_x-=2;
			break;
		case 2:				// Up.
			snake_y--;
			break;
		case 3:				// Right.
			snake_x+=2;
			break;
		case 4:				// Down.
			snake_y++;
			break;
	}
	// If snake bites it'self.
	for(i=0;i<score;i++)
	{
		if(snake_x == segment_x[i] && snake_y == segment_y[i]||snake_x + 1 == segment_x[i] && snake_y == segment_y[i]||snake_x - 1 == segment_x[i] && snake_y == segment_y[i])
		{
			GameOver = 0;
		}
	}
	// If snake eats food.
	if(snake_x == food_x && snake_y == food_y || snake_x + 1 == food_x && snake_y == food_y || snake_x - 1 == food_x && snake_y == food_y)
	{
		score++;
		Generator1:			// Generating new food.
		food_x=rand()%70;
		food_y=rand()%30;
		if(food_x == 0 || food_y == 0)
		{
			goto Generator1;
		}
		// To take food inside boundry
		food_x += 18;
		food_y += 8;
	}
	// If snake bite's boundry.
	if(snake_x == 88||snake_x == 17 || snake_y == 7 || snake_y ==37 || snake_x + 1 == 88 || snake_x - 1 == 88 || snake_x + 1 == 17 )
	{
		GameOver=0;
	}
	// Copying coordinates of previous segment to it's next segment.
	for(i=0;i<score;i++)
		{
			tempx2 = segment_x[i];
			tempy2 = segment_y[i];
			segment_x[i] = tempx1;
			segment_y[i] = tempy1;
			tempx1 = tempx2;
			tempy1 = tempy2;
		}
	if(!GameOver)
	{
		for(i=0;i<100;i++)
		{
			for(j=0;j<100;j++)
			{
				segment_x[i]=0;
				segment_y[i]=0;
			}
		}
	}
}

void message()
{
	// This function will execute when user loses one live.
	system("cls");
	if(lives)
	{
		lives--;
		setup();
		system("color 5E");
		table(70,20,14,2);
		gotoxy(71,21);
		printf("1 Life lost.");				// Displaying message.
		gotoxy(80,30);
		GameOver=1;
		printf("press any key to continue....");
		getch();
	}
	else
	{
		lives--;
		GameOver = 0;
		system("color 40");
		table(70,20,10,2);
		gotoxy(71,21);
		printf("Game Over.");
		getch();
	}
	
}

void record()
{
	// This function will keep records of player.
	char c;
	FILE *file;
	char name[50];
	time_t t;				// To print time in record file.
	time(&t);
	system("cls");
	system("color E5");
	gotoxy(30,10);
	file = fopen("record.txt","a+");
	printf(" * Enter your name :");
	scanf("%[^\n]",name);
	fprintf(file," Player name : %s",name);
	fprintf(file,"\n   Score : %d",score);
	fprintf(file,"\n   Date & Time : %s",ctime(&t));
	fprintf(file,"----------------------------------\n");
	fclose(file);
	system("cls");
	gotoxy(50,10);
	printf("Past records : \n");
	file=fopen("record.txt","r");
    do
    {
    	putchar(c=getc(file));
	}while(c!=EOF);
	fclose(file);
	getch();
}
