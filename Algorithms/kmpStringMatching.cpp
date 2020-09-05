#include <iostream>
#include <string>


void createLPSTable(std::string pattern, int M, int* lps)
{
    lps[0] = 0;
    int length = 0;

    int i = 1;
    while (i < M) {
        if (pattern[i] == pattern[length]) {
            length++;
            lps[i] = length;
            i++;
        } else {
            if (length != 0) {
                length = lps[length - 1];
            } else {
                lps[i] = 0;
                i++;
            }
        }
    }
}

void search(std::string pattern, std::string str)
{
    int M, N;
    int i, j;
    M = pattern.size();
    N = str.size();

    int lps[M];
    createLPSTable(pattern, M, lps);

    i = j = 0;
    while (i < N) {
        if (str[i] == pattern[j]) {
            i++;
            j++;
        }

        if (j == M) {
            std::cout << "Pattern found between " << i - j;
            std::cout << " and " << i - j + M - 1 << std::endl;
            j = lps[j - 1];
        }

        else if (i < N && str[i] != pattern[j]) {
            if (j != 0)
                j = lps[j - 1];
            else
                i++;
        }
    }
}

int main()
{
    std::string a;
    std::string pat;

    a = "Vadim ebaniy endon i gandon!!!";
    pat = "nd";

    search(pat, a);
    return 0;
}
