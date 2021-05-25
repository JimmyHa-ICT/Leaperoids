#pragma once 
#include "Sprite2D.h"
#include "ObjectPool.h"
#include "Bullet.h"
#include "ResourceManagers.h"

enum EnemyState {
	AIMING = 0,
	ATTACKING,
	LEAVING, // for runnning, reload the bullet, prepare for re-aiming
};

class Enemy : public Sprite2D
{
public:
	Enemy(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture);
	~Enemy();
	void	Update(GLfloat deltaTime);
	int		GetHP();
	void	SetHP(int);
	void	EnemyAttack();
	bool	isActive = false;
	void	Reset();
	void	SetTexture(std::shared_ptr<Texture> texture);
	void	SetBulletPool(std::shared_ptr<ObjectPool<Bullet>>);
	void	SetVelocity(Vector2);
	void	Init();
	bool	InAttackRange(std::shared_ptr<Sprite2D>);
	void	SetTarget(std::shared_ptr<Sprite2D>);
	void	ChangeState(EnemyState);
	bool	OnScreen();

private:

	EnemyState	m_state;
	std::shared_ptr<Sprite2D> m_target;
	int		m_bulletNum = 4;	//current number of bullets
	int		m_hp;
	float	m_velocity = 150;
	float	m_currentTime = 0;
	float	m_ShootInterval = 0.3;
	std::shared_ptr<ObjectPool<Bullet>>	m_bulletPool;
};
