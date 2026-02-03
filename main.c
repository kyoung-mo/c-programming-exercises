#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 10000

double compare_count = 0;
double swap_count = 0;

void swap(int* a, int* b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}

void cocktail_sort(int* arr, int size) {
	int start = 0, end = size - 1;
	int isEnd = 0;
	compare_count = 0;
	swap_count = 0;

	while (1) {
		isEnd = 1;
		for (int i = start; i < end; i++) {
			compare_count++;
			if (arr[i] > arr[i + 1]) {
				swap(&arr[i], &arr[i + 1]);
				swap_count++;
				isEnd = 0;
			}
		}
		end--;
		if (isEnd) break;

		isEnd = 1;
		for (int i = end; i > start; i--) {
			compare_count++;
			if (arr[i] < arr[i - 1]) {
				swap(&arr[i], &arr[i - 1]);
				swap_count++;
				isEnd = 0;
			}
		}
		start++;
		if (isEnd) break;
	}
}

void bubble_sort(int* arr, int size) {
	int is_end = 0;
	compare_count = 0;
	swap_count = 0;

	for (int i = 0; i < size - 1; i++) {
		is_end = 1;
		for (int j = 0; j < size - i - 1; j++) {
			compare_count++;
			if (arr[j] > arr[j + 1]) {
				swap(&arr[j], &arr[j + 1]);
				swap_count++;
				is_end = 0;
			}
		}
		if (is_end) break;
	}
}

int main() {
	int* reversed; reversed = (int*)malloc(sizeof(int) * SIZE);
	int* random; random = (int*)malloc(sizeof(int) * SIZE);

	srand(0);

	clock_t start, end;
	double duration; // 실제 시간을 초 단위로 저장하는 역할


	for (int i = 0; i < SIZE; i++)
		reversed[i] = SIZE - i; // 역순 배열 생성

	printf("\\n[역순 배열(최악)]\\n");

	start = clock();
	bubble_sort(reversed, SIZE);
	printf("버블 정렬 비교 횟수: %.0lf\\n", compare_count);
	printf("버블 정렬 스왑 횟수: %.0lf\\n", swap_count);
	end = clock();

	duration = (double)(end - start) / CLOCKS_PER_SEC;
	printf("소요 시간 : %.2f초\\n", duration);

	for (int i = 0; i < SIZE; i++)
		reversed[i] = SIZE - i;

	start = clock();
	cocktail_sort(reversed, SIZE);
	printf("칵테일 정렬 비교 횟수: %.0lf\\n", compare_count);
	printf("칵테일 정렬 스왑 횟수: %.0lf\\n", swap_count);
	end = clock();

	duration = (double)(end - start) / CLOCKS_PER_SEC;
	printf("소요 시간 : %.2f초\\n", duration);





	for (int i = 0; i < SIZE; i++)
		random[i] = ((rand() << 15) | rand()) % (SIZE + 1);

	printf("\\n[랜덤 배열(평균)]\\n");
	start = clock();
	bubble_sort(random, SIZE);
	printf("버블 정렬 비교 횟수: %.0lf\\n", compare_count);
	printf("버블 정렬 스왑 횟수: %.0lf\\n", swap_count);
	end = clock();

	duration = (double)(end - start) / CLOCKS_PER_SEC;
	printf("소요 시간 : %.2f초\\n", duration);


	for (int i = 0; i < SIZE; i++)
		random[i] = ((rand() << 15) | rand()) % (SIZE + 1);

	start = clock();
	cocktail_sort(random, SIZE);
	printf("칵테일 정렬 비교 횟수: %.0lf\\n", compare_count);
	printf("칵테일 정렬 스왑 횟수: %.0lf\\n", swap_count);
	end = clock();

	duration = (double)(end - start) / CLOCKS_PER_SEC;
	printf("소요 시간 : %.2f초\\n", duration);



	free(reversed);
	free(random);
}
