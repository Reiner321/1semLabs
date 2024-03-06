#include <stdio.h>
#include <random>
#include <fstream>
#include <iostream>

bool createFileWithRandomNumber(const std::string &fileName, const int numbersCount, const int maxNumberValue)
{
	std::fstream file(fileName);
	if (!file) {
		return -1;
	}
	
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_int_distribution<int> dist(0, maxNumberValue);

	for (int i = 0; i < numbersCount; ++i) {
		file << dist(mt) << std::endl;
	}
	if (!file.good()) {
		return false;
	}
	file.close();
	return true;
}

bool isFileContainsSortedArray(const std::string& fileName) {
	std::ifstream file(fileName);
	if (!file) {
		return -1;
	}

	int prev;
	file >> prev;
	while (true) {
		int num;
		file >> num;
		if (num < prev) return false;
		prev = num;
	}
}

int sortFile(const std::string& fileName)
{

}

int createAndSortFile(const std::string& fileName, const int numbersCount, const int maxNumberValue)
{
	if (!createFileWithRandomNumber(fileName, numbersCount, maxNumberValue)) {
		return -1;
	}

	sortFile(fileName);

	if (!isFileContainsSortedArray(fileName)) {
		return -2;
	}
	return 1;
}

int main()
{
	std::string fileName = "file.txt";
	const int numbersCount = 1000000;
	const int maxNumberValue = 10000;
	for (int i = 0; i < 10; i++) {
		switch (createAndSortFile(fileName, numbersCount, maxNumberValue)) {
		case 1:
			std::cout << "Test passed" << std::endl;
		break;
		
		case -1:
			std::cout << "Test failed:can't create file" << std::endl;
		break;
		
		case -2:
			std::cout << "Test failed:file isn't sorted" << std::endl;
		break;
		}
	}
	return 0;
}