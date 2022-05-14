/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   leak_test.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Juyeong Maing <jmaing@student.42seoul.kr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 14:57:45 by jmaing            #+#    #+#             */
/*   Updated: 2022/05/14 20:08:10 by Juyeong Maing    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEAK_TEST_H
# define LEAK_TEST_H

# include <stdbool.h>

typedef bool	(*t_leak_test)(void *context);

int		leak_test(t_leak_test target, void *context);
void	leak_test_start(void);
void	leak_test_end(void);

# define FT_LEAK_TEST_RESULT_OK 0
# define FT_LEAK_TEST_RESULT_ERROR -1
# define FT_LEAK_TEST_RESULT_LEAK 1

#endif
