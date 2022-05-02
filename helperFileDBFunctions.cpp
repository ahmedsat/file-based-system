//? this file include helper functions
//? which designed to be used any where
//? just include the file and use

#include <iostream>
#include <fstream>
using namespace std;

void createFile(string fileName, string data)
{
  ofstream fileObject(fileName);

  fileObject << data;

  fileObject.close();
}

void addToFile(string fileName, string data)
{
  ofstream fileObject(fileName, ios_base::app);

  fileObject << data;

  fileObject.close();
}

string fileToString(string filename)
{

  string result;

  string temp;

  ifstream fileObject(filename);
  while (getline(fileObject, temp))
  {
    result += temp + "\n";
  }
  fileObject.close();
  return result;
}