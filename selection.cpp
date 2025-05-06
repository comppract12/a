#include <iostream>
using namespace std;


class Selection_Sort
{
    public:
    void sort(int a[],int n)
    {
        cout<<"Initial Array is"<<endl;
        print(a,n);

        for(int i=0;i<n;i++)
        {
            int min_index=i;
            for(int j=i+1;j<n;j++)
            {
                if(a[j]<a[min_index])
                {
                    min_index=j;
                }
            }
            swap(a[i],a[min_index]);
        }

        cout<<"\nSorted Array is"<<endl;
        print(a,n);
       
    }

    void print(int a[],int n)
    {
        for(int i=0;i<n;i++)
        {
            cout<<a[i]<<" ";
        }
    }

};
int main()
{
    cout<<"Selection Sort"<<endl;
    Selection_Sort s=Selection_Sort();
    int a[]={8,5,6,2,7,1};
    s.sort(a,sizeof(a)/sizeof(a[0]));
    return 0;
}