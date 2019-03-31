#include <stdio.h>
#include <time.h>
#include <Windows.h>

int purple_on_screen(POINT pos)
{
	HDC hdc = GetDC(0);
	COLORREF cr = GetPixel(hdc, pos.x, pos.y) & 0x00ffffff;
	//#7819a8
	printf("%08x\r", cr);
	return cr == 0x00a81978;
}

int main()
{
	srand(time(0));
	puts("press 'p' for puggle mode, anything else for vote mode");
	if (getchar() == 'p')
	{
		puts("PUGGLE");
		puts("please position your cursor for the bottom right hand corner of the button...");
		getchar();
		POINT p;
		if (!GetCursorPos(&p)) puts("cant get cursor pos"), exit(1);
		while (1)
		{
			SetCursorPos(p.x, p.y);
			INPUT i;
			i.type = INPUT_MOUSE;
			i.mi.dx = i.mi.dy = 0;
			i.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
			SendInput(1, &i, sizeof(INPUT));
			Sleep(rand() % 50);
			i.mi.dwFlags = MOUSEEVENTF_LEFTUP;
			SendInput(1, &i, sizeof(INPUT));
			Sleep(rand() % 10000);
		}
	}
	else
	{
		puts("please position your cursor for the like button...");
		getchar();
		POINT like;
		if(!GetCursorPos(&like)) puts("cant get cursor pos"), exit(1);
		puts("please position your cursor for the next button...");
		getchar();
		POINT next;
		if (!GetCursorPos(&next)) puts("cant get cursor pos"), exit(1);
		puts("please position your cursor for the area thats purple while loading...");
		getchar();
		POINT loading;
		if (!GetCursorPos(&loading)) puts("cant get cursor pos"), exit(1);
		int cur_pnt = 0;
		while(1)
		{
			while (purple_on_screen(loading)) Sleep(1);
			Sleep(500);
			POINT p = rand() % 2 ? next : like;
			SetCursorPos(p.x, p.y);
			INPUT i;
			i.type = INPUT_MOUSE;
			i.mi.dx = i.mi.dy = 0;
			i.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
			SendInput(1, &i, sizeof(INPUT));
			Sleep(rand() % 50);
			i.mi.dwFlags = MOUSEEVENTF_LEFTUP;
			SendInput(1, &i, sizeof(INPUT));
			Sleep(1000);
		}
	}
}
