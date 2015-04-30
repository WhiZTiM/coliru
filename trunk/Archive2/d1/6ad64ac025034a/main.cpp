#include <stdio.h>
//#include <wiringPi.h>

#include <fstream>
#include <iostream>

int main ()
{

//  wiringPiSetup ();

  char instructions[100];

  ifstream b_file ( "instructions.txt" );
  b_file>> instructions;
  cout<< instructions <<"\n";

}