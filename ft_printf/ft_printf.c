/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsalazar <fsalazar@student.42madrid.com:>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 12:59:50 by fsalazar          #+#    #+#             */
/*   Updated: 2023/03/24 13:01:50 by fsalazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>

static int	ft_case(const char *input, va_list ap)
{
	int	i;

	i = 0;
	if (*input == 'c')
		i += ft_print_char(va_arg(ap, int));
	else if (*input == 's')
		i += ft_print_str(va_arg(ap, char *));
	else if (*input == 'p')
		i += ft_print_ptr(va_arg(ap, unsigned long));
	else if (*input == 'd' || *input == 'i')
		i += ft_print_int(va_arg(ap, int));
	else if (*input == 'u')
		i += ft_print_uint(va_arg(ap, unsigned int));
	else if (*input == 'x')
		i += ft_print_hex(va_arg(ap, unsigned int), 0);
	else if (*input == 'X')
		i += ft_print_hex(va_arg(ap, unsigned int), 1);
	else if (*input == '%')
		i += ft_print_char('%');
	return (i);
}

int	ft_printf(const char *input, ...)
{
	va_list	ap;
	int		i;

	i = 0;
	va_start(ap, input);
	while (*input)
	{
		if (*input == '%' && *(input + 1) != '\0')
		{
			i += ft_case(input + 1, ap);
			input++;
		}
		else
			i += ft_print_char(*input);
		input++;
	}
	va_end(ap);
	return (i);
}
/*
int	main(int argc, char **argv)
{
	if (argc == 3)
	{
		ft_printf(argv[1], argv[2]);
		ft_printf("\n");
	}
	else
	{
		char			c;
		char			*test;
		int				i;
		unsigned int	ui;
		unsigned int	hex;
		int				print_count;

		c = 'c';
		test = "Hello World!";
		i = 2651;
		ui = 10;
		hex = 30;

		print_count = printf("\n\nThis is what printf prints:\n\n");
		ft_printf("ft_printf CHAR prints: %c\n", c);
		printf("Printf prints: %c\n", c);
		ft_printf("ft_printf STRING prints: %s\n", test);
		printf("Printf prints: %s\n", test);
		ft_printf("ft_printf POINTER prints: %p\n", test);
		printf("Printf prints: %p\n", test);
		ft_printf("ft_printf INTEGER prints: %d  :  %i\n", i, -i);
		printf("Printf prints: %d  :  %i\n", i, -i);
		ft_printf("ft_printf UNSIGNED INT prints: %u\n", ui);
		printf("Printf prints: %u\n", ui);
		ft_printf("ft_printf HEXADECIMAL prints: %x : %X\n", hex, hex);
		printf("Printf prints: %x  :  %X\n", hex, hex);
		ft_printf("ft_printf JUST %% prints: %%\n");
		printf("Printf prints: %%\n");
		ft_printf("ft_printf PRINTF_INT prints: %d\n", print_count);
		printf("Printf prints: %d\n", print_count);	
	}
	return (0);
}*/