/////////////////////////////////////////
/////////////////////////////////////////
/////////////////////////////////////////
/////////created by Artur Holiev/////////
////////create by Oleksandr Dzunyik//////
/////////////////////////////////////////
/////////////////////////////////////////
/////////////////////////////////////////

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

void clean_array(char **names, int size)
{
    for (int i = 0; i < size; i++)
    {
        free(names[i]);
    }
    free(names);
}

int check_empty(DIR *dir, struct dirent *entry, char *path)
{
    if ((dir = opendir(path)) == NULL)
    {
        perror("");
        return 1;
    }
    else
    {
        int size = 0;
        while ((entry = readdir(dir)) != NULL)
        {
            size++;
        }
        if (size == 2)
            return 0;
        else
            return 1;
    }
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
            if (mx_get_char_index(argv[i], '/') != -1)
            {
                char **name = mx_strsplit(argv[i], '/');

                dir = opendir(name[0]);
                while ((entry = readdir(dir)) != NULL)
                {
                    if (mx_strcmp(name[1], entry->d_name) == 0)
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
        if (check_empty(dir, entry, directories[i]) == 0)
        {
            mx_printstr(directories[i]);
            mx_printstr(":\t# empty directory\n");
            if (i != countDir - 1)
                mx_printchar('\n');
            continue;
        }
        if (countDir == 1 && temp == 0)
        {
            this_dir(dir, entry, directories[i]);
            break;
        }
        if (countDir == 1 && temp > 0)
        {
            mx_printstr(directories[i]);
            mx_printstr(":\n");
            this_dir(dir, entry, directories[i]);
            break;
        }
        mx_printstr(directories[i]);
        mx_printstr(":\n");
        this_dir(dir, entry, directories[i]);
        if (i != countDir - 1)
            mx_printchar('\n');
    }
    clean_array(directories, countDir);
    clean_array(files, temp);
}

bool flag(char **argv)
{
    if (mx_strcmp("-l", argv[1]) == 0)
    {
        return true;
    }
    else
        return false;
}

void count_total(DIR *dir, struct dirent *entry, char *path)
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

        int total = 0;
        for (int i = 0; i < size; i++)
        {
            struct stat filestat;
            stat(files[i], &filestat);
            total += filestat.st_blocks;
        }
        clean_array(files, size);
        mx_printstr("total ");
        mx_printint(total); // total / 2
        mx_printchar('\n');
    }
    free(entry);
    closedir(dir);
}

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

void l_flag_this_dir(DIR *dir, struct dirent *entry, char *path)
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

        count_total(dir, entry, path);

        for (int i = 0; i < size; i++)
        {
            struct stat filestat;
            stat(files[i], &filestat);
            char *temp = ctime(&filestat.st_ctime);
            if (temp[mx_strlen(temp) - 1] == '\n')
                temp[mx_strlen(temp) - 1] = '\0';

            char **arr = mx_strsplit(temp, ' ');
            struct passwd *pw = getpwuid(filestat.st_uid);
            struct group *gr = getgrgid(filestat.st_gid);

            show_permission(filestat);
            mx_printchar(' ');
            mx_printint(filestat.st_nlink);
            mx_printchar(' ');
            mx_printstr(pw->pw_name);
            mx_printchar(' ');
            mx_printstr(gr->gr_name);
            mx_printchar(' ');
            mx_printint(filestat.st_size);
            mx_printchar(' ');
            mx_printstr(arr[1]);
            mx_printchar(' ');
            mx_printstr(arr[2]);
            mx_printchar(' ');
            int j = 0;
            for (int i = 0;; i++)
            {
                if (arr[3][i] == ':')
                    j++;
                if (j == 2)
                    break;
                mx_printchar(arr[3][i]);
            }
            mx_printchar(' ');
            mx_printstr(files[i]);
            mx_printchar('\n');
        }

        clean_array(files, size);
    }

    free(entry);
    closedir(dir);
}

