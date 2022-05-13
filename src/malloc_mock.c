/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_mock.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaing <jmaing@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 12:30:10 by jmaing            #+#    #+#             */
/*   Updated: 2022/05/13 17:30:37 by jmaing           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gnu_source.h"
#include "malloc_mock.h"

#include <stddef.h>
#include <dlfcn.h>

static const t_malloc_mock	*g_mock = NULL;
static void					*g_context = NULL;

void	*malloc(size_t size)
{
	static void	*(*real)(size_t size) = NULL;

	if (!real)
		real = (void *(*)(size_t size))dlsym(RTLD_NEXT, "malloc");
	if (!g_mock)
		return (real(size));
	return (g_mock->malloc_mock(size, real, g_context));
}

void	free(void *ptr)
{
	static void	(*real)(void *ptr) = NULL;

	if (!real)
		real = (void (*)(void *ptr))dlsym(RTLD_NEXT, "free");
	if (!g_mock)
		return (real(ptr));
	return (g_mock->free_mock(ptr, real, g_context));
}

void	malloc_mock(const t_malloc_mock *mock, void *context)
{
	g_mock = mock;
	g_context = context;
}
