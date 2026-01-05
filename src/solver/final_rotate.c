/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   final_rotate.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapohlen <rapohlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 16:34:04 by rapohlen          #+#    #+#             */
/*   Updated: 2026/01/05 16:53:46 by rapohlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solver.h"

static int	get_min_val_i(t_stack *head, int num_elem)
{
	int		min_i;
	int		min_val;
	int		i;

	i = 1;
	min_i = 0;
	min_val = head->val;
	head = head->next;
	while (i < num_elem)
	{
		if (head->val > min_val)
		{
			min_val = head->val;
			min_i = i;
		}
		head = head->next;
		i++;
	}
	return (min_i);
}

static void	do_final_rotate(t_solver *d, int index, int num_elem)
{
	if (index <= num_elem / 2)
	{
		while (index > 0)
		{
			do_op(d, RA);
			index--;
		}
	}
	else
	{
		while (index < num_elem)
		{
			do_op(d, RRA);
			index++;
		}
	}
}

void	final_rotate(t_solver *d)
{
	int	index;

	index = get_final_rotate_index(d->stacka, d->num_elem);
	do_final_rotate(d, index, d->num_elem);
}
