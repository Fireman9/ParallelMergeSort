#ifndef POLYGON__MERGESORT_H_
#define POLYGON__MERGESORT_H_

#include <vector>
#include <future>

using std::vector;
using std::swap;
using std::distance;
using std::async;

class MergeSort {
public:
	// Simple merge sort algorithm using merge with buffer
	template<typename Iter>
	void sequentialMergeSort(Iter begin, Iter end);

	// Merge sort algorithm using inplace_sort
	template<typename Iter>
	void sequentialMergeSortInplace(Iter begin, Iter end);

	// Merge sort algorithm using inplace_sort and std::sort on sub arrays with size < threshold
	template<typename Iter>
	void sequentialMergeSortInsInplace(Iter begin, Iter end, int threshold = 32);

	// Parallel merge sort algorithm
	template<typename Iter>
	void parallelMergeSort(Iter begin, Iter end, unsigned int N);

	// Parallel merge sort algorithm using inplace_sort
	template<typename Iter>
	void parallelMergeSortInplace(Iter begin, Iter end, unsigned int N);

	// Parallel merge sort algorithm using inplace_sort and std::sort on sub arrays with size < threshold
	template<typename Iter>
	void parallelMergeSortInsInplace(Iter begin, Iter end, unsigned int N, int threshold = 32);

private:
	// Merge algorithm
	template<typename Iter>
	void merge(Iter begin, Iter mid, Iter end);
};

template<typename Iter>
void MergeSort::merge(Iter begin, Iter mid, Iter end) {
	vector<int> temp(distance(begin, end));
	auto tempIter = temp.begin();
	auto beginDup = begin;
	auto midDup = mid;
	while (begin != midDup && mid != end) {
		if (*begin < *mid) *tempIter++ = *begin++;
		else *tempIter++ = *mid++;
	}
	while (begin != midDup) *tempIter++ = *begin++;
	while (mid != end) *tempIter++ = *mid++;
	tempIter = temp.begin();
	while (beginDup != end) *beginDup++ = *tempIter++;
}

template<typename Iter>
void MergeSort::sequentialMergeSort(Iter begin, Iter end) {
	auto len = distance(begin, end);
	if (len < 2) return;
	Iter mid = next(begin, len / 2);
	sequentialMergeSort(begin, mid);
	sequentialMergeSort(mid, end);
	merge(begin, mid, end);
}

template<typename Iter>
void MergeSort::sequentialMergeSortInplace(Iter begin, Iter end) {
	auto len = distance(begin, end);
	if (len < 2) return;
	Iter mid = next(begin, len / 2);
	sequentialMergeSortInplace(begin, mid);
	sequentialMergeSortInplace(mid, end);
	inplace_merge(begin, mid, end);
}

template<typename Iter>
void MergeSort::sequentialMergeSortInsInplace(Iter begin, Iter end, int threshold) {
	auto len = distance(begin, end);
	if (len < 2) return;
	if (len < threshold) {
		sort(begin, end);
		return;
	}
	Iter mid = next(begin, len / 2);
	sequentialMergeSortInsInplace(begin, mid);
	sequentialMergeSortInsInplace(mid, end);
	inplace_merge(begin, mid, end);
}

template<typename Iter>
void MergeSort::parallelMergeSort(Iter begin, Iter end, unsigned int N) {
	auto len = distance(begin, end);
	if (len < 2) return;
	Iter mid = next(begin, len / 2);
	if (N > 1) {
		auto fn = async([this](Iter begin, Iter end, unsigned int N) {
			parallelMergeSort<Iter>(begin, end, N);
		}, begin, mid, N - 2);
		parallelMergeSort(mid, end, N - 2);
		fn.wait();
	} else {
		parallelMergeSort(begin, mid, 0);
		parallelMergeSort(mid, end, 0);
	}
	merge(begin, mid, end);
}

template<typename Iter>
void MergeSort::parallelMergeSortInplace(Iter begin, Iter end, unsigned int N) {
	auto len = distance(begin, end);
	if (len < 2) return;
	Iter mid = next(begin, len / 2);
	if (N > 1) {
		auto fn = async([this](Iter begin, Iter end, unsigned int N) {
			parallelMergeSortInplace<Iter>(begin, end, N);
		}, begin, mid, N - 2);
		parallelMergeSortInplace(mid, end, N - 2);
		fn.wait();
	} else {
		parallelMergeSortInplace(begin, mid, 0);
		parallelMergeSortInplace(mid, end, 0);
	}
	inplace_merge(begin, mid, end);
}

template<typename Iter>
void MergeSort::parallelMergeSortInsInplace(Iter begin, Iter end, unsigned int N, int threshold) {
	auto len = distance(begin, end);
	if (len < 2) return;
	if (len < threshold) {
		sort(begin, end);
		return;
	}
	Iter mid = next(begin, len / 2);
	if (N > 1) {
		auto fn = async([this](Iter begin, Iter end, unsigned int N) {
			parallelMergeSortInsInplace<Iter>(begin, end, N);
		}, begin, mid, N - 2);
		parallelMergeSortInsInplace(mid, end, N - 2);
		fn.wait();
	} else {
		parallelMergeSortInsInplace(begin, mid, 0);
		parallelMergeSortInsInplace(mid, end, 0);
	}
	inplace_merge(begin, mid, end);
}

#endif //POLYGON__MERGESORT_H_
