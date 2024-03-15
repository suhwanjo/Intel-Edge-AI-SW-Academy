#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include <conio.h>
#include <Windows.h> // GUI ���� ���
#define PI 3.141592

//////////////////////
// ���� ������
//////////////////////

// ������ API ���α׷���
HWND hwnd; // �޵��� ȭ��(�ܺ�, ������)
HDC hdc; // ������ ȭ��(����, ����)

FILE* rfp, * wfp;
char fileName[200];
int inH, inW, outH, outW;
int width;
// �޸� Ȯ��
//unsigned char inImage[height][width];
//unsigned char outImage[height][width];
unsigned char** inImage, ** outImage = NULL;

/////////////////////
// �Լ� �����
/////////////////////
void loadImage(); void saveImage();
void freeInputMemory(); void freeOutputMemory(); void mallocInputMemory(); void mallocOutputMemory();
int getInValue(); double getFlValue();
void printImage(); void printMenu();

void equalImage();
void addImage(); void reverseImage(); void binaryImage(); int medCalc(); int avgCalc();
void gammaImage(); void paraImage(); void postImage(); void emphImage();
void scaleImage(); void rotatImage(); void moveImage(); void mirrorImage();

void main() {
	hwnd = GetForegroundWindow();
	hdc = GetWindowDC(NULL); // windows 10 : hwnd

	char inKey = 0;
	while (inKey != '9') {
		printMenu(); // �޴� ���
		inKey = _getch(); // �� ���� �Է� �ޱ�
		system("cls"); // ȭ�� ����

		switch (inKey) {
		case '0': loadImage(); break;
		case '1': saveImage(); break;
		case '9': break;
		case 'a':
		case 'A': equalImage(); break;
		case 'b':
		case 'B': addImage(); break;
		case 'c':
		case 'C': reverseImage(); break;
		case 'd':
		case 'D': binaryImage(); break;
		case 'e':
		case 'E': gammaImage(); break;
		case 'f':
		case 'F': paraImage(); break;
		case 'g':
		case 'G': postImage(); break;
		case 'h':
		case 'H': emphImage(); break;
		case 'i':
		case 'I': scaleImage(); break;
		case 'j':
		case 'J': rotatImage(); break;
		case 'k':
		case 'K': moveImage(); break;
		case 'l':
		case 'L': mirrorImage(); break;
		}
	}
	freeInputMemory();
	freeOutputMemory();
}

///////////////////
// �Լ� ���Ǻ�
///////////////////

