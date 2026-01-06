/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_back_cost.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapohlen <rapohlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 22:40:44 by rapohlen          #+#    #+#             */
/*   Updated: 2026/01/06 04:42:10 by rapohlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solver.h"

/*	Searching for B's insert position in A
 *
 * We want to return the index where the elem that comes right after B is in A.
 * This elem in A will need to be rotated to the top of A for B to be inserted.
 *
 * The elem needs to be the smallest value higher than B, or if B will be the
 *	highest value after insertion, the elem after B needs to be A's smallest
 *	value.
 *
 * So as long as we haven't found any value higher than B, look for a strict
 *	minimum.
 * The moment we find any value higher than B, switch to looking for a minimum
 *	which is still higher than B.
*/
static int	get_insert_index(t_stack *stacka, int bval, int alen)
{
	int		min_val;
	int		min_i;
	int		i;

	min_i = 0;
	min_val = stacka->val;
	i = 1;
	while (i < alen)
	{
		stacka = stacka->next;
		if ((min_val < bval && stacka->val < min_val)
			|| (stacka->val > bval && (min_val < bval || stacka->val < min_val)))
		{
			min_i = i;
			min_val = stacka->val;
		}
		i++;
	}
	return (min_i);
}

// A value < 0 implies inverse rotations
//		   > 0		   regular
static void	update_cost(int *tcost, int *rcost, int *rot, int min_cost)
{
	if (tcost[0] == min_cost)
	{
		rot[A] = rcost[0];
		rot[B] = rcost[1];
	}
	else if (tcost[1] == min_cost)
	{
		rot[A] = -rcost[2];
		rot[B] = -rcost[3];
	}
	else if (tcost[2] == min_cost)
	{
		rot[A] = rcost[0];
		rot[B] = -rcost[3];
	}
	else if (tcost[3] == min_cost)
	{
		rot[A] = -rcost[2];
		rot[B] = rcost[1];
	}
}

/*	Cost math
 *
 *	Args:
 * index[A/B]	index of the value that needs to be put at top of A/B
 * len[A/B]		length of A/B
 * rot[A/B]		rots to execute on A/B, replaced if computed cost is new lowest
 *
 *	Rotational Costs (rcost):
 * There are 4 rotational costs.
 *	0/1. Regular rotations in A/B for elem to reach index 0.
 *		 This is simply the index.
 *		 E.g: At index [1], only one [ra]/[rb] is needed to reach top of stack
 *	2/3. Inverse rotations in A/B for elem to reach index 0.
 *		 This is the length - index.
 *		 E.g: At index [2] in a stack of 3 elems, only one [rra]/[rrb] is needed
 *
 *	Total Combined Costs (tcost):
 * There are 4 combined costs.
 *	0. Do regular rotations for both A and B
 *	1. Do inverse rotations for both A and B
 *	2. Do regular rots for A, inverse for B
 *	3. Do inverse rots for A, normal for B
 * 0 and 1 have the advantage of combining into rr or rrr. Because of this, we
 *	only take the highest value between both rotational costs.
 * 2 and 3 cannot be combined into rr/rrr, so we need to add their rotational
 *	costs.
 * We still have to calculate all 4 since 2 and 3 might still win over 1 and 2
 *	despite their disadvantages.
 *
 * The lowest total combined cost is compared to the lowest (so far) cost.
 * If an improvement is found (or we are at the 1st elem), we update the
 *	rotations which will be executed at the end.
*/
static void	compute_cost(int *index, int *len, int *rot, int *lowest_cost)
{
	int	rcost[4];
	int	tcost[4];
	int	min_cost;

	rcost[0] = index[A];
	rcost[1] = index[B];
	rcost[2] = len[A] - index[A];
	rcost[3] = len[B] - index[B];
	tcost[0] = ft_max(rcost[0], rcost[1]);
	tcost[1] = ft_max(rcost[2], rcost[3]);
	tcost[2] = rcost[0] + rcost[3];
	tcost[3] = rcost[2] + rcost[1];
	min_cost = ft_min(ft_min(tcost[0], tcost[1]), ft_min(tcost[2], tcost[3]));
	if (!index[B] || min_cost < lowest_cost)
	{
		lowest_cost = min_cost;
		update_cost(tcost, rcost, rot, min_cost);
	}
}

/*	Cost computing
 *
 * For every element of B, we want to know how many rotations (in A and B)
 *	will be necessary to get that element to where it needs to be in A.
 *
 * The first step is figuring out where B needs to be in A. We have B's index
 *	already, we need to figure A's index (where the elem that should come right
 *	after B currently is in A).
 *
 * Once this is done, with just indexes and total lengths of the stacks, we can
 *	calculate rotation costs for both stacks, both ways. Then we only need to
 *	combine these costs and find the minimum combined cost.
 *
 * That minimum is then compared to the lowest cost we've found thus far. If it
 *	is lower, we simply update the values to execute at the end of the loop.
 *
 * Note 2 things:
 *	1. If we find a combined cost of 0 (only need to PA), we execute instantly
 *	2. If the elem in B is so far from start/end that it mathematically cannot
 *		ever beat the lowest cost, we skip without further calculations
*/
void	compute_next_move(t_stack *stacka, t_stack *stackb, int *len, int *rot)
{
	int		index[2];
	int		lowest_cost;

	index[B] = 0;
	while (index[B] < len[B])
	{
		if (!index[B] || index[B] < lowest_cost
				|| ft_abs(index[B] - len[B]) < lowest_cost)
		{
			index[A] = get_insert_index(stacka, stackb->val, len[A]);
			compute_cost(index, len, rot, &lowest_cost);
			if (!lowest_cost)
				return ;
		}
		stackb = stackb->next;
		index[B]++;
	}
}
