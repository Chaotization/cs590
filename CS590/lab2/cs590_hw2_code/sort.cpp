#include <cstdio>
#include <cstdlib>

#include "sort.h"

/* 
 * HW 2 part
 */
int string_compare(char* s1, char *s2)
{ 
/*
 * We assume that s1 and s2 are non-null pointers
 */
  int i;

  i = 0;
  while ((s1[i] != 0) && (s2[i] != 0) && (s1[i] == s2[i]))
    i++;

  if (s1[i] == s2[i])
    return 0;
  else
    {
      if (s1[i] < s2[i])
	return -1;
      else
	return 1;
    }
} /*>>>*/

int string_compare_digit(char* s1, char *s2, int d)
{
/*
 * We assume that s1 and s2 are non-null pointers
 */
    int i = d;
    while ((s1[i] != 0) && (s2[i] != 0) && (s1[i] == s2[i]))
        i++;

    if (s1[i] == s2[i])
        return 0;
    else
    {
        if (s1[i] < s2[i])
            return -1;
        else
            return 1;
    }
} /*>>>*/

void insertion_sort(char** A, int l, int r)
{ 
  int i;
  char* key;

  for (int j = l+1; j <= r; j++)
    {
      key = A[j];
      i = j - 1;

      while ((i >= l) && (string_compare(A[i], key) > 0))
        {
	  A[i+1] = A[i];
	  i = i - 1;
	}

      A[i+1] = key;
    }
}

void insertion_sort_digit(char** A, int* A_len, int l, int r, int d){
    int i;
    char* key;
    for(int j = l + 1; j <= r; j++){
        key = A[j];
        int key_len = A_len[j];
        i = j - 1;
        while((i >= l) && string_compare_digit(A[i], key, d) > 0){
            A[i + 1] = A[i];
            A_len[i + 1] = A_len[i];
            i--;
        }
        A[i + 1] = key;
        A_len[i + 1] = key_len;
    }
}

void counting_sort_digit(char** A, int* A_len, char** B, int* B_len, int n, int d){
    int C[256] = {0};
    for(int i = 0; i < n; i++){
        int index = (int)A[i][d];
        if(A_len[i] <= d){
            index = 0;
        }
        C[index]++;
    }
    for(int i = 1; i < 255; i++){
        C[i] += C[i - 1];
    }
    for(int i = n - 1; i >= 0; i--){
        int index = (int)A[i][d];
        if(A_len[i] <= d){
            index = 0;
        }
        B[C[index] - 1] = A[i];
        B_len[C[index] - 1] = A_len[i];
        C[index]--;
    }
    for(int i = 0; i < n; i++){
        A[i] = B[i];
        A_len[i] = B_len[i];
    }
}

void radix_sort_is(char** A, int* A_len, int n, int m){
    int max = A_len[0];
    for (int i = 1; i < n; i++) {
        if (A_len[i] > max) {
            max = A_len[i];
        }
    }
    for (int d = m - 1; d >= 0; d--) {
        insertion_sort_digit(A, A_len, 0, n - 1, d);
    }
}

void radix_sort_cs(char** A, int* A_len, int n, int m){
    char** B = new char* [n];
    int* B_len = new int[n];
    for(int i = m - 1; i >= 0; i--){
        counting_sort_digit(A, A_len, B, B_len, n, i);
    }
    delete[] B;
    delete[] B_len;
}

/*
 * Simple function to check that our sorting algorithm did work
 * -> problem, if we find position, where the (i-1)-th element is 
 *    greater than the i-th element.
 */
bool check_sorted(char** A, int l, int r)
{
  for (int i = l+1; i < r; i++)
    if (string_compare(A[i-1],A[i]) > 0)
      return false;
  return true;
}
