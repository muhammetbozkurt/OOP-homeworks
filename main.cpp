#include <istream>
#include <stdio.h>
#include "Vector.h"
#include "Polynomial.h"

using namespace std;

void mainUI(int&);
void slave(int masters_wish,Vector** vec_arr,Polynomial** pol_arr,int vec_size,int pol_size);

int main(){
	/*i am sorry that this part of code is messy
	*/
	FILE* pol_file;
	FILE* vec_file;
	Polynomial** pol_holder;
	Vector** vec_holder;
	int pol_size,vec_size,temp_limit; 
	/*
	pol_size and vec_size hold size of arrays 
	temp_limit holds limit of int arrays
	pol_holder is our polynom data array
	vec_holder is our vector data array
	both of them hold address of objects to prevent unwanted construct operation
	*/
	int* temp_memory=NULL;
	char buffer[100];

	pol_file = fopen("Polynomial.txt","r");
	vec_file = fopen("Vector.txt","r");
	if(!vec_file || !pol_file)
		cerr<<"There is a problem about files";

	//reading polynomials
	fscanf(pol_file,"%d",&pol_size);
	pol_holder = new Polynomial*[pol_size];
	for(int i =0;i<pol_size;i++){
		fscanf(pol_file,"%d",&temp_limit);
		temp_memory = new int[temp_limit+1];
		for(int j=temp_limit;j>=0;j--)
			fscanf(pol_file,"%d",&temp_memory[j]);
		pol_holder[i] = new Polynomial(temp_limit,temp_memory);
	}
	//reading vector
	fscanf(vec_file,"%d",&vec_size);
	vec_holder = new Vector*[vec_size];
	for(int i =0;i<vec_size;i++){
		fscanf(vec_file,"%d",&temp_limit);
		temp_memory = new int[temp_limit];
		for(int j=temp_limit-1;j>=0;j--)
			fscanf(vec_file,"%d",&temp_memory[j]);
		vec_holder[i] = new Vector(temp_limit,temp_memory);
	}

	int masters_wish = 4;
	for(;masters_wish != 0;){

		mainUI(masters_wish);
		slave(masters_wish,vec_holder,pol_holder,vec_size,pol_size);

	}

	return 0;
}

void mainUI(int & destiny){
	if(destiny == 4){
		cout<<"Polynomial and Vector List Program!\nPolynomials and Vectors are read from text files!\n\n";
		cout<<"Possible Actions:\n1. Print Polynomial and Vector lists\n2. Do a polynomial operation\n";
		cout<<"3. Do a vector operation\n4. Help: Print possible actions\n0. Exit the program\n\n\n";}
	cout << "Enter an option: " ;
	cin>>destiny;
}

void slave(int masters_wish,Vector** vec_arr,Polynomial** pol_arr,int vec_size,int pol_size){
	if(masters_wish == 1){
		cout<<"Vectors:"<<endl;
		for (int i = 0; i < vec_size; i++){
			cout<<i+1<<". ";
			*(vec_arr[i])<<*(vec_arr[i]);
			cout<<endl;
		}
		cout<<endl<<"Polynomial:"<<endl;
		for (int i = 0; i < pol_size; i++){
			cout<<i+1<<". ";
			*(pol_arr[i])<<*(pol_arr[i]);
			cout<<endl;
		}
		cout<<endl;
	}
	else if(masters_wish == 2){
		int operand1,operand2;
		char operation;
		cout<<"Which polynomial operation would you like to do?(+:addition, *:multiplication):"<<endl;
		cin>>operand1;
		operation=getchar();
		cin>>operand2;
		operand1--;
		operand2--;
		if(operation == '+'){
			cout<<"\n(";
			*(pol_arr[operand1])<<*(pol_arr[operand1]);
			cout<<") + (";
			*(pol_arr[operand2])<<*(pol_arr[operand2]);
			cout<<")";
			cout<<" = ";
			*(pol_arr[operand1])<<*(pol_arr[operand1])+*(pol_arr[operand2]);
			cout<<endl<<endl;
		}
		else if(operation == '*'){
			cout<<"(";
			*(pol_arr[operand1])<<*(pol_arr[operand1]);
			cout<<") * (";
			*(pol_arr[operand2])<<*(pol_arr[operand2]);
			cout<<")";
			cout<<" = ";
			*(pol_arr[operand1])<<*(pol_arr[operand1])**(pol_arr[operand2]);
			cout<<endl<<endl;
		}
	}
	else if(masters_wish == 3){
		int operand1,operand2;
		char operation;
		cout<<"Which vector operation would you like to do?(+:addition, *:scalar multiplication, .:dot product):"<<endl;
		cin>>operand1;
		operation=getchar();
		cin>>operand2;
		operand1--;
		if(operation == '+'){
			operand2--;
			*(vec_arr[operand1])<<*(vec_arr[operand1]);
			cout<<" + ";
			*(vec_arr[operand2])<<*(vec_arr[operand2]);
			cout<<" = ";
			*(vec_arr[operand1])<<*(vec_arr[operand1])+*(vec_arr[operand2]);
			cout<<endl<<endl;
		}
		else if(operation == '*'){
			*(vec_arr[operand1])<<*(vec_arr[operand1]);
			cout<<" * "<<operand2;
			cout<<" = ";
			*(vec_arr[operand1])<<*(vec_arr[operand1])*operand2;
			cout<<endl<<endl;
		}
		else if(operation=='.'){
			operand2--;
			*(vec_arr[operand1])<<*(vec_arr[operand1]);
			cout<<" . ";
			*(vec_arr[operand2])<<*(vec_arr[operand2]);
			cout<<" = ";
			cout<<*(vec_arr[operand1])**(vec_arr[operand2]);
			cout<<endl<<endl;
		}
	}
}
