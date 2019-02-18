/*
Problem 5.2 - Chapter 15: Change StringOfCars class to array of pointers to objects.
Program will use inheritance to create two new classes inherited from the class Car
Order of classes and functions:
1. Car class
2. FreightCar class inherited from Car class
3. PassengerCar class inherited from Car class
4. StringOfCars class : contains an array of pointers to objects rather than an array of objects
5. buildCar functions - in Global area
6. input function reads data from a file "cardata.txt" then call buildcar functions to build the cars
7. main : call input function and does nothing else
*/
#include <iostream>
#include <string>
#include <iomanip>
#include <cstdlib>      // Needed for the exit function
#include <fstream>
using namespace std;

// Global area - Define an enum
enum Kind {business, maintenance, other, box, tank, flat, otherFreight, chair, sleeper, otherPassenger};
const int NUMCARKIND = 10;
// define an array of const string objects named KIND_ARRAY.
const string KIND_ARRAY[NUMCARKIND] = {"business", "maintenance", "other",
    "box", "tank", "flat", "otherFreight", "chair", "sleeper", "otherPassenger" };

/**************** CAR CLASS DECLARATION ****************/
class Car
{
protected:
    string c_type;
    string c_order;
    string reportingMark;   // a string of 5 or less upper case characters
    int carNumber;          // an int
    Kind kind;              // enumerated type
    bool loaded;            // a bool
    string destination;     // a string with a destination or the word NONE
public:
    // #1 - Default constructor initializes the five values
    Car();

    // #2 - Copy constructor
    Car(const Car& obj);

    // Constructor #3 - accepts five constant reference parameters. Call setUp function
    Car(const string &type, const string &order, const string &rMark,
        const int &cNumber, const string &knd, const bool &load, const string &dest);

    // Destructor does nothing
    ~Car(){ };

    // Mutator member function prototypes
        void setType(string type)
        {c_type = type;}

        void setOrder(string order)
        {c_order = order;}

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

    // Accessor member function prototypes
        string getType() const
        {return c_type;}

        string getOrder() const
        {return c_order;}

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

    // Member functions
    void output();  // Print the Car
    void setUp(const string &type, const string &order, const string &rMark, const int &cNumber,
               const string &knd, const bool &load, const string &dest);
    // operator= overload member function returns the left hand operator by reference
    Car & operator=(const Car & carB);
    // Friend function
    friend bool operator == (const Car &left, const Car &right);

    // Build function setKind. Pass a constant reference to the string
    virtual void setKind(const string &knd)
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
/*--------------- END OF CAR CLASS DECLARATION -----------------*/

/**************** FREIGHTCAR CLASS DECLARATION (DERIVED) ****************/
class FreightCar : public Car
{
public:
    // Constructor #1 - Default constructor. Freight inherited from Car class
    FreightCar() : Car()
    {   }

    // Constructor #2 - Copy constructor
    FreightCar(const Car& obj) : Car(obj)
    {    }

    // Constructor #3 - accepts five constant reference parameters
    FreightCar(const string type, const string order, const string rMark, const int cNumber, const string knd, const bool load, const string dest)
                : Car(type, order, rMark, cNumber, knd, load, dest)
    {  setKind(knd); }
    // Build function setKind. Pass a constant reference to the string
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
/*--------------- END OF FREIGHTCAR CLASS DECLARATION -----------------*/

/**************** PASSENGERCAR CLASS DECLARATION (DERIVED) ****************/
class PassengerCar : public Car
{
public:
    // Constructor #1 - Default constructor. PassengerCar inherited from Car class
    PassengerCar(): Car()
    {    }

    // Constructor #2 - Copy constructor
    PassengerCar(const Car& obj): Car(obj)
    {    }

