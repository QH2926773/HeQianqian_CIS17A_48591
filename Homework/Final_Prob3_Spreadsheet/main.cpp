/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: Qianqian He
 *
 * Created on December 8, 2021, 7:07 PM
 */

#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
using namespace std;

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

int main(){
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


