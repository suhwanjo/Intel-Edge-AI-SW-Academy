#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

void main() {
	int iNum1, iNum2;
	float fResult, fResult2, fResult3, fResult4;

	printf("ù ��° ���ڸ� �Է��ϼ���: ");
	scanf("%d", &iNum1);
	printf("�� ��° ���ڸ� �Է��ϼ���: ");
	scanf("%d", &iNum2);


	fResult = iNum1 + iNum2;
	fResult2 = iNum1 - iNum2;
	fResult3 = iNum1 * iNum2;
	fResult4 = ((float)iNum1 / (float)iNum2);

	printf("%d + %d = %f \n", iNum1, iNum2, fResult);
	printf("%d - %d = %f \n", iNum1, iNum2, fResult2);
	printf("%d * %d = %f \n", iNum1, iNum2, fResult3);
	if (iNum2 == 0)
		printf("0���� ���� �� �����ϴ�");
	else
		printf("%d / %d = %f \n", iNum1, iNum2, fResult4);


}