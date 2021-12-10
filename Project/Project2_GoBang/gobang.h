/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   gobang.h
 * Author: nancyhe
 *
 * Created on December 10, 2021, 12:10 PM
 */

#ifndef GOBANG_H
#define GOBANG_H

#pragma once

#include "ui.h"
#include <string>
#include <vector>
using namespace std;

enum Turn
{
    T_BLACK = 0,
    T_WHITE = 1,
};

/**
 * @brief GoBang class support both
 * chess logic and UI rendering
 *
 * @param h_ int height
 * @param w_ int width
 * @param x_ int selected x
 * @param y_ int selected y
 * @param board_ vector<string> the gobang board, size h_ x w_
 * @param board_win_ WINDOW* window to render board
 * @param info_win WINDOW* window to render information
 * @param save_load_win_ WINDOW* window to show save/load info
 */
class GoBang : public UI
{
public:
    GoBang();
    ~GoBang();

private:
    virtual bool render() override;

    Turn turn();
    bool place(int x, int y);
    bool check_win();
    bool in(int x, int y);
    bool is_win(int x, int y, int dx, int dy);
    void render_grid();
    void render_board();
    void render_info();
    void render_save();
    void render_load();
    void render_win();
    int get_visual_x(int x);
    int get_visual_y(int y);
    void reset_state();
    void read(const string& file);
    bool save(const string& file);
    void play();

    int h_;
    int w_;
    int x_;
    int y_;
    Turn turn_;
    vector<string> board_;
    WINDOW* board_win_;
    WINDOW* info_win_;
    WINDOW* save_load_win_;
};



#endif /* GOBANG_H */

