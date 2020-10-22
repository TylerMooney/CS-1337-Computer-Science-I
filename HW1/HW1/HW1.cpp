/*
Author: Tyler Mooney
Date: January 30, 2020
Professor: Khiem Le
Compiler: GNU GCC

Purpose: prompt the user for a file name, then acquire the records of students,
and then prompt the user to choose between seeing the top students above a specified rank,
search for a student, and to exit the program.

Notes:
When reading in a student record it will be in this order: netID, major, GPA.
Don't check for input validation when reading from the file.
GPA must always have 2 decimal places present
Functions:
    main: the main function that holds the original arrays and will call the other functions
    modifiedSortGPA: sorts the arrays cotents based on the lowest to highest GPA
    modifiedSortID: sorts the arrays contents based on the lowest to highest ID
    linearSearchID: does a linear search for the inputted ID
    binarySearchID: does a binary search for the inputted ID

*/

#include <iostream>
#include <iomanip>
#include <fstream>

using namespace std;

//function prototypes
void modifiedSortGPA(double[], int[], string[], int);
void modifiedSortID(int [], double [], string [], int);
int linearSearchID(int [], int, int, int&);
int binarySearchID(int [], int, int, int&);

int main()
{
    //Variable and array initializations
    string fileName;
    const int NUM_ELMTS = 18;
    int size = 0, choice = 0;

    // netID, major and GPA are parallel arrays
    int netID[NUM_ELMTS]; // Original netID array
    string major[NUM_ELMTS]; // Original major array
    double GPA[NUM_ELMTS]; // Original GPA array

    // sortedGPAbyGPA is sorted by GPA, and sortedNetIDbyGPA and sortedMajorbyGPA are parallel arrays
    double sortedGPAbyGPA[NUM_ELMTS]; // GPA array, sorted by GPA
    int sortedNetIDbyGPA[NUM_ELMTS];
    string sortedMajorbyGPA[NUM_ELMTS];

    // sortedNetIDbyID is sorted by netID, and sortedMajorbyID and sortedGPAbyID are parallel arrays 
    int sortedNetIDbyID[NUM_ELMTS]; // netID array,sorted by netID
    string sortedMajorbyID[NUM_ELMTS];
    double sortedGPAbyID[NUM_ELMTS];

    //Prompt user for file name
    cout << "Enter file name: ";
    cin >> fileName;

    //file for input
    ifstream inFile;
    inFile.open(fileName);

    //Checks if file will open, if it doesn't it will close the program
    //if it does, read in the information from the file into the the proper arrays
    if (inFile.fail())
    {
        cout << "Could not open file\nExiting" << endl;
        inFile.close();
        exit(EXIT_FAILURE);
    }
    else
    {
        //temporary variable initilizations
        int tempNetID = 0;
        string tempMajor = "";
        double tempGPA = 0;
        int i = 0;

        //read in information from the file into the proper arrays
        while (inFile >> tempNetID >> tempMajor >> tempGPA && i < NUM_ELMTS)
        {
            netID[i] = tempNetID;
            major[i] = tempMajor;
            GPA[i] = tempGPA;
            sortedNetIDbyGPA[i] = tempNetID;
            sortedMajorbyGPA[i] = tempMajor;
            sortedGPAbyGPA[i] = tempGPA;
            sortedNetIDbyID[i] = tempNetID;
            sortedMajorbyID[i] = tempMajor;
            sortedGPAbyID[i] = tempGPA;
            i++;
        }
        size = i;
    }
    inFile.close();

    //sorts one set of arrays by GPA and the other set by ID
    modifiedSortGPA(sortedGPAbyGPA, sortedNetIDbyGPA, sortedMajorbyGPA, size);
    modifiedSortID(sortedNetIDbyID, sortedGPAbyID, sortedMajorbyID, size);

    //printing original arrays
    cout << "Original arrays:\n----------------\n";
    cout << "index  netID  major   GPA   index  netID  major   GPA\n";
    for (int i = 0; i < size; i++)
    {
        //checks if this is the second iteration in a row or not
        if (i % 2 == 1)
        {
            cout << fixed << setprecision(2) << setw(8) << i << setw(7) << netID[i]
                << setw(7) << major[i] << setw(6) << GPA[i] << endl;
        }
        else
        {
            cout << fixed << setprecision(2) << setw(5) << i << setw(7) << netID[i]
                << setw(7) << major[i] << setw(6) << GPA[i];
        }

    }

    //printing arrays sorted by GPA
    cout << "\nArrays sorted by GPA:\n---------------------\n";
    cout << "index  netID  major   GPA   index  netID  major   GPA\n";
    for (int i = 0; i < size; i++)
    {
        //checks if this is the second iteration in a row or not
        if (i % 2 == 1)
        {
            cout << fixed << setprecision(2) << setw(8) << i << setw(7) << sortedNetIDbyGPA[i]
                << setw(7) << sortedMajorbyGPA[i] << setw(6) << sortedGPAbyGPA[i] << endl;
        }
        else
        {
            cout << fixed << setprecision(2) << setw(5) << i << setw(7) << sortedNetIDbyGPA[i]
                << setw(7) << sortedMajorbyGPA[i] << setw(6) << sortedGPAbyGPA[i];
        }
    }

    //printing arrays sorted by netID
    cout << "\nArrays sorted by netID:\n-----------------------\n";
    cout << "index  netID  major   GPA   index  netID  major   GPA\n";
    for (int i = 0; i < size; i++)
    {
        //checks if this is the second iteration in a row or not
        if (i % 2 == 1)
        {
            cout << fixed << setprecision(2) << setw(8) << i << setw(7) << sortedNetIDbyID[i]
                << setw(7) << sortedMajorbyID[i] << setw(6) << sortedGPAbyID[i] << endl;
        }
        else
        {
            cout << fixed << setprecision(2) << setw(5) << i << setw(7) << sortedNetIDbyID[i]
                << setw(7) << sortedMajorbyID[i] << setw(6) << sortedGPAbyID[i];
        }
    }

    //loop prompting user to choose a menu option, and then executing chosen option
    while (choice != 3)
    {
        cout << "\n***************\nMenu of choices\n***************\n";
        cout << "1 - List top n students\n";
        cout << "2 - Search on a netID\n";
        cout << "3 - Quit\n";

        cin >> choice;

        if (choice == 1) //lists top n students
        {
            int n = 0;
            cout << "Enter n: ";
            cin >> n;

            //checks if n is higher than or lower than the array size
            if (size > n)
            {
                cout << "Top " << n << "students are:\n\n";
                while (n >= 0)
                {
                    cout << "netID: " << sortedNetIDbyGPA[n];
                    cout << ", major : " << sortedMajorbyGPA[n];
                    cout << ", GPA : " << sortedGPAbyGPA[n] << endl;
                    n--;
                }
            }
            else
            {
                cout << "Top " << size << " students are:\n\n";
                n = size - 1;
                while (n >= 0)
                {
                    cout << "netID: " << sortedNetIDbyGPA[n];
                    cout << ", major : " << sortedMajorbyGPA[n];
                    cout << ", GPA : " << sortedGPAbyGPA[n] << endl;
                    n--;
                }
            }
        }
        else if (choice == 2) //searches for student with matching netID and prints results
        {
            int ID = 0, index = 0, linearNIter = 0, binaryNIter = 0;
            cout << "Enter netID: ";
            cin >> ID;

            cout << "\nResult of linear search:\n------------------------\n";
            index = linearSearchID(netID, size, ID, linearNIter);
            
            if (index == -1)
            {
                cout << "Student not found\n";
                cout << "It took " << linearNIter << " iterations\n";
            }
            else
            {
                cout << fixed << setprecision(2) << "Student found at index " << index << ", GPA is " << GPA[index] << endl;
                cout << "It took " << linearNIter << " iterations\n";
            }

            cout << "\nResult of binary search:\n------------------------\n";
            index = binarySearchID(netID, size, ID, binaryNIter);

            if (index == -1)
            {
                cout << "Student not found\n";
                cout << "It took " << binaryNIter << " iterations\n";
            }
            else
            {
                cout << fixed << setprecision(2) << "Student found at index " << index << ", GPA is " << GPA[index] << endl;
                cout << "It took " << binaryNIter << " iterations\n";
            }
        }
    }
    
    cout << "Exiting\n";
    exit(EXIT_SUCCESS);
}


