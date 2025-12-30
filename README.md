# 43\_push\_swap

Checker done. Pretty useless, but hey.

For checker, used 1-way chained lists. Also used a 1-way list for operations.

I can't see the upside of a 2-way list. But I haven't looked at sorting algorithms yet...

Re-using the same skeleton as the checker for the actual prog is probably a good idea. Implementing functions to copy the stacks will be useful to sort several times using different algorithms and compare how long the operations list is. Same thing for op list (having several will be useful).

All that's left now, apart from re-using everything from checker to make a solver version, is to look at sorting, which is the ACTUAL hard part.

### How-to

Strategy I'm going to follow:

https://medium.com/@dansylvain84/my-implementation-of-the-42-push-swap-project-2706fd8c2e9f

Gonna try to implement this since it seems "good enough". We'll see what we do after that. Turn in, or try to do even better. Or try different ways just to compare.

Don't really need a 2-way list for this. 1-way works just fine.

Another strategy I heard about:

Divide your numbers in 3 groups, one lowest, one highest, one middle group. Start pushing to B, doing basically "ra ra pb ra ra ra pb" and push members of the 3rd group to the top of B, and members of the 2nd group to the bottom of B. Only the lowest values are left in A - push them all to B until 2 values remain in A, swap them if needed then start pushing to A - this way B is already sorta-sorted. You can then start pushing back to A and sorting the values, calculating the lowest cost operations (not sure on the details but there you go).

### Tester

https://github.com/SimonCROS/push_swap_tester

### Progress

All done except:
- LIS building (halfway done, got lis addr, need to calculate actual lis and set bool flags)
- Pivot calculating (should be easy, do a bubble sort)
- First push (should be very easy, if no bool flag then pb if < pivot and pb rb otherwise)
- Push back (this is most of what's remaining - about half of the project, this is fairly complex)
- Rotate back (this is very easy)
- Optimize list (strictly speaking this is done but I can optimize further)

Final touch that I can work on right now instead of delaying it:
- My current system has a key for each action
- Instead, I can use bit masking
- pa 1, pb 2, sa 4, sb 8, ra 16, rb 32, rra 64, rrb 128
- Handy because you only have 8 actions, rr, rrr and ss are just combinations of 2 actions
- E.g rr is ra + rb (0b00110000)
- There is absolutely no point in doing this rather than my current system other than swag
- One fringe advantage to this is testing values faster instead of going `op == RA_KEY || op == RB_KEY` you go `op & (RA | RB)`, very cool

PS: In the end, not gonna do this, because it involves rewriting too much. Rip swag. For posterity this is what the macros would've looked like. My dreams are shattered.
```# define PA			0b00000001
# define PB			0b00000010
# define SA			0b00000100
# define SB			0b00001000
# define RA			0b00010000
# define RB			0b00100000
# define RRA		0b01000000
# define RRB		0b10000000
# define SS			SA | SB
# define RR			RA | RB
# define RRR		RRA | RRB```
