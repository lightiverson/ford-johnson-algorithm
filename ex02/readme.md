# Ford–Johnson algorithm

* What’s an in place sorting algorithm?
    * In computer science, an in-place algorithm is an algorithm that operates directly on the input data structure without requiring extra space proportional to the input size.
* What are comparison sorts?
    * A comparison sort is a type of sorting algorithm that only reads the list elements through a single abstract comparison operation (often a "less than or equal to" operator or a three-way comparison) that determines which of two elements should occur first in the final sorted list.
* Do we use Jacobshthall to determine which number to insert?
    * You use Jacobsthall to determine which index of the PEND array to insert.
* How do you determine the insertion area? Is it only three for Jacobsthall numbers with an N of 8, because of 2log8 = 3?
* What about the non Jacobsthall numbers, is the insertion area everything up to its own label?
    * For non Jacobsthall numbers the insertion area is everything up to its own index.