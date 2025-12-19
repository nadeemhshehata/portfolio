"""
-------------------------------------------------------
[program description]
-------------------------------------------------------
Author:  Nadeem Hassan
ID:      169093285
Email:   hass3285@mylaurier.ca
__updated__ = "2024-10-01"
-------------------------------------------------------
"""
# Imports

from Stack_array import Stack
from Queue_array import Queue
from Priority_Queue_array import Priority_Queue
from List_array import List as ls
# Constants


def array_to_stack(stack, source):
    """
    -------------------------------------------------------
    Pushes contents of source onto stack. At finish, source is empty.
    Last value in source is at bottom of stack,
    first value in source is on top of stack.
    Use: array_to_stack(stack, source)
    -------------------------------------------------------
    Parameters:
        stack - a Stack object (Stack)
        source - a Python list (list)
    Returns:
        None
    -------------------------------------------------------
    """

    for i in reversed(range(len(source))):
        stack.push(source[i])

    source.clear()


def stack_to_array(stack, target):
    """
    -------------------------------------------------------
    Pops contents of stack into target. At finish, stack is empty.
    Top value of stack is at end of target,
    bottom value of stack is at beginning of target.
    Use: stack_to_array(stack, target)
    -------------------------------------------------------
    Parameters:
        stack - a Stack object (Stack)
        target - a Python list (list)
    Returns:
        None
    -------------------------------------------------------
    """
    reverse = []
    while stack.is_empty() == False:
        value = stack.pop()
        reverse.append(value)

    for i in reversed(range(len(reverse))):
        target.append(reverse[i])


def stack_test(source):
    """
    -------------------------------------------------------
    Tests the methods of Stack for empty and
    non-empty stacks using the data in source:
    is_empty, push, pop, peek
    (Testing pop and peek while empty throws exceptions)
    Use: stack_test(source)
    -------------------------------------------------------
    Parameters:
        source - list of data (list of ?)
    Returns:
        None
    -------------------------------------------------------
    """
    my_stack = Stack()

    try:
        my_stack.peek()

    except AssertionError:
        print("peek and pop operations on a empty stack")

    finally:

        for value in source:
            my_stack.push(value)

        for item in my_stack.__iter__():
            print(item)

        while my_stack.is_empty() == False:
            my_stack.pop()

        for item in my_stack.__iter__():
            print(item)


def array_to_queue(queue, source):
    """
    -------------------------------------------------------
    Inserts contents of source into queue. At finish, source is empty.
    Last value in source is at rear of queue,
    first value in source is at front of queue.
    Use: array_to_queue(queue, source)
    -------------------------------------------------------
    Parameters:
        queue - a Queue object (Queue)
        source - a Python list (list)
    Returns:
        None
    -------------------------------------------------------
    """
    for i in (range(len(source))):
        queue.insert(source[i])

    source.clear()


def queue_to_array(queue, target):
    """
    -------------------------------------------------------
    Removes contents of queue into target. At finish, queue is empty.
    Front value of queue is at front of target,
    rear value of queue is at end of target.
    Use: queue_to_array(queue, target)
    -------------------------------------------------------
    Parameters:
        queue - a Queue object (Queue)
        target - a Python list (list)
    Returns:
        None
    -------------------------------------------------------
    """

    while queue.is_empty() == False:
        value = queue.remove()
        target.append(value)


def queue_test(a):
    """
    -------------------------------------------------------
    Tests queue implementation.
  Tests the methods of Queue are tested for both empty and
  non-empty queues using the data in a:
        is_empty, insert, remove, peek, len
    Use: queue_test(a)
    -------------------------------------------------------
    Parameters:
        a - list of data (list of ?)
    Returns:
        None
    -------------------------------------------------------
    """
    q = Queue()

    try:
        q.peek()

    except AssertionError:
        print("peek and pop operations on a empty queue")

    finally:

        for value in a:
            q.insert(value)

        for item in q.__iter__():
            print(item)

        while q.is_empty() == False:
            q.remove()

        for item in q.__iter__():
            print(item)

    # tests for the queue methods go here
    # print the results of the method calls and verify by hand

    return


def array_to_pq(pq, source):
    """
    -------------------------------------------------------
    Inserts contents of source into pq. At finish, source is empty.
    Last value in source is at rear of pq,
    first value in source is at front of pq.
    Use: array_to_pq(pq, source)
    -------------------------------------------------------
    Parameters:
        pq - a Priority_Queue object (Priority_Queue)
        source - a Python list (list)
    Returns:
        None
    -------------------------------------------------------
    """
    for i in (range(len(source))):
        pq.insert(source[i])

    source.clear()


def pq_to_array(pq, target):
    """
    -------------------------------------------------------
    Removes contents of pq into target. At finish, pq is empty.
    Highest priority value in pq is at front of target,
    lowest priority value in pq is at end of target.
    Use: pq_to_array(pq, target)
    -------------------------------------------------------
    Parameters:
        pq - a Priority_Queue object (Priority_Queue)
        target - a Python list (list)
    Returns:
        None
    -------------------------------------------------------
    """
    while pq.is_empty() == False:
        value = pq.remove()
        target.append(value)


