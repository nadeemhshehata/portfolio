"""
-------------------------------------------------------
Food class utility functions.
-------------------------------------------------------
Author:  Nadeem Hassan
ID:      169093285
Email:   hass3285@mylaurier.ca
__updated__ = "2024-09-19"
-------------------------------------------------------
"""
from Food import Food


def get_food():
    """
    -------------------------------------------------------
    Creates a Food object by requesting data from a user.
    Use: source = get_food()
    -------------------------------------------------------
    Returns:
        food - a completed food object (Food).
    -------------------------------------------------------
    """

    # Your code here
    is_vegetarian = False
    name = input("Name: ")
    print("Origin")
    print(Food.origins())
    origin = int(input(":"))
    veg = input("Vegetarian (Y/N): ")
    veg = veg.strip().lower()
    if veg == 'y':
        is_vegetarian = True

    #is_vegetarian = input("Vegetarian (Y/N): ").strip().lower() == 'y'
    calories = int(input("Calories: "))

    food = Food(name, origin, is_vegetarian, calories)
    return food


def read_food(line):
    """
    -------------------------------------------------------
    Creates and returns a Food object from a line of string data.
    Use: source = read_food(line)
    -------------------------------------------------------
    Parameters:
        line - a vertical bar-delimited line of food data in the format
          name|origin|is_vegetarian|calories (str)
    Returns:
        food - contains the data from line (Food)
    -------------------------------------------------------
    """

    # Your code here

    list_line = line.split("|")
    if (len(list_line)) == 4:
        name = list_line[0]
        origin = int(list_line[1])
        is_vegetarian = list_line[2].lower() == "true"
        calories = int(list_line[3])
        food = Food(name, origin, is_vegetarian, calories)
        return food
    else:
        print("Line does not have 4 values")


def read_foods(file_variable):
    """
    -------------------------------------------------------
    Reads a file of food strings into a list of Food objects.
    Use: foods = read_foods(file_variable)
    -------------------------------------------------------
    Parameters:
        file_variable - an open file of food data (file)
    Returns:
        foods - a list of food objects (list of Food)
    -------------------------------------------------------
    """

    # Your code here
    foods = []
    lines = file_variable.readlines()
    for i in range(len(lines)):
        x = read_food(lines[i])
        foods.append(x)

    return foods


def write_foods(file_variable, foods):
    """
    -------------------------------------------------------
    Writes a list of Food objects to a file.
    file_variable contains the objects in foods as strings in the format
          name|origin|is_vegetarian|calories
    foods is unchanged.
    Use: write_foods(file_variable, foods)
    -------------------------------------------------------
    Parameters:
        file_variable - an open file of food data (file variable)
        foods - a list of Food objects (list of Food)
    Returns:
        None
    -------------------------------------------------------
    """
    # Your code here
    for food in foods:
        x = str(food.name)
        y = str(food.origin)
        z = str(food.is_vegetarian)
        q = str(food.calories)

        file_variable.write(x+"|"+y+"|"+z+"|"+q+"\n")


def get_vegetarian(foods):
    """
    -------------------------------------------------------
    Creates a list of vegetarian Food objects.
    foods is unchanged.
    Use: v_foods = get_vegetarian(foods)
    -------------------------------------------------------
    Parameters:
        foods - a list of Food objects (list of Food)
    Returns:
        veggies - Food objects from foods that are vegetarian (list of Food)
    -------------------------------------------------------
    """

    # Your code here
    veggies = []
    for food in foods:
        if food.is_vegetarian == True:
            veggies.append(food)

    return veggies


def by_origin(foods, origin):
    """
    -------------------------------------------------------
    Creates a list of Food objects by origin.
    foods is unchanged.
    Use: o_foods = by_origin(foods, origin)
    -------------------------------------------------------
    Parameters:
        foods - a list of Food objects (list of Food)
        origin - a food origin (int)
    Returns:
        origins - Food objects from foods that are of a particular origin (list of Food)
    -------------------------------------------------------
    """
    assert origin in range(len(Food.ORIGIN))

    # Your code here
    origins = []
    for food in foods:
        if food.origin == origin:
            origins.append(food)

    return origins


