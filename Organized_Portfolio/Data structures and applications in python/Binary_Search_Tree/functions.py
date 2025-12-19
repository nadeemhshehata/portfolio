"""
-------------------------------------------------------
[program description]
-------------------------------------------------------
Author:  Nadeem Hassan
ID:      169093285
Email:   hass3285@mylaurier.ca
__updated__ = "2024-11-12"
-------------------------------------------------------
"""
# Imports
from Food import Food
from BST_linked import BST
from Letter import Letter
from Stack_array import Stack
from Queue_array import Queue
from Priority_Queue_array import Priority_Queue
from enum import Enum

# Constants

# Enumerated constant
MIRRORED = Enum('MIRRORED',
                {'IS_MIRRORED': "is a mirror", 'TOO_MANY_LEFT': "too many characters in L",
                 'TOO_MANY_RIGHT': "too many characters in R", 'MISMATCHED': "L and R don't match",
                 'INVALID_CHAR': "invalid character", 'NOT_MIRRORED': "no mirror character"})


def hash_table(slots, values):
    """
    -------------------------------------------------------
    Print a hash table of a set of values. The format is:
Hash     Slot Key
-------- ---- --------------------
     695    2 Lasagna, 7
    1355    4 Butter Chicken, 2
    Do not create an actual Hash_Set.
    Use: hash_table(slots, values)
    -------------------------------------------------------
    Parameters:
       slots - the number of slots available (int > 0)
       values - the values to hash (list of ?)
    Returns:
       None
    -------------------------------------------------------
    """

    print("Hash     Slot Key")
    print("-------- ---- --------------------")
    for each in values:
        hsh = hash(each)
        slot = hsh % 7
        key = each.key()
        print("{:8}{:5} {}".format(hsh, slot, key))

    return


def do_comparisons(file_variable, bst):
    """
    -------------------------------------------------------
    Retrieves every letter in file_variable from bst. Generates
    comparisons in bst objects. Each Letter object in bst contains
    the number of comparisons found by searching for that Letter
    object in file_variable.
    Use: do_comparisons(file_variable, bst)
    -------------------------------------------------------
    Parameters:
        file_variable - the already open file containing data to evaluate (file)
        bst - the binary search tree containing 26 Letter objects
            to retrieve data from (BST)
    Returns:
        None
    -------------------------------------------------------
    """
    # Zeroes out all comparison values in tree nodes
    for node in bst:
        node.comparisons = 0

    line = file_variable.readline()
    lines = []

    while line != '':
        line = line.strip()
        lines.append(line)
        line = file_variable.readline()

    for line in lines:
        for letter in line:
            if letter.isalpha():
                temp_letter = Letter(letter.upper())
                bst.retrieve(temp_letter)

    file_variable.close()
    return


def comparison_total(bst):
    """
    -------------------------------------------------------
    Sums the comparison values of all Letter objects in bst.
    Use: total = comparison_total(bst)
    -------------------------------------------------------
    Parameters:
        bst - a binary search tree of Letter objects (BST)
    Returns:
        total - the total of all comparison fields in the bst
            Letter objects (int)
    -------------------------------------------------------
    """
    val = bst.inorder()
    total = 0

    for letter in val:
        total += letter.comparisons

    return total


def letter_table(bst):
    """
    -------------------------------------------------------
    Prints a table of letter counts for each Letter object in bst.
    Use: letter_table(bst)
    -------------------------------------------------------
    Parameters:
        bst - a binary search tree of Letter objects (BST)
    Returns:
        None
    -------------------------------------------------------
    """

    letters = bst.inorder()
    total = 0

    for l in letters:
        total += l.count

    print("Letter Count/Percent Table")
    print()
    print("Total Count: {:,}".format(total))
    print()
    print("Letter  Count       %")
    print("---------------------")
    if total != 0:
        for l in letters:
            per = l.count / total * 100
            print("{:>4s}{:>7,d}{:9.2f}%".format(l.letter, l.count, per))
    else:
        for l in letters:
            print("{:>4s}{:>7,d}".format(
                l.letter, l.count))

    return


def clean_list(values):
    """
    -------------------------------------------------------
    Removes all duplicate values from a list: values contains
    only one copy of each of its integers. The order of values
    must be preserved.
    Use: clean_list(values)
    -------------------------------------------------------
    Parameters:
        values - a list of integers (list of int)
    Returns:
        None
    -------------------------------------------------------
    """
    org_list = []
    for i in range(len(values)):
        if values[i] not in org_list:
            org_list.append(values[i])
    print(org_list)


