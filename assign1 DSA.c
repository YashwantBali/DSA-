#include <stdio.h>
int RFib(int n){
    if(n==0){
        return 0;
    }
    if(n==1){
        return 1;
    }
    else return (RFib(n-1) + RFib(n-2)) % 2025;
}
void matrixMultiplication(int M[2][2], int N[2][2], int ans[2][2]) {
    ans[0][0] = (M[0][0]*N[0][0] + M[0][1]*N[1][0]) % 2025;
    ans[0][1] = (M[0][0]*N[0][1] + M[0][1]*N[1][1]) % 2025;
    ans[1][0] = (M[1][0]*N[0][0] + M[1][1]*N[1][0]) % 2025;
    ans[1][1] = (M[1][0]*N[0][1] + M[1][1]*N[1][1]) % 2025;
}
int powerN(int A[2][2], int N, int result[2][2]){
    int ans[2][2];
    while(N > 0){
        if(N == 1){
            int temp1[2][2];
            matrixMultiplication(A, result, temp1);
            return temp1[0][0];
        }
        if(N%2 == 1){
            int temp[2][2]; 
            matrixMultiplication(A, result, ans);
            for(int i=0; i<2; i++){
                for(int j=0; j<2; j++){
                    result[i][j] = ans[i][j];
                }
            }
            matrixMultiplication(A, A, temp);
            for(int i=0; i<2; i++){
                for(int j=0; j<2; j++){
                    A[i][j] = temp[i][j];
                }
            }
            N /= 2;
        }
        else if(N%2 == 0){
            int temp[2][2];
            matrixMultiplication(A, A, temp);
            for(int i=0; i<2; i++){
                for(int j=0; j<2; j++){
                    A[i][j] = temp[i][j];
                }
            }
            N /= 2;
        }
    }
    return 0;
}
int CleverFib(int n){
    int base[2][2] = {{1,1}, {1,0}};
    int result[2][2] = {{1,0}, {0,1}};
    return powerN(base, n-1, result);
}
int min(int a, int b) {
    return (a < b) ? a : b;
}
int TrivialGCD(int a, int b){
    int m = min(a,b);
    for(int i=m; i>0; i--){
        if(a%i == 0 && b%i == 0) return i;
    }
    return 1;
}
long int EuclidGCD(long int a, long int b){
    if(a==0) return b;
    return EuclidGCD(b%a, a);
}