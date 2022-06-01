/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Juyeong Maing <jmaing@student.42seoul.kr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 15:00:12 by jmaing            #+#    #+#             */
/*   Updated: 2022/06/02 00:46:52 by Juyeong Maing    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "portable_prelude.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <ft/leak_test.h>

#define ANY_SIZE 42

static const char	*g_b[2] = {"false", "true"};

static const char	*malloc_succeed(size_t size)
{
	void *const	result = malloc(size);

	free(result);
	return (g_b[!!result]);
}

bool	has_no_leak(const void *context)
{
	void		*p1;
	void		*p2;
	const char	*p3;
	const char	*p4;
	const char	*p5;

	printf("%s", (char *)context);
	leak_test_start();
	p1 = malloc(ANY_SIZE);
	p2 = malloc(ANY_SIZE);
	free(p1);
	free(p2);
	if (!p1 || !p2)
	{
		leak_test_end();
		printf("%s %s\n", g_b[!!p1], g_b[!!p2]);
		return (false);
	}
	p3 = malloc_succeed(ANY_SIZE);
	p4 = malloc_succeed(ANY_SIZE);
	p5 = malloc_succeed(ANY_SIZE);
	leak_test_end();
	printf("%s %s %s %s %s\n", g_b[!!p1], g_b[!!p2], p3, p4, p5);
	return (false);
}

bool	has_leak(const void *context)
{
	void	*this_might_leak;
	void	*if_this_fails;

	(void) context;
	leak_test_start();
	this_might_leak = malloc(ANY_SIZE);
	if (!this_might_leak)
		return (false);
	if_this_fails = malloc(ANY_SIZE);
	if (!if_this_fails)
		return (false);
	free(this_might_leak);
	free(if_this_fails);
	return (false);
}

bool	do_nothing(const void *context)
{
	return (*(bool *)context);
}

int	main(void)
{
	t_leak_test_options	options;
	bool				context;

	memset(&options, 0, sizeof(t_leak_test_options));
	options.allow_empty = false;
	options.maximum_count = 10;
	printf("[1] %s\n", leak_test_error(
			leak_test(&has_no_leak, "[1]:\t", &options)));
	options.maximum_count = 11;
	printf("[2] %s\n", leak_test_error(
			leak_test(&has_no_leak, "[2]:\t", &options)));
	printf("[3] %s\n", leak_test_error(leak_test(&has_leak, NULL, &options)));
	context = false;
	printf("[4] %s\n", leak_test_error(
			leak_test(&do_nothing, &context, &options)));
	options.allow_empty = true;
	printf("[5] %s\n", leak_test_error(
			leak_test(&do_nothing, &context, &options)));
	options.minimum_count = 1;
	printf("[6] %s\n", leak_test_error(
			leak_test(&do_nothing, &context, &options)));
	context = true;
	printf("[7] %s\n", leak_test_error(
			leak_test(&do_nothing, &context, &options)));
	return (EXIT_SUCCESS);
}
