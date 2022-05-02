#include <iostream>
#include <fstream>
#include <string>
#include "helperFunctions.cpp"
#include "helperFileDBFunctions.cpp"
using namespace std;

class Admin
{
private:
  string path;

public:
  Admin(string path)
  {
    this->path = path;
  }

  void menu()
  {
    while (true)
    {
      string input;
      clearScreen();
      cout << "   =>   Menu   <=   " << endl;
      cout << "1) Add user" << endl;
      cout << "2) List all users" << endl;
      cout << "3) search user" << endl;
      cout << "4) Update user" << endl;
      cout << "5) Delete user" << endl;

      cout << "0) Close the app" << endl;
      cout << "Enter your selection :  ";
      cin >> input;
      if (input == "0")
      {
        break;
      }
      if (input == "1")
      {
        add();
      }
      if (input == "2")
      {
        listAll();
      }
    }
  }
  void add()
  {
    int id;
    string name;
    string password;
    string user;
    bool validData = true;
    do
    {
      cout << "Enter user id :  ";
      cin >> id;
      cout << "Enter user name :  ";
      cin >> name;
      cout << "Enter user password :  ";
      cin >> password;
      user = "|" + to_string(id) + "|" + name + "|" + password + "|\n";
      cout << endl
           << "User data :  " + user << endl
           << "if data is correct enter => 1" << endl
           << "else enter => 0" << endl
           << "any thing else will be true  ";
      int in;
      cin >> in;
      if (in)
      {
        validData = 1;
      }
      else
      {
        validData = 0;
      }

    } while (!validData);
    addToFile(path, user);
  }
  void listAll()
  {
    string temp;
    cout << "|id|name|password|\n"
         << fileToString(path);
    cin >> temp;
  }
};