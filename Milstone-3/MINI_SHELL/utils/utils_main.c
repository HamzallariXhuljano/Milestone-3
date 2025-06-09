/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xhamzall <xhamzall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 18:36:32 by xhamzall          #+#    #+#             */
/*   Updated: 2025/06/08 19:03:15 by xhamzall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	init_shell(void)
{
	char	*username;

	username = getenv("USER");
	printf("\e[2J\e[H\e[1;96m-----------------------------------------");
	printf("\e[1;96m--------------------------\e[0m\n\n");
	printf("\e[91m███╗   ███╗██╗███╗   ██╗██╗");
	printf("███████╗██╗  ██╗███████╗██╗     ██╗     \n");
	printf("████╗ ████║██║████╗  ██║██║██╔════╝");
	printf("██║  ██║██╔════╝██║     ██║     \n");
	printf("██╔████╔██║██║██╔██╗ ██║██║███████╗");
	printf("███████║█████╗  ██║     ██║     \n");
	printf("██║╚██╔╝██║██║██║╚██╗██║██║╚════██║");
	printf("██╔══██║██╔══╝  ██║     ██║     \n");
	printf("██║ ╚═╝ ██║██║██║ ╚████║██║███████║");
	printf("██║  ██║███████╗███████╗███████╗\n");
	printf("╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝╚═╝╚══════╝");
	printf("╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝\e[0m\n\n");
	printf("\e[1;96mMade by: Giuseppe and Xhuljano\e[0m\n\n");
	printf("\e[1;96m-----------------------------------------");
	printf("\e[1;96m--------------------------\e[0m\n");
	printf("\n\e[91mWelcome %s\n\e[0m", username);
}

void	ft_control_c(int sig)
{
	if (sig == SIGINT)
	{
		g_sigint = 130;
		write(STDOUT_FILENO, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	check_signal(int status, t_env *env)
{
	int	sig;

	sig = -1;
	if (status == 256)
	{
		env->exit_code = 127;
		return ;
	}
	if (status == 1 || status == 2)
		return ;
	else if (WIFEXITED(status))
		g_sigint = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		sig = WTERMSIG(status);
		if (sig == SIGQUIT)
			write(2, "Quit (core dumped)\n", 19);
		else if (sig == SIGINT)
			write(2, "\n", 1);
		g_sigint = 128 + sig;
		env->exit_code = g_sigint;
	}
	signal(SIGINT, ft_control_c);
	signal(SIGQUIT, SIG_IGN);
}

char	**ft_copy_env(char **envp)
{
	int		i;
	char	**env_copy;
	int		j;

	j = 0;
	i = 0;
	while (envp[i])
		i++;
	env_copy = ft_calloc(sizeof(char *), (i + 1));
	if (!env_copy)
		return (perror("Error allocating memory for env_copy"), NULL);
	while (j < i)
	{
		env_copy[j] = ft_strdup(envp[j]);
		if (!env_copy[j])
			return (perror("Error allocating memory for env_copy[j]"), NULL);
		j++;
	}
	return (env_copy);
}

void	ft_clean_red2(t_redirect *redirect)
{
	t_redirect	*temp;

	if (!redirect || redirect == NULL)
		return ;
	while (redirect)
	{
		temp = redirect;
		redirect = redirect->next;
		if (!ft_strcmp(temp->operator, "<<") && temp->heredoc_tmpfile)
			free(temp->heredoc_tmpfile);
		free(temp->operator);
		free(temp->filename);
		free(temp);
	}
}
