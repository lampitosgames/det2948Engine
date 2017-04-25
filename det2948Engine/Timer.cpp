#include "Timer.h"

Timer::Timer() {
	this->prev = clock();
	this->cur = clock();
	this->t = 0;
	this->dt = 0;
	this->fps = 0;
}

Timer::~Timer() {
}

void Timer::Update() {
	this->prev = this->cur;
	this->cur = clock();
	this->dt = (this->cur - this->prev) / ((float)CLOCKS_PER_SEC);
	this->t += dt;
	this->fps = 1 / dt;
}
