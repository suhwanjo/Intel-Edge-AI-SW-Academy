#include <stdio.h>

void main() {
	// ���� ��� ��Ģ : ���� �̸��� ���� � �뵵���� ���� �ǵ���
	// integer type input first number
	// integer_type_input_first_number
	// integerTypeInputFirstNumer
	// intFirstNumber
	// intNumber1
	// iNum1
	int iNum1, iNum2, fResult6;
	float fResult1, fResult2, fResult3, fResult4, fResult5;

	iNum1 = 100;
	iNum2 = 200;

	fResult1 = iNum1 + iNum2;
	fResult2 = iNum1 - iNum2;
	fResult3 = iNum1 * iNum2;
	fResult4 = ((float)iNum1 / (float)iNum2);
	fResult5 = iNum1 % iNum2;
	fResult6 = iNum1 / iNum2; // ������ �� ����ȭ == ��
	
	printf("%d + %d = %f \n", iNum1, iNum2, fResult1);
	printf("%d - %d = %f \n", iNum1, iNum2, fResult2);
	printf("%d * %d = %f \n", iNum1, iNum2, fResult3);
	printf("%d / %d = %f \n", iNum1, iNum2, fResult4);
	printf("%d %% %d = %f \n", iNum1, iNum2, fResult5);
	printf("%d // %d = %d \n", iNum1, iNum2, fResult6);

}