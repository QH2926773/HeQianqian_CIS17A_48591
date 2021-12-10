/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ui.h
 * Author: nancyhe
 *
 * Created on December 10, 2021, 12:10 PM
 */

#ifndef UI_H
#define UI_H

#pragma once

#include <ncurses.h>
#include <string>
using namespace std;


class Window
{
public:
    Window(int h, int w, int x, int y);

    void adds(const string& s);
    void addc(char c);

private:
    WINDOW *win;
};


class UI
{
public:
    static const int FPS = 15;

public:
    UI();
    ~UI();
    void adds(const string& s);
    void addc(char c);
    Window *new_window(int h, int w, int x, int y);
    void run();

private:
    virtual bool render() = 0;
};



#endif /* UI_H */

