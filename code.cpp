#include<stack>
#include<fstream>
#include<iostream>
#include<string>
#include<queue>
#include<vector>
#include<graphics.h>
using namespace std;
const int MaxSize = 12;
int maze[MaxSize][MaxSize];
int win_high = 500, win_width = 500;
int rectangle_high = 30, rectangle_width = 30;
int m, n;//迷宫的行列数
int speed = 1000;
struct node {
	int x;
	int y;
};
node current_node;//当前点   
node next_node;//试探的下一个点
node start_node;//迷宫起点     
node end_node;//迷宫终点
stack<node> S;
void init_maze();//初始化迷宫矩阵
int  has_nextnode();//在current_node处是否存在可向前的方向
void forward();//在current_node点，向next_node前进一步
void backward();//后退一步
int DFS_maze();//深度优先搜索迷宫的出口
void draw_rectangle(int x, int y, int high, int width, int type);
void init_win()//初始化窗口大小，窗口坐标中心点/画板背景
{
	initgraph(win_high, win_width);//创建绘图窗口
	setorigin(100, 100);//设置坐标原点
	setbkcolor(BLACK);//设置背景颜色
	cleardevice();// 清理窗口
	return;
}

void init_maze()//初始化迷宫矩阵
{
	int i, j;
	string filename = "../maze.txt";
	ifstream infile(filename);
	infile >> m >> n;//读文件，获取行数m，列数n
	for (i = 0; i <= m; i++)//设定maze[][]数组的第0行、第m + 1行，第0列、n + 1列均为障碍；
	{
		maze[i][0] = 1;
		maze[i][n + 1] = 1;
	}
	for (j = 0; j <= n; j++)
	{
		maze[0][j] = 1;
		maze[m + 1][j] = 1;
	}
	infile >> start_node.x >> start_node.y;//读起点位置；
	infile >> end_node.x >> end_node.y;//读终点位置；
	for (i = 1; i <= m; i++)//读矩阵的各个值；
	{
		for (j = 1; j <= n; j++)
		{
			infile >> maze[j][i];
		}
	}
	infile.close();
}

int  has_nextnode()//在current_node处是否存在可向前的方向
{
	for (int i = 0; i <= 3; i++)
	{
		next_node = current_node;
		switch (i)
		{
		case 0:next_node.x--; break;
		case 1:next_node.y--; break;
		case 2:next_node.x++; break;
		case 3:next_node.y++; break;
		}
		if (maze[next_node.x][next_node.y] == 0)
			return 1;//试探i号方向下的next_node是否可走，若可以，返回1；
	}
	return 0;//无方向可走，返回0；
}
void forward()//在current_node点，向next_node前进
{
	S.push(next_node);// 把next_node压栈
	draw_rectangle(current_node.x, current_node.y, rectangle_high - 3, rectangle_width - 3, 2);
	current_node = next_node;//更新current_node为next_node;
	maze[current_node.x][current_node.y] = 2;//标志当前点为已经被走过
	draw_rectangle(current_node.x, current_node.y, rectangle_high - 3, rectangle_width - 3, 3);
	Sleep(speed);
}

void backward()//后退一步
{
	draw_rectangle(current_node.x, current_node.y, rectangle_high - 3, rectangle_width - 3, 2);
	S.pop();// 弹栈；
	current_node = S.top();// current_node更新为回退的点；
	draw_rectangle(current_node.x, current_node.y, rectangle_high - 3, rectangle_width - 3, 4);
	Sleep(speed);
}
int DFS_maze()//深度优先搜索迷宫的出口
{
	current_node = start_node;
	S.push(current_node);
	maze[current_node.x][current_node.y] = 2;//标注该结点为已访问过节点
	while (!S.empty())//栈不空
	{
		if (has_nextnode())//可以向前走
		{
			forward(); //向前走一步；
			if (current_node.x == end_node.x && current_node.y == end_node.y)//	如果到达终点，返回1；
				return 1;
		}
		else
			backward();//后退一步		
	}
	if (S.empty())
		return 0;
}
void draw_rectangle(int x, int y, int high, int width, int type)
//在x行y列绘制高high宽widt，类型为type的矩形
{
	switch (type)//根据type的值这的不同的颜色；
	{
	case 0:setfillcolor(WHITE); break;//未走
	case 1:setfillcolor(DARKGRAY); break;//障碍
	case 2:setfillcolor(BLUE); break;//已走
	case 3:setfillcolor(RED); break;//当前位置
	case 4:setfillcolor(GREEN); break;//back
	case 5:setfillcolor(YELLOW); break;//解决方案
	default:setfillcolor(-1 * type * 0x001100);
	}
	solidrectangle((x - 1) * rectangle_width, (y - 1) * rectangle_high, (x - 1) * rectangle_width + high, (y - 1) * rectangle_high + width);
}
void draw_maze() //绘制迷宫的各个矩形
{
	setlinestyle(PS_SOLID, 3);
	setlinecolor(BLACK);
	for (int i = 1; i <= m; i++)
	{
		for (int j = 1; j <= n; j++)//绘制第i行第j列的顶点			
			draw_rectangle(i, j, rectangle_high - 3, rectangle_width - 3, maze[i][j]);
	}
}
void display_DFSpath()
{
	while (S.empty() != 1)
	{
		current_node = S.top();
		draw_rectangle(current_node.x, current_node.y, rectangle_high - 3, rectangle_width - 3, 5);
		S.pop();
	}
}
int main()
{
	init_maze();
	init_win();
	draw_maze();
	Sleep(speed);
	DFS_maze();
	display_DFSpath();
	Sleep(speed);
}
