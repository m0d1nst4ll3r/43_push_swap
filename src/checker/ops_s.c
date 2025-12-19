/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ops_s.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapohlen <rapohlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 15:57:51 by rapohlen          #+#    #+#             */
/*   Updated: 2025/12/16 19:13:21 by rapohlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

static void	do_sx(t_stack **stack)
{
	t_stack	*tmp;

	if (!*stack || !(*stack)->next)
		return ;
	tmp = (*stack)->next;
	(*stack)->next = tmp->next;
	tmp->next = *stack;
	*stack = tmp;
}

void	do_sa(t_checker *d)
{
	do_sx(&d->stacka);
}

void	do_sb(t_checker *d)
{
	do_sx(&d->stackb);
}

void	do_ss(t_checker *d)
{
	do_sx(&d->stacka);
	do_sx(&d->stackb);
}
