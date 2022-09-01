/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: nancyhe
 *
 * Created on December 17, 2021, 12:48 PM
 */

#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
using namespace std;
#include "Prob2Sort.h"

class SavingsAccount {
public:
SavingsAccount(float); //Constructor
void Transaction(float); //Procedure
float Total(float = 0, int = 0); //Savings Procedure
float TotalRecursive(float = 0, int = 0);
void toString(); //Output Properties
private:
float Withdraw(float); //Utility Procedure
float Deposit(float); //Utility Procedure
float Balance; //Property
int FreqWithDraw; //Property
int FreqDeposit; //Property
};
SavingsAccount::SavingsAccount(float f){
if (f < 0) {
this->Balance = 0;
}
else {
this->Balance = f;
}
this->FreqDeposit = 0;
this->FreqWithDraw = 0;
}
void SavingsAccount::Transaction(float f){
if (f > 0)
Deposit(f);
else
Withdraw(f);
}
float SavingsAccount::Total(float f, int time)
{
double tot = Balance;
for (int i = 0; i < time; i++) {
tot += (tot * f);
}
return tot;
}
float SavingsAccount::TotalRecursive(float rate, int years)
{
Balance = Balance + (Balance * rate);
if (years > 1) {
Balance = TotalRecursive(rate, years - 1);
}
return Balance;
}
void SavingsAccount::toString()
{
cout << "Balance=" << Balance << endl;
cout << "WithDraws=" << FreqWithDraw << endl;
cout << "Deposit=" << FreqDeposit << endl;
}
float SavingsAccount::Withdraw(float f)
{

if (f != 0) {
if ((Balance + f) >= 0) {
Balance += f;
FreqWithDraw++;
}
}
else {
cout << "WithDraw not Allowed" << endl;
}
}
float SavingsAccount::Deposit(float f)
{
Balance += f;
FreqDeposit++;
}

class Employee{
    public:
        Employee(char[],char[],float); //Constructor
        float CalculatePay(float,int); //Procedure
        float getGrossPay(float,int); //Procedure
        float getNetPay(float);        //Procedure
        void   toString();              //Procedure
        int    setHoursWorked(int);     //Procedure
        float setHourlyRate(float);    //Procedure

    private:
        double Tax(float);      //Utility Procedure
        char   MyName[20];      //Property
        char   JobTitle[20];    //Property
        float HourlyRate;      //Property
        int    HoursWorked;     //Property
        float GrossPay;        //Property
        float NetPay;          //Property
};
Employee::Employee(char str1[], char str2[], float val){
    strcpy(MyName, str1);
    strcpy(JobTitle, str2);
    if(val < 0 || val > 200){
        cout << "\n Unacceptable Hourly Rate \n";
        HourlyRate = 0;
    }else{
        HourlyRate = val;
    }HoursWorked = 0;
     GrossPay = 0;
     NetPay = 0;
}
float Employee::setHourlyRate(float val){
    if(val < 0 || val > 200){
        cout << "\n Unacceptable Hourly Rate \n";
        HourlyRate = 0;
    }else{
        HourlyRate = val;
    }return HourlyRate;
}

int Employee::setHoursWorked(int val){
 
    if(val < 0 || val > 84){
        cout << "\n Unacceptable Hours Worked \n";
        HoursWorked = 0;
    }else{
        HoursWorked = val;
    }return HoursWorked;
}
float Employee::getGrossPay(float hRate, int hWorked){

    if(hWorked <= 40){
        GrossPay = hRate * hWorked;
    }else if(hWorked > 40 && hWorked <= 50){
        GrossPay = ( (40 * hRate) + ((hWorked - 40) * hRate * 1.5));
    }else{
        GrossPay = ( (40 * hRate) + (10 * hRate * 1.5)
                +((hWorked - 50) * hRate * 2));
    }return GrossPay;
}

