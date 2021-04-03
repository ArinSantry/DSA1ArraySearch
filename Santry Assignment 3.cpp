#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <algorithm>
#include <chrono>

using namespace std;

// const array size
const int ARRAY_SIZE = 100;

// max value for random numbers
int numIterations;
double timeElapsed;

void fillRandomNumbers(int a[], const int size) {

	srand(time(NULL));
	if (size >= 1) {
		for (int i = 0; i < size; i++)
			a[i] = (rand() % (6 * size + 1)) - (3 * size);
	}
	else {
		cerr << "invalid array size ..." << endl;
	}
}

// print the unput array, 10 numbers per line
void printArray(int a[], const int size) {

	if (size >= 1) {
		for (int i = 0; i < size; i++) {
			cout << a[i] << "\t";
			if (i % 10 == 0)
				cout << endl;
		}
	}
	else {
		cerr << "invalid array size ..." << endl;
	}
}


int linearSearch(int arr[], int size, int key)
{
	chrono::steady_clock::time_point begin = chrono::steady_clock::now();
	for (int i = 0; i < size; i++)
	{
		numIterations++;
		if (arr[i] == key)
		{
			chrono::steady_clock::time_point end = chrono::steady_clock::now();
			timeElapsed = (double)chrono::duration_cast<chrono::nanoseconds>(end - begin).count();
			return i;
		}
	}
	chrono::steady_clock::time_point end = chrono::steady_clock::now();
	timeElapsed = (double)chrono::duration_cast<chrono::nanoseconds>(end - begin).count();
	return -1;
}

int binarySearch(int arr[], int start, int end, int key)
{
	chrono::steady_clock::time_point begin = chrono::steady_clock::now();
	numIterations++;
	int mid;
	if (start > end)
	{
		chrono::steady_clock::time_point end = chrono::steady_clock::now();
		timeElapsed = (double)chrono::duration_cast<chrono::nanoseconds>(end - begin).count();
		return -1;
	}
	else
	{
		mid = (start + end) / 2;
		if (key == arr[mid])
		{
			chrono::steady_clock::time_point end = chrono::steady_clock::now();
			timeElapsed = (double)chrono::duration_cast<chrono::nanoseconds>(end - begin).count();
			return mid;
		}
		else if (key < arr[mid])
			binarySearch(arr, start, mid - 1, key);
		else
			binarySearch(arr, mid + 1, end, key);
	}
}

int main() {

	int* myArray = new int[ARRAY_SIZE];
	fillRandomNumbers(myArray, ARRAY_SIZE);
	sort(myArray, myArray + ARRAY_SIZE);
	printArray(myArray, ARRAY_SIZE);
	int num;
	numIterations = 0;

	cout << "\nEnter number: " << endl;
	cin >> num;
	int position = linearSearch(myArray, ARRAY_SIZE, num);
	cout << endl << "Linear search: " << endl;
	if (position == -1)
		cout << "Number is not present in the array, " << numIterations << " searches in " << timeElapsed << " nanoseconds." << endl;
	else
		cout << "Number is in position " << position << ", found in " << numIterations << " searches in " << timeElapsed << " nanoseconds." <<  endl;

	numIterations = 0;
	cout << endl << "Binary search: " << endl;
	position = binarySearch(myArray, 0, ARRAY_SIZE - 1, num);
	if (position == -1)
		cout << "Number is not present in the array, " << numIterations << " searches in " << timeElapsed << " nanoseconds." << endl;
	else
		cout << "Number is in position " << position << ", found in " << numIterations << " searches in " << timeElapsed << " nanoseconds." << endl;

	delete[] myArray;
	return 0;
}