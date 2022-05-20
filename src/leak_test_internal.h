/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   leak_test_internal.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Juyeong Maing <jmaing@student.42seoul.kr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 17:25:11 by jmaing            #+#    #+#             */
/*   Updated: 2022/05/21 02:48:43 by Juyeong Maing    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEAK_TEST_INTERNAL_H
# define LEAK_TEST_INTERNAL_H

# include "include/ft/leak_test.h"

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
	t_malloc_mock		mock;
	t_leak_test			target;
	const void			*context;
	t_node				*head;
	t_leak_test_options	options;
	size_t				test_count;
	size_t				count_limit;
	size_t				total_count;
	size_t				remain_count;
	t_node				*current;
	size_t				fail_counter;
	bool				error;
}	t_context;

typedef struct s_leak_test_iterator_internal
{
	t_node	*current;
	size_t	fail_counter;
	size_t	remain;
}	t_leak_test_iterator_internal;

int		leak_test_internal_execute(t_context *context);
int		leak_test_internal_on_leak(t_context *context);

#endif
