#include <iostream>
#include <cstring>
#include <string>
using namespace std;  // std�� �ִ� �ֵ� �� 'std::' �Ⱦ��� ��� ����

int main() {
	// 1���� �迭 �Ҵ�
	cout << "�� ��?";
	int n; // ����
	cin >> n;

	int* p = new int[n]; // ���� �迭

	delete[] p;

	// 2���� �迭 �Ҵ�
	int h, w;
	cout << "��?";
	cin >> h;
	cout << "��?";
	cin >> w;

	int** p = new int*[h];
	for (int i = 0; i < h; i++)
		p[i] = new int[w];

	for (int i = 0; i < h; i++)
		delete p[i];
	delete[] p;
}