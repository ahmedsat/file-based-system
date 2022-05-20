#include <iostream>
#include <string.h>
#include <fstream>
#include "Doctor.h"
#include "Patient.h"
using namespace std;

// function to clear the screen
void clearScreen()
{
  system("cls");
}

// entry point of the program
int main()
{
  // object declaration
  Patient patient;
  Doctor doctor;

  // message to inform user of the errors that may occur
  string message = "";

  // variable to store user input
  int choice;

  // view menu and get user input for choice of action
  do
  {
    clearScreen();
    // show message if any error occurs
    if (message != "")
    {
      cout << "==========================" << endl;
      cout << message << endl;
      cout << "==========================" << endl;
      message = "";
    }
    // display menu
    cout << "1.Doctors" << endl;
    cout << "2.Patients" << endl;
    cout << "0.Exit" << endl;
    cout << "Enter your choice: ";
    cin >> choice;
    switch (choice)
    {
    case 1:
      doctor.controller(); // call the controller function of doctor class
      break;
    case 2:
      patient.controller(); // call the controller function of patient class
      break;
    case 0:
      break;
    default:
      message = "Invalid choice";
      break;
    }
  } while (choice != 0);
  return 0;
}
