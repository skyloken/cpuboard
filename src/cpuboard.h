/*
 *	Project-based Learning II (CPU)
 *
 *	Program:	instruction set simulator of the Educational CPU Board
 *	File Name:	cpuboard.h
 *	Description:	resource definition of the educational computer board
 */

/*=============================================================================
 *   Architectural Data Types
 *===========================================================================*/
typedef signed char Sword;
typedef unsigned char Uword;
typedef unsigned short Addr;
typedef unsigned char Bit;

/*=============================================================================
 *   CPU Board Resources
 *===========================================================================*/
#define MEMORY_SIZE 256*2
#define IMEMORY_SIZE 256

typedef struct iobuf {
    Bit flag;
    Uword buf;
} IOBuf;

typedef struct cpuboard {
    Uword pc;
    Uword acc;
    Uword ix;
    Bit cf, vf, nf, zf;
    IOBuf *ibuf;
    IOBuf obuf;
    /*
     *   [ add here the other CPU resources if necessary ]
     */
    Uword mem[MEMORY_SIZE]; /* 0XX:Program, 1XX:Data */
} Cpub;

/*=============================================================================
 *   Top Function of an Instruction Simulation
 *===========================================================================*/
#define    RUN_HALT    0
#define    RUN_STEP    1

int step(Cpub *);

void LD(char obj2, Cpub *cpub);

void ST(char obj2, Cpub *cpub);

void ADD(char obj2, Cpub *cpub);

void ADC(char obj2, Cpub *cpub);

void SUB(char obj2, Cpub *cpub);

void SBC(char obj2, Cpub *cpub);

void CMP(char obj2, Cpub *cpub);

void AND(char obj2, Cpub *cpub);

void OR(char obj2, Cpub *cpub);

void EOR(char obj2, Cpub *cpub);

