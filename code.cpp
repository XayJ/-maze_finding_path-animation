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
int m, n;//�Թ���������
int speed = 1000;
struct node {
	int x;
	int y;
};
node current_node;//��ǰ��   
node next_node;//��̽����һ����
node start_node;//�Թ����     
node end_node;//�Թ��յ�
stack<node> S;
void init_maze();//��ʼ���Թ�����
int  has_nextnode();//��current_node���Ƿ���ڿ���ǰ�ķ���
void forward();//��current_node�㣬��next_nodeǰ��һ��
void backward();//����һ��
int DFS_maze();//������������Թ��ĳ���
void draw_rectangle(int x, int y, int high, int width, int type);
void init_win()//��ʼ�����ڴ�С�������������ĵ�/���屳��
{
	initgraph(win_high, win_width);//������ͼ����
	setorigin(100, 100);//��������ԭ��
	setbkcolor(BLACK);//���ñ�����ɫ
	cleardevice();// ������
	return;
}

void init_maze()//��ʼ���Թ�����
{
	int i, j;
	string filename = "../maze.txt";
	ifstream infile(filename);
	infile >> m >> n;//���ļ�����ȡ����m������n
	for (i = 0; i <= m; i++)//�趨maze[][]����ĵ�0�С���m + 1�У���0�С�n + 1�о�Ϊ�ϰ���
	{
		maze[i][0] = 1;
		maze[i][n + 1] = 1;
	}
	for (j = 0; j <= n; j++)
	{
		maze[0][j] = 1;
		maze[m + 1][j] = 1;
	}
	infile >> start_node.x >> start_node.y;//�����λ�ã�
	infile >> end_node.x >> end_node.y;//���յ�λ�ã�
	for (i = 1; i <= m; i++)//������ĸ���ֵ��
	{
		for (j = 1; j <= n; j++)
		{
			infile >> maze[j][i];
		}
	}
	infile.close();
}

int  has_nextnode()//��current_node���Ƿ���ڿ���ǰ�ķ���
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
			return 1;//��̽i�ŷ����µ�next_node�Ƿ���ߣ������ԣ�����1��
	}
	return 0;//�޷�����ߣ�����0��
}
void forward()//��current_node�㣬��next_nodeǰ��
{
	S.push(next_node);// ��next_nodeѹջ
	draw_rectangle(current_node.x, current_node.y, rectangle_high - 3, rectangle_width - 3, 2);
	current_node = next_node;//����current_nodeΪnext_node;
	maze[current_node.x][current_node.y] = 2;//��־��ǰ��Ϊ�Ѿ����߹�
	draw_rectangle(current_node.x, current_node.y, rectangle_high - 3, rectangle_width - 3, 3);
	Sleep(speed);
}

void backward()//����һ��
{
	draw_rectangle(current_node.x, current_node.y, rectangle_high - 3, rectangle_width - 3, 2);
	S.pop();// ��ջ��
	current_node = S.top();// current_node����Ϊ���˵ĵ㣻
	draw_rectangle(current_node.x, current_node.y, rectangle_high - 3, rectangle_width - 3, 4);
	Sleep(speed);
}
int DFS_maze()//������������Թ��ĳ���
{
	current_node = start_node;
	S.push(current_node);
	maze[current_node.x][current_node.y] = 2;//��ע�ý��Ϊ�ѷ��ʹ��ڵ�
	while (!S.empty())//ջ����
	{
		if (has_nextnode())//������ǰ��
		{
			forward(); //��ǰ��һ����
			if (current_node.x == end_node.x && current_node.y == end_node.y)//	��������յ㣬����1��
				return 1;
		}
		else
			backward();//����һ��		
	}
	if (S.empty())
		return 0;
}
void draw_rectangle(int x, int y, int high, int width, int type)
//��x��y�л��Ƹ�high��widt������Ϊtype�ľ���
{
	switch (type)//����type��ֵ��Ĳ�ͬ����ɫ��
	{
	case 0:setfillcolor(WHITE); break;//δ��
	case 1:setfillcolor(DARKGRAY); break;//�ϰ�
	case 2:setfillcolor(BLUE); break;//����
	case 3:setfillcolor(RED); break;//��ǰλ��
	case 4:setfillcolor(GREEN); break;//back
	case 5:setfillcolor(YELLOW); break;//�������
	default:setfillcolor(-1 * type * 0x001100);
	}
	solidrectangle((x - 1) * rectangle_width, (y - 1) * rectangle_high, (x - 1) * rectangle_width + high, (y - 1) * rectangle_high + width);
}
void draw_maze() //�����Թ��ĸ�������
{
	setlinestyle(PS_SOLID, 3);
	setlinecolor(BLACK);
	for (int i = 1; i <= m; i++)
	{
		for (int j = 1; j <= n; j++)//���Ƶ�i�е�j�еĶ���			
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
