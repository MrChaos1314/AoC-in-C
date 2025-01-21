#include <iostream>
#include <fstream>
#include <unordered_set>
#include <thread>
#include <vector>

#include <cstdlib>
#include <cstdio>
#include <cstring>


class Map{

public:

    Map(const char* mapFileLocation = "./data.txt");

    ~Map();

    /*
    Map(const Map& cp_map);

    Map& operator=(const Map cp_map){
        for(int i = 0; i < WIDTH; i++){
            std::swap(map[i], cp_map.map[i]);
        }

        return *this;
    };
    */

    //variables
    struct position{
        unsigned int x;
        unsigned int y;
    };

    //init once in constructor
    unsigned int MAP_SIZE;

    //should be calc once in constructor and then no touchy
    unsigned int WIDTH = 0;
    unsigned int HEIGTH = 0;


    enum cell_type{
        EMPTY,
        BARRIER,
        PLAYER_UP,
        PLAYER_DOWN,
        PLAYER_LEFT,
        PLAYER_RIGHT,
        MARK_UP,
        MARK_DOWN,
        MARK_LEFT,
        MARK_RIGHT,
        MARK_CROSS,
        MARK_HORIZONTAL,
        MARK_VERTICAL,
    };


    void print_map();
    void print_player_position();
    void print_barrier_position();

    bool is_in_map(position cell_pos);

    void init_new_map();

    int count_marks();
    bool is_mark(position cell_pos);

    bool is_player(position cell_pos);

    position get_player_position();
    position get_barrier_position();

    bool barrier_finish = false;

    void reset_barrier_position();

    cell_type get_cell(position cell_pos);

    void set_player_position(unsigned int /*row*/, unsigned int /*col*/);
    void set_cell(position  cell_pos, cell_type);

    char translate_to_char(cell_type);
    enum cell_type translate_to_cell_type(char cell);

private:
    std::ifstream fileStream;

    char** map; 

    char** original_map;


    position _barrier = {0,0};
    position _player;

    void reset_map();

    //private functions
    void _init_map();

    void _init_player_position();
    void _init_barrier_position();

    void _set_barrier_position(unsigned int /*row*/, unsigned int /*col*/);

};
