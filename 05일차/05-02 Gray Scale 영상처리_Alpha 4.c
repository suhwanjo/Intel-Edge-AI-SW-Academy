//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//#include <stdbool.h>
//#include <time.h>
//#include <stdlib.h>
//
//// ������ ������ ����x����
//#define HEIGHT 5
//#define WIDTH 5
//
//// �޸� �غ�
//unsigned char image[HEIGHT][WIDTH];
//
//// �Լ��� �����
//void loadImage() {
//	for (int i = 0; i < HEIGHT; i++) {
//		for (int j = 0; j < WIDTH; j++) {
//			image[i][j] = rand() % 256;
//		}
//	}
//}
//
//void printImage() {
//	for (int i = 0; i < HEIGHT; i++) {
//		for (int j = 0; j < WIDTH; j++) {
//			printf("%3d ", image[i][j]);
//		}
//		printf("\n");
//	}
//	printf("\n");
//}
//
//void reverseImage() {
//	for (int i = 0; i < HEIGHT; i++) {
//		for (int j = 0; j < WIDTH; j++) {
//			image[i][j] = 255 - image[i][j];
//		}
//	}
//	printImage();
//}
//
//int addImage(int val) {
//	for (int i = 0; i < HEIGHT; i++) {
//		for (int j = 0; j < WIDTH; j++) {
//			if (image[i][j] + val < 256)
//				image[i][j] += val;
//			else
//				image[i][j] = 255;
//		}
//	}
//	printImage();
//}
//
//
//
//void main() {
//	// ���� �ʱ�ȭ
//	srand((unsigned int)time(0));
//
//	// �̹��� ���� -> 2���� �迭�� Loading
//	loadImage();
//
//	//���� ���
//	printImage();
//
//	// ���� ���� ó��
//	reverseImage();
//
//	// ���� ��� ó��
//	int value;
//	printf("�󸶳� ��� �ұ��? : ");
//	scanf("%d", &value);
//	addImage(value);
//}
//
//// �Լ��� ���Ǻ