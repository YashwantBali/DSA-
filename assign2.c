#include"assign2.h"
#include <stdio.h>
#include <stdlib.h>
void function1(){
    int n;
    scanf("%d", &n);
    int queue[n], max[n];
    int a = 0, b = 0, p = 0, q = 0;
    for (int i = 0; i < n; i++){
        int operation;
        scanf("%d", &operation);
        if(operation == 1){
            int value;
            scanf("%d", &value);
            queue[b] = value;
            b++;
            while(q > p && max[q - 1] < value)
                q--;
            max[q] = value;
            q++;
        }
        else if(operation == 2){
            if(a < b){
                if(queue[a] == max[p]){
                    p++;
                }
                a++;
            }
        }
        else if(operation == 3){
            printf("%d\n", max[p]);
        }
    }
}
int log2_int(unsigned int x) {
    int log = -1;
    while (x) {
        log++;
        x >>= 1;
    }
    return log;
}
void dataTable(int n, int arr[n],int data[n][30]){
    for (int i = 0; i < n; i++)
        data[i][0] = arr[i];
    for (int j = 1; (1 << j) <= n; j++) { 
        for (int i = 0; i + (1 << j) - 1 < n; i++) {
            if(data[i][j - 1] < data[i + (1 << (j - 1))][j - 1]){
                data[i][j] = data[i][j - 1];
            }
            else{
               data[i][j] = data[i + (1 << (j - 1))][j - 1];
            }
        }
    }
}
int rangeMin(int i, int j, int n, int data[n][30]){
    int L = j - i + 1; 
    int k = log2_int(L);          
    int t = (1 << k);       
    if (t == L) return data[i][k];
    if(data[i][k] < data[j - t + 1][k]){
        return data[i][k];
    }
    else return data[j - t + 1][k]; 
}
void function2(){
    int n, q, a, b; 
    scanf("%d %d", &n, &q);
    int data[n][30];
    int arr[n];
    for(int i=0; i<n; i++){
        scanf("%d", &arr[i]);
    }
    dataTable(n, arr, data);
    for(int i=0; i<q; i++){
        scanf("%d %d", &a, &b);
        printf("%d\n", rangeMin(a-1, b-1, n, data));
    } 
}
long long count_bst(int n, long long dp[1000]) {
    if (n <= 1) {
        return 1;
    }
    if (dp[n] != 0) {
        return dp[n];
    }
    long long total_bst = 0;
    for (int i = 1; i <= n; i++) {
        long long left = count_bst(i - 1, dp);
        long long right = count_bst(n - i, dp);
        total_bst += left * right;
    }
    dp[n] = total_bst;
    return total_bst;
}
void function3(){
    int n;
    scanf("%d", &n); 
    long long dp[1000];
    for(int i=0; i<1000; i++){
        dp[i] = 0;
    } 
    printf("%lld\n", count_bst(n, dp));
}
void findNextSmaller(int arr[], int size, int nextSmaller[]){
    int stack[size], top = -1;
    for(int i = size - 1; i >= 0; i--){
        while (top >= 0 && arr[stack[top]] >= arr[i]) {
            top--;
        }
        nextSmaller[i] = (top >= 0) ? stack[top] : size;
        stack[++top] = i;
    }
}
void findPrevSmaller(int arr[], int size, int prevSmaller[]){
    int stack[size], top = -1;
    for(int i = 0; i < size; i++) {
        while (top >= 0 && arr[stack[top]] >= arr[i]) {
            top--;
        }
        prevSmaller[i] = (top >= 0) ? stack[top] : -1;
        stack[++top] = i;
    }
}
void computeMaxLength(int arr[], int size, int nextSmaller[], int prevSmaller[], int maxLength[100001]){
    for(int i = 0; i < size; i++) {
        int range = nextSmaller[i] - prevSmaller[i] - 1;
        if (maxLength[arr[i]] < range) {
            maxLength[arr[i]] = range;
        }
    }
}
void function4(){
    int maxLength[100001];
    int size, queries;
    scanf("%d %d", &size, &queries);
    int arr[size];
    for(int i = 0; i < size; i++) {
        scanf("%d", &arr[i]);
    }   
    int nextSmaller[size], prevSmaller[size];
    findNextSmaller(arr, size, nextSmaller);
    findPrevSmaller(arr, size, prevSmaller);
    computeMaxLength(arr, size, nextSmaller, prevSmaller, maxLength); 
    for(int i = 0; i < queries; i++){
        int key;
        scanf("%d", &key);
        printf("%d\n", (key > 100000) ? 0 : maxLength[key]);
    }
}