#include "general.h"

General::General(Map* map /*= Map("./data.txt")*/)
{
    this->map = map;
    _init_position();
    _init_direction();

    passed_size = map->HEIGTH * map->WIDTH * 4;
    passed = (int*)malloc(passed_size * sizeof(int));
}

void General::_init_position()
{
    cur_pos.x = map->get_player_position().x;
    cur_pos.y = map->get_player_position().y;
}

void General::_init_passed(){
    memset(passed, 0, passed_size * sizeof(int));
}

struct General::position General::get_pos(){
    return cur_pos;
}

void General::set_position(unsigned int y, unsigned int x){
    cur_pos.y = y;
    cur_pos.x = x;
}

void General::print_position()
{
    std::cout << "x: " << cur_pos.x << " | " << "y: " << cur_pos.y << "\n";
}

void General::print_map(){
    map->print_map();
}

void General::go_up()
{
    //WATCH AT THIS POINT IF NO PROBLEMS WITH first set mark
    //then go next without saving the position before
    if(is_in_map()){
        //mark current spot
        map->set_cell(cur_pos.y, cur_pos.x, Map::MARK_VERTICAL);

        set_position(get_up().y, get_up().x);

        map->set_cell(cur_pos.y, cur_pos.x, Map::PLAYER_UP);
    }
}

void General::go_right()
{
    if(is_in_map()){
        //mark current spot
        map->set_cell(cur_pos.y, cur_pos.x, Map::MARK_HORIZONTAL);

        set_position(get_right().y, get_right().x);

        map->set_cell(cur_pos.y, cur_pos.x, Map::PLAYER_RIGHT);
    }
}

void General::go_down(){

    if(is_in_map()){
        //mark current spot
        map->set_cell(cur_pos.y, cur_pos.x, Map::MARK_VERTICAL);

        set_position(get_down().y, get_down().x);

        map->set_cell(cur_pos.y, cur_pos.x, Map::PLAYER_DOWN);
    }
}

void General::go_left()
{
    if(is_in_map()){
        //mark current spot
        map->set_cell(cur_pos.y, cur_pos.x, Map::MARK_HORIZONTAL);

        set_position(get_left().y, get_left().x);

        map->set_cell(cur_pos.y, cur_pos.x, Map::PLAYER_LEFT);
    }
}

struct General::position General::get_up(){

    struct position position_up = {
        cur_pos.x,
        cur_pos.y - 1,
    };

    return position_up;
}

struct General::position General::get_right(){

    struct position position_right = {
        cur_pos.x + 1,
        cur_pos.y,
    };

    return position_right;
}

struct General::position General::get_down(){

    struct General::position position_down = {
        cur_pos.x,
        cur_pos.y + 1,
    };

    return position_down;
}

struct General::position General::get_left(){

    struct General::position position_left = {
        cur_pos.x - 1,
        cur_pos.y,
    };

    return position_left;
}

void General::turn(){

    Map::cell_type type = map->get_cell(cur_pos.y, cur_pos.x);

    switch(type){

        case Map::PLAYER_UP:
            map->set_cell(cur_pos.y, cur_pos.x, Map::PLAYER_RIGHT);
            direction = RIGHT;
        break;

        case Map::PLAYER_RIGHT:
            map->set_cell(cur_pos.y, cur_pos.x, Map::PLAYER_DOWN);
            direction = DOWN;
        break;

        case Map::PLAYER_DOWN:
            map->set_cell(cur_pos.y, cur_pos.x, Map::PLAYER_LEFT);
            direction = LEFT;
        break;

        case Map::PLAYER_LEFT:
            map->set_cell(cur_pos.y, cur_pos.x, Map::PLAYER_UP);
            direction = UP;
        break;

        default:
        break;
    }
}

bool General::is_up_blocked(){

    if(is_in_map()){
        if(map->get_cell(get_up().y, get_up().x) == Map::BARRIER){
            return 1;
        }
    }

    return 0;
}

bool General::is_down_blocked(){

    if(is_in_map()){
        if(map->get_cell(get_down().y, get_down().x) == Map::BARRIER){
            return 1;
        }
    }

    return 0;
}

bool General::is_left_blocked(){

    if(is_in_map()){
        if(map->get_cell(get_left().y, get_left().x) == Map::BARRIER){
            return 1;
        }
    }

    return 0;
}

bool General::is_right_blocked(){

    if(is_in_map()){
        if(map->get_cell(get_right().y, get_right().x) == Map::BARRIER){
            return 1;
        }
    }

    return 0;
}

bool General::is_in_map()
{
    return map->is_in_map(cur_pos.y, cur_pos.x);
}

int General::get_marks(){
    return map->count_marks();
}


void General::next_map(){

    map->init_new_map();
    _init_position();
    _init_direction();
    _init_passed();

    cur_walk = 0;
}

bool General::is_barrier_end(){
    return map->barrier_finish;
}


bool General::is_loop(){

    int index = 4*(cur_pos.y * map->WIDTH + cur_pos.x) + (int)direction;

    if(passed[index] == true){
        return true;
    }

    return false;
}

void General::add_passed(){
    int index = 4*(cur_pos.y * map->WIDTH + cur_pos.x) + (int)direction;
    passed[index] = true;
}

void General::reset_barrier(){
    map->reset_barrier_position();
}

void General::walk(){

    switch(direction){

        case UP:

            if(is_up_blocked()){
                add_passed();
                turn();
                cur_walk++;
            }else{
                //add_passed();
                go_up();
                cur_walk++;
            } 

            break;

        case RIGHT:

            if(is_right_blocked()){
                add_passed();
                turn();
                cur_walk++;
            }else{
                //add_passed();
                go_right();
                cur_walk++;
            }

            break;

        case DOWN:

            if(is_down_blocked()){
                add_passed();
                turn();
                cur_walk++;
            }else{
                //add_passed();
                go_down();
                cur_walk++;
            }

            break;

        case LEFT:

            if(is_left_blocked()){
                add_passed();
                turn();
                cur_walk++;
            }else{
                //add_passed();
                go_left();
                cur_walk++;
            } 

            break;
    }


    //DEBUG
    //map->print_map();
    //std::this_thread::sleep_for(std::chrono::milliseconds(5));
}

//gets the player facing to which direction on the map
Map::cell_type General::get_player(){
    return map->get_cell(cur_pos.y,cur_pos.x);
}


void General::_init_direction(){
    Map::cell_type player = get_player();

    switch (player){
        case Map::PLAYER_UP:
            direction = UP;
            break;
        case Map::PLAYER_RIGHT:
            direction = RIGHT;
            break;
        case Map::PLAYER_DOWN:
            direction = DOWN;
            break;
        case Map::PLAYER_LEFT:
            direction = LEFT;
            break;

        default:
            break;
    }
}
