/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: nancyhe
 *
 * Created on December 10, 2021, 12:10 PM
 */

/**
 * this is the driver file
 * of the gobang game
 *
 * as the main game logic is in
 * gobang file
 *
 * this is just to trigger the game
 * to run
 */

#include "gobang.h"

#include <iostream>

using namespace std;


int main(int argc, char **argv)
{
    if (argc == 1)
    {
        cout << "======= "
             << "Welcome to Gobang!!!"
             << " ======="
             << endl;

        cout << endl;

        GoBang().run();
    }

    else
    {
        cout << "Usage: "
             << argv[0]
             << endl;
    }

    return 0;
}

