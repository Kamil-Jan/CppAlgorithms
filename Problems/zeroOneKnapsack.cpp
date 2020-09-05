#include <iostream>
#include <cmath>
using namespace std;


int max(int a, int b)
{
    if (a > b) { return a; }
    return b;
}

void printMatrix(int** V, size_t rows, size_t cols)
{
    for (size_t i=0; i < rows; i++) {
        for  (size_t j=0; j < cols; j++) {
            if (V[i][j] < 10) {
                cout << " " << V[i][j] << " ";
            } else {
                cout << V[i][j] << " ";
            }
        }
        cout << endl;
    }
}

int** knapsackProblem(int n, int profits[], int weights[], int W)
{
    int** V = 0;
    V = new int *[n + 1];

    for (int i=0; i <= n; i++) {
        V[i] = new int[W + 1];
        for (int w=0; w <= W; w++) {
            if (i == 0 || w == 0) {
                V[i][w] = 0;
            } else if (weights[i - 1] <= w) {
                int product_weight = weights[i - 1];
                V[i][w] = max(V[i - 1][w - product_weight] + profits[i - 1],
                              V[i - 1][w]);
            } else {
                V[i][w] = V[i - 1][w];
            }
        }
    }

    return V;
}

int main()
{
    int p[] = { 1, 2, 5, 6 };
    int w[] = { 2, 3, 4, 5 };
    int n = sizeof(p) / sizeof(p[0]);
    int W = 8;

    int** V = knapsackProblem(n, p, w, W);
    printMatrix(V, n + 1, W + 1);

    cout << "\nMax Profit: " << V[n][W];

    return 0;
}

