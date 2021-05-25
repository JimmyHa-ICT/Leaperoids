#include "Player.h"

extern int screenWidth; //need get on Graphic engine
extern int screenHeight; //need get on Graphic engine


Player::Player(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture)
	: Sprite2D(model, shader, texture), m_lives(6)
{
}

Player::~Player()
{
}

void Player::HandleTouchEvents(GLint x, GLint y, bool bIsPressed)
{
	if (bIsPressed)
	{
		Vector2 pos = Get2DPosition();
		if (y - pos.y < 0)
			this->Set2DRotation(atanf((x - pos.x) / (y - pos.y)));
		else
			this->Set2DRotation(atanf((x - pos.x) / (y - pos.y)) - PI);
	}
}

void Player::HandleKeyEvent(unsigned char key, bool bIsPresseded)
{
	if (bIsPresseded)
	{
		if (key == KEY_MOVE_LEFT || key == KEY_LEFT)
			horizontalInput = -1;

		else if (key == KEY_MOVE_RIGHT || key == KEY_RIGHT)
			horizontalInput = 1;

		if (key == KEY_MOVE_BACKWORD || key == KEY_DOWN)
			verticalInput = 1;

		if (key == KEY_MOVE_FORWORD || key == KEY_UP)
			verticalInput = -1;

		/*if (key == 'z' || key == 'Z')
			rotationInput = -1;
		if (key == 'c' || key == 'C')
		{
			rotationInput = 0;
			std::cout << m_2DRotation << std::endl;
		}*/
	}

	else
	{
		horizontalInput = verticalInput = 0;
	}
}

int Player::GetLives()
{
	return this->m_lives;
}

void Player::SetLives(int lives)
{
	this->m_lives = lives;
}

void Player::Update(GLfloat deltaTime)
{
	this->Set2DPosition(m_Vec2DPos.x + horizontalInput * m_velocity * deltaTime,
		m_Vec2DPos.y + verticalInput * m_velocity * deltaTime);
	
	if (Get2DPosition().x > screenWidth - m_iWidth / 2)
		Set2DPosition(screenWidth - m_iWidth / 2, Get2DPosition().y);
	if (Get2DPosition().y > screenHeight - m_iHeight / 2)
		Set2DPosition(Get2DPosition().x, screenHeight - m_iHeight / 2);
	if (Get2DPosition().x < m_iWidth / 2)
		Set2DPosition(m_iWidth / 2, Get2DPosition().y);
	if (Get2DPosition().y < m_iHeight / 2)
		Set2DPosition(Get2DPosition().x, m_iHeight / 2);
}


bool Player::IsCollided(std::shared_ptr<Sprite2D> obj)		// AABB box collision detection
{
	Vector2 A = this->Get2DPosition();
	Vector2 B = obj->Get2DPosition();

	if (A.x + this->m_iWidth / 2 < B.x - obj->Get2DSize().x / 2)
		return false;

	if (A.x - this->m_iWidth / 2 > B.x + obj->Get2DSize().x / 2)
		return false;

	if (A.y + this->m_iHeight / 2 < B.y - obj->Get2DSize().y / 2)
		return false;

	if (A.y - this->m_iHeight / 2 > B.y + obj->Get2DSize().y / 2)
		return false;

	return true;
}