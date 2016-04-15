#include <iostream>
#include <cmath>
#include "conio2.h"
#include "game.h"
#include "walls.h"

#define TREE '#'
#define WALL (char)178
#define STONE (char)15
#define BUSH (char)176
#define STATUE (char)206
#define DOOR (char)219
#define DOOROPEN 'O'
#define NOTHING ' '

#define FRONT 1
#define LEFT 2
#define RIGHT 3
#define LEFTWALL 4
#define RIGHTWALL 5

#define OPENING 0
#define CLOSING 1

bool isVisible(char elem);
void showWall(Location l, int Type, int Side);
void viewBuilder(Player player, Labyrinth labyrinth, bool DoorAction);
void showDoorAnimation(Player player, Labyrinth labyrinth, int mode);

bool isVisible(char elem)
{
	if (elem != NULL && elem != NOTHING)
		return true;
	else
		return false;
}
void showWall(Location l,int Type, int Side)
{
	int x = l.x + 2;
	int y = l.y + 6;
	int Distance = l.d;
	int width, height;
	Draw* Object;
	if (Side == FRONT)
	{
		switch (Distance)
		{
		case 1:
			width = 15;
			height = 20;
			switch (Type)
			{
			case WALL:
				Object = WallFront1;
				break;
			case BUSH:
				Object = BushFront1;
				break;
			case STONE:
				Object = StoneFront1;
				break;
			case TREE:
				Object = TreeFront1;
				break;
			case STATUE:
				Object = StatueFront1;
				break;
			case DOOR:
				Object = DoorFront1;
				break;
			case DOOROPEN:
				Object = DoorOpenFront1;
				break;
			}
			break;
		case 2:
			width = 13;
			height = 17;
			switch (Type)
			{
			case WALL:
				Object = WallFront2;
				break;
			case BUSH:
				Object = BushFront2;
				break;
			case STONE:
				Object = StoneFront2;
				break;
			case TREE:
				Object = TreeFront2;
				break;
			case STATUE:
				Object = StatueFront2;
				break;
			case DOOR:
				Object = DoorFront2;
				break;
			case DOOROPEN:
				Object = DoorOpenFront2;
				break;
			}
			break;
		case 3:
			width = 11;
			height = 15;
			switch (Type)
			{
			case WALL:
				Object = WallFront3;
				break;
			case BUSH:
				Object = BushFront3;
				break;
			case STONE:
				Object = StoneFront3;
				break;
			case TREE:
				Object = TreeFront3;
				break;
			case STATUE:
				Object = StatueFront3;
				break;
			case DOOR:
				Object = DoorFront3;
				break;
			case DOOROPEN:
				Object = DoorOpenFront3;
				break;
			}
			break;
		case 4:
			width = 9;
			height = 12;
			switch (Type)
			{
			case WALL:
				Object = WallFront4;
				break;
			case BUSH:
				Object = BushFront4;
				break;
			case STONE:
				Object = StoneFront4;
				break;
			case TREE:
				Object = TreeFront4;
				break;
			case STATUE:
				Object = StatueFront4;
				break;
			case DOOR:
				Object = DoorFront4;
				break;
			case DOOROPEN:
				Object = DoorOpenFront4;
				break;
			}
			break;
		case 5:
			width = 7;
			height = 10;
			switch (Type)
			{
			case WALL:
				Object = WallFront5;
				break;
			case BUSH:
				Object = BushFront5;
				break;
			case STONE:
				Object = StoneFront5;
				break;
			case TREE:
				Object = TreeFront5;
				break;
			case STATUE:
				Object = StatueFront5;
				break;
			case DOOR:
				Object = DoorFront5;
				break;
			case DOOROPEN:
				Object = DoorOpenFront5;
				break;
			}
			break;
		case 6:
			width = 5;
			height = 7;
			switch (Type)
			{
			case WALL:
				Object = WallFront6;
				break;
			case BUSH:
				Object = BushFront6;
				break;
			case STONE:
				Object = StoneFront6;
				break;
			case TREE:
				Object = TreeFront6;
				break;
			case STATUE:
				Object = StatueFront6;
				break;
			case DOOR:
				Object = DoorFront6;
				break;
			case DOOROPEN:
				Object = DoorOpenFront6;
				break;
			}
			break;
		case 7:
			width = 3;
			height = 5;
			switch (Type)
			{
			case WALL:
				Object = WallFront7;
				break;
			case BUSH:
				Object = BushFront7;
				break;
			case STONE:
				Object = StoneFront7;
				break;
			case TREE:
				Object = TreeFront7;
				break;
			case STATUE:
				Object = StatueFront7;
				break;
			case DOOR:
				Object = DoorFront7;
				break;
			case DOOROPEN:
				Object = DoorOpenFront7;
				break;
			}
			break;
		}
	}
	else if (Side == LEFT || Side == RIGHT)
	{
		switch (Distance)
		{
		case 1:
			width = 10;
			height = 20;
			switch (Type)
			{
			case WALL:
				Object = WallSide1;
				break;
			case BUSH:
				Object = BushSide1;
				break;
			case STONE:
				Object = StoneSide1;
				break;
			case TREE:
				Object = TreeSide1;
				break;
			case STATUE:
				Object = StatueSide1;
				break;
			case DOOR:
				Object = DoorSide1;
				break;
			case DOOROPEN:
				Object = DoorOpenSide1;
				break;
			}
			break;
		case 2:
			width = 8;
			height = 17;
			switch (Type)
			{
			case WALL:
				Object = WallSide2;
				break;
			case BUSH:
				Object = BushSide2;
				break;
			case STONE:
				Object = StoneSide2;
				break;
			case TREE:
				Object = TreeSide2;
				break;
			case STATUE:
				Object = StatueSide2;
				break;
			case DOOR:
				Object = DoorSide2;
				break;
			case DOOROPEN:
				Object = DoorOpenSide2;
				break;
			}
			break;
		case 3:
			width = 7;
			height = 15;
			switch (Type)
			{
			case WALL:
				Object = WallSide3;
				break;
			case BUSH:
				Object = BushSide3;
				break;
			case STONE:
				Object = StoneSide3;
				break;
			case TREE:
				Object = TreeSide3;
				break;
			case STATUE:
				Object = StatueSide3;
				break;
			case DOOR:
				Object = DoorSide3;
				break;
			case DOOROPEN:
				Object = DoorOpenSide3;
				break;
			}
			break;
		case 4:
			width = 6;
			height = 12;
			switch (Type)
			{
			case WALL:
				Object = WallSide4;
				break;
			case BUSH:
				Object = BushSide4;
				break;
			case STONE:
				Object = StoneSide4;
				break;
			case TREE:
				Object = TreeSide4;
				break;
			case STATUE:
				Object = StatueSide4;
				break;
			case DOOR:
				Object = DoorSide4;
				break;
			case DOOROPEN:
				Object = DoorOpenSide4;
				break;
			}
			break;
		case 5:
			width = 5;
			height = 10;
			switch (Type)
			{
			case WALL:
				Object = WallSide5;
				break;
			case BUSH:
				Object = BushSide5;
				break;
			case STONE:
				Object = StoneSide5;
				break;
			case TREE:
				Object = TreeSide5;
				break;
			case STATUE:
				Object = StatueSide5;
				break;
			case DOOR:
				Object = DoorSide5;
				break;
			case DOOROPEN:
				Object = DoorOpenSide5;
				break;
			}
			break;
		case 6:
			width = 3;
			height = 7;
			switch (Type)
			{
			case WALL:
				Object = WallSide6;
				break;
			case BUSH:
				Object = BushSide6;
				break;
			case STONE:
				Object = StoneSide6;
				break;
			case TREE:
				Object = TreeSide6;
				break;
			case STATUE:
				Object = StatueSide6;
				break;
			case DOOR:
				Object = DoorSide6;
				break;
			case DOOROPEN:
				Object = DoorOpenSide6;
				break;
			}
			break;
		case 7:
			width = 2;
			height = 5;
			switch (Type)
			{
			case WALL:
				Object = WallSide7;
				break;
			case BUSH:
				Object = BushSide7;
				break;
			case STONE:
				Object = StoneSide7;
				break;
			case TREE:
				Object = TreeSide7;
				break;
			case STATUE:
				Object = StatueSide7;
				break;
			case DOOR:
				Object = DoorSide7;
				break;
			case DOOROPEN:
				Object = DoorOpenSide7;
				break;
			}
			break;
		}
	}
	else if (Side == LEFTWALL)
	{
		for (int i = 0; i < 20; i++)
		{
			gotoxy(x, y + i);
			for (int j = 0; j < 5; j++)
			{
				textcolor(WallSide1[i * 10 + j].color);
				printf("%c", WallSide1[i * 10 + j].c);
			}
		}
		return;
	}
	else if (Side == RIGHTWALL)
	{
		for (int i = 0; i < 20; i++)
		{
			gotoxy(x, y + i);
			for (int j = 4; j >= 0; j--)
			{
				textcolor(WallSide1[i * 10 + j].color);
				printf("%c", WallSide1[i * 10 + j].c);
			}
		}
		return;
	}
	if (Type != NOTHING && Type != NULL)
	{
		for (int i = 0; i < height; i++)
		{
			gotoxy(x, y + i);
			if (Side == FRONT || Side == LEFT)
				for (int j = 0; j < width; j++)
				{
					if (Object[i * width + j].c == ' ')
					{
						gotoxy(wherex() + 1, wherey());
					}
					else
					{
						textcolor(Object[i * width + j].color);
						printf("%c", Object[i * width + j].c);
					}
				}
			else
				for (int j = width - 1; j >= 0; j--)
				{
					if (Object[i * width + j].c == ' ')
					{
						gotoxy(wherex() + 1, wherey());
					}
					else
					{
						textcolor(Object[i * width + j].color);
						printf("%c", Object[i * width + j].c);
					}
				}
		}
	}
}
void viewBuilder(Player player, Labyrinth labyrinth, bool DoorAction)
{
	textcolor(LIGHTGRAY);
	for (int i = 0; i < 56; i++)
	{
		for (int j = 0; j < 24; j++)
		{
			if (i == 0 || j == 0 || i == 55 || j == 23)
			{
				gotoxy(1 + i, 5 + j);
				putch((char)178);
			}
		}
	}
	char** view = new char*[8];
	for (int i = 0; i < 8; i++)
		view[i] = new char[3];
	int x = player.pos.x - 1;
	int y = player.pos.y - 1;

	if (player.dir.up)
		for (int i = 0; i < 8; i++)
			for (int j = 0; j < 3; j++)
				if (labyrinth.isInside(x - 1 + j, y - 8 + i))
					view[i][j] = labyrinth.lab[y - 8 + i][x - 1 + j];
				else
					view[i][j] = NULL;

	else if (player.dir.down)
		for (int i = 0; i < 8; i++)
			for (int j = 0; j < 3; j++)
				if (labyrinth.isInside(x + 1 - j, y + 8 - i))
					view[i][j] = labyrinth.lab[y + 8 - i][x + 1 - j];
				else
					view[i][j] = NULL;

	else if (player.dir.left)
		for (int i = 0; i < 8; i++)
			for (int j = 0; j < 3; j++)
				if (labyrinth.isInside(x - 8 + i, y + 1 - j))
					view[i][j] = labyrinth.lab[y + 1 - j][x - 8 + i];
				else
					view[i][j] = NULL;

	else if (player.dir.right)
		for (int i = 0; i < 8; i++)
			for (int j = 0; j < 3; j++)
				if (labyrinth.isInside(x + 8 - i,y + 1 - j))
					view[i][j] = labyrinth.lab[y + 1 - j][x + 8 - i];
				else
					view[i][j] = NULL;
	
	for (int i = 0; i < 8; i++)
	{
		if (view[i][1] == WALL)
		{
			if (isVisible(view[i][0]))
				showWall(frontWallPosition[i * 3], view[i][0], FRONT);
			if (isVisible(view[i][1]))
				showWall(frontWallPosition[i * 3 + 1], view[i][1], FRONT);
			if (isVisible(view[i][2]))
				showWall(frontWallPosition[i * 3 + 2], view[i][2], FRONT);
			if (i == 7)
			{
				showWall(sideWallPosition[7 * 3], view[7][0], LEFTWALL);
				showWall(sideWallPosition[7 * 3 + 2], view[7][2], RIGHTWALL);
			}
		}
		else if (view[i][1] == DOOR || view[i][1] == DOOROPEN)
		{
			
				if (isVisible(view[i][0]))
					showWall(frontWallPosition[i * 3], view[i][0], FRONT);
				if (isVisible(view[i][1]))
					if(!DoorAction)
					showWall(frontWallPosition[i * 3 + 1], view[i][1], FRONT);
				if (isVisible(view[i][2]))
					showWall(frontWallPosition[i * 3 + 2], view[i][2], FRONT);
		}
		else
		{
			if (isVisible(view[i][0]))
				showWall(sideWallPosition[i * 3], view[i][0], LEFT);
			if (isVisible(view[i][1]))
				showWall(sideWallPosition[i * 3 + 1], view[i][1], FRONT);
			if (isVisible(view[i][2]))
				showWall(sideWallPosition[i * 3 + 2], view[i][2], RIGHT);
		}
	}
}
void showDoorAnimation(Player player, Labyrinth labyrinth, int mode)
{
	int time = 50;
	if (mode == OPENING)
	{
		Location loc = frontWallPosition[22];
		clrscr();
		viewBuilder(player, labyrinth, true);
		for (int i = 0; i < 20; i++)
		{
			gotoxy(loc.x + 2, loc.y + i + 6);
			for (int j = 0; j < 15; j++)
			{
				if (DoorOpening1[i * 15 + j].c == ' ')
				{
					gotoxy(wherex() + 1, wherey());
				}
				else
				{
					textcolor(DoorOpening1[i * 15 + j].color);
					printf("%c", DoorOpening1[i * 15 + j].c);
				}
			}
		}
		_sleep(time);
		clrscr();
		viewBuilder(player, labyrinth, true);
		for (int i = 0; i < 20; i++)
		{
			gotoxy(loc.x + 2, loc.y + i + 6);
			for (int j = 0; j < 15; j++)
			{
				if (DoorOpening2[i * 15 + j].c == ' ')
				{
					gotoxy(wherex() + 1, wherey());
				}
				else
				{
					textcolor(DoorOpening2[i * 15 + j].color);
					printf("%c", DoorOpening2[i * 15 + j].c);
				}
			}
		}
		_sleep(time);
		clrscr();
		viewBuilder(player, labyrinth, true);
		for (int i = 0; i < 20; i++)
		{
			gotoxy(loc.x + 2, loc.y + i + 6);
			for (int j = 0; j < 15; j++)
			{
				if (DoorOpening3[i * 15 + j].c == ' ')
				{
					gotoxy(wherex() + 1, wherey());
				}
				else
				{
					textcolor(DoorOpening3[i * 15 + j].color);
					printf("%c", DoorOpening3[i * 15 + j].c);
				}
			}
		}
		_sleep(time);
		clrscr();
		viewBuilder(player, labyrinth, true);
		for (int i = 0; i < 20; i++)
		{
			gotoxy(loc.x + 2, loc.y + i + 6);
			for (int j = 0; j < 15; j++)
			{
				if (DoorOpening4[i * 15 + j].c == ' ')
				{
					gotoxy(wherex() + 1, wherey());
				}
				else
				{
					textcolor(DoorOpening4[i * 15 + j].color);
					printf("%c", DoorOpening4[i * 15 + j].c);
				}
			}
		}
		_sleep(time);
		clrscr();
		viewBuilder(player, labyrinth, true);
		for (int i = 0; i < 20; i++)
		{
			gotoxy(loc.x + 2, loc.y + i + 6);
			for (int j = 0; j < 15; j++)
			{
				if (DoorOpening5[i * 15 + j].c == ' ')
				{
					gotoxy(wherex() + 1, wherey());
				}
				else
				{
					textcolor(DoorOpening5[i * 15 + j].color);
					printf("%c", DoorOpening5[i * 15 + j].c);
				}
			}
		}
		_sleep(time);
	}
	else if (mode == CLOSING)
	{
		Location loc = frontWallPosition[22];
		clrscr();
		viewBuilder(player, labyrinth, true);
		for (int i = 0; i < 20; i++)
		{
			gotoxy(loc.x + 2, loc.y + i + 6);
			for (int j = 0; j < 15; j++)
			{
				if (DoorOpening5[i * 15 + j].c == ' ')
				{
					gotoxy(wherex() + 1, wherey());
				}
				else
				{
					textcolor(DoorOpening5[i * 15 + j].color);
					printf("%c", DoorOpening5[i * 15 + j].c);
				}
			}
		}
		_sleep(time);
		clrscr();
		viewBuilder(player, labyrinth, true);
		for (int i = 0; i < 20; i++)
		{
			gotoxy(loc.x + 2, loc.y + i + 6);
			for (int j = 0; j < 15; j++)
			{
				if (DoorOpening4[i * 15 + j].c == ' ')
				{
					gotoxy(wherex() + 1, wherey());
				}
				else
				{
					textcolor(DoorOpening4[i * 15 + j].color);
					printf("%c", DoorOpening4[i * 15 + j].c);
				}
			}
		}
		_sleep(time);
		clrscr();
		viewBuilder(player, labyrinth, true);
		for (int i = 0; i < 20; i++)
		{
			gotoxy(loc.x + 2, loc.y + i + 6);
			for (int j = 0; j < 15; j++)
			{
				if (DoorOpening3[i * 15 + j].c == ' ')
				{
					gotoxy(wherex() + 1, wherey());
				}
				else
				{
					textcolor(DoorOpening3[i * 15 + j].color);
					printf("%c", DoorOpening3[i * 15 + j].c);
				}
			}
		}
		_sleep(time);
		clrscr();
		viewBuilder(player, labyrinth, true);
		for (int i = 0; i < 20; i++)
		{
			gotoxy(loc.x + 2, loc.y + i + 6);
			for (int j = 0; j < 15; j++)
			{
				if (DoorOpening2[i * 15 + j].c == ' ')
				{
					gotoxy(wherex() + 1, wherey());
				}
				else
				{
					textcolor(DoorOpening2[i * 15 + j].color);
					printf("%c", DoorOpening2[i * 15 + j].c);
				}
			}
		}
		_sleep(time);
		clrscr();
		viewBuilder(player, labyrinth, true);
		for (int i = 0; i < 20; i++)
		{
			gotoxy(loc.x + 2, loc.y + i + 6);
			for (int j = 0; j < 15; j++)
			{
				if (DoorOpening1[i * 15 + j].c == ' ')
				{
					gotoxy(wherex() + 1, wherey());
				}
				else
				{
					textcolor(DoorOpening1[i * 15 + j].color);
					printf("%c", DoorOpening1[i * 15 + j].c);
				}
			}
		}
		_sleep(time);
	}
}

