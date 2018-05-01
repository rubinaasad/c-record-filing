// getline.cpp : Defines the entry point for the console application.

#include "stdafx.h"
#include<fstream>
#include<cstring>
#include<iostream>
#include<iomanip>
#include<stdio.h>
#include<conio.h>
#include<string>
#include<sstream>
using namespace std;

#pragma warning (disable: 4996)
const int Max=100;
int cur_size=0;
struct Student
{
	string nRollNo;
	string name;
	string dMarks;
	string cGrade;
	Student()
	{
		nRollNo="0";
		name="";
		dMarks="0";
		cGrade="";
	}
};
Student input()
{
	Student st;
	cout<<"Roll NO: " ;
	cin>>st.nRollNo;
	cout<<"Name: ";
	cin>>st.name;
	cout<<"Marks: ";
	cin>>st.dMarks;
	cout<<"Grade: ";
	cin>>st.cGrade;
	return st;
}
void output(Student st)
{
	cout<<"\n" <<endl;
	cout<<"Roll NO: " <<st.nRollNo <<endl;
	cout<<"Name: " <<st.name <<endl;
	cout<<"Marks: " <<st.dMarks <<endl;
	cout<<"Grade: " <<st.cGrade <<endl;
}

char sFileName[32]="D:\\students.txt";				//create an empty file first//
void write_data(Student st[],int Max) //writing data to the file after adding,modifying and deleting record from file//
{
	
	fstream f;
	f.open(sFileName,ios::out);
	if(!f.is_open())
	{
		cout<<"unable to open file..." <<endl;
	}

	if(Max>cur_size)
	
	{
		
		for(int i=0;i<cur_size;i++)
		
		{
		f<<st[i].nRollNo <<" "<<st[i].name <<" "<<st[i].dMarks <<" "<<st[i].cGrade <<endl;
		}

	}
	
	f.close();
	
}
void read_data(Student st[],int Max) //reading data from the file through getline//
{
	
	const int size=64;
	int i=0;
	char strRead[64];
	fstream f;
	f.open(sFileName,ios::in);
	if(f.is_open()==false)
	{
		cout<<"Unable to open file..." <<endl;
	}
		while(getline(f,st[i].nRollNo,' ') && getline(f,st[i].name,' ')&&getline(f,st[i].dMarks,' ')&& getline(f,st[i].cGrade,'\n'))
		{
			i++;
			cur_size++;
		}
	
	f.close();
	
}
void add_student(Student st[],int Max)
{
	if(Max>cur_size)
	{
		st[cur_size]=input();
		cur_size++;
		cout<<"Record added..." <<endl;
	}
	write_data(st,Max);
	system("pause");
}


void display_all(Student st[])
{
	for(int i=0;i<cur_size;i++)
	{
		output(st[i]);
	}
	
	system("pause");
}
void search_student(Student st[],string n)
{
	bool found=false;
	for(int i=0;i<cur_size;i++)
	{
		if(n==st[i].nRollNo)
		{
			output(st[i]);
		found=true;
		break;
		}
	}
	if(found==false)
	cout<<"record not found..." <<endl;
	system("pause");
	
}


void modify_student(Student st[],string n)
{
	bool found=false;
	for(int i=0;i<cur_size;i++)
	{
		if(n==st[i].nRollNo)
		{
			output(st[i]);
			cout<<"update the record..." <<endl;
			st[i]=input();
			found=true;
			break;
		
		}
	}
	write_data(st,Max);
	if(found==false)
	cout<<"Record not found..." <<endl;
	system("pause");
}

void delete_student(Student st[],int Max,int &cur_size,string n)
{	
	bool flag=false;
	for (int i=0;i<cur_size;i++) 
	{
		if(n==st[i].nRollNo)
		{
			st[i]=st[i+1];
			cur_size--;
			cout<<"Record deleted...";
			flag=true;
			break;
		}
		
	}
	write_data(st,Max);
	if(flag==false)
		cout<<"Record not found..."<<endl;
	system("pause");
}

char menu()
{
	cout<<"\t@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@";
	cout<<"\n\n\t1.CREATE STUDENT RECORD";
	cout<<"\n\n\t2.DISPLAY ALL STUDENTS RECORDS";
	cout<<"\n\n\t3.SEARCH STUDENT RECORD ";
	cout<<"\n\n\t4.MODIFY STUDENT RECORD";
	cout<<"\n\n\t5.DELETE STUDENT RECORD";
	cout<<"\n\n\t6. EXIT";
	cout<<"\n\n\t@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@";
	cout<<"\n\n\tPlease Enter Your Choice (1-6): ";
	char choice;
	cin>>choice;
	return choice;
	system("pause");
}

int _tmain(int argc, _TCHAR* argv[])
{
	Student list[Max];
	read_data(list,Max);
	string num;
	char choice;
	cout.setf(ios::fixed|ios::showpoint);
	cout<<setprecision(2); 
	do
	{
		system("cls");
		choice=menu();
		system("cls");
		switch(choice)
		{
		case '1':	add_student(list,Max);
			break;
		case '2':	display_all(list);
			break;
		case '3':	cout<<"\n\n\tPlease Enter Student's ID number: "; cin>>num;
			search_student(list,num);
			break;
		case '4':	cout<<"\n\n\tPlease Enter Student's ID number: "; cin>>num;
			modify_student(list,num);
			break;
		case '5':	cout<<"\n\n\tPlease Enter Student's ID number: "; cin>>num;
			delete_student(list,Max,cur_size,num);
			break;
		case '6':	exit(0);;
		default:	cout<<"\a";
		}
	}while(choice!='6');
	return 0;
}



