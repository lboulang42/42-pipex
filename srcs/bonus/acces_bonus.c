/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   acces_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboulang <lboulang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 20:58:51 by lboulang          #+#    #+#             */
/*   Updated: 2023/07/10 14:36:07 by lboulang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

/*
Split cmd to get cmd name and command arguments in pipex->cmd_args
Send to funct to check if the cmd is accessible and get the cmd_path from it.
*/
void	ft_get_exec_assets(t_pipex *pipex, char *command)
{
	pipex->cmd_args = ft_split(command, ' ');
	if (!pipex->cmd_args)
		return ;
	pipex->cmd_path = ft_check_acces(pipex->env_path, pipex->cmd_args[0], -1);
}

char	*ft_join_path(char *try_path, char *cmd_name)
{
	char	*tmp_path;
	char	*cmd_path;

	tmp_path = ft_strjoin(try_path, "/");
	if (!tmp_path)
		return (NULL);
	cmd_path = ft_strjoin(tmp_path, cmd_name);
	if (!cmd_path)
		return (free(tmp_path), NULL);
	free(tmp_path);
	return (cmd_path);
}

/*
separate way if cmd is global path / only name / only name without PATH in env
*/
char	*ft_check_acces(char **env_path, char *cmd_name, int i)
{
	char	*cmd_path;

	if (!ft_strncmp(cmd_name, "/", 1))
	{
		cmd_path = ft_strdup(cmd_name);
		if (!access(cmd_path, F_OK | X_OK))
			return (cmd_path);
		return (ft_access_fail(cmd_path, cmd_name), NULL);
	}
	if (!env_path)
	{
		cmd_path = ft_strdup(cmd_name);
		if (!access(cmd_name, F_OK | X_OK))
			return (cmd_path);
		return (ft_access_fail(cmd_path, cmd_name), NULL);
	}
	while (env_path[++i])
	{
		cmd_path = ft_join_path(env_path[i], cmd_name);
		if (!access(cmd_path, F_OK | X_OK))
			return (cmd_path);
		if (env_path[i + 1])
			free(cmd_path);
	}
	return (ft_access_fail(cmd_path, cmd_name), NULL);
}

/*
Send the accurate error message.
*/
void	ft_access_fail(char *cmd_path, char *cmd_name)
{
	if (cmd_path[ft_strlen(cmd_path) - 1] == '/')
	{
		ft_printf("Pipex: %s: %s\n", cmd_path, ERR_NOTDIR);
		free(cmd_path);
		return ;
	}
	if (access(cmd_path, F_OK))
		ft_printf("Pipex: %s: '%s'\n", cmd_name, ERR_CMD);
	else if (access(cmd_path, X_OK))
		ft_printf("Pipex: %s: %s\n", cmd_path, ERR_PERM);
	free(cmd_path);
}

/*
Get env $PATH var in a char ** (every env path in a separate char *)
*/
char	**ft_get_env_path(char **env)
{
	int		i;
	char	**tmp;
	char	**env_path;

	i = -1;
	while (env[++i])
	{
		if (!ft_strncmp("PATH=", env[i], 5))
		{
			tmp = ft_split(env[i], '=');
			if (!tmp)
				return (NULL);
			env_path = ft_split(tmp[1], ':');
			if (!env_path)
				return (ft_free_tab((void **)tmp), NULL);
			return (ft_free_tab((void **)tmp), env_path);
		}
	}
	return (NULL);
}
