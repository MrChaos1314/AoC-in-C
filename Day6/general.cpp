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
    cur_pos = map->get_player_position();
}

void General::_init_passed(){
    memset(passed, 0, passed_size * sizeof(int));
}

struct Map::position General::get_pos(){
    return cur_pos;
}

void General::set_position(Map::position player_pos){
    cur_pos.y = player_pos.y;
    cur_pos.x = player_pos.x;
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
        map->set_cell(cur_pos, Map::MARK_VERTICAL);

        set_position(get_up());

        map->set_cell(cur_pos, Map::PLAYER_UP);
    }
}

void General::go_right()
{
    if(is_in_map()){
        //mark current spot
        map->set_cell(cur_pos, Map::MARK_HORIZONTAL);

        set_position(get_right());

        map->set_cell(cur_pos, Map::PLAYER_RIGHT);
    }
}

void General::go_down(){

    if(is_in_map()){
        //mark current spot
        map->set_cell(cur_pos, Map::MARK_VERTICAL);

        set_position(get_down());

        map->set_cell(cur_pos, Map::PLAYER_DOWN);
    }
}

void General::go_left()
{
    if(is_in_map()){
        //mark current spot
        map->set_cell(cur_pos, Map::MARK_HORIZONTAL);

        set_position(get_left());

        map->set_cell(cur_pos, Map::PLAYER_LEFT);
    }
}

struct Map::position General::get_up(){

    struct Map::position position_up = {
        cur_pos.x,
        cur_pos.y - 1,
    };

    return position_up;
}

struct Map::position General::get_right(){

    struct Map::position position_right = {
        cur_pos.x + 1,
        cur_pos.y,
    };

    return position_right;
}

struct Map::position General::get_down(){

    struct Map::position position_down = {
        cur_pos.x,
        cur_pos.y + 1,
    };

    return position_down;
}

struct Map::position General::get_left(){

    struct Map::position position_left = {
        cur_pos.x - 1,
        cur_pos.y,
    };

    return position_left;
}

void General::turn(){

    Map::cell_type type = map->get_cell(cur_pos);

    switch(type){

        case Map::PLAYER_UP:
            map->set_cell(cur_pos, Map::PLAYER_RIGHT);
            direction = RIGHT;
        break;

        case Map::PLAYER_RIGHT:
            map->set_cell(cur_pos, Map::PLAYER_DOWN);
            direction = DOWN;
        break;

        case Map::PLAYER_DOWN:
            map->set_cell(cur_pos, Map::PLAYER_LEFT);
            direction = LEFT;
        break;

        case Map::PLAYER_LEFT:
            map->set_cell(cur_pos, Map::PLAYER_UP);
            direction = UP;
        break;

        default:
        break;
    }
}

bool General::is_up_blocked(){

    if(is_in_map()){
        if(map->get_cell(get_up()) == Map::BARRIER){
            return 1;
        }
    }

    return 0;
}

bool General::is_down_blocked(){

    if(is_in_map()){
        if(map->get_cell(get_down()) == Map::BARRIER){
            return 1;
        }
    }

    return 0;
}

bool General::is_left_blocked(){

    if(is_in_map()){
        if(map->get_cell(get_left()) == Map::BARRIER){
            return 1;
        }
    }

    return 0;
}

bool General::is_right_blocked(){

    if(is_in_map()){
        if(map->get_cell(get_right()) == Map::BARRIER){
            return 1;
        }
    }

    return 0;
}

bool General::is_in_map()
{
    return map->is_in_map(cur_pos);
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
    //three dimensional array as one dimensional 
    //(y.index * max.x * max.z + x.index *max.z + z.index)
    //index to the element in the three dimensional one dimensional array

    int index = 4*(cur_pos.y * map->WIDTH + cur_pos.x) + (int)direction;

    if(passed[index] == true){
        return true;
    }

    return false;
}

void General::add_passed(){
    //three dimensional array as one dimensional 
    //(y.index * max.x * max.z + x.index *max.z + z.index)
    //index to the element in the three dimensional one dimensional array

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
    return map->get_cell(cur_pos);
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
