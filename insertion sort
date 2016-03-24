+#include <iostream>
using namespace std;

void insertionsort(int a[],int t){

    int i=0,j,key;

    for(j=2;j<t;j++){

        key = a[j];

        i=j-1;

        while (i>=0&&a[i]>key){

            a[i+1]=a[i];

            i=i-1;

        }

        a[i+1]=key;
    }

}



int main()

{

    int a[]={31,41,59,26,41,58};

    insertionsort(a,6);

    for(int i=0;i<6;i++){

        cout<<a[i]<<" ";
    }

    return 0;
}
