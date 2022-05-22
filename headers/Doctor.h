#include <iostream>
#include <string>
#include <fstream>
using namespace std;

class Doctor
{
private:
  int id;
  string name;
  string specialization;
  string experience;
  string phone;
  string email;
  string address;
  string message;
  string DoctorPath;

public:
  // constructor to initialize the variables
  Doctor();

  // function to control the flow of the program
  void controller();

  // function to add doctor
  void addDoctor();

  // function to remove doctor
  void removeDoctor();

  // function to edit doctor
  void editDoctor();

  // function to search doctor
  bool searchDoctor(int id);

  // function find doctor
  void printDoctor();

  // function to display all doctors
  void displayDoctors();

  void clearScreen()
  {
    system("clear");
    system("cls");
  }
};