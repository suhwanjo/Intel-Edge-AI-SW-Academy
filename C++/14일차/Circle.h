#pragma once
#ifndef CIRCLE_H  // ������� �ѹ� �� �����ص� ��������
#define CIRCLE_H
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

#endif // ������� �ѹ� �� �����ص� ��������