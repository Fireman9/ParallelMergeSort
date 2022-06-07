#include "DataGenerator.h"
#include "MergeSort.h"
#include "Clock.h"

using std::vector;
using std::cout;
using std::endl;

void isSorted(vector<int> &array) {
	cout << "Is sorted: " << (is_sorted(array.begin(), array.end()) ? "true" : "false") << endl << endl;
}

int main() {
	size_t const SIZE = 1000000;
	size_t const RANGE = 1000;
	unsigned h_c = std::thread::hardware_concurrency();
	h_c = h_c ? h_c : 1;
	DataGenerator data_generator;
	Clock clock;
	MergeSort sort;

	// Arrays initialization
	vector<int> randomArray(SIZE);
	vector<int> testRandomArray(SIZE);
	vector<int> reversedArray(SIZE);
	vector<int> testReversedArray(SIZE);
	vector<int> shuffledArray(SIZE);
	vector<int> testShuffledArray(SIZE);

	// Data generation
	data_generator.generateRandomArray(randomArray.data(), randomArray.size(),
									   0, RANGE);
	data_generator.generateReverseSortedArray(reversedArray.data(), reversedArray.size(),
											  0, RANGE);
	data_generator.generateShuffledArray(shuffledArray.data(), shuffledArray.size(),
										 0, RANGE, 10);
	testRandomArray = randomArray;
	reversedArray = testReversedArray;
	shuffledArray = testShuffledArray;

	std::sort(testRandomArray.begin(), testRandomArray.end());
	std::sort(testReversedArray.begin(), testReversedArray.end());
	std::sort(testShuffledArray.begin(), testShuffledArray.end());

	// Testing
	cout << "Arrays size = " << SIZE << ", randInt%" << RANGE << endl << endl;

	clock.start();
	sort.parallelMergeSortInsInplace(randomArray.begin(), randomArray.end(), h_c);
	clock.stop();
	cout << "Random array sorted in: ";
	clock.printResult();
	cout << "No data loses: " << ((randomArray == testRandomArray) ? "true" : "false") << endl;
	isSorted(randomArray);

	clock.start();
	sort.parallelMergeSortInsInplace(reversedArray.begin(), reversedArray.end(), h_c);
	clock.stop();
	cout << "Reversed array sorted in: ";
	clock.printResult();
	cout << "No data loses: " << ((reversedArray == testReversedArray) ? "true" : "false") << endl;
	isSorted(reversedArray);

	clock.start();
	sort.parallelMergeSortInsInplace(shuffledArray.begin(), shuffledArray.end(), h_c);
	clock.stop();
	cout << "Shuffled array sorted in: ";
	clock.printResult();
	cout << "No data loses: " << ((shuffledArray == testShuffledArray) ? "true" : "false") << endl;
	isSorted(shuffledArray);

	return 0;
}
