#include <iostream>
#include <cstring>
#include <string>

bool average(int a[], int size, double& avg) {  // ���� ���� return �ϰ� ���� �� : &
	if (size <= 0)
		return false;
	double sum = 0;
	for (int i = 0; i < size; i++)
		sum += a[i];
	avg = sum / size;
	return true;
}	
using namespace std;

int main() {
	int x[] = { 1,2,3,4 };
	double avg;
	if (average(x, 4, avg))
		cout << avg;
	else
		cout << "1�� �̻�";
}