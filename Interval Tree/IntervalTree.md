Implementation of dynamic interval tree data structure. An interval is two integers.
The underlying binary search tree structure is implemented using an unbalanced binary search tree.
The dynamic interval tree supports InsertInterval(), DeleteInterval(), SearchInterval().
SearchInterval() returns all intervals overlapping with the parameter interval, by first getting one overlapping interval, then deleting it, and so on. Then, all such intervals must be inserted again in the tree to restore its status.