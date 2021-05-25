#include "Meteor.h"

extern GLint screenWidth;
extern GLint screenHeight;

Meteor::Meteor(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture)
	: Sprite2D(model, shader, texture), m_angularVel(1)
{
}

Meteor::~Meteor()
{
}

void Meteor::Update(GLfloat deltaTime)
{
	Set2DPosition(Get2DPosition() + m_velocity * deltaTime);
	Set2DRotation(m_2DRotation + m_angularVel * PI * deltaTime);

	if (Get2DPosition().x  <  -100 || Get2DPosition().x > screenWidth + 100)
		Reset();
	else if (Get2DPosition().y  < -100 || Get2DPosition().y > screenHeight + 100)
		Reset();
}

void Meteor::Reset()
{
	Set2DPosition(0, 0);
	Set2DRotation(0);
	SetVelocity(Vector2(0, 0));
	isActive = false;
}

void Meteor::SetTexture(std::shared_ptr<Texture> texture)
{
	m_pTexture = texture;
}

void Meteor::SetTexture(int textr)
{
	m_textr = textr;
	switch (textr)
	{
		case 0:
		{
			SetTexture(ResourceManagers::GetInstance()->GetTexture("meteorBrown2"));
			SetSize(45, 40);
			break;
		}
		case 1:
		{
			SetTexture(ResourceManagers::GetInstance()->GetTexture("meteorBrown1"));
			SetSize(45, 40);
			break;
		}
		case 2:
		{
			SetTexture(ResourceManagers::GetInstance()->GetTexture("meteorGrey2"));
			SetSize(45, 40);
			break;
		}
		case 3:
		{
			SetTexture(ResourceManagers::GetInstance()->GetTexture("meteorGrey2"));
			SetSize(45, 40);
			break;
		}
		case 4:
		{
			SetTexture(ResourceManagers::GetInstance()->GetTexture("meteorBrown_big1"));
			SetSize(101, 84);
			break;
		}
		case 5:
		{
			SetTexture(ResourceManagers::GetInstance()->GetTexture("meteorBrown_big2"));
			SetSize(89, 82);
			break;
		}
		case 6:
		{
			SetTexture(ResourceManagers::GetInstance()->GetTexture("meteorGrey_big2"));
			SetSize(120, 98);
			break;
		}
		case 7:
		{
			SetTexture(ResourceManagers::GetInstance()->GetTexture("meteorGrey_big1"));
			SetSize(98, 96);
			break;
		}
	}
}

void Meteor::SetVelocity(Vector2 vel)
{
	m_velocity = vel;
}

void Meteor::Init()
{
	srand(time(0));
	int textr = rand() % 8;

	m_textr = textr;
	SetTexture(textr);
}