#pragma once
#include <iostream>
#include <string>
#include <ctime>

using namespace std;

class Timer {
private:
	clock_t cur, prev;
public:
	//Time in seconds since starting/constructor/declaration
	float t;
	//Time in seconds between two most recent updates
	float dt;
	//Measures 1/dt, approximate # of updates per second
	float fps;

	Timer();
	~Timer();

	void Update();
};