void l_flag_more_dir(int num, char **argv)
{
    DIR *dir = NULL;
    struct dirent *entry = NULL;
    bool consist;
    char **directories = NULL;
    char **files = NULL;
    int countDir = 0;
    int countFiles = 0;
    int temp = 0;

    for (int i = 2; i < num; i++)
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
    int c = 0;
    for (int i = 2; i < num; i++)
    {
        if (opendir(argv[i]) != NULL)
        {
            directories[a] = mx_strdup(argv[i]);
            a++;
        }
        else
        {
            if (mx_get_char_index(argv[i], '/') != -1)
            {
                char **name = mx_strsplit(argv[i], '/');

                dir = opendir(name[0]);
                while ((entry = readdir(dir)) != NULL)
                {
                    if (mx_strcmp(name[1], entry->d_name) == 0)
                    {
                        consist = true;
                        break;
                    }
                    else
                        consist = false;
                }
                closedir(dir);
                if (mx_strcmp(argv[i], "-l") == 0 && b == 0)
                {
                    countFiles--;
                    c++;
                    continue;
                }
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
                if (mx_strcmp(argv[i], "-l") == 0 && b == 0)
                {
                    countFiles--;
                    c++;
                    continue;
                }
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
    }
    mx_bubble_sort(directories, countDir);
    mx_bubble_sort(files, countFiles);

    if (countDir == 0)
    {
        if (c == temp)
        {
            l_flag_this_dir(dir, entry, ".");
            exit(EXIT_SUCCESS);
        }
    }

    for (int i = 0; i < countFiles; i++)
    {
        struct stat filestat;
        stat(files[i], &filestat);
        char *temp = ctime(&filestat.st_ctime);
        if (temp[mx_strlen(temp) - 1] == '\n')
            temp[mx_strlen(temp) - 1] = '\0';
        char **arr = mx_strsplit(temp, ' ');
        struct passwd *pw = getpwuid(filestat.st_uid);
        struct group *gr = getgrgid(filestat.st_gid);

        show_permission(filestat);
        mx_printchar(' ');
        mx_printint(filestat.st_nlink);
        mx_printchar(' ');
        mx_printstr(pw->pw_name);
        mx_printchar(' ');
        mx_printstr(gr->gr_name);
        mx_printchar(' ');
        mx_printint(filestat.st_size);
        mx_printchar(' ');
        mx_printstr(arr[1]);
        mx_printchar(' ');
        mx_printstr(arr[2]);
        mx_printchar(' ');
        int j = 0;
        for (int i = 0;; i++)
        {
            if (arr[3][i] == ':')
            {
                j++;
            }
            if (j == 2)
            {
                break;
            }
            mx_printchar(arr[3][i]);
        }
        mx_printchar(' ');
        mx_printstr(files[i]);
        mx_printchar('\n');
    }

    if (countFiles != 0 && countDir != 0)
        mx_printchar('\n');

    for (int i = 0; i < countDir; i++)
    {
        if (check_empty(dir, entry, directories[i]) == 0)
        {
            mx_printstr(directories[i]);
            mx_printstr(":\t# empty directory\n");
            if (i != countDir - 1)
                mx_printchar('\n');
            continue;
        }
        if (countDir == 1 && temp == 0)
        {
            l_flag_this_dir(dir, entry, directories[i]);
            break;
        }
        if (countDir == 1 && temp > 0)
        {
            mx_printstr(directories[i]);
            mx_printstr(":\n");
            l_flag_this_dir(dir, entry, directories[i]);
            break;
        }
        mx_printstr(directories[i]);
        mx_printstr(":\n");
        l_flag_this_dir(dir, entry, directories[i]);

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
    if (argc > 1)
    {
        if (argv[1][0] == '-')
        {
            if (flag(argv))
            {
                if (argc >= 3)
                {
                    l_flag_more_dir(argc, argv);
                }
                else
                {
                    l_flag_this_dir(dir, entry, ".");
                }

                exit(EXIT_SUCCESS);
            }
            else
            {
                mx_printstr("uls: illegal option -- ");
                char **phrase = mx_strsplit(argv[1], '-');
                mx_printstr(phrase[0]);
                mx_printchar('\n');
                mx_printstr("usage: uls [-l] [file ...]\n");
                exit(EXIT_FAILURE);
            }
        }
        else
        {
            more_dir(argc, argv);
            exit(EXIT_SUCCESS);
        }
    }
    exit(EXIT_SUCCESS);
}
