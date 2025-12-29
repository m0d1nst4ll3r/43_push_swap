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
