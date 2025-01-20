#include "map.h"

Map::Map(const char* mapFileLocation /*= "./data.txt"*/){
    fileStream.open(mapFileLocation);

    std::string line;
    while(std::getline(fileStream, line))
    {
        HEIGTH++;
        WIDTH = line.length();
    } 
    fileStream.clear();
    fileStream.seekg(0);

    MAP_SIZE = HEIGTH * WIDTH;


    //init map space for origin
    original_map = (char**)malloc(HEIGTH * sizeof(char*));
    for(unsigned int i = 0; i < HEIGTH; i++)
    {
        original_map[i] = (char*)malloc(WIDTH * sizeof(char));
    }

    //init map space for copy
    map = (char**)malloc(HEIGTH * sizeof(char*));
    for(unsigned int i = 0; i < HEIGTH; i++)
    {
        map[i] = (char*)malloc(WIDTH * sizeof(char));
    }

    //paste from data.txt in map
    _init_map();     
    _init_player_position();
}

Map::~Map(){
    for(unsigned int row = 0; row < HEIGTH; row++){
        for(unsigned int col = 0; col < WIDTH; col++){
        }
        free(map[row]);
        free(original_map[row]);
    }
    free(map);
    free(original_map);

    fileStream.close();
}

/*
Map::Map(const Map& cp_map){
    map = (char**)malloc(HEIGTH * sizeof(char*)); 
    for(int i = 0; i < HEIGTH; i++)
    {
        map[i] = (char*)malloc(WIDTH * sizeof(char));
    }

    for(int row = 0; row < cp_map.HEIGTH; row++){
        for(int col = 0; col < cp_map.WIDTH; col++){
            map[row][col] = cp_map.map[row][col];
        }
    }
}
*/

void Map::_init_map(){
    std::string line;

    for(unsigned int index = 0;std::getline(fileStream, line); index++){

        const char* line_c = line.c_str();

        //paste in map
        for(unsigned int i = 0; i < WIDTH; i++){
            original_map[index][i] = line_c[i];
        }
    }
    fileStream.clear();
    fileStream.seekg(0);

    reset_map();

}

void Map::reset_map(){
    /*
    for(unsigned int row = 0; row < HEIGTH; row++){
        for(unsigned int col = 0; col < WIDTH; col++){
            map[row][col] = original_map[row][col];
        }
    }
        */
    for(unsigned int row = 0; row < HEIGTH; row++){
        memcpy(map[row], original_map[row], HEIGTH * sizeof(char));
    }
}

