template<int dim, int loop>
class Partition{
    // ...
public:
    // ...
    template<int r, int c> using matrix = int[r][c];
    template<int r, int c> void readPattern(const matrix<r,c> &pattern)
    {
       // ...
    }
    // ...
};

int main()
{
    const int DENOISE_UR[3][4] = {/*...*/};
    Partition<1,2> partition;
    partition.readPattern(DENOISE_UR);
}