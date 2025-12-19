package cp213;

import java.time.LocalDate;

/**
 * Tests the Student class.
 *
 * @author Nadeem Hassan
 * @version 2025-02-03
 */
public class Main {

    public static void main(String[] args) {
	final String line = "-".repeat(40);
	int id = 169093285;
	String surname = "Hassan";
	String forename = "Nadeem";
	LocalDate birthDate = LocalDate.parse("2004-03-10");
	Student student = new Student(id, surname, forename, birthDate);
	System.out.println("New Student:");
	System.out.println(student);
	System.out.println(line);
	System.out.println("Test Getters");

	// call getters here

	System.out.println("ID: " + student.getId());
	System.out.println("Surname: " + student.getSurname());
	System.out.println("Forename: " + student.getForename());
	System.out.println("Birth Date: " + student.getBirthDate());

	System.out.println(line);
	System.out.println("Test Setters");

	// call setters here

	student.setId(789012);
	student.setSurname("nassah");
	student.setForename("meedan");
	student.setBirthDate(LocalDate.parse("2000-05-15"));

	System.out.println("Updated Student:");
	System.out.println(student);
	System.out.println(line);
	System.out.println("Test compareTo");

	// create new Students - call comparisons here

	Student student1 = new Student(123456, "Brown", "David", LocalDate.parse("1962-10-25"));
	Student student2 = new Student(999999, "Brown", "David", LocalDate.parse("1962-10-25"));
	Student student3 = new Student(123456, "Brown", "David", LocalDate.parse("1962-10-25"));

	System.out.println("Compare student1 and student2: " + student1.compareTo(student2));
	System.out.println("Compare student2 and student1: " + student2.compareTo(student1));
	System.out.println("Compare student1 and student3: " + student1.compareTo(student3));
    }

}
