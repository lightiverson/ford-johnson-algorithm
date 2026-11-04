# Merge-insertion sort (Ford–Johnson algorithm)

Write a program to sort a positive integer sequence. Your program must use a merge-insert algorithm also known as the Ford-Johnson algorithm.

While the better known algorithms are designed to be fast or memory efficient, Merge-insertion sort is concerned with minimizing comparisons. A comparison is something as simple as checking if `a < b`.

The way the algorithm manages this is pretty interesting. One of the steps of the algorithm is to use binary search to determine the position at which an element should be inserted in a sub array (created in another step of the algorithm). Specifically, it uses binary search on sub arrays with a length of one less than a power of two.

What's cool about this is that binary search on arrays of these specific sizes is most efficient (from the point of view of worst case analysis).

For example, looking for an element in an array with a length of 8 (2^3) requires the same number of comparisons as looking in an array with a length of 15 ((2^4) - 1).

#### Grade: 100/100

## Resources

https://github.com/decidedlyso/merge-insertion-sort

https://github.com/PunkChameleon/ford-johnson-merge-insertion-sort

https://codereview.stackexchange.com/questions/116367/ford-johnson-merge-insertion-sort

https://stackoverflow.com/questions/27751132/how-does-merge-insertion-sort-work

https://warwick.ac.uk/fac/sci/dcs/teaching/material-archive/cs341/fj.pdf

https://oeis.org/A001768
