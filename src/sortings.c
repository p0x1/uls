#include "../inc/uls.h"

void sorting_for_l(t_file *files, int count){
    for(int i = 1; i < count; i++){
        for(int j = 0; j < count - i; j++){
            if(mx_strcmp(files[j].name, files[j+1].name) > 0){
                t_file temp = files[j];
                files[j] = files[j+1];
                files[j+1] = temp;
            }
        }
    }
}

void sorting(char **names, int count){
    for(int i = 1; i < count; i++){
        for(int j = 0; j < count - i; j++){
            if(mx_strcmp(names[j], names[j+1]) > 0){
                char* temp = names[j];
                names[j] = names[j+1];
                names[j+1] = temp;
            }
        }
    }
}
