#include "Enemy.h"

extern int screenWidth; //need get on Graphic engine
extern int screenHeight; //need get on Graphic engine

Enemy::Enemy(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture)
	: Sprite2D(model, shader, texture), m_hp(10), m_state(EnemyState::AIMING)
{
}

Enemy::~Enemy()
{
}

int Enemy::GetHP()
{
	return this->m_hp;
}

void Enemy::SetHP(int hp)
{
	this->m_hp = hp;
}

void Enemy::EnemyAttack()
{
	auto bullet = m_bulletPool->GetObjectT();
	bullet->Set2DPosition(Get2DPosition() + Vector2(-80 * sinf(Get2DRotation()), -80 * cosf(Get2DRotation())));
	bullet->SetVelocity(Vector2(sinf(Get2DRotation()), cosf(Get2DRotation())) * -700);
	bullet->SetTexture(ResourceManagers::GetInstance()->GetTexture("enemyLaser"));
	bullet->Set2DRotation(Get2DRotation());
	bullet->SetSize(13, 37);
}

void Enemy::Reset()
{
	m_state = EnemyState::AIMING;
	m_target = nullptr;
	Set2DPosition(0, 0);
	isActive = false;
	m_hp = 10;
}

void Enemy::SetTexture(std::shared_ptr<Texture> texture)
{
	m_pTexture = texture;
}

void Enemy::SetBulletPool(std::shared_ptr<ObjectPool<Bullet>> bulletPool)
{
	m_bulletPool = bulletPool;
}

void Enemy::SetVelocity(Vector2 linear)
{

}

void Enemy::Init()
{
}

bool Enemy::InAttackRange(std::shared_ptr<Sprite2D> obj)
{
	Vector2 e_pos = Get2DPosition();
	Vector2 t_pos = obj->Get2DPosition();
	float distance = (e_pos.x - t_pos.x) * (e_pos.x - t_pos.x) + (e_pos.y - t_pos.y) * (e_pos.y - t_pos.y);

	if (distance < 250000)
		return true;
	else
		return false;
}


void Enemy::SetTarget(std::shared_ptr<Sprite2D> obj)
{
	m_target = obj;
}

void Enemy::ChangeState(EnemyState estt)
{
	m_state = estt;
}

bool Enemy::OnScreen()
{
	Vector2 pos = Get2DPosition();
	
	if (pos.x - m_iWidth / 2 < 0 || pos.x + m_iWidth / 2 > screenWidth)
		return false;
	if (pos.y - m_iHeight / 2 < 0 || pos.y + m_iHeight / 2 > screenHeight)
		return false;
	return true;
}

void Enemy::Update(GLfloat deltaTime)
{
	if (m_state == EnemyState::AIMING)
	{
		if (InAttackRange(m_target) && OnScreen())
		{
			m_bulletNum = 4;
			ChangeState(EnemyState::ATTACKING);
		}

		//set rotation
		Vector2 e_pos = Get2DPosition();
		Vector2 t_pos = m_target->Get2DPosition();
		if (t_pos.y - e_pos.y < 0)
			this->Set2DRotation(atanf((t_pos.x - e_pos.x) / (t_pos.y - e_pos.y)));
		else
			this->Set2DRotation(atanf((t_pos.x - e_pos.x) / (t_pos.y - e_pos.y)) - PI);

		// move toward the target
		Vector2 translate = t_pos - e_pos;
		Set2DPosition(e_pos + translate.Normalize() * m_velocity * deltaTime);
	}

	else if (m_state == EnemyState::ATTACKING)
	{
		m_currentTime += deltaTime;

		if (m_currentTime > m_ShootInterval)
		{
			EnemyAttack();
			m_bulletNum--;
			m_currentTime -= m_ShootInterval;
		}

		if (m_bulletNum == 0)
		{
			ChangeState(EnemyState::LEAVING);
		}
	}

	else if (m_state == EnemyState::LEAVING)
	{
		Vector2 e_pos = Get2DPosition();
		Vector2 t_pos = m_target->Get2DPosition();
		
		if (e_pos.x <= m_iWidth || e_pos.x >= screenWidth - m_iWidth || e_pos.y <= m_iHeight || e_pos.y > screenHeight - m_iHeight)
		{
			ChangeState(EnemyState::AIMING);
		}

		// move toward the target
		Vector2 translate = t_pos - e_pos;
		Vector2 normal = Vector2(translate.y, -translate.x);
		translate = translate * (rand() % 10 + 40) + normal * (rand() % 10 + 40) * (rand() % 2 - 1);
		Set2DPosition(e_pos - translate.Normalize() * m_velocity * deltaTime);

	}

	if (this->m_hp <= 0)
		this->Reset();
}