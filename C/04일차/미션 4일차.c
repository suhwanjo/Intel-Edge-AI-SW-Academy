#define _CRT_SECURE_NO_WARNINGS
#include <stdbool.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>  // Include stdlib.h for srand() and rand()
#define HEIGHT 7
#define WIDTH 7

// �޸� �غ�
unsigned char image[HEIGHT][WIDTH];

// �Լ��� �����
void loadImage() {
	for (int i = 0; i < HEIGHT; i++) {
		for (int j = 0; j < WIDTH; j++) {
			image[i][j] = rand() % 256;
		}
	}
}

void printImage() {
	for (int i = 0; i < HEIGHT; i++) {
		for (int j = 0; j < WIDTH; j++) {
			printf("%3d ", image[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

void reverseImage() {
	for (int i = 0; i < HEIGHT; i++) {
		for (int j = 0; j < WIDTH; j++) {
			image[i][j] = 255 - image[i][j];
		}
	}
	printImage();
}

int addImage(int val) {
	for (int i = 0; i < HEIGHT; i++) {
		for (int j = 0; j < WIDTH; j++) {
			if (image[i][j] + val < 256)
				image[i][j] += val;
			else
				image[i][j] = 255;
		}
	}
	printImage();
}

int binaryImage(int th) {
	for (int i = 0; i < HEIGHT; i++) {
		for (int j = 0; j < WIDTH; j++) {
			if (image[i][j] > th) // �Ӱ谪 128�� ����
				image[i][j] = 255;
			else
				image[i][j] = 0;
		}
	}
	printImage();
}

void main() {
	srand((unsigned int)time(0));
	// ������ ������ ũ�� ��ŭ�� �޸� Ȯ�� (jolly.raw : 10x10 ũ�� ������, �̰��� �̹��� ����)
	// �̹��� �ε�
	loadImage();

	// ���� ���
	printImage();

	// ����
	reverseImage();

	// ���, ��Ӱ�
	int value;
	printf("��� ���� ���� : ");
	scanf("%d", &value);
	addImage(value);

	// ���
	int threshold;
	printf("��� �Ӱ谪: ");
	scanf("%d", &threshold);
	binaryImage(threshold);

	// ��ȭ
	// ������ ��� ���� ���
	int hap = 0;
	int result;
	for (int i = 0; i < HEIGHT; i++) {
		for (int j = 0; j < WIDTH; j++) {
			hap += image[i][j];
		}
	}
	result = hap / (HEIGHT * WIDTH);
	printf("%d\n", result);

	// ������ �ִ밪, �ּҰ� ��  �� ��ġ�� ���
	int max = 0;
	int min = 9999;
	int maxIndexH;
	int maxIndexW;
	int minIndexH;
	int minIndexW;

	for (int i = 0; i < HEIGHT; i++) {
		for (int j = 0; j < WIDTH; j++) {
			if (image[i][j] >= max) {
				max = image[i][j];
				maxIndexH = i;
				maxIndexW = j;
			}
			if (image[i][j] <= min) {
				min = image[i][j];
				minIndexH = i;
				minIndexW = j;
			}
		}
	}
	printf("max = %d, index=(%d,%d), min = %d, index=(%d,%d) \n", max, maxIndexH, maxIndexW, min, minIndexH, minIndexW);

	// ������ �߾Ӱ�(=������=Median)�� ��ġ�� ���
	// 1�������� ��� -> �����ϱ� -> �߰� �� ��ġ ���

	// 1�������� ���
	unsigned char arr[HEIGHT * WIDTH];
	int index = 0;
	for (int i = 0; i < HEIGHT; i++) {
		for (int j = 0; j < WIDTH; j++) {
			arr[index] = image[i][j];
			// printf("%d ", arr[index]);
			index++;
		}
	}

	// �����ϱ�
	for (int i = 0; i < HEIGHT * WIDTH-1; i++) {
		for (int j = 0; j < HEIGHT * WIDTH - i-1; j++) {
			if (arr[j] > arr[j + 1]) {
				int temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
		}
	}

	// ���� ��� ���
	for (int i = 0; i < HEIGHT * WIDTH; i++)
		printf("%d ", arr[i]);
	printf("\n");

	// �߰� ���� ��ġ ���
	int median = arr[(HEIGHT * WIDTH) / 2];
	int medianIndexH;
	int medianIndexW;
	for (int i = 0; i < HEIGHT; i++) {
		for (int j = 0; j < WIDTH; j++) {
			if (image[i][j] == median) {
				medianIndexH = i;
				medianIndexW = j;
			}
		}
	}
	printf("median = %d, index=(%d,%d)", median, medianIndexH, medianIndexW);
	// ���󿡼� �ֺ�(���� ���� ������ ��)�� ���
	// 1�������� ��� -> ���� ũ��� ������ �迭 ����(�� �� ����) -> �� ���� -> �ִ� �ȼ� ���� ��ġ ���
	unsigned char arr2[HEIGHT * WIDTH];
	int index2 = 0;
	for (int i = 0; i < HEIGHT; i++) {
		for (int j = 0; j < WIDTH; j++) {
			arr2[index2] = image[i][j];
			// printf("%d ", arr2[index]);
			index2++;
		}
	}
	// ���� ũ��� ������ �迭 ����
	unsigned char freq[HEIGHT * WIDTH] = { 1 };
	// �� ����
	for (int i = 0; i < HEIGHT * WIDTH; i++) {
		for (int j = i + 1; j < HEIGHT * WIDTH; j++) {
			if (arr2[i] == arr2[j])
				freq[i] += 1;
		}
	}
	// �ִ� �ȼ� �� ���ϱ�
	int max2 = 0;
	int maxFreq;
	for (int i = 0; i < HEIGHT * WIDTH; i++) {
		if (freq[i] >= max2) {
			max2 = freq[i];
			maxFreq = arr2[i];
		}
	}
	// ��ġ ã��
	int maxFreqIndexH = -1;
	int maxFreqIndexW = -1;
	for (int i = 0; i < HEIGHT; i++) {
		for (int j = 0; j < WIDTH; j++) {
			if (image[i][j] == maxFreq) {
				maxFreqIndexH = i;
				maxFreqIndexW = j;
				break;
			}
		}
		if (maxFreqIndexH != -1) // ó�� �߰��� �ִ� �󵵸� ���
			break;
	}
	printf("\nmax freq= %d, index=(%d,%d)", maxFreq, maxFreqIndexH, maxFreqIndexW);

}