#include "ParticleSystem.h"


ParticleSystem::ParticleSystem()
{
	m_particlePool = std::make_shared<ObjectPool<Particle>>();
}

ParticleSystem::~ParticleSystem()
{
}

void ParticleSystem::Update(GLfloat deltaTime)
{
	for (auto particle : m_particlePool->GetAllActive())
	{
		particle->Update(deltaTime);
	}
}

void ParticleSystem::Draw()
{
	m_particlePool->Draw();
}

void ParticleSystem::SetLifeTime(GLfloat min, GLfloat max)
{
	m_lifeTime = Vector2(min, max);
}

void ParticleSystem::SetEmissionRate(float rate)
{
	m_emissionRate = rate;
}

void ParticleSystem::Emit(std::string texture, int buffer, Vector2 pos)
{
	srand(time(0));
	auto m_texture = ResourceManagers::GetInstance()->GetTexture(texture);
	for (int i = 0; i < buffer; i++)
	{
		auto particle = m_particlePool->GetObjectT();
		particle->SetSize(16, 16);
		particle->Set2DPosition(pos);
		particle->SetTexture(m_texture);
		particle->SetLifeTime(m_lifeTime.x + rand() / RAND_MAX * (m_lifeTime.y - m_lifeTime.x));
		particle->Set2DVelocity(Vector2(rand() % 200 - 100, rand() % 200 - 100));
		particle->Init();
	}
}

void ParticleSystem::SetColor(Vector4 color)
{
	m_particleColor = color;
}
