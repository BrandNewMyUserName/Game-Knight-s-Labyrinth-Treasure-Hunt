#pragma once
#include <iostream>
#include "GameSettings.h"
#include <vector>
#include <queue>

using namespace std;

struct Node {
    double f;
    double g;
    double h;
    int parent_i;
    int parent_j;
};

struct NodeFValue {
    double f;
    pair<int, int> coordinates;

    bool operator>(const NodeFValue& other) const {
        return this->f > other.f;
    }
};

class AStar {
public:
    AStar(const vector<vector<int>>& inputGrid, bool& HasKey);
    bool search(int x_pos, int y_pos);
    vector<pair<int, int>> backPath();
    bool isDestinationFound();

private:
    const int HEIGHT_MAP;
    const int WIDTH_MAP;

    vector<vector<int>> grid;
    vector<vector<bool>> closedList;
    vector<vector<Node>> cell;
    vector<pair<int, int>> path;

    pair<int, int> src;
    pair<int, int> dest;
    bool foundDest;

    bool isAccessible(int row, int col);
    bool isDestination(int row, int col, pair<int, int> dest);
    double calculateManhattanDistance(int row1, int col1, int row2, int col2);
    void tracePath(pair<int, int> dest, vector<pair<int, int>>& path);
};