// Voltorb_Game.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "pch.h"


#include "Application.h"



Application* app;



int main() {


	app = new Application();
	app->Init();


	sf::Clock clock;

	while (app->IsRunning()) {

		sf::Time frameTime = clock.restart();

		app->Update(frameTime);
		app->Render();
	}


	return 0;
}

/*
void merge(int arr[], int left, int middle, int right);
void mergeSort(int arr[], int left, int right);


int main()
{

	int arr[] = { 54, 32, 16, 45, 65, 1, 1, 4, 3 };
	int arr_size = sizeof(arr) / sizeof(arr[0]);

	mergeSort(arr, 0, arr_size - 1);

	int meh;

	return 0;
	
}



void merge(int arr[], int left, int middle, int right) {


	int i, j, k;
	int leftLength = middle - left + 1;
	int rightLength = right - middle;

	

	int* arrLeft = new int[leftLength];
	int* arrRight = new int[rightLength];

	for (i = 0; i < leftLength; i++) {
		arrLeft[i] = arr[left + i];
	}

	for (j = 0; j < rightLength; j++) {
		arrRight[j] = arr[middle + 1 + j];
	}

	i = 0;
	j = 0;
	k = left;

	while (i < leftLength && j < rightLength) {

		if (arrLeft[i] <= arrRight[j]) {

			arr[k] = arrLeft[i];
			i++;
		}
		else {

			arr[k] = arrRight[j];
			j++;
		}

		k++;
	}

	while (i < leftLength) {

		arr[k] = arrLeft[i];
		i++;
		k++;
	}

	while (j < rightLength) {

		arr[k] = arrRight[j];
		j++;
		k++;
	}

	delete arrLeft;
	arrLeft = nullptr;
	delete arrRight;
	arrRight = nullptr;

}



void mergeSort(int arr[], int left, int right) {

	if (left < right) {

		int middle = left + (right - 1) / 2;

		mergeSort(arr, left, middle);
		mergeSort(arr, middle + 1, right);

		merge(arr, left, middle, right);
	}
}


// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
*/