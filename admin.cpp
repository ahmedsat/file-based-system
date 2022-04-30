#include <iostream>
#include <fstream>
#include <string>
#include "helperFunctions.cpp"
using namespace std;

class Admin
{
public:
  static void menu()
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
    }
  }
};