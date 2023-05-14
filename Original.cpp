#include <graphics.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <array>
#include <windows.h>
#include <string>
#include <conio.h>
#include <time.h>
#include "block.h"

// nested array of the blocks
std::array<std::array<block, 4>, 4> game;

// judge
int win_loss()
{
	int gameover{ 0 };

	for (int i{}; i <= 3; i++)
	{
		for (int j{}; j <= 3; j++)
		{
			if (game.at(i).at(j).getflag() == 11)
				return 2;
		}
	}

	for (int i{}; i <= 3; i++)
	{
		for (int j{}; j <= 3; j++)
		{
			if (!game.at(i).at(j).getflag())
				return 1;
		}
	}

	for (int i{}; i <= 3; i++)
	{
		for (int j{}; j <= 2; j++)
		{
			if (game.at(i).at(j).getflag() == game.at(i).at(j + 1).getflag())
				return 1;
		}
	}

	for (int i{}; i <= 2; i++)
	{
		for (int j{}; j <= 3; j++)
		{
			if (game.at(i).at(j).getflag() == game.at(i + 1).at(j).getflag())
				return 1;
		}
	}

	return 0;
}

// spawn new blocks
void make_random_block()
{
	size_t count{};
	std::vector<size_t> line;
	std::vector<size_t> colume;
	//srand((unsigned)time(NULL));

	for (size_t i{}; i <= 3; i++)
	{
		for (size_t j{}; j <= 3; j++)
		{
			if (game.at(i).at(j).getflag() == 0)
			{
				count++;
				line.push_back(i);
				colume.push_back(j);
			}
		}
	}

	int r = rand() % count;
	if (rand() % 5 == 0)
	{
		game.at(line.at(r)).at(colume.at(r)).draw_number(2);
		game.at(line.at(r)).at(colume.at(r)).change(2);
	}
	else
	{
		game.at(line.at(r)).at(colume.at(r)).draw_number(1);
		game.at(line.at(r)).at(colume.at(r)).change(1);
	}
}

// make movement
void move(const char a)
{
	int front_flag, back_flag;

	if (a == 'a')
	{
		for (int k{}; k <= 3; k++)
		{
			for (int i{}; i <= 2; i++)
			{
				for (int j{ i + 1 }; j <= 3; j++)
				{
					front_flag = game.at(k).at(i).getflag(), back_flag = game.at(k).at(j).getflag();

					if (front_flag && front_flag == back_flag)
					{
						game.at(k).at(i).change(front_flag + 1);
						game.at(k).at(j).change(0);
						//i = j-1;
						break;
					}

					if ((front_flag && back_flag) && front_flag != back_flag)
						break;

					if (!front_flag && back_flag)
					{
						game.at(k).at(i).change(back_flag);
						game.at(k).at(j).change(0);
						continue;
					}
				}
			}
		}
	}

	if (a == 's')
	{
		for (int k{}; k <= 3; k++)
		{
			for (int i{ 3 }; i >= 1; i--)
			{
				for (int j{ i - 1 }; j >= 0; j--)
				{
					front_flag = game.at(i).at(k).getflag(), back_flag = game.at(j).at(k).getflag();

					if (front_flag && front_flag == back_flag)
					{
						game.at(i).at(k).change(front_flag + 1);
						game.at(j).at(k).change(0);
						break;
					}

					if ((front_flag && back_flag) && front_flag != back_flag)
						break;

					if (!front_flag && back_flag)
					{
						game.at(i).at(k).change(back_flag);
						game.at(j).at(k).change(0);
						continue;
					}
				}
			}
		}
	}

	if (a == 'w')
	{
		for (int k{}; k <= 3; k++)
		{
			for (int i{}; i <= 2; i++)
			{
				for (int j{ i + 1 }; j <= 3; j++)
				{
					front_flag = game.at(i).at(k).getflag(), back_flag = game.at(j).at(k).getflag();

					if (front_flag && front_flag == back_flag)
					{
						game.at(i).at(k).change(front_flag + 1);
						game.at(j).at(k).change(0);
						break;
					}

					if ((front_flag && back_flag) && front_flag != back_flag)
						break;

					if (!front_flag && back_flag)
					{
						game.at(i).at(k).change(back_flag);
						game.at(j).at(k).change(0);
						continue;
					}
				}
			}
		}
	}

	if (a == 'd')
	{
		for (int k{}; k <= 3; k++)
		{
			for (int i{ 3 }; i >= 1; i--)
			{
				for (int j{ i - 1 }; j >= 0; j--)
				{
					front_flag = game.at(k).at(i).getflag(), back_flag = game.at(k).at(j).getflag();

					if (front_flag && front_flag == back_flag)
					{
						game.at(k).at(i).change(front_flag + 1);
						game.at(k).at(j).change(0);
						break;
					}

					if ((front_flag && back_flag) && front_flag != back_flag)
						break;

					if (!front_flag && back_flag)
					{
						game.at(k).at(i).change(back_flag);
						game.at(k).at(j).change(0);
						continue;
					}
				}
			}
		}
	}

	for (size_t i{}; i <= 3; i++)
	{
		for (size_t j{}; j <= 3; j++)
		{
			game.at(i).at(j).draw_number(game.at(i).at(j).getflag());
		}
	}
}

int main()
{
	char movement;
	initgraph(length, width);
	setbkcolor(BLACK);
	cleardevice();
	//给每个格子初始化
	for (int i{ }; i <= 3; i++)
	{
		for (int j{ }; j <= 3; j++)
		{
			game.at(i).at(j).change(j * (cube + gap), i * (cube + gap), 0);
			game.at(i).at(j).draw_number(0);
		}
	}
	//game.at(2).at(3).draw_number(6);

	srand((unsigned)time(NULL));
	make_random_block();
	while (1)
	{
		movement = _getch();
		move(movement);
		Sleep(100);
		make_random_block();
		switch (win_loss())
		{
		case 2:
			closegraph();			// 关闭绘图窗口
			std::cout << "恭喜你赢了~~~";
			getchar();
			system("pause");
			break;
		case 0:
			closegraph();			// 关闭绘图窗口
			std::cout << "很遗憾，下次一定！";
			getchar();
			system("pause");
			break;
		}
	}
}