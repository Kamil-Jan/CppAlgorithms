#include <iostream>
#include <string>
#include <tuple>
#include <vector>
using namespace std;

void printArray(vector<int> arr) {
    for (size_t i = 0; i < arr.size(); i++) {
        cout << arr[i] << " ";
    }
    cout << "\n";
}

class MaxHeap {
public:
    void heapify(vector<int> &arr, int n, int i);
    void build(vector<int> &arr);
    void insert(vector<int> &arr, int key);
    int extract_root(vector<int> &arr);
    void display(vector<int> arr);
private:
    tuple<vector<string>, int, int, int> display_aux(vector<int> arr, int i=0);
};

void MaxHeap::heapify(vector<int> &arr, int n, int i)
{
    int l = 2 * i + 1;
    int r = 2 * i + 2;
    int largest = i;
    bool left = l < n;
    bool right = r < n;

    if (left && arr[l] > arr[largest]) {
        largest = l;
    }

    if (right && arr[r] > arr[largest]) {
        largest = r;
    }

    if (largest != i) {
        int temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;
        heapify(arr, n, largest);
    }
}

void MaxHeap::build(vector<int> &arr)
{
    int length = arr.size();
    for (int start = int(length / 2); start > -1; start--) {
        heapify(arr, length, start);
    }
}

void MaxHeap::insert(vector<int> &arr, int key)
{
    arr.push_back(key);
    int length = arr.size();
    int i = int((length - 2) / 2);
    while (i >= 0 && key > arr[i]) {
        heapify(arr, length, i);
        i = int((i - 1) / 2);
    }
}

int MaxHeap::extract_root(vector<int> &arr)
{
    int last_idx = arr.size() - 1;
    int temp = arr[0];
    arr[0] = arr[last_idx];
    arr[last_idx] = temp;

    arr.pop_back();
    heapify(arr, last_idx, 0);
    return temp;
}

void MaxHeap::display(vector<int> arr)
{
    if (arr.size() > 0) {
        auto t = display_aux(arr);
        vector<string> lines = get<0>(t);
        int lines_size = lines.size();
        for (int i = 0; i < lines_size; i++) {
            cout << lines[i] << "\n";
        }
    }
    else {
        cout << "-" << "\n";
    }
}

tuple<vector<string>, int, int, int> MaxHeap::display_aux(vector<int> arr, int i)
{
    int n = arr.size();
    int l = 2 * i + 1;
    int r = 2 * i + 2;
    bool left = l < n;
    bool right = r < n;

    if (!right && !left) {
        vector<string> line = { to_string(arr[i]) };
        int width = line[0].length();
        int height = 1;
        int middle = int(width / 2);
        return make_tuple(line, width, height, middle);
    }

    if (!right) {
        auto t = display_aux(arr, l);
        vector<string> lines = get<0>(t);
        int n = get<1>(t);
        int p = get<2>(t);
        int x = get<3>(t);

        string s = to_string(arr[i]);
        int u = s.size();

        string first_line = string(x + 1, ' ') + string(n - x - 1, '_') + s;
        string second_line = string(x, ' ') + '/' + string(n - x - 1 + u, ' ');
        vector<string> shifted_lines;
        int lines_size = lines.size();

        for (int k = 0; k < lines_size; k++) {
            shifted_lines.push_back(lines[k] + string(u, ' '));
        }

        vector<string> two_lines = { first_line, second_line };
        vector<string> output_lines;
        output_lines.reserve( two_lines.size() + shifted_lines.size() );
        output_lines.insert( output_lines.end(), two_lines.begin(), two_lines.end() );
        output_lines.insert( output_lines.end(), shifted_lines.begin(), shifted_lines.end() );

        return make_tuple(output_lines, n + u, p + 2, n + int(u / 2));
    }

    if (!left) {
        auto t = display_aux(arr, r);
        vector<string> lines = get<0>(t);
        int n = get<1>(t);
        int p = get<2>(t);
        int x = get<3>(t);

        string s = to_string(arr[i]);
        int u = s.size();

        string first_line = s + string(x, '_') + string(n - x, ' ');
        string second_line = string(u + x, ' ') + '\\' + string(n - x - 1, ' ');
        vector<string> shifted_lines;
        int lines_size = lines.size();

        for (int k = 0; k < lines_size; k++) {
            shifted_lines.push_back(string(u, ' ') + lines[k]);
        }

        vector<string> two_lines = { first_line, second_line };
        vector<string> output_lines;
        output_lines.reserve( two_lines.size() + shifted_lines.size() );
        output_lines.insert( output_lines.end(), two_lines.begin(), two_lines.end() );
        output_lines.insert( output_lines.end(), shifted_lines.begin(), shifted_lines.end() );

        return make_tuple(output_lines, n + u, p + 2, int(u / 2));
    }

    auto t = display_aux(arr, l);
    vector<string> left_s = get<0>(t);
    int o = get<1>(t);
    int p = get<2>(t);
    int x = get<3>(t);

    auto tu = display_aux(arr, r);
    vector<string> right_s = get<0>(tu);
    int m = get<1>(tu);
    int q = get<2>(tu);
    int y = get<3>(tu);

    string s = to_string(arr[i]);
    int u = s.size();
    string first_line = string(x + 1, ' ') + string(o - x - 1, '_') + s + string(y, '_') + string(m - y, ' ');
    string second_line = string(x, ' ') + '/' + string(o - x - 1 + u + y, ' ') + '\\' + string(m - y - 1, ' ');

    if (p < q) {
        int k = 0;
        while (k < q - p) {
            left_s.push_back(string(o, ' '));
            k++;
        }
    }
    else if (q < p) {
        int k = 0;
        while (k < p - q) {
            right_s.push_back(string(m, ' '));
            k++;
        }
    }

    int k = 0;
    vector<tuple<string, string>> zipped_lines;
    int lines_size = left_s.size();
    while (k < lines_size) {
        zipped_lines.push_back(make_tuple(left_s[k], right_s[k]));
        k++;
    }

    vector<string> shifted_lines;
    for (int j = 0; j < lines_size; j++) {
        auto t = zipped_lines[j];
        string a = get<0>(t);
        string b = get<1>(t);

        string shifted_line = a + string(u, ' ') + b;
        shifted_lines.push_back(shifted_line);
    }

    vector<string> two_lines = { first_line, second_line };
    vector<string> output_lines;
    output_lines.reserve( two_lines.size() + shifted_lines.size() );
    output_lines.insert( output_lines.end(), two_lines.begin(), two_lines.end() );
    output_lines.insert( output_lines.end(), shifted_lines.begin(), shifted_lines.end() );

    int max_child_height = (p > q)? p: q;
    return make_tuple(output_lines, o + m + u, max_child_height + 2, o + int(u / 2));
}

int main()
{
    MaxHeap x = MaxHeap();
    vector<int> arr;
    for (int i = 0; i < 30; i++) {
        arr.push_back(i);
    }

    x.build(arr);
    x.display(arr);
    return 0;
}

