/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapohlen <rapohlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 16:53:36 by rapohlen          #+#    #+#             */
/*   Updated: 2026/01/06 15:27:09 by rapohlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solver.h"

static void	free_stack(t_stack *begin)
{
	t_stack	*cur;
	t_stack	*last;

	if (!begin)
		return ;
	cur = begin;
	while (1)
	{
		last = cur;
		cur = cur->next;
		free(last);
		if (cur == begin)
			return ;
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

void	exit_prog(t_solver d, unsigned char retval)
{
	if (d.lis_len)
		free(d.lis_len);
	if (d.lis_sub)
		free(d.lis_sub);
	free_stack(d.stacka);
	free_stack(d.stackb);
	free_op(d.op_list);
	exit(retval);
}

void	error_out(t_solver d)
{
	ft_fprintf(2, ERROR);
	exit_prog(d, 1);
}