    // Constructor #3 - accepts five constant reference parameters
    PassengerCar(const string type, const string order, const string rMark, const int cNumber, const string knd, const bool load, const string dest)
                : Car(type, order, rMark, cNumber, knd, load, dest)
    {   setKind(knd); }
    // Build function setKind. Pass a constant reference to the string
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
/*--------------- END OF PASSENGERCAR CLASS DECLARATION -----------------*/

/**************** STRINGOFCARS CLASS DECLARATION ****************/
class StringOfCars
{
protected:
    Car **carPtr;    // array of pointers to objects
    static const int ARRAY_MAX_SIZE = 10;
    int size;       // Current number of Cars in the array
public:
     // Default Constructor gets space for the array in the heap and sets the size to 0
    StringOfCars();
    // Copy constructor gets new space in the heap for the array and copies all Car objects
    StringOfCars(const StringOfCars &) ;
    // Destructor returns space to the heap
    ~StringOfCars();
    // push function adds a car to the string of cars
    void push(Car &car);
    // output2 function prints a heading for each car
    void output2();
};
/*--------------- END OF STRINGOFCARS CLASS DECLARATION -----------------*/

/************* CAR MEMBER FUNCTION DEFINITIONS **************/
/******* #1 - Default constructor initializes the seven values *******/
Car::Car()
{
    c_type = "";
    c_order = "";
    reportingMark = "";
    carNumber = 0;
    setKind("");
    loaded = false;
    destination = "NONE";
}
/********** #2 - Copy constructor **********/
Car::Car(const Car &obj)
{
    c_type = obj.c_type;
    c_order = obj.c_order;
    reportingMark = obj.reportingMark;
    carNumber = obj.carNumber;
    kind = obj.kind;
    loaded = obj.loaded;
    destination = obj.destination;
}
/********** Constructor #3 - accepts seven constant reference parameters **********
Constructor calls the setUp member function
*/
Car::Car(const string &type, const string &order, const string &rMark,
         const int &cNumber, const string &knd, const bool &load, const string &dest)
{
    setUp(type, order, rMark, cNumber, knd, load, dest);
}
/******************** output ********************
void output member function print the Car data in a neat format
*/
void Car::output()
{
    cout << setw(15) << left << "Type: " << c_type << endl;
    cout << setw(15) << left << "Order: " << c_order << endl;
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
It accepts seven variable parameters as constant reference parameters
*/
void Car::setUp(const string &type, const string &order, const string &rMark, const int &cNumber,
               const string &knd, const bool &load, const string &dest)
{
    c_type = type;
    c_order = order;
    reportingMark = rMark;
    carNumber = cNumber;
    setKind(knd);   // call function setKind
    loaded = load;
    destination = dest;
}
/******************** Car  operator=  ********************
operator= overload member function returns the left hand operator by reference
*/
Car & Car::operator=(const Car & carB)
{
  c_type        = carB.c_type;
  c_order       = carB.c_order;
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
    carPtr = new Car*[ARRAY_MAX_SIZE];
}
/*************** StringOfCars Copy Constructor **************
Copy Constructor gets new space in the heap for the array and
copies all the Car objects
*/
StringOfCars::StringOfCars(const StringOfCars &obj)
{
    carPtr = new Car*[ARRAY_MAX_SIZE];
    size = obj.size;
    for (int count = 0; count < ARRAY_MAX_SIZE; count++)
        carPtr[count] = obj.carPtr[count];
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
        carPtr[n]->output();
    }
}
/*************** StringOfCars Push **************
Push function adds a car to the string of cars
*/
void StringOfCars::push(Car &car)
{
    if (size >=10)
        return;
    carPtr[size++] = &car;
}
/*-------- END OF STRINGOFCARS MEMBER FUNCTIONS DEFINITION ---------*/

/*************** Friend function ***************
operator== tests if reportingMark and carNumber are the same
*/
bool operator == (const Car &left, const Car &right)
{
    return left.reportingMark == right.reportingMark && left.carNumber == right.carNumber;
}

/*************** GLOBAL AREA - BUILD CARS ***************/
void buildCar(Car * &carPtr, const string &type, const string &order, const string &rMark,
              const int &cNumber, const string &knd, const bool &load, const string &dest, StringOfCars &stringOfCars1)
{
    carPtr = new Car;
    carPtr -> setUp(type, order, rMark, cNumber, knd, load, dest);
    stringOfCars1.push(*carPtr);
}
void buildFreightCar(FreightCar * &carPtr, const string &type, const string &order, const string &rMark,
                     const int &cNumber, const string &knd, const bool &load, const string &dest, StringOfCars &stringOfCars1)
{
    carPtr = new FreightCar;
    carPtr-> setUp(type, order, rMark, cNumber, knd, load, dest);
    stringOfCars1.push(*carPtr);
}

void buildPassengerCar(PassengerCar * &carPtr, const string &type, const string &order, const string &rMark,
                       const int &cNumber, const string &knd, const bool &load, const string &dest, StringOfCars &stringOfCars1)
{
    carPtr = new PassengerCar;
    carPtr-> setUp(type, order, rMark, cNumber, knd, load, dest);
    stringOfCars1.push(*carPtr);
}
/******************** input ********************
input function is not a member of Car class.
Read cars data from file "cardata.txt".
Then call buildCar function to build the car.
*/
void input()
{
    StringOfCars stringOfCars1; // Create a default string of cars.
    // Define local variables
    string type;        // Read Type field
    string order;       // Read Order field
    string rMark;       // Read ARR field - string of 5 or less upper characters
    int cNumber;        // an int
    string knd;         // could be box, tank, flat or other
    bool load;          // a bool
    string dest;        // a string with a destination or the word NONE
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
        inputFile >> type >> order >> rMark >> cNumber >> knd ;
        inputFile >> std::boolalpha >> load;
        getline(inputFile, dest);
        if(type == "Car")
        {
             Car * carPtr;
             buildCar(carPtr, type, order, rMark, cNumber, knd, load, dest, stringOfCars1);
        }
        else if(type == "FreightCar")
        {
             FreightCar * carPtr;
             buildFreightCar(carPtr, type, order, rMark, cNumber, knd, load, dest, stringOfCars1);
        }
        else if(type == "PassengerCar")
        {
            PassengerCar * carPtr;
            buildPassengerCar(carPtr, type, order, rMark, cNumber, knd, load, dest, stringOfCars1);
        }
        else
            cout << "Error Type class\n";
    };

