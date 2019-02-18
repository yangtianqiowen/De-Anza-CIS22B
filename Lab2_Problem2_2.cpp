/*
Tianqi Yang
Winter 2017
Lab 2
Problem 2.2
Description of problem:
Declear a class with type name: Car
Make the data in the class Car public
*/
#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

class Car
{
public:
    string reportingMark;
    int carNumber;
    string kind;
    bool loaded;
    string destination;
public:
        Car()
        {
            reportingMark = "None";
            carNumber = 0;
            kind = "None";
            loaded = false;
            destination = "None";
        }

        Car(string rMark, int cNumber, string knd, bool load, string dest)
        {
            reportingMark = rMark;
            carNumber = cNumber;
            kind = knd;
            loaded = load;
            destination = dest;
        }

        ~Car()
        {};

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

        Car* setUpCar(string rMark, int cNumber, string knd, bool load, string dest)
        {
            Car *c1 = new Car(rMark, cNumber, knd, load, dest);
            return c1;
        }
};

void input(string &rMark, int &cNumber, string &knd, bool &load, string &dest);
void output(Car *cPtr);

/********************** main ****************************/
int main()
{

    string rMark;
    int cNumber;
    string knd;
    bool load;
    string dest;

    input(rMark, cNumber, knd, load, dest);
    Car *cPtr;
    cPtr = cPtr->setUpCar(rMark, cNumber, knd, load, dest);
    output(cPtr);
    delete cPtr;
    return 0;
}
/********************** input ****************************
Read only the data from the user and call an additional
function named setUpCar which will put the data in the object.
Function accepts a Car class object pointer
*/
void input(string &rMark, int &cNumber, string &knd, bool &load, string &dest)
{
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
}
/********************* output *************************
Print the data in a neat format
Function accepts a Car class object pointer
*/
void output(Car *cPtr)
{
    cout << "\n * Display the Car data *\n";
    cout << setw(15) << left << "ReportingMark: " << cPtr->reportingMark;
    cout << setw(16) << left << "\nCarNumber: " << cPtr->carNumber;
    cout << setw(16) << left << "\nKind: " << cPtr->kind;
    cout << setw(16) << left <<"\nLoaded: ";
    cout << std::boolalpha << cPtr->loaded;
    cout << setw(16) << left << "\nDestination: " << cPtr->destination;
    cout << endl;
}

