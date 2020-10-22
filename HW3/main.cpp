/*
Author: Tyler Mooney
Date: February 13th, 2020
Professor: Khiem Le
Compiler: GNU GCC

Purpose: Program will read from a file containing grocery product records,
and will check the input validation of these records

Notes:
Requirements for a valid data file:
    - Has exactly five items on the line
    - First item is a PLU (must be 4 letters long and have only letters or digits)
    - Second item is a product name (only valid if and only if first character is a letter)
    - Third item is sales type (Must only be 1 char, which can only be 0 or 1)
    - Fourth item is unit price (only digits, up to one dot, if dot: have only 2 digits after)
    - Fifth item is inventory level (valid if and only if it contains only digits)
Each item is separated into "tokens"
Use getline(inFile, stringRead) to read line by line
Detect end of file when getline returns an empty string
All messages must end with a new line
Functions:
    main: reads in the
    tokenize: takes a string and takes out each individual token from said string
    isValidPrice: returns true if the string is a valid price
    isValidPLU: returns true if the string is a valid PLU
    isValidName: returns true if the string is a valid Name
    isValidType: returns true if the string is a valid Sales Type
    isValidInventory: returns true if the string is a valid Inventory Level
*/

#include <iostream>
#include <cstring>
#include <cctype>
#include <fstream>

using namespace std;

//function prototypes
string tokenize(string &);
bool isValidPrice(string);
bool isValidPLU(string);
bool isValidName(string);
bool isValidType(string);
bool isValidInventory(string);

//Main function that reads in files
int main()
{
    //Variable and structure initializations
    string fileName, stringRead, token;

    //Prompt user for file name and print out header
    cout << "Enter input file:";
    getline(cin, fileName);
    cout << "\nChecking " << fileName << "\n---------";

    //printing out the remaining -s
    for(unsigned int i = 0; i < fileName.length(); i++)
        cout << '-';
    cout << endl << endl;

    //open file and check if it can open
    ifstream inFile;
    inFile.open(fileName);

    if (inFile.fail())
    {
        cout << "Could not open file\nExiting" << endl;
        inFile.close();
        exit(EXIT_FAILURE);
    }

    //populating a string with the current line
    //if the parameter for the first while doesn't work, try a if with a break
    while(getline(inFile, stringRead))
    {
        //variable initialization
        int counter = 1;
        bool isValid = false;

        //creating the tokens used, and checking if they're valid
        while(stringRead.length() != 0)
        {
            if(counter == 1)
            {
                token = tokenize(stringRead);
                isValid = isValidPLU(token);

                //checks if token is invalid, if so print out error and exit program
                if(!isValid)
                {
                    cout << "Token #1 is " << token << ", PLU is invalid\n\n"
                         << "######## " << fileName << " has invalid content ########\n";
                    inFile.close();
                    exit(EXIT_FAILURE);
                }
                cout << "Token #1 is " << token << ", PLU is valid\n";
            }
            else if(counter == 2)
            {
                token = tokenize(stringRead);
                isValid = isValidName(token);

                //checks if token is invalid, if so print out error and exit program
                if(!isValid)
                {
                    cout << "Token #2 is " << token << ", Product name is invalid\n\n"
                         << "######## " << fileName << " has invalid content ########\n";
                    inFile.close();
                    exit(EXIT_FAILURE);
                }
                cout << "Token #2 is " << token << ", Product name is valid\n";
            }
            else if(counter == 3)
            {
                token = tokenize(stringRead);
                isValid = isValidType(token);

                //checks if token is invalid, if so print out error and exit program
                if(!isValid)
                {
                    cout << "Token #3 is " << token << ", Sales type is invalid\n\n"
                         << "######## " << fileName << " has invalid content ########\n";
                    inFile.close();
                    exit(EXIT_FAILURE);
                }
                cout << "Token #3 is " << token << ", Sales type is valid\n";
            }
            else if(counter == 4)
            {
                token = tokenize(stringRead);
                isValid = isValidPrice(token);

                //checks if token is invalid, if so print out error and exit program
                if(!isValid)
                {
                    cout << "Token #4 is " << token << ", Price is invalid\n\n"
                         << "######## " << fileName << " has invalid content ########\n";
                    inFile.close();
                    exit(EXIT_FAILURE);
                }
                cout << "Token #4 is " << token << ", Price is valid\n";
            }
            else if (counter == 5)
            {
                token = tokenize(stringRead);

                //checking to make sure the token length isn't empty
                if(token.length() > 0)
                {
                    isValid = isValidInventory(token);

                    //checks if token is invalid, if so print out error and exit program
                    if(!isValid)
                    {
                        cout << "Token #5 is " << token << ", Inventory is invalid\n\n"
                             << "######## " << fileName << " has invalid content ########\n";
                        inFile.close();
                        exit(EXIT_FAILURE);
                    }
                    cout << "Token #5 is " << token << ", Inventory is valid\n";
                }
                else
                {
                    //there were too little token entries,printing out error and exiting program
                    cout << "Inventory is invalid, record has missing items\n\n"
                    << "######## " << fileName << " has invalid content ########\n";
                    inFile.close();
                    exit(EXIT_FAILURE);
                }
            }
            //checking if item has too many entries,if so print out error and exit program
            else if (counter >= 6)
            {
                token = tokenize(stringRead);

                //checks to make sure that this remaining characters aren't just whitespace
                if(token.length() > 0)
                {
                    cout << "Token #" << counter << " is " << token
                         << ", Too many items in record\n\n" << "######## " << fileName
                         << " has invalid content ########\n";
                    inFile.close();
                    exit(EXIT_FAILURE);
                }
            }
            counter++;
        }

        //print line for a successful run through of one line
        cout << endl;
    }

    //print out successful run through message, close file, and exit program
    cout << "######## " << fileName << " has valid content ########\n";
    inFile.close();
    exit(EXIT_SUCCESS);
}

