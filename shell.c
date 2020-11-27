#include "holberton.h"

/**
 * main - emulates a shell
 * @ac: arguments count
 * @av: argouments values
 * @environ: enviroment
 * Return: 0 if success, -1 on error.
 */
int main(int ac, char **av, char **environ)
{
    int characters = 0, exit = 0, glcount = 0;
    char *promt_sign = "$ ", *arguments = NULL, **arg_array = NULL;
    size_t arguments_size = 0;

    (void)ac;
    if (isatty(STDIN_FILENO))
    {
        /* interactive mode */
        signal(SIGINT, sigint_handler);
        shell_loop(&characters, &glcount, promt_sign, &arguments, &arguments_size,
                   &exit, &av, &arg_array, environ);
        if (exit == 0 || characters == EOF)
            check_error(write(STDOUT_FILENO, "\n", 1));
        if (exit == -1)
            exit = 0;
    }
    else
    {
        /* non interactive mode */
        arguments = malloc(2048 * sizeof(char));
        characters = read(STDIN_FILENO, arguments, 2048);
        create_nonInterac_arg_array(wrdcounter(arguments), &arguments, &arg_array);
        run_command(&arg_array, glcount, av, environ);
        free_arguments(&arg_array, &arguments);
    }
    return (exit);
}
