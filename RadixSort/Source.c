#include <stdio.h>
#include <time.h>
#include <math.h>


#define W 25
#define C 5
#define LENGTH 10000000

char INPUTARR[LENGTH][W + 1] = {0};
char OUTPUTARR[LENGTH][W + 1] = {0};

void radixSort(char INPUTARR[LENGTH][W + 1], int listLength, int width, int minChar, int radixNumber, int demoFlag) {

	int i;
	int j;
	int k = 0;
	int temp;
	int size;

	for (size = width - 1; size > 0; size--) {
		int counterArr[C] = {0};
		for (i = 0; i < listLength; i++) {
			counterArr[INPUTARR[i][size - 1] - minChar]++;
		}

		for (i = 1; i < radixNumber; i++) {
			counterArr[i] += counterArr[i - 1];
		}

		for (i = listLength - 1; i >= 0; i--) {
			temp = INPUTARR[i][size - 1] - minChar;
			counterArr[temp]--;
			for (j = 0; j < width + 1; j++) {
				OUTPUTARR[counterArr[temp]][j] = INPUTARR[i][j];
			}
		}

		if (demoFlag == 1) {
//			printf("Sort on digit %d:\n", size);
//			printf("================\n");
			for (i = 0; i < listLength; i++) {
				for (j = 0; j < width; j++) {
//					printf("%c", OUTPUTARR[i][j]);
				}
//				printf("\n");
			}
//			printf("\n");
		}

		for (i = 0; i < listLength; i++) {
			for (j = 0; j < width; j++) {
				INPUTARR[i][j] = OUTPUTARR[i][j];
			}
		}
	}

//	printf("Sorted Array:\n");
//	printf("================\n");
	for (i = 0; i < listLength; i++) {
		for (j = 0; j < width - 1; j++) {
//			printf("%c", INPUTARR[i][j]);
		}
//		printf("\n");
	}
//	printf("\n");
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

void printTable(int timeCount, long TIME[]) {
	printf("%12s %16s %14s %14s\n", "  N  ", "Measured Time(ms)", "Dbling Ratio", "Expected Ratio");
	printf("        ====================================================\n");
	int n = 2;
	printf("%12d %12lf\n", 1, (double)TIME[0]);
	for (int i = 1; i < timeCount; i++) {
		printf("%12d %12lf %12.2lf %12.2lf\n", n, (double) TIME[i], (double) TIME[i]/TIME[i-1], (double) n/(n/2));
		n = n * 2;
	}
}

int main()
{
	int minChar = 65;
	int demoFlag = 0;
	int i;
	int j;
	int trialCount;
	int splitTime;
	int listLength = 1000000;

	trialCount = 0;
	clock_t startTime;
	clock_t endTime;
	long trialTime;
	int timeCount = 0;
	long TIME[1000] = { 0 };


	//	printf("Original Array:\n");
	//	printf("================\n");

	int z = 1;
	while (z <= listLength) {

		startTime = clock();

		for (i = 0; i < z; i++) {
			for (j = 0; j < W - 1; j++) {
				INPUTARR[i][j] = rand() % C + minChar;
				//			printf("%c",INPUTARR[i][j]);
			}
			//		printf("\n");
		}

		//	printf("\n");
		radixSort(INPUTARR, listLength, W, minChar, C, demoFlag);
		endTime = clock();
		trialTime = (endTime - startTime);
		TIME[timeCount] = trialTime;

		timeCount++;
		z = z * 2;

	}

	printTable(timeCount, TIME);
	return 0;
}
/*

printf("%16s %16s %16s %16s\n", "  N  ", "Measured Time", "Dbling Ratio", "Expected Ratio");
// what printing a line for the table might look like
printf("%12d %12lf %12.2lf %12.2\n", n, t, mRatio, xRatio);

*/