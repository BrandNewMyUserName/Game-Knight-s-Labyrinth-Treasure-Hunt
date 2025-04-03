#pragma once
class GameResult
{
private:
	int gameScore;
	float gameTime;


public:
	GameResult();
	void loadResults(int gameScore, float gameTime);
	void reloadResults();
	float getScore();
	int getTime();
};

