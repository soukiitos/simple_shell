#include "shell.h"

/**
 * is_cmd - determines if a file is an executable command
 * @info: the info struct
 * @path: path to the file
 *
 * Return: 1 if true, 0 otherwise
 */
int is_cmd(info_t *info, char *path)
{
    struct stat st;

    (void)info;
    if (!path || stat(path, &st))
        return 0;

    if (st.st_mode & S_IFREG)
    {
        return 1;
    }
    return 0;
}

/**
 * dup_chars - duplicates characters
 * @pathstr: the PATH string
 * @start: starting index
 * @stop: stopping index
 *
 * Return: pointer to new buffer
 */
char *dup_chars(char *pathstr, int start, int stop)
{
    static char buf[1024];
    int i = 0, k = 0;

    for (k = 0, i = start; i < stop; i++)
        if (pathstr[i] != ':')
            buf[k++] = pathstr[i];
    buf[k] = 0;
    return buf;
}

/**
 * find_path - finds this cmd in the PATH string
 * @info: the info struct
 * @pathstr: the PATH string
 * @cmd: the cmd to find
 *
 * Return: full path of cmd if found or NULL
 */
char *find_path(info_t *info, char *pathstr, char *cmd)
{
    int i = 0, curr_pos = 0;
    char *path;

    if (!pathstr)
        return NULL;
    if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
    {
        if (is_cmd(info, cmd))
            return cmd;
    }
    while (1)
    {
        if (!pathstr[i] || pathstr[i] == ':')
        {
            path = dup_chars(pathstr, curr_pos, i);
            if (!*path)
                _strcat(path, cmd);
            else
            {
                _strcat(path, "/");
                _strcat(path, cmd);
            }
            if (is_cmd(info, path))
                return path;
            if (!pathstr[i])
                break;
            curr_pos = i;
        }
        i++;
    }
    return NULL;
}

/**
 * hsh - main shell loop
 * @info: the parameter & return info struct
 * @av: the argument vector from main()
 *
 * Return: 0 on success, 1 on error, or error code
 */
int hsh(info_t *info, char **av)
{
    ssize_t r = 0;
    int builtin_ret = 0;

    while (r != -1 && builtin_ret != -2)
    {
        clear_info(info);
        if (interactive(info))
            _puts("$ ");
        _eputchar(BUF_FLUSH);
        r = get_input(info);
        if (r != -1)
        {
            set_info(info, av);
            builtin_ret = find_builtin(info);
            if (builtin_ret == -1)
                find_cmd(info);
        }
        else if (interactive(info))
            _putchar('\n');
        free_info(info, 0);
    }
    write_history(info);
    free_info(info, 1);
    if (!interactive(info) && info->status)
        exit(info->status);
    if (builtin_ret == -2)
    {
        if (info->err_num == -1)
            exit(info->status);
        exit(info->err_num);
    }
    return builtin_ret;
}

/**
 * find_builtin - finds a builtin command
 * @info: the parameter & return info struct
 *
 * Return: -1 if builtin not found,
 *  0 if builtin executed successfully,
 *  1 if builtin found but not successful,
 *  2 if builtin signals exit()
 */
int find_builtin(info_t *info)
{
    int i, built_in_ret = -1;
    builtin_table builtintbl[] = {
        {"exit", _myexit},
        {"env", _myenv},
        {"help", _myhelp},
        {"history", _myhistory},
        {"setenv", _mysetenv},
        {"unsetenv", _myunsetenv},
        {"cd", _mycd},
        {"alias", _myalias},
        {NULL, NULL}
    };

    for (i = 0; builtintbl[i].type; i++)
        if (_strcmp(info->argv[0], builtintbl[i].type) == 0)
        {
            info->line_count++;
            built_in_ret = builtintbl[i].func(info);
            break;
        }
    return built_in_ret;
}

/**
 * find_cmd - finds a command in PATH
 * @info: the parameter & return info struct
 *
 * Return: void
 */
void find_cmd(info_t *info)
{
    char *path = NULL;
    int i, k;

    info->path = info->argv[0];
    if (info->linecount_flag == 1)
    {
        info->line_count++;
        info->linecount_flag = 0;
    }
    for (i = 0, k = 0; info->arg[i]; i++)
        if (!is_delim(info->arg[i], " \t\n"))
            k++;
    if (!k)
        return;

    path = find_path(info, _getenv(info, "PATH="), info->argv[0]);
    if (path)
    {
        info->path = path;
        fork_cmd(info);
    }
    else
    {
        if ((interactive(info) || _getenv(info, "PATH=")
                    || info->argv[0][0] == '/') && is_cmd(info, info->argv[0]))
            fork_cmd(info);
        else if (*(info->arg) != '\n')
        {
            info->status = 127;
            print_error(info, "not found\n");
        }
    }
}

/**
 * fork_cmd - forks an exec thread to run cmd
 * @info: the parameter & return info struct
 *
 * Return: void
 */
void fork_cmd(info_t *info)
{
    pid_t child_pid;

    child_pid = fork();
    if (child_pid == -1)
    {
        /* TODO: PUT ERROR FUNCTION */
        perror("Error:");
        return;
    }
    if (child_pid == 0)
    {
        if (execve(info->path, info->argv, get_environ(info)) == -1)
        {
            free_info(info, 1);
            if (errno == EACCES)
                exit(126);
            exit(1);
        }
        /* TODO: PUT ERROR FUNCTION */
    }
    else
    {
        wait(&(info->status));
        if (WIFEXITED(info->status))
        {
            info->status = WEXITSTATUS(info->status);
            if (info->status == 126)
                print_error(info, "Permission denied\n");
        }
    }
}
