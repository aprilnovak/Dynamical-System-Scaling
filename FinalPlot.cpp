// Plot full data

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

#define maximum = 100000
#define lines_in_original_input = 1298

int main () 
{

string location;
cin >> location;

string original_input = "test1.o";
string line [100000];
string words;
ifstream myfile_original;
myfile_original.open (original_input);

int original_lines = 0;
int marker;
int flag = 0;

for (int in = 0; in < 100000; in++)
{
  getline(myfile_original,words);
  line[in] = words;

  if (flag == 0)
  {
     if (line[in] == "1 time        mflowfj      mflowfj      mflowfj      mflowfj      tempf        tempf        tempf        tempf        tempf        ")
    {
      marker = in + 1;
      flag = 1;
    }
  }
  if (myfile_original.eof())
    break;

  original_lines++; 
}

original_lines++;

original_lines = original_lines-5; // last data point
marker = marker + 4; // start of actual data collection
int begin = marker;
int end = marker + 2193;
string finaldata[100000];

// only record the first 1000 seconds after the transient
int count = 1;

string filename_output = location + "final.txt";
ofstream myfile_out;
myfile_out.open (filename_output, ios::in | ios::app);

for (int i = marker; i < end; i++)
{  
  if (count > 110)
    count = 1;

  if (count <= 49)
    {
      finaldata[i] = line[marker];
      myfile_out << finaldata[i] << '\n';
    }
  else if ((count > 49) && (count <= 54))
  {

  }
  else
  {  
    if ((count > 103) && (count <= 110))
      {
        // do nothing
      } 
    else
    {
      finaldata[i] = line[marker];
      myfile_out << finaldata[i] << '\n';
    }
  }
  count++;
  marker++;
}

count = 1;



/*for (int i = begin; i < 15080; i++)
{  
  if (count <= 49)
  {
    myfile_out << finaldata[i] << finaldata[i+54] << '\n' << '\n' << '\n';
    count++;
  }
  else
    count = 1;
}*/






} 