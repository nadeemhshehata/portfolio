package cp213;

/**
 * Inherited class in simple example of inheritance / polymorphism.
 *
 * @author Nadeem Hassan
 * @version 2022-03-02
 */
public class CAS extends Professor {

    // your code here
    /** The term the CAS member is hired for. */
    private String term;

    /**
     * Constructor for CAS.
     * 
     * @param lastName   The last name of the CAS member.
     * @param firstName  The first name of the CAS member.
     * @param department The department of the CAS member.
     * @param term       The term in which the CAS member is hired (e.g., "202105").
     */
    public CAS(String lastName, String firstName, String department, String term) {
	super(lastName, firstName, department);
	this.term = term;
    }

    /**
     * Gets the term of the CAS member.
     * 
     * @return The term in format YYYYMM.
     */
    public String getTerm() {
	return this.term;
    }

    /**
     * Returns a string representation of the CAS object.
     * 
     * @return Formatted CAS details.
     */
    @Override
    public String toString() {
	return super.toString() + "\nTerm: " + this.term;
    }
}