    StringOfCars stringOfCars2(stringOfCars1);  //Make stringOfCars2 a copy of stringOfCars1 in the stack
    cout << "\n===== Display list of stringOfCars2 =====\n";
    // Print stringOfCars2
    stringOfCars2.output2();
    // Close the file
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

===== Display list of stringOfCars2 =====
Contents of Car Number: 1
Type:          Car
Order:         car1
reportingMark: CN
carNumber:     819481
kind:          maintenance
loaded:        false
destination:   NONE

Contents of Car Number: 2
Type:          Car
Order:         car2
reportingMark: SLSF
carNumber:     46871
kind:          business
loaded:        true
destination:   Memphis

Contents of Car Number: 3
Type:          Car
Order:         car3
reportingMark: AOK
carNumber:     156
kind:          other
loaded:        true
destination:   McAlester

Contents of Car Number: 4
Type:          FreightCar
Order:         car4
reportingMark: MKT
carNumber:     123456
kind:          tank
loaded:        false
destination:   Fort Worth

Contents of Car Number: 5
Type:          FreightCar
Order:         car5
reportingMark: MP
carNumber:     98765
kind:          box
loaded:        true
destination:   Saint Louis

Contents of Car Number: 6
Type:          FreightCar
Order:         car6
reportingMark: SP
carNumber:     567890
kind:          flat
loaded:        true
destination:   Chicago

Contents of Car Number: 7
Type:          FreightCar
Order:         car7
reportingMark: GMO
carNumber:     7878
kind:          otherFreight
loaded:        true
destination:   Mobile

Contents of Car Number: 8
Type:          PassengerCar
Order:         car8
reportingMark: KCS
carNumber:     7893
kind:          chair
loaded:        true
destination:   Kansas City

Contents of Car Number: 9
Type:          PassengerCar
Order:         car9
reportingMark: PAPX
carNumber:     145
kind:          sleeper
loaded:        true
destination:   Tucson

Contents of Car Number: 10
Type:          PassengerCar
Order:         car10
reportingMark: GN
carNumber:     744
kind:          otherPassenger
loaded:        false
destination:   NONE

Process returned 0 (0x0)   execution time : 0.203 s
Press any key to continue.

*/
