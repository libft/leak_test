/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   leak_test_internal.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaing <jmaing@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 17:22:35 by jmaing            #+#    #+#             */
/*   Updated: 2022/05/14 02:30:08 by jmaing           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "leak_test_internal.h"

#include "malloc_mock.h"

static t_context	*g_context = NULL;

void	leak_test_start(void)
{
	malloc_mock(&g_context->mock, g_context);
}

void	leak_test_end(void)
{
	malloc_mock(NULL, NULL);
}

static int	leak_test_execute(t_context *context)
{
	context->total_count = 0;
	context->remain_count = 0;
	context->current = context->head;
	context->fail_counter = 0;
	g_context = context;
	context->target(context);
	g_context = NULL;
	if (context->remain_count)
		return (MALLOC_TEST_RESULT_LEAK);
	if (context->error)
		return (MALLOC_TEST_RESULT_ERROR);
	return (0);
}

static int	leak_test_internal(
	t_context *context,
	t_node *tail,
	size_t total_count_limit,
	size_t current_skipped
)
{
	t_node	node;
	int		error;

	if (!tail)
		context->head = &node;
	else
		tail->next = &node;
	node.next = NULL;
	node.next_fail = total_count_limit - current_skipped;
	error = 0;
	while (--node.next_fail && !error)
	{
		error = leak_test_execute(context);
		if (!error)
			error = leak_test_internal(
					context,
					&node,
					context->total_count,
					current_skipped + node.next_fail + 1);
	}
	if (!tail)
		context->head = NULL;
	else
		tail->next = NULL;
	return (error);
}

int	leak_test(t_leak_test target, void *context)
{
	t_context	my_context;
	int			error;

	my_context.mock.malloc_mock = ft_leak_test_internal_mock_malloc;
	my_context.mock.free_mock = ft_leak_test_internal_mock_free;
	my_context.target = target;
	my_context.context = context;
	my_context.head = NULL;
	my_context.error = false;
	my_context.count_limit = 0;
	error = leak_test_execute(&my_context);
	if (error)
		return (error);
	my_context.count_limit = my_context.total_count;
	return (leak_test_internal(&my_context, NULL, my_context.count_limit, 0));
}
