#include <iostream>
#include <string>
#include <tuple>
#include <vector>
#include <algorithm>
#include <unordered_map>
using namespace std;


struct TreeNode
{
public:
    string ch;
    int count;
    unordered_map<string, string> table;

    TreeNode* left = NULL;
    TreeNode* right = NULL;

    TreeNode(string nodeChar, int nodeCount)
    {
        ch = nodeChar;
        count = nodeCount;
        if (ch.size() == 1) {
            table[ch] = "";
        }
    }

    void addChildren(TreeNode* L, TreeNode* R);
    void display();
private:
    tuple<vector<string>, int, int, int> displayAux();
};

void TreeNode::addChildren(TreeNode* L, TreeNode* R)
{
    left = L;
    right = R;

    unordered_map<string, string> Ltable = L->table;
    unordered_map<string, string> Rtable = R->table;

    for ( auto kv : Ltable ) {
        table[kv.first] = "0" + Ltable[kv.first];
    }

    for ( auto kv : Rtable ) {
        table[kv.first] = "1" + Rtable[kv.first];
    }
}

void TreeNode::display()
{
    auto t = displayAux();
    vector<string> lines = get<0>(t);
    int lines_size = lines.size();
    for (int i = 0; i < lines_size; i++) {
        cout << lines[i] << "\n";
    }
}

tuple<vector<string>, int, int, int> TreeNode::displayAux()
{
    if (right == NULL && left == NULL) {
        vector<string> line = { ch };
        int width = line[0].length();
        int height = 1;
        int middle = int(width / 2);

        return make_tuple(line, width, height, middle);
    }

    if (right == NULL) {
        auto t = left->displayAux();
        vector<string> lines = get<0>(t);
        int n = get<1>(t);
        int p = get<2>(t);
        int x = get<3>(t);

        string s = ch;
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

    if (left == NULL) {
        auto t = right->displayAux();
        vector<string> lines = get<0>(t);
        int n = get<1>(t);
        int p = get<2>(t);
        int x = get<3>(t);

        string s = ch;
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

    auto t = left->displayAux();
    vector<string> left_s = get<0>(t);
    int o = get<1>(t);
    int p = get<2>(t);
    int x = get<3>(t);

    auto tu = right->displayAux();
    vector<string> right_s = get<0>(tu);
    int m = get<1>(tu);
    int q = get<2>(tu);
    int y = get<3>(tu);

    string s = ch;
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

unordered_map<string, int> getCharsFreq(string message)
{
    unordered_map<string, int> charsFreq;
    for (size_t i = 0; i < message.size(); i++) {
        string ch = string(1, message[i]);
        if (charsFreq.find(ch) == charsFreq.end()) {
            charsFreq[ch] = 1;
        }
        else {
            charsFreq[ch]++;
        }
    }
    return charsFreq;
}

vector<TreeNode*> createNodes(unordered_map<string, int> charsFreq)
{
    vector<TreeNode*> nodes;
    for (auto kv : charsFreq) {
        string ch = kv.first;
        int count = kv.second;
        nodes.push_back(new TreeNode(ch, count));
    }
    return nodes;
}

struct ComparisonFunc
{
    bool operator()(TreeNode* a, TreeNode* b)
    {
        return a->count > b->count;
    }
};

TreeNode* createTree(string message)
{
    unordered_map<string, int> charsFreq = getCharsFreq(message);
    vector<TreeNode*> nodes = createNodes(charsFreq);
    ComparisonFunc comFunc = ComparisonFunc();
    make_heap(nodes.begin(), nodes.end(), comFunc);

    while (nodes.size() > 1) {
        TreeNode* smallestNode = nodes.front();
        pop_heap(nodes.begin(), nodes.end(), comFunc);
        nodes.pop_back();

        TreeNode* secondSmallestNode = nodes.front();
        pop_heap(nodes.begin(), nodes.end(), comFunc);
        nodes.pop_back();

        string newChar = smallestNode->ch + secondSmallestNode->ch;
        int newCount = smallestNode->count + secondSmallestNode->count;

        TreeNode* newNode = new TreeNode(newChar, newCount);
        newNode->addChildren(smallestNode, secondSmallestNode);

        nodes.push_back(newNode);
        push_heap(nodes.begin(), nodes.end(), comFunc);
    }
    return nodes[0];
}

tuple<string, TreeNode*> decode(string message)
{
    TreeNode* t = createTree(message);
    string output = "";

    for (size_t i = 0; i < message.size(); i++) {
        string ch = string(1, message[i]);
        output += t->table[ch];
    }
    return make_tuple(output, t);
}

string encode(string code, TreeNode* tree)
{
    string message = "";
    TreeNode* curNode = tree;

    size_t i = 0;
    while (i <= code.size()) {
        string curChar = string(1, code[i]);
        if (curChar == "0") {
            if (curNode->left != NULL) {
                curNode = curNode->left;
            } else {
                message += curNode->ch;
                curNode = tree;
                i--;
            }
        }
        else {
            if (curNode->right != NULL) {
                curNode = curNode->right;
            } else {
                message += curNode->ch;
                curNode = tree;
                i--;
            }
        }
        i++;
    }

    return message;
}

int main()
{
    string str = string(2, 'E') + string(3, 'A') +
                 string(4, 'D') + string(5, 'B') + string(6, 'C');
    cout << "Message: " << str << "\n\n";
    auto t = decode(str);
    string code = get<0>(t);
    TreeNode* tree = get<1>(t);

    tree->display();
    for ( auto kv : tree->table ) {
        cout << kv.first << ": " << kv.second << "\n";
    }

    cout << "\nDecoded message:\n" << code << "\n";

    string encoded = encode(code, tree);
    cout << "\nEncoded back:\n" << encoded << "\n";
    return 0;
}