float Employee::getNetPay(float gross){
    float tax = 0;
    if(gross <= 500){
        tax = gross * (0.1);
    }else if(gross > 500 && gross <= 1000){
        tax =  500 * (0.1) + ((gross - 500) * (0.2));
    }else{
        tax = 500 * (0.1) + 500 * (0.2) + ((gross-1000) * (0.3));
    }NetPay = (gross - tax);

    return NetPay;
}

float Employee::CalculatePay(float x, int y){
    return getNetPay(getGrossPay(setHourlyRate(x) ,setHoursWorked(y)));
}

void Employee::toString(){
cout << "\n Name = " << MyName << " Job Title = " 
        << JobTitle << "\n Hourly Rate = " << HourlyRate 
        << " Hours Worked = " << HoursWorked << " Gross Pay = " << GrossPay 
        << " Net Pay = " << NetPay << " \n";
}
template<class T>
class Prob3Table{
protected:
int rows; //Number of rows in the table
int cols; //Number of cols in the table
T *rowSum; //RowSum array
T *colSum; //ColSum array
T *table; //Table array
T grandTotal; //Grand total
void calcTable(void); //Calculate all the sums
public:
Prob3Table(char *,int,int); //Constructor then Destructor
~Prob3Table(){delete [] table;delete [] rowSum;delete [] colSum;};
const T *getTable(void){return table;};
const T *getRowSum(void){return rowSum;};
const T *getColSum(void){return colSum;};
T getGrandTotal(void){return grandTotal;};
};

template<typename T>
Prob3Table<T>::Prob3Table(char *filename,int r,int c){
ifstream in(filename);
if(in.fail()){
cout << "ERROR: could not read input file " << filename << endl;
exit(1);
}
table = new T[r * c];
rows = r;
cols = c;
for(int i = 0; i < r; i++)
for(int j = 0; j < c; j++)
in >> table[i * c + j];

in.close();
rowSum = new T[r];
colSum = new T[c];
calcTable();
}

template<typename T>
void Prob3Table<T>::calcTable(void){
grandTotal = 0;
for(int r = 0; r < rows; r++){
rowSum[r] = 0;
for(int c = 0; c < cols; c++){
rowSum[r] += table[r * cols + c];
}

grandTotal += rowSum[r];
}

for(int c = 0; c < cols; c++){
colSum[c] = 0;
for(int r = 0; r < rows; r++){
colSum[c] += table[r * cols + c];
}
}

}

template<class T>
class Prob3TableInherited:public Prob3Table<T>{
protected:
T *augTable;
public:
Prob3TableInherited(char *filename,int rows,int cols):Prob3Table<T>(filename, rows, cols){

augTable = new T[(rows+1) * (cols+1)];
for(int i = 0; i < rows; i++)
for(int j = 0; j < cols; j++)
augTable[i * (cols + 1) + j] = Prob3Table<T>::table[i * cols + j];

int r, c;
c = cols;
for( r = 0; r < rows; r++)
augTable[r * (cols + 1) + c] = Prob3Table<T>::rowSum[r];

r = rows;
for( c = 0; c < cols; c++)
augTable[r * (cols + 1) + c] = Prob3Table<T>::colSum[c];

augTable[(rows +1)* (cols+1) - 1] = Prob3Table<T>::getGrandTotal();
}
~Prob3TableInherited(){delete [] augTable;}; 
const T *getAugTable(void){return augTable;};
};

class Prob1Random

{

private:

char *set; //The set of numbers to draw random numbers from

char nset; //The number of variables in the sequence

int *freq; //Frequency of all the random numbers returned

int numRand; //The total number of times the random number function is called

public:

Prob1Random(const char,const char *); //Constructor

~Prob1Random(void); //Destructor

char randFromSet(void); //Returns a random number from the set

int *getFreq(void) const; //Returns the frequency histogram

char *getSet(void) const; //Returns the set used

int getNumRand(void) const; //Gets the number of times randFromSet has

};

//constructor

