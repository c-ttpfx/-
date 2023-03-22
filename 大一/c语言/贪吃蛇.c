#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<windows.h>
#define high 20		//��ͼ�߶�
#define width 40	//��ͼ���
int canvas[high][width];	//�������鴢�����
int i, j, k;
int felon_x, felon_y;	//��ͷλ��
int moveDirection;		//�ƶ�����
int food_x, food_y;		//ʳ��λ��
int len;				//��ʼ���߳���
int score;				//����
void hidden()     //Ӱ�ع��
{
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cci;
	GetConsoleCursorInfo(hOut, &cci);
	cci.bVisible = FALSE;
	SetConsoleCursorInfo(hOut, &cci);
}
void gotoxy(int x, int y)		//�ƶ����
{
	COORD pos = { x,y };
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);// ��ȡ��׼����豸���
	SetConsoleCursorPosition(hOut, pos);//���������ֱ���ָ���ĸ����壬����λ��
}
void SerprntMove()		//���ƶ�
{
	int oldophiurid_x, oldophiurid_y;	//�ɵ���βλ��
	int oldfelon_x, oldfelon_y;		//�ɵ���ͷλ��
	int max = 0;		//��¼���ֵ
	for (i = 1; i < high-1; i++)
	{
		for (j = 1; j < width-1; j++)
		{
			if (canvas[i][j] > 0)
				canvas[i][j]++;
			if (max < canvas[i][j])
			{
				max = canvas[i][j];
				oldophiurid_x = i;
				oldophiurid_y = j;
			}
			if (canvas[i][j] == 2)
			{
				oldfelon_x = i;
				oldfelon_y = j;
			}
		}
	}
	canvas[oldophiurid_x][oldophiurid_y] = 0;//ʹ����βΪ0
	int newfelon_x, newfelon_y;		//Ϊ�˼�¼�µ���ͷλ��
	if (moveDirection == 1)		//moveDirectionΪ1ʱ�����ƶ�
	{
		newfelon_x = oldfelon_x - 1;
		newfelon_y = oldfelon_y;
	}
	if (moveDirection == 2)		//moveDirectionΪ2ʱ�����ƶ�
	{
		newfelon_x = oldfelon_x +1;
		newfelon_y = oldfelon_y;
	}
	if (moveDirection == 3)		//moveDirectionΪ3ʱ�����ƶ�
	{
		newfelon_x = oldfelon_x;
		newfelon_y = oldfelon_y-1;
	}
	if (moveDirection == 4)		//moveDirectionΪ4ʱ�����ƶ�
	{
		newfelon_x = oldfelon_x;
		newfelon_y = oldfelon_y+1;
	}
	if ((canvas[newfelon_x][newfelon_y] == -1) || (canvas[newfelon_x][newfelon_y] > 1))	//����ͷ�����߽�ʱ����������ʱ��Ϸ����
	{
		printf("��Ϸʧ��\n");
		exit(0);
	}
	else
		canvas[newfelon_x][newfelon_y] = 1;
	if ((newfelon_x == food_x) && (newfelon_y == food_y))	//���Ե�ʳ��ʱ
	{
		score++;	//������1
		canvas[oldophiurid_x][oldophiurid_y] = max;		//�������峤����ĩβ��1
		food_x = rand() % (high - 5) + 2;	//���ʳ������
		food_y = rand() % (width - 5) + 2;
		canvas[food_x][food_y] = -2;	//������ֵ��Ϊ-2
	}


}
void startup()		//���ݳ�ʼ��
{
	score = 0;
	len = 4;	//������
	food_x = rand() % (high-5)+2;	//���ʳ������
	food_y = rand() % (width - 5) + 2;
	canvas[food_x][food_y] = -2;	//������ֵ��Ϊ-2
	moveDirection = 4;	//�����ʼ�����ƶ�����
	//����߽�
	for (i = 0; i < high; i++)
	{
		canvas[i][0] = canvas[i][width - 1] = -1;
	}
	for (j = 0; j < width; j++)
	{
		canvas[0][j] = canvas[high - 1][j] = -1;
	}
	felon_x = high / 2;
	felon_y = width / 2;
	canvas[felon_x][felon_y] = 1;//�����ʼ����ͷλ��
	for (k = 1; k <= len; k++)	//lenΪ������
	{
		canvas[felon_x][felon_y - k] = k +1;  //����1��Ϊ����
	}
	
}
void show()		//��ʾ����
{
	gotoxy(0,0);
	hidden();
	for (i = 0; i < high; i++)
	{
		for (j = 0; j < width; j++)
		{
			if (canvas[i][j] == -1)
				printf("#");		//����߽�
			else if (canvas[i][j] == 1)
				printf("@");		//�����ͷ
			else if (canvas[i][j] > 1)
				printf("*");		//�������
			else if (canvas[i][j] == -2)
				printf("F");		//���ʳ��
			else
				printf(" ");
		}
		printf("\n");
	}
	printf("����%d\n",score);
}
void updateWithoutInput()		//���û������޹صĸ���
{
	SerprntMove();
	

}
void updateWithInput()		//���û������йصĸ���
{
	if (_kbhit())		//����Ұ�����ʱ
	{
		
		char input = _getch();
		if (input == 'w')
		{
			if(moveDirection!=2)
			moveDirection = 1;
		}
		if (input == 's')
		{
			if(moveDirection!=1)
			moveDirection = 2;
		}
		if (input == 'a')
		{
			if(moveDirection!=4)
			moveDirection = 3;
		}
		if (input == 'd')
		{
			if(moveDirection!=3)
			moveDirection = 4;
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
		Sleep(100);

	}

	return 0;
}

