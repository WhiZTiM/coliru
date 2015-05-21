int main(int argc, char **argv)
{
    const char aChar = 5;
    enum 
    {
        firstVal = 1 & aChar,
        secondVal = 1 & "WOW"[0]
    }; 
}