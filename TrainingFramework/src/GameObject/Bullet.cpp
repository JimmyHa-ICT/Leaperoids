#include "Bullet.h"


extern GLint screenWidth;
extern GLint screenHeight;


Bullet::Bullet(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture)
	: Sprite2D(model, shader, texture), m_velocity(Vector2(0, -800)), isActive(false)
{
	
}

Bullet::~Bullet()
{
}

bool Bullet::IsCollided(std::shared_ptr<Sprite2D> obj)		// AABB box collision detection
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

void Bullet::Update(GLfloat deltaTime)
{
		Set2DPosition(this->Get2DPosition() + m_velocity * deltaTime);

		if (Get2DPosition().x  <  -300 || Get2DPosition().x > screenWidth + 300)
			Reset();
		else if (Get2DPosition().y  < -300 || Get2DPosition().y > screenHeight + 300)
			Reset();
}

void Bullet::Reset()
{
	Set2DPosition(0, 0);
	isActive = false;
}


void Bullet::SetTexture(std::shared_ptr<Texture> texture)
{
	m_pTexture = texture;
}

void Bullet::SetVelocity(Vector2 vec)
{
	m_velocity = vec;
}

Vector2 Bullet::GetVelocity()
{
	return m_velocity;
}

void Bullet::Init()
{

}