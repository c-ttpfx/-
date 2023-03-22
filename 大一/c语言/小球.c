#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<windows.h>
int ball_x, ball_y;//С��λ��
int ball_vx, ball_vy;//С���ٶ�
int i, j;
int high, width;//����߽�
int position;//�����м�λ��
int radius;//����뾶
int n = 0;
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
	high = 25;
	width = 40;
	ball_x = high / 2;
	ball_y = width / 2;
	ball_vx = 1;
	ball_vy = 1;
	position = width / 2;
	radius = 5;
	sorce = 0;
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
	for (i = 0; i < high+1; i++)
	{
		for (j = 0; j < width + 1; j++)
			if ((i == ball_x) && (j == ball_y))
				printf("o");
			else if (j == width)
				printf("|");
			else if (i == high)
				printf("_");
			else if ((i == high - 1) && (j >= position - radius) && (j <= position + radius))
				printf("_");
			else
				printf(" ");
		printf("\n");
		
	}
	printf("����:%d\n",sorce);
}
void updateWithoutInput()		//���û������޹صĸ���
{
	if (n < 10)
		n++;
	if (n == 10)
	{
		ball_x = ball_x + ball_vx;
		ball_y = ball_y + ball_vy;
		if ((ball_x+1  == high) && ((ball_y < position - radius) || (ball_y > position + radius)))
		{
			printf("Game Over\n");
			exit(0);
		}
		if ((ball_x == 0) || (ball_x + 1 == high))
			ball_vx = -ball_vx;
		if ((ball_y == 0) || (ball_y == width))
			ball_vy = -ball_vy;
		n = 0;
	}
	if ((ball_x + 1 == high) && ((ball_y >= position - radius) || (ball_y <= position + radius)))
		sorce++;
}
void updateWithInput()		//���û������йصĸ���
{
	if (_kbhit())
	{
		char input;
		input = _getch();
		if (input == 'a')
			position--;
		if (input == 'd')
			position++;
		


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

