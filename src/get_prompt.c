#include "minishell.h"

static char	*get_path_part(char *cwd)
{
	char	*home;
	char	*path_part;

	home = getenv("HOME");
	if (home && ft_strncmp(cwd, home, ft_strlen(home)) == 0)
	{
		path_part = ft_strjoin("~", cwd + ft_strlen(home));
		if (!path_part)
			return (NULL);
	}
	else
	{
		path_part = ft_strdup(cwd);
		if (!path_part)
			return (NULL);
	}
	return (path_part);
}

static char	*build_prompt(char *user, char *path)
{
	char	*tmp;
	char	*prompt;
	char	*final;

	tmp = ft_strjoin(user, ":");
	if (!tmp)
		return (NULL);
	prompt = ft_strjoin(tmp, path);
	free(tmp);
	if (!prompt)
		return (NULL);
	final = ft_strjoin(prompt, "$ ");
	free(prompt);
	return (final);
}

char	*get_prompt(void)
{
	char	cwd[PATH_MAX];
	char	*user;
	char	*path;
	char	*prompt;

	if (getcwd(cwd, sizeof(cwd)) == NULL)
		return (ft_strdup("minishell$ "));
	path = get_path_part(cwd);
	if (!path)
		return (ft_strdup("minishell$ "));
	user = getenv("USER");
	if (!user)
		user = "user";
	prompt = build_prompt(user, path);
	free(path);
	if (!prompt)
		return (ft_strdup("minishell$ "));
	return (prompt);
}
