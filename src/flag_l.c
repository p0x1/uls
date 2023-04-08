#include "../inc/uls.h"

void flag_l(const char** path, int num, int error){
    char* non_direct = NULL;
    char* directories = NULL;
    char** arr_directories = NULL;
    int num_directories = 0;
    for(int i = 2; i < num; i++){
        if(opendir(path[i]) == NULL && i==2 && mx_strcmp(path[i], " ") != 0){
            non_direct = mx_strdup(path[i]);
            non_direct = mx_strjoin(non_direct, ",");
        }
        else if(opendir(path[i]) == NULL && mx_strcmp(path[i], " ") != 0){
            non_direct = mx_strjoin(non_direct, path[i]);
            non_direct = mx_strjoin(non_direct, ",");
        }
        if(opendir(path[i]) != NULL && i == 2){
            directories = mx_strdup(path[i]);
            directories = mx_strjoin(directories, ",");
            num_directories++;
        }
        else if(opendir(path[i]) != NULL){
            directories = mx_strjoin(directories, path[i]);
            directories = mx_strjoin(directories, ",");
            num_directories++;
        }
    }
    if(num_directories != 0){
        arr_directories = mx_strsplit(directories, ',');
        sorting(arr_directories, num_directories);
    }
    if(non_direct != NULL){
        only_flag_l(non_direct);
    }
    for(int i = 0; i < num_directories; i++){
        if(non_direct != NULL){
                mx_printstr("\n");
        }
        if( num != 3 || error == 1){
            mx_printstr(arr_directories[i]);
            mx_printstr(":\n");
        }
        DIR *dir;
        struct dirent *entry;
        dir = opendir(arr_directories[i]);
        int count = 0;
        char* hidden = mx_strnew(1);
        while ( (entry = readdir(dir)) != NULL) {
            hidden = mx_strncpy(hidden, entry->d_name, 1);
            if(mx_strcmp(hidden, ".") != 0){
                count++;
            }
        }
        if(count == 0){
            mx_printstr("total 0\n");
        }
        else{
            closedir(dir);
            char* temp = mx_strdup(arr_directories[i]);
            int length = mx_strlen(arr_directories[i]);
            int check_slash = 0;
            if(mx_strcmp(&temp[length - 1], "/") != 0){
                check_slash = 1;
            }
            t_file *files = malloc(sizeof(t_file)*count);
            int k = 0;
            char* fullpath;
            dir = opendir(arr_directories[i]);
            while ( (entry = readdir(dir)) != NULL) {
                hidden = mx_strncpy(hidden, entry->d_name, 1);
                if(mx_strcmp(hidden, ".") != 0){
                if(check_slash == 1){
                    fullpath = mx_strjoin(arr_directories[i], "/");
                    fullpath = mx_strjoin(fullpath, entry->d_name);
                }
                else{
                    fullpath = mx_strjoin(arr_directories[i],entry->d_name);
                    }
                struct stat *st = malloc(sizeof(struct stat));
                lstat(fullpath, st);
                set_file(entry->d_name, fullpath, st, &files[k]);
                k++;
                }
            }
            mx_strdel(&temp);
            sorting_for_l(files, count);
            output_flag_l(files, count);
            if(i+1 != num_directories){
                mx_printstr("\n");
            }
            mx_strdel(&fullpath);
            closedir(dir);
            }
    }
           
       

    if(directories != NULL)
        mx_strdel(&directories);
    if(arr_directories != NULL)
        mx_strdel(arr_directories);
    if(non_direct != NULL)
        mx_strdel(&non_direct);
}
