#include "../inc/uls.h"



void only_flag_l(char* path){
    char** exact_files = NULL;
    int num_files = 0;
    DIR *dir;
    struct dirent *entry;
    char* hidden = mx_strnew(1);
    char* fullpath;
    t_file *files = NULL;
    if(mx_strchr(path, ',') != NULL){
        exact_files = mx_strsplit(path, ',');
        while(*path){
            char temp = *path;
            if(temp == ','){
                num_files++;
            }
            path++;
        }
    }
    files = malloc(sizeof(t_file)*(num_files+1));
    for(int i = 0; i < num_files; i++){
        char* temp_str = mx_strdup(exact_files[i]);
        if(temp_str[0] == '/'){
            struct stat *st = malloc(sizeof(struct stat));
            lstat(exact_files[i], st);
            set_file(exact_files[i], exact_files[i], st, &files[i]);
            exact_files[i] = " ";
            files[i].blocks = -1;
        }
        else if(mx_strcmp(path, "./") != 0){
            int last_slash = 0;
            for(int k = 0; k < mx_strlen(exact_files[i]); k++){
                if(temp_str[k] == '/'){
                    last_slash = k+1;
                }
            }
            char* new_str = mx_strnew(last_slash);
            new_str = mx_strncpy(new_str, exact_files[i], last_slash);
            char* name = mx_strnew(mx_strlen(exact_files[i])-last_slash);
            int idx = 0;
            for(int k = last_slash; k < mx_strlen(exact_files[i]);k++){
                name[idx] = temp_str[k];
                idx++;
            }
            dir = opendir(mx_strjoin("./", new_str));
            while ( (entry = readdir(dir)) != NULL) {
                hidden = mx_strncpy(hidden, entry->d_name, 1);
                if(mx_strcmp(hidden,".") != 0 ){
                   if(mx_strcmp(exact_files[i], " ") != 0 && mx_strcmp(entry->d_name, name) == 0){
                       fullpath = mx_strjoin("./",exact_files[i]);
                       struct stat *st = malloc(sizeof(struct stat));
                       lstat(fullpath, st);
                       set_file(exact_files[i], fullpath, st, &files[i]);
                       files[i].blocks = -100;
                   }
                }
            }
            closedir(dir);
            mx_strdel(&name);
            mx_strdel(&new_str);
            mx_strdel(&temp_str);
            mx_strdel(&fullpath);
        }
    }
    if(mx_strcmp(path, "./")==0){
        dir = opendir(path);
        while((entry = readdir(dir)) != NULL){
            hidden = mx_strncpy(hidden, entry->d_name, 1);
            if(mx_strcmp(hidden,".") != 0 ){
                num_files++;
            }
        }
        closedir(dir);
        files = malloc(sizeof(t_file)*(num_files+1));
        dir = opendir(path);
        int i = 0;
        while((entry = readdir(dir)) != NULL){
            hidden = mx_strncpy(hidden, entry->d_name, 1);
            if(mx_strcmp(hidden,".") != 0){
                fullpath = mx_strjoin("./",entry->d_name);
                struct stat *st = malloc(sizeof(struct stat));
                lstat(fullpath, st);
                set_file(entry->d_name, fullpath, st, &files[i]);
                i++;
            }
        }
        closedir(dir);
    }
    sorting_for_l(files, num_files);
    output_flag_l(files, num_files);
    mx_strdel(&hidden);
}
