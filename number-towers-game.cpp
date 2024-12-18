#include <iostream>
using namespace std;

const int MAX_NUM_TOWER = 4;
const int MAX_NUM_FLOOR = 4;
const int MAX_ENCOUNTER_LENGTH = 10;

void copy_floor(int to[], const int from[]){
    for (int i=0; i<MAX_NUM_FLOOR; i++){
        to[i] = from[i];
    }
}

int calculate_strength(int strength, const char encounter[MAX_ENCOUNTER_LENGTH]){
    char symbol=encounter[0]; 
    int numberUsed = 0;
    for (int i = 1;encounter[i]!='\0';++i){
        numberUsed=numberUsed*10+(encounter[i]-'0'); 
    }
    switch (symbol){
        case '+':
            strength+=numberUsed;
            break;
        case '-':
            strength-=numberUsed;
            break;
        case '*':
            strength*=numberUsed;
            break;
        case '/':
            if (numberUsed!=0){ 
                strength/=numberUsed;
            }
            break;
        case 'M':
            if (strength>numberUsed){
                strength+=numberUsed; 
            } else {
                strength=-1; 
            }
            break;
    }

    return strength; 
}

int find_path(const char stage[][MAX_NUM_FLOOR][MAX_ENCOUNTER_LENGTH], int num_tower, int current_tower, 
    int num_floor, int explored_floor_count, int explored_floor[],
    int strength, int floor_path[], int stage_path[][MAX_NUM_FLOOR]) {
    
    
    if (current_tower >= num_tower) {
        return strength;
    }


    if (explored_floor_count == num_floor) {
        copy_floor(floor_path, explored_floor);
        return strength;
    }

    int highest_strength = -1;
    int best_floor_path[MAX_NUM_FLOOR];

  
    for (int i = 0; i < num_floor; i++) {
       
        bool is_selected = false;
        for (int j = 0; j < explored_floor_count; j++) {
            if (i == explored_floor[j]) {
                is_selected = true;
                break; 
            }
        }
        if (is_selected) {
            continue; 
        }

        
        int new_strength = calculate_strength(strength, stage[current_tower][i]);
        if (new_strength <= 0) {
            continue; 
        }

        
        explored_floor[explored_floor_count] = i;

       
        int recursion_floor_path[MAX_NUM_FLOOR];
        int recursion_result = find_path(stage, num_tower, current_tower,
                                          num_floor, explored_floor_count + 1,
                                          explored_floor, new_strength,
                                          recursion_floor_path, stage_path);

        
        if (recursion_result > highest_strength) {
            highest_strength = recursion_result;
            copy_floor(best_floor_path, recursion_floor_path);
        }

    }

    
    if (explored_floor_count == 0) {
       
        copy_floor(stage_path[current_tower], best_floor_path);
        
        
        int floor_explored[MAX_NUM_FLOOR];
        int floor_path[MAX_NUM_FLOOR];
        
        find_path(stage, num_tower, current_tower + 1,
                  num_floor, 0, floor_explored,
                  highest_strength, floor_path,
                  stage_path);
    } 


    copy_floor(floor_path, best_floor_path);


    return highest_strength;
}