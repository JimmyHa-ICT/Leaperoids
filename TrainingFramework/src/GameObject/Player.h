#pragma once 
#include "Sprite2D.h"

class Player : public Sprite2D
{
public:
	Player(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture);
	~Player();
	void	HandleTouchEvents(GLint x, GLint y, bool bIsPressed);
	void	HandleKeyEvent(unsigned char key, bool bIsPresseded);
	void	Update(GLfloat deltaTime);
	int		GetLives();
	void	SetLives(int);
	bool	IsCollided(std::shared_ptr<Sprite2D>);

private:
	int		m_lives;
	float	m_velocity = 250;
	int		horizontalInput = 0;
	int		verticalInput = 0;
	float   rotationInput = 0;
};
