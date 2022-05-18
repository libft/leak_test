/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   leak_test_internal.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Juyeong Maing <jmaing@student.42seoul.kr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 17:22:35 by jmaing            #+#    #+#             */
/*   Updated: 2022/05/18 21:47:18 by Juyeong Maing    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "leak_test_internal.h"

#include "malloc_mock.h"

static const t_leak_test_options	g_default_options = {
	0, // test count limit - default unlimited
	0, // expected minimum malloc() count
	false, // allow empty - default false to catch wrong test function
};

static int	leak_test_internal(
	t_context *context,
	t_node *tail,
	size_t total_count_limit,
	size_t current_skipped
)
{
	t_node	node;
	int		error;

	if (total_count_limit <= current_skipped)
		return (0);
	if (!tail)
		context->head = &node;
	else
		tail->next = &node;
	node.next = NULL;
	node.next_fail = total_count_limit - current_skipped;
	error = 0;
	while (node.next_fail && !error)
	{
		node.next_fail--;
		error = leak_test_internal_execute(context);
		if (!error)
			error = leak_test_internal(context, &node, context->total_count,
					current_skipped + node.next_fail + 1);
	}
	if (!tail)
		context->head = NULL;
	else
		tail->next = NULL;
	return (error);
}

int	leak_test(
	t_leak_test target,
	const void *context,
	t_leak_test_options *options
)
{
	t_context	my_context;
	int			error;

	my_context.mock.malloc_mock = ft_leak_test_internal_mock_malloc;
	my_context.mock.free_mock = ft_leak_test_internal_mock_free;
	my_context.target = target;
	my_context.context = context;
	my_context.head = NULL;
	if (options)
		my_context.options = *options;
	else
		my_context.options = g_default_options;
	my_context.test_count = 0;
	my_context.error = false;
	my_context.count_limit = 0;
	error = leak_test_internal_execute(&my_context);
	if (error)
		return (FT_LEAK_TEST_RESULT_ERROR);
	my_context.count_limit = my_context.total_count;
	if (!my_context.count_limit && !my_context.options.allow_empty)
		return (FT_LEAK_TEST_RESULT_NO_ALLOCATION);
	if (my_context.options.minimum_count
		&& my_context.count_limit < my_context.options.minimum_count)
		return (FT_LEAK_TEST_RESULT_ERROR_TOO_SMALL);
	return (leak_test_internal(&my_context, NULL, my_context.count_limit, 0));
}

const char	*leak_test_error(int errno)
{
	if (!errno)
		return ("No error.");
	if (errno == FT_LEAK_TEST_RESULT_LEAK)
		return ("At least one leak was found.");
	if (errno == FT_LEAK_TEST_RESULT_NO_ALLOCATION)
		return ("No malloc() call. Possibly wrong test function.");
	if (errno == FT_LEAK_TEST_RESULT_ERROR)
		return ("Test function returned an error, or allocation failed.");
	if (errno == FT_LEAK_TEST_RESULT_ERROR_TOO_MANY)
		return ("Too many tries. Avoid allocations after allocation failures.");
	if (errno == FT_LEAK_TEST_RESULT_ERROR_ALLOCATION_FAILURE)
		return ("malloc() call in malloc hook was failed.");
	if (errno == FT_LEAK_TEST_RESULT_ERROR_WRONG_TEST)
		return ("Test function didn't do same even with same malloc() result.");
	if (errno == FT_LEAK_TEST_RESULT_ERROR_TOO_SMALL)
		return ("malloc() called count is smaller than minimum count");
	return ("Incorrect error code");
}
