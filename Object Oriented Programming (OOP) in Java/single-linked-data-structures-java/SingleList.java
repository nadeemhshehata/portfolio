package cp213;

/**
 * A single linked list structure of <code>Node T</code> objects. These data
 * objects must be Comparable - i.e. they must provide the compareTo method.
 * Only the <code>T</code> object contained in the priority queue is visible
 * through the standard priority queue methods. Extends the
 * <code>SingleLink</code> class.
 *
 * @author David Brown
 * @version 2025-01-05
 * @param <T> this SingleList data type.
 */
public class SingleList<T extends Comparable<T>> extends SingleLink<T> {

    /**
     * Searches for the first occurrence of key in this SingleList. Private helper
     * methods - used only by other ADT methods.
     *
     * @param key The object to look for.
     * @return A pointer to the node previous to the node containing key.
     */
    private SingleNode<T> linearSearch(final T key) {

	// your code here

	SingleNode<T> previous = null;
	SingleNode<T> current = this.front;

	while (current != null && !current.getEntity().equals(key)) {
	    previous = current;
	    current = current.getNext();
	}

	return previous;
    }

    /**
     * Appends data to the end of this SingleList.
     *
     * @param entity The object to append.
     */
    public void append(final T entity) {

	// your code here

	SingleNode<T> node = new SingleNode<>(entity, null);

	if (this.front == null) {
	    this.front = node;
	    this.rear = node;
	} else {
	    this.rear.setNext(node);
	    this.rear = node;
	}

	this.length++;
    }

    /**
     * Removes duplicates from this SingleList. The list contains one and only one
     * of each object formerly present in this SingleList. The first occurrence of
     * each object is preserved.
     */
    public void clean() {

	// your code here

	if (this.front == null) {
	    return;
	}

	SingleNode<T> current = this.front;

	while (current != null && current.getNext() != null) {
	    SingleNode<T> prev = current;
	    SingleNode<T> temp = current.getNext();

	    while (temp != null) {
		if (current.getEntity().equals(temp.getEntity())) {
		    prev.setNext(temp.getNext());
		    this.length--;
		    if (temp == this.rear) {
			this.rear = prev;
		    }
		} else {
		    prev = temp;
		}
		temp = temp.getNext();
	    }
	    current = current.getNext();
	}
    }

    /**
     * Combines contents of two lists into a third. Values are alternated from the
     * origin lists into this SingleList. The origin lists are empty when finished.
     * NOTE: data must not be moved, only nodes.
     *
     * @param left  The first list to combine with this SingleList.
     * @param right The second list to combine with this SingleList.
     */
    public void combine(final SingleList<T> left, final SingleList<T> right) {

	// your code here

	while (left.front != null || right.front != null) {
	    if (left.front != null) {
		this.moveFrontToRear(left);
	    }
	    if (right.front != null) {
		this.moveFrontToRear(right);
	    }
	}
    }

    /**
     * Determines if this SingleList contains key.
     *
     * @param key The key object to look for.
     * @return true if key is in this SingleList, false otherwise.
     */
    public boolean contains(final T key) {

	// your code here

	SingleNode<T> current = this.front;

	while (current != null) {
	    if (current.getEntity().equals(key)) {
		return true;
	    }
	    current = current.getNext();
	}

	return false;
    }

    /**
     * Finds the number of times key appears in list.
     *
     * @param key The object to look for.
     * @return The number of times key appears in this SingleList.
     */
    public int count(final T key) {

	// your code here

	int count = 0;
	SingleNode<T> current = this.front;

	while (current != null) {
	    if (current.getEntity().equals(key)) {
		count++;
	    }
	    current = current.getNext();
	}

	return count;
    }

    /**
     * Finds and returns the object in list that matches key.
     *
     * @param key The object to search for.
     * @return The object that matches key, null otherwise.
     */
    public T find(final T key) {

	// your code here

	SingleNode<T> current = this.front;

	while (current != null) {
	    if (current.getEntity().equals(key)) {
		return current.getEntity();
	    }
	    current = current.getNext();
	}

	return null;
    }

    /**
     * Get the nth object in this SingleList.
     *
     * @param n The index of the object to return.
     * @return The nth object in this SingleList.
     * @throws ArrayIndexOutOfBoundsException if n is not a valid index.
     */
    public T get(final int n) throws ArrayIndexOutOfBoundsException {

	// your code here

	if (n < 0 || n >= this.length) {
	    throw new ArrayIndexOutOfBoundsException("Index out of bounds: " + n);
	}

	SingleNode<T> current = this.front;
	for (int i = 0; i < n; i++) {
	    current = current.getNext();
	}

	return current.getEntity();
    }

