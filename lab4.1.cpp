/*
Tianqi Yang
Winter 2017
Lab 4
Problem 4.1
Description of problem:
1.main: call input function which read cars data from a file "cardata.txt"
2. Car: default constructor, copy constructor,
        constructor with five parameters, destructor, output, setup,
3. friend operator== with Car parameters
4. input: not a member function
*/
#include <iostream>
#include <string>
#include <iomanip>
#include <cstdlib>
#include <fstream>
using namespace std;
class Car
{
private:
    string reportingMark;
    int carNumber;
    string kind;
    bool loaded;
    string destination;
public:
    Car();
    Car(const Car& obj);
    Car(const string &rMark, const int &cNumber, const string &knd, const bool &load, const string &dest);
    ~Car(){ };

        void setReportingMark(string rMark)
        {   reportingMark = rMark;}

        void setCarNumber(int cNumber)
        {   carNumber = cNumber;}

        void setKind(string knd)
        {   kind = knd;}

        void setLoaded(bool load)
        {   loaded = load;}

        void setDestination(string dest)
        {   destination = dest;}

        string getReportingMark() const
        {   return reportingMark;}

        int getCarNumber() const
        {   return carNumber;}

        string getKind() const
        {   return kind;}

        bool getLoaded() const
        {   return loaded;}

        string getDestination() const
        {   return destination;}

    void output();
    void setUp(const string &rMark, const int &cNumber, const string &knd, const bool &load, const string &dest);
    friend bool operator == (const Car &left, const Car &right);
};

void input();

int main()
{
    input();
    return 0;
}
/************* CAR MEMBER FUNCTION DEFINITIONS **************/
/******* #1 - Default constructor initializes the five values *******/
Car::Car()
{
    reportingMark = "";
    carNumber = 0;
    kind = "other";
    loaded = false;
    destination = "NONE";
}
/********** #2 - Copy constructor **********/
Car::Car(const Car &obj)
{
    reportingMark = obj.reportingMark;
    carNumber = obj.carNumber;
    kind = obj.kind;
    loaded = obj.loaded;
    destination = obj.destination;
}
/********** Constructor #3 - accepts five constant reference parameters **********
Constructor calls the setUp member function
*/
Car::Car(const string &rMark, const int &cNumber, const string &knd, const bool &load, const string &dest)
{
    setUp(rMark, cNumber, knd, load, dest);
}
/******************** output ********************
void output member function print the Car data in a neat format
*/
void Car::output()
{
    cout << setw(15) << left << "reportingMark: " << reportingMark << endl;
    cout << setw(15) << left << "carNumber: " << carNumber << endl;
    cout << setw(15) << left << "kind: " << kind << endl;
    cout << setw(15) << left << "loaded: ";
    if (loaded)
        cout << "true";
    else
        cout << "false";
    cout << endl;
    cout << setw(14) << left << "destination: " << destination;
    cout << endl;
}
/******************** setUp ********************
void setUp function sets the data in the object.
It accepts five variable parameters as constant reference parameters
*/
void Car::setUp(const string &rMark, const int &cNumber, const string &knd, const bool &load, const string &dest)
{
    reportingMark = rMark;
    carNumber = cNumber;
    kind = knd;
    loaded = load;
    destination = dest;
}
/*************** Friend function ***************
operator== tests if reportingMark and carNumber are the same
*/
bool operator == (const Car &left, const Car &right)
{
    return left.reportingMark == right.reportingMark && left.carNumber == right.carNumber;
}
/******************** input ********************
void input function read cars data from file "cardata.txt"
Function is not a member of Car class. Call output to print the Car
*/
void input()
{

    string type;
    string rMark;
    int cNumber;
    string knd;
    bool load;
    string dest;
    int count = 0;
    ifstream inputFile;
    inputFile.open("cardata.txt");
    if(!inputFile)
    {
        std::cerr << "Error opening the file" << endl;
        exit(0);
    }

    while (inputFile.peek()!= EOF)
    {
        inputFile >> type >> rMark>> cNumber >> knd;
        inputFile >> std::boolalpha >> load;
        getline(inputFile, dest);

        Car temp(rMark, cNumber, knd, load, dest);
        cout << "Contents of Car" << ++count << ":" << endl;
        temp.output();
        cout << endl;
    }
    inputFile.close();
}

/* OUTPUT RESULT
Contents of Car1:
reportingMark: CN
carNumber:     819481
kind:          maintenance
loaded:        false
destination:   NONE

Contents of Car2:
reportingMark: SLSF
carNumber:     46871
kind:          business
loaded:        true
destination:   Memphis

Contents of Car3:
reportingMark: AOK
carNumber:     156
kind:          tender
loaded:        true
destination:   McAlester


Process returned 0 (0x0)   execution time : 0.078 s
Press any key to continue.

*/
