#ifndef __SET__H__
#define __SET__H__

#include "massages.h"


/**
 * @brief: According to the forum, the max length of a line is 80 chars. I took
 *         extra space just in case.
 */
#define MAX_LEN 80

/**
 * @brief: Max amount of members which can be printed in a line.
 */
#define MAX_PRINT 16

/**
 * @brief: Amount of sets used in program.
 */
#define SET_AMOUNT 6

/**
 * @brief: Size of legal range.
 */
#define SIZE 128

/**
 * @brief: The first legal value in range.
 */
#define START_RANGE 0

/**
 * @brief: The last legal value in range.
 */
#define END_RANGE 127

/**
 * @brief: A bit struct that's holds less space than an unsigned int.
 *         It's writen here and not just declaration because the comipler had
 *          problems. 
 */
typedef struct bit_t {
    unsigned int value : 1;
} bit;

/**
 * @brief: A set struct that's holds an array of SIZE (128) bits.
 *         It's writen here and not just declaration because the comipler had
 *          problems. 
 */
typedef struct set_t {
    bit bits[SIZE];
} set;

/**
 * @brief: Sets 'Set' as a pointer to a struct set_t.
 */
typedef set* Set;

/**
 * List of functions in this header:
 *
 *	read_set - resets and enetrs members to set.
 *	print_set - prints set's members.
 *	union_set - takes all of the first and second sets' members and sets them
 *              in the third one.
 *	intersect_set - takes all of the members which belong to both the first and
 *              second sets and sets them in the third one.
 *	sub_set - takes all of the members which belong to the first set and don't
 *              belong to the second set and sets them in the third one.
 *	symdiff_set - takes all of the members which belong to the first and second
 *              sets and don't belong to both sets and sets them in the third one.
 *	stop - exits the program.
 *
 *	clean - turns off all bits in the set.
 *	copy_set - copies the first set to the second one.
 *
 */


/**
 * @brief: Enetrs members to set.
 *          1. Creates a temporary set and resets it.
 *          2. Goes through the array (nums):
 *              If one of the members of the array (nums) isn't in range
 *               ([0,127]), returns an error.
 *              Else turns on the corresponding bit.
 *          3. When reaches -1, copies the the temporary set to x and returns.
 *              If reaches the end of the loop and didn't pass '-1' then
 *              returns an error.
 * 
 * @param x - pointer to set.
 * @param nums - array with integers.
 *
 * @return: NULL_ARGUMENT - if the array (nums) or the pointer to the set are NULL.
 *          INVALID_MEMBER_RANGE - if one of the integers in the array (nums)
 *              isn't in range ([0,127]).
 *          ILLEGAL_READ_ENDING - if array (nums) didn't end with -1.
 *          NONE - otherwise.
 */
Error read_set(Set x, int* nums);

/**
 * @brief: Prints the set's members.
 *         Goes through the set and for evry bit that is turned on prints the
 *          bit's number. If non of the bits are turned on, prints a masssage
 *          that the set is empty.
 *         Prints up to MAX_PRINT (16) numbers in a line.
 *
 *         NOTE: if x is null prints error massage via null_argument func.
 * 
 * @param x - pointer to set.
 */
void print_set(Set x);

/**
 * @brief: Takes all of the first and second sets' members and sets them in the
 *          third one.
 *
 *          1. Creates a temporary set and resets it.
 *          2. Goes through the first and second sets at the same time. If the
 *              bit in one of them is turned on, it turns on the bit in the
 *              temporary set.
 *          3. When done copies the temporary set to the third set.
 * 
 * @param x - pointer to the first set.
 * @param y - pointer to the second set.
 * @param z - pointer to the third set.
 */
void union_set(Set x, Set y, Set z);

/**
 * @brief: Takes all of the members which belong to both the first and
 *          second sets and sets them in the third one.
 *
 *          1. Creates a temporary set and resets it.
 *          2. Goes through the first and second sets at the same time. If the
 *              bit in both of them is turned on, it turns on the bit in the
 *              temporary set.
 *          3. When done copies the temporary set to the third set.
 * 
 * @param x - pointer to the first set.
 * @param y - pointer to the second set.
 * @param z - pointer to the third set.
 */
void intersect_set(Set x, Set y, Set z);

/**
 * @brief: Takes all of the members which belong to the first set and don't
 *          belong to the second set and sets them in the third one.
 *
 *          1. Creates a temporary set and resets it.
 *          2. Goes through the first and second sets at the same time. If the
 *              bit in the first set is turned on and turned off in the second
 *              set, it turns on the bit in the temporary set.
 *          3. When done copies the temporary set to the third set.
 * 
 * @param x - pointer to the first set.
 * @param y - pointer to the second set.
 * @param z - pointer to the third set.
 */
void sub_set(Set x, Set y, Set z);

/**
 * @brief: Takes all of the members which belong to the first and second
 *          sets and don't belong to both sets and sets them in the third one.
 *
 *          1. Creates 3 temporary sets.
 *          2. Sends one temporary set to sub_set function as the third set
 *              with the first and second sets accordingly.
 *          3. Sends another temporary set to sub_set function as the third set
 *              with the first and second sets as the second and first sets
 *              accordingly.
 *          4. Sends the third temporary set to union_set function as the third
 *              set with the other 2 temporary sets as the first and second sets.
 * 
 * @param x - pointer to the first set.
 * @param y - pointer to the second set.
 * @param z - pointer to the third set.
 */
void symdiff_set(Set x, Set y, Set z);

/**
 * @brief: Exits the program with 0 as exit value.
 */
void stop();

/**
 * @brief: Turns off all bits in the set.
 * 
 * @param x - pointer to set.
 */
void clean(Set);

/**
 * @brief: Copies every bit's value in the first set to the second set.
 *         If one of the pointers is NULL, returns without doing anything.
 *
 */
void copy_set(Set, Set);


#endif  /*!__SET__H__*/