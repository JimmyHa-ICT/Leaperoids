#pragma once
#include <vector>
#include "BaseObject.h"

template <class T>

class ObjectPool
{
private:
	std::vector<std::shared_ptr<T>> objects;
	int POOL_SIZE = 100;
	bool isSpawning = false;
	float currentTime = 0;
	float spawnInterval = 1;
	
public:
	ObjectPool()
	{
		srand(time(0));
		Init();
	}

	void Init()
	{
		for (int i = 0; i < POOL_SIZE; i++)
		{
			auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
			auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
			//auto texture = ResourceManagers::GetInstance()->GetTexture("button_play");
			auto obj = std::make_shared<T>(model, shader, nullptr);
			objects.push_back(obj);
		}
	}

	std::shared_ptr<T> GetObjectT()
	{
		for (auto obj : objects)
		{
			if (!obj->isActive)
			{
				obj->isActive = true;
				return obj;
			}
		}

		Init();

		POOL_SIZE *= 2;
		return GetObjectT();
	}

	void ReturnObject(std::shared_ptr<T> obj)
	{
		obj->Reset();
	}

	void Update(GLfloat deltaTime)
	{
		if (isSpawning)
		{
			//std::cout << currentTime << std::endl;
			currentTime += deltaTime;
			if (currentTime > spawnInterval)
			{
				
				currentTime -= spawnInterval;
				SpawnObjectT();
			}
		}

		for (auto obj : objects)
		{
			if (obj->isActive)
				obj->Update(deltaTime);
		}
	}

	void Draw()
	{
		for (auto obj : objects)
		{
			if (obj->isActive)
				obj->Draw();
		}
	}

	std::vector<std::shared_ptr<T>> GetAllActive()
	{
		std::vector<std::shared_ptr<T>> allActives;
		for (auto obj : objects)
		{
			if (obj->isActive)
				allActives.push_back(obj);
		}

		return allActives;
	}

	void StartSpawning(float interval = 1)
	{
		spawnInterval = interval;
		isSpawning = true;
	}

	void SpawnObjectT()
	{
		std::shared_ptr<T> meteor;
		
		if (rand() % 2 == 1)		// spawn from left
		{
			meteor = GetObjectT();
			meteor->Init();
			meteor->Set2DPosition(-80, rand() % screenHeight);
			meteor->SetVelocity(Vector2(rand() % 100 + 200, rand() % 400 - 200));
		}
		
		if (rand() % 2 == 1)		// spawn from top
		{
			meteor = GetObjectT();
			meteor->Init();
			meteor->Set2DPosition(rand() % screenWidth, -80);
			meteor->SetVelocity(Vector2(rand() % 400 - 200, rand() % 100  + 200));
		}

		if (rand() % 2 == 1)		//spawn from right
		{
			meteor = GetObjectT();
			meteor->Init();
			meteor->Set2DPosition(screenWidth + 80, rand() % screenHeight);
			meteor->SetVelocity(Vector2(-(rand() % 100 + 200), rand() % 400 - 200));
		}

		if (rand() % 2 == 1)		// spawn from bottom
		{
			meteor = GetObjectT();
			meteor->Init();
			meteor->Set2DPosition(rand() % screenWidth, -80);
			meteor->SetVelocity(Vector2(rand() % 400 - 200, -(rand() % 100 + 200)));
		}
	}

	void StopSpawning()
	{
		isSpawning = false;
		currentTime = 0;
	}
};