// C++ program for the above approach
#include <string>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;
int ROW, COL;

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
                leaf = false;
                pair<int, int>adj_node;
                adj_node.first = adjx;
                adj_node.second = adjy;
				q.push(adj_node);
                grid[adjx][adjy] += grid[x][y];
				vis[adjx][adjy] = true;
			}
		}
        if(leaf){
            pair<int, int>n;
            n.first = x;
            n.second = y;
            leaf_node.push_back(n);  
        }   
	}

    int min = INT16_MAX;
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
    BFS(grid, vis, start_x, start_y);
	return 0;
}
