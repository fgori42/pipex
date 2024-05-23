/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgori <fgori@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 12:10:30 by fgori             #+#    #+#             */
/*   Updated: 2024/02/12 10:53:30 by fgori            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdio.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include "libft.h"

typedef struct s_data
{
	char	**full_cmd;
	char	**full_cmd2;
	char	**mat_path;
	char	*cmd;
	char	*cmd2;

	int		pip[2];
	int		file;
	int		outfile;
	int		id;
	int		id_2;
}	t_data;

char	**find_phat(char	**env, t_data *data);
void	put_error(char *str, t_data *data);
void	first_cmd(t_data *data, char *av[], char *env[]);
void	second_cmd(t_data *data, char *av[], char *env[]);
void	freemat(char **mat);
void	freestruct(t_data *data);

#endif
