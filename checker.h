/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapohlen <rapohlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 12:50:10 by rapohlen          #+#    #+#             */
/*   Updated: 2025/12/16 18:53:04 by rapohlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHECKER_H
# define CHECKER_H

# define SA			"sa"
# define SB			"sb"
# define SS			"ss"
# define RA			"ra"
# define RB			"rb"
# define RR			"rr"
# define RRA		"rra"
# define RRB		"rrb"
# define RRR		"rrr"
# define PA			"pa"
# define PB			"pb"
# define K_SA		0
# define K_SB		1
# define K_SS		2
# define K_RA		3
# define K_RB		4
# define K_RR		5
# define K_RRA		6
# define K_RRB		7
# define K_RRR		8
# define K_PA		9
# define K_PB		10
# define N_OP		11

# define ERROR		"Error\n"
# define OK			"OK\n"
# define KO			"KO\n"

# include <stdlib.h>
# include "libft.h"

typedef struct s_stack
{
	int				val;
	struct s_stack	*next;
}	t_stack;

typedef struct s_op
{
	int			op;
	struct s_op	*next;
}	t_op;

typedef struct s_checker
{
	t_stack	*stacka;
	t_stack	*stackb;
	t_op	*op;
	char	*op_list[N_OP];
	void	(*ops[N_OP])(struct s_checker *);
}	t_checker;

// util.c
int		find_op(char *s, char **op_list);
int		ft_atoi_strict(char *s, int *n);
t_stack	*get_last(t_stack *stack);
t_stack	*get_before_last(t_stack *stack);

// ops.c ops2.c
void	do_sa(t_checker *d);
void	do_sb(t_checker *d);
void	do_ss(t_checker *d);
void	do_ra(t_checker *d);
void	do_rb(t_checker *d);
void	do_rr(t_checker *d);
void	do_rra(t_checker *d);
void	do_rrb(t_checker *d);
void	do_rrr(t_checker *d);
void	do_pa(t_checker *d);
void	do_pb(t_checker *d);

// checker.c
int		build_stack(t_stack **stack, char **av);
int		check_duplicates(t_stack *stack);
int		read_input(t_op **op, char **op_list);
void	apply_input(t_checker *d);
int		is_sorted(t_stack *stack);

// exit.c
void	exit_prog(t_checker d);
void	error_out(t_checker d);

#endif
