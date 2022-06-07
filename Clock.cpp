#include "Clock.h"

void Clock::start() {
	m_start = high_resolution_clock::now();
}

void Clock::stop() {
	m_stop = high_resolution_clock::now();
}

void Clock::printResult() {
	auto duration = duration_cast<milliseconds>(m_stop - m_start);
	std::cout << duration.count() << "ms" << std::endl;
}
