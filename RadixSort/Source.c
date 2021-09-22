#include <stdio.h>

#define N 20
#define W 15
#define C 10


void radixSort(char inputArr[N][W + 1], int width, int minChar, int radixNumber, int demoFlag) {
	char outputArr[N][W + 1] = { 0 };
	int i;
	int j;
	int k = 0;
	int temp;
	int size;

	for (size = width - 1; size > 0; size--) {
		int counterArr[C] = { 0 };
		for (i = 0; i < N; i++) {
			counterArr[inputArr[i][size - 1] - minChar]++;
		}

		for (i = 1; i < radixNumber; i++) {
			counterArr[i] += counterArr[i - 1];
		}

		for (i = N - 1; i >= 0; i--) {
			temp = inputArr[i][size - 1] - minChar;
			counterArr[temp]--;
			for (j = 0; j < W + 1; j++) {
				outputArr[counterArr[temp]][j] = inputArr[i][j];
			}

		}
		if (demoFlag == 1) {
			printf("Sort on digit %d:\n", size);
			printf("================\n");
			for (i = 0; i < N; i++) {
				for (j = 0; j < W; j++) {
					printf("%c", outputArr[i][j]);
				}
				printf("\n");
			}
			printf("\n");
		}

		for (i = 0; i < N; i++) {
			for (j = 0; j < W; j++) {
				inputArr[i][j] = outputArr[i][j];
			}
		}
	}

	printf("Sorted Array:\n");
	printf("================\n");
	for (i = 0; i < N; i++) {
		for (j = 0; j < W - 1; j++) {
			printf("%c", inputArr[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

/*
void bubbleSort(char inputArr[N][W + 1]) {
	int swap;
	int width = W;
	int temp1;
	int temp2;

	for (int i = 0; i < N; i++) {
		temp1 = inputArr[i][width - 1];
		temp2 = inputArr[i][width - 2];

		if (temp1 > temp2) {
		}
}
*/

int main()
{
	int minChar = 65;
	int demoFlag = 0;
	char inputArr[N][W + 1];
	int i;
	int j;

	printf("Original Array:\n");
	printf("================\n");
	for (i = 0; i < N; i++) {
		inputArr[i][W-1] = '\0';
		for (j = 0; j < W - 1; j++) {
			inputArr[i][j] = rand() % C + minChar;
			printf("%c",inputArr[i][j]);
		}
		printf("\n");
	}

	printf("\n");

	radixSort(inputArr, W, minChar, C, demoFlag);
	return 0;
}