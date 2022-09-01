/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: Qianqian He
 *
 * Created on December 8, 2021, 6:32 PM
 */
#include <iostream>
#include <string>

using namespace std;

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
int main(){
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

    return 0;
}


