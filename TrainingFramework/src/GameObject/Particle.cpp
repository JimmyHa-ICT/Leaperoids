#include "Particle.h"


Particle::Particle(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader,
	std::shared_ptr<Texture> texture) : Sprite2D(model, shader, texture)
{

}

/*Particle::Particle(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader,
	Vector4 color) : Sprite2D(model, shader, color)
{

}*/

Particle::~Particle()
{

}

void Particle::Update(GLfloat deltaTime)
{
	m_lifeTime -= deltaTime;
	//std::cout << m_lifeTime << std::endl;

	if (m_lifeTime > 0)
	{
		Set2DPosition(Get2DPosition() + m_velocity * deltaTime);

		float ageRatio = m_lifeTime / m_lifeTimeOriginal;
		this->SetSize((int)m_originalSize.x * ageRatio, (int)m_originalSize.y * ageRatio);
		this->SetColor(Vector4(m_Color.x, m_Color.y, m_Color.z, ageRatio));
	}
	else
		Reset();
}

void Particle::SetLifeTime(float lifeTime)
{
	m_lifeTime = lifeTime;
	m_lifeTimeOriginal = lifeTime;
}


void Particle::Set2DVelocity(Vector2 v)
{
	m_velocity = v;
}

void Particle::SetTexture(std::shared_ptr<Texture> texture)
{
	m_pTexture = texture;
}

void Particle::Init()
{
	m_originalSize = Vector2(m_iWidth, m_iHeight);
}

void Particle::Reset()
{
	isActive = false;
	Set2DPosition(0, 0);
	Set2DVelocity(Vector2(0, 0));
}