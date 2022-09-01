/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: nancyhe
 *
 * Created on December 9, 2021, 10:43 AM
 */

#include<iostream>

#include<stdlib.h>

#include<time.h>

using namespace std;

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
int main(){

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

    return 0;

}

