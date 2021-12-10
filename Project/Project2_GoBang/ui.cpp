/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "ui.h"
#include <chrono>
#include <thread>
#include <locale>
using namespace std;

Window::Window(int h, int w, int x, int y)
    : win(newwin(h, w, x, y))
{
}

void Window::adds(const string& s)
{
    waddstr(win, s.c_str());
}

void Window::addc(char c)
{
    waddch(win, c);
}

UI::UI()
{
    setlocale(LC_ALL, "");

    initscr();
    cbreak();
    noecho();
    curs_set(0);
}

UI::~UI()
{
    endwin();
}

void UI::adds(const string& s)
{
    addstr(s.c_str());
}

void UI::addc(char c)
{
    addch(c);
}

Window *UI::new_window(int h, int w, int x, int y)
{
    Window *win = new Window(h, w, x, y);

    return win;
}

void UI::run()
{
    while (true)
    {
        if (!render())
        {
            break;
        }

        this_thread::sleep_for(chrono::milliseconds(1000 / FPS));
    }
}

