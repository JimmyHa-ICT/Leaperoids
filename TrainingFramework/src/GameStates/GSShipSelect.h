#pragma once
#pragma once
#include "gamestatebase.h"
#include "GameButton.h"

class GSShipSelect :
	public GameStateBase
{
public:
	GSShipSelect();
	~GSShipSelect();

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
	std::shared_ptr<Sprite2D> m_ship;
	std::shared_ptr<Sprite2D> m_leftBtn;
	std::shared_ptr<Sprite2D> m_rightBtn;
	int m_currentSelect = 0;
};

