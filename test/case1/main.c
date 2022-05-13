/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaing <jmaing@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 15:00:12 by jmaing            #+#    #+#             */
/*   Updated: 2022/05/14 02:49:20 by jmaing           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "portable_prelude.h"

#include <stdlib.h>
#include <stdio.h>

#include "../../src/leak_test.h"

static const char	*b(void *ptr)
{
	if (ptr)
		return ("true");
	else
		return ("false");
}

bool	test(void *context)
{
	void	*p1;
	void	*p2;
	void	*p3;
	void	*p4;
	void	*p5;

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
	p3 = malloc(42);
	p4 = malloc(42);
	p5 = malloc(42);
	free(p3);
	free(p4);
	free(p5);
	leak_test_end();
	printf("%s %s %s %s %s\n", b(p1), b(p2), b(p3), b(p4), b(p5));
	return (false);
}

int	main(void)
{
	const int	error = leak_test(&test, NULL);

	if (error == MALLOC_TEST_RESULT_ERROR)
		puts("Error occurred");
	else if (error == MALLOC_TEST_RESULT_LEAK)
		puts("LEAK FOUND!!!");
	return (0);
}
