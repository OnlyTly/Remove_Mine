#define _CRT_SECURE_NO_WARNINGS
#include "game.h"

void menu()
{
	printf("****************   一起来扫雷  ****************\n");
	printf("****************     1.Play    ****************\n");
	printf("****************     0.Exit    ****************\n");
	printf("***********************************************\n");

}

void Game()
{
	char mine[ROWS][COLS] = {0};					//存放布置的雷 雷是'1';
	char show[ROWS][COLS] = { 0 };					//存放排查出的雷的信息，周围雷的个数，排雷旗，或者问号

	//初始化数组的内容为指定的内容
	//mine 数组在没有布置雷的时候 都是'0'
	InitBoard(mine, ROWS, COLS,'0');

	//show 数组在没有布置雷的时候 都是'*'
	InitBoard(show, ROWS, COLS,'*');

	//打印埋雷的雷场
	//DisplayBoard(mine, ROW, COL);

	//埋雷
	SetMine(mine,ROW,COL);
	DisplayBoard(show, ROW, COL);

	//排查雷
	FindMine(mine,show,ROW,COL);

}

int main()
{
	int inpute = 0;
	srand((unsigned int)time(NULL));
	do
	{
		menu();//打印菜单
		printf("请选择:");
		scanf("%d", &inpute);
		switch (inpute)
		{
		case 1:
			Game();
			break;
		case 0:
			printf("退出游戏\n");
			break;
		default:
			printf("选择错误！请选择1/0。\n");
			break;
		}
	} while (inpute);
}