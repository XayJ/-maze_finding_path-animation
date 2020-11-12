//#include<bits/stdc++.h>
//using namespace std;
//typedef long long ll;
//const ll inf = 0x3f3f3f3f;
//const ll mod = 1e9+7;
//const double eps = 1e-8;
//const ll mx = 1e6+10; //check the limits, dummy
//const double PI = acos(-1);
//ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }
//ll lcm(ll a, ll b) { return a * b / gcd(a, b); }
//bool isprime(int n) { if (n <= 1)return 0; for (int i = 2; i * i <= n; i++)if (n % i == 0)return 0; return 1; }
//#define swa(a,b) a^=b^=a^=b
//#define re(i,a,b) for(ll i=(a),_=(b);i<_;i++)
//#define rb(i,a,b) for(ll i=(a),_=(b);i>=_;i--)
//#define clr(a,b) memset(a, b, sizeof(a))
//#define lowbit(x) ((x)&(x-1))
//#define all(a) a.begin(),a.end()
//inline ll qpow(ll a, ll b) { return b ? ((b & 1) ? a * qpow(a * a % mod, b >> 1) % mod : qpow(a * a % mod, b >> 1)) % mod : 1; }
//inline ll qpow(ll a, ll b, ll c) { return b ? ((b & 1) ? a * qpow(a * a % c, b >> 1) % c : qpow(a * a % c, b >> 1)) % c : 1; }
//void ca(int kase, int ans) { cout << "Case #" << kase << ": " << ans << endl; }
////void sc(int& x) { scanf("%d", &x); }void sc(int64_t& x) { scanf("%lld", &x); }void sc(double& x) { scanf("%lf", &x); }void sc(char& x) { scanf(" %c", &x); }void sc(char* x) { scanf("%s", x); }
//ll t,m,n,k;
//ll sum = 0,cnt = 0;
//
//int main()
//{
//	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
//	int n;
//	cin >> n;
//
//}
//
#include <iostream>
#include<bits/stdc++.h>
using namespace std;

// 定义结点结构
struct node
{
	int data;  // 数据域
	node* next;  // 指针域,指向下一个结点
};



// 函数printList：输出链表，每个数据之间用一个空格隔开
// 参数：h-链表头指针
void printList(node* h);

// 函数delList：删除链表，释放空间
// 参数：h-链表头指针
void delList(node* h);

void delList(node* h)
{
	node* p = h; //指针p指向头结点，第一个要删除的结点
	while (p) //这个结点是存在的
	{
		h = h->next; //头指针h指向下一个结点（下一个结点的地址存在当前结点的指针域中，即h->next中
		delete p; //删除p指向的结点
		p = h; //p指向当前的头结点，即下一个要删除的结点
	}
}
//函数printList：输出链表，每个数据之间用一个空格隔开
//参数：h-链表头指针
void printList(node* h)
{
	cout << "List:";
	h = h->next;
	while (h)
	{// h为真，即h指向的结点存在，则输出该结点的数据
		cout << " " << h->data;  // 输出结点数据
		h = h->next;  // 将该结点的指针域赋值给h，h就指向了下一个结点
	}
	cout << endl; // 输出换行符
}


typedef node* intSet;  // 定义类型别名，intSet即相当于node*

//函数insertHead：链表头部插入
//参数：h-链表头指针，t-指向要插入的结点
//返回值：插入结点后链表的首结点地址
node* insertHead(node* h, node* t)
{
	t->next = h;
	return t;
}
//函数search：在链表中查找包含数据num的结点
//参数：h-链表头指针，num-要查找的数据
//返回值：找到了返回该结点的地址，否则返回NULL
node* search(node* h, int num)
{
	while (h)
	{//h为真，即h指向的结点存在
		if (h->data == num)
			return h;
		h = h->next;  //将该结点的指针域赋值给h，h就指向了下一个结点
	}
	return NULL; //没找到包含num的结点
}

// 函数addElement：在集合h中，增加一个元素t
// 参数：h-链表头指针，t-待插入元素
// 返回值：插入结点后链表的首结点地址
void addElement(intSet is, int num)
{
	// 请在此添加代码，补全函数addElement
	/********** Begin *********/
	// 首先确认num是否在is中
	node* p = search(is, num);
	if (p != NULL)
		return;
	//准备结点
	p = new node;
	p->data = num;
	p->next = NULL;
	is = insertHead(is, p);
	/********** End **********/
}


// 函数unionSet：求集合a和b的并集
// 参数：a-集合，b-集合
// 返回值：集合（集合a和b的并集）
intSet unionSet(intSet a, intSet b)
{
	// 请在此添加代码，补全函数unionSet
	/********** Begin *********/
	// 准备空集合
	intSet c = NULL;
	// 把a中每一个元素加入c中
	node* p = a;
	while (p)
	{
		addElement(c, p->data);
		p = p->next;
	}
	// 把b中每一个元素加入c中
	p = b;
	while (p)
	{
		addElement(c, p->data);
		p = p->next;
	}
	return c;
	/********** End **********/
}

// 函数intersection：求集合a和b的交集
// 参数：a-集合，b-集合
// 返回值：集合（集合a和b的交集）
intSet intersection(intSet a, intSet b)
{
	// 请在此添加代码，补全函数intersection
	/********** Begin *********/
	// 准备空集合
	intSet c = NULL;
	// 查看a中每一个元素
	node* p = a;
	while (p)
	{
		if (search(b, p->data))
		{// 也在b中，则选入集合c
			addElement(c, p->data);
		}
		p = p->next;
	}
	return c;
	/********** End **********/
}
int main()
{
	//声明4个空集合
	intSet a = new node, b = new node, c = NULL, d = NULL, t;
	a->next = NULL; b->next = NULL;
	int n, num, i;
	//输入集合a
	cin >> n;
	for (i = 0; i < n; i++)
	{
		cin >> num;
		addElement(a, num);
	}
	//输入集合b
	cin >> n;
	for (i = 0; i < n; i++)
	{
		cin >> num;
		addElement(b, num);
	}
	//计算集合交集
	c = intersection(a, b);
	//计算并集
	d = unionSet(a, b);

	//输出结果
	printList(c);
	printList(d);
	//删除结点，释放空间
	delList(a);
	delList(b);
	delList(c);
	delList(d);

	return 0;
}
