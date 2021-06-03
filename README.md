# set-calculator

This program is a set calculator. It has 6 sets for the user to use and 7 functions.

The sets names are: SETA, SETB, SETC, SETD, SETE and SETF.
They are stored in an array.
The sets can only have members which are integers and belong to the range [0,127].

The calculator functions are:
  1. read_set - a function that resets the set and adds members to it.
    It can be used the following way: "read_set SETX, member1, member2, ..., last_member, -1"
    * X can be A-F.
    * between the command and the set name must be a space or a tab.
    * there has to be a comma after the set name and after each member.
    * after '-1' there can only be spaces and tabs.
    * all members must be intergers and belong to [0,127].
    
  2. print_set - a function that prints the members of the given set.
    It can be used the following way: "print_set SETX"
    * X can be A-F.
    * between the command and the set name must be a space or a tab.
    * after the set name, there can only be spaces and tabs.

  3. union_set - a function that combines the members of the first 2 sets and stors them in the
                 third set.
    It can be used the following way: "union_set SETX, SETY, SETZ"
    * X can be A-F, Y can be A-F, Z can be A-F.
    * between the command and the set name must be a space or a tab.
    * there has to be a comma after the first and second sets' names.
    * after the third set name, there can only be spaces and tabs.

  4. intersect_set - a function that finds which members belong to both of the first 2 sets and
                     stors them in the third set.
    It can be used the following way: "intersect_set SETX, SETY, SETZ"
    * X can be A-F, Y can be A-F, Z can be A-F.
    * between the command and the set name must be a space or a tab.
    * there has to be a comma after the first and second sets' names.
    * after the third set name, there can only be spaces and tabs.

  5. sub_set - a function that finds all members which belong to the first set but don't belong to
               the second set and stors them in the third set.
    It can be used the following way: "sub_set SETX, SETY, SETZ"
    * X can be A-F, Y can be A-F, Z can be A-F.
    * between the command and the set name must be a space or a tab.
    * there has to be a comma after the first and second sets' names.
    * after the third set name, there can only be spaces and tabs.

  6. symdiff_set - a function that finds all members which belong to the first set but don't belong
                   to the second set and vice versa then it stors them in the third set.
    It can be used the following way: "symdiff_set SETX, SETY, SETZ"
    * X can be A-F, Y can be A-F, Z can be A-F.
    * between the command and the set name must be a space or a tab.
    * there has to be a comma after the first and second sets' names.
    * after the third set name, there can only be spaces and tabs.

  7. stop - a function that exits from the calculator.
    It can be used the following way: "stop"
    * after the command, there can only be spaces and tabs.

 The structs that are used in this program are:
  * bit - a struct that holds an unsigned int with the width of 1.
  * set - a struct that holds an array of SIZE (128) bits.
  
 Files used for this program are:
  * myset.c - this file has the main function in it and some helping functions.
  * set.h - this file has some macro defined in it, the declarations and definition of bit and set, the
            declarations of the 7 functions for the calculator and a couple of helping functions.
  * set.c - this file has the definition of the functions which are declared in the set.h file.
  * analyze.h - this file has the declarations and definition of the Command and SetName enums and the
                declarations of the some functions which are used to analyze the input.
  * analyze.c - this file has the definition of the functions which are declared in the analyze.h file.
  * massages.h - this file has the declarations and definition of the Error enum and the declarations of
                 the some functions which are used to print massages (mainly errors).
  * massages.c - this file has the definition of the functions which are declared in the massages.h file.
