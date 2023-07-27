/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asouchet <asouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 11:21:40 by lcamilo-          #+#    #+#             */
/*   Updated: 2023/06/08 15:41:31 by asouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <fcntl.h>
# include <errno.h>
# include <string.h>
# include <unistd.h>
# include <stdbool.h>
# include <sys/termios.h>
# include <stdlib.h>
# include <signal.h>
# include <limits.h>
# include <readline/history.h>
# include <sys/ioctl.h>
# include "libft.h"

int	g_error_num;

typedef struct s_cmd
{
	char			*cmd;
	struct s_cmd	*next;
	struct s_cmd	*prev;
}	t_cmd;

typedef struct t_redir
{
	char			*file;
	int				cases;
	char			*here_doc;
	struct t_redir	*next;
	struct t_redir	*prev;
}	t_redir;

typedef struct s_error {
	int				global;
	int				error;
}	t_error;

typedef struct s_fd {
	int				tmp[2];
	int				fd[2];
}	t_fd;

typedef struct s_file {
	int	output;
	int	input;
	int	fd[2];
}	t_file;

typedef struct s_variable{
	char				*name;
	char				*value;
	struct s_variable	*next;
	struct s_variable	*prev;
}	t_variable;

typedef struct s_exec
{
	char			**cmd_args;
	t_redir			*redir;
	struct s_exec	*next;
	struct s_exec	*prev;
}	t_exec;

typedef struct s_shell
{
	char			*read;
	t_variable		*env;
	t_cmd			*cmd;
	t_exec			*exec;
	t_file			*fd;
	t_error			*error;
	int				level;
	int				*pid;
	char			**ft_sett_env;
}	t_shell;

//////////////////////////////MAIN.C////////////////////////////////////////////
void		parsing(t_shell *shell);
void		init_shell(t_shell *shell, char **env);

////////////////////////////////////////////////////////////////////////////////
///////////////////////////////Free/////////////////////////////////////////////
//////////////////////////////Folder////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

//////////////////////////////FREE.C////////////////////////////////////////////
void		free_env(t_shell *shell);
void		free_cmd(t_shell *shell);
void		free_exec(t_shell *shell);

////////////////////////////////////////////////////////////////////////////////
//////////////////////////////Builtin///////////////////////////////////////////
//////////////////////////////Folder////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
/////////////////////////////CD_UTILS.C/////////////////////////////////////////
char		*ft_new_path(t_shell *shell, char *new_path, char *value);
char		*stock_pwd(char *old_pwd);
void		cd_error(char *new_path);

///////////////////////////////CD.C/////////////////////////////////////////////
void		update_env_value(t_shell *shell, char *name, char *value);
void		cd(t_shell *shell, char **cmd);
char		*get_path(t_shell *shell, char *var_name);

/////////////////////////////ECHO.C/////////////////////////////////////////////
void		echo(char **args);

/////////////////////////////EXIT.C/////////////////////////////////////////////
void		ft_exit(t_shell *shell, char **args);

//////////////////////////////ENV.C/////////////////////////////////////////////
void		env(t_shell *shell);

////////////////////////////EXPORT.C////////////////////////////////////////////
void		ft_export(t_shell *shell, char **args);
int			degeu(char *str);

////////////////////////////EXPORT_UTILS.C//////////////////////////////////////
int			ft_is_alphanum_(char c);
int			check_non_authorized_names(char *str, int *i);
void		bubblesort(t_variable *head);
void		swap(t_variable *a, t_variable *b);
void		printlist(t_variable *node);

//////////////////////////////PWD.C/////////////////////////////////////////////
void		pwd(t_shell *shell);

////////////////////////////UNSET.C/////////////////////////////////////////////
void		unset(char **args, t_variable **env_ptr);
void		free_node(t_variable **env, t_variable **head);
void		free_inside_node(t_variable *env);

////////////////////////////////////////////////////////////////////////////////
/////////////////////////////Execution//////////////////////////////////////////
//////////////////////////////Folder////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

//////////////////////////////EXECUTION.C///////////////////////////////////////
void		minishell_fork(t_shell *shell, t_exec *exec, t_fd *fd);
void		multiple_cmd(t_shell *shell, t_exec *exec, t_fd *fd);
void		last_cmd_in_file(t_shell *shell, t_exec *exec, t_fd *fd);
void		execution(t_shell *shell);

//////////////////////////////DUP_CASE.C////////////////////////////////////////
void		last_dup_case(t_shell *shell, t_fd *fd);
void		dup_case(t_shell *shell, t_fd *fd);

//////////////////////////////REDIR.C///////////////////////////////////////////
void		land_here_doc(t_shell *shell, char *heredoc);
void		redir_new_file(char *file, t_shell *shell, int cases);
void		redir_file(char *file, t_shell *shell);
void		parse_redir(t_shell *shell, t_redir *redir);
void		parse_opening(t_shell *shell, t_redir *redir);

//////////////////////////////REDIR_2.C/////////////////////////////////////////
void		t_redir_exec(t_shell *shell, t_exec *exec);
void		sh_level_update(t_variable *env);
char		*join_env(char *name, char *value);

//////////////////////////////IMPROVED_FT.C/////////////////////////////////////
int			improved_dup2(int fildes, int fildes2, t_shell *shell);
int			improved_pipe(int fd[2], t_shell *shell);
pid_t		improved_fork(t_shell *shell);
void		_close(int fd);
int			is_redir(t_exec *exec);

//////////////////////////////BUILTIN.C/////////////////////////////////////////
int			builtin_in_fork(t_shell *shell, char *cmd, t_exec *tmp);
int			builtin_out_fork(t_shell *shell, char *cmd, t_exec *tmp);

//////////////////////////////EXECUTION_UTILS.C/////////////////////////////////
void		one_cmd(t_shell *shell, t_exec *tmp, t_fd *fd);
int			ft_lst_len_exec(t_exec *lst);
char		*ft_get_path(char *cmd, t_shell *shell);
void		inside_last_fork(t_shell *shell, t_exec *exec,
				t_fd *fd, char *path);

//////////////////////////////EXEC_SETUP.C//////////////////////////////////////
void		declare_var(t_shell *shell, t_fd *fd, t_file *file, t_error *error);
void		middle_execution(t_shell *shell, t_exec *tmp, t_fd *fd);
int			cmd_nb(t_exec *lst);
int			ft_env_len(t_variable *lst);
char		**ft_sett(t_variable *env);

///////////////////////////////ERROR.C//////////////////////////////////////////
void		cmd_not_found(char *cmd);
void		parse_error(char *cmd);
void		minishell_wait(int exec_len);

////////////////////////////////////////////////////////////////////////////////
//////////////////////////////Utils/////////////////////////////////////////////
//////////////////////////////Folder////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

////////////////////////////ENV_UTILS.C/////////////////////////////////////////
void		add_to_env(char **args, t_shell *shell);
void		env_add_back(t_variable **env, t_variable *new);
t_variable	*create_env(char *name, char *value);

////////////////////////////////SIG.C///////////////////////////////////////////
void		rl_replace_line(const char *text, int clear_undo);
void		run_signals(int sig);
void		restore_prompt(int sig);

//////////////////////////////GET_ENV.C/////////////////////////////////////////
t_variable	*init_env(char **env);

//////////////////////////////UTILS_LST.C///////////////////////////////////////
void		lst_show(t_cmd *lst);
int			lst_len(t_cmd *lst);
void		lst_add_front(t_cmd **lst, t_cmd *new);
void		lst_add_back(t_cmd **lst, t_cmd *new);
t_cmd		*lst_create(char *str);

//////////////////////////////UTILS_LST2.C//////////////////////////////////////
void		printf_list(t_cmd *lst);
void		free_lst(t_shell *shell);
size_t		len_cmd(t_cmd *tmp, char c);
t_cmd		*ft_pop(t_cmd *lst, t_shell *shell);

////////////////////////////////UTILS.C/////////////////////////////////////////
int			is_token(char c);
int			count_args(t_cmd *tmp);
void		ft_print_struct(t_shell *shell);
int			check_quotes(t_shell *shell);
int			check_specific_quotes(t_shell *shell, char c, char quotes);

/////////////////////////////EXEC_UTILS.C///////////////////////////////////////
void		exec_add_back(t_exec **exec, t_exec *new);
t_exec		*exec_create(char **args, t_redir *redir);

/////////////////////////////REDIR_UTILS.C//////////////////////////////////////
t_redir		*redir_create(char *file, int cases, char *hd);
void		redir_add_back(t_redir **redir, t_redir *new);

////////////////////////////////////////////////////////////////////////////////
/////////////////////////////Parsing////////////////////////////////////////////
//////////////////////////////Folder////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

/////////////////////////////CREATE_CMD.C///////////////////////////////////////
void		create_cmd(t_shell *shell);

///////////////////////////CREATE_REDIR.C///////////////////////////////////////
t_redir		*create_redir(t_cmd	*cmd);
t_redir		*redirection(t_redir *redir, t_cmd *cmd);
t_cmd		*zebi_redir(t_redir **redir, t_cmd *tmp);
t_cmd		*basic_redir(t_redir **redir, t_cmd *tmp);
///////////////////////////////DOLLARS.C////////////////////////////////////////
void		parse_dollars(t_shell *shell);
char		*extract_value(t_shell *shell, char *cmd, int i);
char		*get_env_value(t_shell *shell, char *str);

///////////////////////////////GET_CMD.C////////////////////////////////////////
void		get_cmd(t_shell *shell);
t_cmd		*check_exec(t_shell *shell, t_cmd *cmd, char **args,
				t_redir *redir);
t_cmd		*return_args_tmp(char ***args, t_cmd *tmp);

///////////////////////////////SPACE.C//////////////////////////////////////////
void		parse_space(t_shell *shell);
void		parse_space_around(t_shell *shell, int i);

///////////////////////////////PARSING.C////////////////////////////////////////
void		parse_cmd(t_shell *shell);
void		error_msg(t_shell *shell, char *msg);
void		parse_rd_token(t_shell *shell, int *j);
t_cmd		*parse_rd(t_shell *shell);

///////////////////////////////QUOTES.C/////////////////////////////////////////
void		remove_quotes(t_shell *shell);
void		replace_str(char **replace, char *str);
char		*remove_quotes_utils(t_cmd *tmp, char c);

/////////////////////////////HERE_DOC.C/////////////////////////////////////////
t_redir		*here_doc(t_cmd *tmp, char *limiter);
t_redir		*redirection(t_redir *redir, t_cmd *cmd);
t_redir		*import_heredoc(t_cmd *cmd, char *hd);

#endif
