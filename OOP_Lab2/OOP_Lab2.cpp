#include <iostream>

#include "Array.h"

template <typename T>
double calculateAvg(const Array<T> arr)
{
	if (arr.size() == 0) {
		return 0;
	}

	double avg = 0;
	for (int i = 0; i < arr.size(); ++i) {
		avg += arr[i];
	}
	avg /= arr.size();
	return avg;
}

template <typename T>
void testArray()
{
	{
		Array<T> arrA(5, 0);
		Array<T> arrB(5, 1);
		arrA += arrB;
		arrA.print();
	}

	Array<T> arr(10, 0);
	T a = arr[3];
	std::cout << arr[3] << ' ' << arr[9] << std::endl;
	arr[3] = 16;
	arr[5] = arr[3];
	std::cout << "Average value: " << calculateAvg(arr) << '\n';

	/*
	std::cout << "Average value: " << calculateAvg(arr) << '\n' :
	operator<<(
		operator<<(
			operator<<(std::cout, "Average value: "),
			calculateAvg(arr)
		),
		'\n'
	);
	*/

	arr.print();
}

int main()
{
	testArray<int>();
	getchar();
	return 0;
}