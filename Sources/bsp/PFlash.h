/*******************************************************************************
* Freescale Semiconductor Inc.
* (c) Copyright 2004-2005 Freescale Semiconductor, Inc.
* ALL RIGHTS RESERVED.
********************************************************************************
Services performed by FREESCALE in this matter are performed AS IS and without 
any warranty. CUSTOMER retains the final decision relative to the total design 
and functionality of the end product. FREESCALE neither guarantees nor will be 
held liable by CUSTOMER for the success of this project.
FREESCALE DISCLAIMS ALL WARRANTIES, EXPRESSED, IMPLIED OR STATUTORY INCLUDING, 
BUT NOT LIMITED TO, IMPLIED WARRANTY OF MERCHANTABILITY OR FITNESS FOR 
A PARTICULAR PURPOSE ON ANY HARDWARE, SOFTWARE ORE ADVISE SUPPLIED TO THE PROJECT
BY FREESCALE, AND OR NAY PRODUCT RESULTING FROM FREESCALE SERVICES. IN NO EVENT
SHALL FREESCALE BE LIABLE FOR INCIDENTAL OR CONSEQUENTIAL DAMAGES ARISING OUT OF 
THIS AGREEMENT.

CUSTOMER agrees to hold FREESCALE harmless against any and all claims demands or 
actions by anyone on account of any damage, or injury, whether commercial, 
contractual, or tortuous, rising directly or indirectly as a result of an advise
or assistance supplied CUSTOMER in connection with product, services or goods 
supplied under this Agreement.
********************************************************************************
* File      PFlash.h
* Owner     b01802
* Version   1.0 
* Date      Dec-02-2010
* Classification   General Business Information
* Brief     Program and Erase functions
********************************************************************************
* Detailed Description:
********************************************************************************
Revision History:
Version  Date          Author    Description of Changes
1.0      Feb-24-2010   b01802    Initial version
*******************************************************************************/
#ifndef _FLASH_H
#define _FLASH_H
#include "S12_COMMON.h"
/**** P-Flash and D-Flash Commands ****/

#define ERASE_VERIFY_ALL_BLOCKS  0x01 
/* Verify that all program and data Flash blocks are erased. */
/* CCOBIX end = 0 */
/* CCOB Params - NONE */
/* MGSTAT set if fault */

#define ERASE_VERIFY_BLOCK       0X02      
/* Verify that a Flash block is erased. */
/* CCOBIX end = 0 */
/* CCOB Params - gpage */
/* MGSTAT set if fault */

#define ERASE_ALL_BLOCKS         0x08 
/* Erase all program and data Flash blocks.
   An erase of all Flash blocks is only possible when the FPLDIS, FPHDIS, and FPOPEN
   bits in the FPROT register and the EPDIS and EPOPEN bits in the EPROM register are
   set prior to launching the command. */
/* CCOBIX end = 0 */
/* CCOB Params - NONE */
/* MGSTAT set if fault, FPVIOL / ACCERR set where appropriate */

#define UNSECURE_FLASH           0x0B 
/*Supports a method of releasing MCU security by erasing all program and data Flash
  blocks and verifying that all program and data Flash blocks are erased. */
/* CCOBIX end = 0 */
/* CCOB Params - NONE */
/* MGSTAT set if fault */

#define SET_USER_MARGIN_LEVEL    0x0D 
/*Specifies a user margin read level for all program Flash blocks. */
/* CCOBIX end = 1 */
/* CCOB Params - gpage, level setting (0-2) in CCOB[1] */
/* ACCERR set if invalid level */

#define SET_FIELD_MARGIN_LEVEL   0x0E 
/*Specifies a field margin read level for all program Flash blocks (special modes only). */
/* CCOBIX end = 1 */
/* CCOB Params - gpage, level setting (0-4) in CCOB[1] */
/* ACCERR set if invalid level */

/* **** P-Flash Only Commands ****/

#define ERASE_VERIFY_P_FLASH_SECTION 0x03  
/*Verify that a given number of words starting at the address provided are erased. */
/* CCOBIX end = 2 */
/* CCOB Params - global address, number of phrases in CCOB[2]*/
/* MGSTAT set if fault */

#define READ_ONCE	               0x04  
/* Read a phrase from a dedicated 64 word area in a hidden region of a programFlash block
   that was previously programmed using the Program Once command. */
/* CCOBIX end = 1 */
/* CCOB Params - read once index (0-3) in CCOB[1], phrase in CCOB [5:2] */
/* returns phrase in CCOB [4:1] */

#define PROGRAM_P_FLASH          0x06 
/* Program a phrase in a program Flash block and any previously loaded phrases for any
   other program Flash block (see Load Data Field command). */
/* CCOBIX end = 5 */
/* CCOB Params - global address, phrase in CCOB [5:2] */
/* MGSTAT set if fault, FPVIOL / ACCERR set where appropriate */

#define PROGRAM_ONCE             0x07 
/* Program a dedicated 64 word area in a hidden region of a program Flash block that is
   allowed to be programmed only once. */
/* CCOBIX end = 5 */
/* CCOB Params - read once index (0-3) in CCOB[1], phrase in CCOB [5:2] */
/* MGSTAT set if fault */

#define ERASE_P_FLASH_BLOCK      0x09 
/* Erase a program Flash block.
   An erase of the full program Flash block is only possible when FPLDIS, FPHDIS and
   FPOPEN bits in the FPROT register are set prior to launching the command. */
/* CCOBIX end = 1 */
/* CCOB Params - global address */
/* MGSTAT set if fault, FPVIOL / ACCERR set where appropriate */

#define ERASE_P_FLASH_SECTOR 0x0A 
/* Erase all bytes in a program Flash sector. */
/* CCOBIX end = 1 */
/* CCOB Params - global address */
/* MGSTAT set if fault, FPVIOL / ACCERR set where appropriate */

