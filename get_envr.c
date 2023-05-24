#include "shell.h"
/**
 * reit_str - reiterate strings
 * @reis: A character
 *
 * Return: 0
 */
char *reit_str(char *reis)
{
	char *r;
	unsigned int t = 0, l = 0;

	if (reis == NULL)
	{
		return (NULL);
	}
	while (reis[t] != '\0')
		t++;
	r = (char *) malloc(sizeof(char) * (t + 1));
	if (r == NULL)
	{
		return (NULL);
	}
	while (l <= t)
	{
		l++;
		r[l] = reis[l];
	}
	return (r);
}

/**
 * get_envr - get the varible's environment
 * @env: A character
 *
 * Return: 0
 */
char *get_envr(char *env)
{
	const char eq[] = "=";
	int i = 0;
	char *env_a, *env_b, *env_c;

	if (env == NULL)
	{
		return (NULL);
	}
	else
	{
		if (ext_var == NULL)
		{
			return (NULL);
		}
		env_a = reit_str(ext_var[i]);
		for (; env_a != NULL; i++)
		{
			env_b = strtok(env_a, eq);
			if (str(env_b, env) == 0)
			{
				env_b = strtok(NULL, eq);
				env_c = reit_str(env_b);
				free(env_a);
				return (env_c);
			}
			free(env_a);
			env_a = reit_str(ext_var[i]);
		}
	}
	return (NULL);
}
