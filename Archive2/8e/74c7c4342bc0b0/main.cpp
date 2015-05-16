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
for_each(current_temp.begin(), current_temp.end(), [&](int v) 
       { other_temp.erase(std::remove(other_temp.begin(), other_temp.end(), v); });