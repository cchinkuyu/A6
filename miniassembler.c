/*--------------------------------------------------------------------*/
/* miniassembler.c                                                    */
/* Author: Chimwemwe Chinkuyu                                   */
/*--------------------------------------------------------------------*/

#include "miniassembler.h"
#include <assert.h>
#include <stddef.h>

/*--------------------------------------------------------------------*/
/* Modify *puiDest in place,
   setting uiNumBits starting at uiDestStartBit (where 0 indicates
   the least significant bit) with bits taken from uiSrc,
   starting at uiSrcStartBit.
   uiSrcStartBit indicates the rightmost bit in the field.
   setField sets the appropriate bits in *puiDest to 1.
   setField never unsets any bits in *puiDest.                        */
static void setField(unsigned int uiSrc, unsigned int uiSrcStartBit,
                     unsigned int *puiDest, unsigned int uiDestStartBit,
                     unsigned int uiNumBits)
{

   /* Strip of the bits in the scr field to the left of the desired bits */
   uiSrc <<= 32 - (uiNumBits + uiSrcStartBit);

   /* Shift uiSrc to right justify */
   uiSrc >>= 32 - uiNumBits;

   /* Shift uiSrc to the left to align it with destination */
   uiSrc <<= uiDestStartBit;

   /* Insert uiSrc into the instruction */
   *puiDest |= uiSrc;
}
/*--------------------------------------------------------------------*/

unsigned int MiniAssembler_mov(unsigned int uiReg, int iImmed)
{
   unsigned int uiInstr;
   unsigned int uiImmed;

   /* Base Instruction Code */
   uiInstr = 0x52800000;

   /* Register to be inserted in instruction */
   setField(uiReg, 0, &uiInstr, 0, 5);

   /* Converts int iImmed to an unsigned int */
   uiImmed = (unsigned int)iImmed;

   setField(uiImmed, 0, &uiInstr, 5, 16);

   return uiInstr;
}

/*--------------------------------------------------------------------*/

unsigned int MiniAssembler_adr(unsigned int uiReg, unsigned long ulAddr,
   unsigned long ulAddrOfThisInstr)
{
   unsigned int uiInstr;
   unsigned int uiDisp;

   /* Base Instruction Code */
   uiInstr = 0x10000000;

   /* Register to be inserted in instruction */
   setField(uiReg, 0, &uiInstr, 0, 5);

   /* Displacement to be split into immlo and immhi and inserted */
   uiDisp = (unsigned int)(ulAddr - ulAddrOfThisInstr);

   setField(uiDisp, 0, &uiInstr, 29, 2);
   setField(uiDisp, 2, &uiInstr, 5, 19);

   return uiInstr;
}

/*--------------------------------------------------------------------*/

unsigned int MiniAssembler_strb(unsigned int uiFromReg,
   unsigned int uiToReg)
{
   unsigned int uiInstr;

   /* Base Instruction Code */
   uiInstr = 0x39000000;

   setField(uiFromReg, 0, &uiInstr, 0, 5);
   setField(uiToReg, 0, &uiInstr, 5, 5);

   return uiInstr;
}

/*--------------------------------------------------------------------*/

unsigned int MiniAssembler_b(unsigned long ulAddr,
   unsigned long ulAddrOfThisInstr)
{
   unsigned int uiInstr;
   unsigned int uiImm = (unsigned int)((ulAddr - ulAddrOfThisInstr) / 4);

   /* Base Instruction Code */
   uiInstr = 0x14000000;

   setField(uiImm, 0, &uiInstr, 0, 26);

   return uiInstr;
}
