#include "general.h"

#define PART 2

int main(){
    int counter = 0;
    General general;
    general.print_map();
    general.print_position();

    if(PART == 1){
        //order of whiles importent (clockwise turning)
        for(;;){
            while(!general.is_up_blocked()){
                if(general.is_out_of_bounds()){
                    goto end;
                }
                general.go_up();
            }
            while(!general.is_right_blocked()){
                if(general.is_out_of_bounds()){
                    goto end;
                }
                general.go_right();
            }
            while(!general.is_down_blocked()){
                if(general.is_out_of_bounds()){
                    goto end;
                }
                general.go_down();
            }
            while(!general.is_left_blocked()){
                if(general.is_out_of_bounds()){
                    goto end;
                }
                general.go_left();
            }
        }
    }else if(PART == 2){
        while(general.next_map()){

            for(int i = 0; i< 1000; i++){
                while(!general.is_up_blocked()){
                    if(general.is_out_of_bounds()){
                        goto outer;
                    }
                    general.go_up();
                }
                while(!general.is_right_blocked()){
                    if(general.is_out_of_bounds()){
                        goto outer;
                    }
                    general.go_right();
                }
                while(!general.is_down_blocked()){
                    if(general.is_out_of_bounds()){
                        goto outer;
                    }
                    general.go_down();
                }
                while(!general.is_left_blocked()){
                    if(general.is_out_of_bounds()){
                        goto outer;
                    }
                    general.go_left();
                }
            }
            counter++;
        outer:;
        }
    }

end:

    //general.print_map();
    //std::cout << general.count_marks() << "\n";
    std::cout << counter << "\n";

    return 1;
}
