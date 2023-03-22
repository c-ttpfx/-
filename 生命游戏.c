#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<windows.h>
#define high 30
#define width 50
int cell[high][width];
int i, j;
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
	for (i = 0; i < high; i++)
	{
		for (j = 0; j < width; j++)
			cell[i][j] = rand() % 2;

	}

}
void gotoxy(int x, int y)
{
	COORD pos = { x,y };
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);// ��ȡ��׼����豸���
	SetConsoleCursorPosition(hOut, pos);//���������ֱ���ָ���ĸ����壬����λ��
}

void show()		//��ʾ����
{
	gotoxy(0,0);
	hidden();
	
	for (i = 0; i < high-1; i++)
	{
		for (j = 0; j < width-1; j++)
		{
			if (cell[i][j] == 1)
				printf("*");
			else
				printf(" ");
		}
		printf("\n");
	}
	Sleep(50);
}
void updateWithoutInput()		//���û������޹صĸ���
{
	
	int temp[high][width];
	for (i = 0; i < high; i++)
	{
		for (j = 0; j < width; j++)
			temp[i][j] = cell[i][j];
	}
	int n = 0;
	for (i = 1; i < high - 1; i++)
	{
		for (j = 1; j < width - 1; j++)
		{
			n = cell[i - 1][j - 1] + cell[i][j - 1] + cell[i + 1][j - 1] + cell[i - 1][j] + cell[i][j] + cell[i + 1][j] + cell[i - 1][j + 1] + cell[i][j + 1] + cell[i + 1][j + 1];
			if (n == 3)
				temp[i][j] = 1;
			else if (n == 2|| n==1)
				temp[i][j] = cell[i][j];
			else
				temp[i][j] = 0;
		}
	}
	for (i = 0; i < high; i++)
	{
		for (j = 0; j < width; j++)
			cell[i][j] = temp[i][j];
	}
}
void updateWithInput()		//���û������йصĸ���
{

}
int main()
{
	startup();	//���ݳ�ʼ��
	while (1)
	{

		show();		//��ʾ����
		updateWithoutInput();	//���û������޹صĸ���
		updateWithInput();		//���û������йصĸ���
		Sleep(20);

	}

	return 0;
}

