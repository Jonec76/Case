#include <string>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

// nthu-acm problem 13190
// 問題分析

/**
 * 看到題目說明，是要用 linked-list 建立一個 tree 出來，並且計算到 leaf 的最短路徑。
 * 其實這個有點像要誤導ＸＤ並不用使用到 linked-list，這個其實是用 BFS 跑出來的一個 tree
 * 所以其實只要跑 BFS 即可，下方主要是依據 BFS 的演算法寫出來的解。
 */
struct node{
    int row, col, value;
    struct node* left,* right, *up, *down;
};

int ROW, COL;

// 定義上下左右的 action
int dRow[] = { -1, 0, 1, 0 };
int dCol[] = { 0, 1, 0, -1 };

bool isValid(bool** vis,
			int row, int col)
{
	if (row < 0 || col < 0 || row >= ROW || col >= COL)
		return false;

	if (vis[row][col])
		return false;

	return true;
}

void BFS(int** grid, bool** vis,
		int row, int col)
{
	queue<pair<int, int> > q;
	vector<pair<int, int> > leaf_node;
    pair<int, int>first_node;
    first_node.first = row;
    first_node.second = col;
    struct node* head = new struct node;
    head->row = row;
    head->col = col;
    head->value = value;

    if(grid[row][col] == -1){
        cout<<0<<"\n";
        return;
    }    
	q.push(first_node);
	vis[row][col] = true;

	while (!q.empty()) {

		pair<int, int> cell = q.front();
		int x = cell.first;
		int y = cell.second;


		q.pop();

        bool leaf = true;
		for (int i = 0; i < 4; i++) {

			int adjx = x + dRow[i];
			int adjy = y + dCol[i];

			if (isValid(vis, adjx, adjy)) {
                // 如果我還有鄰居，表示我不是 leaf
                leaf = false;

                // 如果這個鄰居不是死路，才可以把該鄰居加入 stack，否則就不考慮他
                if(grid[adjx][adjy] != -1){
                    pair<int, int>adj_node;
                    adj_node.first = adjx;
                    adj_node.second = adjy;
                    q.push(adj_node);

                    // 擴散 BFS，會把目前的值往鄰居加上去，如此一來就可以知道 root 到每個點的距離了
                    grid[adjx][adjy] += grid[x][y];
                }
                vis[adjx][adjy] = true;
			}
		}

        // 把所有 leaf 加入一個 vector
        if(leaf){
            pair<int, int>n;
            n.first = x;
            n.second = y;
            leaf_node.push_back(n);  
        }   
	}
    // 這邊錯了幾次，因為 xy 最大為 10^5 ，加上距離 range 最高可能到 10^6，所以要有一個比 10^6 還要大的數字來找 min
    // 這邊是把所有 leaf 列出來，並且找最小的 leaf。
    int min = INT32_MAX;
    for(int i=0;i<leaf_node.size();i++){
        int leaf_x = leaf_node[i].first;
        int leaf_y = leaf_node[i].second;
        if(grid[leaf_x][leaf_y] < min){
            min = grid[leaf_x][leaf_y];
        }
    }
    cout<< min<<"\n";
}

int main()
{
    int start_x, start_y;
    cin >> ROW >> COL;

    // 他的測資的第一個值其實是 y position，所以要先 input start_y 再 input start_x
    cin >> start_y >>start_x;

    int *grid[ROW];
    for (int i=0; i<ROW; i++)
         grid[i] = (int *)malloc(COL * sizeof(int));
	
    for(int i=0;i<ROW;i++){
        for(int j=0;j<COL;j++){
            cin>>grid[i][j];
        }
    }

    bool *vis[ROW];
    for (int i=0; i<ROW; i++)
         vis[i] = (bool *)malloc(COL * sizeof(bool));
  
    for(int i=0;i<ROW;i++){
        for(int j=0;j<COL;j++){
            if(grid[i][j] == 0)
                vis[i][j] = true;
            else
                vis[i][j] = false;

        }
    }
    if(vis[start_x][start_y] == true)
        cout<<0<<"\n";
    else
        BFS(grid, vis, start_x, start_y);
	return 0;
}
