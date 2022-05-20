#include <iostream>
#include <string.h>
#include <fstream>
using namespace std;
string PatientPath = "Patients.txt"; // path of the file to store patients

// function to clear the screen
void clearScreen()
{
  system("cls");
}

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

public:
  // constructor to initialize the variables
  Patient()
  {
    id = 0;
    name = "";
    age = 0;
    diagnoses = "";
    phone = "";
    email = "";
    address = "";
    message = "";
  }

  // function to control the flow of the program
  void controller()
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

  // function to add patient
  void addPatient()
  {

    clearScreen();
    cout << message << endl;
    cout << "Enter Patient's ID: ";
    cin >> id;      // get patient's id
    if (cin.fail()) // check if the id is valid
    {
      cin.clear();                                 // clear the error flag
      cin.ignore(10000, '\n');                     // ignore the rest of the input
      clearScreen();                               // clear the screen
      message = "Invalid input, please try again"; // set the message
      return;
    }
    ifstream fin(PatientPath); // open the file to read
    if (fin.is_open())         // check if the file is opened successfully
    {
      string line;               // variable to store each line of the file
      while (getline(fin, line)) // read each line of the file
      {
        line = line.substr(0, line.find("|")); // extract the id from the line
        if (line == to_string(id))             // check if the id is already in the file
        {
          message = "Patient with this ID already exists"; // set the message
          return;
        }
      }
      fin.close();
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
      clearScreen();                               // clear the screen
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
    ofstream fout(PatientPath, ios::app); // open the file to write
    if (fout.is_open())                   // check if the file is opened successfully
    {
      // write the data to the file
      fout
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
          << "|"
          << address
          << endl;
      fout.close();
      message = "Patient added successfully"; // set the message
    }
    else
    {
      message = "Error adding patient";
    }
  }

  // function to remove patient
  void removePatient()
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
      clearScreen();                               // clear the screen
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

  // function to edit patient
  void editPatient()
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
      clearScreen();                               // clear the screen
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
              clearScreen();
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

  // function to display all patients
  void printPatient()
  {
    int id;
    string line;
    cout << "Enter Patient ID: ";
    cin >> id;      // get patient's id
    if (cin.fail()) // check if the id is valid
    {
      cin.clear();                                 // clear the error flag
      cin.ignore(10000, '\n');                     // ignore the rest of the input
      clearScreen();                               // clear the screen
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

  // function to display all patients
  void printAllPatients()
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
};
