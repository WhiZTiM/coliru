class Student
{
public:
    int roll;
    int marks;

    Student()
    {
        roll = 10;
        marks = 0;
    }
};    

int main()
{
    printf("Hello, World!\n");
    int iCounter;

    char attr[][6] = {"roll", "marks"};

    Student std;

#define PRINT1(std, X) printf("%d", std.##X);
    for (iCounter = 0; iCounter < 2; iCounter++)
    {
        PRINT1(std, attr[iCounter])
    }

    return 0;
}