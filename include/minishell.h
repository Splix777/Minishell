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
# define CHARACTER
# define SYMBOL
// Colors
# define RESET "\033[0m"
# define COLOR_GREEN "\033[0;32m"
# define COLOR_BLUE "\033[0;34m"
// Stack
# define STDIN 0
# define STDOUT 1
# define STDERR 2

typedef struct s_minishell		t_minishell;
typedef struct s_command		t_command;
typedef struct s_history		t_history;
typedef struct s_env_variable	t_env_variable;
typedef struct s_process		t_process;

typedef struct s_command
{
	char						*cmd;
	char						**cmd_args;
	char						*input_redirection;
	char						*output_redirection;
	int							append_mode;
	int							here_doc;
	char						*here_doc_delimiter;
	char						**here_document_lines;
	struct s_command			*next;
}								t_command;
/*
cmd: A string to store the command name.
cmd_args: A pointer to a string array (char**) to store the command arguments.
input_redirection: A string to store the input redirection file name or descriptor.
output_redirection: A string to store the output redirection file name or descriptor.
append_mode: An integer flag indicating whether the output redirection should be performed 
in append mode.
here_doc: An integer flag indicating whether the command uses a here document for input.
here_doc_delimiter: A string to store the delimiter for the here document.
here_document_lines: A pointer to a string array (char**) to store the lines of input 
for the here document.
background_execution: An integer flag indicating whether the command should be executed 
in the background.*/
typedef struct s_history
{
	char						*command;
	time_t						timestamp;
	struct s_history			*next;
}								t_history;
/*
command: A string to store the command entered by the user.
timestamp: A time_t variable to store the timestamp indicating when the command was 
executed or added to the history.
next: A pointer to the next entry in the history,
	allowing you to maintain a linked 
list of history entries.*/
typedef struct s_env
{
	char						*name;
	char						*value;
	struct s_env				*next;
}								t_env;
/*
In this structure, name represents the name of the environment variable,
	value stores 
its corresponding value,
	and next is a pointer to the next environment variable in 
the linked list.*/
typedef struct s_process
{
	pid_t						pid;
	int							status;
	char						*command;
	struct s_process			*next;
}								t_process;

typedef struct	s_builtins
{
	char	*cmd[7];
	void	(*func[7])(t_minishell*);

}				t_builtins;
/*
Here, pid holds the process ID of the child process,
	status represents its exit status, 
command stores the command associated with the process,
	and next is a pointer to the next
process in the linked list.*/
typedef struct s_minishell
{
	int				exit_status;
	t_builtins		*builtins;	// Structure for builtin cmds
	t_command		*command; 	// Structure for command-related data
	t_history		*history; 	// Structure for command history data
	t_env			*env;		// Structure for environment variables data
	t_process		*process;	// Structure for signal handling data
}								t_minishell;
/* GLOBAL*/

// extern t_minishell *minishell;

// errors/checks_exits.c
void	free_structs(t_minishell *minishell);
int		line_empty(char *line);
// initialize/init_structs.c
t_minishell	*init_structs(char **envp);
t_env		*init_env(char **envp);
t_command	*init_command(void);
t_history	*init_history(void);
t_builtins	*init_builtins(void);
t_process	*init_process(void);
// initialize/env_lst_utils.c
void	add_env(t_env **head, t_env *env);
void	ft_envclear(t_env **lst);
void	ft_envdelone(t_env *lst);
t_env	*ft_envlast(t_env *lst);
// initialize/display_prompt.c
char	*ft_strcat(char *dest, const char *src);
char	*multi_strjoin(int total_len, int count, ...);
char    *find_env_var(t_minishell *minishell, char *var);
char	*display_prompt(t_minishell *minishell);
// signals/signals.c
void    sigint_handler(int sig);
void    sigquit_handler(int sig);
void    listen_signals(void);
// builtins/ft_echo.c
void	ft_echo(t_minishell *minishell);
// builtins/ft_cd.c
void	ft_cd(t_minishell *minishell);
// builtins/ft_pwd.c
void	ft_pwd(t_minishell *minishell);
// builtins/ft_export.c
void	ft_export(t_minishell *minishell);
// builtins/ft_unset.c
void	ft_unset(t_minishell *minishell);
// builtins/ft_env.c
void	ft_env(t_minishell *minishell);
// builtins/ft_exit.c
void	ft_exit(t_minishell *minishell);


#endif