#include "../inc/uls.h"


int error_handling(const char** files, int count){
    int result = 0;
    int check = 0;
    if(count != 1){
        if(mx_strchr(files[1], '-') != NULL){
            if(mx_strcmp("-l", files[1]) != 0){
                mx_printerr("uls: invalid option -- ");
                files[1]= mx_replace_substr(files[1], "-", "");
                mx_printerr(files[1]);
                mx_printerr("\n");
                mx_printerr("usage: uls [-l] [file ...]\n");
                exit(-1);
            }
        }
        for(int i = 1; i < count; i++){
            if(opendir(".")== NULL){
                if(errno == EACCES){
                    mx_printerr("uls: ");
                    mx_printerr(".");
                    mx_printerr(" Permission denied\n");
                }
            }
            else{
                check = 1;
            }
            if(opendir(files[i]) == NULL){
                char* temp = mx_strdup(files[i]);
                if(errno == ENOENT && mx_strcmp(temp,"-l") != 0){
                    mx_printerr("uls: ");
                    mx_printerr(files[i]);
                    mx_printerr(": No such file or directory\n");
                    result = 1;
                    files[i] = " ";
                    if(check == 0){
                        check = 2;
                    }
                }
                if(errno == ENOTDIR && mx_strcmp(&temp[mx_strlen(temp)-1],"/") == 0){
                    mx_printerr("uls: ");
                    mx_printerr(files[i]);
                    mx_printerr(": Not a directory\n");
                    result = 1;
                    files[i] = " ";
                    if(check == 0){
                        check = 2;
                    }
                }
                 if(errno == EACCES && mx_strcmp(&temp[mx_strlen(temp)-1],"/") == 0){
                    mx_printerr("uls: ");
                    mx_printerr(".");
                    mx_printerr(" Permission denied\n");
                    result = 1;
                    files[i] = " ";
                    if(check == 0){
                        check = 2;
                    }
                }
                else{
                    check = 1;
                }
            }
        }
    
    }
   
    if(check == 2)
        exit(-1);
    
    return result;
}
