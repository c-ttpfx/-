#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<windows.h>
int high,width;
int bird_x, bird_y;
int i, j;
int bar_y, bar_x, bar_xp;
int sorce;
void hidden()
{
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cci;
	GetConsoleCursorInfo(hOut, &cci);
	cci.bVisible = FALSE;
	SetConsoleCursorInfo(hOut, &cci);
}
void startup()		//���ݳ�ʼ��
{
	sorce = 0;
	high = 15;
	width = 25;
	bird_x = 10;
	bird_y = 5;
	bar_y = width;
	bar_xp = high / 2;
	bar_x = bar_xp - 6;
	

}
void gotoxy(int x, int y)
{
	COORD pos = { x,y };
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);// ��ȡ��׼����豸���
	SetConsoleCursorPosition(hOut, pos);//���������ֱ���ָ���ĸ����壬����λ��
}

void show()		//��ʾ����
{
	hidden();
	gotoxy(0,0);
	
	for (i = 0; i <=high+2; i++)
	{
		for (j = 0; j< width+2; j++)

			if ((i == bird_x) && (j == bird_y))
				printf("@");
			else if ((j == bar_y) && ((i <= bar_x) || (i >= bar_xp)))
				printf("*");
			else if (i == high+2)
				printf("-");
			else if (j == width+1)
				printf("|");
			else
				printf(" ");
		
		printf("\n");


	}
	printf("\n������%d",sorce);
}
void updateWithoutInput()		//���û������޹صĸ���
{
	Sleep(150);
	bird_x++;
	if(sorce>=10)
		bar_y=bar_y-2;
	else
		bar_y--;
	if (bar_y<=0)
	{
		bar_xp = rand() % (high - 7) + 4;
		bar_y = width;
			bar_x = bar_xp - 6;
	}
	if (bird_y == bar_y)
	{
		if ((bird_x > bar_x) && (bird_x < bar_xp))
			sorce++;
		else
			exit(0);
	}
	if (bird_y<0 || bird_x>high+1)
		exit(0);
	

}
void updateWithInput()		//���û������йصĸ���
{
	if (_kbhit())
	{
		char input;
		input = _getch();
		if (input == ' ')
		{
			bird_x = bird_x - 3;

		}


	}
}
int main()
{
	startup();	//���ݳ�ʼ��
	while (1)
	{

		show();		//��ʾ����
		updateWithoutInput();	//���û������޹صĸ���
		updateWithInput();		//���û������йصĸ���
		

	}

	return 0;
}

