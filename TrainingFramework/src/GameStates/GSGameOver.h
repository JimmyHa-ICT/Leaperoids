#pragma once
#include "gamestatebase.h"
#include "GameButton.h"

class GSGameOver :
	public GameStateBase
{
public:
	GSGameOver();
	~GSGameOver();
	
	void Init();
	void Exit();

	void Pause();
	void Resume();

	void HandleEvents();
	void HandleKeyEvents(int key, bool bIsPressed);
	void HandleTouchEvents(int x, int y, bool bIsPressed);
	void Update(float deltaTime);
	void Draw();

private:
	std::shared_ptr<Sprite2D> m_BackGround;
	std::list<std::shared_ptr<GameButton>>	m_listButton;
	std::shared_ptr<Text>  m_Text_gameName;
	//std::shared_ptr<Text> m_scoreText;
	//std::shared_ptr<Text> m_highScoreText;
	std::vector<std::shared_ptr<Text>> m_textList;
};

