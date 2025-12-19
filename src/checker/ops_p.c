/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ops_p.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapohlen <rapohlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 18:10:49 by rapohlen          #+#    #+#             */
/*   Updated: 2025/12/16 18:11:49 by rapohlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

static void	do_px(t_stack **stack_from, t_stack **stack_to)
{
	t_stack	*tmp;

	if (!*stack_from)
		return ;
	tmp = *stack_from;
	*stack_from = (*stack_from)->next;
	tmp->next = *stack_to;
	*stack_to = tmp;
}

void	do_pa(t_checker *d)
{
	do_px(&d->stackb, &d->stacka);
}

void	do_pb(t_checker *d)
{
	do_px(&d->stacka, &d->stackb);
}
