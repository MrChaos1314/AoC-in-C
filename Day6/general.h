#include <iostream>
#include <fstream>

#include <cstdlib>
#include <cstdio>
#include <cstring>

class General{

public:
    // constructor
    General(const char* mapFileLocation = "./data.txt");

    // copy constructor idk noch, was das ist...
    //General( const General &right);

    ~General();

    //assignment constructor idk was das ist
    //const General& operator=(const General &right);


    //functions
    void print_map();
    void print_position();
    void print_direction();

    void go_up();
    void go_down();
    void go_left();
    void go_right();

    int is_up_blocked();
    int is_down_blocked();
    int is_left_blocked();
    int is_right_blocked();

    int is_out_of_bounds();

    int count_marks();
    int next_map();
    int barrier_pos_x = 0;
    int barrier_pos_y = 0;

private:
    //private variables
    std::ifstream fileLocation;

    //should be calc once and then no touchy
    int MAP_ROW = 0;
    int MAP_COL = 0;

    int cur_pos_x;
    int cur_pos_y;

    //Part 2 variable

    char** map; 
    enum General_direction{
        UP,
        DOWN,
        LEFT,
        RIGHT
    } direction;

    //private functions
    void _set_map();
    void _set_position();

};
