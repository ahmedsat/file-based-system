#include <iostream>
using namespace std;
void clearScreen()
{
  cout << "\033[2J\033[1;1H";
}

// press any key to continue cross platform
void pressAnyKey()
{
  cout << "\nPress any key to continue...";
  cin.get();
}
