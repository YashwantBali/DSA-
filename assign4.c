#include <stdio.h>
#include <stdlib.h>

int majorityElement(int* nums, int numsSize, int* result) {
    int count1 = 0, count2 = 0;
    int candidate1 = 0, candidate2 = 1;
    for (int i = 0; i < numsSize; i++) {
        if (count1 == 0 && nums[i] != candidate2) {
            candidate1 = nums[i];
            count1 = 1;
        } 
        else if(count2 == 0 && nums[i] != candidate1) {
            candidate2 = nums[i];
            count2 = 1;
        } 
        else if(nums[i] == candidate1) {
            count1++;
        }
        else if (nums[i] == candidate2) {
            count2++;
        } 
        else{
            count1--;
            count2--;
        }
    }
    count1 = 0;
    count2 = 0;
    for(int i = 0; i < numsSize; i++) {
        if(nums[i] == candidate1) count1++;
        else if(nums[i] == candidate2) count2++;
    }
    int threshold = numsSize / 3;
    int resCount = 0;
    if (count1 > threshold) result[resCount++] = candidate1;
    if (count2 > threshold) result[resCount++] = candidate2;
    return resCount;
}
void function1() {
    int t;
    scanf("%d", &t);
    while(t--){
    int n;
    scanf("%d", &n);
    int nums[n];
    for(int i=0; i<n; i++){
        scanf("%d", &nums[i]);
    }
    int result[2];
    int count = majorityElement(nums, n, result);

    if(count == 2){
        if (result[0] > result[1]) {
            int temp = result[0];
            result[0] = result[1];
            result[1] = temp;
        }
        printf("YES\n%d %d\n", result[0], result[1]);
    } 
    else{
        printf("NO\n");
    }
    }
}

#define MAXN 100005

typedef struct {
    int u, v;
} Edge;

Edge bridges[MAXN];
int bridgeCount = 0;

int timer = 0;
int tin[MAXN], low[MAXN], visited[MAXN];

typedef struct Node {
    int val;
    struct Node* next;
} Node;

Node* adj[MAXN];

void addEdge(int u, int v) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->val = v;
    node->next = adj[u];
    adj[u] = node;
}

void dfs(int v, int p) {
    visited[v] = 1;
    tin[v] = low[v] = ++timer;

    for (Node* it = adj[v]; it; it = it->next) {
        int to = it->val;
        if (to == p) continue;
        if (visited[to]) {
            if (low[v] > tin[to]) low[v] = tin[to];
        } else {
            dfs(to, v);
            if (low[v] > low[to]) low[v] = low[to];
            if (low[to] > tin[v]) {
                bridges[bridgeCount].u = v < to ? v : to;
                bridges[bridgeCount].v = v < to ? to : v;
                bridgeCount++;
            }
        }
    }
}

int compare(const void* a, const void* b) {
    Edge* ea = (Edge*)a;
    Edge* eb = (Edge*)b;
    if (ea->u == eb->u) return ea->v - eb->v;
    return ea->u - eb->u;
}

void function2(){
    int n, m;
    scanf("%d %d", &n, &m);
    int u, v;

    for (int i = 0; i < m; i++) {
        scanf("%d %d", &u, &v);
        addEdge(u, v);
        addEdge(v, u);
    }

    dfs(0, -1);

    if (bridgeCount == 0) {
        printf("-1\n");
    } else {
        qsort(bridges, bridgeCount, sizeof(Edge), compare);
        for (int i = 0; i < bridgeCount; i++) {
            printf("%d %d\n", bridges[i].u, bridges[i].v);
        }
    }
}


typedef struct {
    int value;
    int arrIndex;
    int elemIndex;
} HeapNode;

HeapNode heap[100001];
int heapSize = 0;

void swap(HeapNode* a, HeapNode* b) {
    HeapNode temp = *a;
    *a = *b;
    *b = temp;
}

void push(HeapNode node) {
    heap[heapSize++] = node;
    int i = heapSize - 1;
    while (i && heap[(i - 1) / 2].value > heap[i].value) {
        swap(&heap[i], &heap[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

HeapNode pop() {
    HeapNode top = heap[0];
    heap[0] = heap[--heapSize];
    int i = 0;

    while (2*i + 1 < heapSize) {
        int smallest = i;
        int l = 2*i + 1;
        int r = 2*i + 2;
        if (heap[l].value < heap[smallest].value) smallest = l;
        if (r < heapSize && heap[r].value < heap[smallest].value) smallest = r;
        if (smallest == i) break;
        swap(&heap[i], &heap[smallest]);
        i = smallest;
    }

    return top;
}

void function3(){
    int k;
    scanf("%d", &k);

    int* arr[k];
    int sizes[k];
    int total = 0;

    for (int i = 0; i < k; i++) {
        scanf("%d", &sizes[i]);
        total += sizes[i];
        arr[i] = (int*)malloc(sizes[i] * sizeof(int));
        for (int j = 0; j < sizes[i]; j++) {
            scanf("%d", &arr[i][j]);
        }
        if (sizes[i] > 0) {
            HeapNode node = {arr[i][0], i, 0};
            push(node);
        }
    }

    int result[total], index = 0;

    while (heapSize > 0) {
        HeapNode node = pop();
        result[index++] = node.value;
        int nextElemIndex = node.elemIndex + 1;
        if (nextElemIndex < sizes[node.arrIndex]) {
            HeapNode newNode = {arr[node.arrIndex][nextElemIndex], node.arrIndex, nextElemIndex};
            push(newNode);
        }
    }

    for (int i = 0; i < total; i++) printf("%d ", result[i]);
}