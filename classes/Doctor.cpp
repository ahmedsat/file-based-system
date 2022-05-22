#include <iostream>
#include <string>
#include <fstream>
#include <filesystem>

#include "../headers/Doctor.h"

using namespace std;

Doctor::Doctor()
{

  id = 0;
  name = "";
  specialization = "";
  experience = "";
  phone = "";
  email = "";
  address = "";
  message = "";
  DoctorPath = "DB/Doctors.txt";
}

void Doctor::controller()
{
  int choice; // variable to store user input

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
    cout << "1. Add Doctor" << endl;
    cout << "2. Remove Doctor" << endl;
    cout << "3. Edit Doctor" << endl;
    cout << "4. Print Doctor" << endl;
    cout << "5. Print All Doctors" << endl;
    cout << "0. Exit" << endl;
    cout << "Enter your choice: ";
    cin >> choice;
    switch (choice)
    {
    case 1:
      addDoctor(); // call the addDoctor function
      break;
    case 2:
      removeDoctor(); // call the removeDoctor function
      break;
    case 3:
      editDoctor(); // call the editDoctor function
      break;
    case 4:
      printDoctor(); // call the printDoctor function
      break;
    case 5:
      displayDoctors(); // call the printAllDoctors function
      break;
    case 0:
      break;
    default:
      cout << "Invalid choice" << endl;
    }
  } while (choice != 0);
}

void Doctor::addDoctor()
{

  // show message if any error occurs
  cout << message << endl;

  cout << "Enter Doctor's ID: ";
  cin >> id; // get doctor's id

  // check if user entered a valid id
  // if not, show error message
  if (cin.fail()) // if user entered a non-integer value show error message and return
  {
    cin.clear();             // clear the error flag
    cin.ignore(10000, '\n'); // ignore the rest of the input

    message = "Invalid input, please try again";
    return;
  }

  // check if id greater than 0
  // if not, show error message
  if (id <= 0) // if user entered a non-integer value show error message and return
  {

    message = "ID must be greater than 0";
    return;
  }

  // check if the id is already in use
  if (searchDoctor(id)) // if id is already in use show error message and return
  {

    message = "ID already in use";
    return;
  }

  cin.ignore(); // ignore the rest of the input
  // if the id is not in use, get the other details of the doctor
  cout << "Enter Doctor's Name: ";
  cin.ignore();
  getline(cin, name);
  cout << "Enter Doctor's Specialization: ";
  getline(cin, specialization);
  cout << "Enter Doctor's Experience: ";
  getline(cin, experience);
  cout << "Enter Doctor's Phone: ";
  getline(cin, phone);
  cout << "Enter Doctor's Email: ";
  getline(cin, email);
  cout << "Enter Doctor's Address: ";
  getline(cin, address);

  // save data to file
  // variable to store the record to be written to the file
  string record = "#|" + to_string(id) + "|" + name + "|" + specialization + "|" + experience + "|" + phone + "|" + email + "|" + address;

  fstream file;                              // create file object
  file.open(DoctorPath, ios::in | ios::out); // open the file in read and write mode

  string line; // variable to store each line of the file
  while (getline(file, line))
  {
    if (line[0] == '#') // if the line is not deleted, escape the line
    {
      continue;
    }
    if (line.size() >= record.size()) // if line size is greater than record size, write the record to the file
    {
      // fill the rest of the line with spaces
      while (line.size() > record.size())
      {
        record += ' ';
      }
      file.seekp(-line.size() - 1, ios::cur); // move the cursor to the start of the line
      file << record;                         // write the record to the file
      return;
    }
  }
  // if no line is having the same size as the record, write the record to the end of file
  file.close();                    // close the file
  file.open(DoctorPath, ios::app); // open the file in append mode
  file << record << endl;          // write the record to the end of file
  file.close();                    // close the file
}

void Doctor::removeDoctor()
{

  int id;
  string line; // variable to store each line of the file

  cout << "Enter Doctor ID: ";
  cin >> id;      // get doctor's id
  if (cin.fail()) // if user entered a non-integer value show error message and return
  {
    cin.clear();             // clear the error flag
    cin.ignore(10000, '\n'); // ignore the rest of the input

    message = "Invalid input, please try again";
    return;
  }

  fstream file;
  file.open(DoctorPath, ios::in | ios::out);
  if (!file)
  {
    message = "Error opening file";
    return;
  }

  message = "Doctor not found"; // set message to indicate that the doctor is not found
  while (getline(file, line))
  {
    if (line[0] != '#') // if the line is deleted, escape the line
    {
      continue;
    }
    string recordId = line.substr(2, line.find('|', 2) - 2); // get the id of the record

    if (recordId == to_string(id))
    {
      // move to start of line
      file.seekp(-line.size() - 1, ios::cur); // move the cursor to the start of the line
      // add new record
      file << "*";
      file.close();
      message = "Doctor removed successfully";
      return;
    }
  }
  file.close();
}

