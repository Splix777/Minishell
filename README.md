<h1 align="center">Minishell 🐚</h1>
<h4 align="center">As beautiful as a shell </h4>

## About ##

- Minishell is a project at school 42.

### Execution : ###
To execute this Program you have use linux.    
```
make && ./minishell
```

### Brief Summary ###

## Your shell should: ##

• Not interpret unclosed quotes or unspecified special characters like \ or ;.

• Not use more than one global variable, think about it and be ready to explain why
you do it.

• Show a prompt when waiting for a new command.

• Have a working History.

• Search and launch the right executable (based on the PATH variable or by using
relative or absolute path)

## • It must implement the builtins: ##

  ◦ echo with option -n
  
  ◦ cd with only a relative or absolute path
  
  ◦ pwd with no options

## Minishell As beautiful as a shell ##

  ◦ export with no options
  
  ◦ unset with no options
  
  ◦ env with no options or arguments
  
  ◦ exit with no options
  
• ’ inhibit all interpretation of a sequence of characters.

• " inhibit all interpretation of a sequence of characters except for $.

## • Redirections: ##
  ◦ < should redirect input.
  
  ◦ > should redirect output.
  
  ◦ “<<” read input from the current source until a line containing only the delimiter is seen. it doesn’t need to update history!
  
  ◦ “>>” should redirect output with append mode.
  
• Pipes | The output of each command in the pipeline is connected via a pipe to the
input of the next command.

• Environment variables ($ followed by characters) should expand to their values.

• $? should expand to the exit status of the most recently executed foreground
pipeline.

• ctrl-C ctrl-D ctrl-\ should work like in bash.

## • When interactive: ##

  ◦ ctrl-C print a new prompt on a newline.
  
  ◦ ctrl-D exit the shell.
  
  ◦ ctrl-\ do nothing.
  
readline function can produce some leak you don’t need to fix this.
But beware your own code should not produce leaks.
You should limit yourself to the subject description.
Anything not asked is not required.
For every point, if you have any doubt take [bash](https://www.gnu.org/savannah-checkouts/gnu/bash/manual/) as a reference.
