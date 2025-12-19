-- DROP DATABASE Car_RentalDB; -- Use this line after first Run
CREATE DATABASE Car_RentalDB;
use Car_RentalDB;

CREATE TABLE Customer (
    CustomerID INT PRIMARY KEY,
    FirstName VARCHAR(225) NOT NULL,
    MiddleName VARCHAR(225),
    LastName VARCHAR(225) NOT NULL,
    Email VARCHAR(225) NOT NULL,
    PhoneNumber VARCHAR(20) NOT NULL,
    DriverLicenseNumber VARCHAR(20) NOT NULL
);

CREATE TABLE Location (
    LocationID INT PRIMARY KEY,
    City VARCHAR(225) NOT NULL,
    State VARCHAR(225) NOT NULL,
    Address VARCHAR(225) NOT NULL,
    PostalCode VARCHAR(50) NOT NULL
);

CREATE TABLE Employee (
    EmployeeID INT PRIMARY KEY,
    FirstName VARCHAR(225) NOT NULL,
    LastName VARCHAR(225) NOT NULL,
    Position VARCHAR(225) NOT NULL,
    StartDate DATE NOT NULL,
    LocationID INT NOT NULL,
    FOREIGN KEY (LocationID) REFERENCES Location(LocationID)
);

CREATE TABLE Vehicle (
    VehicleID INT PRIMARY KEY,
    VIN VARCHAR(50) UNIQUE NOT NULL,
    Make VARCHAR(100) NOT NULL,
    Model VARCHAR(100) NOT NULL,
    Year INT NOT NULL,
    EngineDisplacement FLOAT NOT NULL,
    EngineCylinders INT NOT NULL,
    OdometerKM INT NOT NULL,
    AvailabilityStatus VARCHAR(20) NOT NULL
);

CREATE TABLE Insurance (
    InsuranceID INT PRIMARY KEY,
    PolicyNumber VARCHAR(50) UNIQUE NOT NULL,
    VehicleID INT UNIQUE NOT NULL,
    EndDate DATE NOT NULL,
    FOREIGN KEY (VehicleID) REFERENCES Vehicle(VehicleID)
);

CREATE TABLE Maintenance (
    MaintenanceID INT PRIMARY KEY,
    MaintenanceDate DATE NOT NULL,
    Cost DECIMAL(10, 2) NOT NULL,
    Details TEXT NOT NULL,
    VehicleID INT NOT NULL,
    FOREIGN KEY (VehicleID) REFERENCES Vehicle(VehicleID)
);

CREATE TABLE Reservation (
    ReservationID INT PRIMARY KEY,
    ReservationDate DATE NOT NULL,
    Status VARCHAR(20) NOT NULL,
    CustomerID INT NOT NULL,
    PickupLocationID INT NOT NULL,
    DropoffLocationID INT NOT NULL,
    VehicleID INT NOT NULL,
    FOREIGN KEY (CustomerID) REFERENCES Customer(CustomerID),
    FOREIGN KEY (PickupLocationID) REFERENCES Location(LocationID),
    FOREIGN KEY (DropoffLocationID) REFERENCES Location(LocationID),
    FOREIGN KEY (VehicleID) REFERENCES Vehicle(VehicleID)
);

CREATE TABLE Rental (
    RentalID INT PRIMARY KEY,
    StartDate DATE NOT NULL,
    EndDate DATE NOT NULL,
    TotalCost DECIMAL(10, 2) NOT NULL,
    CustomerID INT NOT NULL,
    VehicleID INT NOT NULL,
    FOREIGN KEY (CustomerID) REFERENCES Customer(CustomerID),
    FOREIGN KEY (VehicleID) REFERENCES Vehicle(VehicleID)
);

CREATE TABLE Payment (
    PaymentID INT PRIMARY KEY,
    PaymentDate DATE NOT NULL,
    PaymentMethod VARCHAR(20) NOT NULL,
    Amount DECIMAL(10, 2) NOT NULL,
    RentalID INT UNIQUE NOT NULL,
    FOREIGN KEY (RentalID) REFERENCES Rental(RentalID)
);

CREATE TABLE Feedback (
    FeedbackID INT PRIMARY KEY,
    Rating INT NOT NULL CHECK (Rating BETWEEN 1 AND 5),
    FeedbackText TEXT,
    RentalID INT UNIQUE NOT NULL,
    FOREIGN KEY (RentalID) REFERENCES Rental(RentalID)
);

