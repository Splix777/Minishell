#ifndef MINISHELL_H
# define MINISHELL_H

// libft
# include "libft/libft.h"
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
// Manually assigning ENV
# define PWD_PATH "/Users/fsalazar/Desktop/minishell"
# define PATH "/Users/fsalazar/.brew/bin:/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin"
# define SHLVL "SHLVL=1"
# define UNDERSCORE "/Users/fsalazar/Desktop/minishell/./minishell"
// Pipes
# define READ_END 0
# define WRITE_END 1
// Parsing
# define CHARACTER
# define SYMBOL
// Prompt


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
	int							background_execution;
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
typedef struct s_env_variable
{
	char						**envp;
	char						*path;
	char						*pwd;
	char						*oldpwd;
	char						*shlvl;
	char						*underscore;
}								t_env_variable;
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
	char.	*cmd;
	void	(*f)(t_minishell*);

}				t_builtins;
/*
Here, pid holds the process ID of the child process,
	status represents its exit status, 
command stores the command associated with the process,
	and next is a pointer to the next
process in the linked list.*/
typedef struct s_minishell
{
	int				exit_code;
	t_builtins		*builtins; // Structure for builtin cmds
	t_command		*command;  // Structure for command-related data
	t_history		*history;  // Structure for command history data
	t_env_variable	*env; // Structure for environment variables data
	t_process		*process;  // Structure for signal handling data
}								t_minishell;
/* GLOBAL*/

extern t_minishell *minishell;

// init_structs.c
t_minishell						*init_structs(char **envp);
t_command						*init_command(void);
t_history						*init_history(void);
t_env_variable					*init_env(char **envp);
t_process						*init_process(void);
// checks_exits.c
void							free_structs(t_minishell *minishell, int which);
// init_utils.c
char							*find_path(char **envp);
char							*find_pwd(char **envp);
char							*find_shlvl(char **envp);
char							*find_underscore(char **envp);
t_env_variable					*create_default_env(void);

#endif
