#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<windows.h>
int sorce;	//����
int position_x, position_y;//�ɻ�λ��
int enemy_x, enemy_y;//�л�λ��
int bullet_x, bullrt_y;//�ӵ�λ��
int high, width;//��Ϸ����ߴ�
int initial;//�л���ʼ�ٶ�
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
	initial = 10;
	sorce = 0;
	high =28;
	width = 40;
	position_x = high / 2;
	position_y = width / 2;
	bullet_x = -1;
	enemy_x = 0;
	enemy_y = width / 2;
}
void gotoxy(int x, int y)
{
	COORD pos = { x,y };
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);// ��ȡ��׼����豸���
	SetConsoleCursorPosition(hOut, pos);//���������ֱ���ָ���ĸ����壬����λ��
}

void show()		//��ʾ����
{
	int i, j;

	gotoxy(0, 0);
	for (i = 0; i < high; i++)
	{
		
		for (j = 0; j < width; j++)
		{
			 if ((i == position_x) && (j == position_y))
				printf("*");//����ɻ�*
			else if ((i == bullet_x) && (j == bullrt_y))
				printf("|");//����ӵ�
			else if ((i == enemy_x) && (j == enemy_y))
				printf("@");//����л�
			else
				printf(" ");//����ո�
			 
	
				
		}
		printf("\n");//����
	}
	printf("����:%d\n",sorce);//��ʾ����
}
void updateWithoutInput()		//���û������޹صĸ���
{
	hidden();
	if(bullet_x>-1)
			bullet_x--;
	static int speed = 0;
	if (speed < initial)	//�л��ٶ�
		speed++;
	if (speed == initial) 
	{

		speed = 0;
		if (enemy_x > high)	//��������л�
		{
			enemy_x = 0;
			enemy_y = rand()%width;
		}
		else
			enemy_x++;
		
	}
	if ((bullet_x == enemy_x) && (bullrt_y == enemy_y))	//��ɱ�л���������1
	{
		enemy_x = 0;
		enemy_y = rand() % width;
		sorce++;
	}
	if (sorce > 10 && speed>8)
	{
		initial = initial - 5;
		speed = 0;
	}
}
void updateWithInput()		//���û������йصĸ���
{
	char input;
	if (_kbhit())		//����������ʱ
	{
		input = _getch();
		if (input == 'w')
			position_x--;
		if (input == 's')
			position_x++;
		if (input == 'a')
			position_y--;
		if (input == 'd')
			position_y++;
		if (input == ' ')
		{
			bullet_x = position_x - 1;
			bullrt_y = position_y;
		}
	}

}
int main()
{
	startup();	//���ݳ�ʼ��
	while (1) 
	{
		if (((position_x == enemy_x) && (position_y == enemy_y)) || enemy_x>high )//��û�л�ɱ�л��������л�ʱ����Ϸ����
		{
			printf("\nyou die\n");
			break;

		}
		show();		//��ʾ����
		updateWithoutInput();	//���û������޹صĸ���
		updateWithInput();		//���û������йصĸ���
		Sleep(20);
		
	}
	
	 return 0;
}

