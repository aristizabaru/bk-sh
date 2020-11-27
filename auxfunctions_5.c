#include "holberton.h"
/**
 * check_exit_compare - compare argument with string "exit"
 * @arguments: the arguments line.
 * @bytes: resulting bytes of string comparation
 * @offset: resulting offset of string analysis
 * Return: nothing
 */
void check_exit_compare(char *arguments, int *bytes, int *offset)
{
    char *exit = "exit";
    int i = 0;

    for (i = 0; arguments[i]; i++, (*offset)++)
    {
        if (arguments[i] != ' ')
        {
            if (arguments[i] == exit[*bytes])
                (*bytes)++;
            if (arguments[i] == exit[3])
            {
                (*offset)++;
                break;
            }
        }
    }
}

/**
 * check_exit - this function checks for exit arg.
 * @arguments: the arguments line.
 * Return: the status.
 */
int check_exit(char *arguments)
{
    char *result = NULL;
    int i = 0, bytes = 0, status = 0, offset = 0, numFound_control = -1;

    check_exit_compare(arguments, &bytes, &offset);
    if (arguments[offset] != '\n')
    {
        for (i = 0; arguments[i + offset]; i++)
        {
            if (arguments[i + offset] != ' ')
            {
                if ((arguments[i + offset] >= '0' && arguments[i + offset] <= '9') &&
                    numFound_control == -1)
                {
                    bytes++;
                    push_char(&result, arguments[i + offset]);
                    status = _atoi(result);
                    if (arguments[(i + offset) + 1] < '0' ||
                        arguments[(i + offset) + 1] > '9')
                        numFound_control = 0;
                }
                else if (status == 0)
                {
                    bytes++;
                    status = -2;
                    break;
                }
            }
        };
    }
    if (bytes == 4)
        status = -1;
    free(result);
    return (status);
}

/**
 * check_error - checks status of error
 * @error: number to check
 * Description: if error is -1 then print
 * error message and errno description of
 * the error
 *
 * Return: nothing
 */
void check_error(int error)
{
    if (error == -1)
    {
        perror("Error");
    }
}

/**
 * printnum - this function prints a number to stdoutput
 * @a: the number to print
 */
void printnum(int a)
{
    int b;
    char c, d, e;

    if (a >= 10)
    {
        b = a % 10;
        a = a / 10;
        if (a >= 10)
        {
            printnum(a);
            c = b + '0';
            write(STDOUT_FILENO, &c, 1);
        }
        else
        {
            d = a + '0';
            write(STDOUT_FILENO, &d, 1);
            e = b + '0';
            write(STDOUT_FILENO, &e, 1);
        }
    }
    else
    {
        d = a + '0';
        write(STDOUT_FILENO, &d, 1);
    }
}

/**
 * exit_illegal_command - print exit status if exit + number is invalid
 * @av: arguments values
 * @count: iteration counter
 * @arguments: arguments caputure from stdin
 * Return: nothing
 */
void exit_illegal_command(char *av, int count, char *arguments)
{
    int i = 0, offset = 0, bytes = 0;
    char *exit = "exit";
    char *letter = NULL;

    write(STDOUT_FILENO, av, _strlen(av));
    write(STDOUT_FILENO, ": ", 2);
    printnum(count);
    write(STDOUT_FILENO, ": exit: ", 8);
    write(STDOUT_FILENO, "Illegal number: ", 16);

    for (i = 0; arguments[i]; i++, offset++)
    {
        if (arguments[i] != ' ')
        {
            if (arguments[i] == exit[bytes])
                bytes++;
            if (arguments[i] == exit[3])
            {
                offset++;
                break;
            }
        }
    }
    for (i = 0; arguments[i + offset]; i++)
    {
        if (arguments[i + offset] != ' ')
        {
            letter = malloc(2 * sizeof(char));
            letter[0] = arguments[i + offset];
            letter[1] = '\0';
            write(STDOUT_FILENO, letter, 1);
            free(letter);
        }
    }
}
