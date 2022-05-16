/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Juyeong Maing <jmaing@student.42seoul.kr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 15:00:12 by jmaing            #+#    #+#             */
/*   Updated: 2022/05/16 21:51:55 by Juyeong Maing    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "portable_prelude.h"

#include <stdlib.h>
#include <stdio.h>

#include <ft/leak_test.h>

static const char	*g_b[2] = {"false", "true"};

static void	*a(size_t size)
{
	void *const	result = malloc(size);

	free(result);
	return (result);
}

bool	has_no_leak(const void *context)
{
	void	*p1;
	void	*p2;
	void	*p3;
	void	*p4;
	void	*p5;

	printf("%s", (char *)context);
	leak_test_start();
	p1 = malloc(42);
	p2 = malloc(42);
	free(p1);
	free(p2);
	if (!p1 || !p2)
	{
		leak_test_end();
		printf("%s %s\n", g_b[!!p1], g_b[!!p2]);
		return (false);
	}
	p3 = a(42);
	p4 = a(42);
	p5 = a(42);
	leak_test_end();
	printf("%s %s %s %s %s\n",
		g_b[!!p1], g_b[!!p2], g_b[!!p3], g_b[!!p4], g_b[!!p5]);
	return (false);
}

bool	has_leak(const void *context)
{
	void	*a;
	void	*b;

	(void) context;
	leak_test_start();
	a = malloc(42);
	if (!a)
		return (false);
	b = malloc(42);
	if (!b)
		return (false);
	free(a);
	free(b);
	return (false);
}

bool	do_nothing(const void *context)
{
	return (*(bool *)context);
}

int	main(void)
{
	int					error;
	t_leak_test_options	options;
	bool				context;

	options.allow_empty = false;
	options.maximum_count = 10;
	printf("[1] %d\n", leak_test(&has_no_leak, "[1]:\t", &options));
	options.maximum_count = 11;
	printf("[2] %d\n", leak_test(&has_no_leak, "[2]:\t", &options));
	printf("[3] %d\n", leak_test(&has_leak, NULL, &options));
	context = false;
	printf("[5] %d\n", leak_test(&do_nothing, &context, &options));
	options.allow_empty = true;
	printf("[6] %d\n", leak_test(&do_nothing, &context, &options));
	context = true;
	printf("[7] %d\n", leak_test(&do_nothing, &context, &options));
	return (0);
}