def average_calories(foods):
    """
    -------------------------------------------------------
    Determines the average calories in a list of Foods objects.
    foods is unchanged.
    Use: avg = average_calories(foods)
    -------------------------------------------------------
    Parameters:
        foods - a list of Food objects (list of Food)
    Returns:
        avg - average calories in all Food objects of foods (int)
    -------------------------------------------------------
    """

    # Your code here
    if len(foods) == 0:
        return 0
    calories = 0

    for food in foods:
        calories = calories + food.calories
    avgs = calories / len(foods)
    avg = int(avgs)

    return avg


def calories_by_origin(foods, origin):
    """
    -------------------------------------------------------
    Determines the average calories in a list of Foods objects.
    foods is unchanged.
    Use: by_origin = calories_by_origin(foods, origin)
    -------------------------------------------------------
    Parameters:
        foods - a list of Food objects (list of Food)
        origin - the origin of the Food objects to find (int)
    Returns:
        avg - average calories for all Foods of the requested origin (int)
    -------------------------------------------------------
    """
    assert origin in range(len(Food.ORIGIN))

    # Your code here
    if len(foods) == 0:
        return 0
    counter = 0
    calories = 0

    for food in foods:
        if food.origin == origin:
            counter = counter + 1
            calories = calories + food.calories

    total = calories / counter
    avg = int(total)

    return avg


def food_table(foods):
    """
    -------------------------------------------------------
    Prints a formatted table of Food objects, sorted by name.
    foods is unchanged.
    Use: food_table(foods)
    -------------------------------------------------------
    Parameters:
        foods - a list of Food objects (list of Food)
    Returns:
        None
    -------------------------------------------------------
    """

    # Your code here
    name_width = max(len(food.name) for food in foods) + 2
    origin_width = max(len(Food.ORIGIN[food.origin]) for food in foods) + 2
    veg_width = len('Vegetarian') + 2
    cal_width = len('Calories') + 2

    print(f"{'Name':<{name_width}} {'Origin':<{origin_width}} {'Vegetarian':<{veg_width}} {'Calories':<{cal_width}}")
    print(f"{'-' * name_width} {'-' * origin_width} {'-' * veg_width} {'-' * cal_width}")

    sorted_foods = sorted(foods)
    for food in sorted_foods:
        origin_name = Food.ORIGIN[food.origin]
        print(
            f"{food.name:<{name_width}} {origin_name:<{origin_width}} {str(food.is_vegetarian):<{veg_width}} {food.calories:<{cal_width}}"
        )


def food_search(foods, origin, max_cals, is_veg):
    """
    -------------------------------------------------------
    Searches for Food objects that fit certain conditions.
    foods is unchanged.
    Use: results = food_search(foods, origin, max_cals, is_veg)
    -------------------------------------------------------
    Parameters:
        foods - a list of Food objects (list of Food)
        origin - the origin of the food; if -1, accept any origin (int)
        max_cals - the maximum calories for the food; if 0, accept any calories value (int)
        is_veg - whether the food is vegetarian or not; if False accept any food (boolean)
    Returns:
        result - a list of foods that fit the conditions (list of Food)
            foods parameter must be unchanged
    -------------------------------------------------------
    """
    assert origin in range(-1, len(Food.ORIGIN))

    # Your code here
    search = []

    # 000
    if origin == -1 and max_cals == 0 and is_veg == False:
        search = foods

    # 001
    if origin == -1 and max_cals == 0 and is_veg == True:
        for food in foods:
            if food.is_vegetarian == is_veg:
                search.append(food)

    # 011
    if origin == -1 and max_cals >= 1 and is_veg == True:
        for food in foods:
            if food.is_vegetarian == is_veg and food.calories < max_cals:
                search.append(food)

    # 101
    if origin >= 0 and max_cals == 0 and is_veg == True:
        for food in foods:
            if food.origin == origin and food.is_vegetarian == is_veg:
                search.append(food)

    # 100
    if origin >= 0 and max_cals == 0 and is_veg == False:
        for food in foods:
            if food.origin == origin:
                search.append(food)

    # 010
    if origin == -1 and max_cals >= 1 and is_veg == False:
        for food in foods:
            if food.calories < max_cals:
                search.append(food)
    # 110
    if origin >= 0 and max_cals >= 1 and is_veg == False:
        for food in foods:
            if food.origin == origin and food.calories < max_cals:
                search.append(food)

    # 111
    if origin >= 0 and max_cals >= 1 and is_veg == True:
        for food in foods:
            if food.origin == origin and food.calories < max_cals and food.is_vegetarian == is_veg:
                search.append(food)

    return search
