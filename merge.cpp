#include <iostream>
using namespace std;




void mergee (int* a, int p, int q, int r){

    int n1,n2,i,j,k,inf=9999;

    n1=q-p+1;

    n2=r-q;



    int *L=new int[n1+1];

    int *R = new int[n2+1];



    for(i=0; i<n1; i++){

        L[i]=a[p+i];

    }



    for(j=0; j<n2; j++){

        R[j]=a[q+1+j];

    }



    L[n1]=inf;
    R[n2]=inf;

    i=0;j=0;



    for(k=p;k<=r;k++){

        if(L[i]<=R[j]){

            a[k]=L[i];

            i=i+1;
        }

        else{

            a[k]=R[j];
            j=j+1;

        }

    }

}




void mergesort(int* a,int p,int r){

    int q;

    if(p<r){

        q=(p+r)/2;

        mergesort(a,p,q);
        mergesort(a,q+1,r);
        mergee(a,p,q,r);

    }



}



int main()
{

    int arr[]={6,9,10,5,4,3,2,1,7,8,11};

    mergesort(arr,0,11);



    for(int i=0; i<11; i++){
        cout << arr[i]<<" ";
    }


    return 0;
}
