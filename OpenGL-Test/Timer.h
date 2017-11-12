#pragma once
#include <ctime>

class Timer
{
private: 
	clock_t cur;
	clock_t prev;
public:
	float t;
	float dt;
	float fps;

	Timer();
	~Timer();

	void update();
};

