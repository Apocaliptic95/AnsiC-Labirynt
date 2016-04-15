#include "conio2.h"
#include <ctime>
#include <string.h>
#include <stdio.h>
#include <cstdlib>

#define TREE '#'
#define WALL (char)178
#define STONE (char)15
#define BUSH (char)176
#define STATUE (char)206
#define DOOR (char)219
#define DOOROPEN 'O'
#define NOTHING ' '

#define PROPER 0
#define MULTIPLEEXIT 1
#define LARGEEMPTYAREA 2

class Player;
class Game;
class Labyrinth;
class Editor;

struct Direction
{
	bool left = false;
	bool right = false;
	bool up = false;
	bool down = false;
};

struct Position
{
	int x;
	int y;
};

bool FileExists(const char *filename)
{
	FILE *fp;
	int err = fopen_s(&fp,filename, "r");
	if (err == 0)
		return true;
	else
		return false;
}
int max(int a, int b)
{
	if (a > b)
		return a;
	else
		return b;
}

class Labyrinth
{
public:
	char** lab;
	int Height;
	int Width;
	bool readed = false;
	Position start;
	Position end;
	bool colide = true;

	bool isFree(int x, int y)
	{
		x--;
		y--;
		if (isInside(x, y))
		{
			if (lab[y][x] == NOTHING || !colide || lab[y][x] == DOOROPEN)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		else
		{
			return false;
		}
	}
	bool isDoor(int x, int y)
	{
		x--;
		y--;
		if (isInside(x, y))
		{
			if (lab[y][x] == DOOR)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		else
		{
			return false;
		}
	}
	bool isDoorOpen(int x, int y)
	{
		x--;
		y--;
		if (isInside(x, y))
		{
			if (lab[y][x] == DOOROPEN)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		else
		{
			return false;
		}
	}
	void getLab(char* inFileName)
	{
		FILE* filePointer;

		if (!fopen_s(&filePointer, inFileName, "r"))
		{
			fscanf_s(filePointer, "%i", &Height);
			fscanf_s(filePointer, "%i", &Width);
			fgetc(filePointer);
			char** tempLab = new char*[Height];
			for (int i = 0; i < Height; i++)
			{
				tempLab[i] = new char[Width];
			}
			for (int i = 0; i < Height; i++)
			{
				for (int j = 0; j < Width; j++)
				{
					char in = fgetc(filePointer);
					if (in == '0')
					{
						tempLab[i][j] = NOTHING;
					}
					else if (in == '1')
					{
						if (i == 0 || j == 0 || i == Height - 1 || j == Width - 1)
							tempLab[i][j] = WALL;
						else
						{
							int x = (rand() % 4);
							char c;
							switch (x)
							{
							case 0: c = STATUE; break;
							case 1: c = STONE; break;
							case 2: c = TREE; break;
							case 3: c = BUSH; break;
							default: c = WALL; break;
							}
							tempLab[i][j] = c;
						}
					}
					else if (in == '2')
					{
						tempLab[i][j] = DOOR;
					}
				}
				fgetc(filePointer);
			}
			fclose(filePointer);
			lab = tempLab;
			setStartAndExit();
			readed = true;
		}
		else
		{
			printf("Brak pliku: %s", inFileName);
			readed = false;
		}
	}
	int isProper()
	{
		int exitCount = 0;

		for (int i = 0; i < Width; i++)
			if (lab[0][i] == NOTHING)
				exitCount++;
		for (int i = 0; i < Height; i++)
			if (lab[i][0] == NOTHING)
				exitCount++;
		for (int i = 0; i < Height; i++)
			if (lab[i][Width - 1] == NOTHING)
				exitCount++;
		for (int i = 0; i < Width; i++)
			if (lab[Height - 1][i] == NOTHING)
				exitCount++;
		if (exitCount != 2)
			return MULTIPLEEXIT;

		for (int i = 0; i < Height; i++)
			for (int j = 0; j < Width; j++)
				if (isInside(j, i))
					if (lab[i][j] == NOTHING)
						if (isInside(j, i + 1))
							if (lab[i + 1][j] == NOTHING)
								if (isInside(j + 1, i))
									if (lab[i][j + 1] == NOTHING)
										if (isInside(j + 1, i + 1))
											if (lab[i + 1][j + 1] == NOTHING)
												return LARGEEMPTYAREA;

		return PROPER;
	}
	void getLabFromFile()
	{
		clrscr();
		char name[30];
		gotoxy(1, 1);
		printf("Podaj nazwe pliku:");
		gets_s(name, 30);
		char location[50] = "Labyrinths/";
		memcpy(&location[11], name, sizeof(name) - 1);
		getLab(location);
	}
	void getDefaultLab()
	{
		getLab("Labyrinths/default.lab");
	}
	void printLab(int x,int y)
	{
		textcolor(7);
		gotoxy(x, y);
		srand((int)time(NULL));
		for (int i = 0; i < Height; i++)
		{
			gotoxy(x, y + i);
			for (int j = 0; j < Width; j++)
			{
				char c = lab[i][j];
				switch (c)
				{
				case WALL: textcolor(RED); break;
				case TREE: textcolor(GREEN); break;
				case STONE: textcolor(DARKGRAY); break;
				case BUSH: textcolor(LIGHTGREEN); break;
				case STATUE: textcolor(YELLOW); break;
				case DOOR: textcolor(BROWN); break;
				case DOOROPEN: textcolor(BROWN); break;
				default: textcolor(LIGHTGRAY); break;
				}
				printf("%c", c);
			}
		}
	}
	bool isInside(int x, int y)
	{
		if (x >= 0 && y >= 0 && x < Width && y < Height)
			return true;
		else
			return false;
	}
	void setStartAndExit()
	{
		bool startFound = false;
		start.x = 0;
		start.y = 0;
		bool endFound = false;
		end.x = 0;
		end.y = 0;

		for (int i = 0; i < Height; i++)
		{
			for (int j = 0; j < Width; j++)
			{
				if (i == 0 || i == Height - 1 || j == 0 || j == Width - 1)
				{
					if (lab[i][j] == NOTHING)
					{
						if (!startFound)
						{
							start.x = j + 1;
							start.y = i + 1;
							startFound = true;
						}
						else if (!endFound)
						{
							end.x = j + 1;
							end.y = i + 1;
							endFound = true;
						}
					}
				}
			}
		}
	}
	void saveToFile()
	{
		int err = isProper();
		if (err == PROPER)
		{
			clrscr();
			char name[30];
			gotoxy(1, 1);
			printf("Podaj nazwe pliku:");
			gets_s(name, 30);
			char location[50] = "Labyrinths/";
			memcpy(&location[11], name, sizeof(name) - 1);
			FILE* filePointer;
			if (!FileExists(location))
			{
				if (!fopen_s(&filePointer, location, "w"))
				{
					fprintf_s(filePointer, "%i ", Height);
					fprintf_s(filePointer, "%i\n", Width);
					for (int i = 0; i < Height; i++)
					{
						for (int j = 0; j < Width; j++)
						{
							if (lab[i][j] == NOTHING)
							{
								fprintf(filePointer, "0");
							}
							else if (lab[i][j] == DOOR)
							{
								fprintf(filePointer, "2");
							}
							else
							{
								fprintf(filePointer, "1");
							}
						}
						fprintf(filePointer, "\n");
					}
					fclose(filePointer);
				}
				else
				{
					clrscr();
					printf("Nie mozna utworzyc pliku: %s", location);
				}
			}
			else
			{
				clrscr();
				printf("Plik juz istnieje.");
			}
		}
		else if (err == MULTIPLEEXIT)
		{
			clrscr();
			gotoxy(1, 1);
			printf("Wczytany labirynt ma nieprawidlowa ilosc wyjsc.");
			gotoxy(1, 2);
			printf("Nacisnij dowolny klawisz aby kontynuowac...");
			getch();
		}
		else if (err == LARGEEMPTYAREA)
		{
			clrscr();
			gotoxy(1, 1);
			printf("Wczytany labirynt zawiera duze pola puste.");
			gotoxy(1, 2);
			printf("Nacisnij dowolny klawisz aby kontynuowac...");
			getch();
		}
	}
	void closeAllDoors()
	{
		for (int i = 0;i < Height;i++)
			for (int j = 0; j < Width; j++)
				if (lab[i][j] == DOOROPEN)
					lab[i][j] = DOOR;
	}
};
class Player
{
public:
	Direction dir;
	Position pos;
	char form = 'v';
	int movements = 0;

	void turnLeft()
	{
		if (dir.up)
		{
			dir.up = false;
			dir.left = false;
			dir.right = true;
			dir.down = false;
			form = '>';
		}
		else if (dir.down)
		{
			dir.up = false;
			dir.left = true;
			dir.right = false;
			dir.down = false;
			form = '<';
		}
		else if (dir.left)
		{
			dir.up = true;
			dir.left = false;
			dir.right = false;
			dir.down = false;
			form = '^';
		}
		else if (dir.right)
		{
			dir.up = false;
			dir.left = false;
			dir.right = false;
			dir.down = true;
			form = 'v';
		}
	}
	void turnRight()
	{
		if (dir.up)
		{
			dir.up = false;
			dir.left = true;
			dir.right = false;
			dir.down = false;
			form = '<';
		}
		else if (dir.down)
		{
			dir.up = false;
			dir.left = false;
			dir.right = true;
			dir.down = false;
			form = '>';
		}
		else if (dir.left)
		{
			dir.up = false;
			dir.left = false;
			dir.right = false;
			dir.down = true;
			form = 'v';
		}
		else if (dir.right)
		{
			dir.up = true;
			dir.left = false;
			dir.right = false;
			dir.down = false;
			form = '^';
		}
	}
	void goForward(Labyrinth lab)
	{
		if (dir.up)
		{
			if (lab.isFree(pos.x, pos.y - 1))
			{
				pos.y--;
				movements++;
			}
		}
		else if (dir.down)
		{
			if (lab.isFree(pos.x, pos.y + 1))
			{
				pos.y++;
				movements++;
			}
		}
		else if (dir.right)
		{
			if (lab.isFree(pos.x + 1, pos.y))
			{
				pos.x++;
				movements++;
			}
		}
		else if (dir.left)
		{
			if (lab.isFree(pos.x - 1, pos.y))
			{
				pos.x--;
				movements++;
			}
		}
	}
	void goBack(Labyrinth lab)
	{
		if (dir.up)
		{
			if (lab.isFree(pos.x, pos.y + 1))
			{
				pos.y++;
				movements++;
			}
		}
		else if (dir.down)
		{
			if (lab.isFree(pos.x, pos.y - 1))
			{
				pos.y--;
				movements++;
			}
		}
		else if (dir.right)
		{
			if (lab.isFree(pos.x - 1, pos.y))
			{
				pos.x--;
				movements++;
			}
		}
		else if (dir.left)
		{
			if (lab.isFree(pos.x + 1, pos.y))
			{
				pos.x++;
				movements++;
			}
		}
	}
	void showPlayer(int x,int y,int attr)
	{
		x--;
		y--;
		gotoxy(x+pos.x,y+pos.y);
		textcolor(attr);
		putch(form);
		textcolor(LIGHTGRAY);
	}
};
class Game
{
public:
	clock_t tStart;
	void reset(Player* player, Labyrinth* lab)
	{
		player->movements = 0;
		player->pos.x = lab->start.x;
		player->pos.y = lab->start.y;
		lab->closeAllDoors();
		tStart = clock();
	}
	void startTimer()
	{
		tStart = clock();
	}
};
class Editor
{
public:
	void showMenu(int x, int y, int width)
	{
		textcolor(LIGHTGRAY);
		for (int i = 0; i < width; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				if (i == 0 || j == 0 || i == width-1 || j == 7)
				{
					gotoxy(x + i, y + j);
					putch((char)178);
				}
			}
		}
		gotoxy(x + 2, y + 2);
		cputs("Q = Wyjdz i graj");
		gotoxy(x + 2, y + 3);
		cputs("O = Wczytaj labirynt z pliku");
		gotoxy(x + 2, y + 4);
		cputs("S = Zapis labiryntu do pliku");
		gotoxy(x + 33, y + 2);
		cputs("W = Dodaj sciane");
		gotoxy(x + 33, y + 3);
		cputs("D = Dodaj drzwi");
		gotoxy(x + 33, y + 4);
		cputs("N = Dodaj puste pole");
	}
	Labyrinth StartEditor()
	{
		Labyrinth labyrinth;
		labyrinth.colide = false;

		clrscr();
		gotoxy(1, 1);
		printf("Podaj wysokosc:");
		scanf("%i", &labyrinth.Height);
		gotoxy(1, 2);
		printf("Podaj szerokosc:");
		scanf("%i", &labyrinth.Width);
		labyrinth.lab = new char*[labyrinth.Height];
		for (int i = 0; i < labyrinth.Height; i++)
		{
			labyrinth.lab[i] = new char[labyrinth.Width];
		}
		for (int i = 0; i < labyrinth.Height; i++)
		{
			for (int j = 0; j < labyrinth.Width; j++)
			{
				labyrinth.lab[i][j] = NOTHING;
			}
		}
		Player player;
		player.form = '+';
		player.pos.x = 1;
		player.pos.y = 1;
		char zn;
		do
		{
			clrscr();
			int editorWidth = max(55, labyrinth.Width+2);
			showMenu(1, 1, editorWidth);
			textcolor(LIGHTGRAY);
			for (int i = 0; i < labyrinth.Width + 2; i++)
			{
				for (int j = 0; j < labyrinth.Height+2; j++)
				{
					if (i == 0 || i == labyrinth.Width + 1 || j == labyrinth.Height + 1)
					{
						gotoxy(i + (editorWidth- labyrinth.Width)/2, 8 + j);
						putch((char)178);
					}
				}
			}
			labyrinth.printLab(1 + (editorWidth - labyrinth.Width) / 2, 9);
			player.showPlayer(1 + (editorWidth - labyrinth.Width) / 2, 9, LIGHTBLUE);

			zn = getch();
			if (zn == 0)
			{
				zn = getch();
				if (zn == 0x48)
				{
					player.dir.up = true;
					player.dir.down = false;
					player.dir.right = false;
					player.dir.left = false;
					player.goForward(labyrinth);
				}
				else if (zn == 0x50)
				{
					player.dir.up = false;
					player.dir.down = true;
					player.dir.right = false;
					player.dir.left = false;
					player.goForward(labyrinth);
				}
				else if (zn == 0x4b)
				{
					player.dir.up = false;
					player.dir.down = false;
					player.dir.right = false;
					player.dir.left = true;
					player.goForward(labyrinth);
				}
				else if (zn == 0x4d)
				{
					player.dir.up = false;
					player.dir.down = false;
					player.dir.right = true;
					player.dir.left = false;
					player.goForward(labyrinth);
				}
			}
			else if (zn == 'o')
			{
				labyrinth.getLabFromFile();
			}
			else if (zn == 's')
			{
				labyrinth.saveToFile();
			}
			else if (zn == 'w')
			{
				int x = wherex() - (2 + (editorWidth - labyrinth.Width) / 2);
				int y = wherey() - 9;
				if (x == 0 || y == 0 || y == labyrinth.Height - 1 || x == labyrinth.Width - 1)
					labyrinth.lab[y][x] = WALL;
				else
				{
					int r = (rand() % 4);
					char c;
					switch (r)
					{
					case 0: c = STATUE; break;
					case 1: c = STONE; break;
					case 2: c = TREE; break;
					case 3: c = BUSH; break;
					default: c = WALL; break;
					}
					labyrinth.lab[y][x] = c;
				}
			}
			else if (zn == 'd')
			{
				int x = wherex() - (2 + (editorWidth - labyrinth.Width) / 2);
				int y = wherey() - 9;
				if (x == 0 || y == 0 || y == labyrinth.Height - 1 || x == labyrinth.Width - 1)
					labyrinth.lab[y][x] = WALL;
				else
				{
					labyrinth.lab[y][x] = DOOR;
				}
			}
			else if (zn == 'n')
			{
				int x = wherex() - (2 + (editorWidth - labyrinth.Width) / 2);
				int y = wherey() - 9;
				labyrinth.lab[y][x] = NOTHING;
			}
			else if(zn == 'q')
			{
				int err = labyrinth.isProper();
				if (err == MULTIPLEEXIT)
				{
					clrscr();
					gotoxy(1, 1);
					printf("Wczytany labirynt ma nieprawidlowa ilosc wyjsc.");
					gotoxy(1, 2);
					printf("Nacisnij dowolny klawisz aby kontynuowac...");
					getch();
					zn = '1';
				}
				else if (err == LARGEEMPTYAREA)
				{
					clrscr();
					gotoxy(1, 1);
					printf("Wczytany labirynt zawiera duze pola puste.");
					gotoxy(1, 2);
					printf("Nacisnij dowolny klawisz aby kontynuowac...");
					getch();
					zn = '1';
				}
				else if (err == PROPER)
				{
					labyrinth.readed = true;
				}
			}
		} while (zn != 'q');
		labyrinth.setStartAndExit();
		labyrinth.colide = true;
		return labyrinth;
	}
};
