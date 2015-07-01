struct AA
{
    AA() = delete;
    int r;
};

int main()
{    
    AA aa{};
    
    (void)aa;
}