void showMenu(int x, int y)
{
	clrscr();
	textcolor(LIGHTGRAY);
	for (int i = 0; i < 45; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (i == 0 || j == 0 || i == 44)
			{
				gotoxy(x + i, y + j);
				putch((char)178);
			}
		}
	}
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 30; j++)
		{
			gotoxy(x + j + 7, y + i + 2);
			textcolor(LIGHTGRAY);
			putch(labyrinthString[30 * i + j]);
		}
	}
	for (int i = 0; i < 45; i++)
	{
		for (int j = 0; j < 15; j++)
		{
			if (i == 0 || j == 0 || i == 44 || j == 14)
			{
				gotoxy(x + i, y + j + 8);
				putch((char)178);
			}
		}
	}
	gotoxy(x + 3, y + 3 + 8);
	cputs("I - Start gry z podstawowym labiryntem");
	gotoxy(x + 4, y + 5 + 8);
	cputs("O - Start gry z wczytanego labiryntu");
	gotoxy(x + 11, y + 7 + 8);
	cputs("E = Edytor labiryntow");
	gotoxy(x + 17, y + 9 + 8);
	cputs("H = Pomoc");
	gotoxy(x + 16, y + 11 + 8);
	cputs("Q = Wyjscie");
}
void showHelp(int x, int y)
{
	char zn;
	do
	{
		clrscr();
		textcolor(LIGHTGRAY);
		for (int i = 0; i < 45; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				if (i == 0 || j == 0 || i == 44)
				{
					gotoxy(x + i, y + j);
					putch((char)178);
				}
			}
		}
		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < 30; j++)
			{
				gotoxy(x + j + 7, y + i + 2);
				textcolor(LIGHTGRAY);
				putch(labyrinthString[30 * i + j]);
			}
		}
		for (int i = 0; i < 45; i++)
		{
			for (int j = 0; j < 26; j++)
			{
				if (i == 0 || j == 0 || i == 44 || j == 25)
				{
					gotoxy(x + i, y + j + 8);
					putch((char)178);
				}
			}
		}
		gotoxy(x + 3, y + 3 + 8);
		cputs("Strzalki gora/dol - poruszanie przod/tyl");
		gotoxy(x + 4, y + 5 + 8);
		cputs("Strzalki prawo/lewo - obrot prawo/lewo");
		gotoxy(x + 7, y + 7 + 8);
		cputs("Spacja - Zmiana koloru gracza");
		gotoxy(x + 12, y + 9 + 8);
		cputs("R - Reset labiryntu");
		gotoxy(x + 7, y + 11 + 8);
		cputs("D - Otwieranie/zamykanie drzwi");
		gotoxy(x + 4, y + 13 + 8);
		cputs("I - Wczytanie podstawowego labiryntu");
		gotoxy(x + 7, y + 15 + 8);
		cputs("O - Wczytanie labiryntu z pliku");
		gotoxy(x + 11, y + 17 + 8);
		cputs("E - Edytor labiryntow");
		gotoxy(x + 17, y + 19 + 8);
		cputs("H - Pomoc");
		gotoxy(x + 16, y + 21 + 8);
		cputs("Q - Wyjscie");
		gotoxy(x + 32, y + 23 + 8);
		cputs("P - Powrot");
		zn = getch();
	} while (zn != 'p');
}
void showData(Player player, clock_t tStart)
{
	int x = 1;
	int y = 1;
	textcolor(LIGHTGRAY);
	for (int i = 0; i < 56; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			if (i == 0 || j == 0 || i == 55)
			{
				gotoxy(x + i, y + j);
				putch((char)178);
			}
		}
	}
	gotoxy(x + 6, y + 2);
	printf("Ruchy: %i", player.movements);
	gotoxy(x + 19, y + 2);
	printf("Czas: %.2fs\n", (double)(clock() - tStart) / CLOCKS_PER_SEC);
	gotoxy(x + 36, y + 2);
	puts("H - Pomoc");
}
void showWin(Player player, time_t tStart,int x, int y)
{
	char zn;
	do
	{
		clrscr();
		textcolor(LIGHTGRAY);
		for (int i = 0; i < 45; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				if (i == 0 || j == 0 || i == 44)
				{
					gotoxy(x + i, y + j);
					putch((char)178);
				}
			}
		}
		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < 34; j++)
			{
				gotoxy(x + j + 5, y + i + 2);
				textcolor(LIGHTGRAY);
				putch(winString[34 * i + j]);
			}
		}
		for (int i = 0; i < 45; i++)
		{
			for (int j = 0; j < 13; j++)
			{
				if (i == 0 || j == 0 || i == 44 || j == 12)
				{
					gotoxy(x + i, y + j + 8);
					putch((char)178);
				}
			}
		}
		gotoxy(x + 7, y + 11);
		puts("Gratulacje! Przeszedles labirynt.");
		gotoxy(x + 13, y + 13);
		printf("Wykonales %i ruchow.", player.movements);
		gotoxy(x + 15, y + 15);
		printf("W czasie %.2fs\n", (double)(clock() - tStart) / CLOCKS_PER_SEC);
		gotoxy(x + 36, y + 17);
		printf("O - Ok");
		zn = getch();
	} while (zn != 'o');
}
