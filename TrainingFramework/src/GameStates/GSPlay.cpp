#include "GSPlay.h"

#include "Shaders.h"
#include "Texture.h"
#include "Models.h"
#include "Camera.h"
#include "Font.h"
#include "Sprite2D.h"
#include "Sprite3D.h"
#include "Text.h"
#include "Util.h"

extern int screenWidth; //need get on Graphic engine
extern int screenHeight; //need get on Graphic engine

GSPlay::GSPlay()
{
}


GSPlay::~GSPlay()
{

}


void GSPlay::Init()
{
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto texture = ResourceManagers::GetInstance()->GetTexture("bg_blue2");

	//BackGround
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	m_BackGround = std::make_shared<Sprite2D>(model, shader, texture);
	m_BackGround->Set2DPosition(screenWidth / 2, screenHeight / 2);
	m_BackGround->SetSize(screenWidth, screenHeight);

	//pause button
	texture = ResourceManagers::GetInstance()->GetTexture("button_quit");
	std::shared_ptr<GameButton> button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(screenWidth - 100, 40);
	button->SetSize(100, 25);
	button->SetOnClick([]() {
		GameStateMachine::GetInstance()->ChangeState(StateTypes::STATE_GameOver);
		//exit(0);
	});
	m_listButton.push_back(button);

	//main player
	texture = ResourceManagers::GetInstance()->GetTexture(Util::ConvertShipTexture(Util::shipColor));	//the texture selected in shipselect state
	m_player = std::make_shared<Player>(model, shader, texture);
	m_player->Set2DPosition(screenWidth / 2, screenHeight - 100);
	m_player->Set2DRotation(0);
	m_player->SetSize(66, 50);

	// all player lives
	for (int i = 0; i < m_player->GetLives(); i++)
	{
		texture = ResourceManagers::GetInstance()->GetTexture(Util::ConvertLifeTexture(Util::shipColor));
		auto li = std::make_shared<Sprite2D>(model, shader, texture);
		li->Set2DPosition(25 + 36 * i, 80);
		li->SetSize(32, 26);
		m_liveRenderer.push_back(li);
	}

	//bullet pool
	
	m_bulletPool = std::make_shared<ObjectPool<Bullet>>();


	// enemy pool
	m_enemyPool = std::make_shared<ObjectPool<Enemy>>();

	// meteor pool
	m_meteorPool = std::make_shared<ObjectPool<Meteor>>();
	m_meteorPool->StartSpawning(1.5f);

	//sample particle system
	m_particleSystem = std::make_shared<ParticleSystem>();
	m_particleSystem->SetLifeTime(2, 3);


	//score text
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("kenvector_future_thin");
	m_score_text = std::make_shared< Text>(shader, font, Util::ToStringFixedLength(m_currentScore, 6), TEXT_COLOR::RED, 1.0);
	m_score_text->Set2DPosition(Vector2(25, 50));

	//level text
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	font = ResourceManagers::GetInstance()->GetFont("kenvector_future");
	m_levelText = std::make_shared< Text>(shader, font, "The boss is coming!", TEXT_COLOR::RED, 2);
	m_levelText->Set2DPosition(Vector2(screenWidth / 2 - 300, screenHeight / 2));

	srand(time(0));
}

void GSPlay::Exit()
{
	Util::SetFinalScore(m_currentScore);
	if (m_currentScore > Util::GetHighScore())
	{
		Util::SaveHighScore(m_currentScore);
	}
}


void GSPlay::Pause()
{

}

void GSPlay::Resume()
{

}


void GSPlay::HandleEvents()
{

}

void GSPlay::HandleKeyEvents(int key, bool bIsPressed)
{
	m_player->HandleKeyEvent(key, bIsPressed);

	if (key == KEY_BACK && bIsPressed)
		GameStateMachine::GetInstance()->ChangeState(StateTypes::STATE_GameOver);
}

void GSPlay::HandleTouchEvents(int x, int y, bool bIsPressed)
{
	for (auto it : m_listButton)
	{
		(it)->HandleTouchEvents(x, y, bIsPressed);
		if ((it)->IsHandle()) break;
	}

	//player rotation
	m_player->HandleTouchEvents(x, y, bIsPressed);

	// player shooting
	if (bIsPressed)
	{
		ResourceManagers::GetInstance()->PlaySound("sfx_laser1.ogg");
		auto bullet = m_bulletPool->GetObjectT();
		bullet->Set2DPosition(m_player->Get2DPosition() + 
			Vector2(-75 * sinf(m_player->Get2DRotation()), -75 * cosf(m_player->Get2DRotation())));
		bullet->SetVelocity(Vector2(sinf(m_player->Get2DRotation()), cosf(m_player->Get2DRotation())) * -700);
		bullet->SetTexture(ResourceManagers::GetInstance()->GetTexture(Util::ConvertBulletTexture(Util::shipColor)));
		bullet->Set2DRotation(m_player->Get2DRotation());
		bullet->SetSize(13, 37);
	}
}

