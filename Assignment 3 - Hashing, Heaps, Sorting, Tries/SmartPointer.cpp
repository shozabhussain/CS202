#include <iostream>
#include <memory>
using namespace std;

int main()
{

//----------------------------------------------------  Raw Pointers  --------------------------------------------------------------

	/* Dynamically declaring an array of objects */
	int* normalArray = new int[5];

	/* Assinging values to the array */
	for(int i = 0; i < 5; i++)
	{
		normalArray[i] = i;
	}

	/*Creating a temporary pointer to the array */
	int* temp = normalArray;

	/* Reallocating the array to a larger size */
	normalArray = new int[10];

	/* Copying back the old values*/
	for(int i = 0; i < 5; i++)
	{
		normalArray[i] = temp[i];
	}

	/* Filling up the remaining space with new values */
	for(int i = 5; i < 10; i++)
	{
		normalArray[i] = i*i;
	}

	/* Deallocating the space allocated for the original array of size 5 */
	delete [] temp;
	temp = NULL;

	cout << "Printing with Raw Pointers:" << endl;

	for(int i = 0; i < 10; i++)
	{
		cout << normalArray[i] << "	";
	}
	cout << endl << endl;

//----------------------------------------------------  Smart Pointers  --------------------------------------------------------------

	/* Dynamically declaring an array of objects */
	shared_ptr<int> myArray(new int[5], default_delete<int[]>());

	/* Assinging values to the array */
	for(int i = 0; i < 5; i++)
	{
		myArray.get()[i] = i;
	}

	/*Creating a temporary pointer to the array */
	shared_ptr<int> tempArray = myArray;

	/* Reallocating the array to a larger size */
	myArray.reset(new int[10], default_delete<int[]>());

	/* Copying back the old values*/
	for(int i = 0; i < 5; i++)
	{
		myArray.get()[i] = tempArray.get()[i];
	}

	/* Filling up the remaining space with new values */
	for(int i = 5; i < 10; i++)
	{
		myArray.get()[i] = i*i;
	}

	tempArray.reset();
	tempArray = NULL;

	cout << "Printing with Smart Pointers" << endl;

	for(int i = 0; i < 10; i++)
	{
		cout << myArray.get()[i] << "	";
	}

	return 0;
}