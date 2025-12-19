package cp213;

import java.awt.Font;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.print.PageFormat;
import java.awt.print.Printable;
import java.awt.print.PrinterException;
import java.math.BigDecimal;
import java.math.RoundingMode;
import java.util.HashMap;
import java.util.Map;

/**
 * Stores a HashMap of MenuItem objects and the quantity of each MenuItem
 * ordered. Each MenuItem may appear only once in the HashMap.
 *
 * @author your name here
 * @author Abdul-Rahman Mawlood-Yunis
 * @author David Brown
 * @version 2025-01-05
 */
public class Order implements Printable {

    private static final String lineFormat = "%-14s%2d @ $%5.2f = $%6.2f\n";
    private static final String totalFormat = "%-9s                   $%6.2f\n";
    /**
     * The current tax rate on menu items.
     */
    public static final BigDecimal TAX_RATE = new BigDecimal(0.13);

    // define a Map of MenuItem objects
    // Note that this must be a *Map* of some flavour
    // @See
    // https://docs.oracle.com/en/java/javase/21/docs/api/java.base/java/util/Map.html

    // your code here
    private final Map<MenuItem, Integer> orderMap = new HashMap<>();

    /**
     * Increments the quantity of a particular MenuItem in an Order with a new
     * quantity. If the MenuItem is not in the order, it is added.
     *
     * @param item     The MenuItem to purchase - the HashMap key.
     * @param quantity The number of the MenuItem to purchase - the HashMap value.
     */
    public void add(final MenuItem item, final int quantity) {

	// your code here
	orderMap.put(item, orderMap.getOrDefault(item, 0) + quantity);

    }

    /**
     * Calculates the total value of all MenuItems and their quantities in the
     * HashMap.
     *
     * @return the total cost for the MenuItems ordered.
     */
    public BigDecimal getSubTotal() {

	// your code here

	BigDecimal subTotal = BigDecimal.ZERO;
	for (Map.Entry<MenuItem, Integer> entry : orderMap.entrySet()) {
	    // Assume MenuItem provides a getter for its price.
	    BigDecimal price = entry.getKey().getAmount();
	    int quantity = entry.getValue();
	    subTotal = subTotal.add(price.multiply(new BigDecimal(quantity)));
	}
	return subTotal.setScale(2, RoundingMode.HALF_UP);
    }

    /**
     * Calculates and returns the total taxes to apply to the subtotal of all
     * MenuItems in the order. Tax rate is TAX_RATE.
     *
     * @return total taxes on all MenuItems
     */
    public BigDecimal getTaxes() {

	// your code here

	BigDecimal taxes = getSubTotal().multiply(TAX_RATE);
	return taxes.setScale(2, RoundingMode.HALF_UP);
    }

    /**
     * Calculates and returns the total cost of all MenuItems order, including tax.
     *
     * @return total cost
     */
    public BigDecimal getTotal() {

	// your code here

	return getSubTotal().add(getTaxes()).setScale(2, RoundingMode.HALF_UP);
    }

    /*
     * Implements the Printable interface print method. Prints lines to a Graphics2D
     * object using the drawString method. Prints the current contents of the Order.
     */
    @Override
    public int print(final Graphics graphics, final PageFormat pageFormat, final int pageIndex)
	    throws PrinterException {
	int result = PAGE_EXISTS;

	if (pageIndex == 0) {
	    final Graphics2D g2d = (Graphics2D) graphics;
	    g2d.setFont(new Font("MONOSPACED", Font.PLAIN, 12));
	    g2d.translate(pageFormat.getImageableX(), pageFormat.getImageableY());
	    // Now we perform our rendering
	    final String[] lines = this.toString().split("\n");
	    int y = 100;
	    final int inc = 12;

	    for (final String line : lines) {
		g2d.drawString(line, 100, y);
		y += inc;
	    }
	} else {
	    result = NO_SUCH_PAGE;
	}
	return result;
    }

    /**
     * Returns a String version of a receipt for all the MenuItems in the order.
     */
    @Override
    public String toString() {

	// your code here

	StringBuilder receipt = new StringBuilder();

	// Print each MenuItem line using the lineFormat:
	// (menu item name, quantity, price, line total)
	for (Map.Entry<MenuItem, Integer> entry : orderMap.entrySet()) {
	    MenuItem item = entry.getKey();
	    int quantity = entry.getValue();
	    BigDecimal price = item.getAmount(); // Assumes a getAmount() method exists.
	    BigDecimal lineTotal = price.multiply(new BigDecimal(quantity)).setScale(2, RoundingMode.HALF_UP);
	    receipt.append(String.format(lineFormat, item.getEntity(), quantity, price.doubleValue(),
		    lineTotal.doubleValue()));
	}

	// Append the summary lines.
	receipt.append(String.format(totalFormat, "Subtotal:", getSubTotal().doubleValue()));
	receipt.append(String.format(totalFormat, "Taxes:", getTaxes().doubleValue()));
	receipt.append(String.format(totalFormat, "Total:", getTotal().doubleValue()));
	return receipt.toString();
    }

    /**
     * Replaces the quantity of a particular MenuItem in an Order with a new
     * quantity. If the MenuItem is not in the order, it is added. If quantity is 0
     * or negative, the MenuItem is removed from the Order.
     *
     * @param item     The MenuItem to update
     * @param quantity The quantity to apply to item
     */
    public void update(final MenuItem item, final int quantity) {

	// your code here
	if (quantity <= 0) {
	    orderMap.remove(item);
	} else {
	    orderMap.put(item, quantity);
	}

    }
}