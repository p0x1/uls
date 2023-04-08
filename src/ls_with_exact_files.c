#include "../inc/uls.h"


void ls_with_exact_files(const char** files, int count, int error){
    int num_files = 0;
    int num_direct = 0;
    for(int i = 1; i < count; i++){
        if(opendir(files[i])==NULL && mx_strcmp(files[i], " ") != 0){
            num_files++;
        }
        if(opendir(files[i]) != NULL){
            num_direct++;
        }
    }
  
    char** arr_files = malloc(sizeof(char *)*(num_files+1));
    char** arr_directories = malloc(sizeof(char *)*num_direct);
    int k = 0, j =0;
    for(int i = 1; i < count; i++){
        if(opendir(files[i])==NULL && mx_strcmp(files[i], " ") != 0){
            arr_files[k] = mx_strdup(files[i]);
            k++;
        }
        else if(opendir(files[i])!=NULL){
            arr_directories[j] = mx_strdup(files[i]);
            j++;
        }
    }
    if(num_files != 0){
        sorting(arr_files, num_files);
    }
    if(num_direct != 0){
        sorting(arr_directories, num_direct);
    }

    int a = 0;
    char* res = NULL;
    if(num_files != 0){
        res =mx_strdup(arr_files[0]);
        res = mx_strjoin(res, ",");
        a = 1;
    }
    for(int i = 1; i< num_files; i++){
        if(mx_strcmp(arr_files[i], " ") != 0){
            res = mx_strjoin(res, arr_files[i]);
            res = mx_strjoin(res,",");
            a = 1;
        }
       
    }
    if(num_files != 0){
        default_ls(res);
    }
    mx_strdel(&res);
    if(a==1 && num_direct != 0){
        mx_printstr("\n");

    }
    for(int i = 0; i < num_direct; i++){
        if(opendir(arr_directories[i])!=NULL && count > 1 && (a == 1 || num_direct > 1)){
            mx_printstr(arr_directories[i]);
            mx_printstr(":\n");
        }
        else if(error == 1){
            mx_printstr(arr_directories[i]);
            mx_printstr(":\n");
        }
        if(opendir(arr_directories[i])!=NULL ){
            default_ls(arr_directories[i]);
            if(i+1 != num_direct ){
                mx_printstr("\n");
            }
        }
    }
    free(arr_files);
    free(arr_directories);
}
