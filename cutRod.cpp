#include <iostream>

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
  int * a=new int[10];
  a[0]=1;
  a[1]=5;
  a[2]=8;
  a[3]=9;
  a[4]=10;
  a[5]=17;
  a[6]=17;
  a[7]=20;
  a[8]=24;
  a[9]=30;
  int var_size=8;
  cout<<cutRod(a,var_size)<<endl;
  cout<<memoized_cutRod(a,var_size)<<endl;
  cout<<bottom_up_cutRod(a,var_size)<<endl;
  delete a;
  return 0;
}
