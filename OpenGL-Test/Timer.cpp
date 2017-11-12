#include "Timer.h"

Timer::Timer()
{
	cur = clock();
	prev = cur;

	t = 0;
	dt = 0;
	fps = 0;
}


Timer::~Timer() { }

void Timer::update()
{
	prev = cur;
	cur = clock();
	dt = (cur - prev) / (float)CLOCKS_PER_SEC;
	t += dt;
	fps = 1 / dt;
}
