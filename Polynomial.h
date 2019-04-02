#include<iostream>
using namespace std;
#ifndef polynomial_h
#define polynomial_h



class Polynomial
{
	int* coeffs;
	int degree;
public:
	Polynomial(int degree=0,int* coeffs=NULL);				/*default constructor*/
	Polynomial(const Polynomial&);							/*default constructor*/
	~Polynomial();											/*destructor*/
	Polynomial operator+(const Polynomial&) const;
	Polynomial operator*(const Polynomial&) const;
	void operator<<(const Polynomial&) const;
	Polynomial& operator=(const Polynomial&);
};

Polynomial& Polynomial::operator=(const Polynomial& idol){
	delete[] coeffs;
	degree = idol.degree;
	coeffs = new int[idol.degree+1];
	for(int i=0;i<=degree;i++)
		coeffs[i] = idol.coeffs[i];
	return *this;
}

Polynomial::Polynomial(int degree, int* coeffs){
	this->degree = degree;
	this->coeffs = coeffs;
}

Polynomial::Polynomial(const Polynomial& idol){
	degree = idol.degree;
	delete[] coeffs;
	coeffs = new int[degree+1];
	for(int i=0;i<=degree;i++)
		coeffs[i] = idol.coeffs[i];
}

Polynomial::~Polynomial(){
	delete[] coeffs;
}

Polynomial Polynomial::operator+(const Polynomial& X) const{
	int bigDegree = X.degree > degree ? X.degree : degree;
	int* totalCoeffs;
	totalCoeffs = new int[bigDegree+1];
	int i =0;
	for(;i<=degree && i<=X.degree;i++)
		totalCoeffs[i] = coeffs[i] + X.coeffs[i];
	if(degree != X.degree){
		if(degree > X.degree){
			for(;i<=bigDegree;i++)
				totalCoeffs[i] = coeffs[i];
		}
		else{
			for (; i <=bigDegree; i++)
				totalCoeffs[i] = coeffs[i];
		}
	}
	return Polynomial(bigDegree,totalCoeffs);
}

Polynomial Polynomial::operator*(const Polynomial& X) const{
	int productDegree = degree + X.degree;
	int* productCoeffs = new int[productDegree+1];
	for(int i=0;i<=productDegree;i++)
		productCoeffs[i] = 0;
	for(int i=0;i<=degree;i++)
		for(int j=0;j<=X.degree;j++)
			productCoeffs[i+j] += X.coeffs[j] * coeffs[i];
	return Polynomial(productDegree,productCoeffs);
}

void Polynomial::operator<<(const Polynomial& X) const{
	bool sign = false;
	for(int i=X.degree;i>=0;i--){
		if(sign)
			cout<<" + ";
		if(i == 0 && X.coeffs[i] != 0){
			cout<<X.coeffs[i];
			sign = true;
		}
		else if(X.coeffs[i] != 0 && X.coeffs[i] != 1 ){
			cout<<X.coeffs[i]<<"X^"<<i;
			sign = true;
		}
		else if(X.coeffs[i] == 1){
			cout<<"X^"<<i;
			sign = true;
		}
	}
}

#endif