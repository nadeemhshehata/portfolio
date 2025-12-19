package cp213;

import java.util.Scanner;

/**
 * Wraps around an Order object to ask for MenuItems and quantities.
 *
 * @author your name here
 * @author Abdul-Rahman Mawlood-Yunis
 * @author David Brown
 * @version 2025-01-05
 */
public class Cashier {

    private Menu menu = null;

    /**
     * Constructor.
     *
     * @param menu A Menu.
     */
    public Cashier(Menu menu) {
	this.menu = menu;
    }

    /**
     * Reads keyboard input. Returns a positive quantity, or 0 if the input is not a
     * valid positive integer.
     *
     * @param scan A keyboard Scanner.
     * @return
     */
    private int askForQuantity(Scanner scan) {
	int quantity = 0;
	System.out.print("How many do you want? ");

	try {
	    String line = scan.nextLine();
	    quantity = Integer.parseInt(line);
	} catch (NumberFormatException nfex) {
	    System.out.println("Not a valid number");
	}
	return quantity;
    }

    /**
     * Prints the menu.
     */
    private void printCommands() {
	System.out.println("\nMenu:");
	System.out.println(menu.toString());
	System.out.println("Press 0 when done.");
	System.out.println("Press any other key to see the menu again.\n");
    }

    /**
     * Asks for commands and quantities. Prints a receipt when all orders have been
     * placed.
     *
     * @return the completed Order.
     */
    public Order takeOrder() {
	System.out.println("Welcome to WLU Foodorama!");

	Order order = new Order();
	Scanner scan = new Scanner(System.in);

	while (true) {
	    printCommands();
	    System.out.print("Enter the number of the menu item you want (or 0 to finish): ");
	    String input = scan.nextLine();
	    int choice;
	    try {
		choice = Integer.parseInt(input);
	    } catch (NumberFormatException ex) {
		System.out.println("Invalid selection. Please enter a valid number.");
		continue;
	    }

	    if (choice == 0) {
		break;
	    }

	    if (choice < 1 || choice > menu.size()) {
		System.out.println("Invalid menu item number. Please try again.");
		continue;
	    }

	    MenuItem selectedItem = menu.getItem(choice - 1);

	    int quantity = askForQuantity(scan);
	    if (quantity > 0) {
		order.add(selectedItem, quantity);
	    } else {
		System.out.println("Invalid quantity. Item not added.");
	    }
	}

	System.out.println("\nYour order is complete. Here is your receipt:");
	System.out.println(order.toString());

	return order;
    }
}