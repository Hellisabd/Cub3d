#include "cub3D.h"

# define NC "\e[0m"
# define RED "\e[1;31m"
# define GREEN "\e[1;32m"
# define YELLOW "\e[1;33m"
# define ORANGE "\e[1;34m"
# define PURPLE "\e[1;35m"
# define BLUE "\e[1;36m"

void    debug_nbr(char *color, char *msg, long long int content)
{
    if (!msg)
        printf("%s %lld%s\n", color, content, NC);
    else
        printf("%s%s %lld%s\n", color, msg, content, NC);
}

void    debug_str(char *color, char *msg, char *content)
{
    if (!msg)
        printf("%s %s%s\n", color, content, NC);
    else
        printf("%s%s %s%s\n", color, msg, content, NC);
}

void    debug_tab_nbr(char *color, char *msg, long long int *content)
{
    int i;

    i = -1;
    if (!msg)
        while (content[++i])
            printf("%s%s [%d] : %lld%s\n", color, msg, i, content[i], NC);
    else
        while (content[i])
            printf("%s [%d] : %lld%s\n", color, i, content[i], NC);
}

void    debug_tab_str(char *color, char *msg, char **content)
{
    int i;

    i = -1;
    if (!msg)
        while (content[++i])
            printf("%s%s [%d] : %s%s\n", color, msg, i, content[i], NC);
    else
        while (content[i])
            printf("%s [%d] : %s%s\n", color, i, content[i], NC);
}