#pragma once

#include "../libmx/inc/libmx.h"

#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdlib.h>

#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>

void clean_array(char **names, int size);
int check_empty(DIR *dir, struct dirent *entry, char *path);
void this_dir(DIR *dir, struct dirent *entry, char *path);
void more_dir(int num, char **argv);
bool flag(char **argv);
void count_total(DIR *dir, struct dirent *entry, char *path);
void show_permission(struct stat filestat);
void l_flag_this_dir(DIR *dir, struct dirent *entry, char *path);
void l_flag_more_dir(int num, char **argv);
