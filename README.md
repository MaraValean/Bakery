# Bakery
A console application written in C for managing a bakery. Includes undo/redo, filter and tests.


Mary runs her family's bakery, “Bread'n Bagel”. Every day she struggles with keeping up to date with available stocks of raw materials and would like a program to help her manage the business more effectively. Each Material used in the bakery has: a name, a supplier, a quantity and the expiration date. Mary wants a software application that helps her in the following ways:
(a) Add, delete and update a material. A raw material is uniquely identified by its name, supplier and expiration date. If a material that already exists is added, its quantity will be modified (the new quantity is added to the existing one).
(b) See all available materials past their expiration date, containing a given string (if the string is empty, all materials past their expiration date will be considered).
(c) Display all materials from a given supplier, which are in short supply (quantity less than a user-provided value), sorted ascending by their quantities.
(d) Provide multiple undo and redo functionality. Each step will undo/redo the previous operation performed by the user.
