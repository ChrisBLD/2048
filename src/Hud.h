#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Hud
{
private:
	Font m_Font;
	Text m_ScoreText;
	Text m_GameOverText;

	const std::string SCORE_MSG = "Score: ";

public:
	Hud();
	Text getScore();
	Text getGameOver();

	void setScore(int score);
};