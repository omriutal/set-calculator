#include "set.h"
#include "analyze.h"
#include "massages.h"
#include <stdio.h>

/**
 * @brief: This program is a set calculator. It has 6 sets for the user to use
 *          and 7 functions.
 *
 *         The sets names are: SETA, SETB, SETC, SETD, SETE and SETF. They are
 *          stored in an array. The sets can only have members which are
 *          integers and belong to the range [0,127].
 *
 *         The calculator functions are:
 *          1. read_set - a function that resets the set and adds members to it.
 *              It can be used the following way:
 *              "read_set SETX, member1, member2, ..., last_member, -1"
 *              # X can be A-F.
 *              # between the command and the set name must be a space or a tab.
 *              # there has to be a comma after the set name and after each member.
 *              # after '-1' there can only be spaces and tabs.
 *              # all members must be intergers and belong to [0,127].
 *          2. print_set - a function that prints the members of the given set.
 *              It can be used the following way:
 *              "print_set SETX"
 *              # X can be A-F.
 *              # between the command and the set name must be a space or a tab.
 *              # after the set name, there can only be spaces and tabs.
 *          3. union_set - a function that combines the members of the first 2
 *              sets and stors them in the third set.
 *              It can be used the following way:
 *              "union_set SETX, SETY, SETZ"
 *              # X can be A-F, Y can be A-F, Z can be A-F.
 *              # between the command and the set name must be a space or a tab.
 *              # there has to be a comma after the first and second sets' names.
 *              # after the third set name, there can only be spaces and tabs.
 *          4. intersect_set - a function that finds which members belong to
 *              both of the first 2 sets and stors them in the third set.
 *              It can be used the following way:
 *              "intersect_set SETX, SETY, SETZ"
 *              # X can be A-F, Y can be A-F, Z can be A-F.
 *              # between the command and the set name must be a space or a tab.
 *              # there has to be a comma after the first and second sets' names.
 *              # after the third set name, there can only be spaces and tabs.
 *          5. sub_set - a function that finds all members which belong to the
 *              first set but don't belong to the second set and stors them in
 *              the third set.
 *              It can be used the following way:
 *              "sub_set SETX, SETY, SETZ"
 *              # X can be A-F, Y can be A-F, Z can be A-F.
 *              # between the command and the set name must be a space or a tab.
 *              # there has to be a comma after the first and second sets' names.
 *              # after the third set name, there can only be spaces and tabs.
 *          6. symdiff_set - a function that finds all members which belong to
 *              the first set but don't belong to the second set and vice versa
 *              then it stors them in the third set.
 *              It can be used the following way:
 *              "symdiff_set SETX, SETY, SETZ"
 *              # X can be A-F, Y can be A-F, Z can be A-F.
 *              # between the command and the set name must be a space or a tab.
 *              # there has to be a comma after the first and second sets' names.
 *              # after the third set name, there can only be spaces and tabs.
 *          7. stop - a function that exits from the calculator.
 *              It can be used the following way:
 *              "stop"
 *              # after the command, there can only be spaces and tabs.
 *
 *         The structs that are used in this program are:
 *          bit - a struct that holds an unsigned int with the width of 1.
 *          set - a struct that holds an array of SIZE (128) bits.
 *
 *         Files used for this program are:
 *          myset.c - this file has the main function in it and some helping
 *                     functions.
 *          set.h - this file has some macro defined in it, the declarations
 *                      and definition of bit and set, the declarations of the
 *                      7 functions for the calculator and a couple of helping
 *                      functions.
 *          set.c - this file has the definition of the functions which are
 *                      declared in the set.h file.
 *          analyze.h - this file has the declarations and definition of the
 *                      Command and SetName enums and the declarations of the
 *                      some functions which are used to analyze the input.
 *          analyze.c - this file has the definition of the functions which are
 *                      declared in the analyze.h file.
 *          massages.h - this file has the declarations and definition of the
 *                      Error enum and the declarations of the some functions
 *                      which are used to print massages (mainly errors).
 *          massages.c - this file has the definition of the functions which are
 *                      declared in the massages.h file.
 *
 */