//Takes a string and takes out an individual token within
//Removes whitespace and deletes used token
string tokenize(string & s)
{
    //variable initialization
    bool isToken = false, isDone = false;
    int n = 0;
    int start = 0, stop = 0;
    string token = "";

    while(static_cast<unsigned int>(n) <= s.length() && !isDone)
    {
        //if the char isn't a delimiter, recognizes the start of a token
        if(!isToken)
        {
            if(!isspace(s[n]))
            {
                isToken = true;
                start = n;
            }
            //removing any leading delimiters, and decreasing the increment
            if(isspace(s[n]))
            {
                s.erase(0,1);
                n--;
            }
        }

        //if the char is a delimiter after the start of a token,
        //The loop ends and the end point is recorded
        if(isToken)
            if(isspace(s[n]) || static_cast<unsigned int>(n) == s.length())
            {
                isDone = true;
                stop = n;
            }
        n++;
    }

    //assign the return string variable with the found token
    token = s.substr(start, stop);

    //erasing the any leading delimiters and used token chars
    s.erase(0, stop);

    return token;
}

// Returns true if the string is a valid price, false otherwise
bool isValidPrice(string price)
{
    //variable initialization
    bool isDot = false;
    int counter = 0;

    for(unsigned int i = 0; i < price.length(); i++)
    {
        //Checking if string only has digits and one dot
        if(!isdigit(price[i]) && price[i] != '.')
            return false;

        //If a dot appears counter begins
        if(price[i] == '.')
        {
            isDot = true;
            //checks to make sure this isn't a second dot
            if(counter > 0)
                return false;
        }

        //checks to make sure there is no more than 2 digits past the dot
        if(counter > 2)
            return false;

        if(isDot)
            counter++;
    }
    return true;
}

// Returns true if the string is a valid PLU, false otherwise
bool isValidPLU(string PLU)
{
    //checks if the PLU is exactly 4 characters long
    if(PLU.length() > 4 || PLU.length() < 4)
        return false;

    //checks if PLU only has letters or numbers
    for(unsigned int i = 0; i < PLU.length(); i++)
        if(!isalnum(PLU[i]))
            return false;

    //returns true if all test cases are passed
    return true;
}

// Returns true if the string is a valid Name, false otherwise
bool isValidName(string name)
{
    //checks if the first character is not a letter
    if(!isalpha(name[0]))
        return false;

    return true;
}

// Returns true if the string is a valid Sales Type, false otherwise
bool isValidType(string type)
{
    //checks if the string is not only 0 or 1
    if(type != "0" && type != "1")
        return false;

    return true;
}

// Returns true if the string is a valid Inventory Level, false otherwise
bool isValidInventory(string inventory)
{
    for(unsigned int i = 0; i < inventory.length(); i++)
        if(!isdigit(inventory[i]))
            return false;

    return true;
}
