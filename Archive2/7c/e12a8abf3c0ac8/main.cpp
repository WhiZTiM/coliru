#include <iostream>

template <int W, int H>
void solve( int (&a)[W][H] )
{
    int buffer[W][H] = {{}};
    for (int i = 0; i < W; ++i)
        buffer[0][i]=a[0][i];
    for (int i = 1; i < H; ++i)
        buffer[i][0]=a[i][0];    
    
    int max = 0;
    
    for ( int i = 1; i < W; ++i)
    {
        for ( int j = 1; j < H; ++j )
        {
            if ( a[i-1][j] && a[i][j-1] && a[i-1][j-1] && a[i][j] )
            {
                if ( buffer[i-1][j] == buffer[i][j-1] && buffer[i-1][j] == buffer[i-1][j-1] )
                    buffer[i][j] = buffer[i-1][j] + 1;
                else
                    buffer[i][j] = std::max(std::max(buffer[i-1][j],buffer[i][j-1]),buffer[i-1][j-1]);
            }
            else
                buffer[i][j] = a[i][j];
            
            // std::cout << buffer[i][j] << " ";
            
        }
        // std::cout << std::endl;
    }
    
    for( int i = 0; i < W; ++i )
        for ( int j = 0; j < H; ++j )
            if ( buffer[i][j] > max )
                max = buffer[i][j];
    
    std::cout << "Max square = " << max * max << std::endl; 
}

int main()
{
    int data[][5] = 
        {
            {0,1,1,1,1},
            {1,0,1,1,1},
            {0,1,1,1,1},
            {1,1,1,0,1},
            {0,1,0,1,0}
        };
    solve(data);
}