#include "cub3D.h"

void    debug_nbr(char *color, char *msg, long long int content)
{
    if (!msg)
        fprintf(stderr, "%s %lld%s\n", color, content, NC);
    else
        fprintf(stderr, "%s%s %lld%s\n", color, msg, content, NC);
}

void    debug_char(char *color, char *msg, char content)
{
    if (!msg)
        fprintf(stderr, "%s %c%s\n", color, content, NC);
    else
        fprintf(stderr, "%s%s %c%s\n", color, msg, content, NC);
}

void    debug_str(char *color, char *msg, char *content)
{
    if (!msg)
        fprintf(stderr, "%s %s%s\n", color, content, NC);
    else
        fprintf(stderr, "%s%s %s%s\n", color, msg, content, NC);
}

void    debug_tab_nbr(char *color, char *msg, long long int *content)
{
    int i;

    i = -1;
    if (!msg)
        while (content[++i])
            fprintf(stderr, "%s %s [%d] : %lld%s\n", color, msg, i, content[i], NC);
    else
        while (content[i])
            fprintf(stderr, "%s [%d] : %lld%s\n", color, i, content[i], NC);
}

void    debug_tab_str(char *color, char *msg, char **content)
{
    int i;

    i = -1;
    if (!msg)
        while (content[++i])
            fprintf(stderr, "%s%s [%d] : %s%s\n", color, msg, i, content[i], NC);
    else
        while (content[i])
            fprintf(stderr, "%s [%d] : %s%s\n", color, i, content[i], NC);
}