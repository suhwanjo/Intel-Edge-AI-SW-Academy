//#define _CRT_SECURE_NO_WARNINGS
//#include <stdbool.h>
//#include <stdio.h>
//#include <time.h>
//#include <stdlib.h>  // Include stdlib.h for srand() and rand()
//#define HEIGHT 10
//#define WIDTH 10
//
//void main() {
//	srand((unsigned int)time(0));
//	// ������ ������ ũ�� ��ŭ�� �޸� Ȯ�� (jolly.raw : 10x10 ũ�� ������, �̰��� �̹��� ����)
//
//	// �޸� �Ҵ�
//	unsigned char image[HEIGHT][WIDTH];
//
//	// �̹��� ���� -> 2���� �迭�� �ε�(Loading) Disk -> RAM
//	for (int i = 0; i < HEIGHT; i++) {
//		for (int j = 0; j < WIDTH; j++) {
//			image[i][j] = rand() % 256;
//		}
//	}
//	// ���� �̹��� ���
//	for (int i = 0; i < HEIGHT; i++) {
//		for (int j = 0; j < WIDTH; j++) {
//			printf("%3d ", image[i][j]);
//		}
//		printf("\n");
//	}
//	printf("\n");
//
//	// ���� ó�� (Image Processing)
//	for (int i = 0; i < HEIGHT; i++) {
//		for (int j = 0; j < WIDTH; j++) {
//			if (image[i][j]-50 > 0)
//				image[i][j] -= 50;
//			else
//				image[i][j] = 0;
//		}
//	}
//
//	// ��� �̹��� ���
//	for (int i = 0; i < HEIGHT; i++) {
//		for (int j = 0; j < WIDTH; j++) {
//			printf("%3d ", image[i][j]);
//		}
//		printf("\n");
//	}
//}