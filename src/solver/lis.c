/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lis.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapohlen <rapohlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 14:49:07 by rapohlen          #+#    #+#             */
/*   Updated: 2026/01/04 15:20:38 by rapohlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solver.h"

/*	Longest Increasing Subsequence
 *
 * The stack contains a LIS: the longest sequence of numbers that keep going up.
 * We want to figure what it is since it is already sorted, to keep it in stk A.
 *
 * Ex:
 *	0 4 12 2 10 6 9 13 3 11 7 15
 * LIS:
 *	0 4         6 9 13        15
 *
 * We also want to search for this LIS circularly.
 *
 * Ex:
 *	3 4 0 1 2
 * LIS (non-circular):
 *	    0 1 2
 * LIS (circular):
 *	    0 1 2 - 3 4
 *
 * This is because we can easily rotate the stack.
 *
 * There are 2 simple algorithms to find a LIS:
 *	1. Finding LIS length in a given set of numbers (fast algorithm)
 *	2. Finding LIS values in a given set of numbers (slow algorithm)
 *
 * Since we don't just need the length, but also to know the values themselves,
 *	we need algorithm #2. But for this algorithm to work circularly, we have to
 *	apply it to each sub-set of our circular stack.
 *
 * Ex:
 *	3 4 0 1 2
 * Need to test:
 *	3 4 0 1 2
 *	4 0 1 2 3
 *	0 1 2 3 4
 *	1 2 3 4 0
 *	2 3 4 0 1
 *
 * Since algorithm #2 is slow but #1 is fast, we can instead use algorithm #1
 *	on each subset, then memorize which subset had the highest LIS length.
 * We can then run algorithm #2 only on the subset that had the highest LIS len
 *	to get the exact values in the LIS.
 * We then flip a boolean flag for each of the elements representing the values.
 * These elements will be skipped during the initial mass push to B.
 *
 * For descriptions of algorithm #1 and #2, see their respective functions.
 */
void	write_lis(t_solver d);
{
	t_stack	*lis_addr;

	lis_addr = get_lis_addr(d.stacka, d.lis_len);
	get_lis_values(d, lis_addr);
	write_boolean_flags(lis_addr, d.lis_len, d.lis_sub, d.num_elem);
}
