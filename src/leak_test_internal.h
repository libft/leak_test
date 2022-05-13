/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   leak_test_internal.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaing <jmaing@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 17:25:11 by jmaing            #+#    #+#             */
/*   Updated: 2022/05/14 02:29:41 by jmaing           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEAK_TEST_INTERNAL_H
# define LEAK_TEST_INTERNAL_H

# include "leak_test.h"

# include <stddef.h>

# include "malloc_mock.h"

void	*ft_leak_test_internal_mock_malloc(
			size_t size,
			void *(*real)(size_t size),
			void *context);

void	ft_leak_test_internal_mock_free(
			void *ptr,
			void (*real)(void *ptr),
			void *context);

typedef struct s_node
{
	struct s_node	*next;
	size_t			next_fail;
}	t_node;

typedef struct s_context
{
	t_malloc_mock	mock;
	t_leak_test		target;
	void			*context;
	t_node			*head;
	size_t			count_limit;
	size_t			total_count;
	size_t			remain_count;
	t_node			*current;
	size_t			fail_counter;
	bool			error;
}	t_context;

#endif
