#include "../inc/uls.h"

char* get_username(uid_t uid){
    struct passwd* user = getpwuid(uid);
   return user->pw_name;
}

char* get_filename(t_file file){
    ssize_t bytes;
    char link[1024];
    if(S_ISLNK(file.mode)){
        char* res = mx_strjoin(file.name, " -> ");
        bytes = readlink(file.fullpath, link, sizeof(link) - 1);
        link[bytes] = '\0';
        res = mx_strjoin(res, link);
        return res;
      }
    char* res = mx_strdup(file.name);
    return res;
}
char *get_group(gid_t gid){
    struct group *g = malloc(sizeof(struct group));
    g=NULL;
    g=getgrgid(gid);
    return g->gr_name;
}

int get_max_length(char** files, int count){
    int res =0;
    for(int i = 0; i < count; i++){
        if(res < mx_strlen(files[i])){
            res = mx_strlen( files[i]);
        }
    }
    return res;
}

char* get_chmod(unsigned short mode, char* filename){
    char* str = mx_strnew(11);
    str[0] = S_ISBLK(mode) ? 'b' : \
           S_ISCHR(mode) ? 'c' : \
           S_ISDIR(mode) ? 'd' : \
           S_ISSOCK(mode) ? 's' : \
           S_ISFIFO(mode) ? 'p' : \
           S_ISLNK(mode) ? 'l' : '-';
    str[1] = (S_IRUSR & mode) ? 'r' : '-';
    str[2] = (S_IWUSR & mode) ? 'w' : '-';
    str[3] = (S_IXUSR & mode) ? 'x' : '-';
    str[4] = (S_IRGRP & mode) ? 'r' : '-';
    str[5] = (S_IWGRP & mode) ? 'w' : '-';
    str[6] = (S_IXGRP & mode) ? 'x' : '-';
    str[7] = (S_IROTH & mode) ? 'r' : '-';
    str[8] = (S_IWOTH & mode) ? 'w' : '-';
    str[9] = (S_ISTXT & mode) ? 't' : \
        (S_IXOTH & mode) ? 'x' : '-';
    acl_t acl = acl_get_file(filename, ACL_TYPE_EXTENDED);
    ssize_t xattr = listxattr(filename,NULL, 0, XATTR_NOFOLLOW);
    if(xattr > 0){
        str[10] = '@';
    }
    else if(acl != NULL){
        str[10] = '+';
    }
    else
        str[10] = ' ';
    
    return str;
}

char* get_time(char* time){
    char** arr = mx_strsplit(time, ' ');
    if(mx_strlen(arr[2])==2){
        arr[1] = mx_strjoin(arr[1], " ");
    }
    else if(mx_strlen(arr[2])==1){
        arr[1]=mx_strjoin(arr[1],"  ");
    }
    char *date = mx_strjoin(arr[1], arr[2]);
    char** arr_time = mx_strsplit(arr[3], ':');
    arr_time[0] = mx_strjoin(arr_time[0], ":");
    char* exact_time = mx_strjoin(arr_time[0], arr_time[1]);
    date = mx_strjoin(date, " ");
    char *dateTime = mx_strjoin(date, exact_time);
    mx_strdel(arr);
    mx_strdel(&date);
    mx_strdel(&exact_time);
    mx_strdel(arr_time);
    return dateTime;
}

char* get_time_with_year(char* time, int length_dateTime){
    char** arr = mx_strsplit(time, ' ');
    if(mx_strlen(arr[2])==2){
        arr[1] = mx_strjoin(arr[1], " ");
    }
    else if(mx_strlen(arr[2])==1){
        arr[1]=mx_strjoin(arr[1],"  ");
    }
    char *date = mx_strjoin(arr[1], arr[2]);
    if(length_dateTime != 0){
        date = mx_strjoin(date, "  ");
    }
    else{
        date = mx_strjoin(date, " ");
    }
    char *dateYear = mx_strjoin(date, arr[4]);
    mx_strdel(arr);
    mx_strdel(&date);
    char *res = mx_replace_substr(dateYear, "\n", " ");
    return res;
}

int get_totalblocks(t_file *files, int count){
    int result = 0;
    for(int i = 0; i < count; i++){
        result+=files[i].blocks;
    }
    return result;
}

void set_file(char* name, char* fullpath, struct stat* st, t_file *file){
    file->name=mx_strdup(name);
    file->fullpath = mx_strdup(fullpath);
    file->mode = st->st_mode;
    file->size = st->st_size;
    file->uid = st->st_uid;
    file->gid = st->st_gid;
    file->blocks = st->st_blocks;
    file->dev = st->st_dev;
    file->mtime = st->st_mtime;
    file->nlink = st->st_nlink;
}