def priority_queue_test(a):
    """
    -------------------------------------------------------
    Tests priority queue implementation.
    Test the methods of Priority_Queue are tested for both empty and
    non-empty priority queues using the data in a:
        is_empty, insert, remove, peek
    Use: priority_queue_test(a)
    -------------------------------------------------------
    Parameters:
        a - list of data (list of ?)
    Returns:
        None
    -------------------------------------------------------
    """
    pq = Priority_Queue()
    try:
        pq.peek()

    except AssertionError:
        print("peek and pop operations on a empty priority queue")

    finally:

        for value in a:
            pq.insert(value)

        for item in pq.__iter__():
            print(item)

        while pq.is_empty() == False:
            pq.remove()

        for item in pq.__iter__():
            print(item)

    # tests for the priority queue methods go here
    # print the results of the method calls and verify by hand

    return


def array_to_list(llist, source):
    """
    -------------------------------------------------------
    Appends contests of source to llist. At finish, source is empty.
    Last element in source is at rear of llist,
    first element in source is at front of llist.
    Use: array_to_list(llist, source)
    -------------------------------------------------------
    Parameters:
        llist - a List object (List)
        source - a Python list (list)
    Returns:
        None
    -------------------------------------------------------
    """
    while len(source) != 0:
        value = source.pop(0)
        llist.append(value)

    source.clear()
    return


def list_to_array(llist, target):
    """
    -------------------------------------------------------
    Removes contents of llist into target. At finish, llist is empty.
    Front element of llist is at front of target,
    rear element of llist is at rear of target.
    Use: list_to_array(llist, target)
    -------------------------------------------------------
    Parameters:
        llist - a List object (List)
        target - a Python list (list)
    Returns:
        None
    -------------------------------------------------------
    """

    while not llist.is_empty():
        value = llist.remove(llist[0])
        target.append(value)

    return


def list_test(source):
    """
    -------------------------------------------------------
    Tests List implementation.
    The methods of List are tested for both empty and
    non-empty lists using the data in source
    Use: list_test(source)
    -------------------------------------------------------
    Parameters:
        source - list of data (list of ?)
    Returns:
        None
    -------------------------------------------------------
    """
    lst = ls()

   # Test if the list is initially empty using is_empty
    print("Initial testing with an empty list:")
    if lst.is_empty():
        print("The list is initially empty.")
    else:
        print("The list is NOT initially empty.")

    # Test appending elements from source to the list
    print("\nTesting append method:")
    for value in source:
        lst.append(value)  # This explicitly calls the append method
        print(f"Appended {value} to the list")

    # Iterating through the list and printing elements
    print("\nCurrent list contents after appending elements:")
    for item in lst:
        print(item)

    # Insert a few values at specific positions
    print("\nTesting insert method:")
    for idx, value in enumerate([100, 200, 300]):
        lst.insert(idx, value)  # Insert at the beginning, middle, etc.
        print(f"Inserted {value} at index {idx}")

    # Printing the contents of the list after insertions
    print("\nCurrent list contents after insertions:")
    for item in lst:
        print(item)

    # Check if the list is still empty
    print("\nChecking if the list is empty after appending and inserting elements:")
    if lst.is_empty():
        print("The list is empty.")
    else:
        print("The list is NOT empty.")

    # Testing the count method
    print("\nTesting count method:")
    for value in source:
        count_value = lst.count(value)
        print(f"Value {value} appears {count_value} time(s) in the list.")

    # Testing the max method
    print("\nTesting max method:")
    try:
        max_value = lst.max()
        print(f"Maximum value in the list: {max_value}")
    except AssertionError:
        print("Max operation raised an AssertionError (likely due to an empty list).")

    # Testing the min method
    print("\nTesting min method:")
    try:
        min_value = lst.min()
        print(f"Minimum value in the list: {min_value}")
    except AssertionError:
        print("Min operation raised an AssertionError (likely due to an empty list).")

    # Testing index method
    print("\nTesting index method:")
    for value in source:
        index_value = lst.index(value)
        print(f"Value {value} is at index {index_value} in the list.")

    # Testing find method
    print("\nTesting find method:")
    for value in source:
        found_value = lst.find(value)
        if found_value is not None:
            print(f"Found {found_value} in the list.")
        else:
            print(f"Value {value} not found in the list.")

    # Testing contains method
    print("\nTesting __contains__ method:")
    for value in source:
        if value in lst:
            print(f"Value {value} is in the list.")
        else:
            print(f"Value {value} is NOT in the list.")

    # Removing elements by value (not by index)
    print("\nRemoving elements by value from the list:")
    for value in source:
        try:
            lst.remove(value)  # Remove based on the key (value)
            print(f"Removed: {value}")
        except ValueError:
            print(f"Value {value} could not be found for removal.")

    # Checking the list after removal
    print("\nCurrent list contents after removal:")
    for item in lst:
        print(item)

    # Confirming the list is empty
    print("\nChecking if the list is empty after removing all elements:")
    if lst.is_empty():
        print("The list is now empty.")
    else:
        print("The list is NOT empty.")

    return
