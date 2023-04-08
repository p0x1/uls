//
//  uls.h
//  uls
//
//  Created by Vlad on 22.03.2023.
//

#ifndef uls_h
#define uls_h

#include "../libmx/inc/libmx.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <pwd.h>
#include <grp.h>
#include <sys/acl.h>
#include <sys/xattr.h>
#include <time.h>
#include <sys/ttycom.h>
#include <sys/ioctl.h>
#include <errno.h>

typedef struct s_file{
    dev_t         dev;
    mode_t        mode;
    nlink_t       nlink;
    uid_t         uid;
    gid_t         gid;
    off_t         size;
    blkcnt_t      blocks;
    time_t        mtime;
    char* fullpath;
    char* name;
}t_file;

void default_ls(char* path);
void flag_l(const char** path, int count, int error);
char* get_username(uid_t uid);
char *get_group(gid_t gid);
char* get_chmod(unsigned short mode, char* filename);
char* get_time(char* time);
int get_totalblocks(t_file *files, int count);
void set_file(char* name, char* fullpath, struct stat* st, t_file *file);
void output_flag_l(t_file* files, int count);
void sorting_for_l(t_file *files, int count);
int spacing_for_nlink(t_file *files, int count);
int spacing_for_size(t_file *files, int count);
void sorting(char **names, int count);
void ls_with_exact_files(const char** files, int count, int error);
char* get_time_with_year(char* time, int length_dateTime);
int error_handling(const char** files, int count);
void only_flag_l(char* path);
void set_file(char* name, char* fullpath, struct stat* st, t_file *file);
char* get_filename(t_file file);
int get_max_length(char** files, int count);
#endif /* uls_h */
