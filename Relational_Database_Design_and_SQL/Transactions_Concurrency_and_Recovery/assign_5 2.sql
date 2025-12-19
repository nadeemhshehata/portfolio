USE Car_RentalDB; 
-- DESC Reservation;
-- DESC Vehicle;
-- DESC Payment;
-- DESC Employee;
-- DESC Rental;


-- SELECT * FROM Customer LIMIT 5;
-- SELECT * FROM Rental LIMIT 5;
-- SELECT * FROM Employee LIMIT 5;
-- SELECT * FROM Vehicle LIMIT 5;
-- SELECT * FROM Payment LIMIT 5;



-- 1. Query using JOIN and aggregation
SELECT c.CustomerID, c.FirstName, c.LastName, COUNT(r.RentalID) AS TotalRentals
FROM Customer c
JOIN Rental r ON c.CustomerID = r.CustomerID
GROUP BY c.CustomerID, c.FirstName, c.LastName
HAVING COUNT(r.RentalID) > 2;

-- 2. Query using a set operation (UNION)
SELECT VehicleID, 'Available' AS Status FROM Vehicle WHERE VehicleID NOT IN (SELECT VehicleID FROM Rental)
UNION
SELECT VehicleID, 'Rented' AS Status FROM Rental;

-- 3. Query using statistical functions
SELECT res.PickupLocationID AS LocationID, 
       AVG(p.Amount) AS AvgPayment, 
       STDDEV(p.Amount) AS PaymentStdDev
FROM Payment p
JOIN Rental r ON p.RentalID = r.RentalID
JOIN Reservation res ON r.CustomerID = res.CustomerID
GROUP BY res.PickupLocationID;

-- 4. Query with GROUP BY and HAVING
SELECT e.EmployeeID, COUNT(r.RentalID) AS RentalsHandled
FROM Rental r
JOIN Employee e ON r.RentalID = e.EmployeeID
GROUP BY e.EmployeeID
HAVING COUNT(r.RentalID) > 5;

-- 5. Recursive query (if applicable, for hierarchical data)

DROP TABLE IF EXISTS EmployeeHierarchy;
CREATE TABLE EmployeeHierarchy (
    EmployeeID INT,
    FirstName VARCHAR(225),
    LastName VARCHAR(225),
    Position VARCHAR(225),
    StartDate DATE,
    LocationID INT,
    Level INT
);


INSERT INTO EmployeeHierarchy (EmployeeID, FirstName, LastName, Position, StartDate, LocationID, Level)
SELECT e.EmployeeID, e.FirstName, e.LastName, e.Position, e.StartDate, e.LocationID,
       RANK() OVER (ORDER BY e.StartDate ASC) AS Level
FROM Car_RentalDB.Employee e;

SELECT * FROM EmployeeHierarchy;

-- 6. Execution plan analysis (example query to optimize)
EXPLAIN 
SELECT r.RentalID, r.CustomerID, p.Amount
FROM Rental r
JOIN Payment p ON r.RentalID = p.RentalID
WHERE p.Amount > 100;

-- Suggestion: Ensure indexes on RentalID and Amount in Payment table
-- Check and create index on Payment(Amount)
SET @idx_exists = (SELECT COUNT(*) FROM INFORMATION_SCHEMA.STATISTICS WHERE TABLE_SCHEMA = DATABASE() AND TABLE_NAME = 'Payment' AND INDEX_NAME = 'idx_amount');
SET @query = IF(@idx_exists = 0, 'CREATE INDEX idx_amount ON Payment(Amount)', 'SELECT "Index idx_amount already exists"');
PREPARE stmt FROM @query;
EXECUTE stmt;
DEALLOCATE PREPARE stmt;

-- Check and create index on Payment(RentalID)
SET @idx_exists = (SELECT COUNT(*) FROM INFORMATION_SCHEMA.STATISTICS WHERE TABLE_SCHEMA = DATABASE() AND TABLE_NAME = 'Payment' AND INDEX_NAME = 'idx_rental_id');
SET @query = IF(@idx_exists = 0, 'CREATE INDEX idx_rental_id ON Payment(RentalID)', 'SELECT "Index idx_rental_id already exists"');
PREPARE stmt FROM @query;
EXECUTE stmt;
DEALLOCATE PREPARE stmt;
-- 7. Query with a subquery in WHERE
SELECT VehicleID, Model, Year FROM Vehicle
WHERE VehicleID IN (SELECT DISTINCT VehicleID FROM Rental WHERE EndDate IS NULL);



-- Views

-- View 1: Using a subquery in SELECT
CREATE OR REPLACE VIEW CustomerSpending AS
SELECT c.CustomerID, c.FirstName, c.LastName,
       (SELECT SUM(p.Amount) FROM Payment p WHERE p.RentalID IN (SELECT RentalID FROM Rental WHERE Rental.CustomerID = c.CustomerID)) AS TotalSpent
FROM Customer c;

-- View 2: Using a subquery in FROM (derived table)
CREATE OR REPLACE VIEW FrequentRenters AS
SELECT CustomerID, RentalCount
FROM (SELECT CustomerID, COUNT(RentalID) AS RentalCount FROM Rental GROUP BY CustomerID) AS RentalStats
WHERE RentalCount > 3;

-- View 3: Using a subquery in WHERE
CREATE OR REPLACE VIEW ActiveRentals AS
SELECT * FROM Rental
WHERE CustomerID IN (SELECT CustomerID FROM Customer WHERE Email LIKE '%@gmail.com');