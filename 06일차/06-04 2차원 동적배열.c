//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//#include <stdbool.h>
//#include <time.h>
//#include <stdlib.h>
//#include <math.h>
//#include <conio.h>
//#include <Windows.h> // GUI ���� ���
//
//void main() {
//	srand((unsigned int)time(0));
//
//	int row = 512;
//	int col = 512;
//	unsigned char** p;
//	p = (unsigned char**)malloc(sizeof(unsigned char*) * row); // 3�� �Ҵ� (��)
//	for (int i = 0; i < row; i++) {
//		if(p[i]=!NULL)
//			p[i] = (unsigned char*)malloc(sizeof(unsigned char) * col); // 5�� �Ҵ� (��)
//	}
//
//	int value = rand() % 256;
//	int sum = 0;
//	for (int i = 0; i < row; i++) {
//		for (int j = 0; j < col; j++) {
//			p[i][j] = value;
//			printf("%3d ", p[i][j]);
//			sum += value;
//			value++;
//		}
//		printf("\n");
//	}
//	printf("\n");
//
//	int avg;
//	avg = sum / (row * col);
//	printf("avg : %d", avg);
//
//	for (int i = 0; i < row; i++) { // ����
//		free(p[i]);
//	}
//}