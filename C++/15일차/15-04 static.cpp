#include <iostream>
#include <cstring>
#include <string>
using namespace std;

class Circle {
public:
	static int numOfCircles;
	int radius;
public:
	Circle(int radius = 1) {
		this->radius = radius;
		numOfCircles++;
	}	
	~Circle(){
		numOfCircles--;
	}
	static int getNumOfCircle() {
		return numOfCircles;
	}
};

int Circle::numOfCircles = 0;

int main() {
	
	Circle* p = new Circle[10];
	cout << "���� �� ��ü��: " << Circle::getNumOfCircle() << endl;
	delete[] p;
	cout << "���� �� ��ü��: " << Circle::getNumOfCircle() << endl;
	if (true) {
		Circle a, b;
		cout << "���� �� ��ü��: " << Circle::getNumOfCircle() << endl;
	}
	cout << "���� �� ��ü��: " << Circle::getNumOfCircle() << endl;

}