def list_subtraction(minuend, subtrahend):
    """
    -------------------------------------------------------
    Alters the contents of minuend so that it does not contain
    any values in subtrahend.
    i.e. the values in the first list that appear in the second list
    are removed from the first list.
    Use: list_subtraction(minuend, subtrahend)
    -------------------------------------------------------
    Parameters:
        minuend - a list of values (list)
        subtrahend - a list of values to not include in difference (list)
    Returns:
        None
    ------------------------------------------------------
    """
    i = 0
    while i < len(minuend):
        if minuend[i] in subtrahend:
            del minuend[i]
        else:
            i += 1
    print(minuend)


def dsmvwl(string):
    """
    -------------------------------------------------------
    Disemvowels a string. out contains all the characters in s
    that are not vowels. ('y' is not considered a vowel.) Case is preserved.
    Use: out = dsmvwl(string)
    -------------------------------------------------------
    Parameters:
       string - a string (str)
    Returns:
       out - string with the vowels removed (str)
    -------------------------------------------------------
    """
    vowels = "aeiouAEIOU"
    fixed_str = ""
    for character in string:
        if character not in vowels:
            fixed_str = fixed_str + character
    return fixed_str


def is_leap_year(year):
    """
    -------------------------------------------------------
    Leap year determination.
    Use: leap_year = is_leap_year(year)
    -------------------------------------------------------
    Parameters:
        year - year to determine if it is a leap year (int > 0)
    Returns:
        leap_year - True if year is a leap year, False otherwise (boolean)
    -------------------------------------------------------
    """
    if year % 4 == 0:
        if year % 100 == 0:
            if year % 400 == 0:
                return True
            else:
                return False
        else:
            return True
    else:
        return False


def is_valid(name):
    """
    -------------------------------------------------------
    Determines if name is a valid Python variable name.
    Variables names must start with a letter or an underscore.
    The rest of the variable name may consist of letters, numbers
    and underscores.
    Use: valid = is_valid(name)
    -------------------------------------------------------
    Parameters:
        name - a string to test as a Python variable name (str)
    Returns:
        valid - True if name is a valid Python variable name,
            False otherwise (boolean)
    -------------------------------------------------------
    """
    if name.isidentifier():
        return True
    else:
        return False


def max_diff(a):
    """
    -------------------------------------------------------
    Returns maximum absolute difference between adjacent values in a list.
    a must be unchanged.
    Use: md = max_diff(a)
    -------------------------------------------------------
    Parameters:
        a - a list of values (list of int)
    Returns:
        md - the largest absolute difference between adjacent
            values in a list (int)
    -------------------------------------------------------
    """
    md = 0
    for i in range((len(a))-1):
        if a[i] - a[i+1] > md:
            md = a[i] - a[i+1]
    return md


def matrix_stats(a):
    """
    -------------------------------------------------------
    Determines the smallest, largest, total, and average of
    the values in the 2D list a. You may assume there is at
    least one value in a.
    a must be unchanged.
    Use: small, large, total, average = matrix_stats(a):
    -------------------------------------------------------
    Parameters:
        a - a 2D list of numbers (2D list of float)
    Returns:
        small - the smallest number in a (float)
        large - the largest number in a (float)
        total - the total of all numbers in a (float)
        average - the average of all numbers in a (float)
    -------------------------------------------------------
    """
    small = None
    large = None
    total = 0
    count = 0

    for row in a:
        for value in row:
            if small is None or large is None:
                small = value
                large = value
            else:
                if value < small:
                    small = value

                if value > large:
                    large = value
            total = total + value
            count = count + 1

    average = total / count
    return small, large, total, average


def matrixes_add(a, b):
    """
    -------------------------------------------------------
    Sums the contents of matrixes a and b. a and b must have
    the same number of rows and columns.
    a and b must be unchanged.
    Use: c = matrixes_add(a, b)
    -------------------------------------------------------
    Parameters:
        a - a 2D list (2D list of int/float)
        b - a 2D list (2D list of int/float)
    Returns:
        c - the matrix sum of a and b (2D list of int/float)
    -------------------------------------------------------
    """
    assert len(a) == len(b) and len(a[0]) == len(b[0])

    c = [[0 for _ in range(len(a[0]))] for _ in range(len(a))]

    for i in range(len(a)):
        for j in range(len(a[i])):
            c[i][j] = (a[i][j] + b[i][j])

    return(c)


def shift(string, n):
    """
    -------------------------------------------------------
    Encipher a string using a shift cipher.
    Only letters are enciphered, and the returned string is
    in upper case.
    Use: estring = shift(string, n):
    -------------------------------------------------------
    Parameters:
        string - string to encipher (str)
        n - the number of letters to shift (int)
    Returns:
        estring - the enciphered string (str)
    -------------------------------------------------------
    """
    if not string:
        return ""

    shifted_string = []

    for char in string:
        if char.isalpha():
            shift_base = 'a' if char.islower() else 'A'
            shifted_char = chr((ord(char) - ord(shift_base) + n) %
                               26 + ord(shift_base))
            shifted_string.append(shifted_char)
        else:
            shifted_string.append(char)

    return ''.join(shifted_string)


