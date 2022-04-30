//? this file include helper functions
//? which designed to be used any where
//? just include the file and use

#include <iostream>
#include <fstream>
using namespace std;

void createFile(string fileName, string data)
{
  ofstream file(fileName);

  file << data;

  file.close();
}

string fileToString(string filename)
{

  string result;

  string temp;

  ifstream file(filename);
  while (getline(file, temp))
  {
    result += temp + "\n";
  }
  file.close();
  return result;
}