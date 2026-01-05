/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_back.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapohlen <rapohlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 20:12:23 by rapohlen          #+#    #+#             */
/*   Updated: 2026/01/05 21:18:49 by rapohlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solver.h"

void	push_back(t_solver *d)
{
}

/*	Push back explanation
 *
 * We want to push values from B to A, but we want to do it somewhat efficiently
 * To do so, we calculate the amount of operations that each value requires to
 *	be placed at the right spot in A, and will move the value with the lowest
 *	cost
 * We do not calculate all the costs for all the values, e.g a value already
 *	5 spots away from the top of B (cost of 5 rotations + 1 push) can never beat
 *	a 4-cost value
 *
 * The cost calculation goes like this:
 *	- At least 1 operation is always needed (pa)
 *	- How far is the value from the top of stack B? Both ways (for rr, rrr)
 *	- How far is the value right after it from the top of stack A? Both ways
 *	- How many operations as a result? Same-way rotations can be merged
 * Then, compare that value to the lowest cost found thus far
 * If cost is 1 (can just pa), do it right away
 * If value is so far from the top of B that it can't beat the lowest cost,
 *	give up (we proceed incrementally, both ways at once e.g 1 down, 1 up,
 *	2 down, 2 up, 3 down, 3 up etc...)
 *
 *
 * How to ACTUALLY do this. Hahhhhhhhhhhhhhhhhhhhhhhhhhhhhhhh...
 *
 * Summarizing what we have here:
 *
 * Stack A, can never be empty (at least 2 elements in there)
 * Stack B, contains a bunch of random values, but 1st half will all be > to 2nd half
 *
 * Task is to go through the ENTIRETY of stack B, ALL OF IT, and for every single node,
 *	calculate the amount of operations that said node will require to be moved to A
 *	AT THE RIGHT SPOT, meaning right before the first higher value in A
 * Do remember that possibly there is no higher value in A, in which case all we have
 *	to do is pa+ra to put it where it "belongs"
 *
 * Now, once we have calculated all the costs, we take the smallest, and we "execute" it
 * Meaning we do what needs to be done to put it where it needs to be put
 *
 * Couple things there:
 *	1. If the cost is 1 (just have to do pa), it means the first value of stack B
 *		belongs at the top of stack A without needing to rotate anything
 *	   This obviously means that we should just do this right away, as no other value
 *		can beat this.
 *	2. If the value is so far from the top of B that it can't beat the lowest cost
 *		found so far, there's no use in doing anything more, this value loses.
 *	3. We have to account for similar rotations in A and B and count their cost as
 *		1 instead of 1+1
 *
 * We can consider these steps for this entire operation:
 *	0. We do these steps repeatedly in a while loop as long as there's something in B
 *	   We know the value and its index.
 *	1. Using the value's index, figure out how far it is from position 0 (both ways)
 *	   If both distances are >= the lowest cost found so far (-1 for the pa)
 *		, we can give up already and move on to the next value.
 *	   Ex: lowest cost so far is 4 (say rr rr rb pa), next value needs 3+ rb or 3+ rrb
 *			= give up, pointless
 *	   If not, move on to step 2 (and keep in memory both distances)
 *	2. Using the value itself, search what would be the first higher value in A
 *	   We need its index and how far it is from position 0 of A (both ways)
 *	   Once again if both ways are >= lowest cost found so far (-1 again), give up
 *	3. Use a combination of R for A and B and RR for A and B to calculate the one that
 *		yields the smallest value
 *	   Basically we just take the highest of the two same-way values for A and B
 *		and compare them together, take the smallest, and compare that to the lowest
 *		cost found so far. If it is lower, update cost & memorize index, and continue
 *	0. After the loop, execute the required actions for the lowest cost
 *	It can be interesting to also memorize what actions to be done for lowest cost
 *	 rather than having to recalculate everything.
 *	Because of the sheer amount of variables, you might need a bona fide structure
 *	 in order to obey norm constraints.
*/
