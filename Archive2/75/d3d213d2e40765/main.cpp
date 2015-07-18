#include <iostream>
#include <stdio.h>
#include <memory.h>

using    namespace	std;

int main()
{
    struct tm tmlol, tmloltwo;
    time_t t, u;

    // initialize declared structs
    memset(&tmlol, 0, sizeof(struct tm));
    memset(&tmloltwo, 0, sizeof(struct tm));

    strptime("10 February 2010", "%d %b %Y", &tmlol);         
    strptime("10 February 2010", "%d %b %Y", &tmloltwo);

    t = mktime(&tmlol);
    u = mktime(&tmloltwo);

    cout << t << endl;
    cout << u << endl;

    if (u>t)
    {
        cout << "true" << endl;
    }
    else if (u==t)
    {
        cout << "same" << endl;
    }
    else
    {
        cout << "false" << endl;
    }

    cout << (u-t) << endl;

    return 0;
}
