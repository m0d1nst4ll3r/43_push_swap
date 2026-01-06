/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lis_get.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapohlen <rapohlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 22:48:04 by rapohlen          #+#    #+#             */
/*   Updated: 2026/01/06 15:12:01 by rapohlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solver.h"

/*	Longest Increasing Subsequence - Fast Algorithm (#1)
 *
 * For each possible subsequence in our circular list (loop #1 - get_lis_addr)
 * Get the len of its LIS without knowing exact values (loop #2 - get_lis_len)
 * To figure out the length, we need a binary search (loop #3 in bsearch)
 *
 * Iterate through the set of numbers, for each number, compare it to an array
 *	(originally empty). If the array contains a higher value, replace that
 *	value with the number. If not, append the number to the array and increment
 *	the len.
 * We use bsearch to search the array, we use a modified bsearch that returns
 *	the first higher value (since there are no duplicates in our set anyway).
 *
 * Ex:
 *	0 4 12 2 10 6 9 13 3 11 7 15
 * LIS:
 *	0 4         6 9 13        15
 * Array states:
 *					0 (empty before loop)
 *	0				1
 *	0 4				2
 *	0 4 12			3
 *	0 2 12			3
 *	0 2 10			3
 *	0 2 6			3
 *	0 2 6 9			4
 *	0 2 6 9 13		5
 *	0 2 3 9 13		5
 *	0 2 3 9 11		5
 *	0 2 3 7 11		5
 *	0 2 3 7 11 15	6
 *
 * We don't know the exact values of the LIS, but we know it is of length 6.
*/
static int	get_lis_len(t_stack *head, int *arr)
{
	t_stack	*cur;
	int		len;
	int		ret;

	len = 0;
	cur = head;
	while (1)
	{
		ret = bsearch_higher(arr, len, cur->val);
		if (ret == -1)
		{
			arr[len] = cur->val;
			len++;
		}
		else
			arr[ret] = cur->val;
		cur = cur->next;
		if (cur == head)
			return (len);
	}
}

t_stack	*get_lis_addr(t_stack *head, int *arr)
{
	t_stack	*cur;
	int		max_len;
	t_stack	*max_addr;
	int		ret;

	max_len = 0;
	cur = head;
	while (1)
	{
		ret = get_lis_len(cur, arr);
		if (ret > max_len)
		{
			max_len = ret;
			max_addr = cur;
		}
		cur = cur->next;
		if (cur == head)
			return (max_addr);
	}
}

/*	Longest Increasing Subsequence - Slow Algorithm (#2)
 *
 * Now that we have found the subset containing the longest LIS with algo #1,
 *	we find the exact values in that LIS.
 *
 * For each element i of the set starting at index 1 (loop #1)
 *
 * We write the LIS len at that index in a lis_len array (similar to algo #1)
 * But this time we also write the index of the preceding LIS value in a
 *	lis_sub array.
 *
 * We do this by comparing each preceding element to it (loop #2)
 *
 * If elem_j is smaller (valid LIS), and if it would result in the highest LIS
 *	computed thus far at index i, we update values in lis_len and lis_sub.
 *
 * At the end, we will have a complete chain written in lis_sub
 *
 * Ex:
 *	0 4 12 2 10 6 9 13 3 11 7 15
 * LIS:
 *	0 4         6 9 13        15
 *
 * By default, lis_len contains 1 in every slot (smallest possible LIS len is 1)
 *
 * lis_len:
 *	1 1 1 1 1 1 1 1 1 1 1 1
 * lis_sub:
 *	-
 * After 4:
 *	1 2 1 1 1 1 1 1 1 1 1 1
 *	- 0
 *
 * Since 0 < 4, 0 4 is a valid LIS, at index 1 highest LIS found is 2 and the
 *	index of the preceding value at index 1 is 0.
 *
 * After 12:
 *	1 2 3 1 1 1 1 1 1 1 1 1
 *	- 0 1
 * After 2:
 *	1 2 3 2 1 1 1 1 1 1 1 1
 *	- 0 1 0
 *
 * At 2, the only lower value is 0 at index 0. We increment the 1 found at 0,
 *	not the 3 found at 12, and we write the index of the value preceding 2 (0).
 *
 * After 10:
 *	1 2 3 2 3 1 1 1 1 1 1 1
 *	- 0 1 0 1
 *
 * 10 is like 12, it can have 4 before it. It can also have 2, but the LIS len
 *	at 2 is the same as the LIS len at 4, so we do not replace anything. The
 *	result would be the same.
 *
 * After 6:
 *	1 2 3 2 3 3 1 1 1 1 1 1
 *	- 0 1 0 1 1
 * After 9:
 *	1 2 3 2 3 3 4 1 1 1 1 1
 *	- 0 1 0 1 1 5
 *
 * At 9, we find that 4, 2 and 6 can come before it. 4 and 2 have highest LIS
 *	len of 2 while 6 has 3. So we will write 6's index (5) in lis_sub.
 *
 * End:
 *	1 2 3 2 3 3 4 5 3 5 4 6
 *	- 0 1 0 1 1 5 6 3 6 5 7
 *
 * lis_sub contains the final chain. lis_len contains the length of that chain.
 * To find the values, find the highest value in lis_len. Its index is the
 *	index of the highest value in our LIS. The index of the value preceding it
 *	will be the value found at its index in lis_sub.
*/
static void	lis_compare_loop(t_solver d, t_stack *elem_j, t_stack *elem_i,
			int i)
{
	int	j;

	j = 0;
	while (elem_j != elem_i)
	{
		if (elem_j->val < elem_i->val)
		{
			if (d.lis_len[j] + 1 > d.lis_len[i])
			{
				d.lis_len[i] = d.lis_len[j] + 1;
				d.lis_sub[i] = j;
			}
		}
		j++;
		elem_j = elem_j->next;
	}
}

void	get_lis_values(t_solver d, t_stack *head)
{
	t_stack	*elem_i;
	int		i;

	fill_int_array(d.lis_len, d.num_elem, 1);
	fill_int_array(d.lis_sub, d.num_elem, -1);
	elem_i = head->next;
	i = 1;
	while (elem_i != head)
	{
		lis_compare_loop(d, head, elem_i, i);
		i++;
		elem_i = elem_i->next;
	}
}
