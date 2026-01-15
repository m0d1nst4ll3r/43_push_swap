*This project has been created as part of the 42 curriculum by rapohlen*

[Subject](https://cdn.intra.42.fr/pdf/pdf/192339/en.subject.pdf)

## Description

Program receives a list of numbers as arguments :
- Numbers must fit in an int and cannot be duplicates.
- In case of bad number or duplicate, print "Error".
- In case of missing arguments, return 0.

The numbers are added to a "stack" (a list of ints), this is stack A. There is a stack B, originally empty.
- The first argument ends up at the top (beginning) of stack A. The last argument ends up at the bottom (end).

They then need to be sorted in ascending order, with 8 different operations:
- pa
	- If B is not empty, take its first (topmost) element, add it to the beginning (top) of A
- pb
	- \- (same, A->B)
- sa
	- If A has more than one element, swap its position with the second element.
- sb
	- \- (same, for B)
- ra
	- If A has more than one element, move its first (topmost) element to the end (bottom)
- rb
	- \-
- rra
	- If A has more than one element, move its last (bottom) element to the beginning (top)
- rrb
	- \-

There are 3 more operations that are combinations of existing operations:
- ss
	- sa + sb
- rr
	- ra + rb
- rrr
	- rra + rrb

The program has to print a list of operations that will sort stack A in ascending order completely. Stack B has to be empty. The less operations, the better.

For 100% completion, program has to sort:
- 3 numbers     in <= 2 moves
- 5 numbers     in <= 12 moves
- 100 numbers   in <= 700 moves
- 500 numbers   in <= 5500 moves

## Instructions

1. Run `make` (checker is also compiled)
2. `./push_swap [...]`
3. Examples for checking:
- `ARG="2 1 3"; ./push_swap $ARG | wc -l`
- `ARG="2 1 3"; ./push_swap $ARG | ./checker $ARG`

See resources for tester/visualizer.

## Resources

Algorithm description - https://medium.com/@dansylvain84/my-implementation-of-the-42-push-swap-project-2706fd8c2e9f

LIS Algorithm (only length) - https://www.youtube.com/watch?v=on2hvxBXJH4

LIS Algorithm (finding values) - https://www.youtube.com/watch?v=E6us4nmXTHs

Random Number Generator - https://www.calculatorsoup.com/calculators/statistics/random-number-generator.php

Tester - https://github.com/SimonCROS/push_swap_tester

Visualizer - https://github.com/o-reo/push_swap_visualizer

AI use: none