/* This function sorts array1 and maintains the parallelism
of array2, and array3
Whenever elements of array1 are swapped, the elements of array 2
and array3 at the same indices are also swapped
*/
void modifiedSortGPA(double array1[], int array2[], string array3[], int size)
{
    //Selection sort
    int minIndex;
    double minValue;
    for (int start = 0; start < (size - 1); start++)
    {
        minIndex = start;
        minValue = array1[start];
        for (int index = start + 1; index < size; index++)
        {
            if (array1[index] < minValue)
            {
                minValue = array1[index];
                minIndex = index;
            }
        }

        //Swapping first array
        double temp1 = array1[minIndex];
        array1[minIndex] = array1[start];
        array1[start] = temp1;

        //Swapping second array
        int temp2 = array2[minIndex];
        array2[minIndex] = array2[start];
        array2[start] = temp2;

        //Swapping third array
        string temp3 = array3[minIndex];
        array3[minIndex] = array3[start];
        array3[start] = temp3;
    }
}

/* This function sorts array2 and maintains the parallelism
of array1 and array3
Whenever elements of array2 are swapped, the elements of array 1
and array3 at the same indices are also swapped
*/
void modifiedSortID(int array2[], double array1[], string array3[], int size)
{
    //Selection sort
    int minIndex, minValue;
    for (int start = 0; start < (size - 1); start++)
    {
        minIndex = start;
        minValue = array2[start];
        for (int index = start + 1; index < size; index++)
        {
            if (array2[index] < minValue)
            {
                minValue = array2[index];
                minIndex = index;
            }
        }

        //Swapping first array
        int temp1 = array2[minIndex];
        array2[minIndex] = array2[start];
        array2[start] = temp1;

        //Swapping second array
        double temp2 = array1[minIndex];
        array1[minIndex] = array1[start];
        array1[start] = temp2;

        //Swapping third array
        string temp3 = array3[minIndex];
        array3[minIndex] = array3[start];
        array3[start] = temp3;
    }
}

