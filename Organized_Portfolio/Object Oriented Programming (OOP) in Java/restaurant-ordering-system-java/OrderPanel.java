package cp213;

import java.awt.BorderLayout;
import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.FocusEvent;
import java.awt.event.FocusListener;
import java.awt.print.PrinterException;
import java.awt.print.PrinterJob;
import java.text.DecimalFormat;

import javax.swing.JButton;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JTextField;

/**
 * The GUI for the Order class.
 *
 * @author your name here
 * @author Abdul-Rahman Mawlood-Yunis
 * @author David Brown
 * @version 2025-01-05
 */
@SuppressWarnings("serial")
public class OrderPanel extends JPanel {

    /**
     * Implements an ActionListener for the 'Print' button. Prints the current
     * contents of the Order to a system printer or PDF.
     */
    private class PrintListener implements ActionListener {

	@Override
	public void actionPerformed(final ActionEvent e) {

	    // your code here
	    PrinterJob job = PrinterJob.getPrinterJob();
	    job.setPrintable(order);
	    // Show the print dialog to the user.
	    if (job.printDialog()) {
		try {
		    job.print();
		} catch (PrinterException ex) {
		    ex.printStackTrace();
		}
	    }

	}
    }

    /**
     * Implements a FocusListener on a JTextField. Accepts only positive integers,
     * all other values are reset to 0. Adds a new MenuItem to the Order with the
     * new quantity, updates an existing MenuItem in the Order with the new
     * quantity, or removes the MenuItem from the Order if the resulting quantity is
     * 0.
     */
    private class QuantityListener implements FocusListener {
	private MenuItem item = null;

	QuantityListener(final MenuItem item) {
	    this.item = item;
	}

	// your code here
	@Override
	public void focusGained(FocusEvent e) {
	    // Select all text when the field gains focus for easy editing.
	    JTextField tf = (JTextField) e.getSource();
	    tf.selectAll();
	}

	@Override
	public void focusLost(FocusEvent e) {
	    JTextField tf = (JTextField) e.getSource();
	    int quantity = 0;
	    try {
		quantity = Integer.parseInt(tf.getText());
		if (quantity < 0) {
		    quantity = 0;
		}
	    } catch (NumberFormatException ex) {
		quantity = 0;
	    }
	    // Reset the text field with a valid positive integer.
	    tf.setText(String.valueOf(quantity));
	    // Update the Order with the new quantity for the associated MenuItem.
	    order.update(item, quantity);
	    // Update totals displayed in the GUI.
	    updateTotals();
	}

    }

    // Attributes
    private Menu menu = null;
    private final Order order = new Order();
    private final DecimalFormat priceFormat = new DecimalFormat("$##0.00");
    private final JButton printButton = new JButton("Print");
    private final JLabel subtotalLabel = new JLabel("0");
    private final JLabel taxLabel = new JLabel("0");
    private final JLabel totalLabel = new JLabel("0");

    private JLabel nameLabels[] = null;
    private JLabel priceLabels[] = null;
    // TextFields for menu item quantities.
    private JTextField quantityFields[] = null;

    /**
     * Displays the menu in a GUI.
     *
     * @param menu The menu to display.
     */
    public OrderPanel(final Menu menu) {
	this.menu = menu;
	this.nameLabels = new JLabel[this.menu.size()];
	this.priceLabels = new JLabel[this.menu.size()];
	this.quantityFields = new JTextField[this.menu.size()];
	this.layoutView();
	this.registerListeners();
    }

    /**
     * Uses the GridLayout to place the labels and buttons.
     */
    private void layoutView() {

	// your code here
	this.setLayout(new BorderLayout());

	// Create a panel for the menu items using GridLayout: one row per item and 3
	// columns (name, price, quantity).
	JPanel itemsPanel = new JPanel(new GridLayout(menu.size(), 3, 5, 5));

	// Create labels and text fields for each menu item.
	for (int i = 0; i < menu.size(); i++) {
	    MenuItem item = menu.getItem(i);
	    nameLabels[i] = new JLabel(item.getEntity());
	    priceLabels[i] = new JLabel(priceFormat.format(item.getAmount()));
	    quantityFields[i] = new JTextField("0", 5);

	    itemsPanel.add(nameLabels[i]);
	    itemsPanel.add(priceLabels[i]);
	    itemsPanel.add(quantityFields[i]);
	}

	// Create a panel for totals and the print button.
	JPanel totalsPanel = new JPanel(new GridLayout(4, 2, 5, 5));
	totalsPanel.add(new JLabel("Subtotal:"));
	totalsPanel.add(subtotalLabel);
	totalsPanel.add(new JLabel("Tax:"));
	totalsPanel.add(taxLabel);
	totalsPanel.add(new JLabel("Total:"));
	totalsPanel.add(totalLabel);
	totalsPanel.add(new JLabel("")); // Filler cell.
	totalsPanel.add(printButton);

	// Add the items panel to the center and the totals panel to the bottom.
	this.add(itemsPanel, BorderLayout.CENTER);
	this.add(totalsPanel, BorderLayout.SOUTH);
    }

    /**
     * Register the widget listeners with the widgets.
     */
    private void registerListeners() {
	// Register the PrinterListener with the print button.
	this.printButton.addActionListener(new PrintListener());

	// your code here
	for (int i = 0; i < menu.size(); i++) {
	    MenuItem item = menu.getItem(i);
	    quantityFields[i].addFocusListener(new QuantityListener(item));
	}
    }

    /**
     * Updates the subtotal, tax, and total labels with the current Order totals.
     */
    private void updateTotals() {
	subtotalLabel.setText(priceFormat.format(order.getSubTotal()));
	taxLabel.setText(priceFormat.format(order.getTaxes()));
	totalLabel.setText(priceFormat.format(order.getTotal()));
    }
}
