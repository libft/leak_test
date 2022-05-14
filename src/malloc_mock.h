/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_mock.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Juyeong Maing <jmaing@student.42seoul.kr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 12:20:43 by jmaing            #+#    #+#             */
/*   Updated: 2022/05/15 06:19:42 by Juyeong Maing    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_MOCK_H
# define MALLOC_MOCK_H

# include <stddef.h>
# include <stdbool.h>

typedef struct s_malloc_mock
{
	void	*(*malloc_mock)(size_t, void *(*real)(size_t), void *context);
	void	(*free_mock)(void *, void (*real)(void *), void *context);
}	t_malloc_mock;

void	malloc_mock(const t_malloc_mock *mock, void *context);

#endif
