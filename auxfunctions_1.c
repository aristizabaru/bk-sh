#include "holberton.h"

/**
 * _strcat - this function concatenates two strings.
 * @str1: first string.
 * @str2: second string.
 * Return: the concatened string.
*/
char *_strcat(char *str1, char *str2)
{
    int a, b;

    for (a = 0; str1[a]; a++)
    {
    }
    for (b = 0; str2[b]; b++)
    {
        str1[a] = str2[b];
        a++;
    }
    str1[a] = '\0';
    return (str1);
}

/**
 * _strcpy - this function copies a string to other string.
 * @dest: the destination string.
 * @src: the source string.
 */

void _strcpy(char *dest, char *src)
{
    int a;

    for (a = 0; src[a] != '\0'; a++)
    {
        dest[a] = src[a];
    }
    dest[a] = '\0';
}

/**
 * _strlen - this function calculates the lenght of a string.
 * @str: the string.
 * Return: the lenght.
 */

int _strlen(char *str)
{
    int a;

    for (a = 0; str[a]; a++)
        ;
    return (a);
}

/**
 * wrdcounter - this function counts the words in a string.
 * @arguments: this is the string.
 * Description: the count of word stops when \n is found
 *
 * Return: number of words.
 */
int wrdcounter(char *arguments)
{
    int i, count = 0;

    for (i = 0; arguments[i] != '\0'; i++)
    {
        if ((arguments[i] != ' ' && arguments[i] != '\n') &&
            (arguments[i + 1] == ' ' || arguments[i + 1] == '\0' ||
             arguments[i + 1] == '\n'))
            count++;
    }
    return (count);
}

/**
 * _atoi -  convert a string to an integer.
 * @s: string to convert
 *
 * Return: the first number in the string
 */
int _atoi(char *s)
{
    unsigned int res = 0;
    int resNeg = 0;
    int signo = 1;

    while (*s)
    {
        /* compruebo si hay - o + y multiplica */
        if (*s == '-')
            signo *= -1;
        /* imprime números */
        if (*s >= '0' && *s <= '9')
        {
            /* Multiplica x 10 para agregar decena */
            res = res * 10 + *s - '0';
            /* salgo del loop cuando pasa número */
            if (s[1] < '0' || s[1] > '9')
                break;
        }
        s++;
    }
    /*Según el signo cambio de un unsiged a signed int*/
    if (signo < 0)
        return (resNeg = res * signo);
    else
        return (res * signo);
}
