# Study Linear List

[中文](./README_CN.md)

This folder contains example programs related to linear lists:

## File Structure

```
./
├── SequenceList.cpp    # Sequential list (array implementation)
├── SequenceList.exe
├── README.md
└── README_CN.md
```

## Sequential List: `SequenceList.cpp`

Features:
- Implements basic operations of sequential list: initialization, insertion, deletion, search, and traversal.
- Manages student information with name and student ID fields.
- Uses an array as the underlying storage structure with a maximum capacity of 5 elements.

Operations:
- **Initialize**: `MakeEmpty()` - Creates an empty sequential list with `Last` pointer set to -1.
- **Input**: `Input_List()` - Reads student information from console, ends when `#` is entered as name.
- **Display**: `show_seqlist()` - Traverses and prints all student information in the list.
- **Search**: `Find()` - Searches for a student by name or student ID, returns position.
- **Insert**: `Insert()` - Inserts new student information before the specified position.
- **Delete**: `Delete()` - Deletes student information at the specified position.

Details:
- Uses a struct to store student data with name and ID arrays.
- Position starts from 1, following common convention.
- The program runs from `main()` and demonstrates insertion, deletion, and search operations.

## Other Files

Future implementations may include:
- Singly Linked List
- Doubly Linked List
- Circular Linked List

### Usage Suggestions

1. Compile: `g++ SequenceList.cpp -o SequenceList.exe`
2. Run: `SequenceList.exe`
3. Follow prompts to enter student names and IDs (enter `#` to finish).