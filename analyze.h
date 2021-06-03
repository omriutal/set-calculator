#ifndef __ANALYZE__H__
#define __ANALYZE__H__

#include "massages.h"


/**
 * @brief: An enum used for analyzing the input.
 *         It's writen here and not just declaration because the comipler had
 *          problems. 
 */
typedef enum command_t {
    READ,
    PRINT,
    UNION,
    INTERSECT,
    SUB,
    SYMDIFF,
    STOP,
    ERROR,
    EMPTY_LINE
} Command;

/**
 * @brief: An enum used for analyzing the input.
 *         It's writen here and not just declaration because the comipler had
 *          problems. 
 */
typedef enum set_name_t {
    SETA = 0,
    SETB = 1,
    SETC = 2,
    SETD = 3,
    SETE = 4,
    SETF = 5,
    ILLEGAL_NAME = 6,
    EMPTY = 7
} SetName;

/**
 * List of functions in this header:
 *
 *	analyze - analyze the line.
 *
 *	get_command - returns the command in the line.
 *	get_name - returns the name of the set.
 *	get_members - returns an array eith the set's members.
 *
 *	check - checks if the strings are the same.
 *
 */


/**
 * @brief: Analyze the line.
 *          1. Sends the line to get_command func:
 *              If command is EMPTY_LINE then returns.
 *              Else if it's ERROR then sets error to INVALID_COMMAND and returns.
 *              Else if the char right after the command isn't a 'white char':
 *               if char is a comma then sets error to ILLEGAL_COMMA.
 *               else if command is STOP and char marks end of line then returns.
 *               else sets error to INVALID_COMMAND and returns.
 *          2. If command isn't STOP, sends line to get_name func to get the set's name:
 *              If returned ILLEGAL_NAME, then sets error to INVALID_SET.
 *          3. If command isn't PRINT:
 *              If command is READ, goes to get_members func and returns.
 *              Else, tries to get the second and third sets' names. Incase of
 *               an error (such as: INVALID_SET, MULTIPLE_COMMAS, MISSING_SET
 *               or ILLEGAL_CHAR) returns after setting error to the problem.
 *          4. Checks the rest of the line to see if there is an error (such as:
 *               ILLEGAL_COMMA or ILLEGAL_ENDING).
 *              
 * 
 * @param line - array of chars, the size of MAX_LEN (80). doesn't change it.
 * @param command - pointer to store in it the command.
 * @param x - pointer to store in it the first set's name, if there is one.
 * @param y - pointer to store in it the second set's name, if there is one.
 * @param z - pointer to store in it the third set's name, if there is one.
 * @param members - array to store in it the set's members, if command is read.
 *                  members is the size of MAX_LINE/2 since at top it'll have
 *                  less members.
 * @param error - pointer to store in it the error in the line, if there is one.
 */
void analyze(char* line, Command* command, SetName* x, SetName* y, SetName* z,
                int* members, Error* error);

/**
 * @brief: Analyzes the command inside the line and returns it.
 *         As long as line[*iterator] is a 'white char' advances the iterator.
 *         After that, compares the text in the line to the commands:
 *              If recognizes a command, advances the iterator to right after
 *               the command and returns the command.
 *              Else, returns ERROR.
 *
 *         NOTE: doesn't check if there is an illegal comma or char right after
 *                the command.
 * 
 * @param line - array of chars, the size of MAX_LEN (80). doesn't change it.
 * @param iterator - pointer to int that holds the current place in the line.
 *
 * @return: ERROR - if doesn't recognize the command (error = INVALID_COMMAND).
 *          EMPTY_LINE - if line is empty.
 *          READ
 *          PRINT
 *          UNION
 *          SUB
 *          INTERSECT
 *          SYMDIFF
 *          STOP
 */
Command get_command(char* line, int* iterator);

/**
 * @brief: Analyzes the set's name inside the line and returns it.
 *         As long as line[*iterator] is a 'white char' advances the iterator.
 *         After that, compares the text in the line to the sets' names:
 *              If recognizes a name, advances the iterator to right after
 *               the name and returns the name.
 *              Else, returns ERROR.
 *
 *         NOTE: doesn't check if there is an illegal comma or char right after
 *                the name.
 * 
 * @param line - array of chars, the size of MAX_LEN (80). doesn't change it.
 * @param iterator - pointer to int that holds the current place in the line.
 *
 * @return: ILLEGAL_NAME - if doesn't recognize the set's name (error = INVALID_SET).
 *          SETA
 *          SETB
 *          SETC
 *          SETD
 *          SETE
 *          SETF
 */
SetName get_name(char* line, int* iterator);

/**
 * @brief: Sets the set's members inside the array (members).
 *          1. Resets all integers in the array to -2.
 *          2. Goes thriugh a loop on the line searching for a comma and a
 *              number after it untill it reach -1 which signal the end of the
 *              members input. Incase of an error (such as: MISSING_COMMA,
 *              MULTIPLE_COMMAS, ILLEGAL_ENDING, ILLEGAL_READ_ENDING or
 *              INVALID_MEMBER_TYPE) it returns it. Else, returns NONE.
 *
 *         NOTE: doesn't check if members are in range ([0,127]).
 * 
 * @param line - array of chars, the size of MAX_LEN (80). doesn't change it.
 * @param iterator - an integer that holds the current place in the line.
 * @param members - array to store in it the set's members, if command is read.
 *                  members is the size of MAX_LINE/2 since at top it'll have
 *                  less members.
 *
 * @return: MISSING_COMMA - the first non-'white char' wasn't a comma, which is
 *                          needed after the set's name.
 *          MULTIPLE_COMMAS - multiple consecutive commas.
 *          ILLEGAL_ENDING - a non-'white char' after -1.
 *          ILLEGAL_READ_ENDING - there was no -1 in the line.
 *          INVALID_MEMBER_TYPE - member type isn't an integer.
 *          NONE - didn't find an error.
 */
Error get_members(char* line, int iterator, int* members);

/**
 * @brief: Checks if the two strings are the same at the given length.
 * 
 * @param first - first string
 * @param second - second string
 * @param size - size of the strings (or the smaller one of the two).
 *
 * @return: 0, if the strings aren't the same.
 *          1, if are the same.
 */
int check(char* first, char* sec, int size);


#endif /* __ANALYZE__H__ */
