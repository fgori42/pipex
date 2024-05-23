/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utilis.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgori <fgori@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 12:14:36 by fgori             #+#    #+#             */
/*   Updated: 2024/02/12 11:07:17 by fgori            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**find_phat(char	**env, t_data *data)
{
	int		i;
	char	**temp;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
		{
			temp = ft_split(&env[i][5], ':');
			if (!temp)
				put_error("split failed", data);
			return (temp);
		}
		i++;
	}
	put_error("missing PATH", data);
	return (0);
}

static char	*make_cmd(char **full, char *cmd)
{
	int		i;
	char	*temp;
	char	*newcmd;

	i = 0;
	while (full[i])
	{
		temp = ft_strjoin(full[i], "/");
		newcmd = ft_strjoin(temp, cmd);
		free(temp);
		if (access(newcmd, F_OK | X_OK) == 0)
		{
			return (newcmd);
		}
		free (newcmd);
		i++;
	}
	return (NULL);
}

void	first_cmd(t_data *data, char *av[], char *env[])
{
	dup2(data->pip[1], 1);
	close (data->pip[0]);
	dup2(data->file, 0);
	close(data->file);
	close(data->pip[1]);
	close(data->outfile);
	data->full_cmd = ft_split(av[2], ' ');
	data->cmd = make_cmd(data->mat_path, data->full_cmd[0]);
	if (!data->cmd)
	{
		put_error("comand don't find", data);
	}
	if (execve(data->cmd, data->full_cmd, env) < 0)
		put_error("ERROR\n execve don't replies", data);
}

void	second_cmd(t_data *data, char *av[], char *env[])
{
	dup2(data->pip[0], 0);
	close (data->pip[1]);
	dup2(data->outfile, 1);
	close(data->outfile);
	close(data->pip[0]);
	close(data->file);
	data->full_cmd2 = ft_split(av[3], ' ');
	data->cmd2 = make_cmd(data->mat_path, data->full_cmd2[0]);
	if (!data->cmd2)
	{
		put_error("comand don't find", data);
	}
	if (execve(data->cmd2, data->full_cmd2, env) < 0)
		put_error("ERROR\n execve don't replies", data);
}
