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

UI::UI() {
    setlocale(LC_ALL, "");
    initscr();
    cbreak();
    noecho();
    curs_set(0);
}

UI::~UI() {
    endwin();
}

void UI::adds(const string& s) {
    addstr(s.c_str());
}

void UI::addc(char c) {
    addch(c);
}

void UI::run() {
    while (true) {
        if (!render()) {
            break;
        }

        this_thread::sleep_for(chrono::milliseconds(1000 / FPS));
    }
}

