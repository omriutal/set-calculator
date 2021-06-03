#ifndef __MASSAGES__H__
#define __MASSAGES__H__


/**
 * @brief: An enum used for handeling errors in the input.
 *         It's writen here and not just declaration because the comipler had
 *          problems. 
 */
typedef enum error_t {
    INVALID_COMMAND,
    INVALID_SET,
    MISSING_SET,
    INVALID_MEMBER_RANGE,
    INVALID_MEMBER_TYPE,
    ILLEGAL_READ_ENDING,
    ILLEGAL_ENDING,
    MULTIPLE_COMMAS,
    MISSING_COMMA,
    ILLEGAL_COMMA,
    MISSING_WHITE,
    ILLEGAL_CHAR,
    ILLEGAL_LINE_LEN,
    ILLEGAL_EXIT,
    NULL_ARGUMENT,
    NONE
} Error;

/**
 * List of functions in this header:
 *
 *	invalid_command - prints an error massage about command's name.
 *	invalid_set - prints an error massage about set's name.
 *
 *	missing_set - prints an error massage about missing a set's name.
 *
 *	invalid_member_range - prints an error massage about member not being in
 *              range.
 *	invalid_member_type - prints an error massage about member not being in
 *              an integer.
 *
 *	illegal_read_ending - prints an error about line not ending with -1.
 *	illegal_ending - prints an error massage about an illegal char at the end
 *              of the line.
 *
 *	multiple_commas - prints an error massage about multiple consecutive commas.
 *	missing_comma - prints an error massage about a missing comma.
 *	illegal_comma - prints an error massage about a comma being in the wrong
 *              place.
 *
 *	missing_white - prints an error massage about a missing space/tab.
 *	illegal_char - prints an error massage about a char being in the wrong
 *              place.
 *	illegal_line_len - prints an error massage about the line being too long.
 *
 *	illegal_exit - prints an error massage about exiting the program without
 *              the use of stop function.
 *
 *  null_argument - prints an error massage about getting a NULL as an argument.
 *
 *	intro - prints a massage explaining how to use the program.
 *
 */


void invalid_command();

void invalid_set();

void missing_set();

void invalid_member_range();

void invalid_member_type();

void illegal_read_ending();

void illegal_ending();

void multiple_commas();

void missing_comma();

void illegal_comma();

void missing_white();
void illegal_char();
void illegal_line_len();

void illegal_exit();

void null_argument();

void intro();


#endif  /*!__MASSAGES__H__*/