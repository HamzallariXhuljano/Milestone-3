/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xhamzall <xhamzall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 16:36:06 by xhamzall          #+#    #+#             */
/*   Updated: 2025/06/08 19:00:28 by xhamzall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <errno.h>
# include <stdarg.h>
# include <stdint.h>
# include <signal.h>
# include <string.h>
# include <limits.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft/libft.h"

extern int	g_sigint;
typedef struct s_redirect
{
	char				*operator;
	char				*filename;
	char				*heredoc_tmpfile;
	struct s_redirect	*next;
}	t_redirect;

typedef struct s_list_1
{
	char				*comand;
	char				*str_after_comand;
	char				**arg;
	int					exit_status;
	struct s_list_1		*next;
}	t_list_1;

typedef struct s_env
{
	char				*input;
	char				**env_copy;
	char				*current_dir;
	char				*prev_dir;
	int					fd_to_write;
	int					fd_to_read;
	int					pipe_fd[2];
	int					saved_stdin;
	int					saved_stdout;
	int					saved_stderr;
	int					exit_code;
	t_redirect			**redirect;
	t_list_1			*word;
}	t_env;

void		ft_free_env2(char **env_copy);
int			ft_is_quote(char c);
int			ft_check_pipe_empty(char *str, t_env *env);
void		ft_free_redirect(t_redirect **redirect);
t_list_1	*ft_clean_comand_to_quote(t_list_1 *comand);
int			ft_cd(char **args, t_env *env);
int			ft_is_inside_a_singole_quotes(char *str, int pos_c);
int			ft_is_inside_double_quotes(char *str, int pos_c);
char		*ft_clean_dollar(char *str, int i,
				int in_single_quotes, int in_double_quotes);
int			ft_safe_fd(char *filename);
void		ft_cat(char *filename, int fd_to_write);
int			ft_index_dollar(char *str);
int			len_dollaro(char *str, int sgl_qts, int dbl_qts, int i);
char		*take_string(char *str, t_env *start);
char		*check_in_env(char **envp, char *str);
void		ft_echo(char **arg);
void		ft_env(char **envp, int fd_to_write);
char		*ft_get_path(char *cmd_name, char **env, int i);
int			ft_exec_all(t_env *start);
int			exec(t_list_1 *comand, char **env, t_env *start);
char		*my_getenv(char *name, char **env);
int			ft_is_valid(char *str);
void		ft_free_tab(char **tab);
void		do_pipe(t_list_1 *cmd, char **env);
int			open_file(char *file, int in_or_out);
void		print_redirect_matrix(t_redirect **redirect);
void		init_shell(void);
void		check_signal(int status, t_env *start);
void		ft_free_env(t_env *start);
void		ft_clean_red2(t_redirect *redirect);
void		ft_pwd(void);
void		ft_control_c(int sig);
int			ft_is_inside_quotes(char *str, int pos_c);
char		*ft_expand(char *str, char *doll_arg, int index_dollar);
int			ft_redirect(char *file_name);
int			ft_redirect_append(char *file_name);
char		**update_env(char **env_cpy, char *new_var);
char		*ft_expand_str(char *str, t_env *start,
				int i, int in_single_quotes);
void		ft_iter_pointer_two(int *a, int *b, int flags);
int			ft_is_space(char c);
int			ft_find_next_pipe(char *str, int start);
char		*ft_first_word(char *str, int start);
char		*ft_create_argoument(char *str, int start);
void		ft_add_node(t_env *start, char *comand, char *str_after_comand);
int			ft_next_word(char *str, int start);
void		ft_second_parse(t_env *start);
void		ft_set_first_node(char *input, int i, t_env *start);
int			ft_find_next_space(char *str, int start);
char		*ft_clean_word(char *comand);
int			find_var(t_env *env, char *name);
int			ft_count_dollar_to_expand(char *str, int i,
				int count, int in_single_quotes);
t_list_1	*ft_clean_comand_to_quote(t_list_1 *comand);
void		print_list(t_env *start);
int			ft_first_parse(t_env *start, char *input);
int			ft_check_number_quote(char *str, int i, int flags_quote,
				t_env *env);
void		ft_check_str_after_comand(t_list_1 *comand);
char		*ft_double_dollar(char *str);
int			ft_count_command(char *str);
char		*ft_expand_dollar_dollar(char *str, const char *replace_str);
int			ft_set_redirect(t_env *start, char *input, int i, int x);
void		update_pwd(t_env *env);
void		update_oldpwd(t_env *env);
char		*home_path(t_env *env);
void		ft_free_matrix(char **matrix);
void		print_export(char **env_cpy, t_env *env);
void		sort_export(char **env_cpy);
char		**dup_mtx(char **mtx);
void		update_pwd(t_env *env);
void		update_oldpwd(t_env *env);
char		*home_path(t_env *env);
void		ft_free_matrix(char **matrix);
char		**dup_mtx(char **mtx);
int			ft_export(t_env *env, t_list_1 *list);
int			update_var(t_env *env, char *name, char *val);
int			add_name_var(t_env **env, char *name, char *val);
char		*creat_name_val(char *name, char *val);
char		*get_value(char	*str);
char		*get_name(char	*str);
void		export_print_errors(char **arg, int *i);
void		helper_export(char **arg, t_env *env, int i);
void		print_export_equal(char **tmp, int *i, int *j);
int			find_var(t_env *env, char *name);
int			check_equal(char *str);
int			add_name(t_env **env, char *name);
int			remove_var(t_env *env, int index);
int			ft_unset(t_env *env, t_list_1 *list);
int			is_valid(char *str);
char		*path_evnp(char **evnp);
char		*make_path(char *dir, char *cmd );
char		**get_path(char **evnp);
char		*get_comand_path(char *cmd, char **path);
char		*find_path(char *cmd, char **envp);
void		free_redirects(t_redirect *redir);
void		free_cmd_lst(t_list_1 *cmd);
void		close_fds(t_env *env);
void		exit_with_error(int error_code, t_env *env);
void		ft_exit(t_list_1 *cmd, t_env *env);
int			valid_exit(char *str);
void		setup_heredoc(const char *delimiter, int p_fd[2]);
void		handle_redirection_error(const char *context, t_env *env,
				int is_child);
char		*ft_set_operator(char *str, int *i, int *flags_dollar);
int			ft_add_to_redirect_list(t_redirect **head, t_redirect **current,
				t_redirect *new_node);
void		iteri_comand(char **comand, int *i, int *j, char **new_comand);
t_redirect	*ft_parse_redirect_at(t_env *data, char *str, int *i, int *flags);
t_redirect	*ft_set_list_redirect(t_env *data, int start, int end, int *flags);
void		ft_set_argv(t_list_1 *word);
char		**ft_copy_env(char **envp);
void		ft_clean_red2(t_redirect *redirect);
void		sigint_handler_heredoc(int sig);
void		ft_signal_handlers2(int sig);
int			handle_redirections_father(t_redirect *redir, t_env *start, int fd);
void		ft_close_saved_fds(t_env *start);
void		ft_close_all(int i);
int			ft_check_is_my_bultin(t_list_1 *cmd, t_env *start);
void		rst_sdfd(int saved_stdin, int saved_stdout, int saved_stderr);
char		*ft_hel_here(int fd, const char *delimiter, t_env *start,
				const char *tmp_template);
char		*here_doc_file(const char *delimiter, t_env *start);
void		cleanup_heredoc_files(t_redirect **redirects);
int			preprocess_all_heredocs(t_redirect **redirects,
				t_env *start, int i);
void		ft_free_forexc(t_env *start, char **env);
int			exec(t_list_1 *cmd, char **env, t_env *start);
int			ft_exec_help(char *path, t_list_1 *cmd, char **env, t_env *start);
int			ft_invalid_fd(t_env *start, t_redirect *redir);
int			exec_2(t_list_1 *cmd, char **env, t_env *start);
int			ft_last_heredoc(t_env *start, t_redirect *redir, int fd,
				char *last_heredoc_tmp);
void		ft_set_saved_fds(t_env *start);
void		ft_close_saved_fs(t_env *start, t_redirect *redir,
				int fd, char *last_heredoc_tmp);
int			ft_check_sec_lis(t_redirect *redir, t_env *start,
				int fd, char *last_heredoc_tmp);
int			ft_check_list_red_mul(int fd, t_redirect *redir,
				t_env *start, char *last_heredoc_tmp);
void		ft_invalid_fd__her(t_env *start, t_redirect *redir);
int			handle_redirections(t_redirect *redir, t_env *start,
				char *last_heredoc_tmp);
int			ft_handler_pa_check_list2(t_env *start, int fd, t_redirect *redir);
int			ft_handler_pa_check_list(t_env *start, int fd, t_redirect *redir);
int			ft_hree(t_env *start, int fd, t_redirect *redir,
				char *last_heredoc_tmp);
int			handle_redirections_father(t_redirect *redir, t_env *start, int fd);
int			ft_is_my(char *str);
int			ft_is_single_cmd(t_env *start);
void		ft_help_mulp_cmd(int p_fd[2], int prev_fd, t_list_1 *cmd);
void		ft_help_mulp_cmd2(t_env *start, int index, t_list_1 *cmd);
void		ft_help_mulp_cmd3(int (*p_fd)[2], int flags, int *prev_fd);
void		ft_is_multiple_cmd(t_env *start, int index, int prev_fd);
int			ft_len_matrix(char **matrix);
// char	**check_allpath(char **allpath);
char		*ft_check_direct_path(char *cmd_name);
int			ft_true_do_it(char *str, int i, t_redirect *new_redirect,
				int **flags);
char		*ft_help_2set(char *str, int i, t_env *data, int flags_dollar);
int			my_mkstemp(char *template);
void		generate_name(char *template, char *chars,
				unsigned int cnter, int len);
void		ft_check_exit_code(t_env *start);
int			handle_redirections_h(t_redirect *redir, t_env *start,
				char **last_heredoc_tmp, int *fd);
int			is_true_3(char *str, int i, int in_single_quotes);

#endif
