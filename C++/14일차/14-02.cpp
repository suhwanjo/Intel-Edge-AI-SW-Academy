#include <iostream>
#include <cstring>
#include <string>
using namespace std;  // std�� �ִ� �ֵ� �� 'std::' �Ⱦ��� ��� ����

class Circle {
	/// Ŭ������ �Ӽ�
private:
	int radius;
	// ����/����
public:
	void setRadius(int value) { radius = value; };
	int getRadius() { return radius; };
	/// Ŭ������ ���
public:
	Circle();  // �Լ� �����ε�
	Circle(int);  // ������
	double getArea();
};
Circle::Circle() {}
Circle::Circle(int r) {
	cout << "�� �ν��Ͻ� ����" << endl;
	r = 1;
}
double Circle::getArea() {
	return radius * radius * 3.14;


}
int main() {
	Circle donut(1);
	Circle donut1;
	donut.setRadius(2);

	cout << "������ ������" << donut.getArea() << "�Դϴ�.";

}
// ����
class Rectangle {

public:
	int width, height;
public:
	Rectangle();
	Rectangle(int);
	Rectangle(int, int);
	bool isSquare();
};

Rectangle::Rectangle(){}
Rectangle::Rectangle(int wh) {
	width = wh;
	height = wh;
}
Rectangle::Rectangle(int w, int h) {
	width = w;
	height = h;
}

bool Rectangle::isSquare() {
	if (width == height)
		return true;
	return false;
}

int main() {
	Rectangle rect1;
	Rectangle rect2(3,5);
	Rectangle rect3(3);

	if (rect1.isSquare())
		cout << "rect1�� ���簢���̴�." << endl;
	if (rect2.isSquare())
		cout << "rect2�� ���簢���̴�." << endl;
	if (rect3.isSquare())
		cout << "rect3�� ���簢���̴�." << endl;
}