def stack_combine(source1, source2):
    """
    -------------------------------------------------------
    Combines two source stacks into a target stack.
    When finished, the contents of source1 and source2 are interlaced
    into target and source1 and source2 are empty.
    Use: target = stack_combine(source1, source2)
    -------------------------------------------------------
    Parameters:
        source1 - a stack (Stack)
        source2 - another stack (Stack)
    Returns:
        target - the contents of the source1 and source2
            are interlaced into target (Stack)
    -------------------------------------------------------
    """
    target = Stack()
    while (not source1.is_empty()) and (not source2.is_empty()):
        target.push(source1.pop())
        target.push(source2.pop())
    while not source1.is_empty():
        target.push(source1.pop())
    while not source2.is_empty():
        target.push(source2.pop())
    return target


def stack_reverse(source):
    """
    -------------------------------------------------------
    Reverses the contents of a stack.
    Use: stack_reverse(source)
    -------------------------------------------------------
    Parameters:
        source - a Stack (Stack)
    Returns:
        None
    -------------------------------------------------------
    """
    mylist = []
    while not source.is_empty():
        mylist.append(source.pop())
    mylist.reverse()
    while len(mylist) != 0:
        source.push(mylist.pop())


def is_palindrome_stack(string):
    """
    -------------------------------------------------------
    Determines if string is a palindrome. Ignores case, digits, spaces, and
    punctuation in string.
    Use: palindrome = is_palindrome_stack(string)
    -------------------------------------------------------
    Parameters:
        string - a string (str)
    Returns:
        palindrome - True if string is a palindrome, False otherwise (bool)
    -------------------------------------------------------
    """

    stack = Stack()
    flag = True
    whitelist = set('abcdefghijklmnopqrstuvwxyz')
    string = string.lower()
    string = ''.join(filter(whitelist.__contains__, string))

    for char in string:
        stack.push(char)

    for char in string:
        if char != stack.pop():
            flag = False
    return flag


def stack_maze(maze):
    """
    -------------------------------------------------------
    Solves a maze using Depth-First search.
    Use: path = stack_maze(maze)
    -------------------------------------------------------
    Parameters:
        maze - dictionary of points in a maze, where each point
            represents a corridor end or a branch. Dictionary
            keys are the name of the point followed by a list of
            branches, if any. First point is named 'Start', exit
            is named 'X' (dict)
    Returns:
        path - list of points visited before the exit is reached,
            does not include 'Start', but does include 'X'.
            Return None if there is no exit (list of str)
    -------------------------------------------------------
    """
    stack = Stack()  #
    visited = set()
    path = []

    stack.push({'point': 'Start', 'path': ['Start']})

    while not stack.is_empty():

        current_state = stack.pop()
        current_point = current_state['point']
        current_path = current_state['path']

        if current_point == 'X':

            return current_path[1:]

        if current_point not in visited:
            visited.add(current_point)

            for neighbor in maze.get(current_point, []):
                if neighbor not in visited:

                    stack.push(
                        {'point': neighbor, 'path': current_path + [neighbor]})

    return None


def is_mirror_stack(string, valid_chars, m):
    """
    -------------------------------------------------------
    Determines if string is a mirror of characters in valid_chars around the pivot m.
    A mirror is of the form LmR, where L is the reverse of R, and L and R
    contain only characters in valid_chars.
    Use: mirror = is_mirror_stack(string, valid_chars, m)
    -------------------------------------------------------
    Parameters:
        string - a string (str)
        valid_chars - a string of valid characters (str)
        m - the mirror pivot string (str - one character not in valid_chars)
    Returns:
        mirror - the state of the string (Enum MIRRORED)
    -------------------------------------------------------
    """
    assert m not in valid_chars, \
        f"cannot use '{m}' as the mirror character"

    stack = Stack()
    n = len(string)
    pivot_index = string.find(m)

    if pivot_index == -1:
        return MIRRORED.NOT_MIRRORED

    for i in range(pivot_index):
        if string[i] not in valid_chars:
            return MIRRORED.INVALID_CHAR
        stack.push(string[i])

    for i in range(pivot_index + 1, n):
        if stack.is_empty():
            return MIRRORED.TOO_MANY_RIGHT
        top = stack.pop()
        if string[i] != top:
            return MIRRORED.MISMATCHED
        if string[i] not in valid_chars:
            return MIRRORED.INVALID_CHAR

    if not stack.is_empty():
        return MIRRORED.TOO_MANY_LEFT
    else:
        return MIRRORED.IS_MIRRORED


