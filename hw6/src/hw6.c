/* Siddharth Korukonda
   CSE 220.01
   115607752
*/

#include "hw6.h"

int main(int argc, char *argv[]) {
    /* Edge case check to see if the number of arguments is less than 7. We need at least 7 arguments to include the program name, -s flag, -r flag, their
       respective values, and the input/output file names. The conditional checks that and returns the error code if the conditional is true
    */
    if (argc < 7) {
        // Indicates that an argument is missing
        return MISSING_ARGUMENT;
    }

    // Initializes the count for the flags. These counts are used to identify if the flags are present and if there are any duplicates present
    int has_s = 0;
    int has_r = 0;
    int has_l = 0;

    // Initializes the pointers to store the search and replace strings that are extracted from the arguments
    char *search = NULL;
    char *replace = NULL;

    /* Sets the lower and upper bounds for the line range for each file. The 'start_line' bound indicates that the file has at least some content in it
       while the 'end_line' bound indicates that the file has reached the maximum possible length. These values are later used to enable full file
       processing, unless it is overridden by the -l flag
    */
    long start_line = 1;
    long end_line = 2147483647; // Maximum possible 32-bit signed number to represent the end of the file

    /* A for loop to parse the command line arguments. Note that the last two flags are input and output filenames and are therefore excluded. The for loop
       searches for the search string (-s), replacement string (-r), and optionally line range (-l) flags. The loop checks and validates each flag and
       ensures that each flag ensures at most once and returns an error code if the flag is absent or if there is more than one of the flags. The loop
       also checks if the flags are then followed by valid arguments. Note that the '-l' flag is optional and if the flag is absent, that is allowed, and
       if the flag is present, then its value is seperated by two comma seperated integers. The error codes that the loop checks pertain to duplicate flags,
       missing arguments, and invalid line number ranges. 
    */
    for (int i=1; i<argc-2; i++) {
        // This conditional handles the '-s' flag
        if (strcmp(argv[i], "-s") == 0) {
            if (has_s) {
                // Indicates that there is a duplicate '-s' flag
                return DUPLICATE_ARGUMENT;
            }

            // Ensure '-s' is followed by a valid value, not another flag or end of argument
            if (i+1>=argc || argv[i+1][0] == '-') {
                // Indicates that the argument is missing after the '-s' flag
                return S_ARGUMENT_MISSING;
            }

            /* These next three lines of code stores the search string, marks the '-s' as seen by making the 'has_s' count to one, and skips the search
               string in the next iteration
            */
            search = argv[i+1];
            has_s = 1;
            i++;
        }
        // This conditional handles the '-r' flag
        else if (strcmp(argv[i], "-r") == 0) {
            if (has_r) {
                // Indicates that there is a duplicate '-r' flag
                return DUPLICATE_ARGUMENT;
            }

            // Ensure '-r' is followed by a valid value, not another flag or end of argument
            if (i+1>=argc || argv[i+1][0] == '-') {
                // Indicates that the argument is missing after the '-r' flag
                return R_ARGUMENT_MISSING;
            }

            /* These next three lines of code stores the replacement string, marks the '-r' as seen by making the 'has_r' count to one, and skips the 
               replacement string in the next iteration
            */
            replace = argv[i+1];
            has_r = 1;
            i++;
        }
        // This conditional handles the optional '-l' flag
        else if (strcmp(argv[i], "-l") == 0) {
            if (has_l) {
                // Indicates that there is a duplicate '-l' flag
                return DUPLICATE_ARGUMENT;
            }

            // Ensure '-l' is followed by a valid value, not another flag or end of argument
            if (i+1>=argc || argv[i+1][0] == '-') {
                return L_ARGUMENT_INVALID;
            }
        
            // These next three lines of code gets the argument string for line range and extracts the starting and ending line numbers
            char *line_arg = argv[i+1];
            char *start = strtok(line_arg, ",");
            char *end = strtok(NULL, ",");

            // Conditional to check if both the starting and ending are present. If one of them is missing, then the argument is invalid
            if (!start || !end) {
                // Indicates that the '-l' flag has invalid arguments
                return L_ARGUMENT_INVALID;
            }

            /* Converts the starting and ending into values. This is essential because we need to ensure that both line numbers are valid and logically 
               ordered before using them to determine which lines of the input file should undergo the search-and-replace
            */
            long start_value = strtol(start, NULL, 10);
            long end_value = strtol(end, NULL, 10);

            /* This conditional checks if the starting and ending values are positive and in order. If not, then an error code is returned to indicate that
               the '-l' argument is invalid
            */
            if (start_value<1 || end_value<1 || start_value>end_value) {
                return L_ARGUMENT_INVALID;
            }

            /* These next four lines of code assigns the validated line range, marks the '-s' as seen by making the 'has_s' count to one, and skips the 
               line value in the next iteration
            */
            start_line = start_value;
            end_line = end_value;
            has_l = 1;
            i++;
        }
    }

    /* This conditional checks if the '-s' flag is present, and returns an error code if there are any arguments missing. This is important to make sure
       the program can function safely as intended
    */
    if (!has_s) {
        return S_ARGUMENT_MISSING;
    }

    /* This conditional checks if the '-r' flag is present, and returns an error code if there are any arguments missing. This is important to make sure
       the program can function safely as intended
    */
    if (!has_r) {
        return R_ARGUMENT_MISSING;
    }

    // This conditional checks if the input and output filenames are the same to avoid overwriting input
    if (strcmp(argv[argc-2], argv[argc-1]) == 0) {
        // Indicates that there is some error between the input and output filenames and returns that the output file is unwritable
        return OUTPUT_FILE_UNWRITABLE;
    }

    // Gets input and output filenames from the last two arguments
    char *input_file = argv[argc-2];
    char *output_file = argv[argc-1];

    // Opens the input file for reading
    FILE *in = fopen(input_file, "r");
    // Conditional to check if there an error with the input file
    if (!in) {
        // Indicates that there is no input file present
        return INPUT_FILE_MISSING;
    }

    // Opens the output file for writing
    FILE *out = fopen(output_file, "w");
    // Conditonal to check if there is an error with the output file
    if (!out) {
        // Closes the input file to avoid a resource leak
        fclose(in);
        // Indicates that the output file is unwritable
        return OUTPUT_FILE_UNWRITABLE;
    }

    /* This conditional checks if the search and replace strings are valid and not NULL or empty. A NULL or empty search or replacement strings would make
       replacements meaningless or undefined, which is a problem
    */
    if (!search || strlen(search) == 0 || !replace || strlen(replace) == 0) {
        // Closes the input and output file to avoid resource leaks
        fclose(in);
        fclose(out);
        // Indicates that there are argument(s) missing
        return MISSING_ARGUMENT;
    }

    // Allocates memory for line buffer to hold lines from the file
    size_t buffer_size = 64;
    char *line = malloc(buffer_size);
    // Conditional to check if there is an error with the memory allocation
    if (!line) {
        // Closes the input and output file to avoid resource leaks 
        fclose(in);
        fclose(out);
        // Indicates that there are argument(s) missing
        return MISSING_ARGUMENT;
    }

    // Tracks current line number while reading file
    long curr_line = 1;
    // Current length of the line being read
    size_t len = 0;
    // Stores each character read from file
    int curr_char;

    // This loop is used to read the input file character by character until the EOF (end of file) marker is reached
    while ((curr_char = fgetc(in)) != EOF) {
        // Conditional to check if the buffer is full, and if the allocated memory is full, reallocate more memory
        if (len + 1 >= buffer_size) {
            buffer_size *= 2;
            char *new_line = realloc(line, buffer_size);

            // Conditional to check if the memory reallocation was done successfully
            if (!new_line) {
                // CLoses all files to avoid resouces leaks
                free(line);
                fclose(in);
                fclose(out);
                // Indicates that there are argument(s) missing
                return MISSING_ARGUMENT;
            }

            line = new_line;
        }

        // Conditional to check if a newline character is reached, and if a newline character is reached, we should process the full line
        if (curr_char == '\n') {
            line[len] = '\0';

            /* Conditional to check tf current line is within the specified range, and if it is within the specified range, we should apply 
               search-and-replace
            */
            if (curr_line >= start_line && curr_line <= end_line) {
                char *ptr = line;
                char *found;
                size_t search_len = strlen(search);

                /* This loop searches and replaces all instances of the search string. The loop first writes before the match, writes the replacement
                   text, and then moves past the replaced part. This is crucial to successfully rewrite the text without doing the process again
                */
                while ((found = strstr(ptr, search)) != NULL) {
                    fwrite(ptr, 1, found - ptr, out);
                    fputs(replace, out);
                    ptr = found + search_len;
                }

                // Writes remaining part of the line
                fputs(ptr, out);
            } else {
                // Writes line as-is if out of range
                fputs(line, out);
            }

            /* The next three lines of code writes the newline character whilst preserving the structure, resets line length for the next line, then
               increments the count to progress further
            */
            fputc('\n', out);
            len = 0;
            curr_line++;
        } else {
            // Appends character to line buffer
            line[len++] = curr_char;
        }
    }

    // Frees the allocated memory to avoid memory leaks
    free(line);

    // Closes the input and output files to avoid memory leaks
    fclose(in);
    fclose(out);
    return 0;
}
