package cp213;

/**
 * Inherited class in simple example of inheritance / polymorphism.
 *
 * @author Nadeem Hassan
 * @version 2022-03-02
 */
public class IA extends Student {

    /** The course the IA is assisting with. */
    private String course;

    /**
     * Constructor for IA.
     * 
     * @param lastName  The last name of the IA.
     * @param firstName The first name of the IA.
     * @param id        The student ID of the IA (as a String).
     * @param course    The course the IA is assisting with.
     */
    public IA(String lastName, String firstName, String id, String course) {
	super(lastName, firstName, id);
	this.course = course;
    }

    /**
     * Gets the course the IA is assisting with.
     * 
     * @return The course name.
     */
    public String getCourse() {
	return this.course;
    }

    /**
     * Returns a string representation of the IA object.
     * 
     * @return Formatted IA details.
     */
    @Override
    public String toString() {
	return super.toString() + "\nCourse: " + this.course;
    }
}
