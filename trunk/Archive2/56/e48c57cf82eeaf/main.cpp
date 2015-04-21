/*
123456789
123456789
123456789
123456789
123456789
123456789
123456789
123456789
123456789
*/

#include <stdbool.h>
#include <stdio.h>

typedef struct
{
    int box[9][9];
} Sudoku;

bool read_puzzle( Sudoku* p, FILE* f )
{
	if(!f) return false;

	for(int y=0;y<9;++y)
	{
		for(int x=0;x<9;++x)
		{
			int c = fgetc(f);
			if( c == EOF ) return false;
			if( c < '1'  ) return false;
			if( c > '9'  ) return false;
			p->box[y][x] = c-'0';
		}
		if( fgetc(f) != '\n' ) return false;
	}
	return true;
}

int main(int argc, char** argv)
{
    Sudoku s;
    if(argc==2)
    {
        FILE* fp = fopen(argv[1],"rt");
        fseek(fp,3,SEEK_SET);
        if( read_puzzle( &s, fp ) )
        {
            printf("all ok");
            for(int y=0;y<9;++y)
            {
                for(int x=0;x<9;++x)
                {
                    printf("%d",s.box[y][x]);
                }
                printf("\n");
            }
            return 0;
        }
    }
    printf("failed");
}



