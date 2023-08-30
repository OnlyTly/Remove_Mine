#define _CRT_SECURE_NO_WARNINGS
#include "game.h"

//初始化雷场
void InitBoard(char board[ROWS][COLS], int rows, int cols,char set)
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			board[i][j] = set;
		}
	}
}

//打印雷场
void DisplayBoard(char board[ROWS][COLS], int row, int col) 
{
	printf("-------------------扫雷----------------------\n");
	for (int j = 0; j <= col; j++)
	{
		printf("%d ", j);
	}
		printf("\n");
	for (int i = 1; i <= row; i++)
	{
		printf("%d ", i);
		for (int j = 1; j <= col; j++)
		{
			printf("%c ", board[i][j]);
		}
		printf("\n");
	}
	printf("---------------------------------------------\n");
}

//埋雷
void SetMine(char board[ROWS][COLS], int row, int col)
{
	int count = EASY_COUNT;
	while (count)
	{
		//随机设置雷的坐标
		int x = rand() % row + 1;//1~9
		int y = rand() % col + 1;//1~9

		if (board[x][y] == '0') {
			board[x][y]='1';
			count--;
		}
	}
}
//标记雷
void MarkMine(char board[ROWS][COLS], int row, int col)
{
	int x = 0;
	int y = 0;
	while (1)
	{
		printf("请输入你想要标记位置的坐标->");
		scanf("%d %d", &x, &y);
		if (x >= 1 && x <= row && y >= 1 && y <= col)    //判断该坐标是否合法
		{
			if (board[x][y] == '*')        //判断该坐标是否被排查
			{
				board[x][y] = '!';
				break;
			}
			else
			{
				printf("该位置不能被标记，请重新输入!\n");
			}
		}
		else
		{
			printf("输入错误，请重新输入!\n");
		}
	}
}


//记录雷的个数
int get_mine_count(char board[ROWS][COLS],int x,int y)
{
	//统计该坐标周围的雷个数
	int sum = 0;
	for (int i = x-1; i <=x+1; i++)
	{
		for (int j = y-1; j <=y+1; j++)
		{
			if (board[i][j]=='1')
			{
				sum++;
			}
			
		}
	}
		return (sum);
	//即对应坐标显示的值：count;
//----------------------------------------------
	//通过数字字符显示雷：用'1'来代表雷，'1'=49,'0'=48。统计范围内的所有字符的总和 - 个数*'0'= 雷的个数
	/*return (  board[x-1][y]
			+ board[x - 1][y - 1]
			+ board[x][y - 1]
			+ board[x + 1][y - 1]
			+ board[x + 1][y]
			+ board[x + 1][y + 1]
			+ board[x][y + 1]
			+ board[x - 1][y + 1]- 8*'0');*/
	//即对应坐标显示的值：count + '0';
			
}
//递归爆炸式展开一片
void ExplosionSpread(char mine[ROWS][COLS], char show[ROWS][COLS], int row, int col, int x, int y, int* pw)
{
	if (x >= 1 && x <= row && y >= 1 && y <= col)  //判断坐标是否为排查范围内
	{
		int num = get_mine_count(mine, x, y);   //获取坐标周围雷的个数
		if (num == 0)
		{
			(*pw)++;
			show[x][y] = ' ';   //如果该坐标周围没有雷，就把该坐标置成空格，并向周围八个坐标展开
			int i = 0;
			int j = 0;
			for (i = x - 1; i <= x + 1; i++)
			{
				for (j = y - 1; j <= y + 1; j++)
				{
					if (show[i][j] == '*')    //限制递归条件，防止已经排查过的坐标再次递归，从而造成死递归
						ExplosionSpread(mine, show, row, col, i, j, pw);
				}
			}
		}
		else
		{
			(*pw)++;
			show[x][y] = num + '0';
		}
	}
}

//排雷
void FindMine(char mine[ROWS][COLS], char show[ROWS][COLS], int row, int col)
{
	int x = 0;
	int y = 0;
	char mark = 0;//用于接受是否需要标记雷

	int win = 0;////用来标记是否取得胜利
	int *pw = &win;

	while (1)
	{
		printf("请输入排查的坐标:");
		scanf("%d%d", &x, &y);
		if (x>=1 && x<=row && y>=1 && y<=col)
		{
			if (mine[x][y]=='1')
			{
				printf("很遗憾你被炸死了\n");
				DisplayBoard(mine, ROW, COL);
				break;
			}
			else
			{
				if (show[x][y]!='*')
				{
					printf("该坐标已被排查，请重新输入!\n");
					continue;  //直接进入下一次循环
				}
				else
				{
					ExplosionSpread(mine, show, row, col, x, y, pw);  //爆炸展开一片
					system("cls");  //清空屏幕
					DisplayBoard(show, ROW, COL);  //打印棋盘


					printf("需要标记雷的位置请输入y/Y,否则请按任意键->");
					while ((mark = getchar()) != '\n');  //清理缓冲区

					scanf("%c", &mark);
					if (mark == 'Y' || mark == 'y')
					{
						MarkMine(show, row, col);   //标记雷
						system("cls");
						DisplayBoard(show, row, col);
					}
					else
					{
						continue;
					}
				}
			}
		}
		else
		{
			printf("非法坐标，请重新输入\n");
		}
	}
	//
	int count = get_mine_count(mine, x, y);
	if (win == count)
	{
		system("cls");//清楚屏幕
		printf("恭喜你，排雷成功!\n");
		DisplayBoard(show, row, col);
		return;
	}
}