#ifndef MINISHELL_H
# define MINISHELL_H

// libft
# include "../libft/libft.h"
// readline, add_history
# include <readline/history.h>
# include <readline/readline.h>
// printf
# include <stdio.h>
// malloc, free
# include <stdlib.h>
// write, execve
# include <unistd.h>
// exit
# include <signal.h>
// strerror
# include <string.h>
// tgetent, tputs
# include <termcap.h>
// getpid
# include <sys/types.h>
// stat, lstat, fstat
# include <sys/stat.h>
// open
# include <fcntl.h>
// opendir, readdir, closedir
# include <dirent.h>
// perror
# include <errno.h>
// fork, wait, waitpid, wait3, wait4
# include <sys/wait.h>
// signal, sigaction, sigemptyset, sigaddset, kill
# include <sys/signal.h>
// access, getcwd, chdir, unlink, dup, dup2, pipe, isatty, ttyname, ttyslot,
// tcsetattr, tcgetattr, ioctl, getenv
# include <unistd.h>
// va_arg, va_start, va_end
# include <stdarg.h>

// MAX_PATH for getcwd
# define MAX_PATH 1016
// BOOL
# define TRUE 1
# define FALSE 0
// Pipes
# define READ_END 0
# define WRITE_END 1
// Parsing
# define SQUOTE 0
# define DQUOTE 1
# define SYMBOL 2
# define COMMAND 3
# define PIPE 4
# define REDIRECT 5
// Colors
# define RESET "\033[0m"
# define COLOR_GREEN "\033[0;32m"
# define COLOR_BLUE "\033[0;34m"
# define COLOR_RED "\033[0;31m"
// Stack
# define STDIN 0
# define STDOUT 1
# define STDERR 2

typedef struct s_minishell	t_minishell;
typedef struct s_command	t_command;
typedef struct s_token		t_token;
typedef struct s_env		t_env;
typedef struct s_process	t_process;
typedef struct s_redir		t_redir;

typedef struct s_redir
{
	char					*file;
	int						type;
	struct s_redir			*next;
}							t_redir;

typedef struct s_command
{
	char					*cmd;
	char					**cmd_args;
	struct s_redir			*redir;
	struct s_command		*next;
}							t_command;

typedef struct s_token
{
	char					*token;
	int						type;
	struct s_token			*next;
}							t_token;

typedef struct s_env
{
	char					*name;
	char					*value;
	struct s_env			*next;
}							t_env;

typedef struct s_process
{
	pid_t					pid;
	int						status;
	char					*command;
	struct s_process		*next;
}							t_process;

typedef struct s_builtins
{
	char					*cmd[7];
	void					(*func[7])(t_minishell *);

}							t_builtins;

typedef struct s_minishell
{
	int						exit_status;
	char					*line;
	char					*prompt;
	t_redir					*redir;
	t_builtins				*builtins;
	t_command				*command;
	t_token					*tokens;
	t_env					*env;
	t_process				*process;
}							t_minishell;

// errors/checks_exits.c
void						free_structs(t_minishell *minishell);
// initialize/init_structs.c
t_minishell					*init_structs(char **envp);
t_env						*init_env(char **envp);
t_command					*init_command(void);
t_builtins					*init_builtins(void);
t_process					*init_process(void);
// initialize/env_lst_utils.c
void						add_env(t_env **head, t_env *env);
void						ft_envclear(t_env **lst);
void						ft_envdelone(t_env *lst);
void						ft_remove_env_node(t_env *lst, t_env *node);
t_env						*ft_envlast(t_env *lst);
// initialize/display_prompt.c
char						*ft_strcat(char *dest, const char *src);
char						*multi_strjoin(int total_len, int count, ...);
char	*find_env_var(t_minishell *minishell,
					char *var);
char						*display_prompt(t_minishell *minishell);
t_env	*find_env_var_node(t_minishell *minishell,
							char *var);
// signals/signals.c
void						sigint_handler(int sig);
void						sigquit_handler(int sig);
void						listen_signals(void);
// lexer/lexer.c
int							parse_command(t_minishell *minishell);
t_token						*tokenize_line(t_minishell *minishell, char *line);
// lexer/lexer_utils.c
int							make_command(t_minishell *minishell, t_token **head,
								char *line, int i);
int							make_symbol(t_minishell *minishell, t_token **head,
								char *line, int i);
int							make_quote(t_minishell *minishell, t_token **head,
								char *line, int i);
int							is_quote(char c);
int							is_special_character(char c);
// lexer/lexer_lst_utils.c
void						add_token(t_token **head, char *content, int type);
void						ft_tokenclear(t_token **lst);
void						ft_tokendelone(t_token *lst);
// lexer/lexer_errors.c
int							token_error(t_minishell *minishell, char *token,
								int type);
int							symbol_type(t_token *token);
int							parse_errors(t_minishell *minishell);

// parser/build_cmd_struct.c

// parser/cmd_lst_utils.c
void						add_cmd(t_command **head, t_command *cmd);
void						ft_cmdclear(t_command **lst);
void						ft_cmddelone(t_command *lst);
void						ft_remove_cmd_node(t_command *lst, t_command *node);
t_command					*ft_cmdlast(t_command *lst);
// expander/expander.c
char						*expand_token(t_minishell *minishell, char *token);
char						*ft_strjoin_free(char *s1, char *s2);
// builtins/ft_cd.c
void						ft_cd(t_minishell *minishell);
// builtins/ft_echo.c
void						ft_echo(t_minishell *minishell);
// builtins/ft_pwd.c
void						ft_pwd(t_minishell *minishell);
// builtins/ft_export.c
void						ft_export(t_minishell *minishell);
// builtins/ft_unset.c
void						ft_unset(t_minishell *minishell);
// builtins/ft_env.c
void						ft_env(t_minishell *minishell);
// builtins/ft_exit.c
void						ft_exit(t_minishell *minishell);
// utils/general_utils.c
void						ft_free_array(char **array);
int							line_empty(char *line);
#endif
