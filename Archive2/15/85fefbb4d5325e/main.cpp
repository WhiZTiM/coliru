#include <iostream>    
#include <string>

using namespace std;

    void sortScore(int *score, int size, string* name)
    {
        int startScan, minIndex;
        int minValue;
        string minName;

        for (startScan = 0; startScan<(size - 1); startScan++)
        {
            minIndex = startScan;
            minValue = score[startScan];

            for (int index = startScan + 1; index<size; index++)
            {
                if (score[index]<minValue)
                {
                    minValue = score[index];
                    minIndex = index;
                    minName = name[index];
                }
            }
            score[minIndex] = score[startScan];
            score[startScan] = minValue;
            name[minIndex] = name[startScan];
            name[startScan] = minName;
        }

    }

int main()
{
   int scores[] = {10, 30, 5, 15};
   string names[] = {"a", "b", "c", "d"};
   
   sortScore(scores, 4, names);
   
   for (int i = 0; i < 4; ++i) {
       cout << names[i] << " " << scores[i] << '\n';
   }
}