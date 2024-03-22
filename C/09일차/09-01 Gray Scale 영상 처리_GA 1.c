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
void edgeLOG(); void edgeBetterLOG(); void edgeDOG();

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
        case 'B': addImage(); break; // ��� ����
        case 'c':
        case 'C': reverseImage(); break; // ����
        case 'd':
        case 'D': binaryImage(); break; // ����ȭ
        case 'e':
        case 'E': gammaImage(); break; // ���� ����
        case 'f':
        case 'F': paraImage(); break; // �Ķ󺼸� ��ȯ
        case 'g':
        case 'G': postImage(); break; // �����Ͷ���¡
        case 'h':
        case 'H': emphImage(); break; // ���� ����
        case 'i':
        case 'I': scaleImage(); break; // ũ�� ����
        case 'j':
        case 'J': rotatImage(); break; // ȸ��
        case 'k':
        case 'K': moveImage(); break; // �̵�
        case 'l':
        case 'L': mirrorImage(); break; // �̷���(��Ī)
        case 'm':
        case 'M': histoStretch(); break; // ������׷� ��Ʈ��Ī
        case 'n':
        case 'N': histoEqual(); break; // ������׷� ��Ȱȭ
        case 'o':
        case 'O': emboss(); break; // ������/������/������
        case 'p':
        case 'P': edgeLOG(); break; // ���� ����(LOG)
        case 'q': 
        case 'Q': edgeBetterLOG(); break; // ���� ����(LOG��귮����)
        case 'r':
        case 'R': edgeDOG(); break;
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
    puts(" ----------------------------------------------------------------------");
    puts("|  ## Gray Scale Image Processing (GA 1) ##                            |");
    puts("|----------------------------------------------------------------------|");
    puts("|  0. ����     1. ����      9. ����                                    |");
    puts("|----------------------------------------------------------------------|");
    puts("|  A. ����             B. �������      C. ����                        |");
    puts("|  D. ����ȭ           E. ��������      F. �Ķ󺼸���ȯ                |");
    puts("|  G. �����Ͷ���¡     H. ��������      I. Ȯ��/���                   |");
    puts("|  J. ȸ��             K. �̵�          L. �̷���(��Ī)                |");
    puts("|  M. ��ϴ��Ʈ��Ī N. ��Ȱȭ        O. ������/����/������/������ |");
    puts("|  P. ��������(LOG)    Q. LOG��귮���� R. ��������(DOG)               |");
    puts(" ----------------------------------------------------------------------");
}
void printImage() {
    for (int i = 0; i < outH; i++) {
        for (int j = 0; j < outW; j++) {
            int px = outImage[i][j];
            SetPixel(hdc, j + 500, i + 500, RGB(px, px, px)); // �Ѹ� ��ǥ, RGB ä�� ���� ������ Gray Scale
        }
    }
    //system("cls");
}
void loadImage() { // �ϳ� ���� �� ���� ���� ��
    fileName[0] = '\0'; // �������� ���� ���⸦ ���� ���� ���� �ʱ�ȭ

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
    if (rfp == NULL) {
        printf("������ �� �� �����ϴ�.\n");
        return;
    }
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
    if (rfp == NULL) {
        printf("������ �� �� �����ϴ�.\n");
        return;
    }
    for (int i = 0; i < inH; i++) {
        fread(inImage[i], sizeof(unsigned char), inH, rfp);
    }
    fclose(rfp);

    equalImage();
}
void saveImage() {
    if (inImage == NULL)
        return;
    fileName[0] = '\0';
    char fullName[200] = "C:/Users/IOT/Desktop/Project1/Intel-Edge-AI-SW-Academy/RAW/";
    char tmpName[50];
    printf("���ϸ� : ");
    scanf("%s", &tmpName);
    strcat(fullName, tmpName);
    strcat(fullName, ".raw");
    strcat(fileName, fullName);

    wfp = fopen(fileName, "wb");
    //printf("%s", fileName);
    if (wfp == NULL) {
        printf("������ �� �� �����ϴ�.\n");
        return;
    }
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
    double** retMemory = (double**)malloc(sizeof(double*) * h);
    for (int i = 0; i < h; i++) {
        retMemory[i] = (double*)malloc(sizeof(double) * w);
    }

    return retMemory;
}
void freeDoubleMemory(double** memory, int h) {
    if (memory == NULL)
        return;
    for (int i = 0; i < h; i++) {
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
    if (inImage == NULL)
        return;
    freeOutputMemory();
    outH = inH;
    outW = inW;
    mallocOutputMemory();

    printf("��� ���� ������ �Է��ϼ���.(-:��Ӱ�, +:���)\n");
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
    if (inImage == NULL)
        return;
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
    if (inImage == NULL)
        return;
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
        if (count >= (inH * inW / 2)) {
            median = i;
            break;
        }
    }
    printf("������ �߾� ��: %d\n", median);
    return median;
}
void gammaImage() { // ��������
    if (inImage == NULL)
        return;
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
            printf("�߸��� �Է��Դϴ�. �ٽ� �õ��ϼ���.(0.5~2.5)\n");
    }
    printImage();
}
void paraImage() { // �Ķ󺼸���ȯ
    if (inImage == NULL)
        return;
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
    if (inImage == NULL)
        return;
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
    if (inImage == NULL)
        return;
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
            printf("�߸��� �Է��Դϴ�. �ٽ� �õ��ϼ���.(0~255)\n");
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
    if (inImage == NULL)
        return;
    freeOutputMemory();
    outH = inH;
    outW = inW;
    mallocOutputMemory();

    // new = (old - low) / (high - low) * 255
    int high = inImage[0][0]; // �ִ�, �ּ� ���� �� ó�� ������ ����
    int low = inImage[0][0];

    for (int i = 0; i < inH; i++) {
        for (int j = 0; j < inW; j++) {
            if (inImage[i][j] < low)
                low = inImage[i][j];
            if (inImage[i][j] > high)
                high = inImage[i][j];
        }
    }
    // high -= 50;
    // low += 50;  
    //
    int old, new;
    for (int i = 0; i < inH; i++) {
        for (int j = 0; j < inW; j++) {
            // End-In Ž�� : �ִ� �ּҰ� ���̸� ���� ��Ʈ��Ī ȿ���� �ش�ȭ
            // new = (old - low) / (high - low) * 255
            old = inImage[i][j];
            new = (int)((old - low) / (double)(high - low) * 255.0);
            if (new > 255)
                new = 255;
            if (new < 0)
                new = 0;
            outImage[i][j] = new;
        }
    }
    printImage();
}
void histoEqual() { // ������׷� ��Ȱȭ
    if (inImage == NULL)
        return;
    freeOutputMemory();
    outH = inH;
    outW = inW;
    mallocOutputMemory();

    
    int histo[256] = { 0, };
    for (int i = 0; i < inH; i++)
        for (int j = 0; j < inW; j++)
            // 1�ܰ� : �󵵼� ����(=������׷�) histo[256]
            histo[inImage[i][j]]++;
    // 2�ܰ� : ����������׷� ����
    int sumHisto[256] = { 0, };
    sumHisto[0] = histo[0];
    for (int i = 1; i < 256; i++)
        // 2�ܰ� : ����������׷� ����
        sumHisto[i] = sumHisto[i - 1] + histo[i];
    // 3�ܰ� : ����ȭ�� ������׷� ����  normalHisto = sumHisto * (1.0 / (inH*inW) ) * 255.0;
    double normalHisto[256] = { 1.0, };
    for (int i = 0; i < 256; i++) {
        // 3�ܰ� : ����ȭ�� ������׷� ����
        normalHisto[i] = sumHisto[i] * (1.0 / (inH * inW)) * 255.0;
    }
    // 4�ܰ� : inImage�� ����ȭ�� ������ ġȯ
    for (int i = 0; i < inH; i++) {
        for (int j = 0; j < inW; j++) {
            // 4�ܰ� : inImage�� ����ȭ�� ������ ġȯ
            outImage[i][j] = (unsigned char)normalHisto[inImage[i][j]];
        }
    }
    printImage();
}
// ���� ��ȯ
void scaleImage() { // Ȯ��/���
    if (inImage == NULL)
        return;
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
                        // ������׷� ���
                        histo[inImage[k][q]] += 1;
                    }
                }
                count = 0;
                for (int a = 0; a < 256; a++) {
                    count += histo[a];
                    // �߰� �� ���
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
    else {
        outH = inH;
        outW = inW;
        for (int i = 0; i < outH; i++) {
            for (int k = 0; k < outW; k++) {
                outImage[i][k] = inImage[i][k];
            }
        }
    }
        // �缱�� ���� -> ����
        // �ֺ� 4�� ã��
        // ����

        printImage();
    }
}
void rotatImage() { // ȸ��
    if (inImage == NULL)
        return;

    int degree = getInValue();
    double tmp_radian = degree % 90 * PI / 180.0;
    double tmp_radian90 = (90 - degree % 90) * PI / 180.0;
    freeOutputMemory();
    // ȸ�� ������ ���� ��� ������ Ȯ��
    outH = (int)(inH * cos(tmp_radian90) + inW * cos(tmp_radian));
    outW = (int)(inW * cos(tmp_radian) + inH * cos(tmp_radian90));
    double angle = degree * PI / 180.0;
    mallocOutputMemory();
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
    // ������ �߸��� ����
    int dx = (outW - inW) / 2;
    int dy = (outH - inH) / 2;
    unsigned char** tmpImage = (unsigned char**)malloc(sizeof(unsigned char*)*outH);
    for (int i = 0; i < outH; i++) {
        tmpImage[i] = (unsigned char*)malloc(sizeof(unsigned char) * outW);
    }
    for (int i = 0; i < inH; i++)
        for (int j = 0; j < inW; j++)
            // ��� ũ���� �ӽ� ����, �߾ӿ� (0,0) ������ �̵�
            tmpImage[i + dx][j + dy] = inImage[i][j];

    int cx = outH / 2;
    int cy = outW / 2;
    int xs, ys;
    for (int i = 0; i < outH; i++) { 
        for (int j = 0; j < outW; j++) {
            int xd = i;
            int yd = j;
            // ����� + �߾����� �̵�
            xs = (int)(cos(angle) * (xd - cx) + sin(angle) * (yd - cy)) + cx;
            ys = (int)(-sin(angle) * (xd - cx) + cos(angle) * (yd - cy)) + cy;
            if ((0 <= xs && xs < outH) && (0 <= ys && ys < outW))
                outImage[xd][yd] = tmpImage[xs][ys];
        }
    }

    // �ӽ� ���� �޸� ����
    //for (int i = 0; i < outH; i++) {
    //    free(tmpImage[i]);
    //}
    //free(tmpImage);

    printImage();
}
void moveImage() { // �̵�
    if (inImage == NULL)
        return;
    freeOutputMemory();
    outH = inH;
    outW = inW;
    mallocOutputMemory();

    int move = getInValue();
    if (move >= 0) { // ���� �ϴ����� �̵�
        for (int i = 0; i < outH - move; i++) {
            for (int j = 0; j < outW - move; j++) {
                // ���� �ϴ�
                if ((0 <= i && i < outH) && (0 <= j && j < outW))
                    outImage[i + move][j + move] = inImage[i][j];
            }
        }
    }
    else // ���� ������� �̵�
        for (int i = 0; i < outH; i++) {
            for (int j = 0; j < outW; j++) {
                // ���� ���
                if ((0 - move <= i && i < outH) && (0 - move <= j && j < outW))
                    outImage[i + move][j + move] = inImage[i][j];
            }
        }
    printImage();
}
void mirrorImage() { // �̷���(��Ī)
    if (inImage == NULL)
        return;
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
                    // ��-��
                    outImage[i][-(j - outW + 1)] = inImage[i][j];
                }
            }
            break;
        }
        else if (mirror == 0) {
            for (int i = 0; i < outH; i++) {
                for (int j = 0; j < outW; j++) {
                    // ��-��
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
    if (inImage == NULL)
        return;
    freeOutputMemory();
    outH = inH;
    outW = inW;
    mallocOutputMemory();

    int type, size;
    while (1) {
        printf("ȿ���� ������ ����(����ũ ũ��)�� �Է��ϼ���.(Ȧ���� ����)\n");
        size = getInValue();
        if (size % 2 == 0)
            printf("�߸��� �Է��Դϴ�. �ٽ� �õ��ϼ���.(Ȧ��)\n");
        else
            break;
    }

    int center = size / 2;
    double** mask = mallocDoubleMemory(size, size);
    while (1) {
        printf("���� ó�� Ÿ���� �����ϼ���.(0.������ 1.���� 2.������ 3.������)\n");
        type = getInValue();
        if (type == 0) { // ������ : ó���� -1,  ���� 1
            for (int i = 0; i < size; i++) {
                for (int j = 0; j < size; j++) {
                    // ������ ����ũ ����
                    if (i == 0 && j == 0)
                        mask[i][j] = -1.0;
                    else if (i == size - 1 && j == size - 1)
                        mask[i][j] = 1.0;
                    else
                        mask[i][j] = 0.0;
                }
            }
            break;
        }
        else if (type == 1) { // ���� : size * size �� ����
            for (int i = 0; i < size; i++) {
                for (int j = 0; j < size; j++) {
                    // ���� ����ũ ����
                    mask[i][j] = 1 / (double)(size * size);
                }
            }
            break;
        }
        else if (type == 2) { // ������ : exp(-(x * x) / (2 * sigma * sigma)) / (sigma * sqrt(2 * PI)) -> �ñ׸� �Է� �ް� x(�߽����κ����� �Ÿ�) ���ϱ� 
            double sigma;
            while (1) {
                printf("������ ������ ����(Sigma)�� �Է��ϼ���.(0.5~5.0)\n");
                sigma = getFlValue();
                if ((sigma < 0.5) || (sigma > 5.0))
                    printf("�߸��� �Է��Դϴ�. �ٽ� �õ��ϼ���.(0.5~5.0)\n");
                else
                    break;
            }
            double gaussian;
            for (int i = 0; i < size; i++) {
                for (int j = 0; j < size; j++) {
                    // ����þ� ����ũ ����
                    double x = sqrt((pow((i - center), 2)+ pow((j - center), 2)));
                    gaussian = exp(-(x * x) / (2.0 * sigma * sigma)) / (sigma * sqrt(2.0 * PI));
                    mask[i][j] = gaussian;
                }
            }
            break;
        }
        else if (type == 3) { // ������ : �ֺ��� -1, �߾��� �迭 ũ��
            for (int i = 0; i < size; i++) {
                for (int j = 0; j < size; j++) {
                    // ������ ����ũ ����
                    if (i == center && j == center)
                        mask[i][j] = (double)size * size;
                    else
                        mask[i][j] = -1.0;
                }
            }
            break;
        }
        else
            printf("�߸��� �Է��Դϴ�. �ٽ� �õ��ϼ���.(0~3)\n");
    }
    // �ӽ� �̹��� �Ҵ�(�Ǽ�) : �е��� ����
    double** tmpInImage = mallocDoubleMemory(inH + (size - 1), inW + (size - 1)); // ���� ũ�⿡ ���� �е� ��ȭ
    double** tmpOutImage = mallocDoubleMemory(outH, outW);
    // �ӽ� �̹��� �ʱ�ȭ(127)
    for (int i = 0; i < inH + (size - 1); i++) {
        for (int j = 0; j < inW + (size - 1); j++) {
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
            for (int k = 0; k < size; k++) {
                for (int q = 0; q < size; q++) {
                    sum += tmpInImage[i + k][j + q] * mask[k][q];
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
    for (int i = 0; i < outH; i++) {
        for (int j = 0; j < outW; j++) {
            //�ӽ� ��� ���� -> ��� ����
            if (tmpOutImage[i][j] < 0.0)
                outImage[i][j] = 0;
            else if (tmpOutImage[i][j] > 255.0)
                outImage[i][j] = 255;
            else
                outImage[i][j] = (unsigned char)tmpOutImage[i][j];
        }
    }

    freeDoubleMemory(tmpInImage, inH + (size - 1));
    freeDoubleMemory(tmpOutImage, outH);
    freeDoubleMemory(mask, size);
    printImage();
}
void edgeLOG() { // ����þ� ���� -> ���ö�þ� ���� -> zero-crossing
    if (inImage == NULL)
        return;
    freeOutputMemory();
    outH = inH;
    outW = inW;
    mallocOutputMemory();

    //double mask[5][5] // LOG ����
    //    = { {0.0, 0.0, -1.0, 0,0, 0.0} ,
    //        {0.0, -1.0, -2.0, -1,0, 0.0} ,
    //        {-1.0, -2.0, 16.0, -2.0, -1.0},
    //        {0.0,-1.0, -2.0, -1,0, 0.0} ,
    //        {0.0, 0.0, -1.0, 0.0, 0.0} };

    int t;
    while (1) {
        printf("������ �󸶳� ã�����?(0~255)\n");
        t = getInValue();
        if ((t < 0) || (t > 255))
            printf("�߸��� �Է��Դϴ�. �ٽ� �õ��ϼ���.(0~255)\n");
        else
            break;
    }
    double gaussMask[3][3];
    double gaussian;
    // 3x3 ũ���� �ñ׸� 0.5�� ����þ� ����ũ ����
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            // 3x3 ����þ� ����ũ
            double x = sqrt((pow((i - 1), 2) + pow((j - 1), 2)));
            gaussian = exp(-(x * x) / (2.0 * 0.5 * 0.5)) / (0.5 * sqrt(2.0 * PI));
            gaussMask[i][j] = gaussian;
        }
    }
    // ���ö�þ� ����ũ ����
    double laplaceMask[3][3] = {
        {0.0, 1.0, 0.0},
        {1.0, -4.0, 1.0},
        {0.0, 1.0, 0.0}
    };
    double** tmpInImage = mallocDoubleMemory(inH + 2,inW + 2);
    double** tmpOutImage = mallocDoubleMemory(outH,outW);

    // �е�1
    for (int i = 0; i < inH; i++) {
        for (int j = 0; j < inW; j++) {
            tmpInImage[i + 1][j + 1] = inImage[i][j];
        }
    }
    // log�� ������ �ΰ��ϱ� ������ ����þ� ����ũ�� ���� �� ó��
    double sum;
    for (int i = 0; i < inH; i++) {
        for (int j = 0; j < inW; j++) {
            sum = 0;
            for (int k = 0; k < 3; k++) {
                for (int q = 0; q < 3; q++) {
                    // ����þ� ����ũ�� ���� �� ó��
                    sum += tmpInImage[i + k][j + q] * gaussMask[k][q];
                }
            }
            tmpOutImage[i][j] = sum;
        }
    }
    // �е�2
    for (int i = 0; i < inH; i++) {
        for (int j = 0; j < inW; j++) {
            tmpInImage[i + 1][j + 1] = tmpOutImage[i][j];
        }
    }
    // ���ö�þ� ����ũ�� ���� ���� ����
    for (int i = 0; i < inH; i++) {
        for (int j = 0; j < inW; j++) {
            sum = 0;
            for (int k = 0; k < 3; k++) {
                for (int q = 0; q < 3; q++) {
                    sum += tmpInImage[i + k][j + q] * laplaceMask[k][q];
                }
            }
            tmpOutImage[i][j] = sum;
        }
    }
    // �е�3
    for (int i = 0; i < inH; i++) {
        for (int j = 0; j < inW; j++) {
            tmpInImage[i + 1][j + 1] = tmpOutImage[i][j];
        }
    }
    // zero-crossing
    int isEgde;
    for (int j = 1; j < inH - 1; j++) {
        for (int k = 1; k < inW - 1; k++) {
            int sum = 0;

            // ���� 45�� ���⿡�� ��ȣ�� �ٲ���� Ȯ��
            if (tmpInImage[j - 1][k - 1] * tmpInImage[j + 1][k + 1] < 0) { // �ٲ�ٸ� �� ���̰� �Ӱ谪���� ū�� Ȯ��
                isEgde = abs(tmpInImage[j - 1][k - 1]) + abs(tmpInImage[j + 1][k + 1]);
                if (isEgde >= t) {
                    sum += 1;
                }
            }

            // ���� 45�� ���⿡�� ��ȣ�� �ٲ���� Ȯ��
            if (tmpInImage[j + 1][k - 1] * tmpInImage[j - 1][k + 1] < 0) {
                isEgde = abs(tmpInImage[j - 1][k - 1]) + abs(tmpInImage[j - 1][k + 1]);
                if (isEgde >= t) {
                    sum += 1;
                }
            }

            // ���� ���⿡�� ��ȣ�� �ٲ���� Ȯ��
            if (tmpInImage[j][k - 1] * tmpInImage[j][k + 1] < 0) {
                isEgde = abs(tmpInImage[j][k - 1]) + abs(tmpInImage[j][k + 1]);
                if (isEgde >= t) {
                    sum += 1;
                }
            }

            // ���� ���⿡�� ��ȣ�� �ٲ���� Ȯ��
            if (tmpInImage[j - 1][k] * tmpInImage[j + 1][k] < 0) {
                isEgde = abs(tmpInImage[j - 1][k]) + abs(tmpInImage[j + 1][k]);
                if (isEgde >= t) {
                    sum += 1;
                }
            }

            // ��ȣ�� �ٲ�� �ְ� �� ���̰� �Ӱ谪���� ū ��찡 2�� �̻��̸� ���� ó��
            if (sum >= 2) {
                tmpInImage[j][k] = 255.0;
            }
        }
    }
    // �ӽ� ��� ���� -> ��� ����
    for (int i = 1; i < outH - 1; i++) {
        for (int j = 1; j < outW - 1; j++) {
            if (tmpInImage[i][j] < 0.0)
                outImage[i-1][j-1] = 0;
            else if (tmpInImage[i][j] > 255.0)
                outImage[i-1][j-1] = 255;
            else
                outImage[i-1][j-1] = (unsigned char)tmpInImage[i][j];
        }
    }
    freeDoubleMemory(tmpInImage, inH + 2);
    freeDoubleMemory(tmpOutImage, outH);
    printImage();
}
// �ɴϿ� ����
void edgeBetterLOG() { // ����þ� x,y �̺� -> �Է� ���� ���� -> ���� ���� ��� -> ����ȭ
    if (inImage == NULL)
        return;
    freeOutputMemory();
    outH = inH;
    outW = inW;
    mallocOutputMemory();

    //double mask[9][9] = { // DOG ����
    //    {0.0, 0.0, 0.0, -1.0, -1.0, -1.0, 0.0, 0.0, 0.0},
    //    {0.0, -2.0, -3.0, -3.0, -3.0, -3.0, -3.0, -2.0, 0.0},
    //    {0.0, -3.0, -2.0, -1.0, -1.0, -1.0, -2.0, -3.0, 0.0},
    //    {0.0, -3.0, -1.0, 9.0, 9.0, 9.0, -1.0, -3.0, 0.0},
    //    {-1.0, -3.0, -1.0, 9.0, 19.0, 9.0, -1.0, -3.0, -1.0},
    //    {0.0, -3.0, -1.0, 9.0, 9.0, 9.0, -1.0, -3.0, 0.0},
    //    {0.0, -3.0, -2.0, -1.0, -1.0, -1.0, -2.0, -3.0, 0.0},
    //    {0.0, -2.0, -3.0, -3.0, -3.0, -3.0, -3.0, -2.0, 0.0},
    //    {0.0, 0.0, 0.0, -1.0, -1.0, -1.0, 0.0, 0.0, 0.0}
    //    };
    
    int t;
    while (1) {
        printf("������ �󸶳� ã�����?(0~255)\n");
        t = getInValue();
        if ((t < 0) || (t > 255))
            printf("�߸��� �Է��Դϴ�. �ٽ� �õ��ϼ���.(0~255)\n");
        else
            break;
    }
    double gaussMask[3][3];
    double gaussian;
    // 3x3 ũ���� �ñ׸� 0.5�� ����þ� ����ũ ����
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            double x = sqrt((pow((i - 1), 2) + pow((j - 1), 2)));
            gaussian = exp(-(x * x) / (2.0 * 0.5 * 0.5)) / (0.5 * sqrt(2.0 * PI));
            gaussMask[i][j] = gaussian;
        }
    }
    // �̺п����� ���� sobel ����ũ
    double sobelX[3][3] = {
        {-1.0, 0.0, 1.0},
        {-2.0, 0.0, 2.0},
        {-1.0, 0.0, 1.0}
    };
    double sobelY[3][3] = {
        {-1.0, -2.0, -1.0},
        {0.0, 0.0, 0.0},
        {1.0, 2.0, 1.0}
    };
    // ����þ� ����ũ �̺� ����
    double sumX, sumY;
    double gaussX[5][5] = { 0.0, };
    double gaussY[5][5] = { 0.0, };
    double sobelGaussX[3][3];    double sobelGaussY[3][3];

    // ����þ� ����ũ �е�
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            gaussX[i + 1][j + 1] = gaussMask[i][j];
            gaussY[i + 1][j + 1] = gaussMask[i][j];
        }
    }
    // �������
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            sumX = 0.0;
            sumY = 0.0;
            for (int k = 0; k < 3; k++) {
                for (int q = 0; q < 3; q++) {
                    sumX += gaussX[i + k][j + q] * sobelX[k][q];
                    sumY += gaussY[i + k][j + q] * sobelY[k][q];
                }
            }
            sobelGaussX[i][j] = sumX; // �̺е� ����þ� ����ũ
            sobelGaussY[i][j] = sumY;
        }
    }
    // �̺е� ����þ� ���͸� ���� ����
    double** tmpInImageX = mallocDoubleMemory(inH + 2, inW + 2);
    double** tmpInImageY = mallocDoubleMemory(inH + 2,inW + 2);
    double** tmpOutImage = mallocDoubleMemory(outH, outW);
    // �Է� ���� �е�
    for (int i = 0; i < inH; i++) {
        for (int j = 0; j < inW; j++) {
            tmpInImageX[i + 1][j + 1] = inImage[i][j];
            tmpInImageY[i + 1][j + 1] = inImage[i][j];
        }
    }
    // �������
    double dogX, dogY;
    for (int i = 0; i < inH; i++) {
        for (int j = 0; j < inW; j++) {
            dogX = 0.0;
            dogY = 0.0;
            for (int k = 0; k < 3; k++) {
                for (int q = 0; q < 3; q++) {
                    dogX += tmpInImageX[i + k][j + q] * sobelGaussX[k][q];
                    dogY += tmpInImageY[i + k][j + q] * sobelGaussY[k][q];
                }
            }
            tmpOutImage[i][j] = fabs(dogX) + fabs(dogY); // ���� ���� ���
        }
    }
    // �Ӱ� ������ ����ȭ
    for (int i = 0; i < outH; i++) {
        for (int j = 0; j < outW; j++) {
            if (tmpOutImage[i][j] > t)
                tmpOutImage[i][j] = 255.0;
            else
                tmpOutImage[i][j] = 0.0;
        }
    }
    //�ӽ� ��� ���� -> ��� ����
    for (int i = 0; i < outH; i++) {
        for (int j = 0; j < outW; j++) {
            outImage[i][j] = (unsigned char)tmpOutImage[i][j];
        }
    }
    freeDoubleMemory(tmpInImageX, inH + 2);
    freeDoubleMemory(tmpInImageY, inH + 2);
    freeDoubleMemory(tmpOutImage, outH);
    printImage();
}
void edgeDOG() {
    if (inImage == NULL)  // �Է� �̹����� ������ �Լ� ����
        return;
    freeOutputMemory();  // ��� �޸� ����
    outH = inH;  // ��� �̹����� ���̸� �Է� �̹����� ���̷� ����
    outW = inW;  // ��� �̹����� �ʺ� �Է� �̹����� �ʺ�� ����
    mallocOutputMemory();  // ��� �޸� �Ҵ�

    double mask[9][9]
        = { {0,0,0,-1,-1,-1,0,0,0},
            {0,-2,-3,-3,-3,-3,-3,-2,0},
            {0,-3,-2,-1,-1,-1,-2,-3,0},
            {0,-3,-1,9,9,9,-1,-3,0},
            {-1,-3,-1,9,19,9,-1,-3,-1},
            {0,-3,-1,9,9,9,-1,-3,0},
            {0,-3,-2,-1,-1,-1,-2,-3,0},
            {0,-2,-3,-3,-3,-3,-3,-2,0},
            {0,0,0,-1,-1,-1,0,0,0}
    };
    // �ӽ� �Է�/��� �޸� �غ�
    double** tmpInput = mallocDoubleMemory(inH + 8, inW + 8); //�������� ����ŷ�� �����ϰ� �ϱ�����.(�о��� �������� ������ ����)
    double** tmpOutput = mallocDoubleMemory(outH, outW);
    for (int i = 0; i < inH; i++) {
        for (int k = 0; k < inW; k++) {
            tmpInput[i + 4][k + 4] = inImage[i][k];
        }
    }

    // ��¥ ���� ó�� �˰��� ==> ȸ������
    double S = 0.0; // ����ũ9�� X �Է¿��� 9���� ��...
    for (int i = 0; i < inH; i++) {
        for (int k = 0; k < inW; k++) {
            S = 0.0; // ���� ���� �ʱ�ȭ�ϴ� �� ����
            for (int m = 0; m < 9; m++) {
                for (int n = 0; n < 9; n++) {
                    S += tmpInput[i + m][k + n] * mask[m][n];
                }
            }
            tmpOutput[i][k] = S;
        }
    }

    for (int i = 0; i < outH; i++) {
        for (int k = 0; k < outW; k++) {
            double v = tmpOutput[i][k];
            if (v > 255.0) v = 255.0;
            if (v < 0.0) v = 0.0;
            outImage[i][k] = (unsigned char)v;
        }
    }
    freeDoubleMemory(tmpInput, inH + 8);
    freeDoubleMemory(tmpOutput, outH);
    printImage();
    //int t;
    //while (1) {
    //    printf("������ �󸶳� ã�����?(0~255)\n");
    //    t = getInValue();
    //    if ((t < 0) || (t > 255))
    //        printf("�߸��� �Է��Դϴ�. �ٽ� �õ��ϼ���.(0~255)\n");
    //    else
    //        break;
    //}
    //// Gaussian mask generation
    //double gaussMask1[3][3];
    //double gaussMask2[3][3];
    //double gaussian1, gaussian2;
    //// ���� �ٸ� ǥ�������� ���� ����þ� ����ũ ����
    //for (int i = 0; i < 3; i++) {
    //    for (int j = 0; j < 3; j++) {
    //        double x = sqrt((pow((i - 1), 2) + pow((j - 1), 2)));
    //        gaussian1 = exp(-(x * x) / (2.0 * 2.0 * 2.0)) / (2.0 * sqrt(2.0 * PI));
    //        gaussian2 = exp(-(x * x) / (2.0 * 3.2 * 3.2)) / (3.2 * sqrt(2.0 * PI));
    //        gaussMask1[i][j] = gaussian1;
    //        gaussMask2[i][j] = gaussian2;
    //    }
    //}

    //// Temporary memory allocation
    //double** tmpInImage = mallocDoubleMemory(inH + 2, inW + 2);
    //double** tmpOutImage1 = mallocDoubleMemory(outH, outW);
    //double** tmpOutImage2 = mallocDoubleMemory(outH, outW);
    //double** tmpOutImage3 = mallocDoubleMemory(outH, outW);

    //// �ӽ� �޸� �ʱ�ȭ
    //for (int i = 0; i < inH + 2; i++) {
    //    for (int j = 0; j < inW + 2; j++) {
    //        tmpInImage[i][j] = 0.0;
    //    }
    //}

    //// Padding 1
    //// �Է� �̹����� �е��� ������ �ӽ� �̹����� ����
    //for (int i = 0; i < inH; i++) {
    //    for (int j = 0; j < inW; j++) {
    //        tmpInImage[i + 1][j + 1] = inImage[i][j];
    //    }
    //}

    //// Applying Gaussian masks to the input image
    //// ����þ� ����ũ�� �Է� �̹����� ����
    //double sum1, sum2;
    //for (int i = 0; i < inH; i++) {
    //    for (int j = 0; j < inW; j++) {
    //        sum1 = 0.0;
    //        sum2 = 0.0;
    //        for (int k = 0; k < 3; k++) {
    //            for (int q = 0; q < 3; q++) {
    //                sum1 += tmpInImage[i + k][j + q] * gaussMask1[k][q];
    //                sum2 += tmpInImage[i + k][j + q] * gaussMask2[k][q];
    //            }
    //        }
    //        tmpOutImage1[i][j] = sum1;
    //        tmpOutImage2[i][j] = sum2;
    //    }
    //}

    //// Calculating difference between the two filtered images
    //// �� ���͸��� �̹����� ���� ���
    //for (int i = 0; i < outH; i++) {
    //    for (int j = 0; j < outW; j++) {
    //        tmpOutImage3[i][j] = tmpOutImage1[i][j] - tmpOutImage2[i][j];
    //    }
    //}

    //// Copying result from temporary output image to output image
    //// �ӽ� ��� �̹����� ����� ��� �̹����� ����
    //for (int i = 0; i < outH; i++) {
    //    for (int j = 0; j < outW; j++) {
    //        if (tmpOutImage3[i][j] < t)
    //            outImage[i][j] = 255;  
    //        else
    //            outImage[i][j] = 0;  
    //    }
    //}

    //// Freeing allocated memory
    //// �Ҵ�� �޸� ����
    //freeDoubleMemory(tmpInImage, inH + 2);
    //freeDoubleMemory(tmpOutImage1, outH);
    //freeDoubleMemory(tmpOutImage2, outH);
    //freeDoubleMemory(tmpOutImage3, outH);

    //printImage();  // �̹��� ���
}

