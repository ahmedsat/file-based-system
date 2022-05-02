#include <iostream>
#include <string>
#include <fstream>
using namespace std;

string todopath = "/home/ahmedsat/c++/todo/Todo.txt";
string userspath = "/home/ahmedsat/c++/todo/User.txt";

void clearScreen()
{
  cout << "\033[2J\033[1;1H";
}

void pressAnyKey()
{
  cout << "Press any key to continue...";
  cin.get();
}

void addUser()
{
  clearScreen();
  int id;
  string name, password;
  cout << "Enter id: ";
  cin >> id;
  cout << "Enter name: ";
  cin >> name;
  cout << "Enter password: ";
  cin >> password;
  ofstream file;
  file.open(userspath, ios::app);
  file << id << "|" << name << "|" << password << endl;
  file.close();
}
void removeUser()
{
  clearScreen();
  int id;
  cout << "Enter id: ";
  cin >> id;
  ifstream file;
  file.open(userspath);
  ofstream temp;
  temp.open("temp.txt");
  string line;
  while (getline(file, line))
  {
    string id_ = line.substr(0, line.find("|"));
    if (id_ != to_string(id))
    {
      temp << line << endl;
    }
  }
  file.close();
  temp.close();
  remove(userspath.c_str());
  rename("temp.txt", userspath.c_str());
}
void editUser()
{
  clearScreen();
  int id;
  string name, password;
  cout << "Enter id: ";
  cin >> id;
  cout << "Enter name: ";
  cin >> name;
  cout << "Enter password: ";
  cin >> password;
  ifstream file;
  file.open(userspath);
  ofstream temp;
  temp.open("temp.txt");
  string line;
  while (getline(file, line))
  {
    string id_ = line.substr(0, line.find("|"));
    if (id_ != to_string(id))
    {
      temp << line << endl;
    }
    else
    {
      temp << id << "|" << name << "|" << password << endl;
    }
  }
  file.close();
  temp.close();
  remove(userspath.c_str());
  rename("temp.txt", userspath.c_str());
}
void showUserById()
{
  clearScreen();
  int id;
  cout << "Enter id: ";
  cin >> id;
  ifstream file;
  file.open(userspath);
  string line;
  while (getline(file, line))
  {
    string id_ = line.substr(0, line.find("|"));
    if (id_ == to_string(id))
    {
      cout << line << endl;
    }
  }
  file.close();
}
void showUsers()
{
  clearScreen();
  ifstream file;
  file.open(userspath);
  string line;
  while (getline(file, line))
  {
    cout << line << endl;
  }
  file.close();
}
void adminMenu()
{
  int choice;
  do
  {
    clearScreen();
    cout << "1. Add User" << endl;
    cout << "2. Remove User" << endl;
    cout << "3. Edit User" << endl;
    cout << "4. Show User by id" << endl;
    cout << "5. Show Users" << endl;
    cout << "6. Exit" << endl;
    cout << "Enter your choice: ";
    cin >> choice;
    switch (choice)
    {
    case 1:
      addUser();
      break;
    case 2:
      removeUser();
      break;
    case 3:
      editUser();
      break;
    case 4:
      showUserById();
      break;
    case 5:
      showUsers();
      break;
    case 6:
      break;
    default:
      cout << "Invalid choice" << endl;
    }
  } while (choice != 6);
}

class User
{
private:
  int id;
  string username;
  string password;

public:
  User(int id, string username, string password)
  {
    this->id = id;
    this->username = username;
    this->password = password;
  }
  User()
  {
    this->id = 0;
    this->username = "";
    this->password = "";
  }
};

int main()
{
  int choice;
  adminMenu();
  return 0;
}
