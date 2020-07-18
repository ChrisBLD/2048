#include "Hud.h"
#include <sstream>

Hud::Hud()
{
	Vector2u resolution;
	resolution.x = VideoMode::getDesktopMode().width;
	resolution.y = VideoMode::getDesktopMode().height;

	//Load the font
	m_Font.loadFromFile("assets/fonts/Roboto-Light.ttf");

	//Score text
	m_ScoreText.setFont(m_Font);
	m_ScoreText.setCharacterSize(80);
	m_ScoreText.setFillColor(Color::Black);
	FloatRect textRect = m_ScoreText.getLocalBounds();
	m_ScoreText.setPosition(resolution.x / 100.0f, resolution.y - 120.0f);
	m_ScoreText.setString(SCORE_MSG);

	//Game Over text
	m_GameOverText.setFont(m_Font);
	m_GameOverText.setCharacterSize(80);
	m_GameOverText.setFillColor(Color::Black);
	setGameOver(false);

	//Position the GameOver text
	textRect = m_GameOverText.getLocalBounds();
	m_GameOverText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	m_GameOverText.setPosition(resolution.x / 2.0f, resolution.y / 15.0f);
}

Text Hud::getScore()
{
	return m_ScoreText;
}

Text Hud::getGameOver()
{
	return m_GameOverText;
}

void Hud::setScore(int score)
{
	std::stringstream ss;
	ss << SCORE_MSG << score;
	m_ScoreText.setString(ss.str());
}

void Hud::setGameOver(bool win)
{
	if (win)
	{
		m_GameOverText.setString("You win! Press Enter to restart");
	}
	else
	{
		m_GameOverText.setString("Game Over! Press Enter to restart");
	}
}