/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

// gobang header
#include "gobang.h"

// standard libs
#include <memory>
#include <sstream>
#include <iomanip>
#include <fstream>
#include <iostream>

// use std
using namespace std;

// number to win
static const int WIN_COUNT = 5;

// black white chars
static const char BLACK = 'X';
static const char WHITE = 'O';
static const char EMPTY = ' ';
static const char BOARD_CHARS[] = {BLACK, WHITE};

// the corners and borders of the grid
static const string UPPER_LEFT  = "┏";
static const string UPPER_RIGHT = "┓";
static const string LOWER_LEFT  = "┗";
static const string LOWER_RIGHT = "┛";
static const string RIGHT_T     = "┣";
static const string LEFT_T      = "┫";
static const string DOWN_T      = "┳";
static const string UP_T        = "┻";
static const string CROSS       = "╋";
static const string VERTICAL    = "┃";
static const string HORIZONTAL  = "━━━";
static const string SPACES      = "   ";
static const string SPACE       = " ";

// padding
static const int    PADDING     = 3;

// color pairs
static const int COLOR_SELECTED     = 1;
static const int COLOR_PLAYER_BLACK = 2;
static const int COLOR_PLAYER_WHITE = 3;
static const int COLOR_PLAYER_WIN   = 4;


/**
 * @brief GoBang constructor
 * It is the only construtor GoBang provide
 *
 * 1. setup GoBang board related members
 * 2. setup COLOR pairs
 * 3. setup WINDOWs
 */
GoBang::GoBang()
    : UI()
    , h_(10)
    , w_(10)
    , x_(0)
    , y_(0)
    , turn_(T_BLACK)
    , board_(h_, string(w_, EMPTY))
{

    // init color pairs
    start_color();
    init_pair(COLOR_SELECTED, COLOR_WHITE, COLOR_GREEN);
    init_pair(COLOR_PLAYER_BLACK, COLOR_CYAN, COLOR_BLACK);
    init_pair(COLOR_PLAYER_WHITE, COLOR_RED, COLOR_BLACK);
    init_pair(COLOR_PLAYER_WIN, COLOR_MAGENTA, COLOR_BLACK);

    // init windows
    board_win_ = newwin(h_*3+PADDING, w_*5+PADDING, 10, 10);
    // enable keyboard
    keypad(board_win_, TRUE);

    info_win_ = newwin(9, 28, 11, 10+w_*5+PADDING);
    save_load_win_ = newwin(3, 28, 21, 10+w_*5+PADDING);

    // enable keyboard
    keypad(save_load_win_, TRUE);
}

/**
 * @brief GoBang destructor
 *
 * free all the WINDOWs
 */
GoBang::~GoBang()
{
    // destroy all the windows
    delwin(board_win_);
    delwin(info_win_);
    delwin(save_load_win_);
}

/**
 * @brief who's turn?
 *
 * @return Turn enum
 */
Turn GoBang::turn()
{
    return turn_;
}

/**
 * @brief get the position on the board_win_
 * not the actual position on board_
 *
 * @param x int x position on the board_
 * @return int x position on the board_win_
 */
int GoBang::get_visual_x(int x)
{
    return x * 2 + 1 + 1;
}

/**
 * @brief get the position on the board_win_
 * not the actual position on board_
 *
 * @param y int y position on the board_
 * @return int y position on the board_win_
 */
int GoBang::get_visual_y(int y)
{
    return y * 4 + 1 + PADDING;
}

/**
 * @brief render the grid
 *
 * Render board_win_ without colors for BLACK/WHITE
 * This is basically handmade drawing
 */
void GoBang::render_grid()
{
    wclear(board_win_);
    ostringstream out;

    // output padding
    out << SPACES;
    out << SPACE;
    out << SPACE;

    for (int i = 0; i < w_; ++i)
    {
        out << setw(PADDING + 1)
            << left
            << i;
    }

    out << endl;
    out << SPACES;
    out << UPPER_LEFT;

    for (int i = 0; i < w_; ++i)
    {
        out << HORIZONTAL
            << (i + 1 == w_ ? UPPER_RIGHT
                : DOWN_T);
    }

    out << endl;

    for (int i = 0; i < h_; ++i)
    {
        out << setw(PADDING)
            << left
            << i;

        out << VERTICAL;

        for (int j = 0; j < w_; ++j)
        {
            out << SPACE
                <<(board_[i][j])
                << SPACE
                << VERTICAL;
        }

        out << endl;
        out << SPACES;
        out << (i + 1 == w_ ? LOWER_LEFT
                : RIGHT_T);

        for (int j = 0; j < w_; ++j)
        {
            out << HORIZONTAL;
            out << (j + 1 == w_ ? (i + 1 == h_ ? LOWER_RIGHT
                                   : LEFT_T)
                    : (i + 1 == h_ ? UP_T
                       : CROSS));
        }

        out << endl;
    }

    mvwaddstr(board_win_, 0, 0, out.str().c_str());
}