Prob1Random::Prob1Random(const char n, const char* _set){
    srand(time(NULL));
    nset=n;
    set=new char[n];
    for(int i=0;i<n;i++){
        set[i]=_set[i];
    }
    freq=new int[n];
    for(int i=0;i<n;i++){
        freq[i]=0;
    }
    numRand=0;
}

char Prob1Random::randFromSet(){
    int randomIndex=rand()%nset;
    freq[randomIndex]++;
    numRand++;
    return set[randomIndex];
}

int *Prob1Random::getFreq() const{
    return freq;
}
char* Prob1Random::getSet() const{
    return set;

}
int Prob1Random::getNumRand() const{
    return numRand;

}
Prob1Random::~Prob1Random(){
    delete set;
    delete freq;
}

//User Libraries

//Global Constants - Math/Physics Constants, Conversions,
//                   2-D Array Dimensions

//Function Prototypes
void menu();
void prblm1();
void prblm2();
void prblm3();
void prblm4();
void prblm5();
void prblm6();

//Execution Begins Here
int main(int argc, char** argv) {
    //Declare Variables
    char choice;
    do{
        menu();
        cin>>choice;

        //Process/Map inputs to outputs
        switch(choice){
            case '1':{prblm1();break;}
            case '2':{prblm2();break;}
            case '3':{prblm3();break;}
            case '4':{prblm4();break;}
            case '5':{prblm5();break;}
            case '6':{prblm6();break;}
            default: cout<<"Exiting Menu"<<endl;
        }
    }while(choice>='1'&&choice<='6');
    
    //Exit stage right!
    return 0;
}

//000000011111111112222222222333333333344444444445555555555666666666677777777778
//345678901234567890123456789012345678901234567890123456789012345678901234567890
//                         Menu
//Input:  -> Parameters in Argument List, Description/Range/Units
//Output: -> Return, Description/Range/Units
//000000011111111112222222222333333333344444444445555555555666666666677777777778
//345678901234567890123456789012345678901234567890123456789012345678901234567890
void menu(){
    //Display menu
    cout<<endl<<"Choose from the following Menu"<<endl;
    cout<<"Type 1 for Problem 1"<<endl;
    cout<<"Type 2 for Problem 2"<<endl;
    cout<<"Type 3 for Problem 3"<<endl;   
    cout<<"Type 4 for Problem 4"<<endl;
    cout<<"Type 5 for Problem 5"<<endl;   
    cout<<"Type 6 for Problem 6"<<endl<<endl;
}

//000000011111111112222222222333333333344444444445555555555666666666677777777778
//345678901234567890123456789012345678901234567890123456789012345678901234567890
//                         Problem 1
//Input:  -> Parameters in Argument List, Description/Range/Units
//Output: -> Return, Description/Range/Units
//000000011111111112222222222333333333344444444445555555555666666666677777777778
//345678901234567890123456789012345678901234567890123456789012345678901234567890
void prblm1(){
    cout<<"Problem 1"<<endl;
    char n=5;
    char rndseq[]={29,34,57,89,126};             
    int ntimes=100000;
    Prob1Random a(n,rndseq);
    for(int i=1;i<=ntimes;i++){
        a.randFromSet();
    }
    int *x=a.getFreq();         
    char *y=a.getSet();
    for(int i=0;i<n;i++){
        cout<<int(y[i])<<" occured "<<x[i]<<" times"<<endl;
    }
    cout<<"The total number of random numbers is "<<a.getNumRand()<<endl;

}

