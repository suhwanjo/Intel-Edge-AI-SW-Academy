#include <iostream>
#include <cstring>
#include <string>
using namespace std;  // std�� �ִ� �ֵ� �� std �Ⱦ��� ��� ����
int main() {
	std::cout << "Hello \n" << "HI" << std::endl << 3.14;  // << : ������ �����ε�, ȣ�� X -> ����

	cout << "�ʺ� : ";
	int width;
	cin >> width;
	cout << "�Է��� �ʺ��" << width << "�Դϴ�.";

	char passwd[11];
	cout << "��ȣ : ";

	// cin >> passwd;
	cin.getline(passwd, 11, '\n');

	cout << "�Է��� ��ȣ" << passwd << "�Դϴ�.";

	string song("fedsdfsf");
	string elvis("���� ��������");
	cout << "�뷡 �ҷ�!" << song << endl << "���� �θ�??" << elvis;
	return 0;
}