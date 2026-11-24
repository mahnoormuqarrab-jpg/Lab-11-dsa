#include <iostream>
using namespace std;
struct Node {
    int data;
    Node* next;
};
Node* makeNode(int d) {
    Node* n = new Node;
    n->data = d;
    n->next = NULL;
    return n;
}
// min heap (array based)
Node* heap[100];
int heapSize = 0;
void insertHeap(Node* n) {
    heap[heapSize] = n;
    int i = heapSize;
    heapSize++;
    while (i > 0 && heap[(i - 1) / 2]->data > heap[i]->data) {
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
    int i = 0;
    while (true) {
        int l = 2 * i + 1;
        int r = 2 * i + 2;
        int small = i;
        if (l < heapSize && heap[l]->data < heap[small]->data) small = l;
        if (r < heapSize && heap[r]->data < heap[small]->data) small = r;
        if (small == i) break;
        Node* temp = heap[i];
        heap[i] = heap[small];
        heap[small] = temp;
        i = small;
    }
    return top;
}
Node* mergeLists(Node* lists[], int k) {
    // put the first node of each list in the heap
    for (int i = 0; i < k; i++) {
        if (lists[i] != NULL)
            insertHeap(lists[i]);
    }
    Node* head = NULL;
    Node* tail = NULL;
    while (heapSize > 0) {
        Node* smallest = removeMin();
        if (head == NULL) {
            head = smallest;
            tail = smallest;
        } else {
            tail->next = smallest;
            tail = smallest;
        }
        // add the next node of the same list
        if (smallest->next != NULL)
            insertHeap(smallest->next);
    }
    return head;
}
// makes a linked list from an array
Node* makeList(int a[], int n) {
    Node* head = NULL;
    Node* tail = NULL;
    for (int i = 0; i < n; i++) {
        Node* node = makeNode(a[i]);
        if (head == NULL) {
            head = node;
            tail = node;
        } else {
            tail->next = node;
            tail = node;
        }
    }
    return head;
}
void printList(Node* head) {
    while (head != NULL) {
        cout << head->data << " ";
        head = head->next;
    }
    cout << endl;
}
int main() {
    int a[] = {1, 4, 5};
    int b[] = {1, 3, 4};
    int c[] = {2, 6};
    Node* lists[3];
    lists[0] = makeList(a, 3);
    lists[1] = makeList(b, 3);
    lists[2] = makeList(c, 2);
    Node* result = mergeLists(lists, 3);
    cout << "Merged list: ";
    printList(result);
    return 0;
}