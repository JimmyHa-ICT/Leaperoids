#pragma once
#include "Sprite2D.h"

class Particle : public Sprite2D
{
private:
	float m_lifeTime = 0;
	Vector2 m_velocity;
	float m_lifeTimeOriginal = 0;
	Vector2 m_originalSize;

public:
	Particle(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture);
	//Particle(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, Vector4 color);
	~Particle();

	void Update(GLfloat deltaTime);
	void SetLifeTime(float t);
	void Set2DVelocity(Vector2);
	void SetTexture(std::shared_ptr<Texture> texture);
	void Init();
	void Reset();
	bool isActive = false;
};