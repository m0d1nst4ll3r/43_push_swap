/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapohlen <rapohlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 16:03:44 by rapohlen          #+#    #+#             */
/*   Updated: 2025/12/16 18:56:04 by rapohlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

static void	free_stack(t_stack *stack)
{
	t_stack	*cur;
	t_stack	*last;

	cur = stack;
	while (cur != stack)
	{
		last = cur;
		cur = cur->next;
		free(last);
	}
}

static void	free_op(t_op *op)
{
	t_op	*last;

	while (op)
	{
		last = op;
		op = op->next;
		free(last);
	}
}

void	exit_prog(t_checker d)
{
	free_stack(d.stacka);
	free_stack(d.stackb);
	free_op(d.op);
	exit(1);
}

void	error_out(t_checker d)
{
	ft_fprintf(2, ERROR);
	exit_prog(d);
}
