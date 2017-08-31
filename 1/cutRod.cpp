#include <iostream>
#include <time.h>
#include <random>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

// esta funcion es muy ineficiente ya que tarda mucho tiempo en ejecutarse,
//tambien por su llamada recursiva se llama varias veces los mismos parametros
//por eso es su tiempo de ejecucion es 2ˆ(n-1).
int cutRod(int* p, int n){
    if(n==0){
        return 0;
    }
    int q=-9999;
    for(int i=0; i<n;i++){
        q= max(q,p[i]+cutRod(p,n-(i+1)));
    }
    return q;
}

//Aqui se utiliza una programacion dinamica, y tambien se llama a recursividad
//y eso hace que no sea tan eficiente aunque es mejor que la funcion cutRod.
int memoized_cutRod_aux(int* p, int n, int* r){
    if(n!=0 and r[n-1]>=0){
        return r[n-1];
    }
    int q=-9999;
    if(n==0){
        q=0;
    }
    else
    {
        for(int i=0; i<n;i++){
            q=max(q,p[i]+memoized_cutRod_aux(p,n-(i+1),r));
        }
    }
    r[n-1]=q;
    return q;
}

int memoized_cutRod(int* p, int n){
    int* r=new int [n];
    for(int i=0;i<n;i++){
        r[i]=-9999;
    }
    return memoized_cutRod_aux(p,n,r);

}

// Aqui el tiempo de ejecucion es de nˆ2, y es el mas eficiente que
//los otros dos anteriores ya que en la parte del bucle hace menos operaciones
//que en las otras funciones que se llama hasta la recursividad.
int bottom_up_cutRod(int* p, int n){
    int* r=new int [n+1];
    r[0]=0;
    for(int j=0;j<n;j++){
        int q=-9999;
        for(int i=0;i<=j;i++)
            q=max(q,p[i]+r[j-i]);
        r[j+1]=q;
    }
    return r[n];
}


int main()
{
    int var_size;
    cin>>var_size;
    int * a=new int[var_size];
    for(unsigned int i=0;i<var_size;++i)
        a[i]=10*i+rand()%10;
    cout<<"start"<<endl;
    clock_t start, end1;
    double joss_time;
        start = clock();
    //El cut rod esta comentado porque al momento de hacer las pruebas demora mucho por eso es muy ineficiente.
    //cutRod(a,var_size);
        end1 = clock();
        joss_time=end1-start;
        cout<<"cutRod: "<<joss_time/CLOCKS_PER_SEC<<endl;
        start = clock();
    memoized_cutRod(a,var_size);
        end1 = clock();
        joss_time=end1-start;
        cout<<"memorized cutRod: "<<joss_time/CLOCKS_PER_SEC<<endl;
        start = clock();
    bottom_up_cutRod(a,var_size);
        end1 = clock();
        joss_time=end1-start;
        cout<<"bottom cutRod: "<<joss_time/CLOCKS_PER_SEC<<endl;
    delete a;
    //------------------------
    //var size = 70
    //cutRod - 0.00006
    //Memoized_CutRod - 0.00005
    //Bottom_up_cutRod - 0.00005
    //------------------------
    //var size = 1800
    //cutRod - 0.00006
    //Memoized_CutRod -0.01746
    //Bottom_up_cutRod -0.008951
    system("pause");
    return 0;
}
