//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//#include <stdbool.h>
//#include <time.h>
//#include <stdlib.h>
//
//void main() {
//	char str[100]; // �о�� ����
//	FILE* rfp;
//
//	// ���� ó�� 3�ܰ�
//	// (1) ���� ����
//	rfp = fopen("c:/windows/win.ini", "rt");
//
//	// (2) ���� �аų� ����
//	int count = 1;
//	while (1) {
//		fgets(str, 100, rfp);
//
//		if (feof(rfp))
//			break;
//
//		printf("%2d�� : %s", count, str);
//		count++;
//
//	}
//
//
//	// (3) ���� �ݱ�
//	fclose(rfp);
//
//	
//
//}