#define VERIFY_BACKDOOR_ACCESS_KEY 0x0C 
/*Supports a method of releasing MCU security by verifying a set of security keys. */
/* CCOBIX end = 4 */
/* CCOB Params - backdoor key in CCOB [1:4] */
/* ACCERR set if not verified */

/**** D-Flash Only Commands ****/
#define ERASE_D_FLASH_BLOCK      0x09 
/* Erase a program Flash block.
   An erase of the full program Flash block is only possible when DPOPEN bit in the DFPROT
     register is set prior to launching the command. */
/* CCOBIX end = 1 */
/* CCOB Params - global address */
/* MGSTAT set if fault, FPVIOL / ACCERR set where appropriate */

#define ERASE_VERIFY_D_FLASH_SECTION 0x10 
/* Verify that a given number of words starting at the address provided are erased. */
/* CCOBIX end = 2 */
/* CCOB Params - global address of first word, number of words to verify CCOB[2]*/
/* MGSTAT set if fault */

#define PROGRAM_D_FLASH         0x11 
/* Program up to four words in the data Flash block (see Load Data Field command). */
/* CCOBIX end = 2 */
/* CCOB Params - global address, up to 4 data words in CCOB [2:5] */
/* MGSTAT set if fault, EPVIOL / ACCERR set where appropriate */

#define ERASE_D_FLASH_SECTOR    0x12 


/* Erase all bytes in a data Flash sector. */
/* CCOBIX end = 2 */
/* CCOB Params - global address */
/* MGSTAT set if fault, EPVIOL  set where appropriate */

#define FLASH_OK                0
#define FLASH_BUSY              1
#define FLASH_PROGRAM_ERROR     2
#define FLASH_PROTECT_ERROR     4  
#define FLASH_COMMAND_ERROR     8
#define FLASH_ACCESS_ERROR      16 

#ifndef ALIGNED_WORD_MASK
#define ALIGNED_WORD_MASK	     0x0001
#define ALIGNED_PHRASE_MASK	   0x0007
#define SIZEOF_PHRASE          8
#endif

#define CCIF_MASK               0x80
#define ACCERR_MASK             0x20
#define FPVIOL_MASK             0x10
#define CCIF_FPVIOL_MASK        0x90
#define CCIF_ACCERR_MASK        0xA0
#define CCIF_ACCERR_FPVIOL_MASK 0xB0
#define CCIF_MGSTAT1_MASK       0x82
#define CCIF_MGSTAT_MASK        0x83

#define FLASH_OK                0
#define FLASH_BUSY              1
#define FLASH_PROGRAM_ERROR     2
#define FLASH_PROTECT_ERROR     4  
#define FLASH_COMMAND_ERROR     8
#define FLASH_ACCESS_ERROR      16  

#define FLASH_TYPE_D            0
#define FLASH_TYPE_P            1
#define FLASH_PPROT_LREGION     0
#define FLASH_PPROT_HREGION     1

#define FLASH_D_ADDRGH          0               /* bit17~16 of D-flash global address */
#define FLASH_D_SADDRGL         0x0400u         /* bit15~0 of D-flash start global address */ 
#define FLASH_D_SADDRLOGIC      0x10400u        /* start logical address of D-flash */
 
#define FLASH_D_PAGENUM         1
#define FLASH_D_PAGESIZE        0x1000u

#define FLASH_D_SECTSIZE        4               /* sector size of D-flash in bytes */
#define FLASH_D_SECTNUM         1024


#define FLASH_P_ADDRGH          3               /* bit17~16 of P-flash global address */
#define FLASH_P_SADDRGL         0               /* bit15~0 of P-flash start global address */ 
 
#define FLASH_P_PAGENUM         4//8
#define FLASH_P_PAGESIZE        0x4000u

#define FLASH_P_SECTSIZE        512             /* sector size of P-flash in bytes */
#define FLASH_P_SECTNUM         256
#define FLASH_P_PAGESECTNUM     32

#define FLASH_P_CONFIG_SSADDRGL         0xfe00u /* bit15~0 of global section start address for flash configuration field */
#define FLASH_P_CONFIG_SADDRGL          0xff00u /* bit15~0 of global start address for flash configuration field */
#define FLASH_P_CONFIG_SADDRLOGIC       0xfbf00u
#define FLASH_P_VECTOR0_SADDRGL         0xfff8u /* bit15~0 of global start address for phrase containing vector 0 */
#define FLASH_P_CONFIG_SADDRLOCAL       0xff00u
#define FLASH_P_VECTOR0_SADDRLOCAL      0xfffeu /* local address for vector 0 */

#define PATTERN_VALUE           0
#define PATTERN_ADDRESS         1
typedef enum _ERROR_TYPE {
              noErr = 0,
              SRecRangeError = 1,      //S-Record Out Of Range
              SRecOddError = 2,        //S-Record Size Must Be Even
              FlashProgramError = 3,  //Flash Programming Error
              FlashEraseError = 4,    //Flash Erase Error
              BadHexData = 5,          //Bad Hex Data
              SRecTooLong = 6,        //S-Record Too Long
              CheckSumErr = 7,        //Checksum Error
              UnknownPartID = 8       //Unknown Part ID
            }ERROR_TYPE;
extern void Flash_Init(void);
#pragma CODE_SEG RAM_CODE

extern ERROR_TYPE PFlash_Program(UINT32 address, UINT16 *ptr);
extern ERROR_TYPE PFlash_EraseSector(UINT32 address);
extern ERROR_TYPE PFlash_EraseSectorBySector(UINT32 addr_l, UINT32 addr_h);

#pragma CODE_SEG DEFAULT

#endif
/******************************************************************************/
