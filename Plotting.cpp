// Converts readable output file to raw data (csv file) for Matlab input.

#include <iostream>
#include <fstream>
#include <string>
#include <array>
#include <sstream>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <cmath>
#include <iomanip>
using namespace std;

// maximum number of columns in the formatted output file
#define columns 10
#define rows 10000
// number of lines (i.e. variables to be recorded) for the rawdata.txt output
#define num_variables 18

int main () 
{

// Take input from ./irun about the current location, since this will be used for naming the 
// raw data output file. 
string location;
cin >> location;

string line;
ifstream myfile_original;
myfile_original.open ("iterationresults.txt");

int original_lines = 0;
string dataset [rows] [columns];
int col = 0;
int row = 0;

// extracts data into an array, dataset
while (!myfile_original.eof())
{ 
  getline(myfile_original,line);
  istringstream iss(line);
  string word;
  col = 0;

  while (iss >> word)
  {
    dataset [original_lines] [col] = word;
    col++;
  }

  row++;
  original_lines++; 
}

myfile_original.close();

string raw_data [num_variables] [100];
int colum=0;

for (int row=0; row<original_lines; row++)
{
  if (dataset[row][0] == "#")
  { 
    if (dataset[row][1] == "Core")
    {
      raw_data[0][colum] = "0";
      raw_data[13][colum] = dataset[row][4];
    }

    if (dataset[row][1] == "Bypass")
      raw_data[14][colum] = dataset[row][4];

    if (dataset[row][2] == "shell")
      raw_data[15][colum] = dataset[row][5];

    if (dataset[row][2] == "tube")
    {
      raw_data[16][colum] = dataset[row][5];
      raw_data[1][colum] = dataset[10][2];
      raw_data[2][colum] = dataset[11][2];
      raw_data[3][colum] = dataset[12][3];
      raw_data[4][colum] = dataset[13][3]; 
      raw_data[5][colum] = dataset[14][3];
      raw_data[6][colum] = dataset[15][3];
      raw_data[7][colum] = dataset[16][4];
      raw_data[8][colum] = dataset[17][4];
      raw_data[9][colum] = dataset[18][4];
      raw_data[10][colum] = dataset[19][4];
      raw_data[11][colum] = dataset[20][3];
      raw_data[12][colum] = dataset[21][3];
      raw_data[17][colum] = dataset[7][5];
      colum++;
    }
  }

  if (dataset[row][0] == "Iteration")
    raw_data[0][colum] = dataset[row][2];

  if (dataset[row][0] == "Core")
  {
    if (dataset[row][1] == "flowrate:")
      raw_data[1][colum] = dataset[row][4];
    else if (dataset[row][1] == "inlet")
      raw_data[5][colum] = dataset[row][5];
    else //outlet
      raw_data[6][colum] = dataset[row][5];
  }

  if (dataset[row][0] == "Bypass")
    raw_data[2][colum] = dataset[row][4];

  if (dataset[row][0] == "DHX")
  {
    if (dataset[row][1] == "shell")
    {
      if (dataset[row][2] == "flowrate:")
        raw_data[3][colum] = dataset[row][5];
      else if (dataset[row][2] == "inlet")
        raw_data[7][colum] = dataset[row][6];
      else
        raw_data[8][colum] = dataset[row][6];
    }
    else // equals tube
    {
      if (dataset[row][2] == "inlet")
        raw_data[9][colum] = dataset[row][6];
      else if (dataset[row][2] == "outlet")
        raw_data[10][colum] = dataset[row][6];
      else
        raw_data[4][colum] = dataset[row][5];
    }
  }


  if (dataset[row][0] == "TCHX")
  {
    if (dataset[row][1] == "inlet")
      raw_data[11][colum] = dataset[row][5];
    else
      raw_data[12][colum] = dataset[row][5];
  }

  if (dataset[row][0] == "New")
  {
    if (dataset[row][1] == "core")
      raw_data[13][colum] = dataset[row][3];
    if (dataset[row][1] == "bypass")
      raw_data[14][colum] = dataset[row][3];
    if (dataset[row][2] == "shell")
      raw_data[15][colum] = dataset[row][4];
    if (dataset[row][2] == "tube")
      raw_data[16][colum] = dataset[row][4];
    if (dataset[row][1] == "TCHX")
    {
      raw_data[17][colum] = dataset[row][3];
      colum++;
    }
  }
}

// Write to text file data_Test... with the same name as the input file (for use with the Matlab GUI). 
ofstream myfile_raw_out;
myfile_raw_out.open (location);

int R=0;

for (int R =0; R< num_variables; R++)
{
  for (int C = 0; C< colum; C++)
      myfile_raw_out << setw(10) << raw_data[R][C] <<  ", " << ' ';

  myfile_raw_out << '\n';
}

} 