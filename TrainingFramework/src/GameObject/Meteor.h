#pragma once 
#include "Sprite2D.h"
#include "ObjectPool.h"
#include "ResourceManagers.h"
#include <time.h>

class Meteor : public Sprite2D
{
public:
	Meteor(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture);
	~Meteor();
	void	Update(GLfloat deltaTime);
	bool	isActive = false;
	void	Reset();
	void	SetTexture(std::shared_ptr<Texture> texture);
	void	SetTexture(int);
	void	SetVelocity(Vector2);
	void	Init();
	int		m_textr;

private:
	Vector2	m_velocity;
	float	m_angularVel;
};
