package cp213;

import java.io.PrintStream;
import java.util.ArrayList;
import java.util.Scanner;

/**
 * Utilities for working with Movie objects.
 *
 * @author Nadeem Hassan, 169093285, hass3285@mylaurier.ca
 * @version 2025-01-05
 */
public class MovieUtilities {

    /**
     * Counts the number of movies in each genre given in Movie.GENRES. An empty
     * movies list should produce a count array of: [0,0,0,0,0,0,0,0,0,0,0]
     *
     * @param movies List of movies.
     * @return Number of genres across all Movies. One entry for each genre in the
     *         Movie.GENRES array.
     */
    public static int[] genreCounts(final ArrayList<Movie> movies) {

	// your code here

	int[] counts = new int[Movie.GENRES.length];
	for (Movie movie : movies) {
	    if (movie.getGenre() >= 0) {
		counts[movie.getGenre()]++;
	    }
	}
	return counts;
    }

    /**
     * Creates a Movie object by requesting data from a user. Uses the format:
     *
     * <pre>
    Title:
    Year:
    Director:
    Rating:
    Genres:
    0: science fiction
    1: fantasy
    ...
    10: mystery
    
    Enter a genre number:
     * </pre>
     *
     * @param keyboard A keyboard (System.in) Scanner.
     * @return A Movie object.
     */
    public static Movie getMovie(final Scanner keyboard) {

	// your code here

	System.out.print("Title: ");
	String title = keyboard.nextLine();

	System.out.print("Year: ");
	int year = keyboard.nextInt();
	keyboard.nextLine(); // Consume newline

	System.out.print("Director: ");
	String director = keyboard.nextLine();

	System.out.print("Rating: ");
	double rating = keyboard.nextDouble();
	keyboard.nextLine(); // Consume newline

	System.out.println("Genres:\n" + Movie.genresMenu());
	System.out.print("Enter a genre number: ");
	int genre = keyboard.nextInt();
	keyboard.nextLine(); // Consume newline

	// Fix: Ensure valid genre
	if (genre < 0 || genre >= Movie.GENRES.length) {
	    System.out.println("Invalid genre selected. Defaulting to 0.");
	    genre = 0;
	}

	return new Movie(title, year, director, rating, genre);
    }

    /**
     * Creates a list of Movies whose genre is equal to the genre parameter.
     *
     * @param movies List of movies.
     * @param genre  Genre to compare against.
     * @return List of movies of genre.
     */
    public static ArrayList<Movie> getByGenre(final ArrayList<Movie> movies, final int genre) {

	// your code here

	ArrayList<Movie> result = new ArrayList<>();
	for (Movie movie : movies) {
	    if (movie.getGenre() == genre) {
		result.add(movie);
	    }
	}
	return result;
    }

    /**
     * Creates a list of Movies whose ratings are equal to or higher than rating.
     *
     * @param movies List of movies.
     * @param rating Rating to compare against.
     * @return List of movies of rating or higher.
     */
    public static ArrayList<Movie> getByRating(final ArrayList<Movie> movies, final double rating) {

	// your code here

	ArrayList<Movie> result = new ArrayList<>();
	for (Movie movie : movies) {
	    if (movie.getRating() >= rating) {
		result.add(movie);
	    }
	}
	return result;
    }

    /**
     * Creates a list of Movies from a particular year.
     *
     * @param movies List of movies.
     * @param year   Year to compare against.
     * @return List of movies of year.
     */
    public static ArrayList<Movie> getByYear(final ArrayList<Movie> movies, final int year) {

	// your code here

	ArrayList<Movie> result = new ArrayList<>();
	for (Movie movie : movies) {
	    if (movie.getYear() == year) {
		result.add(movie);
	    }
	}
	return result;
    }

    /**
     * Asks a user to select a genre from a list of genres displayed by calling
     * Movie.genresMenu() and returns an integer genre code. The genre must be a
     * valid index to an item in Movie.GENRES.
     *
     * @param keyboard A keyboard (System.in) Scanner.
     * @return An integer genre code.
     */
    public static int readGenre(final Scanner keyboard) {

	// your code here

	System.out.println("Genres:\n" + Movie.genresMenu());
	System.out.print("Enter a genre number: ");
	int genre = keyboard.nextInt();
	keyboard.nextLine(); // Consume newline

	// Fix: Validate the genre number
	return (genre >= 0 && genre < Movie.GENRES.length) ? genre : -1;
    }

    /**
     * Creates and returns a Movie object from a line of formatted string data.
     *
     * @param line A vertical bar-delimited line of movie data in the format
     *             title|year|director|rating|genre
     * @return The data from line as a Movie object.
     */
    public static Movie readMovie(final String line) {

	// your code here

	String[] parts = line.split("\\|");
	if (parts.length != 5) {
	    throw new IllegalArgumentException("Invalid movie data format.");
	}

	String title = parts[0];
	int year = Integer.parseInt(parts[1]);
	String director = parts[2];
	double rating = Double.parseDouble(parts[3]);
	int genre = Integer.parseInt(parts[4]);

	return new Movie(title, year, director, rating, genre);

    }

    /**
     * Reads a list of Movies from a file.
     *
     * @param fileIn A Scanner of a Movie data file in the format
     *               title|year|director|rating|genre
     * @return A list of Movie objects.
     */
    public static ArrayList<Movie> readMovies(final Scanner fileIn) {

	// your code here

	ArrayList<Movie> movies = new ArrayList<>();
	while (fileIn.hasNextLine()) {
	    movies.add(readMovie(fileIn.nextLine()));
	}
	return movies;
    }

    /**
     * Writes the contents of a list of Movie to a PrintStream.
     *
     * @param movies A list of Movie objects.
     * @param ps     Output PrintStream.
     */
    public static void writeMovies(final ArrayList<Movie> movies, PrintStream ps) {

	// your code here
	for (Movie movie : movies) {
	    movie.write(ps);
	}
    }

}