/**
 * @brief: Declerations of helping functions.
 *         Discerption is above each function.
 */
void print_line(char*);
int get_line(char*, Error*);
void clean_line(char*);
void handle_error(Error error);
void do_command(Command, SetName, SetName, SetName, set*, int*);


int main() {
    set sets[SET_AMOUNT];
    char line[MAX_LEN];
    int status = 0, i = 0;
    int members[MAX_LEN/2];/* array to store in it the set's members, if
                              command is read. members is the size of
                              MAX_LINE/2 since at top it'll have less members. */
    SetName x = EMPTY, y = EMPTY, z = EMPTY;
    Command command;
    Error error = NONE;

    for (i = 0; i < SET_AMOUNT; i++) {
        clean(&sets[i]);
    }
    intro();
    while (status != -1) {
        printf(">>> ");/* prompt to indicate that the calculatour is ready for a new command.*/
        status = get_line(line, &error);/* 0 = good, -1 = EOF */
        print_line(line);
        handle_error(error);

        analyze(line, &command, &x, &y, &z, members, &error);
        if (error != NONE) {
            handle_error(error);
        } else {/* error == NONE */
            do_command(command, x, y, z, sets, members);
        }
        error = NONE;
    }/* while */
    illegal_exit();
    stop();

    return 0;
}

/**
 * @brief: Prints the line.
 *         If line is NULL, prints nothing.
 * 
 * @param line - array of chars, the size of MAX_LEN (80).
 */
void print_line(char* line) {
    int i = 0;

    if (!line) {
        return;
    }

    for (i = 0; i < MAX_LEN; i ++) {
        if (line[i] == '\0') {
            break;
        }
        putchar(line[i]);
    }
    putchar('\n');
}

/**
 * @brief: Gets the line from the user.
 *          1. Uses the clean_line function to reset the array (line).
 *          2. Uses the getchar function in a while loop to store the chars
 *              from the input in the array (line). Continues untill it gets an
 *              '\n' char or an EOF (and then return with -1).
 *          3. If stored MAX_LEN (80) amount of chars goes into a second while
 *              loop. Then checks to see if there is a non-'white char' in the
 *              rest of the line.
 *              If there is, stores ILLEGAL_LINE_LEN in error.
 *              If reaches EOF return -1.
 *
 *         NOTE: changes evey tab into a space before storing it in line.
 *         NOTE: even though it changes every tab to a space the program still
 *                checks for tabs later on.
 * 
 * @param line - array of chars, the size of MAX_LEN (80).
 * @param error - pointer to an Error (enum).
 *
 * @return: -1, if getchar function got an EOF.
 *          0, otherwise.
 */
int get_line(char* line, Error* error) {
    int i = 0;
    char x;

    clean_line(line);
    while ((x = getchar()) != '\n') {
        if ((i == 0 || line[i-1] == ' ') && (x == ' ' || x == '\t')) {
            /* multiple white chars */
            continue;
        } else if  (x == EOF) {
            return -1;/* EOF */
        } else if (i == MAX_LEN) {/* line length error */
            while ((x = getchar()) != '\n') {/* unusable data */
                if  (x == EOF) {
                    return -1;/* EOF */
                } else if (x != ' ' && x != '\t') {/* if a non-white char */
                    *error = ILLEGAL_LINE_LEN;
                }
            }
            break;
        }
        if (x == '\t') {
            x = ' ';
        }
        line[i] = x;
        i += 1;
    }
    return 0;
}

/**
 * @brief: Resets all chars in the array (line) to '\0'.
 * 
 * @param line  - array of chars, the size of MAX_LEN (80).
 */
void clean_line(char* line) {
    int i = 0;
    for (i = 0; i < MAX_LEN; i ++) {
        line[i] = '\0';
    }
}

/**
 * @brief: Prints the corresponding massage (through functions from massages.h)
 *          to the error the function got.
 *
 *         NOTE: incase error is ILLEGAL_EXIT, the funstion will also call the
 *                stop function.
 * 
 * @param error  - an enum of Error type.
 */