/**
 * @brief render the chess on board
 *
 * color the chesses
 */
void GoBang::render_board()
{
    for (int i = 0; i < h_; ++i)
    {
        for (int j = 0; j < w_; ++j)
        {
            if (board_[i][j] == BLACK)
            {
                wattron(board_win_, COLOR_PAIR(COLOR_PLAYER_BLACK));

                string s = SPACE + board_[i][j] + SPACE;
                int x = get_visual_x(i);
                int y = get_visual_y(j);

                mvwaddstr(board_win_, x, y, s.c_str());
                wattroff(board_win_, COLOR_PAIR(COLOR_PLAYER_BLACK));
            }
            else if (board_[i][j] == WHITE)
            {
                wattron(board_win_, COLOR_PAIR(COLOR_PLAYER_WHITE));

                string s = SPACE + board_[i][j] + SPACE;
                int x = get_visual_x(i);
                int y = get_visual_y(j);

                mvwaddstr(board_win_, x, y, s.c_str());
                wattroff(board_win_, COLOR_PAIR(COLOR_PLAYER_WHITE));
            }
        }
    }

    wattron(board_win_, COLOR_PAIR(COLOR_SELECTED));

    string s = SPACE + board_[x_][y_] + SPACE;
    int x = get_visual_x(x_);
    int y = get_visual_y(y_);

    mvwaddstr(board_win_, x, y, s.c_str());
    wattroff(board_win_, COLOR_PAIR(COLOR_SELECTED));

    wrefresh(board_win_);
}

/**
 * @brief redner information window
 *
 * 1. how to play
 * 2. who's turn
 */
void GoBang::render_info()
{
    wclear(info_win_);
    ostringstream oss;
    oss << "  Move: UP/DOWN/LEFT/RIGHT\n";
    oss << "  Play: ENTER\n";
    oss << "  Save: s\n";
    oss << "  Load: l\n";
    oss << "  Quit: q\n";
    oss << "\n";
    oss << "  Turn: "
        << (turn_ == T_BLACK ? "BLACK" : "WHITE")
        << " ("
        << BOARD_CHARS[turn_]
        << ")";

    mvwaddstr(info_win_, 1, 0, oss.str().c_str());
    box(info_win_, 0, 0);
    wrefresh(info_win_);
}

/**
 * @brief render the window for load
 *
 * get input load file name and load
 */
void GoBang::render_load()
{
    wclear(save_load_win_);
    mvwaddstr(save_load_win_, 1, 1, " Load from: ");
    box(save_load_win_, 0, 0);
    wrefresh(save_load_win_);

    string file;
    for (int c = wgetch(save_load_win_); c != '\n'; c = wgetch(save_load_win_))
    {
        file.push_back(char(c));
        mvwaddstr(save_load_win_, 1, 13, file.c_str());
        wrefresh(save_load_win_);
    }

    read(file);
}

/**
 * @brief render the window for save
 *
 * save the GoBang to a file
 */
void GoBang::render_save()
{
    wclear(save_load_win_);
    mvwaddstr(save_load_win_, 1, 1, " Save to: ");
    box(save_load_win_, 0, 0);
    wrefresh(save_load_win_);

    string file;
    for (int c = wgetch(save_load_win_); c != '\n'; c = wgetch(save_load_win_))
    {
        if (c == KEY_BACKSPACE ||
            c == 127 ||
            c == '\b')
        {
            file.pop_back();
        }
        else
        {
            file.push_back(char(c));
        }

        wclear(save_load_win_);
        mvwaddstr(save_load_win_, 1, 1, " Save to: ");
        mvwaddstr(save_load_win_, 1, 11, file.c_str());
        box(save_load_win_, 0, 0);
        wrefresh(save_load_win_);
    }

    save(file);
}

/**
 * @brief render the window for winner!
 */
