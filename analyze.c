#include "analyze.h"
#include "massages.h"
#include "set.h"
#include <string.h>


void analyze(char* line, Command* command, SetName* x, SetName* y, SetName* z,
                int* members, Error* error) {
    int i = 0;
    *error = NONE;/* resets it for later use. */
    *y = EMPTY;/* resets it for later use. */
    *z = EMPTY;/* resets it for later use. */

    *command = get_command(line, &i);
    if (*command == EMPTY_LINE) {
        return;
    } else if (*command == ERROR) {
        *error = INVALID_COMMAND;
        return;
    } else if (line[i] != ' ' && line[i] != '\t') {
        if (line[i] == ',') {
            *error = ILLEGAL_COMMA;
        } else if (*command == STOP && (line[i] == '\0' || line[i] == '\r')) {
            return;
        }
        *error = INVALID_COMMAND;
        return;
    }
    /* command is OK and has a white char after it */
    if (*command != STOP) {
        *x = get_name(line, &i);
        if (*x == ILLEGAL_NAME) {
            *error = INVALID_SET;
            return;
        }
        if (*command != PRINT) {/* needs a comma now */
            if (*command == READ) {
                *error = get_members(line, i, members);
                return;
            } else {/* union/intersect/sub/symdiff */
                while (*error == NONE) {
                    if ((line[i] == ' ') || (line[i] == '\t')) {
                        i += 1;
                    } else if (line[i] == ',') {
                        i += 1;
                        if (*y == EMPTY) {/* finding y's name */
                            *y = get_name(line, &i);
                            if (*y == ILLEGAL_NAME) {
                                *error = INVALID_SET;
                                return;
                            }
                        } else if (*z == EMPTY) {/* finding z's name */
                            *z = get_name(line, &i);
                            if (*z == ILLEGAL_NAME) {
                                *error = INVALID_SET;
                                return;
                            }
                            return;/* got all the information needed for these funcs */
                        } else {/* unnecessary comma in the middle of the line */
                            *error = MULTIPLE_COMMAS;
                            return;
                        }
                    } else if (line[i] == '\0' || line[i] == '\r') {/* cutting line short */
                        *error = MISSING_SET;
                        return;
                    } else {/* illegal char */
                        *error = ILLEGAL_CHAR;
                        return;
                    }
                }/* while */
            }/* command = union/intersect/sub/symdiff */
        }/* command != print */
    }/* command != stop */

    /* all commands but read */
    while (i < MAX_LEN) {
        if (line[i] == '\0' || line[i] == '\r') {
            return;
        } else if (line[i] == ' ' || line[i] == '\t') {
            i += 1;
        } else {
            if (line[i] == ',') {
                *error = ILLEGAL_COMMA;
            } else {
                *error = ILLEGAL_ENDING;
            }
            return;
        }
    }/* while */
}

Command get_command(char* line, int* iterator) {
    Command command = ERROR;
    char* read_set = "read_set";
    char* print_set ="print_set";
    char* union_set = "union_set";
    char* sub_set = "sub_set";
    char* intersect_set = "intersect_set";
    char* symdiff_set = "symdiff_set";
    char* stop = "stop";
    
    while (line[*iterator] == ' ' || line[*iterator] == '\t') {
        *iterator += 1;
    }
    if (line[*iterator] == '\0' || line[*iterator] == '\r') {
        command = EMPTY_LINE;
    } else if (check(&line[*iterator], read_set, strlen(read_set))) {
        *iterator += strlen(read_set);
        command = READ;
    } else if (check(&line[*iterator], print_set, strlen(print_set))) {
        *iterator += strlen(print_set);
        command = PRINT;
    } else if (check(&line[*iterator], union_set, strlen(union_set))) {
        *iterator += strlen(union_set);
        command = UNION;
    } else if (check(&line[*iterator], sub_set, strlen(sub_set))) {
        *iterator += strlen(sub_set);
        command = SUB;
    } else if (check(&line[*iterator], intersect_set, strlen(intersect_set))) {
        *iterator += strlen(intersect_set);
        command = INTERSECT;
    } else if (check(&line[*iterator], symdiff_set, strlen(symdiff_set))) {
        *iterator += strlen(symdiff_set);
        command = SYMDIFF;
    } else if (check(&line[*iterator], stop, strlen(stop))) {
        *iterator += strlen(stop);
        command = STOP;
    }

    return command;
}

