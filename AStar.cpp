#include "AStar.h"

bool AStar::isAccessible(int row, int col) {
    return (row >= 0) && (row < HEIGHT_MAP) && (col >= 0) && (col < WIDTH_MAP) && (grid[row][col] != 1);
}

bool AStar::isDestination(int row, int col, pair<int, int> dest) {
    return (row == dest.first && col == dest.second);
}

double AStar::calculateManhattanDistance(int row1, int col1, int row2, int col2) {
    return abs(row1 - row2) + abs(col1 - col2);
}

void AStar::tracePath(pair<int, int> dest, vector<pair<int, int>>& path) {
    int row = dest.first;
    int col = dest.second;

    while (!(cell[row][col].parent_i == row &&
        cell[row][col].parent_j == col)) {
        path.push_back(make_pair(row, col));
        int temp_row = cell[row][col].parent_i;
        int temp_col = cell[row][col].parent_j;
        row = temp_row;
        col = temp_col;
    }

    path.push_back(make_pair(row, col));
    reverse(path.begin(), path.end());
    path.erase(path.begin());
}

AStar::AStar(const vector<vector<int>>& inputGrid, bool& HasKey): HEIGHT_MAP(inputGrid.size()), WIDTH_MAP(inputGrid[0].size()), foundDest(false) {

    grid = inputGrid;
    cell.resize(HEIGHT_MAP, vector<Node>(WIDTH_MAP));
    closedList.resize(HEIGHT_MAP, vector<bool>(WIDTH_MAP, false));
    for (int i = 0; i < HEIGHT_MAP; i++) {
        for (int j = 0; j < WIDTH_MAP; j++) {

          if (grid[i][j] == 4 && !HasKey)
              dest = make_pair(i, j);
          if (grid[i][j] == 5 && HasKey)
              dest = make_pair(i, j);

            cell[i][j].f = numeric_limits<double>::max();
            cell[i][j].g = numeric_limits<double>::max();
            cell[i][j].h = numeric_limits<double>::max();
            cell[i][j].parent_i = -1;
            cell[i][j].parent_j = -1;
        }
    }
}

bool AStar::search(int x_pos, int y_pos) {
    src = make_pair(y_pos, x_pos);

    if (!isAccessible(src.first, src.second) || !isAccessible(dest.first, dest.second)) {
        return false;
    }

    if (isDestination(src.first, src.second, dest)) {
        foundDest = true;
        return true;
    }

    cell[src.first][src.second].f = 0.0;
    cell[src.first][src.second].g = 0.0;
    cell[src.first][src.second].h = 0.0;
    cell[src.first][src.second].parent_i = src.first;
    cell[src.first][src.second].parent_j = src.second;

    priority_queue<NodeFValue, vector<NodeFValue>, greater<NodeFValue>> openList;
    openList.push({ 0.0, {src.first, src.second} });

    while (!openList.empty()) {
        NodeFValue p = openList.top();
        openList.pop();

        int i = p.coordinates.first;
        int j = p.coordinates.second;
        closedList[i][j] = true;

        int x_val[] = { 0, 0, 1, -1 };
        int y_val[] = { 1, -1, 0, 0 };

        for (int dir = 0; dir < 4; ++dir) {
            int ni = i + y_val[dir];
            int nj = j + x_val[dir];

            if (!isAccessible(ni, nj) || closedList[ni][nj])
                continue;

            if (isDestination(ni, nj, dest)) {
                cell[ni][nj].parent_i = i;
                cell[ni][nj].parent_j = j;
                tracePath(dest, path);
                foundDest = true;
                return true;
            }

            double gNew = cell[i][j].g + 1.0;
            double hNew = calculateManhattanDistance(ni, nj, dest.first, dest.second);
            double fNew = gNew + hNew;

            if (fNew < cell[ni][nj].f) {
                openList.push({ fNew, {ni, nj} });
                cell[ni][nj].f = fNew;
                cell[ni][nj].g = gNew;
                cell[ni][nj].h = hNew;
                cell[ni][nj].parent_i = i;
                cell[ni][nj].parent_j = j;
            }
        }
    }

    return false;
}

vector<pair<int, int>> AStar::backPath() {
    return path;
}

bool AStar::isDestinationFound() {
    return foundDest;
}
