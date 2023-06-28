/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsalazar <fsalazar@student.42madrid.com:>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 13:00:00 by fsalazar          #+#    #+#             */
/*   Updated: 2023/03/24 13:00:01 by fsalazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

char	*get_next_line(int fd);
char	*ft_read_and_save(int fd, char *save);
char	*read_line(char *save);
char	*new_save(char *save);

char	*gnl_strjoin(char *s1, char *s2);
char	*gnl_strdup(char *s1);
char	*gnl_strchr(char *str, char c);

size_t	gnl_strlen(char *str);
int		ft_print_char(int c);
int		ft_printf(const char *input, ...);
int		ft_print_hex(unsigned int n, int upper);
int		ft_print_int(int n);
int		ft_print_ptr(unsigned long ptr);
int		ft_print_str(char *str);
int		ft_print_uint(unsigned int n);

#endif
