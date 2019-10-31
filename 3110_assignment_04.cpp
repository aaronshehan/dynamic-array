#include <iostream>
#include <chrono>
//#include <algorithm>

using namespace std::chrono;

class Array {
private:
	int __size;
	int __capacity;
	int* array;
public:
	//default constructor, sets capacity to 10
	Array() {
		__size = 0;
		__capacity = 10;

		array = new int[10];
	}

	//constructor that allows user to define original size of array
	Array(int size) {
		__size = size;
		__capacity = 2 * size;

		array = new int[__capacity];
	}

	//destructor, cleans memory
	~Array() {
		delete array;
	}

	//return size
	int size() { return __size;  }

	//return capacity
	int capacity() { return __capacity;  }

	//add element to end of array
	void append(int val) {
		if (__size == 0 || __size < __capacity) {
			*(array + __size++) = val;
			resize();
		}
		else {
			resize();
			*(array + __size++) = val;	
		}
		
	}

	//remove last element
	void pop() {
		*( array + --__size) = 0;
		resize();
	}

	//checks if array is empty
	int empty() {
		if (__size == 0)
			return 1;
		else
			return 0;

	}

	//resizes array
	//if 1/4 full, array capacity decreases by 1/2
	//when array capacity is met, it doubles
	void resize() {

		if (__size == __capacity) {
			int* temp;
			temp = new int[__size];

			for (int i = 0; i < __size; i++)
				*(temp + i) = *(array + i);

			delete array;

			array = new int[2 * __capacity];

			for (int i = 0; i < __size; i++)
				*(array + i) = *(temp + i);

			__capacity *= 2;

			delete temp;
		}

		else if (__size == __capacity / 4) {
			int* temp;
			temp = new int[__size];

			for (int i = 0; i < __size; i++)
				*(temp + i) = *(array + i);

			delete array;

			array = new int[__capacity / 2];

			for (int i = 0; i < __size; i++)
				*(array + i) = *(temp + i);

			__capacity /= 2;

			delete temp;
		}

		else {
			return;
		}

	}

	//print all elements in array
	void print() {
		for (int i = 0; i < __size; i++)
			std::cout << *(array + i) << " ";
		std::cout << std::endl;
	}

	//overloaded brackets to get element
	int operator [](int index) {
		return *(array + index);
	}
};

//perform random operations on array
void ranops(int n) {
	Array array;
	for (int i = 0; i < n; i++) {
		int dice;
		dice = rand() % 2;
		if (dice > 0)
			array.append(n);
		else if (array.empty() == 0)
			array.pop();
	}

}

//benchmark
void abm(int n) {
	auto start = high_resolution_clock::now();
	ranops(n);
	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(stop - start);
	std::cout << "Benchmark for " << n << " array operations " << duration.count()*0.000001 << " seconds" << std::endl;
}
int main()
{
	Array x;
	abm(1000);
	abm(10000);
	abm(100000);
	abm(1000000);
	abm(10000000);

	return 0;
}
