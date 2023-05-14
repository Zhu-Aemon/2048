#pragma once

// sizes
const int length{ 335 }, width{ 335 };
const int cube{ 80 }, gap{ 5 };

//  render contents
std::array<const char*, 12>number{ "0","2","4","8","16","32","64","128","256","512","1024","2048" };

class block
{
private:
	int i = 0, j = 0, flag = 0;
public:
	block() = default;

	void change(int ivalue, int jvalue, int flagvalue)
	{
		i = ivalue;
		j = jvalue;
		flag = flagvalue;
	}

	void change(int flagvalue)
	{
		flag = flagvalue;
	}

	int geti()
	{
		return i;
	}

	int getj()
	{
		return j;
	}

	int getflag()
	{
		return flag;
	}

	int draw_number(int a)
	{
		settextcolor(BLACK);
		settextstyle(30, 20, "ºÚÌå");
		RECT r = { i, j, i + cube, j + cube };
		switch (a)
		{
		case 0:
			setbkcolor(DARKGRAY);
			setfillcolor(DARKGRAY);
			solidrectangle(i, j, i + cube, j + cube);
			return 0;
		case 1: case 2:
			setbkcolor(WHITE);
			setfillcolor(WHITE);
			break;
		case 3: case 4:
			setbkcolor(LIGHTGRAY);
			setfillcolor(LIGHTGRAY);
			break;
		case 5: case 6:
			setbkcolor(YELLOW);
			setfillcolor(YELLOW);
			break;
		case 7: case 8:
			setbkcolor(RGB(255, 127, 0));
			setfillcolor(RGB(255, 127, 0));
		case 9: case 10:
			setbkcolor(RED);
			setfillcolor(RED);
		case 11:
			setbkcolor(LIGHTRED);
			setfillcolor(LIGHTRED);
		}
		solidrectangle(i, j, i + cube, j + cube);
		drawtext(number[a], &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		return 1;
	}
};