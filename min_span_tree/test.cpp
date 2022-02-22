#include<iostream>
using std::cout;
using std::endl;

struct bar
{
	int x;
	int y;
};

void foo(int array[], int size);
void foo(bar array[], int size);

int main()
{
	int array[4] {0};

	cout << "Before: ";
	for(int i = 0; i < 4; i++)
		cout << array[i] << " ";
	cout << endl;

	foo(array, 4);

	cout << "After: ";
	for(int i = 0; i < 4; i++)
		cout << array[i] << " ";
	cout << endl;

	bar array2[4] {0};

	cout << "Before: ";
	for(int i = 0; i < 4; i++)
		cout << "[" << array2[i].x << ", " << array2[i].y << "] ";
	cout << endl;

	foo(array2, 4);

	cout << "After: ";
	for(int i = 0; i < 4; i++)
		cout << "[" << array2[i].x << ", " << array2[i].y << "] ";
	cout << endl;

	return 0;
}

void foo(int array[], int size)
{
	for(int i = 0; i < size; i++)
	{
		array[i] = array[i] + 10;
	}
}

void foo(bar array[], int size)
{
	for(int i = 0; i < size; i++)
	{
		array[i].x = array[i].x + 10;
		array[i].y = array[i].y + 10;
	}
}