void GSPlay::Update(float deltaTime)
{
	m_BackGround->Update(deltaTime);
	for (auto it : m_listButton)
	{
		it->Update(deltaTime);
	}
	m_player->Update(deltaTime);
	m_bulletPool->Update(deltaTime);

	m_enemyPool->Update(deltaTime);
	m_meteorPool->Update(deltaTime);
	
	// check collision between enemy and bullet
	for (auto enemy : m_enemyPool->GetAllActive())
	{
		for (auto obj : m_bulletPool->GetAllActive())
		{
			if (obj->IsCollided(enemy))
			{
				obj->Reset();
				enemy->SetHP(enemy->GetHP() - 1);
				if (enemy->GetHP() > 0)
					m_particleSystem->Emit("particle2", 8, enemy->Get2DPosition());
				else
				{
					m_particleSystem->Emit("particle2", 32, enemy->Get2DPosition());
					m_currentScore += 200;
					m_currentLevel++;
					m_score_text->setText(Util::ToStringFixedLength(m_currentScore, 6));
					m_meteorPool->StartSpawning(1.5f - (m_currentLevel - 1) * 0.1f);
				}
			}
		}
	}

	// check collision of meteor and others
	for (auto meteor : m_meteorPool->GetAllActive())
	{
		for (auto obj : m_bulletPool->GetAllActive())
		{
			if (obj->IsCollided(meteor))
			{
				m_particleSystem->Emit("particle2", 8, meteor->Get2DPosition());
				m_currentScore += 10;
				m_score_text->setText(Util::ToStringFixedLength(m_currentScore, 6));
				obj->Reset();
				
				if (meteor->m_textr >= 4)
				{
					meteor->SetTexture(rand() % 4);

					auto meteor2 = m_meteorPool->GetObjectT();
					meteor2->Set2DPosition(meteor->Get2DPosition());
					meteor2->SetTexture(rand() % 4);
					meteor2->SetVelocity(Vector2(rand() % 400 - 200, rand() % 400 - 200));

					meteor2 = m_meteorPool->GetObjectT();
					meteor2->Set2DPosition(meteor->Get2DPosition());
					meteor2->SetTexture(rand() % 4);
					meteor2->SetVelocity(Vector2(rand() % 400 - 200, rand() % 400 - 200));
				}
				else
					meteor->Reset();
			}
		}

		if (m_player->IsCollided(meteor))
		{
			ResourceManagers::GetInstance()->PlaySound("rollover1.ogg");
			meteor->Reset();
			m_player->SetLives(m_player->GetLives() - 1);
			m_particleSystem->Emit("particle2", 8, m_player->Get2DPosition());
			if (m_player->GetLives() == 0)
			{
				ResourceManagers::GetInstance()->PlaySound("sfx_lose.ogg");
				GameStateMachine::GetInstance()->ChangeState(StateTypes::STATE_GameOver);
			}
			else
				ResourceManagers::GetInstance()->PlaySound("hurt.wav");
		}
	}

	//checking collision between bullet and player
	for (auto obj : m_bulletPool->GetAllActive())
	{
		if (obj->IsCollided(m_player))
		{
			obj->Reset();
			ResourceManagers::GetInstance()->PlaySound("rollover1.ogg");
			m_player->SetLives(m_player->GetLives() - 1);
			m_particleSystem->Emit("particle2", 8, m_player->Get2DPosition());
			if (m_player->GetLives() == 0)
			{
				ResourceManagers::GetInstance()->PlaySound("sfx_lose.ogg");
				GameStateMachine::GetInstance()->ChangeState(StateTypes::STATE_GameOver);
			}
			else
				ResourceManagers::GetInstance()->PlaySound("hurt.wav");
		}
	}

	//enemy spawning
	m_particleSystem->Update(deltaTime);
	if (m_currentScore >= m_levelMission)
	{
		m_levelMission = m_levelMission * 2 + 200;
		m_meteorPool->StopSpawning();

		//spawn the bot
		auto l_enemy = m_enemyPool->GetObjectT();
		switch (rand() % 4)
		{
			case 0:
				l_enemy->Set2DPosition(-300, rand() % screenHeight);
				break;
			case 1:
				l_enemy->Set2DPosition(screenWidth + 300, rand() % screenHeight);
				break;
			case 2:
				l_enemy->Set2DPosition(rand() % screenWidth, -300);
				break;
			case 3:
				l_enemy->Set2DPosition(rand() % screenWidth, screenHeight + 300);
				break;
		}

		l_enemy->SetSize(93, 84);
		l_enemy->SetTexture(ResourceManagers::GetInstance()->GetTexture("enemyBlack1"));
		l_enemy->SetBulletPool(m_bulletPool);
		l_enemy->SetTarget(m_player);
		m_displayTextTime = 1.5f;
	}

	if (m_displayTextTime > 0)
	{
		m_displayTextTime -= deltaTime;
	}
}

void GSPlay::Draw()
{
	m_BackGround->Draw();
	m_score_text->Draw();
	
	for (auto button : m_listButton)
	{
		button->Draw();
	}

	m_player->Draw();

	m_enemyPool->Draw();
	m_bulletPool->Draw();
	m_meteorPool->Draw();

	for (int i = 0; i < m_player->GetLives(); i++)
	{
		m_liveRenderer[i]->Draw();
	}
	m_particleSystem->Draw();

	if (m_displayTextTime > 0)
		m_levelText->Draw();
}