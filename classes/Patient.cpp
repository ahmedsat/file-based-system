#include <iostream>
#include <string>
#include <fstream>
#include <filesystem>
#include "../headers/Patient.h"

// Constructor
Patient::Patient()
{
  id = 0;
  name = "";
  age = 0;
  diagnoses = "";
  phone = "";
  email = "";
  address = "";
  message = "";
  PatientPath = "DB/Patients.txt";
}

void Patient::controller()
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
    cout << "1. Add Patient" << endl;
    cout << "2. Remove Patient" << endl;
    cout << "3. Edit Patient" << endl;
    cout << "4. Print Patient" << endl;
    cout << "5. Print All Patients" << endl;
    cout << "0. Exit" << endl;
    cout << "Enter your choice: ";
    cin >> choice; // get user input
    switch (choice)
    {
    case 1:
      addPatient(); // call the function to add patient
      break;
    case 2:
      removePatient(); // call the function to remove patient
      break;
    case 3:
      editPatient(); // call the function to edit patient
      break;
    case 4:
      printPatient(); // call the function to print patient
      break;
    case 5:
      printAllPatients(); // call the function to print all patients
      break;
    case 0:
      break;
    default:
      cout << "Invalid choice" << endl;
    }
  } while (choice != 0);
}

void Patient::addPatient()
{

  cout << message << endl;

  cout << "Enter Patient's ID: ";
  cin >> id;      // get patient's id
  if (cin.fail()) // check if the id is valid
  {
    cin.clear();                                 // clear the error flag
    cin.ignore(10000, '\n');                     // ignore the rest of the input
    message = "Invalid input, please try again"; // set the message
    return;
  }

  if (id <= 0) // if user entered a non-integer value show error message and return
  {

    message = "ID must be greater than 0";
    return;
  }

  // check if the id is already in use
  if (searchPatient(id)) // if id is already in use show error message and return
  {

    message = "ID already in use";
    return;
  }

  cin.ignore(); // ignore the rest of the input
  // get the rest of the information
  cout << "Enter Patient's Name: ";
  getline(cin, name);
  cout << "Enter Patient's Diagnoses: ";
  getline(cin, diagnoses);
  cout << "Enter Patient's age: ";
  cin >> age;
  if (cin.fail()) // check if the age is valid
  {
    cin.clear();                                 // clear the error flag
    cin.ignore(10000, '\n');                     // ignore the rest of the input
    message = "Invalid input, please try again"; // set the message
    return;
  }
  cin.ignore(); // ignore the rest of the input
  // get the rest of the information
  cout << "Enter Patient's Phone: ";
  getline(cin, phone);
  cout << "Enter Patient's Email: ";
  getline(cin, email);
  cout << "Enter Patient's Address: ";
  getline(cin, address);

  // save data to file
  // variable to store record
  string record = "#|" + to_string(id) + "|" + name + "|" + diagnoses + "|" + to_string(age) + "|" + phone + "|" + email + "|" + address + "|";

  fstream file;                               // create file object
  file.open(PatientPath, ios::in | ios::out); // open the file in read and write mode

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
  file.close();                     // close the file
  file.open(PatientPath, ios::app); // open the file in append mode
  file << record << endl;           // write the record to the end of file
  file.close();
}

void Patient::removePatient()
{
  int id;
  string line;
  bool found = false; // variable to check if the patient is found
  cout << "Enter Patient ID: ";
  cin >> id;      // get patient's id
  if (cin.fail()) // check if the id is valid
  {
    cin.clear();                                 // clear the error flag
    cin.ignore(10000, '\n');                     // ignore the rest of the input
                                                 // clear the screen
    message = "Invalid input, please try again"; // set the message
    return;
  }
  ifstream file;          // declare file stream object
  file.open(PatientPath); // open the file to read
  if (file.is_open())     // check if the file is opened successfully
  {
    ofstream temp;         // declare file stream object
    temp.open("temp.txt"); // open the file to write
    if (temp.is_open())    // check if the file is opened successfully
    {
      while (getline(file, line)) // read each line of the file and store it in line
      {
        string idCheck = line.substr(0, line.find("|")); // extract the id from the line
        if (idCheck != to_string(id))                    // check if the id is the same as the one entered
        {
          temp << line << endl; // write the line to the temp file
        }
        else
        {
          found = true; // set the found variable to true
        }
      }

      // move temp to doctor file
      temp.close();
      file.close();
      remove("Patients.txt");             // remove the original file
      rename("temp.txt", "Patients.txt"); // rename the temp file to doctor file
      if (found)                          // check if the patient is found
      {
        message = "Patient removed successfully"; // set the message
      }
      else
      {
        message = "Patient not found"; // set the message
      }
    }
    else
    {
      message = "error can't create temp file";
    }
  }
  else
  {
    message = "File not found";
  }
}

