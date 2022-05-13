/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   leak_test.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaing <jmaing@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 14:57:45 by jmaing            #+#    #+#             */
/*   Updated: 2022/05/13 15:02:57 by jmaing           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEAK_TEST_H
# define LEAK_TEST_H

# include <stdbool.h>

typedef bool	(*t_leak_test)(void *context, void (*start)(), void (*end)());

int	leak_test(t_leak_test target, void *context);

# define MALLOC_TEST_RESULT_OK 0
# define MALLOC_TEST_RESULT_ERROR 1
# define MALLOC_TEST_RESULT_TOO_MANY_MALLOC 2
# define MALLOC_TEST_RESULT_LEAK_IF_END 3

#endif
