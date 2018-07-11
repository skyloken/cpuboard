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

/* Bbc (谷垣担当分) */
static void Bbc(char obj2, Cpub *cpub);

/* Ssm, Rsm (谷垣担当分) */
static void Ssm_Rsm(char obj2, Cpub *cpub);

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

    switch (obj1) {
        case '0':
            switch (obj2) {
                case '0':
                    /* NOP(何もしない) */
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
            /* Bbc */
            Bbc(obj2, cpub);
            return RUN_STEP;

        case '4':
            /* Ssm_Rsm */
            Ssm_Rsm(obj2, cpub);
            return RUN_STEP;

        case '5':
            return RUN_STEP;
        case '6':
            return RUN_STEP;
        case '7':
            return RUN_STEP;
        case '8':
            return RUN_STEP;
        case '9':
            return RUN_STEP;
        case 'A':
            return RUN_STEP;
        case 'B':
            return RUN_STEP;
        case 'C':
            return RUN_STEP;
        case 'D':
            return RUN_STEP;
        case 'E':
            return RUN_STEP;
        case 'F':
            return RUN_STEP;
    }

    return RUN_HALT;
}

/* Bbc (谷垣担当分) */
static void Bbc(char obj2, Cpub *cpub) {
    Uword p;
    switch (obj2) {
        case '0':
            /* BA */
            p = cpub->pc;
            cpub->pc++;
            cpub->pc = cpub->mem[p];
            break;
        case '1':
            /* BNZ */
            p = cpub->pc;
            cpub->pc++;
            if (cpub->zf == 0) {
                cpub->pc = cpub->mem[p];
            }
            break;
        case '2':
            /* BZP */
            p = cpub->pc;
            cpub->pc++;
            if (cpub->nf == 0) {
                cpub->pc = cpub->mem[p];
            }
            break;
        case '3':
            /* BP */
            p = cpub->pc;
            cpub->pc++;
            if ((cpub->nf | cpub->zf) == 0) {
                cpub->pc = cpub->mem[p];
            }
            break;
        case '4':
            /* BNI */
            p = cpub->pc;
            cpub->pc++;
            if (cpub->ibuf->flag == 0) {
                cpub->pc = cpub->mem[p];
            }
            break;
        case '5':
            /* BNC */
            p = cpub->pc;
            cpub->pc++;
            if (cpub->cf == 0) {
                cpub->pc = cpub->mem[p];
            }
            break;
        case '6':
            /* BGE */
            p = cpub->pc;
            cpub->pc++;
            if ((cpub->vf ^ cpub->nf) == 0) {
                cpub->pc = cpub->mem[p];
            }
            break;
        case '7':
            /* BGT */
            p = cpub->pc;
            cpub->pc++;
            if (((cpub->vf ^ cpub->nf) & cpub->zf) == 0) {
                cpub->pc = cpub->mem[p];
            }
            break;
        case '8':
            /* BVF */
            p = cpub->pc;
            cpub->pc++;
            if (cpub->vf == 1) {
                cpub->pc = cpub->mem[p];
            }
            break;
        case '9':
            /* BZ */
            p = cpub->pc;
            cpub->pc++;
            if (cpub->zf == 1) {
                cpub->pc = cpub->mem[p];
            }
            break;
        case 'A':
            /* BN */
            p = cpub->pc;
            cpub->pc++;
            if (cpub->nf == 1) {
                cpub->pc = cpub->mem[p];
            }
            break;
        case 'B':
            /* BZN */
            p = cpub->pc;
            cpub->pc++;
            if ((cpub->nf | cpub->zf) == 1) {
                cpub->pc = cpub->mem[p];
            }
            break;
        case 'C':
            /* BNO */
            p = cpub->pc;
            cpub->pc++;
            if (cpub->obuf.flag == 1) {
                cpub->pc = cpub->mem[p];
            }
            break;
        case 'D':
            /* BC */
            p = cpub->pc;
            cpub->pc++;
            if (cpub->cf == 1) {
                cpub->pc = cpub->mem[p];
            }
            break;
        case 'E':
            /* BLT */
            p = cpub->pc;
            cpub->pc++;
            if ((cpub->vf ^ cpub->nf) == 1) {
                cpub->pc = cpub->mem[p];
            }
            break;
        case 'F':
            /* BLE */
            p = cpub->pc;
            cpub->pc++;
            if (((cpub->vf ^ cpub->nf) & cpub->zf) == 1) {
                cpub->pc = cpub->mem[p];
            }
            break;
    }
}

