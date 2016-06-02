#include <iostream>

using namespace std;

void recursiveActivitySelector (int s[],int f[],int k, int n, int a[])
{
    	int m=k+1;
    	while ((m<=n) && (s[m] < f[k]))
    	{
        m=m+1;
    	}
    	if(m<=n)
    	{
        a[m]=1;
        recursiveActivitySelector(s,f, m, n, a);
    	}
}


void greedyActivitySelector(int s[],int tam, int f[],int a[])
{
    	int n=tam;
   	int k=1;
    	for(int m=2;m<n;m++)
    	{
        if(s[m] >= f[k])
	   {
            a[m]=1;
            k=m;
        }
    	}
}



int main() {

    	int a1[] = {1,0,0,0,0,0,0,0,0};
    	int a2[] = {1,0,0,0,0,0,0,0,0};
    	int s[] = {1,2,4,1,5,8,9,11,13};
    	int f[] = {3,5,7,8,9,10,11,14,16};

    	int n =9;

    	recursiveActivitySelector(s, f, 0, n, a1);
    	for (int i=0;i<n;i++)
	{
        if (a1[i] == 1)
            cout<<i+1<<" ";
    	}
    	cout<<endl;
    	greedyActivitySelector(s,n, f, a2);
    	for (int i=0;i<n;i++){
        if (a2[i] == 1)
            cout<<i+1<<" ";
    	}


    return 0;

}
