//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//#include <stdbool.h>
//#include <time.h>
//#include <stdlib.h>
//
///////////////
//// ���� ������
///////////////
//FILE* rfp;
//char fileName[200] = "D:/RAW/LENNA512.raw";
//#define height 512
//#define width 512
//// �޸� Ȯ��
//unsigned char inImage[height][width];
//unsigned char outImage[height][width];
//
///////////////
//// �Լ� �����
///////////////
//void loadImage(); int getInValue(); void printImage();
//
//void equalImage(); void addImage(int);
//
//
//void main() {
//	loadImage();
//	// ����ó�� �˰��� ����
//	// ��� ����
//	int value = getInValue();
//	addImage(value);
//
//}
//
////////////////
//// �Լ� ���Ǻ�
////////////////
//
//// ���� �Լ�
//void printImage() {
//	for (int i = height/2-5; i < height /2+5; i++) {
//		for (int j = width / 2 - 5; j < width / 2 + 5; j++) {
//			printf("%3d ", outImage[i][j]);
//		}
//		printf("\n");
//	}
//	printf("\n");
//}
//void loadImage() {
//	rfp = fopen(fileName, "rb");
//	fread(inImage, sizeof(unsigned char), height * width, rfp);
//
//	fclose(rfp);
//	equalImage();
//}
//int getInValue() {
//	int retValue;
//
//	printf("������ : ");
//	scanf("%d", &retValue);
//
//	return retValue;
//}
//
//// ����ó�� �Լ�
//void equalImage() {
//	// ���� ���� �˰���
//	// �Է� �迭 -> ��� �迭
//	for (int i = 0; i < height; i++) {
//		for (int j = 0; j < width; j++) {
//			outImage[i][j] = inImage[i][j];
//		}
//	}
//	printImage();
//}
//
//void addImage(int val) {
//	// ���ϱ�, ���� �˰���
//	for (int i = 0; i < height; i++) {
//		for (int j = 0; j < width; j++) {
//			if (inImage[i][j]+ val < 255)
//				outImage[i][j] = inImage[i][j] + val;
//			else
//				outImage[i][j] = 255;
//		}
//	}
//	printImage();
//}