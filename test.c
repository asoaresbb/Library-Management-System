#include <stdio.h>

int main()
{
    char option;

    while (1)
    {
        printf("Enter your option: ");
        fflush(stdout);

        option = getchar(); // Read one character from stdin

        // Clear the input buffer
        int c;
        while ((c = getchar()) != '\n' && c != EOF)
            ;

        if (option == EOF)
        {
            // Handle end-of-file condition
            break;
        }

        // Process the option, for example, printing it
        printf("You entered: %c\n", option);
    }

    return 0;
}