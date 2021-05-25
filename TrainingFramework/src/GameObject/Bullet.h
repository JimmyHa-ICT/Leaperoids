#pragma once 
#include "Sprite2D.h"



class Bullet : public Sprite2D
{
public:
	Bullet(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture);
	~Bullet();
	
	bool IsCollided(std::shared_ptr<Sprite2D>);
	void Update(GLfloat);
	bool isActive;
	void Reset();
	void SetTexture(std::shared_ptr<Texture> texture);
	void SetVelocity(Vector2 v);
	Vector2 GetVelocity();
	void Init();

private:
	Vector2	m_velocity;
};
