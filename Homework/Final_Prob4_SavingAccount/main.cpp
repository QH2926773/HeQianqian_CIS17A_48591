/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: nancyhe
 *
 * Created on December 8, 2021, 6:59 PM
 */

#include <iostream>
#include <iomanip>
#include <ctime>
#include <cstdlib>
using namespace std;

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
int main(){
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
return 0;
}

