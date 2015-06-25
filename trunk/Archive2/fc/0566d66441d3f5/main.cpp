struct wat {
    // defined
    wat() {}
};

int main()
{
    // can still copy
    wat w;
    auto copy = w;
}