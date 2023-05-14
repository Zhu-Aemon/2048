#include <graphics.h>
#include <iostream>
#include <conio.h>

class Game
{
	// graphic dimensions
	const int block_size, block_gap, block_total_size;

	// game configurations
	const int goal = 11;
	const int col, lin;
	int empty_block_count, * blocks, * empty_blocks;

	// runtime parameters
	int step1, step2, offset, range, subrange, status = 0;

	// rendering parameters
	const static char* const content[];
	const static int color[];

public:
	Game(int col, int lin) :
		col(col),
		lin(lin),
		block_size((col > lin ? 500 / (col + 4) : 500 / (lin + 4)) + 1),
		block_gap(block_size / 20),
		block_total_size(block_size + 2 * block_gap)
	{
		step1 = col;
		step2 = 1;
		offset = 0;
		range = lin;
		subrange = col;
		empty_block_count = col * lin;
		blocks = new int[empty_block_count]();
		if (col >= lin)
		{
			empty_blocks = new int[col];
			for (int i = 0; i < col; i++)
				empty_blocks[i] = lin;
		}
		else
		{
			empty_blocks = new int[lin]();
			for (int i = 0; i < lin; i++)
				empty_blocks[i] = col;
		}
		srand((unsigned int)time(NULL));
		initgraph(col * block_total_size, lin * block_total_size);
		setbkcolor(BLACK);
		settextcolor(BLACK);
		settextstyle(block_size * 3 / 8, block_size / 4, "ºÚÌå");
		cleardevice();
		spawn();
		render();
	}

	void render()
	{
		int* current_flag = blocks;
		for (int i = 0, y = block_gap; i++ < lin; y += block_total_size)
		{
			for (int j = 0, x = block_gap; j++ < col; x += block_total_size)
			{
				setfillcolor(color[*current_flag]);
				setbkcolor(color[*current_flag]);
				solidrectangle(x, y, x + block_size, y + block_size);
				RECT text_box = { x,y,x + block_size,y + block_size };
				drawtext(content[*current_flag], &text_box, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				current_flag++;
			}
		}
	}

	int judge()
	{
		if (empty_block_count)
			return 0;
		int* current_num = blocks;
		for (int i = 0; i < lin - 1; i++)
		{
			for (int j = 0; j < col - 1; j++)
			{
				if (*current_num == *(current_num + 1) ||
					*current_num == *(current_num + col))
					return 0;
				current_num++;
			}
			if (*current_num == *(current_num + col))
				return 0;
			current_num++;
		}
		for (int j = 0; j < col - 1; j++)
		{
			if (*current_num == *(current_num + 1))
				return 0;
			current_num++;
		}
		std::cout << "What a pity, you lost the game..." << std::endl;
		return -1;
	}

	void spawn()
	{
		int chosen = rand() % empty_block_count--, i = 0;
		while (chosen >= empty_blocks[i])
		{
			chosen -= empty_blocks[i];
			i++;
		}
		chosen = i * step1 + (subrange - chosen - 1) * step2 + offset;
		int* chosen_block = blocks + chosen;
		if (rand() % 5)
			*chosen_block = 1;
		else *chosen_block = 2;
	}

	int make_movement(int direction)
	{
		switch (direction)
		{
		case 'a':
			step1 = col;
			step2 = 1;
			offset = 0;
			range = lin;
			subrange = col;
			break;
		case 'd':
			step1 = col;
			step2 = -1;
			offset = col - 1;
			range = lin;
			subrange = col;
			break;
		case 'w':
			step1 = 1;
			step2 = col;
			offset = 0;
			range = col;
			subrange = lin;
			break;
		case 's':
			step1 = 1;
			step2 = -col;
			offset = col * (lin - 1);
			range = col;
			subrange = lin;
			break;
		case VK_ESCAPE:
			status = -1;
			return 1;
		default:
			return 0;
		}

		int* current_block = blocks + offset, * top = current_block;
		empty_block_count = 0;

		for (int i = 0; i < range; i++)
		{
			for (int j = 1; j < subrange; j++)
			{
				current_block += step2;
				if (*current_block)
				{
					int tmp = *current_block;
					*current_block = 0;
					if (*top)
					{
						if (*top == tmp)
						{
							*top += 1;
							if (*top == goal)
							{
								std::cout << "Congratulations! You won the game!" << std::endl;
								status = 1;
								return 1;
							}
							top += step2;
						}
						else
						{
							top += step2;
							*top = tmp;
						}
					}
					else
						*top = tmp;
				}
			}

			empty_blocks[i] = (current_block - top) / step2;
			if (*top == 0)
				empty_blocks[i] += 1;
			empty_block_count += empty_blocks[i];
			current_block += step1 - (subrange - 1) * step2;
			top = current_block;
		}

		if (empty_block_count == 0)
			return 0;

		spawn();
		render();
		status = judge();
		return 1;
	}

	operator bool()
	{
		return status == 0;
	}

	~Game()
	{
		closegraph();
		delete[] blocks;
		delete[] empty_blocks;
	}
};

const char* const Game::content[] = { " ","2","4","8","16","32","64","128","256","512","1024","2048","4096","8192" };

const int Game::color[] = {
	0x555555,
	0xffffff,
	0xdddddd,
	0xbbbbbb,
	0x999999,
	0x77dddd,
	0x55ffff,
	0x3399ff,
	0x0077ff,
	0x0055ff,
	0x0033dd,
	0x0000bb,
	0x3333dd,
	0x5555ff
};

int main()
{
	int col, lin;
	goto init;
	while (TRUE)
	{
		{
			Game game(col, lin);
			while (game)
				game.make_movement(_getch());
		}

		std::cout << "Do you wanna try again? [y/n]" << std::endl;
		if (_getch() != 'y')
			break;
		std::cout << "Do you wanna change the configurations? [y/n]" << std::endl;
		if (_getch() != 'y')
			continue;
init:
		std::cout << "Set column: ";
		std::cin >> col;
		std::cout << "Set line: ";
		std::cin >> lin;
	}

	std::cout << "Thank you for playing the game! Have a nice day!" << std::endl;
	return 0;
}