#include "general.h"

General::General(const char* mapFileLocation /*= "./data.txt\0"*/)
{
    fileLocation.open(mapFileLocation);

    std::string line;
    while(std::getline(fileLocation, line))
    {

        MAP_ROW++;
        //calc ones width
        const char* line_c = line.c_str();
        for(int i = 0;;i++){
            if(line_c[i] == '\0'){
                MAP_COL = i;
                break;
            }
        }
    } 
    fileLocation.clear();
    fileLocation.seekg(0);


    //init map space
    map = (char**)malloc(MAP_ROW * sizeof(char*));
    for(int i = 0; i < MAP_ROW; i++)
    {
        map[i] = (char*)malloc(MAP_COL * sizeof(char));
    }

    //paste from data.txt in map
    _set_map(); //<----- here TODO:
    _set_position();
}

General::~General()
{
    for(int row = 0; row < MAP_ROW; row++){
        for(int col = 0; col < MAP_COL; col++){
        }
        free(map[row]);
    }
    free(map);
}

void General::_set_map()
{
    std::string line;

    for(int index = 0;std::getline(fileLocation, line); index++){

        const char* line_c = line.c_str();

        //paste in map
        for(int i = 0; i < MAP_COL; i++){
            map[index][i] = line_c[i];
        }
    }
    fileLocation.clear();
    fileLocation.seekg(0);
}

void General::print_map()
{
    for(int row = 0; row < MAP_ROW; row++){
        for(int col = 0; col < MAP_COL; col++){
            if(row == barrier_pos_y && col == barrier_pos_x){
                std::cout << "\033[106;35m" << map[row][col]<< "\033[m";
            }else{
                std::cout << map[row][col];
            }
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}

void General::_set_position()
{
    for(int row = 0; row < MAP_ROW; row++){
        for(int col = 0; col < MAP_COL; col++){
            if(map[row][col] == '^'){
                cur_pos_x = col;
                cur_pos_y = row;
            }
        }
    }
}

void General::print_position()
{
    std::cout << "x: " << cur_pos_x << " | " << "y: " << cur_pos_y << "\n";
}

void General::print_direction()
{
    std::cout << direction << "\n";
}

void General::go_up()
{
    int next_pos_y = cur_pos_y - 1;
    int next_pos_x = cur_pos_x;

    map[cur_pos_y][cur_pos_x] = 'X';

    map[next_pos_y][next_pos_x] = '^';

    cur_pos_y = next_pos_y;
    cur_pos_x = next_pos_x;
}

void General::go_down()
{
    int next_pos_y = cur_pos_y + 1;
    int next_pos_x = cur_pos_x;

    map[cur_pos_y][cur_pos_x] = 'X';

    map[next_pos_y][next_pos_x] = '^';

    cur_pos_y = next_pos_y;
    cur_pos_x = next_pos_x;
}

void General::go_left()
{
    int next_pos_y = cur_pos_y;
    int next_pos_x = cur_pos_x - 1;

    map[cur_pos_y][cur_pos_x] = 'X';

    map[next_pos_y][next_pos_x] = '^';

    cur_pos_y = next_pos_y;
    cur_pos_x = next_pos_x;
}

void General::go_right()
{
    int next_pos_y = cur_pos_y;
    int next_pos_x = cur_pos_x + 1;

    map[cur_pos_y][cur_pos_x] = 'X';

    map[next_pos_y][next_pos_x] = '^';

    cur_pos_y = next_pos_y;
    cur_pos_x = next_pos_x;
}

int General::is_up_blocked()
{
    if(is_out_of_bounds()){
        return 0;
    }
    if(map[cur_pos_y - 1][cur_pos_x] == '#'){
        return 1;
    }

    return 0;
}

int General::is_down_blocked()
{
    if(is_out_of_bounds()){
        return 0;
    }
    if(map[cur_pos_y + 1][cur_pos_x] == '#'){
        return 1;
    }

    return 0;
}

int General::is_left_blocked()
{
    if(is_out_of_bounds()){
        return 0;
    }
    if(map[cur_pos_y][cur_pos_x - 1] == '#'){
        return 1;
    }

    return 0;
}

int General::is_right_blocked()
{
    if(is_out_of_bounds()){
        return 0;
    }
    if(map[cur_pos_y][cur_pos_x + 1] == '#'){
        return 1;
    }

    return 0;
}

int General::is_out_of_bounds()
{
    //std::cout << cur_pos_x << " - " << cur_pos_y << "\n";
    if(cur_pos_x <= 1 || cur_pos_y <= 1 || cur_pos_x >= MAP_COL -1 || cur_pos_y >= MAP_ROW -1){
        return 1;
    }
    return 0;
}

int General::count_marks(){
    int marks = 0;
    for(int row = 0; row < MAP_ROW; row++){
        for(int col = 0; col < MAP_COL; col++){
            if(map[row][col] == 'X'){
                marks++;
            }
        }
    }
    return marks;
}


int General::next_map(){

    _set_map();
    _set_position();

    if(barrier_pos_y >= MAP_ROW - 1){
        std::cout << "oh no" << "\n";
        return 0;
    }

    if(barrier_pos_x >= MAP_COL){
        barrier_pos_x = 0;
        barrier_pos_y++;
    }

    map[barrier_pos_y][barrier_pos_x] = '#';

    barrier_pos_x++;



    
    return 1;
}
