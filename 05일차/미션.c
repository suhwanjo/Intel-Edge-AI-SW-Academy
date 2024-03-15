#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>

/////////////
// ���� ������
/////////////
FILE* rfp;
char fileName[200] = "D:/RAW/LENNA512.raw";
#define height 512
#define width 512
// �޸� Ȯ��
unsigned char inImage[height][width];
unsigned char outImage[height][width];

/////////////
// �Լ� �����
/////////////
void loadImage(); 
int getInValue(); double getFlValue(); 
void printImage();

void equalImage(); 
void addImage(int);
void reverseImage();
void binaryImage(int); int medCalc(); int avgCalc();
void gammaImage();
void paraCAPImage(); void paraCUPImage();

void main() {
	// ���� �ε�
	loadImage();
	// ����ó�� �˰��� ���� 
	// ��� ����
	int value = getInValue();
	addImage(value);

	// ����
	reverseImage();

	// ���(128)
	binaryImage(128);

	// ���(���)
	int average = avgCalc();
	binaryImage(average);

	// ���(�߾�)
	int median = medCalc();
	binaryImage(median);

	// ���� ���� : ���� ��ȭ�� ���������� ��ȭ��Ų ��
	double gamValue = getFlValue();
	gammaImage(gamValue);
	
	// �Ķ󺼶� : 2���� ��׷����� ���� ��ȯ ó����
	paraCAPImage();
	paraCUPImage();
}

//////////////
// �Լ� ���Ǻ�
//////////////

// ���� �Լ�
void printImage() {
	for (int i = height / 2 - 5; i < height / 2 + 5; i++) {
		for (int j = width / 2 - 5; j < width / 2 + 5; j++) {
			printf("%3d ", outImage[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}
void loadImage() {
	rfp = fopen(fileName, "rb");
	fread(inImage, sizeof(unsigned char), height * width, rfp);

	fclose(rfp);
	equalImage();
}
int getInValue() {
	int retValue;

	printf("������ : ");
	scanf("%d", &retValue);

	return retValue;
}
double getFlValue() {
	double retValue;

	printf("�Ǽ� �Ǵ� ������ : ");
	scanf("%lf", &retValue);

	return retValue;
}

// ����ó�� �Լ�
void equalImage() {
	// ���� ���� �˰���
	// �Է� �迭 -> ��� �迭
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			outImage[i][j] = inImage[i][j];
		}
	}
	printImage();
}
void addImage(int val) {
	// ���ϱ�, ���� �˰���
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (val < 0) {
				if (inImage[i][j] + val >= 0) // val�� ������
					outImage[i][j] = inImage[i][j] + val;
				else
					outImage[i][j] = 0;
			}
			else {
				if (inImage[i][j] + val <= 255)
					outImage[i][j] = inImage[i][j] + val;
				else
					outImage[i][j] = 255;
			}
		}
	}
	printImage();
}
void reverseImage() {
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			outImage[i][j] = 255 - inImage[i][j];
		}
	}
	printImage();
}
void binaryImage(int val) {
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (inImage[i][j] > val) 
				outImage[i][j] = 255;
			else
				outImage[i][j] = 0;
		}
	}
	printImage();
}
int avgCalc() {
	int hap = 0;
	int result;
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			hap += inImage[i][j];
		}
	}
	result = hap / (height * width);
	printf("������ ��� ��: %d\n", result);
	return result;
}
int medCalc() { // ���Ŀ��� ����
	int median;
	int max = 0;
	unsigned char arr[256] = { 0 };

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			arr[inImage[i][j]] += 1;
		}
	}
	for (int i = 0; i < 256; i++) {
		if (arr[i] > max) {
			max = arr[i];
			median = i;
		}
	}
	printf("������ �߾� ��: %d\n", median);
	return median;
}
void gammaImage(double gam) {
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			outImage[i][j] = pow(((double)inImage[i][j] / 255.0), gam) * 255.0; // pow�� ��ȯ Ÿ���� double
		}
	}
	printImage();
}
void paraCAPImage() {
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			outImage[i][j] = 255.0 * pow(((double)inImage[i][j] / 127.0 - 1.0), 2.0); // CAP �Ķ󺼶� : ���� ���� ��ü������ ����
		}
	}
	printImage();
}
void paraCUPImage() {
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			outImage[i][j] = 255.0-255.0 * pow(((double)inImage[i][j] / 127.0 - 1.0), 2.0); // CUP �Ķ󺼶� : ��ο� ���� ��ü������ ����
		}
	}
	printImage();
}