// ���� �Լ�
void printMenu() {
	puts(" ----------------------------------------------");
	puts("|  ## Gray Scale Image Processing (RC 2) ##    |");
	puts("|----------------------------------------------|");
	puts("|  0. ����         1. ����      9. ����        |");
	puts("|----------------------------------------------|");
	puts("|  A. ����         B. �������  C. ����        |");
	puts("|  D. ����ȭ       E. ��������  F. �Ķ󺼸���ȯ|");
	puts("|  G. �����Ͷ���¡ H. ��������  I. Ȯ��/���   |");
	puts("|  J. ȸ��         K. �̵�      L. �̷���(��Ī)|");
	puts(" ----------------------------------------------");
}
void printImage() {
	//system("cls");
	for (int i = 0; i < outH; i++) {
		for (int j = 0; j < outW; j++) {
			int px = outImage[i][j];
			SetPixel(hdc, j + 50, i + 250, RGB(px, px, px)); // �Ѹ� ��ǥ, RGB ä�� ���� ������ Gray Scale
		}
	}
}
void loadImage() {
	char fullName[200] = "D:/RAW/";
	char tmpName[50];
	printf("���ϸ� : "); // flower512, LENA256
	scanf("%s", &tmpName);
	strcat(fullName, tmpName); // D:/RAW/Pet_RAW(512x512)/cat01
	strcat(fullName, ".raw"); // D:/RAW/Pet_RAW(512x512)/cat01_512.raw
	strcat(fileName, fullName);

	// (�߿�!) �̹����� ���� ���̸� ����
	rfp = fopen(fileName, "rb");
	fseek(rfp, 0L, SEEK_END); // ������ ������ �̵�
	long long fsize = ftell(rfp); // �� ���������? 512?
	fclose(rfp);
	// �޸� ����
	freeInputMemory();
	// ��=���� ũ�� ���ϱ�
	inH = inW = (int)sqrt(fsize);
	// �޸� �Ҵ�
	mallocInputMemory();

	// ���Ͽ��� �޸𸮷� �б�
	rfp = fopen(fileName, "rb");
	for (int i = 0; i < inH; i++) {
		fread(inImage[i], sizeof(unsigned char), inH, rfp);
	}
	fclose(rfp);

	equalImage();
}
void saveImage() {
	if (outImage == NULL)
		return;
	char fullName[200] = "D:/RAW/";
	char tmpName[50];
	printf("���ϸ� : "); // cat01, dog05
	scanf("%s", &tmpName);
	strcat(fullName, tmpName); // D:/RAW/Pet_RAW(512x512)/cat01
	strcat(fullName, ".raw"); // D:/RAW/Pet_RAW(512x512)/cat01_512.raw
	strcat(fileName, fullName);

	wfp = fopen(fileName, "wb");
	for (int i = 0; i < outH; i++)
		fwrite(outImage[i], sizeof(unsigned char), outW, wfp);
	fclose(wfp);
	printf("���� �Ϸ�\n");
	//MessageBox(hwnd, L"���� �Ϸ�", L"���� â", NULL);
}
int getInValue() {
	if (inImage == NULL)
		return 0;
	int retValue = 0;

	while (1) {
		printf("������ : ");
		if (scanf("%d", &retValue) != 1) {
			// �Է� ���� ó��
			printf("�߸��� �Է��Դϴ�. �ٽ� �õ��ϼ���.\n");
			// �Է� ���۸� ��� ���� �߻� ���� �Է��� �ùٸ��� ó��
			while (getchar() != '\n');
		}
		else 
			break;
		
	}
	return retValue;

}
double getFlValue() {
	if (inImage == NULL)
		return 0.0;
	double retValue = 0.0;

	while (1) {
		printf("�Ǽ� �Ǵ� ������ : ");
		if (scanf("%lf", &retValue) != 1) {
			printf("�߸��� �Է��Դϴ�. �ٽ� �õ��ϼ���.\n");
			while (getchar() != '\n');
		}
		else
			break;		
	}
	return retValue;
}
void freeInputMemory() {
	if (inImage == NULL)
		return;
	for (int i = 0; i < inH; i++) {
		free(inImage[i]);
	}
	free(inImage);
	inImage = NULL;
}
void freeOutputMemory() {
	if (inImage == NULL)
		return;
	for (int i = 0; i < outH; i++) {
		free(outImage[i]);
	}
	free(outImage);
	outImage = NULL;
}
void mallocInputMemory() {
	inImage = (unsigned char**)malloc(sizeof(unsigned char*) * inH);
	for (int i = 0; i < inH; i++) {
		inImage[i] = (unsigned char*)malloc(sizeof(unsigned char) * inW);
	}
}
void mallocOutputMemory() {
	outImage = (unsigned char**)malloc(sizeof(unsigned char*) * outH);
	for (int i = 0; i < outH; i++) {
		outImage[i] = (unsigned char*)malloc(sizeof(unsigned char) * outW);
	}
}
// ����ó�� �Լ�
// �� ��ȯ
void equalImage() {
	// ���� ���� �˰���
	// �Է� �迭 -> ��� �迭
	// 
	// �޸� ����
	freeOutputMemory();
	// (�߿�!) ��� �̹����� ũ�� ���� -> �˰��� ����
	outH = inH;
	outW = inW;
	//  �޸� �Ҵ�
	mallocOutputMemory();

	for (int i = 0; i < inH; i++) {
		for (int j = 0; j < inW; j++) {
			outImage[i][j] = inImage[i][j];
		}
	}
	printImage();
}
void addImage() {
	freeOutputMemory();
	// (�߿�!) ��� �̹����� ũ�� ���� -> �˰��� ����
	outH = inH;
	outW = inW;
	//  �޸� �Ҵ�
	mallocOutputMemory();
	printf("��� ���� ������ �Է��ϼ���.(-:��Ӱ�, +:���)");
	int val = getInValue();
	// ���ϱ�, ���� �˰���
	for (int i = 0; i < inH; i++) {
		for (int j = 0; j < inW; j++) {
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
	freeOutputMemory();
	// (�߿�!) ��� �̹����� ũ�� ���� -> �˰��� ����
	outH = inH;
	outW = inW;
	//  �޸� �Ҵ�
	mallocOutputMemory();

	for (int i = 0; i < inH; i++) {
		for (int j = 0; j < inW; j++) {
			outImage[i][j] = 255 - inImage[i][j];
		}
	}
	printImage();
}
void binaryImage() {
	freeOutputMemory();
	// (�߿�!) ��� �̹����� ũ�� ���� -> �˰��� ����
	outH = inH;
	outW = inW;
	//  �޸� �Ҵ�
	mallocOutputMemory();

	int val = 0;
	while (1) {
		printf("�Ӱ谪 ���� ����� �����ϼ���. \n");
		printf("0.�����Է� 1.��հ� 2.�߾Ӱ� \n");
		int option = getInValue();
		if (option == 0) {
			val = getInValue();
			break;
		}
		else if (option == 1) {
			val = avgCalc();
			break;
		}
		else if (option == 2) {
			val = medCalc();
			break;
		}
		else
			printf("�߸��� �Է��Դϴ�. �ٽ� �õ��ϼ���.(0,1,2)\n");
	}

	for (int i = 0; i < inH; i++) {
		for (int j = 0; j < inW; j++) {
			if (inImage[i][j] > val)
				outImage[i][j] = 255;
			else
				outImage[i][j] = 0;
		}
	}
	printImage();
}
int avgCalc() {
	if (outImage == NULL)
		return 0;
	int hap = 0;
	int result;
	for (int i = 0; i < inH; i++) {
		for (int j = 0; j < inW; j++) {
			hap += inImage[i][j];
		}
	}
	result = hap / (inH * inW);
	printf("������ ��� ��: %d\n", result);
	return result;
}
int medCalc() { // ���Ŀ��� ����
	if (inImage == NULL)
		return 0;
	int median;
	int max = 0;
	unsigned char arr[256] = { 0 };

	for (int i = 0; i < inH; i++) {
		for (int j = 0; j < inW; j++) {
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
void gammaImage() {
	freeOutputMemory();
	outH = inH;
	outW = inW;
	mallocOutputMemory();
	double gam = 0;
	while (1) {
		printf("����(Gamma) ���� �Է��ϼ���.(0.5~25) \n");
		gam = getFlValue();
		if (gam >= 0.5 && gam < 2.5) {
			for (int i = 0; i < inH; i++) {
				for (int j = 0; j < inW; j++) {
					outImage[i][j] = pow(((double)inImage[i][j] / 255.0), gam) * 255.0; // pow�� ��ȯ Ÿ���� double
				}
			}
			break;
		}
		else
			printf("�߸��� �Է��Դϴ�. �ٽ� �õ��ϼ���.(0.5~25)\n");
	}
	printImage();
}
void paraImage() { 
	freeOutputMemory();
	outH = inH;
	outW = inW;
	mallocOutputMemory();
	int option = 0;
	while (1) {
		printf("��ȯ ����� �����ϼ���. \n");
		printf("0.CAP(���� ���� ��ü������) 1.CUP(��ο� ���� ��ü������) \n");
		option = getInValue();
		if (option == 0) {
			for (int i = 0; i < inH; i++) {
				for (int j = 0; j < inW; j++) {
					outImage[i][j] = 255.0 * pow(((double)inImage[i][j] / 127.0 - 1.0), 2.0); // CAP �Ķ󺼶� : ���� ���� ��ü������ ����
				}
			}
			break;
		}
		else if (option == 1) {
			for (int i = 0; i < inH; i++) {
				for (int j = 0; j < inW; j++) {
					outImage[i][j] = 255.0 - 255.0 * pow(((double)inImage[i][j] / 127.0 - 1.0), 2.0); // CUP �Ķ󺼶� : ��ο� ���� ��ü������ ����
				}
			}
			break;
		}
		else
			printf("�߸��� �Է��Դϴ�. �ٽ� �õ��ϼ���.(0,1)\n");
	}
	printImage();
	
}
void postImage() {
	freeOutputMemory();
	outH = inH;
	outW = inW;
	mallocOutputMemory();

	for (int i = 0; i < inH; i++) {
		for (int j = 0; j < inW; j++) {
			if (inImage[i][j] >= 0 && inImage[i][j] <= 31)
				outImage[i][j] = 31;
			else if (inImage[i][j] > 31 && inImage[i][j] <= 63)
				outImage[i][j] = 63;
			else if (inImage[i][j] > 63 && inImage[i][j] <= 95)
				outImage[i][j] = 95;
			else if (inImage[i][j] > 95 && inImage[i][j] <= 127)
				outImage[i][j] = 127;
			else if (inImage[i][j] > 127 && inImage[i][j] <= 159)
				outImage[i][j] = 159;
			else if (inImage[i][j] > 159 && inImage[i][j] <= 191)
				outImage[i][j] = 191;
			else if (inImage[i][j] > 191 && inImage[i][j] <= 223)
				outImage[i][j] = 223;
			else if (inImage[i][j] > 223 && inImage[i][j] <= 255)
				outImage[i][j] = 255;
		}
	}
	printImage();
}
void emphImage() {
	freeOutputMemory();
	outH = inH;
	outW = inW;
	mallocOutputMemory();
	int startVal, endVal = 0;
	while (1) {
		printf("������ �ȼ� ���� ������ �Է��ϼ���.(0~255) \n");
		printf("���� �ȼ� ");
		startVal = getInValue();
		printf("�� �ȼ� ");
		endVal = getInValue();
		if ((startVal >= 0 && startVal <= 255) && (endVal >= 0 && endVal <= 255))
			break;
		else
			printf("�߸��� �Է��Դϴ�. �ٽ� �õ��ϼ���.(0~1)\n");
	}

	for (int i = 0; i < inH; i++) {
		for (int j = 0; j < inW; j++) {
			if ((inImage[i][j] > startVal && inImage[i][j] < endVal) || (inImage[i][j] > startVal && inImage[i][j] < endVal))
				outImage[i][j] = 255;
			else
				outImage[i][j] = inImage[i][j];
		}
	}
	printImage();
}
// ���� ��ȯ
void scaleImage() {
	int scale=1;
	printf("ũ�� ���� ������ �Է��ϼ���.(-:���, +:Ȯ��)\n");
	scale = getInValue();

	if (scale < 0) {
		scale = -scale;
		freeOutputMemory();
		outH = (int)(inH / scale);
		outW = (int)(inW / scale);
		mallocOutputMemory();

		for (int i = 0; i < inH; i++) {
			for (int j = 0; j < inW; j++) {
				outImage[i / scale][j / scale] = inImage[i][j];
			}
		}
		printImage();
		//for (int i = 0; i < outH; i++) { // ��հ� ���
		//	for (int j = 0; i < outW; j++) {
		//		int sum = 0;
		//		int avg = 0;
		//		for (int k = i * scale; k < ((i + 1) * scale) - scale; k++) {
		//			for (int q = j * scale; q < ((j + 1) * scale) - scale; q++) {
		//				if (k < inH && q < inW) {
		//					sum += inImage[k][q];
		//				}
		//			}
		//		}
		//		avg = (int)(sum / (scale * scale));
		//		outImage[i][j] = avg;
		//	}
		//}
		printImage();
	}
	else if (scale > 0) {
		freeOutputMemory();
		outH = (int)inH * scale;
		outW = (int)inW * scale;
		mallocOutputMemory();

		//for (int i = 0; i < inH; i++) { // ������ ���� ���� == ������
		//	for (int j = 0; j < inW; j++) {
		//		outImage[i*2][j*2] = inImage[i][j];
		//	}
		//}
		for (int i = 0; i < outH; i++) { // ���� �ȼ� ������ == �����
			for (int k = 0; k < outW; k++) {
				outImage[i][k] = inImage[(int)(i / scale)][(int)(k / scale)];
			}
		}
		// ���� ������ �����غ���

		printImage();
	}
}
void rotatImage() {
	freeOutputMemory();
	outH = inH;
	outW = inW;
	mallocOutputMemory();
	int degree = getInValue();
	double radian = degree * PI / 180.0;
	//xd = cos(xs) - sin(ys)
	//yd = sin(xs) + cos(ys)
	//for (int i = 0; i < inH; i++) { // ����, �������ϸ��� ���� �� �� ����
	//	for (int j = 0; j < inW; j++) {
	//		int xd = (int)(cos(radian) * i - sin(radian) * j);
	//		int yd = (int)(sin(radian) * i + cos(radian) * j);
	//		if((0<=xd && xd<outH) && (0<=yd && yd<outW))
	//			outImage[xd][yd] = inImage[i][j];
	//	}
	//}

	int cx = inH / 2;
	int cy = inW / 2;
	for (int i = 0; i < outH; i++) { // ����� + �߾����� �̵�
		for (int j = 0; j < outW; j++) {
			int xs = (int)(cos(radian) * (i-cx) + sin(radian) * (j-cy));
			int ys = (int)(-sin(radian) * (i-cx) + cos(radian) * (j-cy));
			xs += cx;
			ys += cy;
			if((0 <= xs && xs < outH) && (0 <= ys && ys < outW))
				outImage[i][j] = inImage[xs][ys];
		}
	}
	printImage();
}
void moveImage() {
	freeOutputMemory();
	outH = inH;
	outW = inW;
	mallocOutputMemory();

	int move = getInValue();
	if (move >= 0) { // ���� �ϴ����� �̵�
		for (int i = 0; i < outH - move; i++) {
			for (int j = 0; j < outW - move; j++) {
				if ((0 <= i && i < outH) && (0 <= j && j < outW))
					outImage[i + move][j + move] = inImage[i][j];
			}
		}
	}
	else // ���� ������� �̵�
		for (int i = 0; i < outH; i++) {
			for (int j = 0; j < outW; j++) {
				if ((0 - move <= i && i < outH) && (0 - move <= j && j < outW))
					outImage[i + move][j + move] = inImage[i][j];
			}
		}
	printImage();
}
void mirrorImage() {
	freeOutputMemory();
	outH = inH;
	outW = inW;
	mallocOutputMemory();
	
	while(1){
		printf("��Ī ����� �����ϼ���.\n");
		printf("0.����, 1.�¿�\n");
		int mirror = getInValue();
		if (mirror == 1) {
			for (int i = 0; i < outH; i++) {
				for (int j = 0; j < outW; j++) {
						outImage[i][-(j - outW + 1)] = inImage[i][j];
				}
			}
			break;
		}
		else if (mirror == 0) {
			for (int i = 0; i < outH; i++) {
				for (int j = 0; j < outW; j++) {
					outImage[-(i - outH + 1)][j] = inImage[i][j];
				}
			}
			break;
		}
		else
			printf("�߸��� �Է��Դϴ�. �ٽ� �õ��ϼ���.(0~1)\n");
	}
	printImage();
}
