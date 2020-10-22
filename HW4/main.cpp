/*
Author: Tyler Mooney
Date: February 20th, 2020
Professor: Khiem Le
Compiler: GNU GCC

Purpose: prompt the user for a file name, then acquire the records of students,
and then prompt the user to choose between seeing the top students above a specified rank,
search for a student, and to exit the program.

Notes:
I used most of the code from my Homework 1 assignment.
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
#include <fstream>
#include <iomanip>

using namespace std;

struct Student
{
    int netID;
    string major;
    double GPA;
};

//function prototypes
void modifiedSortGPA(Student[], int);
void modifiedSortID(Student[], int);
int linearSearchID(Student[], int, int, int&);
int binarySearchID(Student[], int, int, int&);

int main()
{
    //Variable and array initializations
    const int NUM_ELMTS = 18;
    string fileName;
    int size = 0, choice = 0;

    //original array of Student structures
    Student studArray[NUM_ELMTS];

    //array sorted by GPA
    Student studArraysortedbyGPA[NUM_ELMTS];

    //Array sorted by netID
    Student studArraysortedbyID[NUM_ELMTS];

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
        //temporary variable initializations
        int tempNetID = 0;
        string tempMajor = "";
        double tempGPA = 0;
        int i = 0;

        //read in information from the file into the proper arrays
        while (inFile >> tempNetID >> tempMajor >> tempGPA && i < NUM_ELMTS)
        {
            studArray[i].netID = tempNetID;
            studArray[i].major = tempMajor;
            studArray[i].GPA = tempGPA;
            studArraysortedbyGPA[i].netID = tempNetID;
            studArraysortedbyGPA[i].major = tempMajor;
            studArraysortedbyGPA[i].GPA = tempGPA;
            studArraysortedbyID[i].netID = tempNetID;
            studArraysortedbyID[i].major = tempMajor;
            studArraysortedbyID[i].GPA = tempGPA;
            i++;
        }
        size = i;
    }
    inFile.close();

    //sorts one set of arrays by GPA and the other set by ID
    modifiedSortGPA(studArraysortedbyGPA, size);
    modifiedSortID(studArraysortedbyID, size);

    //printing original arrays
    cout << "Original array:\n---------------\n";
    cout << "index  netID  major   GPA   index  netID  major   GPA\n";
    for (int i = 0; i < size; i++)
    {
        //checks if this is the second iteration in a row or not
        if (i % 2 == 1)
        {
            cout << fixed << setprecision(2) << setw(8) << i << setw(7) << studArray[i].netID
                << setw(7) << studArray[i].major << setw(6) << studArray[i].GPA << endl;
        }
        else
        {
            cout << fixed << setprecision(2) << setw(5) << i << setw(7) << studArray[i].netID
                << setw(7) << studArray[i].major << setw(6) << studArray[i].GPA;
        }
        //prints out a line if the last entry is in the first row
        if(i == (size - 1))
            cout << endl;
    }

    //printing arrays sorted by GPA
    cout << "\nArray sorted by GPA:\n--------------------\n";
    cout << "index  netID  major   GPA   index  netID  major   GPA\n";
    for (int i = 0; i < size; i++)
    {
        //checks if this is the second iteration in a row or not
        if (i % 2 == 1)
        {
            cout << fixed << setprecision(2) << setw(8) << i << setw(7) << studArraysortedbyGPA[i].netID
                << setw(7) << studArraysortedbyGPA[i].major << setw(6) << studArraysortedbyGPA[i].GPA << endl;
        }
        else
        {
            cout << fixed << setprecision(2) << setw(5) << i << setw(7) << studArraysortedbyGPA[i].netID
                << setw(7) << studArraysortedbyGPA[i].major << setw(6) << studArraysortedbyGPA[i].GPA;
        }

        //prints out a line if the last entry is in the first row
        if(i == (size - 1))
            cout << endl;
    }

    //printing arrays sorted by netID
    cout << "\nArray sorted by netID:\n----------------------\n";
    cout << "index  netID  major   GPA   index  netID  major   GPA\n";
    for (int i = 0; i < size; i++)
    {
        //checks if this is the second iteration in a row or not
        if (i % 2 == 1)
        {
            cout << fixed << setprecision(2) << setw(8) << i << setw(7) << studArraysortedbyID[i].netID
                << setw(7) << studArraysortedbyID[i].major << setw(6) << studArraysortedbyID[i].GPA << endl;
        }
        else
        {
            cout << fixed << setprecision(2) << setw(5) << i << setw(7) << studArraysortedbyID[i].netID
                << setw(7) << studArraysortedbyID[i].major << setw(6) << studArraysortedbyID[i].GPA;
        }

        //prints out a line if the last entry is in the first row
        if(i == (size - 1))
            cout << endl;
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
                    cout << "netID: " << studArraysortedbyGPA[n].netID;
                    cout << ", major : " << studArraysortedbyGPA[n].major;
                    cout << ", GPA : " << studArraysortedbyGPA[n].GPA << endl;
                    n--;
                }
            }
            else
            {
                cout << "Top " << size << " students are:\n\n";
                n = size - 1;
                while (n >= 0)
                {
                    cout << "netID: " << studArraysortedbyGPA[n].netID;
                    cout << ", major : " << studArraysortedbyGPA[n].major;
                    cout << ", GPA : " << studArraysortedbyGPA[n].GPA << endl;
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
            index = linearSearchID(studArray, size, ID, linearNIter);

            if (index == -1)
            {
                cout << "Student not found\n";
                cout << "It took " << linearNIter << " iterations\n";
            }
            else
            {
                cout << fixed << setprecision(2) << "Student found at index " << index << ", major is "
                     << studArray[index].major << ", GPA is " << studArray[index].GPA << endl;
                cout << "It took " << linearNIter << " iterations\n";
            }

            cout << "\nResult of binary search:\n------------------------\n";
            index = binarySearchID(studArray, size, ID, binaryNIter);

            if (index == -1)
            {
                cout << "Student not found\n";
                cout << "It took " << binaryNIter << " iterations\n";
            }
            else
            {
                cout << fixed << setprecision(2) << "Student found at index " << index << ", major is "
                     << studArray[index].major << ", GPA is " << studArray[index].GPA << endl;
                cout << "It took " << binaryNIter << " iterations\n";
            }
        }
    }

    cout << "Exiting\n";
    exit(EXIT_SUCCESS);
}

// This function sorts array1 by GPA
void modifiedSortGPA(Student array1[], int size)
{
    //Selection sort
    int minIndex;
    double minValue;
    for (int start = 0; start < (size - 1); start++)
    {
        minIndex = start;
        minValue = array1[start].GPA;
        for (int index = start + 1; index < size; index++)
        {
            if (array1[index].GPA < minValue)
            {
                minValue = array1[index].GPA;
                minIndex = index;
            }
        }

        //Swapping GPA
        double temp1 = array1[minIndex].GPA;
        array1[minIndex].GPA = array1[start].GPA;
        array1[start].GPA = temp1;

        //Swapping netID
        int temp2 = array1[minIndex].netID;
        array1[minIndex].netID = array1[start].netID;
        array1[start].netID = temp2;

        //Swapping Major
        string temp3 = array1[minIndex].major;
        array1[minIndex].major = array1[start].major;
        array1[start].major = temp3;
    }
}

// This function sorts array2 by netID
void modifiedSortID(Student array2[], int size)
{
    //Selection sort
    int minIndex, minValue;
    for (int start = 0; start < (size - 1); start++)
    {
        minIndex = start;
        minValue = array2[start].netID;
        for (int index = start + 1; index < size; index++)
        {
            if (array2[index].netID < minValue)
            {
                minValue = array2[index].netID;
                minIndex = index;
            }
        }

        //Swapping netID
        int temp1 = array2[minIndex].netID;
        array2[minIndex].netID = array2[start].netID;
        array2[start].netID = temp1;

        //Swapping GPA
        double temp2 = array2[minIndex].GPA;
        array2[minIndex].GPA = array2[start].GPA;
        array2[start].GPA = temp2;

        //Swapping major
        string temp3 = array2[minIndex].major;
        array2[minIndex].major = array2[start].major;
        array2[start].major = temp3;
    }
}

/* This function implements linear search on an array. It takes the following arguments:
arr: the array, numElems: number of elements of array,
value: search value, and nIter. nIter is a reference variable used
to pass the number of iterations back to the calling function.
The function returns the index where the match is found, -1 if no
match is found
*/
int linearSearchID(Student arr[], int numElems, int value, int& nIter)
{
    nIter = 0;
    int index = 0;

    while (index < numElems)
    {
        nIter++;
        if (arr[index].netID == value)
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
int binarySearchID(Student arr[], int numElems, int value, int& nIter)
{
    nIter = 0;
    int first = 0, last = numElems - 1, middle, position = -1;
    bool found = false;

    while (!found && first <= last)
    {
        middle = (first + last) / 2;
        if (arr[middle].netID == value)
        {
            found = true;
            position = middle;
        }
        else if (arr[middle].netID > value)
            last = middle - 1;
        else
            first = middle + 1;
        nIter++;
    }

    //checking if the student was found or not
    if (arr[position].netID == value)
        return position;
    else
        return -1;
}
