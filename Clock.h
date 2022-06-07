#ifndef POLYGON__CLOCK_H_
#define POLYGON__CLOCK_H_

#include <iostream>
#include <chrono>

using namespace std::chrono;

class Clock {
public:
	void start();

	void stop();

	void printResult();

private:
	system_clock::time_point m_start;
	system_clock::time_point m_stop;
};

#endif //POLYGON__CLOCK_H_