void Patient::editPatient()
{
  int id;
  string line;
  bool found = false; // variable to check if the patient is found
  cout << "Enter Patient ID: ";
  cin >> id;      // get patient's id
  if (cin.fail()) // check if the id is valid
  {
    cin.clear();                                 // clear the error flag
    cin.ignore(10000, '\n');                     // ignore the rest of the input
                                                 // clear the screen
    message = "Invalid input, please try again"; // set the message
    return;
  }
  ifstream file;          // declare file stream object
  file.open(PatientPath); // open the file to read
  if (file.is_open())     // check if the file is opened successfully
  {
    ofstream temp;         // declare file stream object
    temp.open("temp.txt"); // open the file to write
    if (temp.is_open())    // check if the file is opened successfully
    {
      while (getline(file, line)) // get each line of the file and store it in line
      {
        string idCheck = line.substr(0, line.find("|")); // extract the id from the line
        if (idCheck != to_string(id))                    // check if the id is the same as the one entered
        {
          temp << line << endl; // write the line to the temp file
        }
        else
        {
          // get the rest of the information
          cin.ignore();
          cout << "Enter Patient's Name: ";
          getline(cin, name);
          cout << "Enter Patient's Diagnoses: ";
          getline(cin, diagnoses);
          cout << "Enter Patient's Age: ";
          cin >> age;
          if (cin.fail())
          {
            cin.clear();
            cin.ignore(10000, '\n');

            message = "Invalid input, please try again";
            return;
          }
          cin.clear();
          cout << "Enter Patient's Phone: ";
          getline(cin, phone);
          cout << "Enter Patient's Email: ";
          getline(cin, email);
          cout << "Enter Patient's Address: ";
          getline(cin, address);
          temp
              << id
              << "|"
              << name
              << "|"
              << diagnoses
              << "|"
              << age
              << "|"
              << phone
              << "|"
              << email
              << "|" << address << endl;
          found = true;
        }
      }
      // move temp to doctor file
      temp.close();
      file.close();
      remove("Patients.txt");             // remove the original file
      rename("temp.txt", "Patients.txt"); // rename the temp file to doctor file
      if (found)                          // check if the patient is found
      {
        message = "Patient edited successfully"; // set the message
      }
      else
      {
        message = "Patient not found"; // set the message
      }
    }
    else
    {
      message = "error can't create temp file";
    }
  }
  else
  {
    message = "File not found";
  }
}

void Patient::printPatient()
{
  int id;
  string line;
  cout << "Enter Patient ID: ";
  cin >> id;      // get patient's id
  if (cin.fail()) // check if the id is valid
  {
    cin.clear();                                 // clear the error flag
    cin.ignore(10000, '\n');                     // ignore the rest of the input
                                                 // clear the screen
    message = "Invalid input, please try again"; // set the message
    return;
  }
  ifstream file;          // declare file stream object
  file.open(PatientPath); // open the file to read
  if (file.is_open())     // check if the file is opened successfully
  {
    message = "Patient not found"; // set default message
    while (getline(file, line))    // get each line of the file and store it in line
    {
      string idCheck = line.substr(0, line.find("|")); // extract the id from the line
      if (idCheck == to_string(id))                    // check if the id is the same as the one entered
      {
        message = line; // set the message
        break;
      }
    }
    file.close();
  }
  else
  {
    message = "File not found";
  }
}

void Patient::printAllPatients()
{
  string line;
  ifstream file;
  string output = "";     // string to store the output
  file.open(PatientPath); // open the file to read
  if (file.is_open())     // check if the file is opened successfully
  {
    while (getline(file, line)) // get each line of the file and store it in line
    {
      output += line + "\n"; // add the line to the output
    }
    file.close();
    message = output; // set the message
  }
  else
  {
    message = "File not found";
  }
}

bool Patient::searchPatient(int id)
{
  string line;
  ifstream file;          // declare a file to read
  file.open(PatientPath); // open the file to read
  if (!file)              // if file is not opened successfully
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
  message = "Patient not found";
  return false;
}