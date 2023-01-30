#include <iostream>
#include <chrono>
#include <algorithm>
#include <vector>
using namespace std::chrono;
using namespace std;

int binary_search(int arr[], int left, int right, int element);
void insertion_sort_binary_search(int arr[],int n);
void insertion_sort_linear_search(int arr[],int n);
void testCases();
void print(int arr[],int n);

int main()
{
    int *arr, size;
    auto random = []() -> int { return rand() % 10000; };
    cout << "Enter the size of array: ";
    cin >> size;
    arr = new int[size];
    generate(arr, arr + size, random);

    auto start_linear = high_resolution_clock::now();
    insertion_sort_linear_search(arr, size);
    auto end_linear = high_resolution_clock::now();
    auto duration_linear = duration_cast<microseconds>(end_linear - start_linear);
    cout << "Linear Search " << duration_linear.count() << " microseconds\n";

    auto start_binary = high_resolution_clock::now();
    insertion_sort_binary_search(arr, size);
    auto end_binary = high_resolution_clock::now();
    auto duration_binary = duration_cast<microseconds>(end_binary - start_binary);
    cout << "Binary Search " << duration_binary.count() << " microseconds\n";

    testCases();

    return 0;
}

int binary_search(int arr[], int left, int right, int element)
{
    int middle;
    while (left <= right)
    {
        middle = (left + right) / 2;

        if (arr[middle] < element && arr[middle+1]>=element)
        {
            return middle+1;
        }

        if (arr[middle] > element)
        {
            right = middle - 1;
        }

        else
        {
            left = middle + 1;
        }

    }
    return middle;
}

void insertion_sort_binary_search(int arr[],int n)
{
    int temp;
    for (int right = 1,left=0; right < n; right++)
    {
        temp=arr[right];
        int index = binary_search(arr,left,right,temp);
        for (int i = right; i >index; i--)
        {
            arr[i]=arr[i-1];
        }
        arr[index]=temp;
    }
}

void insertion_sort_linear_search(int arr[],int n)
{
    int temp;
    for (int i = 1,j; i < n; ++i)
    {
        temp=arr[i];
        for (j=i-1; j >=0 && temp<arr[j]; j--)
        {
            arr[j+1]=arr[j];

        }
        arr[j+1]=temp;
    }
}

void testCases()
{
    cout<<"------------------------------------------------------------\n";
    cout<<"Test Case1: \n";
    int a1[5]={3,7,5,-8,-6};
    cout<<"The Array Before sorting: ";
    print(a1,5);
    insertion_sort_binary_search(a1,5);
    cout<<"The Array After sorting with insertion sort using binary search: ";
    print(a1,5);

    cout<<"------------------------------------------------------------\n";
    cout<<"Test Case2: \n";
    int a2[5]={1,3,4,5,2};
    cout<<"The Array Before sorting: ";
    print(a2,5);
    insertion_sort_binary_search(a2,5);
    cout<<"The Array After sorting with insertion sort using binary search: ";
    print(a2,5);

    cout<<"------------------------------------------------------------\n";\
    cout<<"Test Case3: \n";
    int a3[7]={0,10,20,30,40,50,60};
    cout<<"The Array Before sorting: ";
    print(a3,7);
    insertion_sort_binary_search(a3,7);
    cout<<"The Array After sorting with insertion sort using binary search: ";
    print(a3,7);

    cout<<"------------------------------------------------------------\n";
    cout<<"Test Case4: \n";
    int a4[4]={15,7,1,0};
    cout<<"The Array Before sorting: ";
    print(a4,4);
    insertion_sort_binary_search(a4,4);
    cout<<"The Array After sorting with insertion sort using binary search: ";
    print(a4,4);
}

void print(int arr[],int n)
{
    for (int i = 0; i <n ; ++i)
    {
        cout<<arr[i]<<" ";
    }
    cout<<endl;
}
