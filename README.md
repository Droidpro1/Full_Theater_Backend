# C++ Theater Backend (part 3)

Problem: In preparation for the release of Avengers 4, you have been hired by the owner of a small movie theater to develop the backend for an online ticket reservation system. Patrons will be able to reserve seats in one of three auditoriums. Once the patron has selected an auditorium, the program should display the current seating arrangement and allow the patron to select seats. A report should be generated at the end of the program to specify for each individual auditorium and overall for all auditoriums how many seats were sold/unsold and how much money was earned.

The theater owner understands that to be competitive, the reservation system needs to track customer orders. The customers need the ability to login to the system and access their orders. The customers should have the ability to add orders, change orders or cancel orders as well as the ability to see the receipts for their orders. The reservation system should also have an administrator interface.

Details

    • The user account information will be stored in a HashMap

        ◦ You may use the STL unordered_map class or modify the hashmap you built for homework 7.

    • Each entry in the HashMap should contain the customer username, password and all orders.

        ◦ An order consists of the selected seats and number of tickets per ticket type

        ◦ I suggest using the username as the key value

    • Three auditoriums will be available to reserve seats

    • The seating arrangement for each auditorium will be stored in a file (​A1.txt, A2.txt and A3.txt)

    • Each line in the file will represent a row in the auditorium. The number of rows in the auditorium is unknown to you.

        ◦ Do not assume that each auditorium has the same number of rows

    • The number of seats in each row of the auditorium will be the same. For example, if the first line of the file has 15 seats, then every subsequent row in the theater will also have 15 seats.

        ◦ Do not assume each auditorium has the same number of seats per row

    • Empty seats are represented by a period (.).

    • Reserved seats are represented by a letter (A, C or S) in the file

        ◦ This will be used to create reports

        ◦ A =adult

        ◦ C = child

        ◦ S = senior

    • Reserved seats will be represented by a hashtag (#) on the screen

        ◦ The user does not need to know what type of ticket was sold, just that a seat is reserved.

    • You may use the reservation system from project 0 or 2.

        ◦ Feel free to tweak the reservation system as you feel is necessary.

    • Tickets can only be reserved the day of the screening and all screenings are at the same time.

    • Ticket prices are as follows:

        ◦ Adult - $10

        ◦ Child - $5

        ◦ Senior - $7.50

    • You must perform input validation

        ◦ Make sure that the user selection does not go out of bounds of the auditorium

    • When the program starts, no user will have any orders, although some seats may already be reserved in the auditorium.

        ◦ There is not enough time remaining in the semester to build a fully functioning system.

Filling the HashMap:

    • All user data will be in a file named userdb.dat
    • The program should read the file and fill in the hashmap before starting the user interface.
    • The format of the file is as follows:

        <username><space><password><newline>

    o  This should be encrypted, but you have enough to do without adding in decryption

    • The last line in the file may not contain a newline character at the end of the line

Customer User Interface and Workflow: Present a user-friendly system for the user to reserve seats.

        ◦ Starting Point: Before the customer can use the system, a login is required. The starting point of the interface is to ask the user for a username. After the username is entered, prompt for the password. Verify that the password is correct. If the password is not valid, prompt the user to enter the password again. If the password is entered incorrectly a total of 3 times, return to the starting point. Once the user has successfully logged in, display the main menu.

        ◦ Main Menu

    1. Reserve Seats

            2. View Orders

            3. Update Order

            4. Display Receipt

            5. Log Out

        ◦ Reserve Seats: ​When the user reserves seats, display the auditorium submenu.

    1. Auditorium 1

        2. Auditorium 2

        3. Auditorium 3

After the auditorium is selected, display that auditorium.

	  ABCDEFGHIJKLMNOPQRST

    1 ...##..#####........

    2 ########....####..##

    3 .........##.........

    4 #.#.#.#.#.#.#.#.#.#.

    5 ########.#####.#####

The rows are numbered and the seats are identified in each row by a letter of the alphabet

After the seating chart has been displayed, prompt the user for the following information in the order below:

    • Row number

    • Starting seat letter

    • Number of adult tickets

    • Number of child tickets

    • Number of senior tickets
Assume that the user wants to reserve sequential seats to the right of the first seat entered. Adult tickets will be reserved first, followed by child and then senior. All seats must be open for a reservation to be processed.

If the desired seats are not available, offer the user the best available seats that meet their criteria In the entire auditorium. The best available seats are the seats closest to the middle of the auditorium.

    • Think of the distance between 2 points

    • Use the distance between the center of the selection and the center of the auditorium.

    • In the event of a tie for distance, the row closest to the middle of the auditorium should be selected.

    • In the event of a tie for closest row, use the row with the smaller number

State to the user what the best available seats are and then ask if they would like those seats. Prompt the user to enter a Y to reserve the best available or N to refuse the best available. If the user declines the best available seats, return the user to the main menu. If the user accepts the best available seats, reserve them and display a confirmation to the screen. Once the selection has been processed, return to the main menu

When prompting the user for input, expect anything. Do not assume any input will be valid. If you ask for a number, the user could put in a floating point number, symbols or maybe even the Gettysburg Address (or at least a sentence or two). Make sure that your program handles proper validation. If invalid input is entered, loop until valid input is received. Use exception handling for this task.

    • View Orders: Develop an easy to read interface that displays all orders by the user that is logged in. As you develop this interface to display orders, consider that the interface will also be utilized when the user wants to update the order. Remember that the order consists of the auditorium, seats, and number of tickets per ticket type. You do not have to specify which type of person is sitting in each seat. Return to the main menu once the orders are displayed.

    • Update Order: Display the orders in a numerical menu system so that the user can enter the number of the order that should be updated. List each order on a separate line and be descriptive of the order. Do not just list Order 1, Order 2, etc.

After the order menu has been displayed and the user has selected an order, display the menu below and prompt the user for an update action:

        1. Add tickets to order

        2. Delete tickets from order

        3. Cancel Order

If the user wishes to add tickets to the order, step the user through the reservation process. All seats reserved this way will be added to the current order. The user may attempt to reserve seats anywhere in the auditorium. Do not offer the user the best available seats if the selected seats are not available. Reserve the seats if available. If not, display an appropriate message and return to the update action menu (see above).
If the user wishes to delete tickets from an order, ask the user for the row and seat number to remove from the order. Verify the seat entered by the user is valid for the order. If the seat selection is not valid, display an appropriate message and return to the Update Order submenu. After validating the seat information to remove, unreserve the seat and update the ticket totals for that order accordingly. It is possible for the user to remove all tickets from the order effectively cancelling it.

If the user wishes to cancel the order, mark all seats in the order as available and remove the order from the user’s account.

Once the order update has been competed, return to the main menu.
    • Display Receipt: Create a formatted receipt for the user. Make it look nice and easy to read. Display each order in detail (auditorium, seats, and number of tickets per ticket type), the amount of each order and the overall amount of all orders. Once displayed, return to the main menu.

    • Log Out: Return to the Starting Point

Admin Interface and Workflow:

        ◦ Starting Point: Like the customer, a login is required for the admin. Both the customer and admin will begin at the login prompt. The admin username is admin( Please note this is a horrible idea professionally, but that is the network admin’s problem). Like all other users, the username and password information for the admin will be in userdb.dat. After the username is entered, prompt for the password. Verify that the password is correct. If the password is not valid, prompt the user to enter the password again. If the password is entered incorrectly a total of 3 times, return to the starting point. Once the user has successfully logged in, display the Admin main menu.

        ◦ Admin Main Menu

            1. Print Report

            2. Logout

            3. Exit

        ◦ Print Report: 
        ◦ Display a formatted report to the console. The report should consist of 7 columns:
        ◦ The first row of the report will be column headers

        ◦ Column 1 – labels

               ▪ Auditorium 1

               ▪ Auditorium 2

               ▪ Auditorium 3

               ▪ Total
               
        ◦ Column 2 - Open seats: number of open seats
        
        ◦ Column 3 – Total reserved seats:number of reserved seats

        ◦ Column 4 - Adult seats:number of adult seats reserved

        ◦ Column 5 - Child seats: number of all child seats reserved

        ◦ Column 6 – Senior seats: number of all senior seats reserved

        ◦ Column 7 – Ticket sales: total amount of ticket sales for entire auditorium

    • Make the report look organized and easy to read

    • Logout: Return to the Starting Point

    • Exit: Store the auditoriums back to the files and end the program. The auditorium files should only contain the proper character for each type of seat reserved. After the files have been updated, end the program.
