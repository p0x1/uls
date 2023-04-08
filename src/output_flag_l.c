#include "../inc/uls.h"

void output_flag_l(t_file* files, int count){
    int num_chars_nlink = spacing_for_nlink(files, count);
    int num_chars_size = spacing_for_size(files, count);
    int length_dateTime = 0;
    long half = 15638400;
    time_t now = time(NULL);
    for(int i = 0; i < count; i++){
        if(now - half < files[i].mtime){
            length_dateTime = mx_strlen(get_time(ctime(&files[i].mtime)));
        }
    }
    if(get_totalblocks(files, count) >= 0){
        mx_printstr("total ");
        mx_printint(get_totalblocks(files, count));
        mx_printstr("\n");
    }
    for(int i = 0; i < count; i++){
        mx_printstr(get_chmod(files[i].mode,files[i].fullpath));
       for(int j = 0; j < num_chars_nlink - mx_strlen(mx_itoa(files[i].nlink)); j++){
           mx_printstr(" ");
        }
        mx_printint(files[i].nlink);
        mx_printstr(" ");
         mx_printstr(get_username(files[i].uid));
         mx_printstr("  ");
         mx_printstr(get_group(files[i].gid));
        int length = mx_strlen(mx_itoa(files[i].size));
        for(int j = 0; j < num_chars_size - length; j++){
            mx_printstr(" ");
        }
         mx_printstr(mx_itoa(files[i].size));
         mx_printstr(" ");
         if(now - half > files[i].mtime){
             mx_printstr(get_time_with_year(ctime(&files[i].mtime), length_dateTime));
         }
         else{
            mx_printstr(get_time(ctime(&files[i].mtime)));
            mx_printstr(" ");
         }
         mx_printstr(get_filename(files[i]));
        if(i+1 != count){
            mx_printstr("\n");
        }
    }
    mx_printstr("\n");
    free(files);
}
