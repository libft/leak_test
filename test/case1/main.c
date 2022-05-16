/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Juyeong Maing <jmaing@student.42seoul.kr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 15:00:12 by jmaing            #+#    #+#             */
/*   Updated: 2022/05/16 16:56:46 by Juyeong Maing    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "portable_prelude.h"

#include <stdlib.h>
#include <stdio.h>

#include <ft/leak_test.h>

static void	*a(size_t size)
{
	void *const	result = malloc(size);

	free(result);
	return (result);
}

static const char	*b(void *ptr)
{
	if (ptr)
		return ("true");
	else
		return ("false");
}

bool	has_no_leak(void *context)
{
	void	*p1;
	void	*p2;
	void	*p3;
	void	*p4;
	void	*p5;

	printf("%s", context);
	leak_test_start();
	p1 = malloc(42);
	p2 = malloc(42);
	free(p1);
	free(p2);
	if (!p1 || !p2)
	{
		leak_test_end();
		printf("%s %s\n", b(p1), b(p2));
		return (false);
	}
	p3 = a(42);
	p4 = a(42);
	p5 = a(42);
	leak_test_end();
	printf("%s %s %s %s %s\n", b(p1), b(p2), b(p3), b(p4), b(p5));
	return (false);
}

bool	has_leak(void *context)
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

int	main(void)
{
	int					error;
	t_leak_test_options	options;

	options.maximum_count = 10;
	error = leak_test(&has_no_leak, "[1]:\t", &options);
	if (error < 0)
		printf("[1]:\tError occurred: %d\n", error);
	else if (error)
		puts("[1]:\tLEAK FOUND!!!");
	options.maximum_count = 11;
	error = leak_test(&has_no_leak, "[2]:\t", &options);
	if (error < 0)
		printf("[2]:\tError occurred: %d\n", error);
	else if (error)
		puts("[2]:\tLEAK FOUND!!!");
	error = leak_test(&has_leak, NULL, NULL);
	if (error < 0)
		printf("[3]:\tError occurred: %d\n", error);
	else if (error == FT_LEAK_TEST_RESULT_LEAK)
		puts("[3]:\tLEAK FOUND!!!");
	return (0);
}
