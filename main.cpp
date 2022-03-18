#include <iostream>
#include <string>

using namespace std;

typedef struct MyStack {
    int *s;//用动态数组表示栈，栈的深度等于盘子的数量
    char name;//栈的名称
    int top;//栈顶位置
    int maxsize;//栈的最大容量，等于盘子的数量
} ST;//定义栈的结构

void init(ST *T, int n);//初始化栈（为表示栈的数组分配空间，给栈的各项参数赋初始值）
void destroy(ST *T);//销毁栈（释放表示栈的数组的空间）
int isFull(ST *t);//判断栈是否满，满返回1，否则返回0
int isEmpty(ST *t);//判断栈是否空，空返回1，否则返回0
void push(ST *t, int index);//向栈顶放入一个编号为index的盘子
int pop(ST *t);//弹出栈顶的盘子，返回盘子序号
void hanoi(ST *t, int n);//模拟实现n个盘子的汉诺塔问题
void showStack(ST *T);//显示所有栈中的内容
int getTop(ST *t);//返回栈顶盘子的编号

int main() {
    ST T[3];//T[0],T[1],T[2]分别表示3个栈
    int n;//盘子的数量
    cout << "请输入盘子的数量:" << endl;

    while (n > 0 && n < 64) {
        init(T, n);//对三个栈做初始化
        cout << "the init stack is:" << endl;
        showStack(T);//显示初始栈的情况（所有盘子都在A，B与C都是空的）
        hanoi(T, n);//模拟实现汉诺塔操作
        cout << "after move, the stack is now:" << endl;
        showStack(T);//显示所有移动结束后栈的情况（应该A与B都是空的，所有盘子都在C中）
        destroy(T);//销毁栈
        cout << "请继续输入盘子的数量:" << endl;
        cin >> n;
    }
}

void init(ST *T, int n)//对三个栈做初始化处理，A是源地址，B是中转，C是目的地
{
    int i;
    for (i = 0; i < 3; i++) {
        T[i].s = new int[n];//为每个栈的数组分配空间,栈的深度等于盘子数量
        T[i].maxsize = n;//栈的最大容量
    }
    T[0].name = 'A';//第一个栈的名字是A
    for (i = 0; i < n; i++)//初始情况下所有的盘子都在A，编号越大盘子越大，最小号盘子在栈顶
        T[0].s[i] = n - i;
    T[0].top = n - 1;//初始情况下A是满的
    T[1].top = T[2].top = -1;//除了A，剩余两个栈都是空的
    if (n % 2 == 0)//根据盘子总数的奇偶数，给剩余的两个栈命名
    {
        T[1].name = 'B';
        T[2].name = 'C';
    } else {
        T[1].name = 'C';
        T[2].name = 'B';
    }
}

void destroy(ST *T) {
    int i;
    for (i = 0; i < 3; i++)
        delete T[i].s;
}


int isFull(ST *t) {
    if (t->top == t->maxsize - 1)
        return 1;
    else
        return 0;
}

int isEmpty(ST *t) {
    if (t->top < 0)
        return 1;
    else
        return 0;
}

void push(ST *t, int index) {
    if (isFull(t)) {
        cout << "the stack is full ,can not push, this step is wrong" << endl;
        exit(0);
    }
    (t->top)++;
    t->s[t->top] = index;
}

int pop(ST *t) {
    int x;
    if (isEmpty(t)) {
        cout << "the stack is empty ,can not pop, this step is wrong" << endl;
        exit(0);
    }
    x = t->s[t->top];
    (t->top)--;
    return x;
}

int getTop(ST *t) {
    if (isEmpty(t)) {
        cout << "the stack is empty ,can not get the top, this step is wrong" << endl;
        exit(0);
    }
    return (t->s[t->top]);
}


void showStack(ST *T)//移动结束后，显示三个栈的内容
{
    int i, j;
    for (i = 0; i < 3; i++) {
        if (T[i].top >= 0) {
            cout << "the" << T[i].name << "stace has the plate:" << endl;
            for (j = T[i].top; j >= 0; j--)
                cout << T[i].s[j] << endl;
        } else
            cout << "the" << T[i].name << "stack is empty" << endl;
    }
    printf("\n");
}


void hanoi(ST *T, int n)//处理过程中把盘子移动的过程记录下来，就是要输出“将XX号盘子从XX移动到XX”
{

}

