#include <iostream>
#include <fstream>
#include <string>

#include "helperFunctions.cpp"
#include "admin.cpp"

using namespace std;
string path = "/home/ahmedsat/c++/todo/DB/Users.txt";

int main()
{

  while (true)
  {
    string input;
    clearScreen();
    cout << "   =>   Menu   <=   " << endl;
    cout << "1) I'm a user" << endl;
    cout << "2) I'm an admin" << endl;
    cout << "0) Close the app" << endl;
    cout << "Enter your selection :  ";
    cin >> input;
    switch (stoi(input))
    {
    case 0:
      break;
    case 1:
      Admin::menu();
    default:
      break;
    }
    if (input == "0")
    {
      break;
    }
  }

  return 0;
}