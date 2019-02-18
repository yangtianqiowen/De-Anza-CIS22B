/*
Tianqi Yang
Winter 2017
Lab 5
Problem 5.1
Description of problem:
Program will use inheritance to create two new classes inherited from the class Car
Order of classes and functions:
1. Car class
2. *FreightCar class inherited from Car class
3. *PassengerCar class inherited from Car class
4. StringOfCars class
5. *buildCar functions in Global area
6. input reads cars data from a file "cardata.txt" then call buildcar functions to build the cars
7. main : call input function and does nothing else
*/
#include <iostream>
#include <string>
#include <iomanip>
#include <cstdlib>
#include <fstream>
using namespace std;
enum Kind {business, maintenance, other, box, tank, flat, otherFreight, chair, sleeper, otherPassenger};
const int NUMCARKIND = 10;
const string KIND_ARRAY[NUMCARKIND] = {"business", "maintenance", "other",
    "box", "tank", "flat", "otherFreight", "chair", "sleeper", "otherPassenger" };

class Car
{
protected:
    string reportingMark;
    int carNumber;
    Kind kind;
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

        void setKind(Kind knd)
        {   kind = knd;}

        void setLoaded(bool load)
        {   loaded = load;}

        void setDestination(string dest)
        {   destination = dest;}

        string getReportingMark() const
        {   return reportingMark;}

        int getCarNumber() const
        {   return carNumber;}

        Kind getKind() const
        {   return kind;}

        bool getLoaded() const
        {   return loaded;}

        string getDestination() const
        {   return destination;}

    void output();
    void setUp(const string &rMark, const int &cNumber, const string &knd, const bool &load, const string &dest);

    Car & operator=(const Car & carB);
    friend bool operator == (const Car &left, const Car &right);

    void setKind(const string &knd)
    {
        for(int i = business; i < other; i++)
        {
            if(KIND_ARRAY[i].compare(knd)==0)
            {
                kind = static_cast<Kind>(i);
                return;
            }
            else
               kind = other;
        }
    };
};

/**************** FREIGHTCAR CLASS DECLARATION (DERIVED) ****************/
class FreightCar : public Car
{
public:
    FreightCar() : Car()
    {   }

    FreightCar(const Car& obj) : Car(obj)
    {    }

    FreightCar(const string &rMark, const int &cNumber, const string &knd, const bool &load, const string &dest)
                : Car(rMark, cNumber, knd, load, dest)
    {  setKind(knd); }
    void setKind(const string &knd)
    {
        for(int i = box; i < otherFreight; i++)
        {
            if(KIND_ARRAY[i].compare(knd)==0)
            {
                kind = static_cast<Kind>(i);
                return;
            }
            else
               kind = otherFreight;
        }
    };
};

/**************** PASSENGERCAR CLASS DECLARATION (DERIVED) ****************/
class PassengerCar : public Car
{
public:
    PassengerCar(): Car()
    {    }

    PassengerCar(const Car& obj): Car(obj)
    {    }

