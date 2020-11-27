#include "holberton.h"

/**
 * free_arguments - this functions free memory allocated.
 * @arg_array: the array of arguments.
 * @arguments: the line of arguments.
 */
void free_arguments(char ***arg_array, char **arguments)
{

    int i = 0;

    /* free array of arguments */
    for (; *(*arg_array + i); i++)
    {
        free(*(*arg_array + i));
        *(*arg_array + i) = NULL;
    }
    free(*arg_array);
    *arg_array = NULL;
    /* free initial buffer allocated with get line */
    if (*arguments != NULL)
    {
        free(*arguments);
        *arguments = NULL;
    }
}

/**
 * create_memstrings - create memory allocation for new array elements
 * @arguments: string literal
 * @new_array: array of pointers
 * @wrdc: number of words in the string
 * Description: the array must have enough space for the strings
 *
 * Return: nothing
 */
void create_memstrings(char **arguments, char **new_array, int wrdc)
{
    int i = 0, bytes = 0;
    int current_wrdc = wrdc;

    while (*(*arguments + i))
    {
        if (*(*arguments + i) != ' ' && *(*arguments + i) != '\n')
            bytes += 1;
        if (*(*arguments + i) == ' ' || *(*arguments + i) == '\n' ||
            *(*arguments + (i + 1)) == '\0')
        {
            if (bytes > 0)
            {
                new_array[wrdc - current_wrdc] = malloc(sizeof(char) * (bytes + 1));
                new_array[wrdc - current_wrdc][bytes] = '\0';
                if (new_array[wrdc - current_wrdc] == NULL)
                {
                    perror("Error");
                    exit(1);
                    /* Free previous allocated memory if fails*/
                }
                bytes = 0;
                current_wrdc--;
            }
        }
        i++;
    }
}

/**
 * copybytes_memstrings - copy bytes from string to array
 * @arguments: string literal
 * @new_array: array of pointers
 * @wrdc: number of words in the string
 * Description: the array must have enough space for the strings
 * to be copied
 *
 * Return: nothing
 */
void copybytes_memstrings(char **arguments, char **new_array, int wrdc)
{
    int i = 0, bytes = 0;
    int current_wrdc = wrdc;

    while (*(*arguments + i))
    {
        if (*(*arguments + i) != ' ' && *(*arguments + i) != '\n')
        {
            new_array[wrdc - current_wrdc][bytes] = *(*arguments + i);
            bytes++;
        }
        if (*(*arguments + i) == ' ' || *(*arguments + i) == '\n' ||
            *(*arguments + (i + 1)) == '\0')
        {
            if (bytes > 0)
            {
                bytes = 0;
                current_wrdc--;
            }
        }
        i++;
    }
}

/**
 * splitter - split a string into an array of strings.
 * @arguments: string to split.
 * @arg_array: empty array of arguments
 * @wrdc: number of words in the string.
 *
 * Return: nothing
 */
void splitter(char **arguments, char ***arg_array, int wrdc)
{
    char **new_array = NULL;

    new_array = malloc(sizeof(new_array) * (wrdc + 1));
    new_array[wrdc] = NULL;
    if (new_array == NULL)
    {
        perror("Error");
        exit(1);
    }
    /* allocate memory for strings */
    create_memstrings(&(*arguments), &(*new_array), wrdc);
    /* copy bytes to new memory */
    copybytes_memstrings(&(*arguments), &(*new_array), wrdc);
    /* asign new array to arg_array */
    *arg_array = new_array;
}

/**
 * get_arguments - convert strings literals to an array
 * @arguments: string literal
 * @arg_array: empty array of arguments
 *
 * Return: nothing
 */
int get_arguments(char **arguments, char ***arg_array)
{
    int wrdc = 0;
    int buffer_status = -1;

    wrdc = wrdcounter(*arguments);
    if (wrdc != 0)
    {
        splitter(&(*arguments), &(*arg_array), wrdc);
        buffer_status = 0;
    }
    return (buffer_status);
}
