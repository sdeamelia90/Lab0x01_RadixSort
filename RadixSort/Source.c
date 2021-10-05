#include <stdio.h>
#include <time.h>
#include <math.h>


#define W 25
#define C 5
#define LENGTH 10000000

char INPUTARR[LENGTH][W + 1];
char OUTPUTARR[LENGTH][W + 1];

void testList(int N, int width, int minChar, int radixNum) {
	int i, j;
	for (i = 0; i < N; i++) {
		for (j = 0; j < width; j++) {
			INPUTARR[i][j] = rand() % C + minChar;
		}
	}
}

void radixSort(char INPUTARR[LENGTH][W + 1], int listLength, int width, int minChar, int radixNumber, int demoFlag) {

	int i;
	int j;
	int k = 0;
	int temp;
	int size;

	for (size = width - 1; size > 0; size--) {
		int counterArr[C] = { 0 };
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

		for (i = 0; i < listLength; i++) {
			for (j = 0; j < width; j++) {
				INPUTARR[i][j] = OUTPUTARR[i][j];
			}
		}

		if (demoFlag == 1) {
			printf("Sort on digit %d:\n", size);
			printf("================\n");
			for (i = 0; i < listLength; i++) {
				for (j = 0; j < width; j++) {
					printf("%c", INPUTARR[i][j]);
				}
				printf("\n");
			}
		}
	}
}

void bubbleSort(char INPUTARR[LENGTH][W + 1], int listLength, int width, int minChar, int radixNumber, int demoFlag) {

	char temp[W + 1];

	for (int j = 0; j < listLength - 1; j++)
	{
		for (int i = j + 1; i < listLength; i++)
		{
			if (strcmp(INPUTARR[j], INPUTARR[i]) > 0)
			{
				strcpy(temp, INPUTARR[j]);
				strcpy(INPUTARR[j], INPUTARR[i]);
				strcpy(INPUTARR[i], temp);
			}
		}
	}
}

void printTest(char INPUTARR[LENGTH][W + 1], int listLength) {
	printf("Sorted Array:\n");
	printf("================\n");
	for (int i = 0; i <= listLength; i++) {
		for (int j = 0; j < W - 1; j++) {
			printf("%c", INPUTARR[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

void quickSort(char INPUTARR[LENGTH][W + 1], int left, int right) {
	int i, j;
	char* pivot;
	char temp[W + 1];
	i = left + 1;
	j = right;
	pivot = INPUTARR[left];

	while (i <= j) {
		while ((strcmp(INPUTARR[i], pivot) < 0) && (i < right)) {
			i++;
		}
		while ((strcmp(INPUTARR[j], pivot) > 0) && (j > left)) {
			j--;
		}
		if (i <= j) {
			strcpy(temp, INPUTARR[i]);
			strcpy(INPUTARR[i], INPUTARR[j]);
			strcpy(INPUTARR[j], temp);
			i++;
			j--;
		}
	}
	strcpy(temp, INPUTARR[j]);
	strcpy(INPUTARR[j], INPUTARR[left]);
	strcpy(INPUTARR[left], temp);

	if (left < j) {
		quickSort(INPUTARR, left, j);
	}
	if (i < right) {
		quickSort(INPUTARR, i, right);
	}
}


void printTable(int timeCount, double TIME[], int sort) {
	printf("%12s %16s %14s %14s\n", "  N  ", "Measured Time(ms)", "Dbling Ratio", "Expected Ratio");
	printf("        ====================================================\n");
	int n = 2;
	double doubleRatio = 0;
	double theoryRatio = 0;
	printf("%12d %12lf\n", 1, TIME[0]);

	for (int i = 1; i < timeCount; i++) {
		if (TIME[i - 1] == 0) {
			doubleRatio = 0;
		}
		else {
			doubleRatio = TIME[i] / TIME[i - 1];
		}
		if (sort == 1) {
			theoryRatio = (double)n / (n / 2);
		}
		else if (sort == 3) {
			theoryRatio =  2 * (double)log2(n) / ((double)log2(n) - (double)log2(2));
		}
		else if (sort == 2) {
			theoryRatio = 4;
		}
		printf("%12d %12lf %12.2lf %12.2lf\n", n, TIME[i], doubleRatio, theoryRatio);
		n = n * 2;
	}
}

int main()
{
	int minChar = 65;
	int demoFlag = 0;

	long timeCount = 0;
	double TIME[1000] = { 0 };
	long trialsTime_max = 200;
	long trialsCount_max = 1000,
		N_min = 1,
		N_max = 1000000,
		n, trial;
	clock_t trialSetStart;
	clock_t splitTimeStamp;
	long trialSetCount = 0;
	long trialSetTime = 0;
	double averageTrialTime;
	long dummySetCount = 0;
	long dummySetTime = 0;
	double averageDummyTrialTime = 0;
	long splitTime = 0;
	double estimatedTimePerTrial;


	// Begin the Set of Trials
	for (n = 1; n < N_max; n = 2 * n) {

		// Create a list of strings		
		testList(n, W, minChar, C);

		//Start set of trials for single value of N
		trialSetStart = clock();
		for (trial = 1; trial < trialsCount_max && splitTime < trialsTime_max; trial++) {

			//Create a list of strings
			testList(n, W, minChar, C);

			//Select which sort to run
			//radixSort(INPUTARR, n, W, minChar, C, demoFlag);
			//bubbleSort(INPUTARR, n, W, minChar, C, demoFlag);
			quickSort(INPUTARR, 0, n-1);

			splitTimeStamp = clock();
			splitTime = (splitTimeStamp - trialSetStart);
		}

		trialSetCount = trial;
		trialSetTime = splitTime;
		averageTrialTime = (double)trialSetTime / (double)trialSetCount;
		splitTime = 0;
		trialSetStart = clock();

		// Subtract overhead
		for (trial = 1; trial < trialSetCount && splitTime < trialsTime_max; trial++) {

			testList(n, W, minChar, C);
			splitTimeStamp = clock();
			splitTime = (splitTimeStamp - trialSetStart);
		}
		
		dummySetCount = trial;
		dummySetTime = splitTime;
		averageDummyTrialTime = (double)dummySetTime / (double)dummySetCount;
		estimatedTimePerTrial = averageTrialTime - averageDummyTrialTime;

		//Add time to array for printing
		TIME[timeCount] = estimatedTimePerTrial;
		timeCount++;
	}
	
	//print to table.  Change last value based on sort algorithm. 1 = radix, 2 = bubble, 3 = quick
	printTable(timeCount, TIME, 3);

	//Demo Testing Calls
	/*
	listLength = 12;
	testList(listLength, W, minChar, C);

	printf("Original Array:\n");
	printf("================\n");
	for (int i = 0; i <= listLength; i++) {
		for (int j = 0; j < W; j++) {
			printf("%c", INPUTARR[i][j]);
		}
		printf("\n");
	}
	printf("\n");
	radixSort(INPUTARR, listLength, W, minChar, C, 1);;

	*/
	return 0;
}