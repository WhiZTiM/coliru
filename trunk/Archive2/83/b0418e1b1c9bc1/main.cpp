#include <iostream>

#define MAX_PARTITIONS 100

int count = 1;

void printSolution(int* solution, int size)
{
    std::cout << count << "| ";
    count++;
    for(int i = 0; i < size; i++)
    {
        std::cout << solution[i] << " ";
    }
    std::cout << std::endl;
}

void generatePartitions(int* solution, int number, int sum, int partitions, 
    int start)
{
    if(sum == number)
    {
        printSolution(solution, partitions);
        return;
    }
    
    solution[partitions] = start;

    while(solution[partitions] + sum < number)
    {
        solution[partitions]++;
        sum += solution[partitions];
        //std::cout << solution[partitions] << std::endl;
        generatePartitions(solution, number, sum, partitions + 1, 
            solution[partitions-1]);
        sum -= solution[partitions];
    }
}

int main(int argc, char const *argv[])
{
    int solution[MAX_PARTITIONS];

    generatePartitions(solution, 4, 0, 0, 0);

    return 0;
}