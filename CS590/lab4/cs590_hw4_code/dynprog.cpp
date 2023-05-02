#include <cstring>
#include <iostream>
#include <limits.h>
#include "dynprog.h"

using namespace std;


/*
 * Bottom up implementation of Smith-Waterman algorithm
 */
void SW_bottomUp(char *X, char *Y, char **P, int **H, int n, int m) {
    for (int i = 0; i <= n; i++) {
        H[i][0] = P[i][0] = 0;
    }
    for (int j = 0; j <= m; j++) {
        H[0][j] = P[0][j] = 0;
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            int p1, p2, p3;
            if (X[i - 1] == Y[j - 1]) {
                p1 = H[i - 1][j - 1] + 2;
            } else {
                p1 = H[i - 1][j - 1] - 1;
            }
            p2 = H[i - 1][j] - 1;
            p3 = H[i][j - 1] - 1;
            H[i][j] = max(p1, p2, p3);
            if (H[i][j] == p1) {
                P[i][j] = 'd';
            } else {
                if (H[i][j] == p2) {
                    P[i][j] = 'u';
                } else {
                    P[i][j] = 'l';
                }
            }
        }
    }

}

int max(int x, int y, int z) {
    if (x >= y && x >= z)
        return x;
    if (y >= x && y >= z)
        return y;
    if (z >= x && z >= y)
        return z;
}

/*
 * Top-down with memoization implementation of Smith-Waterman algorithm
 */
void memoized_SW(char *X, char *Y, char **P, int **H, int n, int m) {
    int **visited = new int *[n + 1];
    for (int i = 0; i <= n; i++) {
        visited[i] = new int[m + 1];
    }
    memoized_SW_AUX(X, Y, P, H, visited, n, m);
}

/*
 * Auxilary recursive function of top-down with memoization implementation of Smith-Waterman algorithm
 */
void memoized_SW_AUX(char *X, char *Y, char **P, int **H, int **visited, int n, int m) {
    if (n == 0 || m == 0) {
        return;
    }
    int p1, p2, p3;
    if (visited[n][m] == 1) {
        return;
    }
    visited[n][m] = 1;
    memoized_SW_AUX(X, Y, P, H, visited, n - 1, m);
    memoized_SW_AUX(X, Y, P, H, visited, n, m - 1);
    memoized_SW_AUX(X, Y, P, H, visited, n - 1, m - 1);
    if (X[n - 1] == Y[m - 1]) {
        p1 = H[n - 1][m - 1] + 2;
    } else {
        p1 = H[n - 1][m - 1] - 1;
    }
    p2 = H[n - 1][m] - 1;
    p3 = H[n][m - 1] - 1;
    H[n][m] = max(p1, p2, p3);
    if (H[n][m] == p1) {
        P[n][m] = 'd';
    } else {
        if (H[n][m] == p2) {
            P[n][m] = 'u';
        } else {
            P[n][m] = 'l';
        }
    }
}

/*
 * Print X'
 */
void print_Seq_Align_X(char *X, char **P, int n, int m) {
    if (n == 0 || m == 0) return;
    if (P[n][m] == 'd') {
        print_Seq_Align_X(X, P, n - 1, m - 1);
        cout << X[n - 1];
    } else {
        if (P[n][m] == 'l') {
            print_Seq_Align_X(X, P, n, m - 1);
            cout << "-";
        } else {
            print_Seq_Align_X(X, P, n - 1, m);
            cout << X[n - 1];
        }
    }
}

/*
 * Print Y'
 */
void print_Seq_Align_Y(char *Y, char **P, int n, int m) {
    if (n == 0 || m == 0) return;
    if (P[n][m] == 'd') {
        print_Seq_Align_Y(Y, P, n - 1, m - 1);
        cout << Y[m - 1];
    } else {
        if (P[n][m] == 'l') {
            print_Seq_Align_Y(Y, P, n, m - 1);
            cout << Y[m - 1];
        } else {
            print_Seq_Align_Y(Y, P, n - 1, m);
            cout << "-";
        }
    }
}
