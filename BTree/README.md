# Study Binary Trees

[中文](./README_CN.md)

This folder contains two binary tree example programs, each demonstrating a different tree type and operation set.

## `BTree.cpp` / `BTree.exe`

Features:
- Builds a general binary tree from level-order input, where `#` represents an empty node.
- Supports preorder, inorder, and postorder traversals.
- Calculates and prints the number of nodes and the height of the tree.

Details:
- Uses a queue to construct the tree level by level.
- Node values are stored as characters (`char`).
- The program runs from `main()` and prompts for level-order input before printing traversal results.

## `BST.cpp` / `BST.exe`

Features:
- Builds a binary search tree (BST) from integer input.
- Reads an integer count `cnt`, then reads `cnt` integer values and inserts them into the BST.
- Outputs all nodes using inorder traversal, resulting in sorted ascending order.

Details:
- Insertion is implemented recursively.
- The `Find()` function supports value lookup in the BST.
- The program runs from `main()`, prompts for input, and prints the sorted traversal output.

### Usage Suggestions

1. Compile `BTree.cpp` and `BST.cpp` separately.
2. Run `BTree.exe` to test general binary tree creation and traversal.
3. Run `BST.exe` to test BST insertion and inorder traversal.
