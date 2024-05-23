/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgori <fgori@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 12:10:20 by fgori             #+#    #+#             */
/*   Updated: 2024/02/22 12:06:21 by fgori            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	freestruct(t_data *data)
{
	if (data->cmd)
		free(data->cmd);
	if (data->cmd2)
		free(data->cmd2);
	if (data->full_cmd2)
		freemat(data->full_cmd2);
	if (data->full_cmd)
		freemat(data->full_cmd);
	if (data->mat_path)
		freemat(data->mat_path);
	if (data->pip[0])
		close(data->pip[0]);
	if (data->pip[1])
		close(data->pip[1]);
}

void	put_error(char *str, t_data *data)
{
	freestruct(data);
	perror(str);
	exit (1);
}

void	freemat(char **mat)
{
	int	i;

	i = 0;
	while (mat[i] != NULL)
	{
		free(mat[i]);
		mat[i] = NULL;
		i++;
	}
	free(mat);
}

static void	inizialize(t_data *data)
{
	data->cmd = NULL;
	data->cmd2 = NULL;
	data->full_cmd = NULL;
	data->full_cmd2 = NULL;
	data->mat_path = NULL;
}

int	main(int ac, char *av[], char *env[])
{
	t_data	data;

	if (ac != 5)
		return (perror("ERROR\nuncorrect number of argument"), 1);
	inizialize(&data);
	data.file = open(av[1], O_RDONLY, 0777);
	if (data.file < 0)
		return (perror("ERROR\n FILE NOT FOUND"), 1);
	data.outfile = open(av[ac - 1], O_TRUNC | O_CREAT | O_RDWR, 0777);
	if (data.outfile < 0)
		return (perror("ERROR\n OUTFILE NOT FOUND"), 1 + close(data.file));
	if (pipe(data.pip) < 0 && !(close(data.file) + close(data.outfile)))
		return (perror("ERROR\n PIPE DON'T SET"), 1);
	data.mat_path = find_phat(env, &data);
	data.id = fork();
	if (data.id == 0)
		first_cmd(&data, av, env);
	data.id_2 = fork();
	if (data.id_2 == 0)
		second_cmd(&data, av, env);
	freestruct(&data);
	waitpid(data.id, NULL, 0);
	waitpid(data.id_2, NULL, 0);
	return (0);
}
