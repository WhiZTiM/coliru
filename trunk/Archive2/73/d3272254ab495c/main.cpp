#include <stdio.h>

typedef char sudoku[9][9];


void imprimir_casilla(int n);

void imprimir_sudoku(sudoku s)
{
    for (int i=0; i<9; ++i) {
        for (int j=0; j<9; ++j)
            imprimir_casilla(s[i][j]);
        puts("");
    }
}

void leer_linea(sudoku s, int linea);

void leer_sudoku(sudoku s)
{
    for (int i=0; i<9; ++i)
        leer_linea(s, i);
}

void leer_casilla(sudoku s, int linea, int columna);

void leer_linea(sudoku s, int linea)
{
    for (int i=0; i<9; ++i)
        leer_casilla(s, linea, i);
}

void leer_casilla_especial(sudoku s, int linea, int columna);

void leer_casilla(sudoku s, int linea, int columna)
{
    int i;
    if (1 == scanf("%d", &i))
        s[linea][columna] = i;
    leer_casilla_especial(s, linea, columna);
}

void leer_casilla_especial(sudoku s, int linea, int columna)
{
    char c = '\0';
    scanf("%c", &c);
    if (c == '?')
        s[linea][columna] = 0;
}

void imprimir_casilla(int n)
{
    if (n>0 && n<10)
        printf("%d ", n);
    else if (n == 0)
        printf("? ");
}

int main()
{
    sudoku s;
    leer_sudoku(s);
    imprimir_sudoku(s);
}
