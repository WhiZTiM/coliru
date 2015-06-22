
#include<iostream>
#include<algorithm>

bool mycomp(int i, int j)
{
    return (((i < 0) && (j > 0)) || ((i > 0) && (j < 0)));
}

int main()
{
int counter, size, *guests;
for (int i = 2; i <= 9; i++)
{
    size = i * 2;
    counter = 1;
    guests = new int[size];
    for (int j = 0; j < size; j += 2)
    {
        guests[j] = counter;
        guests[j + 1] = 0 - counter;
        ++counter;
    }
    std::sort(guests, guests + size);
    counter = 0;
    while (std::next_permutation(guests, guests + size, mycomp))
    {
        ++counter;
    }
}
}
