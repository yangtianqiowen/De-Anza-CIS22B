/*
Tianqi Yang
Winter 2017
Lab 3
Problem 3.1
Description of problem:
Declare a class with a type name: Car. Data : private
output, setup : member functions of the class Car : public
input function : not a member function
main function : define five variables, pass to the input function
                define a Car object, call setUp and output functions
*/
#include <iostream>
#include <string>
#include <iomanip>
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

    void output();
    void setUp(const string &rMark, const int &cNumber, const string &knd, const bool &load, const string &dest);
};

void input(string &rMark, int &cNumber, string &knd, bool &load, string &dest);

/******************** MAIN ********************/
int main()
{
    string rMark;
    int cNumber;
    string knd;
    bool load;
    string dest;
    input(rMark, cNumber, knd, load, dest);

    Car car1;
    car1.setUp(rMark, cNumber, knd, load, dest);
    cout << "\nContents of car1:\n";
    car1.output();

    return 0;
}
/******************** output ********************
void output member function print the data in a neat format
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
    cout << setw(15) << left << "destination: " << destination;
    cout << endl;
}
/******************** setUp ********************
void setUp member sp
sp      spfunction sets the data in the object.
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
/******************** input ********************
void input function read only the data from the user
It accepts five reference parameters corresponding to five fields in the class.
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

