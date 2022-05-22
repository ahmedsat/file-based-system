#include <iostream>
#include <string.h>
#include <fstream>
using namespace std;

class Patient
{
private:
  int id;
  int age;
  string name;
  string diagnoses;
  string phone;
  string email;
  string address;
  string message;
  string PatientPath;

public:
  // constructor to initialize the variables
  Patient();

  // function to control the flow of the program
  void controller();

  // function to add patient
  void addPatient();

  // function to remove patient
  void removePatient();

  // function to edit patient
  void editPatient();

  // function to display all patients
  void printPatient();

  // function to display all patients
  void printAllPatients();

  // function to search doctor
  bool searchPatient(int id);

  void clearScreen()
  {
    system("clear");
    system("cls");
  }
};
