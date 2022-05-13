/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   leak_test_internal_mock.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaing <jmaing@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 19:14:26 by jmaing            #+#    #+#             */
/*   Updated: 2022/05/14 02:36:41 by jmaing           ###   ########.fr       */
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
	else if (ctx->current)
	{
		ctx->current = ctx->current->next;
		ctx->fail_counter++;
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