/* This function implements linear search on an array. It takes the following arguments:
arr: the array, numElems: number of elements of array,
value: search value, and nIter. nIter is a reference variable used
to pass the number of iterations back to the calling function.
The function returns the index where the match is found, -1 if no
match is found
*/
int linearSearchID(int arr[], int numElems, int value, int& nIter)
{
    nIter = 0;
    int index = 0;

    while (index < numElems)
    {
        nIter++;
        if (arr[index] == value)
            return index;
        index++;
    }

    return -1;
}

/* This function implements binary search on an array. It takes the following arguments:
arr: the array, numElems: number of elements of array,
value: search value, and nIter. nIter is a reference variable used
to pass the number of iterations back to the calling function.
The function returns the index where the match is found, -1 if no
match is found
*/
int binarySearchID(int arr[], int numElems, int value, int& nIter)
{
    nIter = 0;
    int first = 0, last = numElems - 1, middle, position = -1;
    bool found = false;

    while (!found && first <= last)
    {
        middle = (first + last) / 2;
        if (arr[middle] == value)
        {
            found = true;
            position = middle;
        }
        else if (arr[middle] > value)
            last = middle - 1;
        else
            first = middle + 1;
        nIter++;
    }

    //checking if the student was found or not
    if (arr[position] == value)
        return position;
    else
        return -1;
}