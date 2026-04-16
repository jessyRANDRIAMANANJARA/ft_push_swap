# ft_push_swap
stack sort
Documentation : 
- https://cdn.intra.42.fr/pdf/pdf/201834/en.subject.pdf (et et instruction a suivre)
- https://openclassrooms.com/fr/courses/7527306-decouvrez-le-fonctionnement-des-algorithmes/7760669-calculez-la-complexite-algorithmique (complexity algorithme)
- https://info.blaisepascal.fr/nsi-complexite-dun-algorithme/ (complexity algorithme)






Deroulement de l'algorithme : 
How --simple works (O(n²))
The --simple flag runs push_swap() in simple_sort.c.

Key steps:

Pushes all but 3 values from stack a to stack b with repeated pb.
Sorts the remaining 3 values in a with tiny_sort().
Re-inserts values from b back into a one by one:
find_cheapest_limited() scans candidates in b
computes the best insertion position in a with find_insert_position()
rotates a and b to bring those nodes to top
pushes with pa
Does a final rotation so the smallest element is on top.
Why O(n²)?

Each reinsertion from b scans parts of a and b to calculate cost.
There are O(n) reinserts and each cost computation is O(n), so total is quadratic.
How --medium works (O(n√n))
The --medium flag runs medium_sort() in medium_sort.c.

Key steps:

assign_final_index() converts every node to its rank in the sorted order.
push_buckets() moves values from a to b in bucket ranges of ranked indices.
It finds the next bucket target in a
rotates a to that item
pushes it to b
optionally rotates b to keep smaller bucket values nearer the top
After only 3 remain in a, tiny_sort() sorts them.
Then it moves values back from b to a:
move_back_fast() computes the best b node to return
uses combined rotations rr / rrr when possible
pushes the cheapest item back to a
Why O(n√n)?

get_bucket_size() chooses bucket size based on len
splitting into buckets reduces the number of expensive shifts
overall work is less than quadratic and is intended to behave like O(n√n) for medium-sized input
How --complex works (O(n log n))
The --complex flag runs radix_sort() in complex_sort.c.

Key steps:

assign_final_index() ranks each node by sorted order.
Computes max_bits from the largest final index.
For each bit from least significant to most:
scans all of a
pushes values whose bit is 0 to b
rotates values whose bit is 1 within a
then pushes all b back to a
Special-case small sizes:
len 2, 3, or 5 use direct small-sort helpers instead of radix loops
Why O(n log n)?

It is binary radix sorting on the rank indices.
There are O(log n) bit passes and each pass processes O(n) elements.
So overall complexity is O(n · bits) = O(n log n).