#include <iostream>
#include <vector>
#include <string>
#include <tuple>
#include <cmath>
#include <ctime>
using namespace std;


void printArray(vector<string> arr)
{
    for (size_t i = 0; i < arr.size(); i++) {
        cout << arr[i] << ",";
    }
    cout << "|size: " << arr.size() << endl;
}


struct TreeNode
{
public:
    int val;
    int height = 1;
    TreeNode *left = NULL;
    TreeNode *right = NULL;
    TreeNode *parent = NULL;

    TreeNode(int aVal) { val = aVal; }

    void display();
    tuple<vector<string>, int, int, int> display_aux();
};

void TreeNode::display()
{
    auto t = display_aux();
    vector<string> lines = get<0>(t);
    int lines_size = lines.size();
    for (int i = 0; i < lines_size; i++) {
        cout << lines[i] << "\n";
    }
}

tuple<vector<string>, int, int, int> TreeNode::display_aux()
{
    if (right == NULL && left == NULL) {
        vector<string> line = { to_string(val) };
        int width = line[0].length();
        int height = 1;
        int middle = int(width / 2);

        return make_tuple(line, width, height, middle);
    }

    if (right == NULL) {
        auto t = left->display_aux();
        vector<string> lines = get<0>(t);
        int n = get<1>(t);
        int p = get<2>(t);
        int x = get<3>(t);

        string s = to_string(val);
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
        auto t = right->display_aux();
        vector<string> lines = get<0>(t);
        int n = get<1>(t);
        int p = get<2>(t);
        int x = get<3>(t);

        string s = to_string(val);
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

    auto t = left->display_aux();
    vector<string> left_s = get<0>(t);
    int o = get<1>(t);
    int p = get<2>(t);
    int x = get<3>(t);

    auto tu = right->display_aux();
    vector<string> right_s = get<0>(tu);
    int m = get<1>(tu);
    int q = get<2>(tu);
    int y = get<3>(tu);

    string s = to_string(val);
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


class AVLTree
{
public:
    struct TreeNode *root;

    AVLTree() { root = NULL; }

    void insert(int key);
    TreeNode* insert(int key, TreeNode *node);

    TreeNode* search(int key, bool possibleParent);
    TreeNode* findMin();
    TreeNode* findMax();

    int getHeight(TreeNode *node);
    int countHeight(TreeNode *node);
    int getBf(TreeNode *node);
    void balance(TreeNode *node, int bf);

    void display();

private:
    void inspectChanges(TreeNode *node);
    void LLRotate(TreeNode *node);
    void RRRotate(TreeNode *node);
    void LRRotate(TreeNode *node);
    void RLRotate(TreeNode *node);
};

void AVLTree::insert(int key)
{
    if (root == NULL) {
        root = new TreeNode(key);
        return;
    }
    TreeNode *node = insert(key, root);
    inspectChanges(node);
}

TreeNode* AVLTree::insert(int key, TreeNode *node)
{
    while (true) {
        if (key > node->val) {
            if (node->right == NULL) {
                node->right = new TreeNode(key);
                node->right->parent = node;
                return node;
            }
            node = node->right;
        }

        else if (key < node->val) {
            if (node->left == NULL) {
                node->left = new TreeNode(key);
                node->left->parent = node;
                return node;
            }
            node = node->left;
        }
    }
}

TreeNode* AVLTree::search(int key, bool possibleParent=false)
{
    TreeNode *node;
    TreeNode *prevNode;

    node = prevNode = root;
    while (node != NULL) {
        if (key > node->val) {
            prevNode = node;
            node = node->right;
        }
        else if (key < node->val) {
            prevNode = node;
            node = node->left;
        }
        else {
            return node;
        }
    }

    if (possibleParent) { return prevNode; }
    return NULL;
}

TreeNode* AVLTree::findMin()
{
    TreeNode *node = root;
    while (true) {
        if (node->left == NULL) { return node; }
        node = node->left;
    }
}

TreeNode* AVLTree::findMax()
{
    TreeNode *node = root;
    while (true) {
        if (node->right == NULL) { return node; }
        node = node->right;
    }
}

void AVLTree::inspectChanges(TreeNode *node)
{
    if (node == NULL) { return; }

    int bf = getBf(node);
    if (abs(double(bf)) > 1) { return balance(node, bf); }

    int newHeight = countHeight(node);
    if (newHeight != node->height) {
        node->height = newHeight;
        inspectChanges(node->parent);
    }
}

int AVLTree::getHeight(TreeNode *node)
{
    if (node == NULL){
        return 0;
    }
    return node->height;
}

int AVLTree::countHeight(TreeNode *node)
{
    if (node->left == NULL || node->right == NULL) {
        if (node->left != NULL && node->right == NULL) {
            return node->left->height + 1;;
        }
        if (node->left == NULL && node->right != NULL) {
            return node->right->height + 1;
        }
        return 1;
        }
    int leftHeight = node->left->height;
    int rightHeight = node->right->height;
    int maxHeight = (leftHeight > rightHeight ? leftHeight : rightHeight);
    return maxHeight + 1;
}

int AVLTree::getBf(TreeNode *node)
{
    return getHeight(node->left) - getHeight(node->right);
}

void AVLTree::balance(TreeNode *node, int bf)
{
    if (bf > 0) {
        if (getBf(node->left) >= 0) {
            return LLRotate(node);
        }
        return LRRotate(node);
    } else {
        if (getBf(node->right) <= 0) {
            return RRRotate(node);
        }
        return RLRotate(node);
    }
}

void AVLTree::LLRotate(TreeNode *node)
{
    TreeNode *A = node;
    TreeNode *B = A->left;
    if (A->parent != NULL) {
        if (A->parent->left == A) {
            A->parent->left = B;
        } else {
            A->parent->right = B;
        }
    } else { root = B; }

    if (B->right != NULL) { B->right->parent = A; }
    B->parent = A->parent;
    A->parent = B;

    A->left = B->right;
    B->right = A;

    A->height = countHeight(A);
    B->height = countHeight(B);
    inspectChanges(B->parent);
}

void AVLTree::RRRotate(TreeNode *node)
{
    TreeNode *A = node;
    TreeNode *B = A->right;
    if (A->parent != NULL) {
        if (A->parent->left == A) {
            A->parent->left = B;
        } else {
            A->parent->right = B;
        }
    } else { root = B; }

    if (B->left != NULL) { B->left->parent = A; }
    B->parent = A->parent;
    A->parent = B;

    A->right = B->left;
    B->left = A;

    A->height = countHeight(A);
    B->height = countHeight(B);
    inspectChanges(B->parent);
}

void AVLTree::LRRotate(TreeNode *node)
{
    TreeNode *A = node;
    TreeNode *B = A->left;
    TreeNode *C = B->right;
    if (A->parent != NULL) {
        if (A->parent->left == A) {
            A->parent->left = C;
        } else {
            A->parent->right = C;
        }
    } else { root = C; }

    if (C->right != NULL) { C->right->parent = A; }
    if (C->left != NULL) { C->left->parent = B; }

    B->parent = C;
    C->parent = A->parent;
    A->parent = C;

    A->left = C->right;
    B->right = C->left;
    C->right = A;
    C->left = B;

    A->height = countHeight(A);
    B->height = countHeight(B);
    C->height = countHeight(C);
    inspectChanges(C->parent);
}

void AVLTree::RLRotate(TreeNode *node)
{
    TreeNode *A = node;
    TreeNode *B = A->right;
    TreeNode *C = B->left;
    if (A->parent != NULL) {
        if (A->parent->left == A) {
            A->parent->left = C;
        } else {
            A->parent->right = C;
        }
    } else { root = C; }

    if (C->right != NULL) { C->right->parent = B; }
    if (C->left != NULL) { C->left->parent = A; }

    B->parent = C;
    C->parent = A->parent;
    A->parent = C;

    A->right = C->left;
    B->left = C->right;
    C->right = B;
    C->left = A;

    A->height = countHeight(A);
    B->height = countHeight(B);
    C->height = countHeight(C);
    inspectChanges(C->parent);
}

void AVLTree::display()
{
    if (root != NULL) {
        root->display();
    }
    else {
        cout << "-" << endl;
    }
}

int main()
{
    AVLTree t = AVLTree();
    clock_t start;
    double duration;

    start = clock();
    for (int i = 0; i < 100; i++) {
        t.insert(i);
    }
    t.display();

    duration = ( clock() - start ) / (double) CLOCKS_PER_SEC;
    cout << duration << endl;
}

