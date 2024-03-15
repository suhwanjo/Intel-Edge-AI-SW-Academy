//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//#include <stdbool.h>
//#include <time.h>
//#include <stdlib.h>
//#include <math.h>
//#include <conio.h>
//#include <Windows.h> // GUI ���� ���
//
////////////////////////
//// ���� ������
////////////////////////
//
//// ������ API ���α׷���
//HWND hwnd; // �޵��� ȭ��(�ܺ�, ������)
//HDC hdc; // ������ ȭ��(����, ����)
//
//FILE *rfp, *wfp;
//char fileName[200];
//#define height 512
//#define width 512
//// �޸� Ȯ��
//unsigned char inImage[height][width];
//unsigned char outImage[height][width];
//
///////////////////////
//// �Լ� �����
///////////////////////
//void loadImage(); void saveImage();
//int getInValue(); double getFlValue();
//void printImage(); void printMenu();
//
//void equalImage();
//void addImage();
//void reverseImage();
//void binaryImage(); int medCalc(); int avgCalc();
//void gammaImage();
//void paraImage();
//void postImage();
//void emphImage();
//
//void main() {
//	hwnd = GetForegroundWindow();
//	hdc = GetWindowDC(NULL); // windows 10 : hwnd
//
//	char inKey = 0;
//	while (inKey != '9') {
//		printMenu(); // �޴� ���
//		inKey = _getch(); // �� ���� �Է� �ޱ�
//		system("cls"); // ȭ�� ����
//
//		switch (inKey) {
//		case '0': loadImage(); break;
//		case '1': saveImage(); break;
//		case '9': break;
//		case 'a':
//		case 'A': equalImage(); break;
//		case 'b':
//		case 'B': addImage(); break;
//		case 'c':
//		case 'C': reverseImage(); break;
//		case 'd':
//		case 'D': binaryImage(); break;
//		case 'e':
//		case 'E': gammaImage(); break;
//		case 'f':
//		case 'F': paraImage(); break;
//		case 'g':
//		case 'G': postImage(); break;
//		case 'h':
//		case 'H': emphImage(); break;
//		}
//	}
//}
//
/////////////////////
//// �Լ� ���Ǻ�
/////////////////////
//
//// ���� �Լ�
//void printMenu() {
//	puts("\b ## Gray Scale Image Processing (Beta 4) ##");
//	puts("\b--------------------------------------------");
//	puts("\b 0.���� 1.���� 9.����");
//	puts("\b--------------------------------------------");
//	puts("\b A.����         B.�������   C.���� ");
//	puts("\b D.����ȭ       E.��������   F.�Ķ󺼶�ȯ");
//	puts("\b G.�����Ͷ���¡ H.��������");
//	puts("\b--------------------------------------------");
//
//}
//void printImage() {
//	for (int i = 0; i < height; i++) {
//		for (int j = 0; j < width; j++) {
//			int px = outImage[i][j];
//			SetPixel(hdc, j + 50, i + 250, RGB(px, px, px)); // �Ѹ� ��ǥ, RGB ä�� ���� ������ Gray Scale
//		}
//		printf("\n");
//	}
//	printf("\n");
//}
//void loadImage() {
//	char fullName[200] = "D:/RAW/Pet_RAW(512x512)/";
//	char tmpName[50];
//	printf("���ϸ� : "); // cat01, dog05
//	scanf("%s", &tmpName);
//	strcat(fullName, tmpName); // D:/RAW/Pet_RAW(512x512)/cat01
//	strcat(fullName, "_512.raw"); // D:/RAW/Pet_RAW(512x512)/cat01_512.raw
//	strcat(fileName, fullName);
//
//	rfp = fopen(fileName, "rb");
//	fread(inImage, sizeof(unsigned char), height * width, rfp);
//	fclose(rfp);
//	equalImage();
//}
//void saveImage() {
//	char fullName[200] = "D:/RAW/Pet_RAW(512x512)/";
//	char tmpName[50];
//	printf("���ϸ� : "); // cat01, dog05
//	scanf("%s", &tmpName);
//	strcat(fullName, tmpName); // D:/RAW/Pet_RAW(512x512)/cat01
//	strcat(fullName, "_512.raw"); // D:/RAW/Pet_RAW(512x512)/cat01_512.raw
//	strcat(fileName, fullName);
//
//	wfp = fopen(fileName, "wb");
//	for (int i = 0; i < height; i++)
//		fwrite(outImage[i], sizeof(unsigned char), width, wfp);
//	fclose(wfp);
//	printf("���� �Ϸ�");
//	//MessageBox(hwnd, L"���� �Ϸ�", L"���� â", NULL);
//}
//int getInValue() {
//	int retValue;
//
//	printf("������ : ");
//	scanf("%d", &retValue);
//
//	return retValue;
//}
//double getFlValue() {
//	double retValue;
//
//	printf("�Ǽ� �Ǵ� ������ : ");
//	scanf("%lf", &retValue);
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
//void addImage() {
//	int val = getInValue();
//	// ���ϱ�, ���� �˰���
//	for (int i = 0; i < height; i++) {
//		for (int j = 0; j < width; j++) {
//			if (val < 0) {
//				if (inImage[i][j] + val >= 0) // val�� ������
//					outImage[i][j] = inImage[i][j] + val;
//				else
//					outImage[i][j] = 0;
//			}
//			else {
//				if (inImage[i][j] + val <= 255)
//					outImage[i][j] = inImage[i][j] + val;
//				else
//					outImage[i][j] = 255;
//			}
//		}
//	}
//	printImage();
//}
//void reverseImage() {
//	for (int i = 0; i < height; i++) {
//		for (int j = 0; j < width; j++) {
//			outImage[i][j] = 255 - inImage[i][j];
//		}
//	}
//	printImage();
//}
//void binaryImage() {
//	int val = 0;
//	printf("0.�����Է� 1.��հ� 2.�߾Ӱ� \n");
//	int option = getInValue();
//	if (option == 0)
//		val = getInValue();
//	else if (option == 1)
//		val = avgCalc();
//	else if (option == 2)
//		val = medCalc();
//
//	for (int i = 0; i < height; i++) {
//		for (int j = 0; j < width; j++) {
//			if (inImage[i][j] > val)
//				outImage[i][j] = 255;
//			else
//				outImage[i][j] = 0;
//		}
//	}
//	printImage();
//}
//int avgCalc() {
//	int hap = 0;
//	int result;
//	for (int i = 0; i < height; i++) {
//		for (int j = 0; j < width; j++) {
//			hap += inImage[i][j];
//		}
//	}
//	result = hap / (height * width);
//	printf("������ ��� ��: %d\n", result);
//	return result;
//}
//int medCalc() { // ���Ŀ��� ����
//	int median;
//	int max = 0;
//	unsigned char arr[256] = { 0 };
//
//	for (int i = 0; i < height; i++) {
//		for (int j = 0; j < width; j++) {
//			arr[inImage[i][j]] += 1;
//		}
//	}
//	for (int i = 0; i < 256; i++) {
//		if (arr[i] > max) {
//			max = arr[i];
//			median = i;
//		}
//	}
//	printf("������ �߾� ��: %d\n", median);
//	return median;
//}
//void gammaImage() {
//	printf("���� ���� �Է��ϼ��� \n");
//	double gam = getFlValue();
//	for (int i = 0; i < height; i++) {
//		for (int j = 0; j < width; j++) {
//			outImage[i][j] = pow(((double)inImage[i][j] / 255.0), gam) * 255.0; // pow�� ��ȯ Ÿ���� double
//		}
//	}
//	printImage();
//}
//void paraImage() { // ��� �� ���� ���� �߰� �ʿ�?
//	printf("0.CAP(���� ���� ��ü������) 1.CUP(��ο� ���� ��ü������) \n");
//	int option = getInValue();
//	if (option == 0) {
//		for (int i = 0; i < height; i++) {
//			for (int j = 0; j < width; j++) {
//				outImage[i][j] = 255.0 * pow(((double)inImage[i][j] / 127.0 - 1.0), 2.0); // CAP �Ķ󺼶� : ���� ���� ��ü������ ����
//			}
//		}
//		printImage();
//	}
//	else if (option == 1) {
//		for (int i = 0; i < height; i++) {
//			for (int j = 0; j < width; j++) {
//				outImage[i][j] = 255.0 - 255.0 * pow(((double)inImage[i][j] / 127.0 - 1.0), 2.0); // CUP �Ķ󺼶� : ��ο� ���� ��ü������ ����
//			}
//		}
//		printImage();
//	}
//}
//void postImage() {
//	for (int i = 0; i < height; i++) {
//		for (int j = 0; j < width; j++) {
//			if (inImage[i][j] >= 0 && inImage[i][j] <= 31)
//				outImage[i][j] = 31;
//			else if(inImage[i][j] > 31 && inImage[i][j] <= 63)
//				outImage[i][j] = 63;
//			else if (inImage[i][j] > 63 && inImage[i][j] <= 95)
//				outImage[i][j] = 95;
//			else if (inImage[i][j] > 95 && inImage[i][j] <= 127)
//				outImage[i][j] = 127;
//			else if (inImage[i][j] > 127 && inImage[i][j] <= 159)
//				outImage[i][j] = 159;
//			else if (inImage[i][j] > 159 && inImage[i][j] <= 191)
//				outImage[i][j] = 191;
//			else if (inImage[i][j] > 191 && inImage[i][j] <= 223)
//				outImage[i][j] = 223;
//			else if (inImage[i][j] > 223 && inImage[i][j] <= 255)
//				outImage[i][j] = 255;
//		}
//	}
//	printImage();
//}
//void emphImage() {
//	printf("������ �ȼ� ���� ������ �Է��ϼ��� \n");
//	printf("���� �ȼ� ");
//	int startVal = getInValue();
//	printf("�� �ȼ� ");
//	int endVal = getInValue();
//
//	for (int i = 0; i < height; i++) {
//		for (int j = 0; j < width; j++) {
//			if (inImage[i][j] > startVal && inImage[i][j] < endVal)
//				outImage[i][j] = 255;
//			else
//				outImage[i][j] = inImage[i][j];
//		}
//	}
//	printImage();
//}
//
