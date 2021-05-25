#pragma once
#include "ObjectPool.h"
#include "Particle.h"
#include "ResourceManagers.h"

class ParticleSystem
{
private:
	std::shared_ptr<ObjectPool<Particle>> m_particlePool;
	Vector2 m_lifeTime;
	float m_emissionRate = 0;
	Vector4 m_particleColor = Vector4(0, 0, 0, 0);
public:
	ParticleSystem();
	~ParticleSystem();

	void SetLifeTime(GLfloat min, GLfloat max);
	void SetEmissionRate(float rate);
	void Update(GLfloat deltaTime);
	void Draw();
	void Emit(std::string texture, int buffer, Vector2 pos = Vector2(0, 0));
	void SetColor(Vector4);
};