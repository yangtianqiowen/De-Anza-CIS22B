/*
Tianqi Yang
Winter 2017
Lab 6
Problem 6.1
Description of problem:
Order of classes and functions:
1. Car class
2. FreightCar class inherited from Car class
3. PassengerCar class inherited from Car class
4. * Build a new class called Node
5. * StringOfCars class : Linked List
6. buildCar functions - in Global area
7. input function reads data from a file "cardata.txt" then call buildcar functions to build the cars
8. main : Create default string of cars and call input function. Test copy constructor stringOfCars2
that is a copy of stringOfCar1.
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

/**************** CAR CLASS DECLARATION ****************/
class Car
{
protected:
    string c_type;
    string c_order;
    string reportingMark;
    int carNumber;
    Kind kind;
    bool loaded;
    string destination;
public:
    Car();

    Car(const Car& obj);

    Car(const string &type, const string &order, const string &rMark,
        const int &cNumber, const string &knd, const bool &load, const string &dest);

    ~Car(){ };

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

    void output();
    void setUp(const string &type, const string &order, const string &rMark, const int &cNumber,
               const string &knd, const bool &load, const string &dest);
    Car & operator=(const Car & carB);
    friend bool operator == (const Car &left, const Car &right);

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

/**************** FREIGHTCAR CLASS DECLARATION (DERIVED) ****************/
class FreightCar : public Car
{
public:
    FreightCar() : Car()
    {   }

    FreightCar(const Car& obj) : Car(obj)
    {    }

    FreightCar(const string type, const string order, const string rMark, const int cNumber, const string knd, const bool load, const string dest)
                : Car(type, order, rMark, cNumber, knd, load, dest)
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

    PassengerCar(const string type, const string order, const string rMark, const int cNumber, const string knd, const bool load, const string dest)
                : Car(type, order, rMark, cNumber, knd, load, dest)
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

class StringOfCars;

/**************** NODE CLASS DECLARATION ****************/
class Node
{
private:
    Node *next;
    Car * data;
    Node()
    {
        next = NULL;
        data = NULL;
    }
public:
    friend class StringOfCars;
};

/**************** STRINGOFCARS CLASS ****************/
class StringOfCars
{
private:
    Node *head;
    Node *tail;
public:
    StringOfCars();
    StringOfCars(const StringOfCars &) ;
    ~StringOfCars(){};
    void push(Car &car);
    void output2();
};

/************* CAR MEMBER FUNCTION DEFINITIONS **************/
/******* #1 - Default constructor initializes the five values *******/
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
/********** Constructor #3 - accepts five constant reference parameters **********
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
It accepts five variable parameters as constant reference parameters
*/
void Car::setUp(const string &type, const string &order, const string &rMark, const int &cNumber,
               const string &knd, const bool &load, const string &dest)
{
    c_type = type;
    c_order = order;
    reportingMark = rMark;
    carNumber = cNumber;
    setKind(knd);
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

/*************** STRINGOFCARS MEMBER FUNCTION DEFINITIONS ****************/
/*************** StringOfCars Default Constructor ***************
Default constructor - Sets head and tail pointers to zero
*/
StringOfCars::StringOfCars()
{
    head = NULL;
    tail = NULL;
}
/*************** StringOfCars Copy Constructor **************
Copy Constructor sets head and tail pointers in the StringOfCars to zero
Loop while the currentNodePointer is not zero.
*/
StringOfCars::StringOfCars(const StringOfCars &obj)
{
    Node * currentNodePtr;
    currentNodePtr = obj.head;
    head = NULL;
    tail = NULL;
    if(obj.head)
    {
        while(currentNodePtr)
        {
            push(*(currentNodePtr->data));
            currentNodePtr = currentNodePtr->next;
        }
    }
}
/*************** StringOfCars output2 **************
output2 print heading for each car then uses Car output()
funtion to print data for each car
*/
void StringOfCars::output2()
{
    Node *currentNodePtr;
    if(!head)
        cout << "NO cars\n";
    else
        currentNodePtr = head;
    int count = 1;
    while(currentNodePtr)
    {
        cout << "Contents of Car Number: " << count++ << endl;
        currentNodePtr->data->output();
        currentNodePtr = currentNodePtr->next;
    }
}
/*************** StringOfCars Push **************
Push function adds a car to the string of cars
Use new to get space in the heap for a new Car
Use new to get space in the heap for a Node
*/
void StringOfCars::push(Car &car)
{
    Car * currentCarPtr;
    Node * currentNodePtr;
    currentCarPtr = new Car;
    currentNodePtr = new Node;

    currentCarPtr = &car;
    currentNodePtr->data = currentCarPtr;
    if(!head)
    {
        head = currentNodePtr;
        tail = currentNodePtr;
    }
    else
    {
        tail->next = currentNodePtr;
        tail = currentNodePtr;
    }
}


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
Read cars data from file "cardata61.txt".
Then call buildCar function to build the car.
*/
void input(StringOfCars &stringOfCars1)
{
    string type;
    string order;
    string rMark;
    int cNumber;
    string knd;
    bool load;
    string dest;
    ifstream inputFile;
    inputFile.open("cardata61.txt");
    if (!inputFile)
    {
        cerr << "Error opening file\n";
        exit(0);
    }

    while(inputFile.peek()!=EOF)
    {
        inputFile >> type >> order >> rMark >> cNumber >> knd ;
        inputFile >> boolalpha >> load;
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

    inputFile.close();
}

/******************** MAIN ********************/
int main()
{
    StringOfCars stringOfCars1;
    input(stringOfCars1);
    StringOfCars stringOfCars2(stringOfCars1);
    cout << "\n===== Display list of stringOfCars2 =====\n";
    stringOfCars2.output2();
    cout << endl;
    return 0;
}