    PassengerCar(const string &rMark, const int &cNumber, const string &knd, const bool &load, const string &dest)
                : Car(rMark, cNumber, knd, load, dest)
    {   setKind(knd); }
    void setKind(const string &knd)
    {
        for(int i = chair; i < otherPassenger; i++)
        {
            if(KIND_ARRAY[i].compare(knd)==0)
            {
                kind = static_cast<Kind>(i);
                return;
            }
            else
                kind = otherPassenger;
        }
    };
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

/************* CAR MEMBER FUNCTION DEFINITIONS **************/
/******* #1 - Default constructor initializes the five values *******/
Car::Car()
{
    reportingMark = "";
    carNumber = 0;
    setKind("");
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
    cout << setw(15) << left << "kind: " << KIND_ARRAY[kind] << endl;
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
    // Build function setKind. Pass a constant reference to the string
    setKind(knd);
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
/*-------------- END OF CAR MEMBER FUNCTIONS DEFINITION -------------*/

/*************** STRINGOFCARS MEMBER FUNCTION DEFINITIONS ****************/
/*************** StringOfCars Default Constructor ***************
Default constructor gets space for the array in the heap, sets the size to zero
*/
StringOfCars::StringOfCars()
{
    size = 0;   // Set size to zero
    // Dynamically allocate Car array
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
    // if the array is empty, prints NO cars
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
/*-------- END OF STRINGOFCARS MEMBER FUNCTIONS DEFINITION ---------*/

/*************** Friend function ***************
operator== tests if reportingMark and carNumber are the same
*/
bool operator == (const Car &left, const Car &right)
{
    return left.reportingMark == right.reportingMark && left.carNumber == right.carNumber;
}

/*************** GLOBAL FUNCTIONS - BUILD CARS **************/
/* buildCar function has the five parameters needed for a Car
   by using the Car constructor that has five parameters.
   Then call s the output member function for the Car
*/
void buildCar(const string &rMark, const int &cNumber, const string &knd, const bool &load, const string &dest)
{
    Car bc(rMark, cNumber, knd, load, dest);
    bc.output();
}
void buildFreightCar(const string &rMark, const int &cNumber, const string &knd, const bool &load, const string &dest)
{
    FreightCar bc(rMark, cNumber, knd, load, dest);
    bc.output();
}
void buildPassengerCar(const string &rMark, const int &cNumber, const string &knd, const bool &load, const string &dest)
{
    PassengerCar bc(rMark, cNumber, knd, load, dest);
    bc.output();
}
/******************** input ********************
input function is not a member of Car class.
Read cars data from file "cardata51.txt".
Then call buildCar function to build the car.
*/
void input()
{
    // Define local variables
    string type;        // Read Type field
    string order;       // Read Order field
    string rMark;       // Read ARR field - string of 5 or less upper characters
    int cNumber;        // an int
    string knd;         // could be box, tank, flat or other
    bool load;          // a bool
    string dest;        // a string with a destination or the word NONE

    int count = 1;      // count the cars
    // Declare object
    ifstream inputFile;
    inputFile.open("cardata51.txt");
    // If the open fails, send message to stderr and exit the program
    if (!inputFile)
    {
        std::cerr << "Error opening file\n";
        exit(0);
    }

    while(inputFile.peek()!=EOF)
    {
        // Read data from file
        inputFile >> type >> order >> rMark >> cNumber >> knd ;
        inputFile >> std::boolalpha >> load;
        getline(inputFile, dest);
        // Display - Build the cars
        cout << "Contents of Car Number: " << count++ << endl;
        cout << setw(15) << left << "Type: " << type << endl;
        cout << setw(15) << left << "order: " << order << "\n";
        if(type == "Car")
             buildCar(rMark, cNumber, knd, load, dest);
        else if(type == "FreightCar")
             buildFreightCar(rMark, cNumber, knd, load, dest);
        else if(type == "PassengerCar")
            buildPassengerCar(rMark, cNumber, knd, load, dest);
        else
            cout << "Error Type class\n";
    };
    // Cloae the file
    inputFile.close();
}

/******************** MAIN ********************/
int main()
{
    // Call input funtion and do nothing else
    input();
    cout << endl;
    return 0;
}
/*-------------- END OF MAIN ----------------*/

/* OUTPUT
Contents of Car Number: 1
Type:          Car
order:         car1
reportingMark: CN
carNumber:     819481
kind:          maintenance
loaded:        false
destination:   NONE

Contents of Car Number: 2
Type:          Car
order:         car2
reportingMark: SLSF
carNumber:     46871
kind:          business
loaded:        true
destination:   Memphis

Contents of Car Number: 3
Type:          Car
order:         car3
reportingMark: AOK
carNumber:     156
kind:          other
loaded:        true
destination:   McAlester

Contents of Car Number: 4
Type:          FreightCar
order:         car4
reportingMark: MKT
carNumber:     123456
kind:          tank
loaded:        false
destination:   Fort Worth

Contents of Car Number: 5
Type:          FreightCar
order:         car5
reportingMark: MP
carNumber:     98765
kind:          box
loaded:        true
destination:   Saint Louis

Contents of Car Number: 6
Type:          FreightCar
order:         car6
reportingMark: SP
carNumber:     567890
kind:          flat
loaded:        true
destination:   Chicago

Contents of Car Number: 7
Type:          FreightCar
order:         car7
reportingMark: GMO
carNumber:     7878
kind:          otherFreight
loaded:        true
destination:   Mobile

Contents of Car Number: 8
Type:          PassengerCar
order:         car8
reportingMark: KCS
carNumber:     7893
kind:          chair
loaded:        true
destination:   Kansas City

Contents of Car Number: 9
Type:          PassengerCar
order:         car9
reportingMark: PAPX
carNumber:     145
kind:          sleeper
loaded:        true
destination:   Tucson

Contents of Car Number: 10
Type:          PassengerCar
order:         car10
reportingMark: GN
carNumber:     744
kind:          otherPassenger
loaded:        false
destination:   NONE



Process returned 0 (0x0)   execution time : 0.141 s
Press any key to continue.
*/
