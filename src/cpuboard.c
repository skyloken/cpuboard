/*
 *	Project-based Learning II (CPU)
 *
 *	Program:	instruction set simulator of the Educational CPU Board
 *	File Name:	cpuboard.c
 *	Description:	simulation(emulation) of an instruction
 */

#include "cpuboard.h"
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

/*=============================================================================
 *   Simulation of a Single Instruction
 *===========================================================================*/
int step(Cpub *cpub) {
    /*
     *   [ add codes here for the simulation of an instruction ]
     *   [ return RUN_STEP or RUN_HALT ]
     */

    /* オブジェクトコードの1語目と2語目を読み込む */
    char obj[4];
    snprintf(obj, 4, "%02X", cpub->mem[cpub->pc]);
    char obj1 = obj[0];
    char obj2 = obj[1];
    //printf("%s\n", obj);

    cpub->pc++;

    Uword p;
    switch (obj1) {
        case '0':
            switch (obj2) {
                case '0':
                    /* NOP(何もしない) */
                    return RUN_STEP;
                case 'A':
                    /* JAL */
                    p = cpub->pc;
                    cpub->pc++;
                    cpub->acc = cpub->pc;
                    cpub->pc = cpub->mem[p];
                    return RUN_STEP;
                case 'B':
                    /* JR */
                    cpub->pc = cpub->acc;
                    return RUN_STEP;
                case 'F':
                    /* HLT(停止) */
                    return RUN_HALT;
            }
            break;

        case '1':
            switch (obj2) {
                case '0':
                    /* OUT */
                    cpub->obuf.buf = cpub->acc;
                    return RUN_STEP;
                case 'F':
                    /* IN */
                    cpub->acc = cpub->ibuf->buf;
                    return RUN_STEP;
            }
            break;

        case '2':
            switch (obj2) {
                case '0':
                    /* RCF */
                    cpub->cf = 0;
                    return RUN_STEP;
                case 'F':
                    /* SCF */
                    cpub->cf = 1;
                    return RUN_STEP;
            }
            break;

        case '3':
            Bbc(obj2, cpub);
            return RUN_STEP;

        case '4':
            Ssm_Rsm(obj2, cpub);
            return RUN_STEP;

        case '6':
            LD(obj2, cpub);
            return RUN_STEP;

        case '7':
            ST(obj2, cpub);
            return RUN_STEP;

        case '8':
            SBC(obj2, cpub);
            return RUN_STEP;

        case '9':
            ADC(obj2, cpub);
            return RUN_STEP;

        case 'A':
            SUB(obj2, cpub);
            return RUN_STEP;

        case 'B':
            ADD(obj2, cpub);
            return RUN_STEP;

        case 'C':
            EOR(obj2, cpub);
            return RUN_STEP;

        case 'D':
            OR(obj2, cpub);
            return RUN_STEP;

        case 'E':
            AND(obj2, cpub);
            return RUN_STEP;

        case 'F':
            CMP(obj2, cpub);
            return RUN_STEP;

    }

    return RUN_HALT;
}