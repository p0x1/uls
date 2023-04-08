//
//  main.c
//  uls
//
//  Created by Vlad on 22.03.2023.
//
#include "../inc/uls.h"

int main(int argc, const char * argv[]) {
    int error = error_handling(argv, argc);
    if(argc == 1){
        default_ls(".");
    }
    else if(argc == 2 && mx_strcmp("-l", argv[1]) == 0){
        only_flag_l("./");
    }
    else if(mx_strcmp("-l", argv[1]) == 0){
        flag_l(argv,argc,error);
    }
    if(argc != 1 && mx_strcmp("-l", argv[1]) != 0){
        ls_with_exact_files(argv, argc,error);
    }
    return 0;
}

