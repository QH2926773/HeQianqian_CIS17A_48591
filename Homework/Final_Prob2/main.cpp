/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: nancyhe
 *
 * Created on December 9, 2021, 10:50 AM
 */
#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <string>
#include <cstdlib> //Random Functions
#include <ctime>    //Setting the seed with time
using namespace std;
#include "Prob2Sort.h"

int main(int argc, char** argv) {
    cout<<"The start of Problem 2, the sorting problem"<<endl;
   Prob2Sort<char> rc;
   bool ascending=true;
   ifstream infile;
   infile.open("Problem2.txt",ios::in);
   char *ch2=new char[10*16];
   char *ch2p=ch2;
   while(infile.get(*ch2)){cout<<*ch2;ch2++;}
   infile.close();
   cout<<endl;
   cout<<"Sorting on which column"<<endl;
   int column;
   cin>>column;
   char *zc= reinterpret_cast<char *>(rc.sortArray(ch2p, 10, 16, column, ascending));
   for(int i=0;i<10;i++)
   {
       for(int j=0;j<16;j++)
       {
           cout<<zc[i*16+j];
       }
   }
   delete []zc;
   cout<<endl;
    return 0;
}