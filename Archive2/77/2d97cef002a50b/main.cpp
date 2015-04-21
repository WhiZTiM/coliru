/* 213112 林雅人 */
/* Quick Sort */

#include "stdio.h"
#include "stdlib.h"
#include "time.h"

#define N 100000

int array[N];

int pivot(int *a, int i, int j) {
    int k= i + 1;
	while (k <= j && *(a + i) == *(a + k)) {
		k++;
	}
	if (k > j) {
		return -1;
	}
	if (*(a + i) >= *(a + k)) {
		return i;
	}
	return k;
}

int partition(int *a, int i, int j, int mid) {
	int left = i, right = j;

	while (left <= right) {
		while (left <= j && *(a + left) < mid) {
			left++;
		}

		while (right >= i && *(a + right) >= mid) {
			right--;
		}

		if (left > right) {
			break;
		}

		int temp = *(a + left);
		*(a + left) = *(a + right);
		*(a + right) = temp;
		left++;
		right--;
	}
	return left;
}


void qs(int *a, int i, int j){
	if(i == j){
		return;
	}
	int p = pivot(a, i, j);
	if(p != -1) {
		int k = partition(a, i, j, *(a + p));
		qs(a, i, k - 1);
		qs(a, k, j);
	}
}

int main() {
	clock_t start;
	int get;
	FILE *fp1, *fp2;
	int i, j;

	if ((fp1 = fopen("h27c3gx03-10.data", "r")) == NULL) {
		printf("h27c3gx03-10.data FILE OPEN ERROR\n");
		exit(1);
	}

	if ((fp2 = fopen("h27c3gx03-10.ans", "w")) == NULL) {
		printf("h27c3gx03-10.data FILE OPEN ERROR\n");
		exit(1);
	}

	for (i = 0; i < N; i++) {
		fscanf(fp1, "%d", &get);
		array[i] = get;
	}

	start = clock();

	qs(array, 0, N - 1);

	printf("Quick Sort  処理時間  :%.3f\n", (double)(clock() - start) / (double)(CLOCKS_PER_SEC));

	for (i = 0; i < N; i++) {
		fprintf(fp2, "%10d\n", array[i]);
	}

	for (i = 0; i < 15; i++) {
		printf("[%9d]:%10d\n", i, array[i]);
	}

	for (i = N - 15; i < N; i++) {
		printf("[%9d]:%10d\n", i, array[i]);
	}
	printf("End\n");

	fclose(fp1);
	fclose(fp2);
	
	return 0;
}