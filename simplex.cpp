#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <assert.h>
#define M 20
#define N 20
using namespace std;

static const double epsilon   = 1.0e-8;
int equal(double a, double b) { return fabs(a-b) < epsilon; }
typedef struct 
{
    int m, n;
    double mat[M][N];;
}
Tableau;

void nl(int k)
{
    int j;
    for(j=0;j<k;j++)
        putchar('-');
    putchar('\n');
}

void print_tableau(Tableau *tab, const char* mes)
{
    static int counter=0;
    int i, j;
    printf("\n%d. Tabla %s:\n", ++counter, mes);
    nl(70);
    printf("%-6s%5s", "col:", "b[i]");
    for(j=1;j<tab->n; j++) 
    {
        printf("    x%d,", j);
    }
    printf("\n");
    for(i=0;i<tab->m; i++)
    {
        if (i==0)
            printf("max:");
        else if (i==0)
            printf("max:");
        else
            printf("b%d: ", i);
        
        for(j=0;j<tab->n; j++)
        {
            if (equal((int)tab->mat[i][j], tab->mat[i][j]))
                printf(" %6d", (int)tab->mat[i][j]);
            else
                printf(" %6.2lf", tab->mat[i][j]);
        }
        printf("\n");
    }
    nl(70);
}

/* Example input file for read_tableau:
 4 5
 0   -0.5  -3 -1  -4
 40    1     1  1   1
 10   -2    -1  1   1
 10    0     1  0  -1
 */
void read_tableau(Tableau *tab, const char * filename)
{
    int err, i, j;
    FILE * fp;
    fp  = fopen(filename, "r" );
    if( !fp )
    {
        printf("No se puede leer %s\n", filename); 
        exit(1);
    }
    memset(tab, 0, sizeof(*tab));
    err = fscanf(fp, "%d %d", &tab->m, &tab->n);
    if (err == 0 || err == EOF)
    {
        printf("No se puede leer m o n\n");
        exit(1);
    }
    for(i=0;i<tab->m; i++)
    {
        for(j=0;j<tab->n; j++)
        {
            err = fscanf(fp, "%lf", &tab->mat[i][j]);
            if (err == 0 || err == EOF) {
                printf("No se puede leer A[%d][%d]\n", i, j); exit(1);
            }
        }
    }
    printf("Leer tabla [%d filas x %d columnas] from file '%s'.\n", tab->m, tab->n, filename);
    fclose(fp);
}

void pivot_on(Tableau *tab, int row, int col) {
    int i, j;
    double pivot;
    
    pivot = tab->mat[row][col];
    assert(pivot>0);
    for(j=0;j<tab->n;j++)
        tab->mat[row][j] /= pivot;
    assert( equal(tab->mat[row][col], 1. ));
    
    for(i=0; i<tab->m; i++) { // foreach remaining row i do
        double multiplier = tab->mat[i][col];
        if(i==row) continue;
        for(j=0; j<tab->n; j++) { // r[i] = r[i] - z * r[row];
            tab->mat[i][j] -= multiplier * tab->mat[row][j];
        }
    }
}

int find_pivot_column(Tableau *tab)
{
    int j, pivot_col = 1;
    double lowest = tab->mat[0][pivot_col];
    for(j=1; j<tab->n; j++)
    {
        if (tab->mat[0][j] < lowest)
        {
            lowest = tab->mat[0][j];
            pivot_col = j;
        }
    }
    printf("Columnas negativas en row[0] es col %d = %g.\n", pivot_col, lowest);
    if( lowest >= 0 )
    {
        return -1;
    }
    return pivot_col;
}
    
int find_pivot_row(Tableau *tab, int pivot_col)
{
    int i, pivot_row = 0;
    double min_ratio = -1;
    printf("Relación A[row_i,0]/A[row_i,%d] = [",pivot_col);
    for(i=1;i<tab->m;i++)
    {
        double ratio = tab->mat[i][0] / tab->mat[i][pivot_col];
        printf("%3.2lf, ", ratio);
        if ( (ratio > 0  && ratio < min_ratio ) || min_ratio < 0 )
        {
            min_ratio = ratio;
            pivot_row = i;
        }
    }
    printf("].\n");
    if (min_ratio == -1)
        return -1;
    printf("Encontrar   pivot A[%d,%d], min positiva relación=%g en row=%d.\n", pivot_row, pivot_col, min_ratio, pivot_row);
    return pivot_row;
}
void add_slack_variables(Tableau *tab)
{
    int i, j;
    for(i=1; i<tab->m; i++)
    {
        for(j=1; j<tab->m; j++)
            tab->mat[i][j + tab->n -1] = (i==j);
    }
    tab->n += tab->m -1;
}

void check_b_positive(Tableau *tab)
{
    int i;
    for(i=1; i<tab->m; i++)
        assert(tab->mat[i][0] >= 0);
}

int find_basis_variable(Tableau *tab, int col)
{
    int i, xi=-1;
    for(i=1; i < tab->m; i++)
    {
        if (equal( tab->mat[i][col],1) )
        {
            if (xi == -1)
                xi=i;
            else
                return -1;
        } else if (!equal( tab->mat[i][col],0) )
        {
            return -1;
        }
    }
    return xi;
}
    
void print_optimal_vector(Tableau *tab, char *message)
{
    int j, xi;
    printf("%s en ", message);
    for(j=1;j<tab->n;j++)
    {
        xi = find_basis_variable(tab, j);
        if (xi != -1)
            printf("x%d=%3.2lf, ", j, tab->mat[xi][0] );
        else
            printf("x%d=0, ", j);
    }
    printf("\n");
}

void simplex(Tableau *tab)
{
    int loop=0;
    add_slack_variables(tab);
    check_b_positive(tab);
    print_tableau(tab,"Llenado con variables Slack");
    while( ++loop )
    {
        int pivot_col, pivot_row;
        pivot_col = find_pivot_column(tab);
        if( pivot_col < 0 )
        {
            printf("Encontrar el valor óptimo value=A[0,0]=%3.2lf (No negativos en row 0).\n", tab->mat[0][0]);
            print_optimal_vector(tab, "Vector optimo");
            break;
        }
        printf("Variable de entrada x%d que se hizo basica, entonses el pivot_col=%d.\n", pivot_col, pivot_col);
        pivot_row = find_pivot_row(tab, pivot_col);
        if (pivot_row < 0)
        {
            printf("ilimitado(no pivot_row).\n");
            break;
        }
        printf("Variable de salida x%d, entonses el pivot_row=%d\n", pivot_row, pivot_row);
        pivot_on(tab, pivot_row, pivot_col);
        print_tableau(tab,"despues del pivot");
        print_optimal_vector(tab, "Solución Básica factible");
        if(loop > 20)
        {
            printf("Muchas iteraciones > %d.\n", loop);
            break;
        }
    }
}
    
Tableau tab  = { 4, 5, {                     
    {  0.0 , -0.5 , -3.0 ,-1.0 , -4.0,   }, 
    { 40.0 ,  1.0 ,  1.0 , 1.0 ,  1.0,   }, 
    { 10.0 , -2.0 , -1.0 , 1.0 ,  1.0,   },
    { 10.0 ,  0.0 ,  1.0 , 0.0 , -1.0,   },
}
};
    
int main(int argc, char *argv[])
{
    if (argc > 1)
    {
        read_tableau(&tab, argv[1]);
    }
    print_tableau(&tab,"Inicial");
    simplex(&tab);
    return 0;
}
