#include "../inc/uls.h"

void space(int n){
    for(int i = 0; i <= n; i++){
        mx_printstr(" ");
    }
}
void default_ls(char* path){
    char** exact_files = NULL;
    if(mx_strchr(path, ',') != NULL){
        exact_files = mx_strsplit(path, ',');
        DIR *dir;
        struct dirent *entry;
        int count = 0;
        int max_length = 0;
        char** arr_names = NULL;
        if(opendir(path) == NULL){
            while(*path){
                char temp = *path;
                if(mx_strcmp(&temp, ",") == 0){
                    count++;
                }
                path++;
            }
            arr_names = malloc(sizeof(char *)* count);
            for(int i = 0; i < count; i++){
                arr_names[i] = exact_files[i];
            }
            sorting(arr_names, count);
        }
        else{
            dir = opendir(path);
            char* hidden = mx_strnew(1);
            while((entry = readdir(dir)) != NULL){
                hidden = mx_strncpy(hidden, entry->d_name, 1);
                if(mx_strcmp(hidden, ".") != 0){
                    count++;
                }
            }
            closedir(dir);
            arr_names = malloc(sizeof(char *)* count);
            dir = opendir(path);
            int i = 0;
            while((entry = readdir(dir)) != NULL){
                hidden = mx_strncpy(hidden, entry->d_name, 1);
                if(mx_strcmp(hidden, ".") != 0){
                    arr_names[i] = entry->d_name;
                    i++;
                }
            }
            mx_strdel(&hidden);
            sorting(arr_names, count);
            
        }
        if(isatty(1)){
            max_length = get_max_length(arr_names, count);
            int rows = 0;
            int cols = 0;
            struct winsize win;
            ioctl(STDOUT_FILENO, TIOCGWINSZ, &win);
            int extra_spaces = 0;
            int kef = 1;
            while(true){
                if(kef*8 > max_length){
                    extra_spaces = kef * 8 - max_length;
                    break;
                }
                kef++;
            }
            cols = win.ws_col / (max_length + extra_spaces);
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                if(count % cols){
                rows = count / cols +1;
            }
            else{
                rows = count / cols;
            }
            for(int i = 0; i < rows; i++){
                for(int j = 0; i + j < count; j+= rows){
                    if(mx_strlen(arr_names[i+j]) < max_length+extra_spaces){
                        mx_printstr(arr_names[i+j]);
                    }
                    else{
                        mx_printstr(arr_names[i+j]);
                    
                    }
                    space(kef*8 - mx_strlen(arr_names[i+j]-1));
                }
                mx_printstr("\n");
            }
        }
      else{
        for(int j = 0; j < count; j++){
                mx_printstr(arr_names[j]);
                mx_printstr("\n");
            }
        }
        free(arr_names);
    }
    else{
        DIR *dir;
           struct dirent *entry;
        int count = 0;
        int max_length = 0;
            dir = opendir(path);
        char* hidden = mx_strnew(1);
        while ( (entry = readdir(dir)) != NULL) {
            hidden = mx_strncpy(hidden, entry->d_name, 1);
            if(mx_strcmp(hidden, ".") != 0){
                count++;
            }
        }
         closedir(dir);
         char** arr_names = malloc(sizeof(char *)* count);
         dir=opendir(path);
         int i=0;
        while ( (entry = readdir(dir)) != NULL) {
            hidden = mx_strncpy(hidden, entry->d_name, 1);
            if(mx_strcmp(hidden, ".") != 0){
                    arr_names[i] = entry->d_name;
                    i++;
                 }
             }
         closedir(dir);
         sorting(arr_names, count);
        if(isatty(1)){
            max_length = get_max_length(arr_names, count);
            int rows = 0;
            int cols = 0;
            struct winsize win;
            ioctl(STDOUT_FILENO, TIOCGWINSZ, &win);
            int extra_spaces = 0;
            int kef = 1;
            while(true){
                if(kef*8 > max_length){
                    extra_spaces = kef * 8 - max_length;
                    break;
                }
                kef++;
            }
            cols = win.ws_col / (max_length + extra_spaces);
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                            if(count % cols){
                rows = count / cols +1;
            }
            else{
                rows = count / cols;
            }
            for(int i = 0; i < rows; i++){
                for(int j = 0; i + j < count; j+= rows){
                    if(mx_strlen(arr_names[i+j]) < max_length+extra_spaces){
                        mx_printstr(arr_names[i+j]);
                    }
                    else{
                        mx_printstr(arr_names[i+j]);
                    
                    }
                    space(kef*8 - mx_strlen(arr_names[i+j]-1));
                }
                mx_printstr("\n");
            }
        }
      else{
        for(int j = 0; j < count; j++){
                mx_printstr(arr_names[j]);
                mx_printstr("\n");
            }
        }
        free(arr_names);
        mx_strdel(&hidden);
        free(exact_files);
    }
   
}
