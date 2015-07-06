struct UWidthsbase_t
{
    int collapsed;
    int expanded;
};

struct UWidths_t
{
    UWidthsbase_t group;
    UWidthsbase_t terrain;
    UWidthsbase_t uConst;
};

int main()
{
    UWidths_t UWidths { {31, 100}, {31, 120}, {31, 140}};
    UWidthsbase_t * pUWidthsClass = &UWidths.group;
    UWidthsbase_t * pUWidthsTerrain = &UWidths.terrain;
    UWidthsbase_t * pUWidthsConst = &UWidths.uConst;
}