void Doctor::editDoctor()
{
  int id;
  string line;
  string newRecord;

  cout << "Enter Doctor ID: ";
  cin >> id;
  if (cin.fail()) // if user entered a non-integer value show error message and return
  {
    cin.clear();             // clear the error flag
    cin.ignore(10000, '\n'); // ignore the rest of the input

    message = "Invalid input, please try again";
    return;
  }

  // check if the id is already in use
  if (!searchDoctor(id)) // if id is already in use show error message and return
  {
    message = "Doctor not found";
    return;
  }

  // get the details of the doctor
  cout << "Enter Doctor's Name: ";
  cin.ignore(); // ignore the rest of the input
  getline(cin, name);
  cout << "Enter Doctor's Specialization: ";
  getline(cin, specialization);
  cout << "Enter Doctor's Experience: ";
  getline(cin, experience);
  cout << "Enter Doctor's Phone: ";
  getline(cin, phone);
  cout << "Enter Doctor's Email: ";
  getline(cin, email);
  cout << "Enter Doctor's Address: ";
  getline(cin, address);

  newRecord = "#|" + to_string(id) + "|" + name + "|" + specialization + "|" + experience + "|" + phone + "|" + email + "|" + address; // create new record
  fstream file;                                                                                                                        // create file object

  // remove the old record
  file.open(DoctorPath, ios::in | ios::out); // open the file in read and write mode
  while (getline(file, line))
  {
    string recordId = line.substr(2, line.find('|', 2) - 2);
    if (recordId == to_string(id))
    {
      // move to start of line
      file.seekp(-line.size() - 1, ios::cur);
      // add new record
      file << "*";
      file.close();
      break;
    }
  }
  file.close(); // close the file

  file.open(DoctorPath, ios::in | ios::out); // open the file in read and write mode

  while (getline(file, line))
  {

    if (line[0] == '#') // if the line is not deleted, escape the line
    {
      continue;
    }
    if (line.size() >= newRecord.size()) // if line size is greater than record size, write the record to the file
    {
      // fill the rest of the line with spaces
      while (line.size() > newRecord.size())
      {
        newRecord += ' ';
      }
      file.seekp(-line.size() - 1, ios::cur); // move the cursor to the start of the line
      file << newRecord;                      // write the record to the file
      message = "Doctor edited successfully\n" + newRecord;
      file.close();
      return;
    }
  }
  file.close();
  // if no line is having the same size as the record, write the record to the end of file

  // write the new record
  file.open(DoctorPath, ios::app); // open the file in append mode
  file << newRecord << endl;       // write the record to the end of file
  file.close();                    // close the file
  message = "Doctor edited successfully\n" + newRecord;
}

void Doctor::printDoctor()
{
  int id;

  cout << "Enter Doctor ID: ";
  cin >> id;      // get doctor's id
  if (cin.fail()) // if user entered a non-integer value show error message and return
  {
    cin.clear();             // clear the error flag
    cin.ignore(10000, '\n'); // ignore the rest of the input

    message = "Invalid input, please try again";
    return;
  }

  // check if ID greater than 0
  if (id <= 0)
  {
    message = "Invalid ID";
    return;
  }

  searchDoctor(id); // search for the doctor
}

bool Doctor::searchDoctor(int id)
{
  string line;
  ifstream file;         // declare a file to read
  file.open(DoctorPath); // open the file to read
  if (!file)             // if file is not opened successfully
  {
    message = "File not found";
    return false;
  }

  while (getline(file, line))
  {
    // if line is not deleted and not a random line
    if (line[0] == '#')
    {
      string recordId = line.substr(2, line.find('|', 2) - 2);

      if (recordId == to_string(id))
      {
        message = line;
        return true;
        file.close();
      }
    }
  }
  file.close();
  message = "Doctor not found";
  return false;
}

void Doctor::displayDoctors()
{
  string line;
  string output = "";
  fstream file;
  file.open(DoctorPath, ios::in);
  if (!file)
  {
    cout << "Error opening file." << endl;
    return;
  }
  while (getline(file, line))
  {
    // if line is not deleted and not a random line
    if (line[0] == '#')
    {
      output += line + "\n";
    }
  }
  message = output;
  file.close();
}