    /**
     * Determines whether two lists are identical.
     *
     * @param source The list to compare against this SingleList.
     * @return true if this SingleList contains the same objects in the same order
     *         as source, false otherwise.
     */
    public boolean equals(final SingleList<T> source) {

	// your code here

	if (this.length != source.length) {
	    return false;
	}

	SingleNode<T> currentThis = this.front;
	SingleNode<T> currentSource = source.front;

	while (currentThis != null) {
	    if (!currentThis.getEntity().equals(currentSource.getEntity())) {
		return false;
	    }
	    currentThis = currentThis.getNext();
	    currentSource = currentSource.getNext();
	}

	return true;
    }

    /**
     * Finds the first location of a object by key in this SingleList.
     *
     * @param key The object to search for.
     * @return The index of key in this SingleList, -1 otherwise.
     */
    public int index(final T key) {

	// your code here

	int index = 0;
	SingleNode<T> current = this.front;

	while (current != null) {
	    if (current.getEntity().equals(key)) {
		return index;
	    }
	    current = current.getNext();
	    index++;
	}

	return -1;
    }

    /**
     * Inserts object into this SingleList at index i. If i greater than the length
     * of this SingleList, append data to the end of this SingleList.
     *
     * @param i      The index to insert the new data at.
     * @param entity The new object to insert into this SingleList.
     */
    public void insert(int i, final T entity) {

	// your code here

	SingleNode<T> node = new SingleNode<>(entity, null);

	if (this.front == null || i <= 0) {
	    // Insert at the front if list is empty or i is 0 or negative
	    node.setNext(this.front);
	    this.front = node;

	    if (this.rear == null) {
		this.rear = node;
	    }
	} else {
	    SingleNode<T> current = this.front;
	    int index = 0;

	    while (current.getNext() != null && index < i - 1) {
		current = current.getNext();
		index++;
	    }

	    node.setNext(current.getNext());
	    current.setNext(node);

	    if (node.getNext() == null) {
		this.rear = node;
	    }
	}

	this.length++;
    }

    /**
     * Creates an intersection of two other SingleLists into this SingleList. Copies
     * data to this SingleList. left and right SingleLists are unchanged. Values
     * from left are copied in order first, then objects from right are copied in
     * order.
     *
     * @param left  The first SingleList to create an intersection from.
     * @param right The second SingleList to create an intersection from.
     */
    public void intersection(final SingleList<T> left, final SingleList<T> right) {

	// your code here

	SingleNode<T> currentLeft = left.front;

	while (currentLeft != null) {
	    if (right.contains(currentLeft.getEntity()) && !this.contains(currentLeft.getEntity())) {
		this.append(currentLeft.getEntity());
	    }
	    currentLeft = currentLeft.getNext();
	}
    }

    /**
     * Finds the maximum object in this SingleList.
     *
     * @return The maximum object.
     */
    public T max() {

	// your code here

	if (this.front == null) {
	    return null;
	}

	SingleNode<T> current = this.front;
	T max = current.getEntity();

	while (current != null) {
	    if (current.getEntity().compareTo(max) > 0) {
		max = current.getEntity();
	    }
	    current = current.getNext();
	}

	return max;
    }

    /**
     * Finds the minimum object in this SingleList.
     *
     * @return The minimum object.
     */
    public T min() {

	// your code here

	if (this.front == null) {
	    return null;
	}

	SingleNode<T> current = this.front;
	T min = current.getEntity();

	while (current != null) {
	    if (current.getEntity().compareTo(min) < 0) {
		min = current.getEntity();
	    }
	    current = current.getNext();
	}

	return min;
    }

    /**
     * Inserts object into the front of this SingleList.
     *
     * @param entity The object to insert into the front of this SingleList.
     */
    public void prepend(final T entity) {

	// your code here

	SingleNode<T> node = new SingleNode<>(entity, this.front);
	this.front = node;

	if (this.rear == null) {
	    this.rear = node;
	}

	this.length++;
    }