//000000011111111112222222222333333333344444444445555555555666666666677777777778
//345678901234567890123456789012345678901234567890123456789012345678901234567890
//                         Problem 2
//Input:  -> Parameters in Argument List, Description/Range/Units
//Output: -> Return, Description/Range/Units
//000000011111111112222222222333333333344444444445555555555666666666677777777778
//345678901234567890123456789012345678901234567890123456789012345678901234567890
void prblm2(){
    cout<<"Problem 2"<<endl;
    cout<<"The start of Problem 2, the sorting problem"<<endl;
	Prob2Sort<char> rc;
	bool ascending=true;
	ifstream infile;
	infile.open("Problem2.txt",ios::in);
        if(infile.fail()){
            cout<<"The file failed to open!\n";
        }
        else{
	char *ch2=new char[10*16];
	char *ch2p=ch2;
	while(infile.get(*ch2)){cout<<*ch2;ch2++;}
	infile.close();
	cout<<endl;
	cout<<"Sorting on which column"<<endl;
	int column;
	cin>>column;
	char *zc=rc.sortArray(ch2p,10,16,column,ascending);
	for(int i=0;i<10;i++)
	{
		for(int j=0;j<16;j++)
		{
			cout<<zc[i*16+j];
		}
	}
	cout<<endl;}
}


//000000011111111112222222222333333333344444444445555555555666666666677777777778
//345678901234567890123456789012345678901234567890123456789012345678901234567890
//                         Problem 3
//Input:  -> Parameters in Argument List, Description/Range/Units
//Output: -> Return, Description/Range/Units
//000000011111111112222222222333333333344444444445555555555666666666677777777778
//345678901234567890123456789012345678901234567890123456789012345678901234567890
void prblm3(){
    cout<<"Problem 3"<<endl;
    cout<<"Entering problem number 3"<<endl;
int rows=5;
int cols=6;
Prob3TableInherited<int> tab("Problem3.txt",rows,cols);
const int *naugT=tab.getTable();
for(int i=0;i<rows;i++)
{
for(int j=0;j<cols;j++)
{
cout<<naugT[i*cols+j]<<" ";
}
cout<<endl;
}
cout<<endl;
const int *augT=tab.getAugTable();
for(int i=0;i<=rows;i++)
{
for(int j=0;j<=cols;j++)
{
cout<<augT[i*(cols+1)+j]<<" ";
}
cout<<endl;
}

}

//000000011111111112222222222333333333344444444445555555555666666666677777777778
//345678901234567890123456789012345678901234567890123456789012345678901234567890
//                         Problem 4
//Input:  -> Parameters in Argument List, Description/Range/Units
//Output: -> Return, Description/Range/Units
//000000011111111112222222222333333333344444444445555555555666666666677777777778
//345678901234567890123456789012345678901234567890123456789012345678901234567890
void prblm4(){
    cout<<"problem 4"<<endl;
    SavingsAccount mine(-300);

for (int i = 1; i <= 10; i++) {
mine.Transaction((float)(rand() % 500) * (rand() % 3 - 1));
}
mine.toString();
cout << "Balance after 7 years given 10% interest = "
<< mine.Total((float)(0.10), 7) << endl;
cout << "Balance after 7 years given 10% interest = "
<< mine.TotalRecursive((float)(0.10), 7)
<< " Recursive Calculation " << endl;
}
void prblm5(){
    cout<<"problem 5"<<endl;
    Employee Mark("Mark","Boss",215.50);

    Mark.setHoursWorked(-3);

    Mark.toString();

    Mark.CalculatePay(Mark.setHourlyRate(20.0), Mark.setHoursWorked(25));

    Mark.toString();

    Mark.CalculatePay(Mark.setHourlyRate(40.0),

    Mark.setHoursWorked(25));

    Mark.toString();

    Mark.CalculatePay(Mark.setHourlyRate(60.0),

    Mark.setHoursWorked(25));

    Mark.toString();


    Employee Mary("Mary","VP",50.0);

    Mary.toString();

    Mary.CalculatePay(Mary.setHourlyRate(50.0),

    Mary.setHoursWorked(40));

    Mary.toString();

    Mary.CalculatePay(Mary.setHourlyRate(50.0),

    Mary.setHoursWorked(50));

    Mary.toString();

    Mary.CalculatePay(Mary.setHourlyRate(50.0),

    Mary.setHoursWorked(60));

    Mary.toString();

}
void prblm6(){
    cout<<"problem 6"<<endl;
}

