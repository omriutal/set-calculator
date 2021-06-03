#include "massages.h"
#include <stdio.h>


void invalid_command() {
    printf("ERROR: invalid command - the program do not have such command.\n");
    printf("The commands are: read_set, print_set, union_set, intersect_set,");
    printf(" sub_set, symdiff_set and stop.\n");
}

void invalid_set() {
    printf("ERROR: invalid set - program do not have a set with that name.\n");
    printf("The set are: SETA, SETB, SETC, SETD, SETE and SETF.\n");
}

void missing_set() {
    printf("ERROR: missing set - program did not get all sets which are\n");
    printf("\t\t\t\t\tnecessary for the command.\n");
}

void invalid_member_range() {
    printf("ERROR: invalid member - set member is out of range.\n");
    printf("All members must belong to [0,127].");
}

void invalid_member_type() {
    printf("ERROR: invalid member - set member is not an integer.\n");
}

void illegal_read_ending() {
    printf("ERROR: illegal read ending - list of set members did not end correctly.\n");
}

void illegal_ending() {
    printf("ERROR: illegal ending - extraneous text after end of command.\n");
    printf("read_set function must end with '-1");
}

void multiple_commas() {
    printf("ERROR: multiple commas - multiple consecutive commas.\n");
}

void missing_comma() {
    printf("ERROR: missing comma.\n");
}

void illegal_comma() {
    printf("ERROR: illegal comma.\n");
}

void missing_white() {
    printf("ERROR: a space or a tab must be after the command.\n");
}

void illegal_char() {
    printf("ERROR: illegal char.\n");
}

void illegal_line_len() {
    printf("ERROR: illegal line length - program does not accept lines so long.\n");
}

void illegal_exit() {
    printf("ERROR: illegal exit - program did not terminate with stop function.\n");
}

void null_argument() {
    printf("ERROR: NULL argument - program sent function a NULL as an argument.\n");
}

void intro() {
    printf("This is a set calculator.\n\n");
    printf("It can store up to 6 sets and they are:\n");
    printf("SETA, SETB, SETC, SETD, SETE and SETF.\n");
    printf("The function in this calculator are:\n");
    printf("read_set, print_set, union_set, intersect_set, sub_set,");
    printf(" symdiff_set and stop.\n\n");

    printf("Here is an explanation on each function:\n\n");

    printf("1. read_set: This function resets the set and stores members in it.\n");
    printf("To use it, you'll need to enter the following data:\n");
    printf("'read_set SETX, member1, member2, ..., last_member, -1'\n");
    printf("* X can be A-F\n");
    printf("* between the command and the set name must be a space or a tab.\n");
    printf("* there has to be a comma after the set name and after each member.\n");
    printf("* after '-1' there can only be spaces and tabs.\n");
    printf("* all members must be intergers and belong to [0,127].\n\n");

    printf("2. print_set: This function prints the members of the given set.\n");
    printf("To use it, you'll need to enter the following data:\n");
    printf("'print_set SETX'\n");
    printf("* X can be A-F\n");
    printf("* between the command and the set name must be a space or a tab.\n");
    printf("* after the set name, there can only be spaces and tabs.\n\n");

    printf("3. union_set: This function combines the members of the first 2");
    printf(" sets and stors them in the third set.\n");
    printf("To use it, you'll need to enter the following data:\n");
    printf("'union_set SETX, SETY, SETZ'\n");
    printf("* X can be A-F, Y can be A-F, Z can be A-F\n");
    printf("* between the command and the first set name must be a space or a tab.\n");
    printf("* there has to be a comma after the first and second sets' names.\n");
    printf("* after the third set name, there can only be spaces and tabs.\n\n");

    printf("4. intersect_set: This function finds which members belong to");
    printf(" both of the first 2 sets and stors them in the third set.\n");
    printf("To use it, you'll need to enter the following data:\n");
    printf("'intersect_set SETX, SETY, SETZ'\n");
    printf("* X can be A-F, Y can be A-F, Z can be A-F\n");
    printf("* between the command and the first set name must be a space or a tab.\n");
    printf("* there has to be a comma after the first and second sets' names.\n");
    printf("* after the third set name, there can only be spaces and tabs.\n\n");

    printf("5. sub_set: This function finds all members which belong to the");
    printf(" first set but don't belong to the second set and stors them in");
    printf(" the third set.\n");
    printf("To use it, you'll need to enter the following data:\n");
    printf("'sub_set SETX, SETY, SETZ'\n");
    printf("* X can be A-F, Y can be A-F, Z can be A-F\n");
    printf("* between the command and the first set name must be a space or a tab.\n");
    printf("* there has to be a comma after the first and second sets' names.\n");
    printf("* after the third set name, there can only be spaces and tabs.\n\n");

    printf("6. symdiff_set: This function finds all members which belong to the");
    printf(" first set but don't belong to the second set and vice versa then it");
    printf(" stors them in the third set.\n");
    printf("To use it, you'll need to enter the following data:\n");
    printf("'symdiff_set SETX, SETY, SETZ'\n");
    printf("* X can be A-F, Y can be A-F, Z can be A-F\n");
    printf("* between the command and the first set name must be a space or a tab.\n");
    printf("* there has to be a comma after the first and second sets' names.\n");
    printf("* after the third set name, there can only be spaces and tabs.\n\n");

    printf("7. stop: This function exits from the calculator.\n");
    printf("To use it, you'll need to enter the following data:\n");
    printf("'stop'\n");
    printf("* after the command, there can only be spaces and tabs.\n\n");
}
