#include "../inc/uls.h"

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
        char *fullPath = mx_strjoin(path, "/");
        for (int i = 0; i < size; i++)
        {
            struct stat filestat;
            stat(mx_strjoin(fullPath, files[i]), &filestat);
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
