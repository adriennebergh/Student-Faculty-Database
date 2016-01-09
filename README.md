# Student-Faculty-Database
Building a Database with Binary Search Trees

@author Adrienne Bergh

# Program Components
Database will allow the user to insert, delete, and query data. The data itself will be persistent, so that it may be processed over several sessions.

- Binary search tree holding Student records (unique student ID (an integer), a String name field, a string level field (Freshman, Sophomore, etc), a String major field, a double GPA field, and an integer advisor field, which will contain the Faculty ID of their advisor). Sorted on student ID number.
- Binary search tree holding Faculty records (integer Faculty ID, a String name, a String level (lecturer, assistant prof, associate prof, etc), a String department, and a list of integers corresponding to all of the faculty member’s advisees’ ids). Sorted on faculty student ID number.
- Operator overloaders for both Student and Faculty classes to compare objects to one another
- When the program begins, it checks for faculty and student tables already in existence and deserializes this data. If the files do not exist, program initializes student and faculty tables to empty.


- Presents a menu to the user to allow them to manipulate the databases. Choices include: Print all students and their information (sorted by ascending id #), Print all faculty and their information (sorted by ascending id #), Find and display student information given the students id, Find and display faculty information given the faculty id, Given a student’s id, print the name and info of their faculty advisor, Given a faculty id, print ALL the names and info of his/her advisees, Add a new student, Delete a student given the id, Add a new faculty member, Delete a faculty member given the id, Change a student’s advisor given the student id and the new faculty id, Remove an advisee from a faculty member given the ids, Rollback, Exit
- Program supports referential integrity
- Rollback command will “undo” the previous action, but only if that action changed the structure of the database
