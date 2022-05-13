/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   leak_test_internal_mock.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Juyeong Maing <jmaing@student.42seoul.kr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 19:14:26 by jmaing            #+#    #+#             */
/*   Updated: 2022/05/14 05:00:52 by Juyeong Maing    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "leak_test_internal.h"

void	*ft_leak_test_internal_mock_malloc(
	size_t size,
	void *(*real)(size_t size),
	void *context
)
{
	t_context *const	ctx = (t_context *) context;
	void				*result;

	if (ctx->count_limit && ctx->total_count >= ctx->count_limit)
	{
		ctx->error = true;
		return (NULL);
	}
	result = NULL;
	if (!ctx->current || ctx->current->next_fail != ctx->fail_counter)
	{
		result = real(size);
		if (!result)
			ctx->error = true;
		else
			ctx->remain_count++;
		ctx->fail_counter++;
	}
	else
	{
		ctx->current = ctx->current->next;
		ctx->fail_counter = 0;
	}
	ctx->total_count++;
	return (result);
}

void	ft_leak_test_internal_mock_free(
	void *ptr,
	void (*real)(void *ptr),
	void *context
)
{
	t_context *const	ctx = (t_context *) context;

	if (ptr)
		ctx->remain_count--;
	real(ptr);
}

static t_context	*g_context = NULL;

int	leak_test_internal_execute(t_context *context)
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

void	leak_test_start(void)
{
	malloc_mock(&g_context->mock, g_context);
}

void	leak_test_end(void)
{
	malloc_mock(NULL, NULL);
}
