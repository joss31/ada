#include <iostream>
#include <math.h>
using namespace std;

int * longestISeq(int *X,int N){
    int L,newL,lo,hi,mid,k;
    int *P= new int[N];
    int *M= new int[N+1];
    L=0;
    for (int i=0;i<N;i++)
    {
        lo=1;
        hi=L;
        while (lo <= hi)
        {
            mid=ceil((lo+hi)/2);
            if(X[M[mid]] < X[i])
                lo = mid +1;
            else
                hi = mid-1;
        }
        newL=lo;
        P[i] = M[newL-1];
        M[newL]=i;
        if(newL > L)
            L=newL;
    }

    int *S= new int[L];
    k=M[L];

    for(int i=(L-1);i>=0;i--){
        S[i]=X[k];
        k=P[k];
    }

    return S;

}
int main()
{
    int A[16]={0, 8, 4, 12, 2, 10, 6, 14, 1, 9, 5, 13, 3, 11, 7, 15};
    int* S=longestISeq(A,16);
    for(unsigned int i=0;i<6;++i)
        cout<<S[i]<<endl;
    return 0;
}
