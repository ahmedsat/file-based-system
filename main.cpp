#include <iostream>
#include <fstream>
#include <string>

// #include "helperFunctions.cpp"
#include "admin.cpp"

using namespace std;
string path = "/home/ahmedsat/c++/todo/DB/Users.txt";

int main()
{

  Admin admin(path);

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

    if (input == "0")
    {
      return 0;
    }

    if (input == "2")
    {
      admin.menu();
    }
  }

  return 0;
}