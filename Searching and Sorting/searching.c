#include<stdio.h>

int linearSearch(int arr[], int n, int key)
{
    for(int i=0;i<n;i++)
    {
        if(arr[i] == key)
            return i;
    }
    return -1;
}
int isSorted(int arr[],int n)
{
    for(int i=0;i<n-1;i++)
    {
        if(arr[i]>arr[i+1])
            return 0;
    }

    return 1;
}

int binarySearch(int arr[], int n, int key)
{
    int s = 0, e = n-1;

    if(!isSorted(arr,n))
        return -1;
        
    while(s<=e)
    {
        int mid = s + (e-s)/2;

        if(arr[mid] == key)
            return mid;
        if(arr[mid] > key)
            e = mid-1;
        
        if(arr[mid] < key)
            s = mid+1;
    }

}