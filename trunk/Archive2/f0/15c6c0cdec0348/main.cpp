struct sample {
        char brand[20];
        char specs[20];
        float price;
};

int main()
{
    sample* plants = new sample[10]{"could also", "do this", 3.14f};
    plants[0] = { "mamama", "dadada", 3.14f };
}
