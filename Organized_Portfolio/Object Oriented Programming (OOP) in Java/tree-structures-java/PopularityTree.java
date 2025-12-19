package cp213;

/**
 * Implements a Popularity Tree. Extends BST.
 *
 * @author Nadeem Hassan
 * @author David Brown
 * @version 2025-03-16
 * @param <T> the data structure data type
 */
public class PopularityTree<T extends Comparable<T>> extends BST<T> {

    /**
     * Auxiliary method for valid. May force node rotation if the retrieval count of
     * the located node data is incremented.
     *
     * @param node The node to examine for key.
     * @param key  The data to search for. Count is updated to count in matching
     *             node data if key is found.
     * @return The updated node.
     */
    private TreeNode<T> retrieveAux(TreeNode<T> node, final CountedEntity<T> key) {

	// your code here

	int compare = node.getCountedEntity().compareTo(key);
	this.comparisons++;

	if (compare == 0) {
	    // Found the key: increment count
	    node.getCountedEntity().incrementCount();
	    return node;
	} else if (compare > 0) {
	    // Search left
	    TreeNode<T> foundNode = this.retrieveAux(node.getLeft(), key);
	    if (foundNode != null) {
		// 1) Move the found node up the left link if it has >= count
		if (node.getLeft().getCountedEntity().getCount() <= foundNode.getCountedEntity().getCount()) {
		    node.setLeft(foundNode);
		}
		// 2) Rotate if node's count <= found node's count
		if (node.getCountedEntity().getCount() <= foundNode.getCountedEntity().getCount()) {
		    TreeNode<T> newRoot = this.rotateRight(node);
		    if (node == this.root) {
			this.root = newRoot;
		    }
		    node.updateHeight();
		    newRoot.updateHeight();
		}
	    }
	    return foundNode;
	} else {
	    // Search right
	    TreeNode<T> foundNode = this.retrieveAux(node.getRight(), key);
	    if (foundNode != null) {
		// 1) Move the found node up the right link if it has >= count
		if (node.getRight().getCountedEntity().getCount() <= foundNode.getCountedEntity().getCount()) {
		    node.setRight(foundNode);
		}
		// 2) Rotate if node's count <= found node's count
		if (node.getCountedEntity().getCount() <= foundNode.getCountedEntity().getCount()) {
		    TreeNode<T> newRoot = this.rotateLeft(node);
		    if (node == this.root) {
			this.root = newRoot;
		    }
		    node.updateHeight();
		    newRoot.updateHeight();
		}
	    }
	    return foundNode;
	}
    }

    /**
     * Performs a left rotation around node.
     *
     * @param parent The subtree to rotate.
     * @return The new root of the subtree.
     */
    private TreeNode<T> rotateLeft(final TreeNode<T> parent) {

	// your code here

	TreeNode<T> pivot = parent.getRight();
	parent.setRight(pivot.getLeft());
	pivot.setLeft(parent);
	pivot.updateHeight();
	parent.updateHeight();
	return pivot;
    }

    /**
     * Performs a right rotation around {@code node}.
     *
     * @param parent The subtree to rotate.
     * @return The new root of the subtree.
     */
    private TreeNode<T> rotateRight(final TreeNode<T> parent) {

	// your code here

	TreeNode<T> pivot = parent.getLeft();

	if (pivot == null) {
	    return parent;
	}
	parent.setLeft(pivot.getRight());
	pivot.setRight(parent);
	pivot.updateHeight();
	parent.updateHeight();
	return pivot;
    }

    /**
     * Replaces BST insertAux - does not increment count on repeated insertion.
     * Counts are incremented only on retrieve.
     */
    @Override
    protected TreeNode<T> insertAux(TreeNode<T> node, final CountedEntity<T> data) {

	// your code here

	if (node == null) {
	    node = new TreeNode<>(data);
	    this.size++;
	} else {
	    final int result = node.getCountedEntity().compareTo(data);
	    if (result > 0) {
		node.setLeft(this.insertAux(node.getLeft(), data));
	    } else if (result < 0) {
		node.setRight(this.insertAux(node.getRight(), data));
	    }
	    // If result == 0, do nothing (don't increment count in PopularityTree).
	}
	node.updateHeight();
	return node;
    }

    /**
     * Auxiliary method for valid. Determines if a subtree based on node is a valid
     * subtree. An Popularity Tree must meet the BST validation conditions, and
     * additionally the counts of any node data must be greater than or equal to the
     * counts of its children.
     *
     * @param node The root of the subtree to test for validity.
     * @return true if the subtree base on node is valid, false otherwise.
     */
    @Override
    protected boolean isValidAux(final TreeNode<T> node, TreeNode<T> minNode, TreeNode<T> maxNode) {

	// your code here

	if (node == null) {
	    return true;
	}
	int leftHeight = (node.getLeft() != null) ? node.getLeft().getHeight() : 0;
	int rightHeight = (node.getRight() != null) ? node.getRight().getHeight() : 0;
	int leftCount = (node.getLeft() != null) ? node.getLeft().getCountedEntity().getCount() : 0;
	int rightCount = (node.getRight() != null) ? node.getRight().getCountedEntity().getCount() : 0;

	// BST property checks + height checks + popularity property checks
	if ((minNode != null && node.getCountedEntity().compareTo(minNode.getCountedEntity()) <= 0)
		|| (maxNode != null && node.getCountedEntity().compareTo(maxNode.getCountedEntity()) >= 0)
		|| (node.getHeight() != Math.max(leftHeight, rightHeight) + 1)
		|| (node.getCountedEntity().getCount() < leftCount)
		|| (node.getCountedEntity().getCount() < rightCount)) {
	    return false;
	}
	boolean isLeftValid = isValidAux(node.getLeft(), minNode, node);
	boolean isRightValid = isValidAux(node.getRight(), node, maxNode);
	return isLeftValid && isRightValid;
    }

    /**
     * Determines whether two PopularityTrees are identical.
     *
     * @param target The PopularityTree to compare this PopularityTree against.
     * @return true if this PopularityTree and target contain nodes that match in
     *         position, data, count, and height, false otherwise.
     */
    public boolean equals(final PopularityTree<T> target) {
	return super.equals(target);
    }

    /**
     * Very similar to the BST retrieve, but increments the data count here instead
     * of in the insertion.
     *
     * @param key The key to search for.
     */
    @Override
    public CountedEntity<T> retrieve(CountedEntity<T> key) {

	// your code here

	TreeNode<T> foundNode = this.retrieveAux(this.root, key);
	return (foundNode != null) ? foundNode.getCountedEntity() : null;
    }
}