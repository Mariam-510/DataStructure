Implementation of a compact Suffix Tree data structure with Search() operation for any substring.
Each node in the tree contains :
1) Array of pointers to children nodes. The array size equals the alphabet size.
2) The starting index (in the original string) of the characters on the edge going to this node.
 3) The starting index (in the original string) of the suffix ending at this node (used for leaf nodes only, otherwise it should be -1).