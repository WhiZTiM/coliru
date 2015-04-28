#include <iostream>
#include <fstream>
#include <cmath>

#define PRECISION (1.0e6)
#define SECS_PER_DAY (86400.0)

void roundEpoch(double & epoch)
{
  epoch = floor(epoch*(SECS_PER_DAY*PRECISION) + 0.5)/(SECS_PER_DAY*PRECISION);
}

int main(int argc, char * argv[])
{
  //double epoch = 25197.389756893475897345;

  double epoch = 40000.389756893475897345;//this can fail since an extra bit is needed
                                          //for the whole days piece

  roundEpoch(epoch);

  double nextEpoch = epoch;
  double nextEpochRounded = epoch;

  int intPrecision = (int)PRECISION;

  int expectedSecs = int(fmod(epoch*SECS_PER_DAY,1.0)*PRECISION + 0.5);

  std::ofstream output("D:\\epochPrecisionTest.txt");

  output << "Expected\t\t\t" <<
            "Unrounded\t\t\t" <<
            "Unrounded-Delta\t\t\t" <<
            "Rounded\t\t\t" <<
            "Rounded-Delta" << std::endl;

  for(int i = 0; i < intPrecision; i++)
  {
     double fractionalSeconds = fmod(nextEpoch*SECS_PER_DAY,1.0);
     double fractionalSecondsRounded = fmod(nextEpochRounded*SECS_PER_DAY,1.0);

     int intMinSecs = int(fractionalSeconds*PRECISION + 0.5);
     int intMinSecsRnd = int(fractionalSecondsRounded*PRECISION + 0.5);

     output << expectedSecs << "\t\t\t" <<
               intMinSecs << "\t\t\t" <<
               (intMinSecs - expectedSecs) << "\t\t\t" <<
               intMinSecsRnd << "\t\t\t" <<
               (intMinSecsRnd - expectedSecs) << std::endl;

     if((intMinSecsRnd - expectedSecs) != 0)
     {
           std::cout << "Rounded Diff" << std::endl;
     }

     nextEpoch         = nextEpoch + (1.0/PRECISION)/(SECS_PER_DAY);

     nextEpochRounded  = nextEpochRounded + (1.0/PRECISION)/(SECS_PER_DAY);

     roundEpoch(nextEpochRounded);

     expectedSecs++;

     expectedSecs = expectedSecs % intPrecision;
  }


  return 0;
}