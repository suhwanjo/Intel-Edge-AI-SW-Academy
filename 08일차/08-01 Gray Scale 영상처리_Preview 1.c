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
void freeInputMemory(); void freeOutputMemory(); void mallocInputMemory(); void mallocOutputMemory(); double** mallocDoubleMemory(); void freeDoubleMemory(double**, int);
int getInValue(); double getFlValue();
void printImage(); void printMenu();

void equalImage();
void addImage(); void reverseImage(); void binaryImage(); int medCalc(); int avgCalc();
void gammaImage(); void paraImage(); void postImage(); void emphImage();
void scaleImage(); void rotatImage(); void moveImage(); void mirrorImage();
void histoStretch(); void histoEqual();
void emboss();

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
        case 'm':
        case 'M': histoStretch(); break;
        case 'n':
        case 'N': histoEqual(); break;
        case 'o':
        case 'O': emboss(); break;
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
    puts(" ---------------------------------------------------------------");
    puts("|  ## Gray Scale Image Processing (RC 2) ##                     |");
    puts("|---------------------------------------------------------------|");
    puts("|  0. ����     1. ����      9. ����                             |");
    puts("|---------------------------------------------------------------|");
    puts("|  A. ����             B. �������  C. ����                     |");
    puts("|  D. ����ȭ           E. ��������  F. �Ķ󺼸���ȯ             |");
    puts("|  G. �����Ͷ���¡     H. ��������  I. Ȯ��/���                |");
    puts("|  J. ȸ��             K. �̵�      L. �̷���(��Ī)             |");
    puts("|  M. ��ϴ��Ʈ��Ī N. ��Ȱȭ    O. ������/����/������     |");
    puts(" ---------------------------------------------------------------");
}
void printImage() {
    //system("cls");
    for (int i = 0; i < outH; i++) {
        for (int j = 0; j < outW; j++) {
            int px = outImage[i][j];
            SetPixel(hdc, j + 500, i + 500, RGB(px, px, px)); // �Ѹ� ��ǥ, RGB ä�� ���� ������ Gray Scale
        }
    }
}
void loadImage() { // �ϳ� ���� �� ���� ���� ��
    //char fullName[200] = "C:/Users/IOT/Desktop/Project1/Intel-Edge-AI-SW-Academy/RAW/";
    char fullName[200] = "C:/Users/shjo/Desktop/Intel-Edge-AI-SW-Academy/RAW/";
    char tmpName[50];
    printf("���ϸ� : "); // flower512, LENA256
    scanf("%s", &tmpName);
    strcat(fullName, tmpName); // D:/RAW/Pet_RAW(512x512)/cat01
    strcat(fullName, ".raw"); // D:/RAW/Pet_RAW(512x512)/cat01.raw
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
    char fullName[200] = "C:/Users/IOT/Desktop/Project1/Intel-Edge-AI-SW-Academy/RAW/";
    char tmpName[50];
    printf("���ϸ� : "); 
    scanf("%s", &tmpName);
    strcat(fullName, tmpName); 
    strcat(fullName, ".raw"); 
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
double** mallocDoubleMemory(int h, int w) {
    double **retMemory = (double**)malloc(sizeof(double*) * h);
    for (int i = 0; i < h; i++) {
        retMemory[i] = (double*)malloc(sizeof(double) * w);
    }

    return retMemory;
}
void freeDoubleMemory(double **memory, int h) {
    if (memory == NULL)
        return;
    for (int i = 0; i < outH; i++) {
        free(memory[i]);
    }
    free(memory);
    memory = NULL;
}
// ����ó�� �Լ�
// �� ��ȯ
void equalImage() { // ���� ���� �˰���
    // �Է� �迭 -> ��� �迭

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
void addImage() { // �������
    freeOutputMemory();
    outH = inH;
    outW = inW;
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
void reverseImage() { // ����
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
void binaryImage() { // ����ȭ
    freeOutputMemory();
    outH = inH;
    outW = inW;
    mallocOutputMemory();

    int val = 0;
    int option;
    while (1) {
        printf("�Ӱ谪 ���� ����� �����ϼ���. \n");
        printf("0.�����Է� 1.��հ� 2.�߾Ӱ� \n");
        option = getInValue();
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
    if (inImage == NULL)
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
    int count = 0;
    int median = 0;
    int arr[256] = { 0 };

    for (int i = 0; i < inH; i++) {
        for (int j = 0; j < inW; j++) {
            arr[inImage[i][j]] += 1;
        }
    }
    for (int i = 0; i < 256; i++) {
        count += arr[i];
        if (count >= (inH*inW / 2)) {
            median = i;
            break;
        }
    }
    printf("������ �߾� ��: %d\n", median);
    return median;
}
void gammaImage() { // ��������
    freeOutputMemory();
    outH = inH;
    outW = inW;
    mallocOutputMemory();
    double gam = 0;
    while (1) {
        printf("����(Gamma) ���� �Ҽ� ���·� �Է��ϼ���.(0.5~2.5) \n");
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
void paraImage() { // �Ķ󺼸���ȯ
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
void postImage() { // �����Ͷ���¡
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
void emphImage() { // ��������
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
            if ((inImage[i][j] > startVal && inImage[i][j] < endVal) || (inImage[i][j] < startVal && inImage[i][j] > endVal))
                outImage[i][j] = 255;
            else
                outImage[i][j] = inImage[i][j];
        }
    }
    printImage();
}
void histoStretch() { // ������׷�(���) ��Ʈ��Ī
    freeOutputMemory();
    outH = inH;
    outW = inW;
    mallocOutputMemory();

    // new = (old - low) / (high - low) * 255
    int high  = inImage[0][0]; // �ִ�, �ּ� ���� �� ó�� ������ ����
    int low = inImage[0][0];
    
    for (int i = 0; i < inH; i++) {
        for (int j = 0; j < inW; j++) {
            if (inImage[i][j] < low)
                low = inImage[i][j];
            if (inImage[i][j] > high)
                high = inImage[i][j];
        }
    }
    // End-In Ž�� : �ִ� �ּҰ� ���̸� ���� ��Ʈ��Ī ȿ���� �ش�ȭ
    // high -= 50;
    // low += 50;  
    //
    int old, new;
    for (int i = 0; i < inH; i++) {
        for (int j = 0; j < inW; j++) {
            old = inImage[i][j];
            new = (int)((old - low) / (double)(high - low) * 255.0);
            outImage[i][j] = new;
        }
    }
    printImage();
}
void histoEqual() { // ������׷� ��Ȱȭ
    freeOutputMemory();
    outH = inH;
    outW = inW;
    mallocOutputMemory();
    
    // 1�ܰ� : �󵵼� ����(=������׷�) histo[256]
    int histo[256] = { 0, };
    for (int i = 0; i < inH; i++)
        for (int j = 0; j < inW; j++)
            histo[inImage[i][j]]++;
    // 2�ܰ� : ����������׷� ����
    int sumHisto[256] = { 0, };
    sumHisto[0] = histo[0];
    for (int i = 1; i < 256; i++)
        sumHisto[i] = sumHisto[i - 1] + histo[i];
    // 3�ܰ� : ����ȭ�� ������׷� ����  normalHisto = sumHisto * (1.0 / (inH*inW) ) * 255.0;
    double normalHisto[256] = { 1.0, };
    for (int i = 0; i < 256; i++) {
        normalHisto[i] = sumHisto[i] * (1.0 / (inH * inW)) * 255.0;
    }
    // 4�ܰ� : inImage�� ����ȭ�� ������ ġȯ
    for (int i = 0; i < inH; i++) {
        for (int j = 0; j < inW; j++) {
            outImage[i][j] = (unsigned char)normalHisto[inImage[i][j]];
        }
    }
    printImage();
}
// ���� ��ȯ
void scaleImage() { // Ȯ��/���
    int scale = 1;
    printf("ũ�� ���� ������ �Է��ϼ���.(-:���, +:Ȯ��)\n");

    scale = getInValue();

    if (scale < 0) {
        scale = -scale;
        freeOutputMemory();
        outH = (int)(inH / scale);
        outW = (int)(inW / scale);
        mallocOutputMemory();

        //for (int i = 0; i < inH; i++) { // �ϳ��� ������ ���
        //    for (int j = 0; j < inW; j++) {
        //        outImage[i / scale][j / scale] = inImage[i][j];
        //    }
        //}

        // ���� ó�� ������ �ʹ� �����ϰ� �� -> ��귮 ����, ������ ����
        //int sum = 0;
        //int avg;
        //for (int i = 0; i < outH; i++) { // ��հ����� ���
        //    for (int j = 0; j < outW; j++) {
        //        sum = 0;
        //        for (int k = i * scale; k < ((i + 1) * scale); k++) {     // for(int k = 0; k < scale; k++)
        //            for (int q = j * scale; q < ((j + 1) * scale); q++) {      // for(int q = 0; q < scale; q++)
        //                sum += inImage[k][q];                                       // sum += inImage[i+k][j+q]; �� ��ü ����
        //            }
        //        }
        //        avg = (double)sum / (scale * scale);
        //        outImage[i][j] = avg;
        //    }
        //}

        int count, median;
        for (int i = 0; i < outH; i++) { // �߰������� ���
            for (int j = 0; j < outW; j++) {
                int histo[256] = { 0, };
                for (int k = i * scale; k < ((i + 1) * scale); k++) {
                    for (int q = j * scale; q < ((j + 1) * scale); q++) {
                        histo[inImage[k][q]] += 1;
                    }
                }
                count = 0;
                for (int a = 0; a < 256; a++) {
                    count += histo[a];
                    if (count >= (scale * scale) / 2) {
                        median = a;
                        break;
                    }
                }
                outImage[i][j] = median;
            }
        }

        //int max;
        //for (int i = 0; i < outH; i++) { // �ִ밪���� ���
        //    for (int j = 0; j < outW; j++) {
        //        int histo[256] = { 0, };
        //        for (int k = i * scale; k < ((i + 1) * scale); k++) {
        //            for (int q = j * scale; q < ((j + 1) * scale); q++) {
        //                histo[inImage[k][q]] += 1;
        //            }
        //        }
        //        max = 0;
        //        for (int a = 0; a < 256; a++) {
        //            if (histo[a] > max)
        //                max = a;
        //        }  
        //        outImage[i][j] = max;
        //    }
        //}
        printImage();
    }
    else if (scale > 0) {
        freeOutputMemory();
        outH = (int)inH * scale;
        outW = (int)inW * scale;
        mallocOutputMemory();

        //for (int i = 0; i < inH; i++) { // ������ ���� ���� == ������
        //   for (int j = 0; j < inW; j++) {
        //      outImage[i*2][j*2] = inImage[i][j];
        //   }
        //}
        for (int i = 0; i < outH; i++) { // ���� �ȼ� ������ == �����
            for (int k = 0; k < outW; k++) {
                outImage[i][k] = inImage[(int)(i / scale)][(int)(k / scale)];
            }
        }
        printImage();
    }
}
void rotatImage() { // ȸ��
    int degree = getInValue();
    double radian = -degree * PI / 180.0;
    freeOutputMemory();
    outH = (int)(inH * fabs(cos(radian)) + inW * fabs(sin(radian)));
    outW = (int)(inW * fabs(cos(radian)) + inH * fabs(sin(radian)));
    mallocOutputMemory();
    printf("%d %d", outH, outW);
    //xd = cos(xs) - sin(ys)
    //yd = sin(xs) + cos(ys)
    //for (int i = 0; i < inH; i++) { // ����, �������ϸ��� ���� �� �� ����
    //   for (int j = 0; j < inW; j++) {
    //      int xd = (int)(cos(radian) * i - sin(radian) * j);
    //      int yd = (int)(sin(radian) * i + cos(radian) * j);
    //      if((0<=xd && xd<outH) && (0<=yd && yd<outW))
    //         outImage[xd][yd] = inImage[i][j];
    //   }
    //}

    // �� ��Ȯ�� �߽����� �� �̵��ϴ��� �𸣰���
    int cx = outW / 2;
    int cy = outH / 2;
 
    int xs, ys;
    for (int i = 0; i < outH; i++) { // ����� + �߾����� �̵�
        for (int j = 0; j < outW; j++) {
            int xd = i;
            int yd = j;
            xs = (int)(cos(-radian) * (xd - cx) + sin(-radian) * (yd - cy));
            ys = (int)(-sin(-radian) * (xd - cx) + cos(-radian) * (yd - cy));
            xs += cx;
            ys += cy;
            if ((0 <= xs && xs < inH) && (0 <= ys && ys < inW))
                outImage[xd][yd] = inImage[xs][ys];
        }
    }
    printImage();
}
void moveImage() { // �̵�
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
void mirrorImage() { // �̷���(��Ī)
    freeOutputMemory();
    outH = inH;
    outW = inW;
    mallocOutputMemory();
    int mirror;
    while (1) {
        printf("��Ī ����� �����ϼ���.\n");
        printf("0.����, 1.�¿�\n");
        mirror = getInValue();
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
// ���� ��ȯ
void emboss() { // ������/����/������
    freeOutputMemory();
    outH = inH;
    outW = inW;
    mallocOutputMemory();

    int type;
    int size = 0;
    double embossMask[3][3];
    while (1) {
        printf("���� ó�� Ÿ���� �����ϼ���.(0.������ 1.���� 2.������ 3.������)\n");
        type = getInValue();
        printf("���� ������ �����ϼ���.(Ȧ���� ����)\n");
        size = getInValue();

        if (type == 0) { // ������ : ó���� -1,  ���� 1
            double mask[3][3] = { // ����ũ(. �ʼ�)
                { -1.0, 0.0, 0.0 },
                {0.0, 0.0, 0.0 },
                {0.0, 0.0, 1.0 } };
            for (int i = 0; i < size; i++) {
                for (int j = 0; j < size; j++) {
                    embossMask[i][j] = mask[i][j];
                }
            }
            break;
        }
        else if (type == 1) { // ���� : size * size �� ����
            double mask[3][3] = {
                { 1 / 9., 1 / 9., 1 / 9. },
                {1 / 9., 1 / 9., 1 / 9. },
                {1 / 9., 1 / 9., 1 / 9. } };
            for (int i = 0; i < size; i++) {
                for (int j = 0; j < size; j++) {
                    embossMask[i][j] = mask[i][j];
                }
            }
            break;
        }
        else if (type == 2) { // ������ : exp(-(x * x) / (2 * sigma * sigma)) / (sigma * sqrt(2 * PI))
            double mask[3][3] = {
                { 1 / 16., 1 / 8., 1 / 16. },
                {1 / 8., 1 / 4., 1 / 8. },
                {1 / 16., 1 / 8., 1 / 16. } };
            for (int i = 0; i < size; i++) {
                for (int j = 0; j < size; j++) {
                    embossMask[i][j] = mask[i][j];
                }
            }
            break;
        }
        else if (type == 3) { // ������ : �ֺ��� -1, �߾��� �ֺ��� (-��)
            double mask[3][3] = {
                { -1.0, -1.0, -1.0 },
                {-1.0, 9.0, -1.0 },
                {-1.0, -1.0, -1.0 } };
            for (int i = 0; i < size; i++) {
                for (int j = 0; j < size; j++) {
                    embossMask[i][j] = mask[i][j];
                }
            }
            break;
        }
        else
            printf("�߸��� �Է��Դϴ�. �ٽ� �õ��ϼ���.(0~3)\n");
    }
    // �ӽ� �̹��� �Ҵ�(�Ǽ�) : �е��� ����
    double** tmpInImage = mallocDoubleMemory(inH + 2, inW + 2); // ���� ũ�⿡ ���� �е� ��ȭ
    double** tmpOutImage = mallocDoubleMemory(outH + 2, outW + 2);
    // �ӽ� �̹��� �ʱ�ȭ(127)
    for (int i = 0; i < inH + 2; i++) {
        for (int j = 0; j < inW + 2; j++) {
            tmpInImage[i][j] = 127;
        }
    }
    // �Է� �̹��� -> �ӽ� �̹����� �ֱ�(�е� �Ϸ�)
    for (int i = 0; i < inH; i++) {
        for (int j = 0; j < inW; j++) {
            tmpInImage[i + 1][j + 1] = inImage[i][j];
        }
    }
    // ������� ����
    double sum;
    for (int i = 0; i < inH; i++) {
        for (int j = 0; j < inW; j++) {
            sum = 0;
            for (int k = 0; k < 3; k++) {
                for (int q = 0; q < 3; q++) {
                    sum += tmpInImage[i + k][j + q] * embossMask[k][q];
                }
            }
            tmpOutImage[i][j] = sum;
        }
    }
    // ����ũ ���� �տ� ���� ��ó�� (�����̸�)
    if (type == 0) {
        for (int i = 0; i < outH; i++) {
            for (int j = 0; j < outW; j++) {
                tmpOutImage[i][j] += 127.0;
            }
        }
    }
        //�ӽ� ��� ���� -> ��� ����
    for (int i = 0; i < outH; i++) {
        for (int j = 0; j < outW; j++) {
            if (tmpOutImage[i][j] < 0.0) 
                outImage[i][j] = 0;
            else if (tmpOutImage[i][j] > 255.0)
                outImage[i][j] = 255;
            else
                outImage[i][j] = (unsigned char)tmpOutImage[i][j];
        }
    }

    freeDoubleMemory(tmpInImage, inH + 2);
    freeDoubleMemory(tmpOutImage, outH);
    printImage();
        
    
}