/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_back.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapohlen <rapohlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 20:12:23 by rapohlen          #+#    #+#             */
/*   Updated: 2026/01/06 04:52:57 by rapohlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solver.h"

static int	get_stack_len(t_stack *stack)
{
	int		i;
	t_stack	*iter;

	i = 1;
	iter = stack->next;
	while (iter != stack)
	{
		iter = iter->next;
		i++;
	}
	return (i);
}

// A value < 0 implies inverse rotations
//		   > 0		   regular
static void	execute_rotations(t_solver *d, int amount, char rop, char rrop)
{
	while (amount)
	{
		if (amount < 0)
		{
			do_op(d, rrop);
			amount++;
		}
		else if (amount > 0)
		{
			do_op(d, rop);
			amount--;
		}
	}
}

/*	Pushing Back To A
 *
 * We push everything in B back to A with rotations to insert elements in the
 *	right positions.
 *
 * We go over every element in B and move the one which requires the least
 *	amount of rotations (taking into account rr/rrr optimizations).
 *
 * Then we start over for the next move, until there is nothing left in B to
 *	push.
 *
 * See push_back_cost.c for cost computing.
*/
void	push_back(t_solver *d)
{
	int	len[2];
	int	rot[2];

	len[A] = get_stack_len(d->stacka);
	len[B] = get_stack_len(d->stackb);
	while (len[B])
	{
		compute_next_move(d->stacka, d->stackb, len, rot);
		execute_rotations(d, rot[A], RA, RRA);
		execute_rotations(d, rot[B], RB, RRB);
		do_op(d, PA);
		len[A]++;
		len[B]--;
	}
}
