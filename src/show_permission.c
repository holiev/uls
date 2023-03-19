#include "../inc/uls.h"

void show_permission(struct stat filestat)
{
    mx_printstr((S_ISDIR(filestat.st_mode)) ? "d" : "-");
    mx_printstr((filestat.st_mode & S_IRUSR) ? "r" : "-");
    mx_printstr((filestat.st_mode & S_IWUSR) ? "w" : "-");
    mx_printstr((filestat.st_mode & S_IXUSR) ? "x" : "-");
    mx_printstr((filestat.st_mode & S_IRGRP) ? "r" : "-");
    mx_printstr((filestat.st_mode & S_IWGRP) ? "w" : "-");
    mx_printstr((filestat.st_mode & S_IXGRP) ? "x" : "-");
    mx_printstr((filestat.st_mode & S_IROTH) ? "r" : "-");
    mx_printstr((filestat.st_mode & S_IWOTH) ? "w" : "-");
    mx_printstr((filestat.st_mode & S_IXOTH) ? "x" : "-");
}
