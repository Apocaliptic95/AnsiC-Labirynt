#include <iostream>
#include <cstdio>
#include "conio2.h"
#include "graphics.h"

/* Uwaga: w docelowym programie nalezy zadeklarowac odpowiednie
   stale, na przyklad po to, aby wyeliminowac z programu
   wartosci numeryczne umieszczajac w ich miejsce 
   dobrze dobrane identyfikatory */

void DoorAction(int x, int y, Player player, Labyrinth labyrinth);

int main()
{
	char zn, attr = 7;	
	Player player;
	Labyrinth labyrinth;
	Game game;
	settitle("imie nazwisko nr_indeksu");
	textbackground(BLACK);
	bool exit = false;
	bool quit = false;
	do
	{
		do
		{
			showMenu(6, 6);
			zn = getch();
			if (zn == 'o')
			{
				labyrinth.getLabFromFile();
				int error = labyrinth.isProper();
				if (error == MULTIPLEEXIT)
				{
					clrscr();
					gotoxy(1, 1);
					printf("Wczytany labirynt ma nieprawidlowa ilosc wyjsc.");
					gotoxy(1, 2);
					printf("Nacisnij dowolny klawisz aby kontynuowac...");
					getch();
					labyrinth.getDefaultLab();
					game.reset(&player, &labyrinth);
				}
				if (error == LARGEEMPTYAREA)
				{
					clrscr();
					gotoxy(1, 1);
					printf("Wczytany labirynt zawiera duze pola puste.");
					gotoxy(1, 2);
					printf("Nacisnij dowolny klawisz aby kontynuowac...");
					getch();
					labyrinth.getDefaultLab();
					game.reset(&player, &labyrinth);
				}
				if (error == PROPER)
				{
					exit = true;
					game.reset(&player, &labyrinth);
				}
			}
			else if (zn == 'i')
			{
				labyrinth.getDefaultLab();
				game.reset(&player, &labyrinth);
				exit = true;
			}
			else if (zn == 'e')
			{
				Editor editor;
				labyrinth = editor.StartEditor();
				game.reset(&player, &labyrinth);
				exit = true;
			}
			else if (zn == 'h')
			{
				showHelp(6, 6);
			}
			else if (zn == 'q')
			{
				quit = true;
				exit = true;
			}
		} while (!exit);
		if (!quit)
		{
			if (labyrinth.readed)
			{
				player.form = 'v';
				player.dir.down = true;
				player.pos = labyrinth.start;
				game.startTimer();
				do {
					clrscr();
					viewBuilder(player, labyrinth, false);
					int horpos = max(55, labyrinth.Width);
					horpos = 1 + (horpos - labyrinth.Width) / 2;
					labyrinth.printLab(horpos, 30);
					showData(player, game.tStart);
					player.showPlayer(horpos, 30, attr);
					if (player.pos.x == labyrinth.end.x && player.pos.y == labyrinth.end.y)
					{
						showWin(player,game.tStart,6,6);
						zn = 'q';
					}
					else
					{
						zn = getch();
						if (zn == 0)
						{
							zn = getch();
							if (zn == 0x48)
								player.goForward(labyrinth);
							else if (zn == 0x50)
								player.goBack(labyrinth);
							else if (zn == 0x4b)
								player.turnRight();
							else if (zn == 0x4d)
								player.turnLeft();
						}
						else if (zn == ' ')
						{
							attr = (attr + 1) % 16;
						}
						else if (zn == 'r')
						{
							game.reset(&player, &labyrinth);
						}
						else if (zn == 'o')
						{
							labyrinth.getLabFromFile();
							int error = labyrinth.isProper();
							if (error == MULTIPLEEXIT)
							{
								clrscr();
								gotoxy(1, 1);
								printf("Wczytany labirynt ma nieprawidlowa ilosc wyjsc.");
								gotoxy(1, 2);
								printf("Nacisnij dowolny klawisz aby kontynuowac...");
								getch();
								labyrinth.getDefaultLab();
								game.reset(&player, &labyrinth);
							}
							if (error == LARGEEMPTYAREA)
							{
								clrscr();
								gotoxy(1, 1);
								printf("Wczytany labirynt zawiera duze pola puste.");
								gotoxy(1, 2);
								printf("Nacisnij dowolny klawisz aby kontynuowac...");
								getch();
								labyrinth.getDefaultLab();
								game.reset(&player, &labyrinth);
							}
							if (error == PROPER)
							{
								game.reset(&player, &labyrinth);
							}
						}
						else if (zn == 'i')
						{
							labyrinth.getDefaultLab();
							game.reset(&player, &labyrinth);
						}
						else if (zn == 'e')
						{
							Editor editor;
							labyrinth = editor.StartEditor();
							game.reset(&player, &labyrinth);
						}
						else if (zn == 'd')
						{
							if (player.dir.up == true)
								DoorAction(player.pos.x, player.pos.y - 1, player, labyrinth);
							else if (player.dir.down == true)
								DoorAction(player.pos.x, player.pos.y + 1, player, labyrinth);
							else if (player.dir.left == true)
								DoorAction(player.pos.x - 1, player.pos.y, player, labyrinth);
							else if (player.dir.right == true)
								DoorAction(player.pos.x + 1, player.pos.y, player, labyrinth);
						}
						else if (zn == 'h')
						{
							clock_t now = game.tStart;
							showHelp(6, 6);
							game.tStart = now;
						}
					}
				} while (zn != 'q');
				exit = false;
			}
			else
			{
				gotoxy(1, 1);
				puts("Blad odczytu.");
				getch();
			}
		}
	} while (!quit);
	return 0;
}

void DoorAction(int x, int y, Player player, Labyrinth labyrinth)
{
	if (labyrinth.isDoor(x, y))
	{
		showDoorAnimation(player, labyrinth, 0);
		x--;
		y--;
		labyrinth.lab[y][x] = DOOROPEN;
	}
	else if (labyrinth.isDoorOpen(x, y))
	{
		showDoorAnimation(player, labyrinth, 1);
		x--;
		y--;
		labyrinth.lab[y][x] = DOOR;
	}
}
