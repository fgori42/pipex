/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgori <fgori@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 12:03:52 by fgori             #+#    #+#             */
/*   Updated: 2024/02/22 12:11:28 by fgori            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

char	**find_phat(char **env)
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
			{
				return (perror("ERROR\nsplit failed"), NULL);
			}
			return (temp);
		}
		i++;
	}
	return (perror("ERROR\nmissing PATH"), NULL);
	return (0);
}

char	*make_cmd(char **full, char *cmd)
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

int	freemat(char **mat)
{
	int	i;

	i = 0;
	if (!mat)
		return (0);
	while (mat[i] != NULL)
	{
		free(mat[i]);
		mat[i] = NULL;
		i++;
	}
	free(mat);
	return (0);
}

int	free2(char *str)
{
	if (str)
		free(str);
	return (1);
}

int	gnl2(char **line)
{
	char	*buf;
	int		i;
	int		n;
	char	ch;

	buf = (char *)ft_calloc(10000, 1);
	i = 1;
	n = 0;
	ch = 'c';
	while (i > 0 && ch != '\n')
	{
		i = read(0, &ch, 1);
		if (i < 0)
			return (free(buf), 0);
		buf[n] = ch;
		n++;
	}
	*line = ft_strdup(buf);
	if (!line)
		return (free(buf), 0);
	free(buf);
	return (n);
}
