#include "minishell.h"

t_env_variable  *create_env_node(char *name, char *value)
{
    t_env_variable  *node;

    node = malloc(sizeof(t_env_variable));
    if (!node)
        return (NULL);
    node->name = ft_strdup(name);
    node->value = ft_strdup(value);
    node->next = NULL;
    return (node);  
}

void add_env_node(t_env_variable **head, const char *name, const char *value)
{
    t_env_variable *node;
    
    node = create_env_node(name, value);
    if (node)
        ft_lstadd_back(head, node);
}

t_env_variable  *create_default_env(void)
{
    t_env_variable *head;

    head = NULL;
    add_env_node(&head, "PWD", PWD_PATH);
    add_env_node(&head, "PATH", PATH);
    add_env_node(&head, "SHLVL", "1");
    add_env_node(&head, "_", "./minishell";)
    return (head);
}