
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>

int main(int argc, char *argv[])
{
    FILE *fp;
    unsigned int ch;
    long file_pos;
    int i;

    if (argc != 2) {
        printf("\nUsage: print_bytes file.\n");
        exit(EXIT_FAILURE);
    }

    if ((fp = fopen(argv[1], "rb")) == NULL) {
            printf("\nError: cannot open %s.\n", argv[1]);
            exit(EXIT_FAILURE);
    }
            
    printf("\n");
    printf(" Offset                    Bytes                         " 
           " Characters\n");
    printf("--------    -------------------------------------    " 
           " ----------------------\n");

    fseek(fp, 0L, SEEK_SET);
    while (true) {
        file_pos = ftell(fp);
        printf("  %ld\t\t", file_pos);

        for (i = 0; i < 10 && ((ch = getc(fp)) != EOF); i++) {
            printf("%x ", ch);
        }

        printf("\t\t");
        fseek(fp, file_pos, SEEK_SET);

        for (i = 0; i < 10 && ((ch = getc(fp)) != EOF); i++) {
            if (!isprint(ch))
                ch = '.';
            printf("%c ", ch);
        }
        printf("\n");
        if (ch == EOF)
            break;
    }
    
    return 0;
}
