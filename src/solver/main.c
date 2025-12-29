/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapohlen <rapohlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 14:52:48 by rapohlen          #+#    #+#             */
/*   Updated: 2025/12/23 12:10:05 by rapohlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solver.h"

static void	init_op(char *op_strings[N_OP], void (*op_funcs[N_OP])(t_solver *))
{
	op_strings[SA_KEY] = SA_STR;
	op_strings[SB_KEY] = SB_STR;
	op_strings[RA_KEY] = RA_STR;
	op_strings[RB_KEY] = RB_STR;
	op_strings[RR_KEY] = RR_STR;
	op_strings[RRA_KEY] = RRA_STR;
	op_strings[RRB_KEY] = RRB_STR;
	op_strings[RRR_KEY] = RRR_STR;
	op_strings[PA_KEY] = PA_STR;
	op_strings[PB_KEY] = PB_STR;
	op_funcs[SA_KEY] = do_sa;
	op_funcs[SB_KEY] = do_sb;
	op_funcs[RA_KEY] = do_ra;
	op_funcs[RB_KEY] = do_rb;
	op_funcs[RR_KEY] = do_rr;
	op_funcs[RRA_KEY] = do_rra;
	op_funcs[RRB_KEY] = do_rrb;
	op_funcs[RRR_KEY] = do_rrr;
	op_funcs[PA_KEY] = do_pa;
	op_funcs[PB_KEY] = do_pb;
}

static void	init_prog(t_solver *d, int ac, char **av)
{
	d->av = av;
	d->num_elem = ac - 1;
	init_op(d->op_strings, d->op_funcs);
	d->stacka = NULL;
	d->stackb = NULL;
	d->op_list = NULL;
	d->lis_sub = NULL;
	d->lis_len = malloc(sizeof(*d->lis_len) * d->num_elem);
	if (!d->lis_len)
		error_out(*d);
	d->lis_sub = malloc(sizeof(*d->lis_len) * d->num_elem);
	if (!d->lis_sub)
		error_out(*d);
}

int	main(int ac, char **av)
{
	t_solver	data;

	if (ac < 2)
		return (0);
	init_prog(&data, ac, av);
	build_stack(&data);
	if (data.num_elem > 1 && is_reverse_sorted(data.stacka))
		do_sa(&data);
	write_lis(); // TODO
	// pivot
	// push ahead
	// push back
	// rotate back into order
	optimize_op_list(&data.op_list);
	print_op_list(data.op_list, data.op_strings);
}
