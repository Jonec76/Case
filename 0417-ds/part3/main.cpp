#include <iostream>
#include <stack>
using namespace std;
#define GREEN "\033[32m"
#define RESET "\033[0m"

int M, P;
bool finish = false;
struct Offsets
{
    int di, dj;
};

enum directions
{
    N=1,
    NE,
    E,
    SE,
    S,
    SW,
    W,
    NW,
    End_Dir
};

Offsets move[8];
struct Items
{
    int x, y, dir;
};

enum directions dir_arr[8] = {N, NE, E, SE, S, SW, W, NW};
Offsets get_offset(enum directions d){
    Offsets res;

    switch (d)
    {
        case directions::N:
            res.di = 0;
            res.dj = -1;
            break;
        case directions::NE:
            res.di = 1;
            res.dj = -1;
            break;
        case directions::E:
            res.di = 1;
            res.dj = 0;
            break;
        case directions::SE:
            res.di = 1;
            res.dj = 1;
            break;
        case directions::S:
            res.di = 0;
            res.dj = 1;
            break;
        case directions::SW:
            res.di = -1;
            res.dj = 1;
            break;
        case directions::W:
            res.di = -1;
            res.dj = 0;
            break;
        case directions::NW:
            res.di = -1;
            res.dj = -1;
            break;
        
        default:
            break;
    }

    return res;



}

bool findPath(int i, int j, int** maze, bool** mark) // find a path starting from (i, j)
{
    for (directions d = N; d < End_Dir; d = directions(d + 1))
    { // explore all directions
        int g = i + get_offset(d).di;
        int h = j + get_offset(d).dj;
        if ((g == M) && (h == P)){
            finish = true;
            return finish;
        }
        if ((!maze[g][h]) && (!mark[g][h]))
        {
            mark[g][h] = true;
            cout<<i<<" "<<j<<endl;
            findPath(g, h, maze, mark); // keep finding a path…
            cout<<"leave: "<<g<<" "<<h<<endl;

        }
    }
    return finish;
}

void Path(const int m, const int p, bool** mark, int** maze)
{ // 輸出迷宮的一個路徑（如果有的話）； maze[0][i] = maze[m+1][i] =
    //  maze[j][0] = maze[j][p+1] = 1, 0  i  p+1, 0  j  m+1。
    // 從 (1, 1) 開始
    mark[1][1] = 1;
    stack<Items> r_stack;
    struct Items temp;
    temp.x = 1;
    temp.y = 1;
    temp.dir = E;
    // 設定 temp.x、temp.y、與temp.dir
    
    r_stack.push(temp);
    while (!r_stack.empty())
    { // 堆疊不是空的
        temp = r_stack.top();
        r_stack.pop(); // 彈出
        int i = temp.x;
        int j = temp.y;
        int d = temp.dir;
        while (d < 8)
        {
            int g = i + get_offset(dir_arr[d]).di;
            int h = j + get_offset(dir_arr[d]).dj;

            if ((g == m) && (h == p)){ // 抵達出口
                
                cout << i << " " << j << endl; // 路徑上的上兩個方塊
                cout << m << " " << p << endl;
                cout<<GREEN<<"Success"<<RESET;
                return;
            }

            if ((!maze[g][h]) && (!mark[g][h])) // 新位置
            {
                mark[g][h] = 1;
                temp.x = i;
                temp.y = j;
                temp.dir = d+1; //try new direction
                r_stack.push(temp); // 加入堆疊
                i = g;
                j = h;
                d = 0; // 移到 (g, h)
            }else{
                d++;
            }
        }
        cout << "No path in maze." << endl;
    }
}

int main(){

    cin >> M >> P;
    int* maze[M+2];
    bool* mark[M+2];

   
    for(int i=0;i<M+2;i++){
        string row;
        cin >> row;
        maze[i] = new int [P+2];
        mark[i] = new bool [P+2];
        for(int j=0;j<P+2;j++){
            maze[i][j] = row[j] - '0';
            mark[i][j] = false;
        }
    }

    cout<<"findPath(recursive way): "<<endl;
    if (findPath(1, 1, maze, mark))     
        cout<<GREEN<<"Success"<<RESET;
    else
        cout << "No path in maze." << endl;

    cout<<endl<<endl<<"Path(stack way): "<<endl;
    for(int i=0;i<M+2;i++)
        for(int j=0;j<P+2;j++)
            mark[i][j] = false;
    Path(M, P, mark, maze);
}