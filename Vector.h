#include<iostream>
using namespace std;

#ifndef vector_h
#define vector_h


class Vector
{
	int size;
	int* values;
public:
	Vector(int size=0,int*values=NULL);
	Vector(const Vector&);
	~Vector();
	Vector operator+(const Vector&) const;
	int operator*(const Vector&) const;					/*dot product*/
	Vector operator*(const int) const;					/*vector product*/
	void operator<<(const Vector&) const;
	Vector& operator=(const Vector&);
};

Vector& Vector::operator=(const Vector& idol){
	delete[] values;
	size = idol.size;
	values = new int[idol.size];
	for(int i=0;i<size;i++)
		values[i] = idol.values[i];
	return *this;
}

Vector::Vector(int size,int*values){
	this->size=size;
	this->values=values;
}
Vector::Vector(const Vector& idol){
	size = idol.size;
	values = new int[size];
	for(int i=0;i<size;i++)
		values[i] = idol.values[i];
}

Vector::~Vector(){
	delete[] values;
}

Vector Vector::operator+(const Vector& X) const{
	if(size == X.size){
		int* total = new int[size];
		for(int i=0;i<size;i++)
			total[i] = values[i] + X.values[i];
		return Vector(size,total);
	}
	cerr<<"Size Error"<<endl;
}

int Vector::operator*(const Vector& X) const{
	if(X.size == size){
		int result = 0;
		for(int i=0;i<size;i++)
			result += values[i] * X.values[i];
		return result;
	}
	cerr<<"Size Error"<<endl;
}

Vector Vector::operator*(const int x) const{
	int* new_values = new int[size];
	for(int i=0;i<size;i++)
		new_values[i] = x * values[i];
	return Vector(size,new_values);
}

void Vector::operator<<(const Vector& X) const{
	for(int i=X.size-1;i>=0;i--){
		if(i == X.size-1)
			cout<<"(";
		cout<<X.values[i];
		if(i==0)
			cout<<")";
		else
			cout<<", ";
	}
}


#endif
