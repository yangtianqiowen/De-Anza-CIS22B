/*
Tianqi Yang
Winter 2017
Lab 4
Problem 4.2
Description of problem:
Order of functions:
1. main
2. Car: default constructor, copy constructor,
    constructor with five parameters, destructor, output, setup, operator=
3. StringOfCars: default constructor, copy constructor, destructor, output2, push, pop
4. friend operator==
5. input function reads cars data from a file "cardata.txt"
*/
#include <iostream>
#include <string>
#include <iomanip>
#include <cstdlib>
#include <fstream>
using namespace std;

/**************** CAR CLASS DECLARATION ****************/
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
    Car & operator=(const Car & carB);
    friend bool operator == (const Car &left, const Car &right);
};
/**************** STRINGOFCARS CLASS DECLARATION ****************/
class StringOfCars
{
private:
    Car *carPtr;
    static const int ARRAY_MAX_SIZE = 10;
    int size;
public:
    StringOfCars();
    StringOfCars(const StringOfCars &) ;
    ~StringOfCars();
    void push(Car car);
    void pop(Car &car);
    void output2();
};

void input(StringOfCars &string1);

/******************** MAIN ********************/
int main()
{
    cout << "***** TEST 1 *****\n\n";
    Car car1("SP", 34567, "box", true, " Salt Lake City");
    Car car2(car1);
    cout << "Contents of car2:\n";
    car2.output();
    StringOfCars string1;
    cout << "\n***** TEST 2 *****\n\n";
    cout << " ~~ STRING 1 - String of Cars ~~\n";
    input(string1);
    string1.output2();
    cout << "\n***** TEST 3 *****\n";
    Car car3;
    string1.pop(car3);
    cout << "\n ~~ CAR 3 ~~\n";
    cout << "Contents of car3:\n";
    car3.output();
    cout << " ~~ STRING 1 - String of Cars ~~\n";
    string1.output2();
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
    cout << setw(14) << left << "destination: " << destination << endl;
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
/******************** Car  operator=  ********************
operator= overload member function returns the left hand operator by reference
*/
Car & Car::operator=(const Car & carB)
{
  reportingMark = carB.reportingMark;
  carNumber     = carB.carNumber;
  kind          = carB.kind;
  loaded        = carB.loaded;
  destination   = carB.destination;

  return * this;
}

/*************** STRINGOFCARS MEMBER FUNCTION DEFINITIONS ****************/
/*************** StringOfCars Default Constructor ***************
Default constructor gets space for the array in the heap, sets the size to zero
*/
StringOfCars::StringOfCars()
{
    size = 0;
    carPtr = new Car[ARRAY_MAX_SIZE];
}
/*************** StringOfCars Copy Constructor **************
Copy Constructor gets new space in the heap for the array and
copies all the Car objects
*/
StringOfCars::StringOfCars(const StringOfCars &obj)
{
    carPtr = new Car[ARRAY_MAX_SIZE];
    for (int count = 0; count < ARRAY_MAX_SIZE; count++)
        *(carPtr + count) = *(obj.carPtr + count);
}
/*************** StringOfCars Destructor ***************
Destructor returns space to the heap
*/
StringOfCars::~StringOfCars()
{
    delete [] carPtr;
}
/*************** StringOfCars output2 **************
output2 print heading for each car then uses Car output()
funtion to print data for each car
*/
void StringOfCars::output2()
{
    if(size == 0)
    {
        cout << "NO cars\n";
        return;
    }

    for(int n = 0; n < size; n++)
    {
        cout << "Contents of Car Number: " << n+1 << endl;
        carPtr[n].output();
    }
}
/*************** StringOfCars Push **************
Push function adds a car to the string of cars
*/
void StringOfCars::push(Car car)
{
    if (size >=10)
        return;
    carPtr[size++] = car;
}
/*************** StringOfCars Pop **************
Pop function removes a car from the string of cars (LIFO)
*/
void StringOfCars::pop(Car &car)
{
    if (size < 0)
        return;
    car = carPtr[size - 1] ;
    size--;
}

/*************** Friend function ***************
operator== tests if reportingMark and carNumber are the same
*/
bool operator == (const Car &left, const Car &right)
{
    return left.reportingMark == right.reportingMark && left.carNumber == right.carNumber;
}
/******************** input ********************
void input function accepts reference parameter to a StringOfCars
Read cars data from file "cardata.txt". Function is not a member of Car class.
*/
void input(StringOfCars &string1)
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
        inputFile >> type >> rMark >> cNumber >> knd;
        inputFile >> std::boolalpha >> load;
        getline(inputFile, dest);
        Car temp(rMark, cNumber, knd, load, dest);
        string1.push(temp);
    }
    inputFile.close();
}

