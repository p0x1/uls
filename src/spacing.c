#include "../inc/uls.h"

int spacing_for_nlink(t_file *files, int count){
    int max = mx_strlen(mx_itoa(files[0].nlink)) + 1;
    for(int i = 1; i<count; i++){
        if(max< mx_strlen(mx_itoa(files[i].nlink)) + 1)
            max=mx_strlen(mx_itoa(files[i].nlink)) + 1;
    }
    return max;
}

int spacing_for_size(t_file *files, int count){
    int max = mx_strlen(mx_itoa(files[0].size)) + 2;
    for(int i = 1; i< count; i++){
        if(max< mx_strlen(mx_itoa(files[i].size)) + 2)
            max=mx_strlen(mx_itoa(files[i].size)) + 2;
    }
    return max;
}
