#include <iostream>

using namespace std;

void max_heapify(int *a, int i, int n){
    int l, temp;
    temp = a[i];
    l = 2*i;
    while (l <= n){
        if (l < n && a[l+1] > a[l])
            l = l+1;
        if (temp > a[l])
            break;
        else if (temp <= a[l]){
            a[l/2] = a[l];
            l = 2*l;
        }
    }
    a[l/2] = temp;
    return;
}

void build_maxheap(int *a, int n){
    int i;
    for(i = n/2; i >= 1; i--){
        max_heapify(a, i, n);
    }
}

void heapsort(int *a, int n){
    int i, temp;
    build_maxheap(a,n);
    for(i = n; i >= 2; i--){
        swap(a[1],a[i]);
        max_heapify(a, 1, i - 1);
    }
}

int main()
{
    int n, i, x;
    cout<<"Ingrese el tamano"<<" ";
    cin>>n;
    int a[20];
    for (i = 1; i <= n; i++){
        cin>>a[i];
    }
    heapsort(a, n);
    cout<<"res: ";
    for (i = 1; i <= n; i++){
        cout<<a[i]<<" ";
    }
    return 0;
}
