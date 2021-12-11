/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ui.h
 * Author: nancyhe
 *
 * Created on December 11, 2021, 2:16 PM
 */

#ifndef UI_H
#define UI_H

#pragma once

#include <ncurses.h>
#include <string>
using namespace std;

template<typename T>
class CursesObj
{
public:
    CursesObj(int h, int w, int x, int y);

    void adds(const string& s);
    void addc(char c);

private:
    T *win;
};


class UI
{
public:
    static const int FPS = 15;

public:
    UI();
    ~UI();
    void run();

protected:
    void adds(const string& s);
    void addc(char c);
    CursesObj<WINDOW> *new_window(int h, int w, int x, int y);

private:
    virtual bool render() = 0;
};



#endif /* UI_H */

