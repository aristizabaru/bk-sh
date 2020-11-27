#include "holberton.h"

/**
 * run_command - this function executes commands in child process.
 * @arg_array: the array of strings.
 * @glcount: count of the getline cycles.
 * @av: array of arguments of the shell.
 * @environ: enviroment
 */

void run_command(char ***arg_array, int glcount, char **av, char **environ)
{
    int pid = 0;
    int wstatus; /* store status return signal */
    int file_status = 0;

    if (stringcomp((*arg_array)[0], "env") == 1)
        envprint(environ);
    else
    {
        file_status = check_file((*arg_array)[0]);
        if (file_status != 0)
        {
            if (file_status == -2)
            {
                notfoundfunc(*arg_array, glcount, av);
                return;
            }
            if (find_path(arg_array, environ) == -1)
            {
                notfoundfunc(*arg_array, glcount, av);
                return;
            }
        }
        pid = fork();
        if (pid == -1)
            check_error(pid);
        if (pid != 0)
        {
            wait(&wstatus);
            if (WIFEXITED(wstatus))
                WEXITSTATUS(wstatus);
        }
        if (pid == 0)
            execve((*arg_array)[0], *arg_array, environ);
    }
}

/**
 * find_path - this functions find the path.
 * @arg_array: this is the command.
 * @environ: environ
 * Return: 0 on succes, -1 on failure.
 */
int find_path(char ***arg_array, char **environ)
{
    char **paths = NULL;
    int i = 0;
    struct stat st;
    int exit_code = 0;

    if (stat((*arg_array)[0], &st) != 0)
    {

        for (i = 0; environ[i]; i++)
        {
            if (environ[i][0] == 'P' && environ[i][3] == 'H')
                create_paths(environ[i], &paths);
        }
        /* Test paths con arg_array[0] */
        if (compare_paths(&paths, arg_array) == -1)
            exit_code = -1;
        for (i = 0; paths[i]; i++)
        {
            free(paths[i]);
            paths[i] = NULL;
        }
        free(paths);
        paths = NULL;
    }
    return (exit_code);
}

/**
 * create_paths - allocate memory for n number of paths in PATH
 * @the_path: null terminated string with PATH
 * @paths: pointer with allocate memory to store PATH paths
 * Return: nothing
 */
void create_paths(char *the_path, char ***paths)
{
    int offset_path = 5;
    int paths_count = 1;
    int i = 0;

    for (; the_path[i]; i++)
    {
        if (the_path[i] == ':')
            paths_count += 1;
    }
    *paths = malloc((paths_count + 1) * sizeof(char *));
    (*paths)[paths_count] = NULL;
    recursion_fill_path(the_path, paths, offset_path, 0);
}

/**
 * recursion_fill_path - fill array with ENVIROMENT PATH
 * @the_path: null terminated string with PATH
 * @paths: pointer with allocate memory to store PATH paths
 * @offset_path: offset of PATH=, it's always 5
 * @current_paths_count: current path to fill paths
 * Return: nothing
 */
void recursion_fill_path(char *the_path, char ***paths,
                         int offset_path, int current_paths_count)
{
    int i = 0;
    int letters_count = 0;
    int letters_count_offset = 0;
    int j = 0;

    /* BASE CASE */
    if (the_path[i + offset_path] == '\0')
        return;
    for (; the_path[i + offset_path]; i++, letters_count++)
    {
        if (the_path[i + offset_path] == ':' ||
            the_path[(i + offset_path) + 1] == '\0')
        {
            if (the_path[(i + offset_path) + 1] == '\0')
                (*paths)[current_paths_count] = malloc(sizeof(char) * (letters_count + 2));
            else
                (*paths)[current_paths_count] = malloc(sizeof(char) * (letters_count + 1));
            letters_count_offset = letters_count;
            for (; letters_count > 0; letters_count--, j++)
                (*paths)[current_paths_count][j] =
                    the_path[(i + offset_path) - letters_count];
            if (the_path[(i + offset_path) + 1] == '\0')
            {
                (*paths)[current_paths_count][j] =
                    the_path[(i + offset_path) - letters_count];
                (*paths)[current_paths_count][j + 1] = '\0';
            }
            else
                (*paths)[current_paths_count][j] = '\0';
            current_paths_count += 1;
            offset_path += letters_count_offset + 1;
            /* RECURSION CALL */
            recursion_fill_path(the_path, paths, offset_path, current_paths_count);
            break;
        }
    }
}

/**
 * compare_paths - test given command with every environ path.
 * @paths: enviroment PATH
 * @arg_array: command given by user
 * Return: 0 on succes, -1 on error.
 */
int compare_paths(char ***paths, char ***arg_array)
{
    char *test_path = NULL;
    int size_arg = 0;
    int size_path = 0;
    int i = 0;
    struct stat st;
    char *separator = "/";

    for (i = 0; (*paths)[i]; i++)
    {
        size_arg = _strlen(*(arg_array)[0]);
        size_path = _strlen((*paths)[i]);
        test_path = malloc((size_path + size_arg + 2) * sizeof(char));
        if (test_path == NULL)
        {
            perror("Error");
            return (-1);
        }
        _strcpy(test_path, (*paths)[i]);
        _strcat(test_path, separator);
        _strcat(test_path, *(arg_array)[0]);
        if (stat(test_path, &st) == 0)
        {
            free(*(arg_array)[0]);
            *(arg_array)[0] = malloc((_strlen(test_path) + 1) * sizeof(char));
            if (*(arg_array)[0] == NULL)
            {
                perror("Error");
                return (-1);
            }
            _strcpy(*(arg_array)[0], test_path);
            free(test_path);
            return (0);
        }
        free(test_path);
    }

    return (-1);
}
