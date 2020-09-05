#include <iostream>
#include <valarray>
#include <ctime>
using namespace std;


valarray<int> slicing(valarray<int> arr, int X, int Y)
{
    return arr[slice(X, Y - X, 1)];
}

void printArr(valarray<int> v)
{
    for (auto i : v) {
        cout << i << ' ';
    }
    cout << '\n';
}

void Merge(valarray<int> &arr, int l, int r)
{
    valarray<int> L;
    valarray<int> R;
    int mid;
    int i, j, k;
    int n, m;

    mid = int( (l + r) / 2 );
    L = slicing(arr, l, mid + 1);
    n = L.size();

    R = slicing(arr, mid + 1, r + 1);
    m = R.size();

    i = j = 0; k = l;

    while (i < n && j < m) {
        if (L[i] < R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < m) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void MergeSort(valarray<int> &arr, int l, int r)
{
    if (l >= r) { return; }

    int mid = int( (l + r) / 2 );
    MergeSort(arr, l, mid);
    MergeSort(arr, mid + 1, r);
    Merge(arr, l, r);
}

int main()
{
    clock_t start;
    double duration;
    int n = 10000;

    valarray<int> arr (n);
    for (int i=0; i < n; i++) { arr[i] = -i; }

    start = clock();
    MergeSort(arr, 0, n - 1);
    duration = ( clock() - start ) / double(CLOCKS_PER_SEC);
    cout << duration << endl;
}

