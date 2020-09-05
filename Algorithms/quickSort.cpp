#include <iostream>
#include <valarray>
#include <ctime>
using namespace std;


int Partition(valarray<int> arr, int l, int h)
{
    int pivot = arr[h];
    int i = l;

    for (int j=l; j < h; j++)
        if (arr[j] < pivot) {
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
            i++;
        }

    int temp = arr[i];
    arr[i] = arr[h];
    arr[h] = temp;
    return i;
}

void QuickSort(valarray<int> arr, int l, int h)
{
    if (l >= h) { return; }

    int j = Partition(arr, l, h);
    QuickSort(arr, l, j - 1);
    QuickSort(arr, j + 1, h);
}

void printArr(valarray<int> v)
{
    for (auto i : v) {
        cout << i << ' ';
    }
    cout << '\n';
}

int main()
{
    clock_t start;
    double duration;
    int n = 10000;

    valarray<int> arr (n);
    for (int i=0; i < n; i++) { arr[i] = -i; }

    start = clock();
    QuickSort(arr, 0, n - 1);
    duration = ( clock() - start ) / (double) CLOCKS_PER_SEC;
    cout << duration;
}

