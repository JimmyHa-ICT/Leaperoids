#pragma once
#include "gamestatebase.h"
#include "GameButton.h"
#include "Player.h"
#include "Bullet.h"
#include "Enemy.h"
#include "Meteor.h"

#include "ObjectPool.h"
#include "ParticleSystem.h"

class Sprite2D;
class Sprite3D;
class Text;

class GSPlay :
	public GameStateBase
{
public:
	GSPlay();
	~GSPlay();

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
	std::shared_ptr<Text>  m_score_text;
	std::list<std::shared_ptr<GameButton>> m_listButton;
	std::shared_ptr<Player> m_player;
	std::shared_ptr<ObjectPool<Bullet>> m_bulletPool;
	std::shared_ptr<ObjectPool<Enemy>> m_enemyPool;
	std::shared_ptr<ObjectPool<Meteor>> m_meteorPool;

	int m_currentScore = 0;
	std::vector<std::shared_ptr<Sprite2D>> m_liveRenderer;
	std::shared_ptr<ParticleSystem> m_particleSystem;
	int m_currentLevel = 1;
	int m_levelMission = 600;
	std::shared_ptr<Text>  m_levelText;
	float m_displayTextTime = 0;
};

