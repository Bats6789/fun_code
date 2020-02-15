#include <graphics.h>

int main(void)
{
	int bigX;
	int bigY;

	bigX = getmaxwidth();
	bigY = getmaxheight();
	initwindow(bigX, bigY, "Full screen window - press key to close");

	line(0,0, bigX, bigY);
	setcolor(BLUE);
	line(bigX, 0, 0, bigY);

	getch();
	closegraph();

	return(0);
}
