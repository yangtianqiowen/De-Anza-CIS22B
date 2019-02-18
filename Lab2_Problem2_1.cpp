/*
Tianqi Yang
Winter 2017
Lab 2
Problem 2.1
Description of problem:
Declare a structure with a type name: Car
Create the following functions: main, input, output
*/
#include <iostream>
#include <string>
#include <iomanip>
using namespace std;
struct Car
{
    string reportingMark;
    int carNumber;
    string kind;
    bool loaded;
    string destination;
};


void input(Car *cPtr);
void output(Car *cPtr);

int main()
{
    Car *cPtr;
    cPtr = new Car;
    input(cPtr);
    output(cPtr);
    delete cPtr;
    return 0;
}
/************************ input ****************************
Read all the data from the user
After all the data has been read, put this data into the structure
Function accepts a structure pointer
*/
void input(Car *cPtr)
{
    string rMark;
    int cNumber;
    string knd;
    bool load;
    string dest;

    int len;


    cout << "Enter reportingMark: ";
    getline(cin, rMark);
    len = rMark.length();
    while (len > 5)
    {
        cout << "Invalid! Enter reportingMark with 5 or less upper case characters: ";
        cin >> rMark;
        len = rMark.length();
    }
    for (int i = 0; i < int (rMark.length());  i++)
        rMark[i] = toupper(rMark[i]);
    cout << "Enter carNumber: ";
    cin >> cNumber;
    cout << "Enter kind (box, tank, flat or other): ";
    cin >> knd;
    cout << "Enter 'true' for load or 'false' for noload:  ";
    cin >> std::boolalpha >> load;
    cin.ignore();
    if (load)
    {
        cout << "Enter destination: ";
        getline(cin, dest);
    }
    else
        dest = "NONE";
    cPtr->reportingMark = rMark;
    cPtr->carNumber = cNumber;
    cPtr->kind = knd;
    cPtr->loaded = load;
    cPtr->destination = dest;
}
/********************* output *************************
Print the data in a neat format
Function accepts a structure pointer
*/
void output(Car *cPtr)
{
    cout << "\n * Display the Car data *\n";
    cout << setw(15) << left << "ReportingMark: " << cPtr->reportingMark;
    cout << setw(16) << left <<"\nCarNumber: " << cPtr->carNumber;
    cout << setw(16) << left <<"\nKind: " << cPtr->kind;
    cout << setw(16) << left <<"\nLoaded: ";
    cout << std::boolalpha << cPtr->loaded;
    cout << setw(16) << left <<"\nDestination: " << cPtr->destination;
    cout << endl;
}

