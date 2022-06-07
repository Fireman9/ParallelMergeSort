#ifndef POLYGON__DATAGENERATOR_H_
#define POLYGON__DATAGENERATOR_H_

#include <cstddef>
#include <random>
#include <algorithm>

class DataGenerator {
public:
	template<typename T>
	void generateRandomArray(T *p, size_t n, int rangeFrom, int rangeTo);

	template<typename T>
	void generateReverseSortedArray(T *p, size_t n, int rangeFrom, int rangeTo);

	template<typename T>
	void generateShuffledArray(T *p, size_t n, int rangeFrom, int rangeTo, size_t parts);
};

template<typename T>
void DataGenerator::generateRandomArray(T *p, size_t n, int rangeFrom, int rangeTo) {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> distr(rangeFrom, rangeTo);
	for (T *pEnd = p + n; p != pEnd; *p++ = distr(gen));
}

template<typename T>
void DataGenerator::generateReverseSortedArray(T *p, size_t n, int rangeFrom, int rangeTo) {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> distr(rangeFrom, rangeTo);
	for (T *pEnd = p + n; p != pEnd; *p++ = distr(gen));
	std::sort(p - n, p, std::greater<>());
}

template<typename T>
void DataGenerator::generateShuffledArray(T *p, size_t n, int rangeFrom, int rangeTo, size_t parts) {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> distr(rangeFrom, rangeTo);
	for (T *pEnd = p + n; p != pEnd; *p++ = distr(gen));
	p -= n;
	size_t elementsPerPart = (size_t) n / parts;
	for (size_t i = 1; i <= parts; i++) {
		if (i % 2 != 0) {
			std::sort(p + (i - 1) * elementsPerPart, p + i * elementsPerPart);
		}
	}
}

#endif //POLYGON__DATAGENERATOR_H_