void GoBang::render_win()
{
    wclear(info_win_);

    ostringstream oss;
    wattron(info_win_, COLOR_PAIR(COLOR_PLAYER_WIN));
    oss << "  "
        << (turn_ == T_BLACK ? "WHITE"
                             : "BLACK");
    oss << "("
        << (turn_ == T_BLACK ? WHITE
                             : BLACK)
        << ")"
        << " WIN !!!\n";

    mvwaddstr(info_win_, 1, 0, oss.str().c_str());
    wattroff(info_win_, COLOR_PAIR(COLOR_PLAYER_WIN));

    mvwaddstr(info_win_, 3, 0, "  Press any key to restart");
    box(info_win_, 0, 0);
    wrefresh(info_win_);
}

/**
 * @brief render the GoBang
 * this overrides @ref UI#render
 *
 * @return bool true if success
 */
bool GoBang::render()
{
    clear();
    refresh();

    render_grid();
    render_board();
    render_info();

    // get keyboard
    int c = wgetch(board_win_);

    // quit
    if (c == 'q')
    {
        return false;
    }

    // move up
    if (c == KEY_UP)
    {
        --x_;
    }
    // move down
    else if (c == KEY_DOWN)
    {
        ++x_;
    }
    // move left
    else if (c == KEY_LEFT)
    {
        --y_;
    }
    // move right
    else if (c == KEY_RIGHT)
    {
        ++y_;
    }
    // place
    else if (c == '\n')
    {
        place(x_, y_);
    }
    // save
    else if (c == 's')
    {
        render_save();

        return false;
    }
    // load
    else if (c == 'l')
    {
        render_load();
    }

    // out of bound
    if (x_ < 0)
    {
        x_ = 0;
    }

    // out of bound
    if (x_ >= h_)
    {
        x_ = h_ - 1;
    }

    // out of bound
    if (y_ < 0)
    {
        y_ = 0;
    }

    // out of bound
    if (y_ >= w_)
    {
        y_ = w_ - 1;
    }

    // anyone win?
    if (check_win())
    {
        render_win();
        getch();
        reset_state();
    }

    return true;
}

/**
 * @brief reset the GoBang state
 */
void GoBang::reset_state()
{
    // reset the grid
    for (int i = 0; i < h_; ++i)
    {
        for (int j = 0; j < w_; ++j)
        {
            // set to empty line by line
            board_[i][j] = EMPTY;
        }
    }

    x_ = 0;
    y_ = 0;
    turn_ = T_BLACK;
}

/**
 * @brief is given position on board
 *
 * @param x int position x
 * @param y int position y
 *
 * @return bool true if on board
 */
bool GoBang::in(int x, int y)
{
    return 0 <= x &&
           x < h_ &&
           0 <= y &&
           y < w_;
}

/**
 * @brief place on board (x, y)
 *
 * @param x int position x
 * @param y int position y
 *
 * @return bool if placed successfully
 */
bool GoBang::place(int x, int y)
{
    // not empty
    // cannot place
    if (board_[x][y] != EMPTY)
    {
        return false;
    }

    // get the char
    board_[x][y] = BOARD_CHARS[turn_];
    turn_ = turn_ == T_BLACK ? T_WHITE
                             : T_BLACK;

    return true;
}

/**
 * @brief is winning on some given position and given direction
 *
 * @param x int position x
 * @param y int position y
 * @param dx int direction unit x
 * @param dy int direction unit y
 *
 * @return bool true if pos (x, y) with dir (dx, dy) wins
 */
bool GoBang::is_win(int x, int y, int dx, int dy)
{
    const char c = board_[x][y];

    // empty
    // do not check!
    if (c == EMPTY)
    {
        return false;
    }

    // check the win count
    for (int i = 0; i < WIN_COUNT; ++i)
    {
        // not on board
        if (!in(x, y))
        {
            return false;
        }

        // not expected
        if (board_[x][y] != c)
        {
            return false;
        }

        x += dx;
        y += dy;
    }

    return true;
}

/**
 * @brief is the board terminal state?
 *
 * @return bool true if someone wins
 */
bool GoBang::check_win()
{
    // direction unit vector

    // direction on x
    static int dx[] = {0, 0, -1, -1, -1, 1, 1, 1};
    // direction on y
    static int dy[] = {-1, 1, -1, 0, 1, -1, 0, 1};

    for (int i = 0; i < h_; ++i)
    {
        for (int j = 0; j < w_; ++j)
        {
            // iterate over the 8 directions
            for (int k = 0; k < 8; ++k)
            {
                // check win on the given
                // position (i, j)
                // and given direction (dx[k], dy[k])
                if (is_win(i, j, dx[k], dy[k]))
                {
                    return true;
                }
            }
        }
    }

    return false;
}