    /**
     * Finds, removes, and returns the object in this SingleList that matches key.
     *
     * @param key The object to search for.
     * @return The object matching key, null otherwise.
     */
    public T remove(final T key) {

	// your code here

	if (this.front == null) {
	    return null;
	}

	SingleNode<T> previous = null;
	SingleNode<T> current = this.front;

	while (current != null && !current.getEntity().equals(key)) {
	    previous = current;
	    current = current.getNext();
	}

	if (current == null) {
	    return null; // Key not found
	}

	if (previous == null) {
	    // Removing the first node
	    this.front = current.getNext();
	    if (this.front == null) {
		this.rear = null;
	    }
	} else {
	    // Removing a middle or last node
	    previous.setNext(current.getNext());
	    if (current == this.rear) {
		this.rear = previous;
	    }
	}

	this.length--;
	return current.getEntity();
    }

    /**
     * Removes the object at the front of this SingleList.
     *
     * @return The object at the front of this SingleList.
     */
    public T removeFront() {

	// your code here

	if (this.front == null) {
	    return null;
	}

	T entity = this.front.getEntity();
	this.front = this.front.getNext();
	this.length--;

	if (this.front == null) {
	    this.rear = null;
	}

	return entity;
    }

    /**
     * Finds and removes all objects in this SingleList that match key.
     *
     * @param key The object to search for.
     */
    public void removeMany(final T key) {

	// your code here

	while (this.front != null && this.front.getEntity().equals(key)) {
	    this.front = this.front.getNext();
	    this.length--;
	}

	if (this.front == null) {
	    this.rear = null;
	    return;
	}

	SingleNode<T> previous = this.front;
	SingleNode<T> current = this.front.getNext();

	while (current != null) {
	    if (current.getEntity().equals(key)) {
		previous.setNext(current.getNext());
		this.length--;
		if (current == this.rear) {
		    this.rear = previous;
		}
	    } else {
		previous = current;
	    }
	    current = current.getNext();
	}
    }

    /**
     * Reverses the order of the objects in this SingleList.
     */
    public void reverse() {

	// your code here

	if (this.front == null || this.front.getNext() == null) {
	    return;
	}

	SingleNode<T> prev = null;
	SingleNode<T> current = this.front;
	this.rear = this.front;

	while (current != null) {
	    SingleNode<T> next = current.getNext();
	    current.setNext(prev);
	    prev = current;
	    current = next;
	}

	this.front = prev;
    }

    /**
     * Splits the contents of this SingleList into the left and right SingleLists.
     * Moves nodes only - does not move object or call the high-level methods insert
     * or remove. this SingleList is empty when done. The first half of this
     * SingleList is moved to left, and the last half of this SingleList is moved to
     * right. If the resulting lengths are not the same, left should have one more
     * object than right. Order is preserved.
     *
     * @param left  The first SingleList to move nodes to.
     * @param right The second SingleList to move nodes to.
     */
    public void split(final SingleList<T> left, final SingleList<T> right) {

	// your code here

	int mid = (this.length + 1) / 2; // Left gets one more if odd
	int index = 0;

	while (this.front != null) {
	    if (index < mid) {
		left.moveFrontToRear(this);
	    } else {
		right.moveFrontToRear(this);
	    }
	    index++;
	}
    }

    /**
     * Splits the contents of this SingleList into the left and right SingleLists.
     * Moves nodes only - does not move object or call the high-level methods insert
     * or remove. this SingleList is empty when done. Nodes are moved alternately
     * from this SingleList to left and right. Order is preserved.
     *
     * @param left  The first SingleList to move nodes to.
     * @param right The second SingleList to move nodes to.
     */
    public void splitAlternate(final SingleList<T> left, final SingleList<T> right) {

	// your code here

	boolean toLeft = true;

	while (this.front != null) {
	    if (toLeft) {
		left.moveFrontToRear(this);
	    } else {
		right.moveFrontToRear(this);
	    }
	    toLeft = !toLeft;
	}
    }

    /**
     * Creates a union of two other SingleLists into this SingleList. Copies object
     * to this list. left and right SingleLists are unchanged. Values from left are
     * copied in order first, then objects from right are copied in order.
     *
     * @param left  The first SingleList to create a union from.
     * @param right The second SingleList to create a union from.
     */
    public void union(final SingleList<T> left, final SingleList<T> right) {

	// your code here

	SingleNode<T> currentLeft = left.front;
	SingleNode<T> currentRight = right.front;

	while (currentLeft != null) {
	    if (!this.contains(currentLeft.getEntity())) {
		this.append(currentLeft.getEntity());
	    }
	    currentLeft = currentLeft.getNext();
	}

	while (currentRight != null) {
	    if (!this.contains(currentRight.getEntity())) {
		this.append(currentRight.getEntity());
	    }
	    currentRight = currentRight.getNext();
	}
    }
}