def queue_split_alt(source):
    """
    -------------------------------------------------------
    Splits the source queue into separate target queues with values
    alternating into the targets. At finish source queue is empty.
    Order of source values is preserved.
    (iterative algorithm)
    Use: target1, target2 = queue_split_alt(source)
    -------------------------------------------------------
    Parameters:
        source - a queue (Queue)
    Returns:
        target1 - contains alternating values from source (Queue)
        target2 - contains other alternating values from source (Queue)
    -------------------------------------------------------
    """
    target1 = Queue()
    target2 = Queue()

    flag = True
    while not source.is_empty():
        if flag:
            target1.insert(source.remove())
        else:
            target2.insert(source.remove())
            flag = not flag

        return target1, target2


def pq_split_key(source, key):
    """
    -------------------------------------------------------
    Splits a priority queue into two depending on an external
    priority key. The source priority queue is empty when the method ends.
    -------------------------------------------------------
    Parameters:
        source - a priority queue (Priority_Queue)
        key - a data object (?)
    Returns:
        target1 - contains values with priority higher than key (Priority_Queue)
        target2 - contains values with priority lower or equal to key (Priority_Queue)
    -------------------------------------------------------
    """
    target1 = Priority_Queue()
    target2 = Priority_Queue()

    while not source.is_empty():
        value = source.remove()
        if value < key:
            target2.insert(value)
        else:
            target1.insert(value)

    return target1, target2


def recurse(x, y):
    """
    -------------------------------------------------------
    Recursive function - example of tree recursion.
    Use: ans = recurse(x, y)
    -------------------------------------------------------
    Parameters:
        x - an integer (int)
        y - an integer (int)
    Returns:
        ans - the function result (int)
    ---
    ----------------------------------------------------
    """
    if x < 0 or y < 0:
        result = x - y
    else:
        result = recurse(x - 1, y) + recurse(x, y - 1)

    return result


def gcd(m, n):
    """
    -------------------------------------------------------
    Recursively find the Greatest Common Denominator of two numbers.
    Use: ans = gcd(m, n)
    -------------------------------------------------------
    Parameters:
        n - an integer (int)
        m - an integer (int)
    Returns:
        ans - the function result (int)
    -------------------------------------------------------
    """
    if m % n == 0:
        result = n
    else:
        result = gcd(n, m % n)

    return result


def vowel_count(s):
    """
    -------------------------------------------------------
    Recursively counts number of vowels in a string.
    Use: count = vowel_count(s)
    -------------------------------------------------------
    Parameters:
        s - string to examine (str)
    Returns:
        count - number of vowels in s (int)
    -------------------------------------------------------
    """
    vowels = "aeiou"

    if s == "":
        result = 0
    else:
        count_for_current = 1 if s[0].lower() in vowels else 0
        result = count_for_current + vowel_count(s[1:])

    return result


def to_power(base, power):
    """
    -------------------------------------------------------
    Calculates base^power.
    Use: ans = to_power(base, power)
    -------------------------------------------------------
    Parameters:
        base - base to apply power to (float)
        power - power to apply (int)
    Returns:
        ans - base ^ power (float)
    -------------------------------------------------------
    """

    if power == 0:
        result = 1
    elif power > 0:
        result = base * to_power(base, power - 1)
    else:
        result = 1 / to_power(base, -power)

    return result


def is_palindrome(s):
    """
    -------------------------------------------------------
    Recursively determines if s is a palindrome. Ignores non-letters and case.
    Use: palindrome = is_palindrome(s)
    -------------------------------------------------------
    Parameters:
        s - a string (str)
    Returns:
        palindrome - True if s is a palindrome, False otherwise (boolean)
    -------------------------------------------------------
    """
    cleaned_s = ''

    for c in s:
        if c.isalpha():
            cleaned_s += c.lower()

    result = len(cleaned_s) <= 1 or (
        cleaned_s[0] == cleaned_s[-1] and is_palindrome(cleaned_s[1:-1]))

    return result


def bag_to_set(bag):
    """
    -------------------------------------------------------
    Copies elements of a bag to a set.
    Use: new_set = bag_to_set(bag)
    -------------------------------------------------------
    Parameters:
        bag - a list of values (list)
    Returns:
        new_set - containing one each of the elements in bag (list)
    -------------------------------------------------------
    """
    if len(bag) == 0:
        result = []
    else:
        first = bag[0]
        remaining_elements = []

        for x in bag[1:]:
            if x != first:
                remaining_elements.append(x)

        rest_set = bag_to_set(remaining_elements)
        result = [first] + rest_set

    return result
