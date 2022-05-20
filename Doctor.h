#include <iostream>
#include <string>
#include <fstream>
using namespace std;

string DoctorPath = "Doctors.txt"; // path of the file to store doctors

// function to clear the screen
void clearScreen()
{
  system("cls");
}

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

public:
  // constructor to initialize the variables
  Doctor()
  {
    id = 0;
    name = "";
    specialization = "";
    experience = "";
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
        printAllDoctors(); // call the printAllDoctors function
        break;
      case 0:
        break;
      default:
        cout << "Invalid choice" << endl;
      }
    } while (choice != 0);
  }

  // function to add doctor
  void addDoctor()
  {

    clearScreen();

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
      clearScreen();
      message = "Invalid input, please try again";
      return;
    }
    // check if the id is already in use
    ifstream fin(DoctorPath); // open the file to read
    if (fin.is_open())        // if file is opened successfully
    {
      string line;               // variable to store each line of the file
      while (getline(fin, line)) // read each line of the file and store it in line
      {
        line = line.substr(0, line.find("|")); // extract the id from the line
        if (line == to_string(id))             // if the id is already in use
        {
          fin.close(); // close the file
          message = "Doctor with this ID already exists";
          return;
        }
      }
      fin.close();
    }
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
    ofstream fout(DoctorPath, ios::app); // open the file to write in append mode
    if (fout.is_open())                  // if file is opened successfully
    {
      // write the data to the file
      fout
          << id
          << "|"
          << name
          << "|"
          << specialization
          << "|"
          << experience
          << "|"
          << phone
          << "|"
          << email
          << "|"
          << address
          << endl;
      fout.close(); // close the file
      message = "Doctor added successfully";
    }
    else
    {
      message = "Error adding doctor";
    }
  }

  // function to remove doctor
  void removeDoctor()
  {

    int id;
    string line;
    bool found = false; // flag to indicate if the doctor is found

    cout << "Enter Doctor ID: ";
    cin >> id;      // get doctor's id
    if (cin.fail()) // if user entered a non-integer value show error message and return
    {
      cin.clear();             // clear the error flag
      cin.ignore(10000, '\n'); // ignore the rest of the input
      clearScreen();
      message = "Invalid input, please try again";
      return;
    }
    ifstream file;
    file.open(DoctorPath); // open the file to read
    if (file.is_open())    // if file is opened successfully
    {
      ofstream temp;         // declare a temporary file to store the data
      temp.open("temp.txt"); // open the temporary file to write
      if (temp.is_open())    // if file is opened successfully
      {
        while (getline(file, line)) // read each line of the file and store it in line
        {
          string idCheck = line.substr(0, line.find("|")); // extract the id from the line
          if (idCheck != to_string(id))                    // if the id is not the one to be removed
          {
            temp << line << endl; // write the data to the temporary file
          }
          else
          {
            found = true; // if the id is the one to be removed, set the flag to true
          }
        }
        // move temp to doctor file
        temp.close();
        file.close();
        remove("Doctors.txt");             // remove the original file
        rename("temp.txt", "Doctors.txt"); // rename the temporary file to the original file
        if (found)                         // if the doctor is found
        {
          message = "Doctor removed successfully";
        }
        else
        {
          message = "Doctor not found";
        }
      }
      else
      {
        message = "error: can't create temp file";
      }
    }
    else
    {
      message = "File not found";
    }
  }

  // function to edit doctor
  void editDoctor()
  {
    int id;
    string line;
    bool found = false; // flag to indicate if the doctor is found
    cout << "Enter Doctor ID: ";
    cin >> id;
    if (cin.fail()) // if user entered a non-integer value show error message and return
    {
      cin.clear();             // clear the error flag
      cin.ignore(10000, '\n'); // ignore the rest of the input
      clearScreen();
      message = "Invalid input, please try again";
      return;
    }
    ifstream file;         // declare a file to read
    file.open(DoctorPath); // open the file to read
    if (file.is_open())    // if file is opened successfully
    {
      ofstream temp;         // declare a temporary file to store the data
      temp.open("temp.txt"); // open the temporary file to write
      if (temp.is_open())    // if the temporary file is opened successfully
      {
        while (getline(file, line)) // read each line of the file and store it in line
        {
          string idCheck = line.substr(0, line.find("|")); // extract the id from the line
          if (idCheck != to_string(id))                    // if the id is not the one to be edited
          {
            temp << line << endl; // write the data to the temporary file
          }
          else
          {
            // if the id is the one to be edited, get the other details of the doctor
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

            // write the data to the temporary file
            temp
                << id
                << "|"
                << name
                << "|"
                << specialization
                << "|"
                << experience
                << "|"
                << phone
                << "|"
                << email
                << "|"
                << address
                << endl;
            found = true; // set the flag to true
          }
        }
        // move temp to doctor file
        temp.close();
        file.close();
        remove("Doctors.txt");             // remove the original file
        rename("temp.txt", "Doctors.txt"); // rename the temporary file to the original file

        if (found) // if the doctor is found
        {
          message = "Doctor edited successfully";
        }
        else
        {
          message = "Doctor not found";
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

  // function to display doctor
  void printDoctor()
  {
    int id;
    string line;
    cout << "Enter Doctor ID: ";
    cin >> id;      // get doctor's id
    if (cin.fail()) // if user entered a non-integer value show error message and return
    {
      cin.clear();             // clear the error flag
      cin.ignore(10000, '\n'); // ignore the rest of the input
      clearScreen();
      message = "Invalid input, please try again";
      return;
    }
    ifstream file;         // declare a file to read
    file.open(DoctorPath); // open the file to read
    if (file.is_open())    // if file is opened successfully
    {
      message = "Doctor not found"; // set the message to default
      while (getline(file, line))   // read each line of the file and store it in line
      {
        string idCheck = line.substr(0, line.find("|")); // extract the id from the line
        if (idCheck == to_string(id))                    // if the id is the one to be displayed
        {
          message = line; // set the message to the line
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

  // function to display all doctors
  void printAllDoctors()
  {
    string line;
    ifstream file;
    string output = "";    // string to store the output
    file.open(DoctorPath); // open the file to read
    if (file.is_open())    // if file is opened successfully
    {
      while (getline(file, line)) // read each line of the file and store it in line
      {
        output += line + "\n"; // append the line to the output
      }
      file.close();
      message = output; // set the message to the output
    }
    else
    {
      message = "File not found";
    }
  };
};