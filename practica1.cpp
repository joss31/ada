#include <iostream>

using namespace std;

int findMSubarray(int A[], int l, int h){
  int sum,lef,rig,n,i,j;
  lef=0;
  rig=0;
  sum = -99999;
  for(i=l; i<h;i++){
      n= 0;
      for(j=i;j<h;j++)
        n+= A[j];
      if (sum < (n))
          sum = n;
      lef=i;
      rig=j;
  }
  return sum;
}



int main()
{
    int a[5]={13,3,2,20,-3};
    cout<<findMSubarray(a,0,5);

    return 0;
}
