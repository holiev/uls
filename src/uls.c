/////////////////////////////////////////
/////////////////////////////////////////
/////////////////////////////////////////
/////////created by Artur Holiev/////////
////////create by Oleksandr Dzunyik//////
/////////////////////////////////////////
/////////////////////////////////////////
/////////////////////////////////////////

#include "../libmx/inc/libmx.h"
#include "../inc/uls.h"

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
