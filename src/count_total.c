#include "../inc/uls.h"

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
        char *fullPath = mx_strjoin(path, "/");
        for (int i = 0; i < size; i++)
        {
            struct stat filestat;
            stat(mx_strjoin(fullPath, files[i]), &filestat);
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
