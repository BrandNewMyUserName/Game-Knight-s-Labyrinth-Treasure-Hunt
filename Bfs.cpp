#include "BFS.h"



BFS::BFS(const vector<vector<int>>& inputGrid, bool& HasKey): foundDest(false), HEIGHT_MAP(inputGrid.size()), WIDTH_MAP(inputGrid[0].size()){

    grid = inputGrid;
    visited.resize(HEIGHT_MAP, vector<bool>(WIDTH_MAP, false));
    parent.resize(HEIGHT_MAP, vector<pair<int, int>>(WIDTH_MAP, { -1, -1 }));

    for (int i = 0; i < HEIGHT_MAP; ++i) {
        for (int j = 0; j < WIDTH_MAP; ++j) {
            if (grid[i][j] == 4 && !HasKey)
                dest = make_pair(i, j);
            if (grid[i][j] == 5 && HasKey)
                dest = make_pair(i, j);
        }
    }
}

bool BFS::search(int x_pos, int y_pos) {
    if (!isAccessible(y_pos, x_pos)) {
        return false;
    }

    queue<pair<int, int>> q;

    visited[y_pos][x_pos] = true;
    src = { y_pos, x_pos };
    q.push({ y_pos, x_pos });

    while (!q.empty()) {
        pair<int, int> curr = q.front();
        q.pop();

        if (isDestination(curr.first, curr.second, dest)) {
            tracePath(path);
            foundDest = true;
            return true;
        }

        int rowNum[] = { -1, 0, 0, 1 };
        int colNum[] = { 0, -1, 1, 0 };

        for (int i = 0; i < 4; ++i) {
            int row = curr.first + rowNum[i];
            int col = curr.second + colNum[i];

            if (isAccessible(row, col) && !visited[row][col]) {
                visited[row][col] = true;
                parent[row][col] = curr;
                q.push({ row, col });
            }
        }
    }

    return false;
}

vector<pair<int, int>> BFS::backPath() {
    return path;
}

bool BFS::isDestinationFound() {
    return foundDest;
}

bool BFS::isAccessible(int row, int col) {
    return (row >= 0) && (row < HEIGHT_MAP) && (col >= 0) && (col < WIDTH_MAP) && (grid[row][col] != 1);
}

bool BFS::isDestination(int row, int col, pair<int, int> dest) {
    return row == dest.first && col == dest.second;
}

void BFS::tracePath(vector<pair<int, int>>& path) {
    pair<int, int> currCell = dest;
    while (!(parent[currCell.first][currCell.second] == src)) {
        path.push_back(currCell);
        currCell = parent[currCell.first][currCell.second];
    }
    path.push_back(src);
    reverse(path.begin(), path.end());
}
