#include "GameResult.h"

GameResult::GameResult()
{
	gameScore = 0;
	gameTime = 0;
}

void GameResult::loadResults(int gameScore, float gameTime)
{
	this->gameScore = gameScore;
	this->gameTime = gameTime;
}

void GameResult::reloadResults()
{
	this->gameScore = 0;
	this->gameTime = 0;
}


int GameResult::getTime()
{
	return gameTime;
}

float GameResult::getScore()
{
	return gameScore;
}
