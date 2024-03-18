#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include <conio.h>
#include <Windows.h> // GUI ���� ���

void main() {
	//int size = 50;
	//int* p;
	//p = (int *)malloc(sizeof(int)* size); // Heap ������ int�� ũ��� size ������ŭ �޸� Ȯ��

	//*p = 100; == p[0]
	//*(p + 1) = 101; == p[1]
	//*(p + 2) = 102;* ==  p[2]
	int size = 100;
	int count = 1234;
	int sum = 0;

	// int p[size] �� ����
	int* p = (int*)malloc(sizeof(int) * size); // Stack���� ������ ����(4Byte)�� �Ҵ�, Heap�� �ּҸ� ����
	free(p);								   // Heap���� ������(4Byte) size(100) ��ŭ�� ������ �Ҵ�

	for (int i = 0; i < size; i++) {
		p[i] = count;
		sum += count;
		count++;
		printf("%d ", p[i]);
	}
	printf("\n");
	printf("sum : %d \n", sum);
	int size1 = 5;
	double count1 = 0.1;
	double count2 = 0.5;
	double* p1 = (double*)malloc(sizeof(double) * size1);
	double* p2 = (double*)malloc(sizeof(double) * size1);
	for (int i = 0; i < size1; i++) {
		p1[i] = count1;
		p2[i] = count2;
		count1 += 0.1;
		count2 -= 0.1;

	}
	for (int i = 0; i < size1; i++) {
		printf("%lf ", p1[i]);
	}
	printf("\n");
	for (int i = 0; i < size1; i++) {
		printf("%lf ", p2[i]);
	}
	free(p1);
	free(p2);
}
