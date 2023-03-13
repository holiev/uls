//
//  main.c
//  uls
//
//  Created by Artur Holiev on 13.03.2023.
//
#include "../libmx/inc/libmx.h"

#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdlib.h>
#include <malloc/malloc.h>
#include <sys/types.h>
#include <dirent.h>

void clean_array(char **names, int size)
{
    for (int i = 0; i < size; i++)
    {
        free(names[i]);
    }
    free(names);
}

void this_dir(void)
{
    DIR *dir = NULL;
    struct dirent *entry = NULL;
    if ((dir = opendir(".")) == NULL)
    {
        perror("");
        exit(EXIT_FAILURE);
    }
    else
    {
        int size = 0;
        while ((entry = readdir(dir)) != NULL)
        {
            if (entry->d_name[0] == '.')
                continue;
            size++;
        }
        free(entry);
        closedir(dir);
        dir = opendir(".");
        char **files = (char **)malloc(size * sizeof(char *));
        for (int i = 0; i < size; i++)
            files[i] = mx_strnew(25);
        int k = 0;
        while ((entry = readdir(dir)) != NULL)
        {
            if (entry->d_name[0] == '.')
                continue;
            files[k] = mx_strdup(entry->d_name);
            k++;
        }
        mx_bubble_sort(files, size);
        for (int i = 0; i < size; i++)
        {
            mx_printstr(files[i]);
            mx_printchar('\t');
        }
        mx_printchar('\n');
        clean_array(files, size);
    }
    free(entry);
    closedir(dir);
}

// void more_dir(int num, char *files)
// {
// }

int main(int argc, char *argv[])
{
    if (argc == 1)
        this_dir();

    if (argv[1] == "-l" && argc > 1)
    {
    }
    else if (argc > 1)
    {
    }
    exit(EXIT_SUCCESS);
}
