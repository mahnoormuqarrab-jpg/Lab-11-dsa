#include <iostream>
using namespace std;
struct Node {
    char ch;
    int freq;
    Node* left;
    Node* right;
};
Node* makeNode(char c, int f) {
    Node* n = new Node;
    n->ch = c;
    n->freq = f;
    n->left = NULL;
    n->right = NULL;
    return n;
}
// min heap (array based)
Node* heap[100];
int heapSize = 0;
void insertHeap(Node* n) {
    heap[heapSize] = n;
    int i = heapSize;
    heapSize++;
    // move up while parent is bigger
    while (i > 0 && heap[(i - 1) / 2]->freq > heap[i]->freq) {
        Node* temp = heap[i];
        heap[i] = heap[(i - 1) / 2];
        heap[(i - 1) / 2] = temp;
        i = (i - 1) / 2;
    }
}
Node* removeMin() {
    Node* top = heap[0];
    heapSize--;
   heap[0] = heap[heapSize];
    // move down
    int i = 0;
    while (true) {
        int l = 2 * i + 1;
        int r = 2 * i + 2;
        int small = i;
        if (l < heapSize && heap[l]->freq < heap[small]->freq) small = l;
        if (r < heapSize && heap[r]->freq < heap[small]->freq) small = r;
        if (small == i) break;
        Node* temp = heap[i];
        heap[i] = heap[small];
        heap[small] = temp;
        i = small;
    }
    return top;
}
// preorder: print the code when we reach a leaf
void printCodes(Node* root, char code[], int len) {
    if (root == NULL) return;
    if (root->left == NULL && root->right == NULL) {
        cout << root->ch << ": ";
        for (int i = 0; i < len; i++) cout << code[i];
        cout << endl;
    }
    code[len] = '0';
    printCodes(root->left, code, len + 1);
    code[len] = '1';
    printCodes(root->right, code, len + 1);
}
int main() {
    char s[] = {'a', 'b', 'c', 'd', 'e', 'f'};
    int f[] = {5, 9, 12, 13, 16, 45};
    int n = 6;
    for (int i = 0; i < n; i++)
        insertHeap(makeNode(s[i], f[i]));
    // join the two smallest until only one is left
    while (heapSize > 1) {
        Node* a = removeMin();
        Node* b = removeMin();
        Node* parent = makeNode('$', a->freq + b->freq);
        parent->left = a;
        parent->right = b;
        insertHeap(parent);
    }
    Node* root = removeMin();
    char code[100];
    cout << "Huffman codes in preorder:" << endl;
    printCodes(root, code, 0);
    return 0;
}