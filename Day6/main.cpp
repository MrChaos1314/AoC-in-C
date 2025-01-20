#include "general.h"

int main(){
    Map map = Map("./data.txt");
    General general = General(&map);
    //General general;

    //Part 1
    //order of whiles importent (clockwise turning)
    while(general.is_in_map()){
            general.walk();
    }


int marks = general.get_marks();
std::cout << marks << "\n";


    //Part 2 brute force
    int counter = 0;
    /*
    while(!general.is_barrier_end()){
        general.next_map();

        //try 1000 times to get out if 1000 reached go out and 
        //don't count - else count
        //counting the potentional loops
        for(int i = 0; general.is_in_map(); i++){

            general.walk();

            //TEST ~Knut
            if(i == 6270){
                counter++;
                break;
            }
        }
        if(!general.is_in_map()){
            if(general.max_walk < general.cur_walk){
                general.max_walk = general.cur_walk;
            }
        }
    }
    std::cout << counter << "\n";
    std::cout << general.max_walk << "\n";
    */

    //Part 2     
    general.reset_barrier();

    //as long as not every barrier position is through
    while(!general.is_barrier_end()){
        general.next_map();

        while(general.is_in_map()){
            general.walk();
            if(general.is_loop()){
                counter++;

                //DEBUG
                //std::cout << general.get_pos().x << " - " << general.get_pos().y << "\n";

                break;
            }
        }
    }

    //general.print_map();
    std::cout << counter << "\n";

    return 1;
}
