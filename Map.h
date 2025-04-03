#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <string>

using namespace std;
using namespace sf;

class Map {
public:
	vector<vector<int>> Grid;
	Map();

	Map(int level);

	void loadMap(int level);

	void loadMap1();

	void loadMap2();

	void loadMap3();


};