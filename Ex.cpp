// Search for input errors during processing. (if slurm.out > 6500 or time > 10 minutes)
// Get more accurate slurm.out size at completion
// Move to earlier recording time
// Get Master preceding values to match those from BlueJ
// if slurm.out does not exist, break
// Get rid of necessity to have iterationresults.txt before hand

// 3: Get Master input values to come directly from BlueJ

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

// [] Number of lines to extract from RELAP output file
#define num_lines_extract 9
// [] Maximum number of words in all the lines of interest (i.e. words in longest line)
#define maximum_words_in_line_extract 10
// [] Number of lines in original input file
#define lines_in_original_input 1298
// Maximum possible number of lines (set arbitrarily high)
#define maximum 100000

int main () 
{
// Receives the iteration number from ./irun
float iterations;
cin >> iterations;

cout << '\n';

// [] Open original input file and determine its number of original lines to determine the correction factor
//    by which to modify the number of lines for copying purposes. 
// [] Original input name (renamed Input.txt from Test-.... by ./Master)
string original_input = "Input.txt";
string line;
ifstream myfile_original;
myfile_original.open (original_input);

int original_lines = 0;

for (int i=0; i<maximum; i++)
{
  getline(myfile_original,line);

// [] End of file is signalled by ". "
  if (line == ". ") 
    break;

  original_lines++; 
}

original_lines++;

int correction = original_lines - lines_in_original_input;

// [] Corrects the lines to be extracted if modifying lines have been appended to the original RELAP input. 
//    It is recommended to not use lines directly from the input, since extra lines could have been appended,
//    changing the values. Ensure that the formula (initial +2*correction) is still valid. 
int i_want_these_lines [num_lines_extract] = {1631+2*correction, 1799+2*correction, 1922 + 2*correction, 4205 + 2*correction, 4415 + 2*correction, 14967 + 2*correction, 14976+2*correction, 15021+ 2*correction, 15030 + 2*correction};

// Stores extracted lines into another array. 
int line_number [num_lines_extract];

for (int i=0; i < num_lines_extract; i++)
{ 
  if (i==0)
    line_number[i]=i_want_these_lines[i];
  else
    line_number[i]=i_want_these_lines[i]-i_want_these_lines[i-1];
}

// Holds data from each line
string line_data [num_lines_extract];

// [] Open output file and extract data. Insert correct name of output file. 
string filename_input = "test1.o";
ifstream myfile_in (filename_input);

if (myfile_in.is_open())
{
  for (int index=0; index<num_lines_extract; index++)
  {
    for (int i=0; i<line_number[index]; i++)
      getline(myfile_in,line);
      line_data[index]=line;
  }
    myfile_in.close();
}

else { cout << "!!! Unable to open file - file does not exist. \n";}

// Displays the line data to the screen for debugging
/*for (int index=0; index < num_lines_extract; index++)
    cout << line_data[index] << '\n';
cout << '\n';*/

// Extract each word into an array. 
string word;
string line_data_words [num_lines_extract] [maximum_words_in_line_extract];
int column=0;

for (int line = 0; line < num_lines_extract; line++)
{ 
  column=0;
  istringstream iss(line_data[line]);

  while (iss >> word)
  { 
    line_data_words[line][column] = word;
    column++; 
  }
}

// [] Assign extracted data values to variables. These will change for someone else using this program for
//    another application where they're not extracting the same info. 
double Tcore_in, Tcore_out;
double TDHX_shell_in, TDHX_shell_out;
double TDHX_tube_in, TDHX_tube_out;
double TTCHX_in, TTCHX_out;
double mflow_core;
double mflow_bypass;
double mflow_DHX_shell;
double mflow_DHX_tube;
double Dr, lr;

// All values are in string format, so convert them to their type definition
stringstream(line_data_words[6][1]) >> mflow_core;
stringstream(line_data_words[6][2]) >> mflow_bypass;
stringstream(line_data_words[6][3]) >> mflow_DHX_shell;
stringstream(line_data_words[6][4]) >> mflow_DHX_tube;
stringstream(line_data_words[6][5]) >> Tcore_in;
stringstream(line_data_words[6][6]) >> Tcore_out;
stringstream(line_data_words[6][7]) >> TDHX_shell_in;
stringstream(line_data_words[6][8]) >> TDHX_shell_out;
stringstream(line_data_words[6][9]) >> TDHX_tube_in;
stringstream(line_data_words[8][1]) >> TDHX_tube_out;
stringstream(line_data_words[8][2]) >> TTCHX_in;
stringstream(line_data_words[8][3]) >> TTCHX_out;

double S_Tcore_in, S_Tcore_out;
double S_TDHX_shell_in, S_TDHX_shell_out;
double S_TDHX_tube_in, S_TDHX_tube_out;
double S_TTCHX_in, S_TTCHX_out;
double S_mflow_core;
double S_mflow_bypass;
double S_mflow_DHX_shell;
double S_mflow_DHX_tube;
double S_core_forward_loss, S_core_Re_forward_loss;
double S_bypass_forward_loss, S_bypass_Re_forward_loss;
double S_DHX_shell_forward_loss, S_DHX_tube_forward_loss;

stringstream(line_data_words[5][1]) >> S_mflow_core;
stringstream(line_data_words[5][2]) >> S_mflow_bypass;
stringstream(line_data_words[5][3]) >> S_mflow_DHX_shell;
stringstream(line_data_words[5][4]) >> S_mflow_DHX_tube;
stringstream(line_data_words[5][5]) >> S_Tcore_in;
stringstream(line_data_words[5][6]) >> S_Tcore_out;
stringstream(line_data_words[5][7]) >> S_TDHX_shell_in;
stringstream(line_data_words[5][8]) >> S_TDHX_shell_out;
stringstream(line_data_words[5][9]) >> S_TDHX_tube_in;
stringstream(line_data_words[7][1]) >> S_TDHX_tube_out;
stringstream(line_data_words[7][2]) >> S_TTCHX_in;
stringstream(line_data_words[7][3]) >> S_TTCHX_out;
stringstream(line_data_words[0][1]) >> S_core_forward_loss;
stringstream(line_data_words[0][2]) >> S_core_Re_forward_loss;
stringstream(line_data_words[1][1]) >> S_bypass_forward_loss;
stringstream(line_data_words[1][2]) >> S_bypass_Re_forward_loss;
stringstream(line_data_words[3][1]) >> S_DHX_shell_forward_loss;
stringstream(line_data_words[4][1]) >> S_DHX_tube_forward_loss;
stringstream(line_data_words[2][3]) >> lr;
stringstream(line_data_words[2][8]) >> Dr;

// [] insert correct values for prototype
lr = lr/0.1795;
Dr = Dr/0.5656;
//cout << "Lr is: " << lr << '\n' << "Dr is : "<< Dr << '\n';
// [] Copy initial values so that they are properly stored in the output.
double Original_core_forward_loss, Original_bypass_forward_loss, Original_DHX_shell_forward_loss, Original_DHX_tube_forward_loss, Original_LTCHX;

if (iterations == 0)
{
  Original_core_forward_loss = S_core_forward_loss;
  Original_bypass_forward_loss = S_bypass_forward_loss;
  Original_DHX_shell_forward_loss = S_DHX_shell_forward_loss;
  Original_DHX_tube_forward_loss = S_DHX_tube_forward_loss;
}

// [] Display output to screen (for easy de-bugging). 
cout << "Core flowrate (Requested):      " << setw(7) << fixed << setprecision(2) << S_mflow_core << "  Actual: " << setw(7) << fixed << setprecision(2) << mflow_core << '\n';
cout << "Bypass flowrate (Requested):    " << setw(7) << fixed << setprecision(2) << S_mflow_bypass << "  Actual: " << setw(7) << fixed << setprecision(2) << mflow_bypass << '\n';
cout << "DHX shell flowrate (Requested): " << setw(7) << fixed << setprecision(2) << S_mflow_DHX_shell << "  Actual: " << setw(7) << fixed << setprecision(2) << mflow_DHX_shell << '\n';
cout << "DHX tube flowrate (Requested):  " << setw(7) << fixed << setprecision(2) << S_mflow_DHX_tube << "  Actual: " << setw(7) << fixed << setprecision(2) << mflow_DHX_tube << '\n' << '\n';
cout << "Core inlet T (Requested):       " << setw(7) << fixed << setprecision(2) << S_Tcore_in << "  Actual: " << setw(7) << fixed << setprecision(2) << Tcore_in << '\n';
cout << "Core outet T (Requested):       " << setw(7) << fixed << setprecision(2) << S_Tcore_out << "  Actual: " << setw(7) << fixed << setprecision(2) << Tcore_out << '\n';
cout << "DHX shell inlet T (Requested):  " << setw(7) << fixed << setprecision(2) << S_TDHX_shell_in << "  Actual: " << setw(7) << fixed << setprecision(2) << TDHX_shell_in << '\n';
cout << "DHX shell outlet T (Requested): " << setw(7) << fixed << setprecision(2) << S_TDHX_shell_out << "  Actual: " << setw(7) << fixed << setprecision(2) << TDHX_shell_out << '\n';
cout << "DHX tube inlet T (Requested):   " << setw(7) << fixed << setprecision(2) << S_TDHX_tube_in << "  Actual: " << setw(7) << fixed << setprecision(2) << TDHX_tube_in << '\n';
cout << "DHX tube outlet T (Requested):  " << setw(7) << fixed << setprecision(2) << S_TDHX_tube_out << "  Actual: " << setw(7) << fixed << setprecision(2) << TDHX_tube_out << '\n';
cout << "TCHX inlet T (Requested):       " << setw(7) << fixed << setprecision(2) << S_TTCHX_in << "  Actual: " << setw(7) << fixed << setprecision(2) << TTCHX_in << '\n';
cout << "TCHX outlet T (Requested):      " << setw(7) << fixed << setprecision(2) << S_TTCHX_out << "  Actual: " << setw(7) << fixed << setprecision(2) << TTCHX_out << '\n' << '\n';

// [] Set convergence criteria. When all of these criteria are met, the iteration process will stop. 
//    Flag containing equal = 1, not equal = 0. The size of flag must equal the number of convergence criteria. 
int flag [12];
int size_flag = sizeof(flag)/sizeof(flag[0]);
for (int i=0; i < size_flag; i++) 
  flag[i] = 0;

if ((fabs((S_mflow_core-mflow_core)/S_mflow_core) <= 0.01) || (fabs(S_mflow_core-mflow_core) < 1))              flag[0] =  1;
// if (fabs((S_mflow_bypass-mflow_bypass)/S_mflow_bypass) <= 0.02)          flag[1] =  1;
// no longer iterating bypass coefficient
//flag[1] = 1;

// need to go at least one iteration to make sure that the updated area doesn't change the needed loss coefficients too much
if (iterations == 0)
  flag[1] = 0;
else
  flag[1] = 1;

if ((fabs((S_mflow_DHX_shell-mflow_DHX_shell)/S_mflow_DHX_shell) <= 0.01) || (fabs(S_mflow_DHX_shell-mflow_DHX_shell) < 0.25)) flag[2] =  1;
if ((fabs((S_mflow_DHX_tube-mflow_DHX_tube)/S_mflow_DHX_tube) <= 0.01) || (fabs(S_mflow_DHX_tube-mflow_DHX_tube) < 0.25))    flag[3] =  1;
if (fabs((S_Tcore_in-Tcore_in)/S_Tcore_in) <= 0.01)                      flag[4] =  1;
if (fabs((S_Tcore_out-Tcore_out)/S_Tcore_out) <= 0.01)                   flag[5] =  1;
if (fabs((S_TDHX_shell_in-TDHX_shell_in)/S_TDHX_shell_in) <= 0.01)       flag[6] =  1;
if (fabs((S_TDHX_shell_out-TDHX_shell_out)/S_TDHX_shell_out) <= 0.01)    flag[7] =  1;
if (fabs((S_TDHX_tube_in-TDHX_tube_in)/S_TDHX_tube_in) <= 0.01)          flag[8] =  1;
if (fabs((S_TDHX_tube_out-TDHX_tube_out)/S_TDHX_tube_out) <= 0.01)       flag[9] =  1;
if (fabs((S_TTCHX_in-TTCHX_in)/S_TTCHX_in) <= 0.01)                      flag[10] = 1;
if (fabs((S_TTCHX_out-TTCHX_out)/S_TTCHX_out) <= 0.01)                   flag[11] = 1;
/*flag[4] = 1;
flag[5] = 1;
flag[6] = 1;
flag[7] = 1;
flag[8] = 1;
flag[9] = 1;
flag[10] = 1;
flag[11] = 1;*/

// [] Display flag data to screen (optional)
cout << "The convergence flags are [1 = converged, 0 = not converged]: " << '\n';

for (int i=0; i< size_flag; i++) 
  cout << flag[i] << ' ';
  
cout << '\n' << '\n';

// [] Select the commands to be performed if a convergence criteria is not met (such as update a loss coefficient).
if (flag[0] == 0)
{ 
  if (mflow_core < S_mflow_core)
    S_core_forward_loss = (1-fabs((mflow_core-S_mflow_core)/(S_mflow_core)))*S_core_forward_loss;
  else
    S_core_forward_loss = (1+fabs((mflow_core-S_mflow_core)/(S_mflow_core)))*S_core_forward_loss;
}
cout << "New core forward loss:      " << setw(10) << fixed << setprecision(3) << S_core_forward_loss << '\n';

if (flag[1] == 0)
{
  if (mflow_bypass < S_mflow_bypass)
    S_bypass_forward_loss = (1-fabs((mflow_bypass-S_mflow_bypass)/(S_mflow_bypass)))*S_bypass_forward_loss;
  else
    S_bypass_forward_loss = (1+fabs((mflow_bypass-S_mflow_bypass)/(S_mflow_bypass)))*S_bypass_forward_loss;
}
cout << "New bypass forward loss:    " << setw(10) << fixed << setprecision(3) << S_bypass_forward_loss << '\n';

if (flag[2] == 0)
{
  if (mflow_DHX_shell < S_mflow_DHX_shell)
    S_DHX_shell_forward_loss = (1-fabs((mflow_DHX_shell-S_mflow_DHX_shell)/(S_mflow_DHX_shell)))*S_DHX_shell_forward_loss;
  else
    S_DHX_shell_forward_loss = (1+fabs((mflow_DHX_shell-S_mflow_DHX_shell)/(S_mflow_DHX_shell)))*S_DHX_shell_forward_loss;
}
cout << "New DHX shell forward loss: " << setw(10) << fixed << setprecision(3) << S_DHX_shell_forward_loss << '\n';

if (flag[3] == 0)
{
  if (mflow_DHX_tube < S_mflow_DHX_tube)
    S_DHX_tube_forward_loss = (1-fabs((mflow_DHX_tube-S_mflow_DHX_tube)/(S_mflow_DHX_tube)))*S_DHX_tube_forward_loss;
  else
    S_DHX_tube_forward_loss = (1+fabs((mflow_DHX_tube-S_mflow_DHX_tube)/(S_mflow_DHX_tube)))*S_DHX_tube_forward_loss;
}
cout << "New DHX tube forward loss:  " << setw(10) << fixed << setprecision(3) << S_DHX_tube_forward_loss << '\n';

cout << "***************************************************************";
// [] Use these new values to calculate new parameters for re-entry into a revised input file. (optional)
double Tbar_loop1 = (Tcore_in + Tcore_out)/2;
double Tbar_loop2 = (TDHX_shell_in+TDHX_shell_out)/2;

// Material Properties: Dowtherm A
double Cp_dowa_1 = 1518 + 2.82*(Tbar_loop1-273);
double Cp_dowa_2 = 1518 + 2.82*(Tbar_loop2-273);
double rho_dowa_1 = 1078 - 0.85*(Tbar_loop1-273);
double rho_dowa_2 = 1078 - 0.85*(Tbar_loop2-273);
double k_dowa_1 = 0.142 - 0.00016*(Tbar_loop1 - 273);
double k_dowa_2 = 0.142 - 0.00016*(Tbar_loop2 - 273);
double beta_dowa_1 = 0.85/rho_dowa_1;
double beta_dowa_2 = 0.85/rho_dowa_2;

// Material Properties: Flibe at prototypical conditions: 650 C Tbar in loop 1, 560 C Tbar in loop 2
double Cp_flibe_1 = 2415.78;
double Cp_flibe_2 = 2415.78;
double rho_flibe_1 = 2415.6 - 0.49072*(650+273);
double rho_flibe_2 = 2415.6 - 0.49072*(560+273);
double k_flibe_1 = 0.5*0.119*sqrt(460+273)*pow(33040/rho_flibe_1, 2/3)/pow(33.04/2.17, 1.167)+0.5*(0.0005*(650+273)+32/33.04-0.34);
double k_flibe_2 = 0.5*0.119*sqrt(460+273)*pow(33040/rho_flibe_2, 2/3)/pow(33.04/2.17, 1.167)+0.5*(0.0005*(560+273)+32/33.04-0.34);
double beta_flibe_1 = 0.49072/rho_flibe_1;
double beta_flibe_2 = 0.49072/rho_flibe_2;

// Calculate relative values for LHS. 
double Cp1R = Cp_dowa_1/Cp_flibe_1;
double rho_1R = rho_dowa_1/rho_flibe_1;
double beta_1R = beta_dowa_1/beta_flibe_1;
double k_1R = k_dowa_1/k_flibe_1;
double h_1R = Dr/k_1R;
double A_DHX_R = lr*Dr;
double inc_z_1R = lr;
double A_1R = Dr*Dr;
double l_div_D_1 = 4.58/0.03 + 3.96/0.5656244 + 3.77/0.5656244 + 0.5/0.58 + 3.008/0.15 + 2.5/0.01085449 + 0.58/0.15 + 0.5/0.056 + 4.76/0.056 + 0.2/0.03;
double LHS = pow(h_1R*A_DHX_R, 3)*(l_div_D_1*lr*(1.5e-5) + S_core_forward_loss + S_DHX_shell_forward_loss)/( pow(A_1R,2) * (l_div_D_1*(1.5e-5) + 40.0 + 19000.0) * pow(Cp1R,2) * pow(rho_1R,2) * beta_1R * inc_z_1R);

// Calculate relative values for RHS
double rho_2R = rho_dowa_2/rho_flibe_2;
double beta_2R = beta_dowa_2/beta_flibe_2;
double k_2R = k_dowa_2/k_flibe_2;
double h_2R = Dr/k_2R;
double mdot_2R = mflow_DHX_tube/S_mflow_DHX_tube;
double inc_z_2R = lr;
double A_2R = A_1R;
double l_div_D_2 = 2.5/0.0109 + 3.45/0.15 + 3.67/0.15 + 2.6/0.15 + 6.0/0.0109 + 4.43/0.15 + 5.95/0.15;
double RHS = h_2R*pow(mdot_2R,2)*( (1.5e-5)*lr*l_div_D_2 + S_DHX_tube_forward_loss )/(pow(A_2R,2)*( (1.5e-5)*l_div_D_2 + 0.0) *pow(rho_2R,2) *beta_2R * inc_z_2R);
double ATCHX_R = LHS/RHS;

Original_LTCHX = 6*lr*2*4*234/34;
double ATCHX = ATCHX_R * Original_LTCHX * 2 * 3.14159 * 0.0109; // model ATCHX
double LTCHX = ATCHX/(2 * 3.14159 * Dr * 0.0109);

//cout << '\n' << "The relative ATCHX is calculated to be: " << ATCHX_R << '\n';
//cout << '\n' << "The new LTCHX is calculated to be: " << LTCHX << '\n';
 

// Substitute new values into a revised input text file. A temporary input file called Updated_Input.txt is created.
// Then all original lines from the input are copied in. At the end are appended any new lines (for RELAP adding
// another line negates the previous line. Other codes may need to selectively replace specific lines rather than
// adding to the bottom. 
string filename_output = "Updated_Input.txt";
ofstream myfile_out;
myfile_out.open (filename_output, ios::in | ios::app);

if (myfile_out.is_open())
{
// [] Open original input file (Input.txt) and copy select lines to Updated_Output.txt
  string original_input = "Input.txt";
  ifstream myfile_original;
  myfile_original.open (original_input);

  for (int i=0; i<maximum; i++)
  {
    getline(myfile_original,line);
    myfile_out << line << '\n';

// [] "* End of input " signals the second line to the end of the original input file. 
//    This is the signal to begin appending new lines afterwards.
    if (line == "* End of input ") 
      break;
  }

// [] Append new lines. 
myfile_out << "100901 " << fixed << setprecision(5) << S_core_forward_loss << " " << fixed << setprecision(5) << S_core_forward_loss << " 25" << '\n' ;
//myfile_out << "200901 " << fixed << setprecision(5) << S_bypass_forward_loss << " " << fixed << setprecision(5) << S_bypass_forward_loss << " 25" << '\n' ;
myfile_out << "1700901 " << fixed << setprecision(5) << S_DHX_shell_forward_loss << " " << fixed << setprecision(5) << S_DHX_shell_forward_loss << " 13" << '\n' ;
myfile_out << "1900901 " << fixed << setprecision(5) << S_DHX_tube_forward_loss << " " << fixed << setprecision(5) << S_DHX_tube_forward_loss << " 13" << '\n' ;
myfile_out << "12301501 230010000 10000 3070 1 " << LTCHX << " 34" << '\n';
myfile_out << "12301601 -50 0 1000 1 " << LTCHX << " 34" << '\n';

// [] End file with the signal that it is the end of the file.  
myfile_out << ". ";

}
else cout << "!!! Unable to write to new input file.";

// [] Delete original input file and rename Updated_Input.txt to original input file name. Also remove the slurm files
//    to give the correct estimate of slurm.out's size (needed by irun to tell it how long to wait until job completion)
remove(original_input.c_str());
remove(filename_input.c_str());
rename(filename_output.c_str(), original_input.c_str());
remove("slurm.err");
remove("slurm.out");
remove("test1.plt");
remove("test1.r");

// [] Write iteration results to iterationresults.txt to store the # of iterations and updated guesses in a readable manner.
//    Plotting.cpp then takes iterationresults.txt and converts it to a Matlab csv file. 
string filename_temp = "iterationresults.txt";
ofstream myfile_temp;
myfile_temp.open (filename_temp, ios::in | ios::app);

if (myfile_temp.is_open())
{
  for (int i = 0; i < maximum; i++)
  { 
    if (line == "* End of results.") 
      break; 
  }

  if (iterations > 0)
  {
// [] Append new lines if variable adjustment has occurred (iteration > 0). 
    myfile_temp << '\n';
    myfile_temp << "Iteration number:   " << iterations+1 << '\n';
    myfile_temp << "Core flowrate:      " << setw(8) << fixed << setprecision(2) << S_mflow_core << " Actual: " << setw(8) << fixed << setprecision(4) <<  mflow_core << '\n';
    myfile_temp << "Bypass flowrate:    " << setw(8) << fixed << setprecision(2) << S_mflow_bypass << " Actual: " << setw(8) << fixed << setprecision(4) << mflow_bypass << '\n';
    myfile_temp << "DHX shell flowrate: " << setw(8) << fixed << setprecision(2) << S_mflow_DHX_shell << " Actual: " << setw(8) << fixed << setprecision(4) << mflow_DHX_shell << '\n';
    myfile_temp << "DHX tube flowrate:  " << setw(8) << fixed << setprecision(2) << S_mflow_DHX_tube << " Actual: " << setw(8) << fixed << setprecision(4) << mflow_DHX_tube << '\n';
    myfile_temp << "Core inlet T:       " << setw(8) << fixed << setprecision(2) << S_Tcore_in << " Actual: " << setw(8) << fixed << setprecision(4) << Tcore_in << '\n';
    myfile_temp << "Core outlet T:      " << setw(8) << fixed << setprecision(2) << S_Tcore_out << " Actual: " << setw(8) << fixed << setprecision(4) << Tcore_out << '\n';
    myfile_temp << "DHX shell inlet T:  " << setw(8) << fixed << setprecision(2) << S_TDHX_shell_in << " Actual: " << setw(8) << fixed << setprecision(4) << TDHX_shell_in << '\n';
    myfile_temp << "DHX shell outlet T: " << setw(8) << fixed << setprecision(2) << S_TDHX_shell_out << " Actual: " << setw(8) << fixed << setprecision(4) << TDHX_shell_out << '\n';
    myfile_temp << "DHX tube inlet T:   " << setw(8) << fixed << setprecision(2) << S_TDHX_tube_in << " Actual: " << setw(8) << fixed << setprecision(4) << TDHX_tube_in << '\n';
    myfile_temp << "DHX tube outlet T:  " << setw(8) << fixed << setprecision(2) << S_TDHX_tube_out << " Actual: " << setw(8) << fixed << setprecision(4) << TDHX_tube_out << '\n';
    myfile_temp << "TCHX inlet T:       " << setw(8) << fixed << setprecision(2) << S_TTCHX_in << " Actual: " << setw(8) << fixed << setprecision(4) << TTCHX_in << '\n';
    myfile_temp << "TCHX outlet T:      " << setw(8) << fixed << setprecision(2) << S_TTCHX_out << " Actual: " << setw(8) << fixed << setprecision(4) << TTCHX_out << '\n' << '\n';
    myfile_temp << "New core loss:      " << setw(8) << fixed << setprecision(5) << S_core_forward_loss << '\n';
    myfile_temp << "New bypass loss:    " << setw(8) << fixed << setprecision(5) << S_bypass_forward_loss << '\n';
    myfile_temp << "New DHX shell loss: " << setw(8) << fixed << setprecision(5) << S_DHX_shell_forward_loss << '\n';
    myfile_temp << "New DHX tube loss:  " << setw(8) << fixed << setprecision(5) << S_DHX_tube_forward_loss << '\n';
    myfile_temp << "New TCHX length:    " << setw(8) << fixed << setprecision(5) << LTCHX << '\n' << '\n';
    }

// [] If no iterations have performed, then append the original values. 
  if (iterations == 0)
  {
    myfile_temp << "# Iteration number:          " << iterations << '\n';
    myfile_temp << "# Core forward loss:         " << Original_core_forward_loss << '\n';
    myfile_temp << "# Bypass forward loss:       " << Original_bypass_forward_loss << '\n';
    myfile_temp << "# DHX shell forward loss:    " << Original_DHX_shell_forward_loss << '\n';
    myfile_temp << "# DHX tube forward loss:     " << Original_DHX_tube_forward_loss << '\n';
    myfile_temp << "# TCHX heat transfer length: " << Original_LTCHX << '\n';
    myfile_temp << '\n';
    myfile_temp << "Iteration number: " << iterations+1 << '\n';
    myfile_temp << "Core flowrate:      " << setw(8) << fixed << setprecision(2) << S_mflow_core << " Actual: " << setw(8) << fixed << setprecision(4) <<  mflow_core << '\n';
    myfile_temp << "Bypass flowrate:    " << setw(8) << fixed << setprecision(2) << S_mflow_bypass << " Actual: " << setw(8) << fixed << setprecision(4) << mflow_bypass << '\n';
    myfile_temp << "DHX shell flowrate: " << setw(8) << fixed << setprecision(2) << S_mflow_DHX_shell << " Actual: " << setw(8) << fixed << setprecision(4) << mflow_DHX_shell << '\n';
    myfile_temp << "DHX tube flowrate:  " << setw(8) << fixed << setprecision(2) << S_mflow_DHX_tube << " Actual: " << setw(8) << fixed << setprecision(4) << mflow_DHX_tube << '\n';
    myfile_temp << "Core inlet T:       " << setw(8) << fixed << setprecision(2) << S_Tcore_in << " Actual: " << setw(8) << fixed << setprecision(4) << Tcore_in << '\n';
    myfile_temp << "Core outet T:       " << setw(8) << fixed << setprecision(2) << S_Tcore_out << " Actual: " << setw(8) << fixed << setprecision(4) << Tcore_out << '\n';
    myfile_temp << "DHX shell inlet T:  " << setw(8) << fixed << setprecision(2) << S_TDHX_shell_in << " Actual: " << setw(8) << fixed << setprecision(4) << TDHX_shell_in << '\n';
    myfile_temp << "DHX shell outlet T: " << setw(8) << fixed << setprecision(2) << S_TDHX_shell_out << " Actual: " << setw(8) << fixed << setprecision(4) << TDHX_shell_out << '\n';
    myfile_temp << "DHX tube inlet T:   " << setw(8) << fixed << setprecision(2) << S_TDHX_tube_in << " Actual: " << setw(8) << fixed << setprecision(4) << TDHX_tube_in << '\n';
    myfile_temp << "DHX tube outlet T:  " << setw(8) << fixed << setprecision(2) << S_TDHX_tube_out << " Actual: " << setw(8) << fixed << setprecision(4) << TDHX_tube_out << '\n';
    myfile_temp << "TCHX inlet T:       " << setw(8) << fixed << setprecision(2) << S_TTCHX_in << " Actual: " << setw(8) << fixed << setprecision(4) << TTCHX_in << '\n';
    myfile_temp << "TCHX outlet T:      " << setw(8) << fixed << setprecision(2) << S_TTCHX_out << " Actual: " << setw(8) << fixed << setprecision(4) << TTCHX_out << '\n' << '\n';
    myfile_temp << "New core loss:      " << setw(8) << fixed << setprecision(5) << S_core_forward_loss << '\n';
    myfile_temp << "New bypass loss:    " << setw(8) << fixed << setprecision(5) << S_bypass_forward_loss << '\n';
    myfile_temp << "New DHX shell loss: " << setw(8) << fixed << setprecision(5) << S_DHX_shell_forward_loss << '\n';
    myfile_temp << "New DHX tube loss:  " << setw(8) << fixed << setprecision(5) << S_DHX_tube_forward_loss << '\n';
    myfile_temp << "New TCHX length:    " << setw(8) << fixed << setprecision(5) << LTCHX << '\n' << '\n';
  }
}
  else cout << "!!! Unable to write to new iteration results file.";
  
  // 8. Check if all convergence criteria were met - if they were not, return 99, else return 1. 
  int escape = 0;

  for (int i = 0; i < size_flag; i++)
  {
    if (flag[i] == 0)
       break;
    else
      escape++;
  }

  if (escape == size_flag)
    return 1;
  else
    return 99;

} 