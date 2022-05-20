/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   leak_test_internal_on_leak.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Juyeong Maing <jmaing@student.42seoul.kr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 02:34:03 by Juyeong Maing     #+#    #+#             */
/*   Updated: 2022/05/21 02:54:10 by Juyeong Maing    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "leak_test_internal.h"

int	leak_test_internal_on_leak(t_context *context)
{
	t_leak_test_iterator_internal	iterator;

	if (context->options.on_leak)
	{
		iterator.current = context->head;
		iterator.fail_counter = 0;
		iterator.remain = context->total_count;
		context->options.on_leak((void *)&iterator, context->context);
	}
	return (FT_LEAK_TEST_RESULT_LEAK);
}

bool	leak_test_iterator_has_next(t_leak_test_iterator *iterator)
{
	t_leak_test_iterator_internal *const	self
		= (t_leak_test_iterator_internal *)iterator;

	return (!!self->remain);
}

bool	leak_test_iterator_next(t_leak_test_iterator *iterator)
{
	t_leak_test_iterator_internal *const	self
		= (t_leak_test_iterator_internal *)iterator;

	self->remain--;
	if (!self->current || self->current->next_fail != self->fail_counter)
	{
		self->fail_counter++;
		return (true);
	}
	self->current = self->current->next;
	self->fail_counter = 0;
	return (false);
}
