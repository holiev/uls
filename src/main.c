#include "../libmx/inc/libmx.h"

#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdlib.h>

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

void this_dir(DIR *dir, struct dirent *entry, char *path)
{
    if ((dir = opendir(path)) == NULL)
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
        closedir(dir);
        dir = opendir(path);
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

void more_dir(int num, char **argv)
{
    DIR *dir = NULL;
    struct dirent *entry = NULL;
    bool consist;
    char **directories = NULL;
    char **files = NULL;
    int countDir = 0;
    int countFiles = 0;
    int temp = 0;

    for (int i = 1; i < num; i++)
    {
        if (opendir(argv[i]) != NULL)
            countDir++;
        else
            countFiles++;
    }
    temp = countFiles;

    directories = (char **)malloc(countDir * sizeof(char *));
    files = (char **)malloc(countFiles * sizeof(char *));

    for (int i = 0; i < countDir; i++)
        directories[i] = mx_strnew(25);
    for (int i = 0; i < countFiles; i++)
        files[i] = mx_strnew(25);

    int a = 0;
    int b = 0;
    for (int i = 1; i < num; i++)
    {
        if (opendir(argv[i]) != NULL)
        {
            directories[a] = mx_strdup(argv[i]);
            a++;
        }
        else
        {
            dir = opendir(".");
            while ((entry = readdir(dir)) != NULL)
            {
                if (mx_strcmp(argv[i], entry->d_name) == 0)
                {
                    consist = true;
                    break;
                }
                else
                    consist = false;
            }
            closedir(dir);
            if (!consist)
            {
                mx_printstr("uls: ");
                mx_printstr(argv[i]);
                mx_printstr(": No such file or directory\n");
                countFiles--;
                continue;
            }
            files[b] = mx_strdup(argv[i]);
            b++;
        }
    }
    mx_bubble_sort(directories, countDir);
    mx_bubble_sort(files, countFiles);

    for (int i = 0; i < countFiles; i++)
    {
        mx_printstr(files[i]);
        mx_printchar('\t');
    }
    if (countFiles > 0 && countDir == 0)
        mx_printchar('\n');
    else if (countFiles != 0 && countDir != 0)
        mx_printstr("\n\n");

    for (int i = 0; i < countDir; i++)
    {
        mx_printstr(directories[i]);
        mx_printstr(":\n");
        this_dir(dir, entry, directories[i]);
        if (i != countDir - 1)
            mx_printchar('\n');
    }
    clean_array(directories, countDir);
    clean_array(files, temp);
}

int main(int argc, char *argv[])
{
    DIR *dir = NULL;
    struct dirent *entry = NULL;
    if (argc == 1)
    {
        this_dir(dir, entry, ".");
        exit(EXIT_SUCCESS);
    }
    else
    {
        more_dir(argc, argv);
        exit(EXIT_SUCCESS);
    }
    exit(EXIT_SUCCESS);
}
