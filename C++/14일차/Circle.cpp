#include <iostream>
#include <cstring>
#include <string>
using namespace std;  // std�� �ִ� �ֵ� �� 'std::' �Ⱦ��� ��� ����
#include "Circle.h"
Circle::Circle() {}
Circle::Circle(int r) {
	cout << "�� �ν��Ͻ� ����" << endl;
	r = 1;
}
double Circle::getArea() {
	return radius * radius * 3.14;
}