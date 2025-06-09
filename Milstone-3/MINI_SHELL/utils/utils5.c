/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xhamzall <xhamzall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 16:22:51 by xhamzall          #+#    #+#             */
/*   Updated: 2025/06/06 17:22:08 by xhamzall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	my_mkstemp(char *template)
{
	char			*chars;
	int				len;
	unsigned int	counter;
	int				fd;

	chars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
	len = (int) ft_strlen(template);
	if (len < 6)
	{
		errno = EINVAL;
		return (-1);
	}
	counter = 0;
	while (counter < 1000000)
	{
		generate_name(template, chars, counter, len);
		fd = open(template, O_RDWR | O_CREAT | O_EXCL, 0600);
		if (fd >= 0)
			return (fd);
		else if (errno != EEXIST)
			return (perror("open"), -1);
		counter++;
	}
	errno = EEXIST;
	return (-1);
}

void	generate_name(char *template, char *chars, unsigned int cnter, int len)
{
	unsigned int	val;
	int				i;

	i = len - 6;
	val = cnter;
	while (i < len)
	{
		template[i] = chars[val % 62];
		val /= 62;
		i++;
	}
}

int	handle_redirections_h(t_redirect *redir, t_env *start,
		char **last_heredoc_tmp, int *fd)
{
	if (redir->heredoc_tmpfile)
	{
		if ((*fd) >= 0)
			close ((*fd));
		(*fd) = open(redir->heredoc_tmpfile, O_RDONLY);
		if ((*fd) < 0)
			return (ft_invalid_fd__her(start, redir), -1);
		if (*last_heredoc_tmp)
			free(*last_heredoc_tmp);
		*last_heredoc_tmp = ft_strdup(redir->heredoc_tmpfile);
	}
	return (0);
}
