#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<windows.h>
#define high 20		//地图高度
#define width 40	//地图宽度
int canvas[high][width];	//定义数组储存变量
int i, j, k;
int felon_x, felon_y;	//蛇头位置
int moveDirection;		//移动方向
int food_x, food_y;		//食物位置
int len;				//初始化蛇长度
int score;				//分数
void hidden()     //影藏光标
{
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cci;
	GetConsoleCursorInfo(hOut, &cci);
	cci.bVisible = FALSE;
	SetConsoleCursorInfo(hOut, &cci);
}
void gotoxy(int x, int y)		//移动光标
{
	COORD pos = { x,y };
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);// 获取标准输出设备句柄
	SetConsoleCursorPosition(hOut, pos);//两个参数分别是指定哪个窗体，具体位置
}
void SerprntMove()		//蛇移动
{
	int oldophiurid_x, oldophiurid_y;	//旧的蛇尾位置
	int oldfelon_x, oldfelon_y;		//旧的蛇头位置
	int max = 0;		//记录最大值
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
	canvas[oldophiurid_x][oldophiurid_y] = 0;//使旧蛇尾为0
	int newfelon_x, newfelon_y;		//为了记录新的蛇头位置
	if (moveDirection == 1)		//moveDirection为1时向上移动
	{
		newfelon_x = oldfelon_x - 1;
		newfelon_y = oldfelon_y;
	}
	if (moveDirection == 2)		//moveDirection为2时向下移动
	{
		newfelon_x = oldfelon_x +1;
		newfelon_y = oldfelon_y;
	}
	if (moveDirection == 3)		//moveDirection为3时向左移动
	{
		newfelon_x = oldfelon_x;
		newfelon_y = oldfelon_y-1;
	}
	if (moveDirection == 4)		//moveDirection为4时向右移动
	{
		newfelon_x = oldfelon_x;
		newfelon_y = oldfelon_y+1;
	}
	if ((canvas[newfelon_x][newfelon_y] == -1) || (canvas[newfelon_x][newfelon_y] > 1))	//当蛇头碰到边界时或碰到蛇身时游戏结束
	{
		printf("游戏失败\n");
		exit(0);
	}
	else
		canvas[newfelon_x][newfelon_y] = 1;
	if ((newfelon_x == food_x) && (newfelon_y == food_y))	//当吃到食物时
	{
		score++;	//分数加1
		canvas[oldophiurid_x][oldophiurid_y] = max;		//在蛇身体长度在末尾加1
		food_x = rand() % (high - 5) + 2;	//随机食物坐标
		food_y = rand() % (width - 5) + 2;
		canvas[food_x][food_y] = -2;	//将坐标值定为-2
	}


}
void startup()		//数据初始化
{
	score = 0;
	len = 4;	//蛇身长度
	food_x = rand() % (high-5)+2;	//随机食物坐标
	food_y = rand() % (width - 5) + 2;
	canvas[food_x][food_y] = -2;	//将坐标值定为-2
	moveDirection = 4;	//定义初始化蛇移动方向
	//定义边界
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
	canvas[felon_x][felon_y] = 1;//定义初始化蛇头位置
	for (k = 1; k <= len; k++)	//len为蛇身长度
	{
		canvas[felon_x][felon_y - k] = k +1;  //大于1的为蛇身
	}
	
}
void show()		//显示画面
{
	gotoxy(0,0);
	hidden();
	for (i = 0; i < high; i++)
	{
		for (j = 0; j < width; j++)
		{
			if (canvas[i][j] == -1)
				printf("#");		//输出边界
			else if (canvas[i][j] == 1)
				printf("@");		//输出蛇头
			else if (canvas[i][j] > 1)
				printf("*");		//输出蛇身
			else if (canvas[i][j] == -2)
				printf("F");		//输出食物
			else
				printf(" ");
		}
		printf("\n");
	}
	printf("分数%d\n",score);
}
void updateWithoutInput()		//与用户输入无关的更新
{
	SerprntMove();
	

}
void updateWithInput()		//与用户输入有关的更新
{
	if (_kbhit())		//当玩家按按键时
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
	startup();	//数据初始化
	while (1)
	{

		show();		//显示画面
		updateWithoutInput();	//与用户输入无关的更新
		updateWithInput();		//与用户输入有关的更新
		Sleep(100);

	}

	return 0;
}

