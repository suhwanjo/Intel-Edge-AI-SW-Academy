#include <iostream>
#include <cstring>
#include <string>
using namespace std;  // std�� �ִ� �ֵ� �� 'std::' �Ⱦ��� ��� ����
#include "Circle.h"
#include "Add.h"

int main() {
	Circle donut(1);
	Circle donut1;
	donut.setRadius(2);

	cout << "������ ������" << donut.getArea() << "�Դϴ�.";

	Circle donut;
	donut.setRadius(30);
	cout << donut.getArea() << endl;

	// ��ü ������
	Circle* p;
	p = &donut;
	p->setRadius(50);
	cout << p->getArea() << endl;

	Circle circleArray[3];

	circleArray[0].setRadius(10);
	circleArray[1].setRadius(20);
	circleArray[2].setRadius(30);

	for (int i = 0; i < 3; i++)
		cout << circleArray[i].getArea() << endl;

	Circle* p;
	p = circleArray;
	for (int i = 0; i < 3; i++) {
		cout << p->getArea() << endl;
		p++;
	}

	//����
	Calulator calc;
	calc.run();
}