#include <stdio.h>

typedef char fila_sudoku[9];
typedef fila_sudoku sudoku[9];

int comprobar_fila(fila_sudoku s);

int comprobar_filas(sudoku s)
{
    for (int i=0; i<9; ++i)
        if (!comprobar_fila(s[i]))
            return 0;
    return 1;
}

int comprobar_fila(fila_sudoku s)
{
    int c[9] = {0};
    for (int i=0; i<9; ++i)
        if (s[i] > 0 && s[i] < 10)
            ++c[s[i] - 1];
    
    for (int i=0; i<9; ++i)
        if (c[i] != 1)
            return 0;
    return 1;
}

int comprobar_columna(sudoku s, int col);

int comprobar_columnas(sudoku s)
{
    for (int i=0; i<9; ++i)
        if (!comprobar_columna(s, i))
            return 0;
    return 1;
}

int comprobar_columna(sudoku s, int col)
{
    fila_sudoku f;
    for (int i=0; i<9; ++i)
        f[i] = s[i][col];
    return comprobar_fila(f);
}


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
    printf("Filas %s\n", comprobar_filas(s)?"correctas":"incorrectas");
    printf("Columnas %s\n", comprobar_columnas(s)?"correctas":"incorrectas");
}