void handle_error(Error error) {
    switch (error) {
        case INVALID_COMMAND:
            invalid_command();
            return;
        case INVALID_SET:
            invalid_set();
            return;
        case MISSING_SET:
            missing_set();
            return;
        case INVALID_MEMBER_RANGE:
            invalid_member_range();
            return;
        case INVALID_MEMBER_TYPE:
            invalid_member_type();
            return;
        case ILLEGAL_READ_ENDING:
            illegal_read_ending();
            return;
        case ILLEGAL_ENDING:
            illegal_ending();
            return;
        case MULTIPLE_COMMAS:
            multiple_commas();
            return;
        case MISSING_COMMA:
            missing_comma();
            return;
        case ILLEGAL_COMMA:
            illegal_comma();
            return;
        case MISSING_WHITE:
            missing_white();
            return;
        case ILLEGAL_CHAR:
            illegal_char();
            return;
        case ILLEGAL_LINE_LEN:
            illegal_line_len();
            return;
        case ILLEGAL_EXIT:
            illegal_exit();
            stop();
        case NULL_ARGUMENT:
            null_argument();
            return;
        default:/* NONE */
            return;
    }
}

/**
 * @brief: Operates the corresponding function (from set.h) according to the var in commmand.
 *         Incase of an error send it to the handle_error function.
 * 
 * @param command - an enum of Command type.
 * @param x - an enum of SetName type. used for the first set in the line.
 * @param y - an enum of SetName type. used for the second set in the line.
 * @param z - an enum of SetName type. used for the third set in the line.
 * @param sets - an array of sets, the size of SET_AMOUNT (6).
 * @param members - an array of integers, the size of MAX_LEN/2 (40).
 */
void do_command(Command command, SetName x, SetName y, SetName z, set sets[], int members[]) {
    switch (command) {
        case STOP:
            stop();
        case READ:
            if (x == EMPTY ) {
                handle_error(MISSING_SET);
            } else if (x == ILLEGAL_NAME) {
                handle_error(INVALID_SET);
            } else {
                handle_error(read_set(&sets[x], members));
            }
            return;
        case PRINT:
            if (x == EMPTY ) {
                handle_error(MISSING_SET);
            } else if (x == ILLEGAL_NAME) {
                handle_error(INVALID_SET);
            } else {
                print_set(&sets[x]);
            }
            return;
        case UNION:
            if (x == EMPTY || y == EMPTY || z == EMPTY) {
                handle_error(MISSING_SET);
            } else if (x == ILLEGAL_NAME || y == ILLEGAL_NAME || z == ILLEGAL_NAME) {
                handle_error(INVALID_SET);
            } else {
                union_set(&sets[x], &sets[y], &sets[z]);
            }
            return;
        case INTERSECT:
            if (x == EMPTY || y == EMPTY || z == EMPTY) {
                handle_error(MISSING_SET);
            } else if (x == ILLEGAL_NAME || y == ILLEGAL_NAME || z == ILLEGAL_NAME) {
                handle_error(INVALID_SET);
            } else {
                intersect_set(&sets[x], &sets[y], &sets[z]);
            }
            return;
        case SUB:
            if (x == EMPTY || y == EMPTY || z == EMPTY) {
                handle_error(MISSING_SET);
            } else if (x == ILLEGAL_NAME || y == ILLEGAL_NAME || z == ILLEGAL_NAME) {
                handle_error(INVALID_SET);
            } else {
                sub_set(&sets[x], &sets[y], &sets[z]);
            }
            return;
        case SYMDIFF:
            if (x == EMPTY || y == EMPTY || z == EMPTY) {
                handle_error(MISSING_SET);
            } else if (x == ILLEGAL_NAME || y == ILLEGAL_NAME || z == ILLEGAL_NAME) {
                handle_error(INVALID_SET);
            } else {
                symdiff_set(&sets[x], &sets[y], &sets[z]);
            }
            return;
        default:/* EMPTY_LINE */
            return;
    }
}

