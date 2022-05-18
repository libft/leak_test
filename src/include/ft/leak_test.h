/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   leak_test.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Juyeong Maing <jmaing@student.42seoul.kr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 14:57:45 by jmaing            #+#    #+#             */
/*   Updated: 2022/05/18 21:28:26 by Juyeong Maing    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEAK_TEST_H
# define LEAK_TEST_H

# include <stddef.h>
# include <stdbool.h>

typedef bool	(*t_leak_test)(const void *context);
typedef struct s_leak_test_options
{
	size_t	maximum_count;
	size_t	minimum_count;
	bool	allow_empty;
}	t_leak_test_options;

int		leak_test(
			t_leak_test target,
			const void *context,
			t_leak_test_options *options);
void	leak_test_start(void);
void	leak_test_end(void);

// OK. No error.
# define FT_LEAK_TEST_RESULT_OK 0
// At least one leak was found.
# define FT_LEAK_TEST_RESULT_LEAK 1
// No malloc() call. Possibly wrong test function.
# define FT_LEAK_TEST_RESULT_NO_ALLOCATION 2
// Test function returned an error, or allocation failed.
# define FT_LEAK_TEST_RESULT_ERROR -1
// Too many tries. Avoid allocations after allocation failures.
# define FT_LEAK_TEST_RESULT_ERROR_TOO_MANY -2
// malloc() call in malloc hook was failed.
# define FT_LEAK_TEST_RESULT_ERROR_ALLOCATION_FAILURE -3
// Test function NOT always do same thing even with same malloc() result.
# define FT_LEAK_TEST_RESULT_ERROR_WRONG_TEST -4
// malloc() called count is smaller than minimum count
# define FT_LEAK_TEST_RESULT_ERROR_TOO_SMALL -5

#endif