SetName get_name(char* line, int* iterator) {
    char* set_a = "SETA";
    char* set_b = "SETB";
    char* set_c = "SETC";
    char* set_d = "SETD";
    char* set_e = "SETE";
    char* set_f = "SETF";
    int i = *iterator;

    while (i < MAX_LEN) {
        if (line[i] == ' ' || line[i] == '\t') {
            i += 1;
            continue;
        } else if (line[i] == '\0' || line[i] == '\r') {
            return ILLEGAL_NAME;
        } else if (check(&line[i], set_a, strlen(set_a))) {
            *iterator = i + strlen(set_a);
            return SETA;
        } else if (check(&line[i], set_b, strlen(set_b))) {
            *iterator = i + strlen(set_b);
            return SETB;
        } else if (check(&line[i], set_c, strlen(set_c))) {
            *iterator = i + strlen(set_c);
            return SETC;
        } else if (check(&line[i], set_d, strlen(set_d))) {
            *iterator = i + strlen(set_d);
            return SETD;
        } else if (check(&line[i], set_e, strlen(set_e))) {
            *iterator = i + strlen(set_e);
            return SETE;
        } else if (check(&line[i], set_f, strlen(set_f))) {
            *iterator = i + strlen(set_f);
            return SETF;
        } else {
            break;
        }
    }
    return ILLEGAL_NAME;
}

Error get_members(char* line, int iterator, int* members) {
    int i = 0;
    int first_comma = 0;/* chacks for a comma after set name */

    for (i = 0; i < (MAX_LEN/2); i++) {
        members[i] = -2;/* mark them */
    }

    i = 0;
    while (iterator < MAX_LEN && i < (MAX_LEN/2)) {
        if (line[iterator] == ' ' || line[iterator] == '\t') {
            iterator += 1;
        } else if (line[iterator] == ',') {
            if (!first_comma) {/* the comma after the set name */
                first_comma = 1;
            } else if (members[i] == -2) {/* multiple consecutive commas */
                return MULTIPLE_COMMAS;
            } else {/* comma marking to move to the next place */
                i += 1;
            }
            iterator += 1;
        } else if (line[iterator] >= '0' && line[iterator] <= '9') {
            /* if char is a digit */
            if (!first_comma) {/* missing a comma after the set name */
                return MISSING_COMMA;
            }
            if (members[i] == -2) {/* empty spot */
                members[i] = line[iterator] - '0';
            } else if (members[i] != -2) { /* num is bigger than 9 */
                members[i] *= 10;
                members[i] += line[iterator] - '0';
            }
            iterator += 1;
        } else if ((line[iterator] == '-') && (line[iterator+1] == '1')) {
            if (members[i] == -2) {/* marks the end of read func */
                members[i] = -1;
                iterator += 2;
                while (iterator < MAX_LEN) {
                    if (line[iterator] == '\0' || line[iterator] == '\r') {
                        return NONE;
                    } else if (line[iterator] == ',') {
                        return ILLEGAL_COMMA;
                    } else if (line[iterator] == ' ' || line[iterator] == '\t') {
                        iterator += 1;
                    } else {
                        return ILLEGAL_ENDING;/* extraneous text after '-1' */
                    }
                }/* while */
            } else {
                return MISSING_COMMA;
            }
        } else if (line[iterator] == '\0' || line[iterator] == '\r') {
            /* illegal read ending - missing '-1' */
            return ILLEGAL_READ_ENDING;
        } else {/* not an integer */
            return INVALID_MEMBER_TYPE;
        }
    }/* while */
    return ILLEGAL_READ_ENDING;
}

int check(char* first, char* second, int size) {
    int i = 0;
    for (i = 0; i < size; i++) {
        if (first[i] != second[i]) {
            return 0;
        }
    }
    return 1;
}