void Map::print_map(){
    std::cout << "\033[2J" << std::endl;
    for(unsigned int row = 0; row < HEIGTH; row++){

        for(unsigned int col = 0; col < WIDTH; col++){

            if(row == _barrier.y && col == _barrier.x){
                std::cout << "\033[106;35m" << map[row][col] << "\033[m";

        }else if(is_player(row, col)){
                std::cout << "\033[106;35m" << map[row][col] << "\033[m";
            }else{
                std::cout << map[row][col];
            }
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}

void Map::_init_player_position(){
    for(unsigned int row = 0; row < HEIGTH; row++){
        for(unsigned int col = 0; col < WIDTH; col++){
            if(map[row][col] == '^'){
                set_player_position(row, col);
            }
        }
    }
}


void Map::set_player_position(unsigned int row, unsigned int col){
    _player.y = row;
    _player.x = col;
}

void Map::print_player_position(){
    std::cout << get_player_position().x << " - " << get_player_position().y << "\n";
}

struct Map::position Map::get_player_position(){
    return _player;
}

void Map::_init_barrier_position(){
    
    if(get_barrier_position().x == WIDTH){
        _set_barrier_position(get_barrier_position().y + 1, 0);
    }

    if(get_barrier_position().y == HEIGTH){
        _set_barrier_position(0, 0);
        barrier_finish = true;
    }
   
    if(barrier_finish == false){
        if(!is_player(_barrier.y, _barrier.x)){
            set_cell(_barrier.y, _barrier.x, BARRIER);
        }

        _set_barrier_position(get_barrier_position().y, get_barrier_position().x + 1);
    }
}

void Map::reset_barrier_position(){
    barrier_finish = false;
    _set_barrier_position(0, 0);
}

struct Map::position Map::get_barrier_position(){
    return _barrier;
}

void Map::_set_barrier_position(unsigned int row, unsigned int col){
    _barrier.y = row;
    _barrier.x = col;
}

int Map::count_marks(){
    int marks = 0;
    for(unsigned int row = 0; row < HEIGTH; row++)
    {
        for(unsigned int col = 0; col < WIDTH; col++)
        {
            if(is_mark(row, col))
            {
                marks++;
            }
        }
    }
    return marks + 1; //counting its own position too
}

bool Map::is_mark(unsigned int row, unsigned int col){

    switch(get_cell(row,col)){

        case MARK_UP:
            return true;

        case MARK_DOWN:
            return true;

        case MARK_LEFT:
            return true;

        case MARK_RIGHT:
            return true;

        case MARK_HORIZONTAL:
            return true;

        case MARK_VERTICAL:
            return true;
            
        case MARK_CROSS:
            return true;

        default:
        return false;
    }
}

bool Map::is_player(unsigned int row, unsigned int col){

    switch(get_cell(row,col)){

        case PLAYER_UP:
            return true;

        case PLAYER_DOWN:
            return true;

        case PLAYER_LEFT:
            return true;

        case PLAYER_RIGHT:
            return true;

        default:
        return false;
    }
}

bool Map::is_in_map(unsigned int row, unsigned int col){
    if(row > 0 && col > 0 && col < WIDTH - 1 && row < HEIGTH - 1){
        return true;
    }else{
        return false;
    }
}

void Map::init_new_map(){

    reset_map();
    _init_barrier_position();

}

Map::cell_type Map::get_cell(unsigned int row, unsigned int col){
    cell_type cell = translate_to_cell_type(map[row][col]);
    return cell;
};

void Map::set_cell(unsigned int row, unsigned int col, cell_type cell){
    map[row][col] = translate_to_char(cell); 
}

char Map::translate_to_char(cell_type cell){
    switch(cell){
        case BARRIER:
            return '#';
            break;

        case PLAYER_UP:
            return '^';
            break;

        case PLAYER_RIGHT:
            return '>';
            break;

        case PLAYER_DOWN:
            return 'V';
            break;

        case PLAYER_LEFT:
            return '<';
            break;

        case MARK_HORIZONTAL:
            return '-';
            break;

        case MARK_VERTICAL:
            return '|';
            break;

        case MARK_UP:
            return 'I';
            break;

        case MARK_DOWN:
            return 'i';
            break;

        case MARK_LEFT:
            return 'W';
            break;

        case MARK_RIGHT:
            return 'w';
            break;

        case MARK_CROSS:
            return '+';
            break;

        case EMPTY:
            return '.';
            break;

        default:
            return '.';
            break;
    }
}

enum Map::cell_type Map::translate_to_cell_type(char cell){
    switch(cell){

        case '#':
            return BARRIER;
            break;

        case '^':
            return PLAYER_UP;
            break;

        case 'V':
            return PLAYER_DOWN;
            break;

        case '<':
            return PLAYER_LEFT;
            break;

        case '>':
            return PLAYER_RIGHT;
            break;

        case '|':
            return MARK_VERTICAL;
            break;

        case '-':
            return MARK_HORIZONTAL;
            break;

        case 'I':
            return MARK_UP;
            break;

        case 'i':
            return MARK_DOWN;
            break;

        case 'W':
            return MARK_LEFT;
            break;

        case 'w':
            return MARK_RIGHT;
            break;

        case '+':
            return MARK_CROSS;
            break;

        case '.':
            return EMPTY;
            break;

        default:
            return EMPTY;
            break;
    }
}
