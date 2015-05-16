//Compare other_temp and current_temp.  If there is a similar number,
//  remove it from current.  Start at end of vectors.
for (int y = other_temp.size(); y > 0; y--)
{
    for (int z = current_temp.size(); z > 0; z--)
    {
        //If the numbers are equal.
        if (current_temp[z - 1] == other_temp[y - 1])
        {
            //Remove from current_temp vector.
            current_temp.erase(current_temp.begin() + z - 1);
        }
    }
}
//...
// That loop can be rewritten:
#include <algorithm>
//...
for_each(other_temp.begin(), other_temp.end(), [&](int v) 
       { current_temp.erase(std::remove(current_temp.begin(), current_temp.end(), v); });
       
//... or
size_t numItems = other_temp.size();
for (size_t i = 0; i < numItems; ++i )
    current_temp.erase(std::remove(current_temp.begin(), current_temp.end(), other_temp[i]));