/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 23:41:55 by njennes           #+#    #+#             */
/*   Updated: 2022/04/13 16:37:20 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../UTest/utest/utest.h"
#include "../../leaky.h"
#include "../../src/core/core.h"

int test_gc_alloc_10b();

int main()
{
	UTEST_BEGIN("gc_alloc");
	RUN_TEST("10 Bytes", test_gc_alloc_10b);
	UTEST_END();


}

int test_gc_alloc_10b()
{
	int malloc_calls = gc_get_malloc_calls();
	int footprint_before = gc_getfootprint();
	UTEST_ASSERT_INT_EQUAL(malloc_calls, 1);
	UTEST_ASSERT_INT_EQUAL(footprint_before, 0);

	void *ptr = gc_alloc(10);
	int malloc_calls_after = gc_get_malloc_calls();
	UTEST_ASSERT_PTR_NOT_NULL(ptr);
	UTEST_ASSERT_INT_EQUAL(gc_failed(), LK_FALSE);
	UTEST_ASSERT_PTR_NULL(gc_get_last_error());
	UTEST_ASSERT_INT_EQUAL((int)gc_getfootprint(), 1);
	UTEST_ASSERT_INT_NOT_EQUAL(malloc_calls_after, malloc_calls);
	UTEST_ASSERT_INT_EQUAL((int)gc_get()->first_free, 1);

	gc_free(ptr);
	UTEST_ASSERT_PTR_NOT_NULL(ptr);
	UTEST_ASSERT_INT_EQUAL(gc_failed(), LK_FALSE);
	UTEST_ASSERT_PTR_NULL(gc_get_last_error());
	UTEST_ASSERT_INT_EQUAL((int)gc_getfootprint(), 0);
	UTEST_ASSERT_INT_EQUAL((int)gc_get_malloc_calls(), malloc_calls_after);
	UTEST_ASSERT_INT_EQUAL((int)gc_get()->first_free, 0);
	return (0);
}
