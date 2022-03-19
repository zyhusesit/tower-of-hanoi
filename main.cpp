#include <iostream>

using namespace std;

struct MyStack {
    int *stack;//用动态数组表示栈，栈的深度等于盘子的数量
    char name;//栈的名称
    int top;//栈顶位置
    int maxsize;//栈的最大容量，等于盘子的数量
};//定义栈的结构

void initializeStack(MyStack *T, int n);//初始化栈（为表示栈的数组分配空间，给栈的各项参数赋初始值）
void destroy(MyStack *T);//销毁栈（释放表示栈的数组的空间）
bool isFull(MyStack *t);//判断栈是否满，满返回1，否则返回0
bool isEmpty(MyStack *t);//判断栈是否空，空返回1，否则返回0
void push(MyStack *t, int index);//向栈顶放入一个编号为index的盘子
int pop(MyStack *t);//弹出栈顶的盘子，返回盘子序号
void hanoi(MyStack *t, int n);//模拟实现n个盘子的汉诺塔问题
void showStack(MyStack *T);//显示所有栈中的内容
int getTop(MyStack *t);//返回栈顶盘子的编号
void move(MyStack *source, MyStack *target);
void safeMove(MyStack *stack1, MyStack *stack2);

int main() {
    MyStack T[3];//T[0],T[1],T[2]分别表示3个栈
    int n;//盘子的数量

    cout << "请输入盘子的数量:" << endl;
    cin >> n;

    while (n > 0 && n < 64) {
        initializeStack(T, n);//对三个栈做初始化
        cout << "the initializeStack stack is:" << endl;
        showStack(T);//显示初始栈的情况（所有盘子都在A，B与C都是空的）
        hanoi(T, n);//模拟实现汉诺塔操作
        cout << "after move, the stack is now:" << endl;
        showStack(T);//显示所有移动结束后栈的情况（应该A与B都是空的，所有盘子都在C中）
        destroy(T);//销毁栈
        cout << "请继续输入盘子的数量:" << endl;
        cin >> n;
    }
    return 0;
}

void initializeStack(MyStack *T, int n)//对三个栈做初始化处理，A是源地址，B是中转，C是目的地
{
    int i;

    for (i = 0; i < 3; i++) {
        T[i].stack = new int[n];//为每个栈的数组分配空间,栈的深度等于盘子数量
        T[i].maxsize = n;//栈的最大容量
    }

    T[0].name = 'A';//第一个栈的名字是A
    T[1].name = 'B';
    T[2].name = 'C';

    for (i = 0; i < n; i++)//初始情况下所有的盘子都在A，编号越大盘子越大，最小号盘子在栈顶
        T[0].stack[i] = n - i;

    T[0].top = n - 1;//初始情况下A是满的
    T[1].top = T[2].top = -1;//除了A，剩余两个栈都是空的
}

void destroy(MyStack *T) {
    int i;
    for (i = 0; i < 3; i++)
        delete T[i].stack;
}

bool isFull(MyStack *t) {
    if (t->top == t->maxsize - 1)
        return true;
    else
        return false;
}

bool isEmpty(MyStack *t) {
    if (t->top < 0)
        return true;
    else
        return false;
}

void push(MyStack *T, int index) {
    if (isFull(T)) {
        cout << "the stack is full ,can not push, this step is wrong" << endl;
        exit(0);
    }
    (T->top)++;
    T->stack[T->top] = index;
}

int pop(MyStack *t) {
    int x;
    if (isEmpty(t)) {
        cout << "the stack is empty ,can not pop, this step is wrong" << endl;
        exit(0);
    }
    x = t->stack[t->top];
    (t->top)--;
    return x;
}

int getTop(MyStack *t) {
    if (isEmpty(t)) {
        cout << "the stack is empty ,can not get the top, this step is wrong" << endl;
        exit(0);
    }
    return (t->stack[t->top]);
}

void showStack(MyStack *T)//移动结束后，显示三个栈的内容
{
    int i, j;
    cout << "###########################################################" << endl;

    for (i = 0; i < 3; i++) {
        if (T[i].top >= 0) {
            cout << "the " << T[i].name << " stace has the plate:" << endl;
            for (j = T[i].top; j >= 0; j--)
                cout << T[i].stack[j] << endl;
        } else
            cout << "the " << T[i].name << " stack is empty" << endl;
    }
    cout << "###########################################################" << endl;
}

void hanoi(MyStack *T, int n)//处理过程中把盘子移动的过程记录下来，就是要输出“将XX号盘子从XX移动到XX”
{
    int total_movement = 1;
    while (n--) {
        total_movement *= 2;
    }
    for (int i = 1; i < total_movement; ++i) {
        if (i % 3 == 0)
            safeMove(T + 1, T + 2);
        else if (i % 3 == 1)
            safeMove(T, T + 2);
        else if (i % 3 == 2)
            safeMove(T, T + 1);
    }
}

void move(MyStack *source, MyStack *target) {
    if (isEmpty(source))
        cout << "Error! The source stack is empty." << endl;
    if (isFull(target))
        cout << "Error! The destination stack is full." << endl;

    cout << "Move the disc " << getTop(source)
         << " from " << source->name << " to " << target->name << endl;
    push(target, pop(source));
}

void safeMove(MyStack *stack1, MyStack *stack2) {
    if (isEmpty(stack1))
        move(stack2, stack1);
    else if (isEmpty(stack2))
        move(stack1, stack2);
    else if (getTop(stack1) > getTop(stack2))
        move(stack2, stack1);
    else
        move(stack1, stack2);
}