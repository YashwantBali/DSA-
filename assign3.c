#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#define MAX_3 10000
#define MAX_2 100000
#define MAX_1 100000


typedef struct Node{
    int data;
    struct Node* left;
    struct Node* right;
} Node;
Node* createNode(int data){
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode -> data = data;
    newNode -> left = newNode -> right = NULL;
    return newNode;
}
Node* insert1(Node* root, int data){
    if(root == NULL){
        return createNode(data);
    }
    if(data < root->data){
        root -> left = insert1(root -> left, data);
    }
    if(data > root->data){
        root -> right = insert1(root -> right, data);
    }
    return root;
}
int heightofTree(Node* root){
    if(root == NULL) return 0;
    int leftHeight = heightofTree(root -> left);
    int rightHeight = heightofTree(root -> right);
    return (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
}

void function1() {
    int n;
    scanf("%d", &n);
    Node* root = NULL;
    for (int i = 0; i < n; i++) {
        int num;
        scanf("%d", &num);
        root = insert1(root, num);
    }
    printf("%d\n", heightofTree(root));
}




typedef struct {
    int pv, p1, k1, p2, k2, p3;
} TwoThreeNode;
TwoThreeNode tree[MAX_1];
int search(int x) {
    int curr = 0;
    while (curr != -1) {
        if (tree[curr].k1 == x || tree[curr].k2 == x) return 1;
        if (x < tree[curr].k1) curr = tree[curr].p1;
        else if (tree[curr].k2 == -1 || x < tree[curr].k2) curr = tree[curr].p2;
        else curr = tree[curr].p3;
    }
    return 0;
}
int successor(int x) {
    int curr = 0, successor = 0;
    while (curr != -1) {
        if (x < tree[curr].k1) {
            successor = tree[curr].k1;
            curr = tree[curr].p1;
        } else if (tree[curr].k2 == -1 || x < tree[curr].k2) {
            successor = tree[curr].k2 > x ? tree[curr].k2 : successor;
            curr = tree[curr].p2;
        } else {
            curr = tree[curr].p3;
        }
    }
    return successor ? successor : 0;
}

void function2() {
    int n, q;
    scanf("%d %d", &n, &q);
    for (int i = 0; i < n; i++) {
        scanf("%d %d %d %d %d %d", &tree[i].pv, &tree[i].p1, &tree[i].k1, &tree[i].p2, &tree[i].k2, &tree[i].p3);
    }
    for (int i = 0; i < q; i++) {
        int qi, x;
        scanf("%d %d", &qi, &x);
        if (qi == 1)
            printf("%d\n", search(x));
        else
            printf("%d\n", successor(x));
    }
}




typedef struct AdjListNode{
    int node;
    struct AdjListNode* next;
} AdjListNode;
typedef struct AdjList{
    AdjListNode* head;
} AdjList;
AdjList graph[MAX_2];
int distOffice[MAX_2], distHome[MAX_2];
bool isMarket[MAX_2];
void addEdge(int u, int v) {
    AdjListNode* newNode = (AdjListNode*)malloc(sizeof(AdjListNode));
    newNode->node = v;
    newNode->next = graph[u].head;
    graph[u].head = newNode;
    newNode = (AdjListNode*)malloc(sizeof(AdjListNode));
    newNode->node = u;
    newNode->next = graph[v].head;
    graph[v].head = newNode;
}
void bfs(int start, int dist[], int n) {
    for (int i = 0; i < n; i++) dist[i] = INT_MAX;
    int queue[MAX_2], front = 0, rear = 0;
    queue[rear++] = start;
    dist[start] = 0;
    while (front < rear) {
        int u = queue[front++];
        for (AdjListNode* temp = graph[u].head; temp != NULL; temp = temp->next) {
            int v = temp->node;
            if (dist[v] == INT_MAX) {
                dist[v] = dist[u] + 1;
                queue[rear++] = v;
            }
        }
    }
}

void function3() {
    int n, e, m;
    scanf("%d %d %d", &n, &e, &m);
    for (int i = 0; i < n; i++) graph[i].head = NULL;
    for (int i = 0; i < e; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        addEdge(u, v);
    }
    int office, home;
    scanf("%d %d", &office, &home);  
    for (int i = 0; i < m; i++) {
        int market;
        scanf("%d", &market);
        isMarket[market] = true;
    }
    bfs(office, distOffice, n);
    bfs(home, distHome, n);
    int minDist = INT_MAX;
    int bestMarkets[MAX_2], count = 0;
    for (int i = 0; i < n; i++) {
        if (isMarket[i]) {
            int totalDist = distOffice[i] + distHome[i];
            if (totalDist < minDist) {
                minDist = totalDist;
                count = 0;
                bestMarkets[count++] = i;
            } else if (totalDist == minDist) {
                bestMarkets[count++] = i;
            }
        }
    }
    printf("%d %d\n", minDist, count);
    for (int i = 0; i < count; i++) {
        printf("%d ", bestMarkets[i]);
    }
    printf("\n");
}




typedef struct {
    int x, height;
    bool isStart;
} Event;
int compare(const void *a, const void *b) {
    Event *e1 = (Event *)a;
    Event *e2 = (Event *)b;
    if (e1->x != e2->x) return e1->x - e2->x;
    if (e1->isStart && e2->isStart) return e2->height - e1->height;
    if (!e1->isStart && !e2->isStart) return e1->height - e2->height;
    return e1->isStart ? -1 : 1;
}
typedef struct {
    int data[MAX_3 * 2], size;
} MaxHeap;
void insert(MaxHeap *heap, int val) {
    heap->data[heap->size++] = val;
}
void removeHeap(MaxHeap *heap, int val) {
    for (int i = 0; i < heap->size; i++) {
        if (heap->data[i] == val) {
            heap->data[i] = heap->data[--heap->size];
            break;
        }
    }
}
int getMax(MaxHeap *heap) {
    int max = 0;
    for (int i = 0; i < heap->size; i++) {
        if (heap->data[i] > max) max = heap->data[i];
    }
    return max;
}

void function4() {
    int N;
    scanf("%d", &N);   
    Event events[MAX_3 * 2];
    int eventCount = 0;
    for (int i = 0; i < N; i++) {
        int L, R, H;
        scanf("%d %d %d", &L, &R, &H);
        events[eventCount++] = (Event){L, H, true};
        events[eventCount++] = (Event){R, H, false};
    }
    qsort(events, eventCount, sizeof(Event), compare);
    MaxHeap heap = { .size = 0 };
    insert(&heap, 0);
    int prevMax = 0;
    for (int i = 0; i < eventCount; i++) {
        if (events[i].isStart) {
            insert(&heap, events[i].height);
        } else {
            removeHeap(&heap, events[i].height);
        }
        int currMax = getMax(&heap);
        if (currMax != prevMax) {
            printf("%d %d ", events[i].x, currMax);
            prevMax = currMax;
        }
    }
    printf("\n");
}