/* Ssm, Rsm (谷垣担当分) */
static void Ssm_Rsm(char obj2, Cpub *cpub) {
    Bit x;
    Bit y;

    switch (obj2) {
        case '0':
            /* SRA ACC */

            x = (cpub->acc >> 7) & 1;   // b7を取り出す
            cpub->cf = cpub->acc & 1;   // CF = b0
            cpub->vf = 0;               // VF = 0

            cpub->acc = cpub->acc >> 1;
            if (x == 0) {
                cpub->acc &= ~0x80;     // b7 = 0
            } else {
                cpub->acc |= 0x80;      // b7 = 1
            }

            if(cpub->acc == 0x00){
                cpub->zf = 1;           // ZF = 1
            }
            cpub->nf = (cpub->acc >> 7) & 1;    // NF = b7

            break;

        case '8':
            /* SRA IX */

            x = (cpub->ix >> 7) & 1;    // b7を取り出す
            cpub->cf = cpub->ix & 1;    // CF = b0
            cpub->vf = 0;               // VF = 0

            cpub->ix = cpub->ix >> 1;   //右シフト
            if (x == 0) {
                cpub->ix &= ~0x80;      // b7 = 0
            } else {
                cpub->ix |= 0x80;       // b7 = 1
            }

            if(cpub->ix == 0x00){
                cpub->zf = 1;           // ZF = 1
            }
            cpub->nf = (cpub->ix >> 7) & 1;    // NF = b7

            break;

        case '1':
            /* SLA ACC */
            cpub->cf = (cpub->acc >> 7) & 1; // CF = b7

            cpub->acc = cpub->acc << 1;     // 左シフト
            cpub->acc &= ~0x01;             // b0 = 0

            if (cpub->cf != ((cpub->acc >> 7) & 1)){
                cpub->vf = 1;               // 異符号ならVF = 1
            }
            if(cpub->acc == 0x00){
                cpub->zf = 1;               // ZF = 1
            }
            cpub->nf = (cpub->acc >> 7) & 1;    // NF = b7

            break;
        case '9':
            /* SLA IX */
            cpub->cf = (cpub->ix >> 7) & 1; // CF = b7

            cpub->ix = cpub->ix << 1;     // 左シフト
            cpub->ix &= ~0x01;             // b0 = 0

            if (cpub->cf != ((cpub->ix >> 7) & 1)){
                cpub->vf = 1;               // 異符号ならVF = 1
            }
            if(cpub->ix == 0x00){
                cpub->zf = 1;               // ZF = 1
            }
            cpub->nf = (cpub->ix >> 7) & 1;    // NF = b7

            break;
        case '2':
            /* SRL ACC */
            cpub->cf = cpub->acc & 1;        // CF = b0
            cpub->vf = 0;                   // VF = 0


            cpub->acc = cpub->acc >> 1;     // 右シフト
            cpub->acc &= ~0x80;             // b7 = 0

            if(cpub->acc == 0x00){
                cpub->zf = 1;               // ZF = 1
            }
            cpub->nf = (cpub->acc >> 7) & 1;    // NF = b7

            break;
        case 'A':
            /* SRL IX */
            cpub->cf = cpub->ix & 1;        // CF = b0
            cpub->vf = 0;                   // VF = 0


            cpub->ix = cpub->ix >> 1;     // 右シフト
            cpub->ix &= ~0x80;             // b7 = 0

            if(cpub->ix == 0x00){
                cpub->zf = 1;               // ZF = 1
            }
            cpub->nf = (cpub->ix >> 7) & 1;    // NF = b7

            break;
        case '3':
            /* SLL ACC */
            cpub->cf = (cpub->acc >> 7) & 1; // CF = b7
            cpub->vf = 0;                   // VF = 0

            cpub->acc = cpub->acc << 1;     // 左シフト
            cpub->acc &= ~0x01;             // b0 = 0

            if(cpub->acc == 0x00){
                cpub->zf = 1;               // ZF = 1
            }
            cpub->nf = (cpub->acc >> 7) & 1;    // NF = b7

            break;
        case 'B':
            /* SLL IX */
            cpub->cf = (cpub->ix >> 7) & 1; // CF = b7
            cpub->vf = 0;                   // VF = 0

            cpub->ix = cpub->ix << 1;     // 左シフト
            cpub->ix &= ~0x01;             // b0 = 0

            if(cpub->ix == 0x00){
                cpub->zf = 1;               // ZF = 1
            }
            cpub->nf = (cpub->ix >> 7) & 1;    // NF = b7

            break;
        case '4':
            /* RRA ACC */
            x = cpub->cf;
            cpub->cf = cpub->acc & 1;        // CF = b0
            cpub->vf = 0;                   // VF = 0

            cpub->acc = cpub->acc >> 1;
            if (x == 0) {
                cpub->acc &= ~0x80;      // b7 = 0
            } else {
                cpub->acc |= 0x80;       // b7 = 1
            }

            if(cpub->acc == 0x00){
                cpub->zf = 1;               // ZF = 1
            }
            cpub->nf = (cpub->acc >> 7) & 1;    // NF = b7

            break;
        case 'C':
            /* RRA IX */
            x = cpub->cf;
            cpub->cf = cpub->ix & 1;        // CF = b0
            cpub->vf = 0;                   // VF = 0

            cpub->ix = cpub->ix >> 1;
            if (x == 0) {
                cpub->ix &= ~0x80;      // b7 = 0
            } else {
                cpub->ix |= 0x80;       // b7 = 1
            }

            if(cpub->ix == 0x00){
                cpub->zf = 1;               // ZF = 1
            }
            cpub->nf = (cpub->ix >> 7) & 1;    // NF = b7

            break;
        case '5':
            /* RLA ACC */
            x = cpub->cf;
            cpub->cf = (cpub->acc >> 7) & 1; // CF = b7

            cpub->acc = cpub->acc << 1;     // 左シフト
            if (x == 0) {
                cpub->acc &= ~0x01;      // b0 = 0
            } else {
                cpub->acc |= 0x01;       // b0 = 1
            }

            if (cpub->cf != ((cpub->acc >> 7) & 1)){
                cpub->vf = 1;               // 異符号ならVF = 1
            }
            if(cpub->acc == 0x00){
                cpub->zf = 1;               // ZF = 1
            }
            cpub->nf = (cpub->acc >> 7) & 1;    // NF = b7

            break;
        case 'D':
            /* RLA IX */
            x = cpub->cf;
            cpub->cf = (cpub->ix >> 7) & 1; // CF = b7

            cpub->ix = cpub->ix << 1;     // 左シフト
            if (x == 0) {
                cpub->ix &= ~0x01;      // b0 = 0
            } else {
                cpub->ix |= 0x01;       // b0 = 1
            }

            if (cpub->cf != ((cpub->ix >> 7) & 1)){
                cpub->vf = 1;               // 異符号ならVF = 1
            }
            if(cpub->ix == 0x00){
                cpub->zf = 1;               // ZF = 1
            }
            cpub->nf = (cpub->ix >> 7) & 1;    // NF = b7

            break;
        case '6':
            /* RRL ACC */
            cpub->cf = cpub->acc & 1;        // CF = b0
            cpub->vf = 0;                   // VF = 0

            cpub->acc = cpub->acc >> 1;
            if (cpub->cf == 0) {
                cpub->acc &= ~0x80;      // b7 = 0
            } else {
                cpub->acc |= 0x80;       // b7 = 1
            }

            if(cpub->acc == 0x00){
                cpub->zf = 1;               // ZF = 1
            }
            cpub->nf = (cpub->acc >> 7) & 1;    // NF = b7

            break;
        case 'E':
            /* RRL IX */
            cpub->cf = cpub->ix & 1;        // CF = b0
            cpub->vf = 0;                   // VF = 0

            cpub->ix = cpub->ix >> 1;
            if (cpub->cf == 0) {
                cpub->ix &= ~0x80;      // b7 = 0
            } else {
                cpub->ix |= 0x80;       // b7 = 1
            }

            if(cpub->ix == 0x00){
                cpub->zf = 1;               // ZF = 1
            }
            cpub->nf = (cpub->ix >> 7) & 1;    // NF = b7

            break;
        case '7':
            /* RLL ACC */
            cpub->cf = (cpub->acc >> 7) & 1; // CF = b7

            cpub->acc = cpub->acc << 1;     // 左シフト
            if (cpub->cf == 0) {
                cpub->acc &= ~0x01;      // b0 = 0
            } else {
                cpub->acc |= 0x01;       // b0 = 1
            }

            if(cpub->acc == 0x00){
                cpub->zf = 1;               // ZF = 1
            }
            cpub->nf = (cpub->acc >> 7) & 1;    // NF = b7

            break;
        case 'F':
            /* RLL IX */
            cpub->cf = (cpub->ix >> 7) & 1; // CF = b7

            cpub->ix = cpub->ix << 1;     // 左シフト
            if (cpub->cf == 0) {
                cpub->ix &= ~0x01;      // b0 = 0
            } else {
                cpub->ix |= 0x01;       // b0 = 1
            }

            if(cpub->ix == 0x00){
                cpub->zf = 1;               // ZF = 1
            }
            cpub->nf = (cpub->ix >> 7) & 1;    // NF = b7

            break;
    }
}