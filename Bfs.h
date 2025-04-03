#pragma once
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class BFS {
public:
    BFS(const vector<vector<int>>& inputGrid,  bool& HasKey);
    bool search(int x_pos, int y_pos);
    vector<pair<int, int>> backPath();
    bool isDestinationFound();

private:
    bool isAccessible(int row, int col);
    bool isDestination(int row, int col, pair<int, int> dest);
    void tracePath(vector<pair<int, int>>& path);

    vector<vector<int>> grid;
    vector<vector<bool>> visited;
    vector<vector<pair<int, int>>> parent;
    vector<pair<int, int>> path;
    pair<int, int> src, dest;
    bool foundDest;
    const int HEIGHT_MAP;
    const int WIDTH_MAP;
};