/**
 * @brief file string file path
 *
 * @param file string file
 * @return bool is save success
 */
bool GoBang::save(const string& file)
{
    ofstream out(file, ios::binary);
    if (!out)
    {
        return false;
    }

    bool is_black = turn_ == T_BLACK;
    // write height
    out.write((char *)(&h_), sizeof(h_));
    // write width
    out.write((char *)(&w_), sizeof(w_));
    // write chosen x
    out.write((char *)(&x_), sizeof(x_));
    // write chosen y
    out.write((char *)(&y_), sizeof(y_));
    // write who's tturn
    out.write((char *)(&is_black), sizeof(is_black));

    // write grid
    for (int i = 0; i < h_; ++i)
    {
        for (int j = 0; j < w_; ++j)
        {
            char c = board_[i][j];
            // write line by line
            out.write(&c, sizeof(char));
        }
    }

    return true;
}

void GoBang::play()
{
    vector<int> xs;
    vector<int> ys;

    char opp = BOARD_CHARS[1 - turn_];

    for (int i = 0; i < h_; ++i)
    {
        for (int j = 0; j < w_; ++j)
        {
            if (board_[i][j] == opp)
            {
                // check right
                if (in(i, j + 1))
                {
                    // ok empty
                    if (board_[i][j+1] == EMPTY)
                    {
                        xs.push_back(i);
                        ys.push_back(j + 1);
                    }
                }

                // check left
                if (in(i, j - 1))
                {
                    // ok empty
                    if (board_[i][j-1] == EMPTY)
                    {
                        xs.push_back(i);
                        ys.push_back(j - 1);
                    }
                }

                // check up
                if (in(i - 1, j))
                {
                    // ok empty
                    if (board_[i-1][j] == EMPTY)
                    {
                        xs.push_back(i - 1);
                        ys.push_back(j);
                    }
                }

                // check down
                if (in(i + 1, j))
                {
                    // ok empty
                    if (board_[i+1][j] == EMPTY)
                    {
                        xs.push_back(i + 1);
                        ys.push_back(j);
                    }
                }

                // check right - up
                if (in(i - 1, j + 1))
                {
                    // ok empty
                    if (board_[i-1][j+1] == EMPTY)
                    {
                        xs.push_back(i - 1);
                        ys.push_back(j + 1);
                    }
                }

                // check right - down
                if (in(i + 1, j + 1))
                {
                    // ok empty
                    if (board_[i+1][j+1] == EMPTY)
                    {
                        xs.push_back(i + 1);
                        ys.push_back(j + 1);
                    }
                }

                // check left - up
                if (in(i - 1, j - 1))
                {
                    // ok empty
                    if (board_[i-1][j-1] == EMPTY)
                    {
                        xs.push_back(i - 1);
                        ys.push_back(j - 1);
                    }
                }

                // check left - down
                if (in(i + 1, j - 1))
                {
                    // ok empty
                    if (board_[i+1][j-1] == EMPTY)
                    {
                        xs.push_back(i + 1);
                        ys.push_back(j - 1);
                    }
                }
            }
        }
    }


    // random pick
    int pick = random() % (xs.size());

    place(xs[pick], ys[pick]);
}

/**
 * @brief read GoBang from a given file
 *
 * @param file string file path
 */
void GoBang::read(const string& file)
{
    ifstream in(file, ios::binary);

    // read height
    in.read((char*)(&h_), sizeof(h_));
    // read width
    in.read((char*)(&w_), sizeof(w_));
    // read chosen x
    in.read((char*)(&x_), sizeof(x_));
    // read chosen y
    in.read((char*)(&y_), sizeof(y_));

    // resize the board
    board_.resize(h_, string(w_, EMPTY));

    // read is who's turn
    bool is_black;
    in.read((char*)(&is_black), sizeof(is_black));
    turn_ = is_black ? T_BLACK
                     : T_WHITE;

    // read board
    char c;
    for (int i = 0; i < h_; ++i)
    {
        for (int j = 0; j < w_; ++j)
        {
            // read line by line
            in.read(&c, sizeof(char));
            board_[i][j] = c;
        }
    }
}

