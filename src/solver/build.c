/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapohlen <rapohlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 22:48:42 by rapohlen          #+#    #+#             */
/*   Updated: 2026/01/13 13:38:05 by rapohlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solver.h"

static int	is_duplicate(t_stack *head, int val)
{
	t_stack	*cur;

	cur = head;
	while (1)
	{
		if (head->val == val)
			return (1);
		head = head->next;
		if (head == cur)
			return (0);
	}
}

void	build_stack(t_solver *d)
{
	int		i;
	int		val;
	t_stack	*new;

	i = 1;
	while (d->av[i])
	{
		if (ft_atoi_strict(d->av[i], &val)
			|| (d->stacka && is_duplicate(d->stacka, val)))
			error_out(*d);
		new = stack_new(val);
		if (!new)
			error_out(*d);
		stack_add_back(&d->stacka, new);
		i++;
	}
}
