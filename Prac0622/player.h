#pragma once
class Player
{
public:
	Player();
	void Update();
	void Render();

	float playerX;
	float playerY;

	int speed;
};

