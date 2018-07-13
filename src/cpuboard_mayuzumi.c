/*
 *	Project-based Learning II (CPU)
 *
 *	Program:	instruction set simulator of the Educational CPU Board
 *	File Name:	cpuboard.c
 *	Descrioption:	simulation(emulation) of an instruction
 */

#include "cpuboard.h"
#include <stdlib.h>
#include <stdio.h>

void LD(char obj2, Cpub *cpub) {
    Uword obj;
    switch (obj2) {
        case '0':
            cpub->acc = cpub->acc;
            break;
        case '1':
            cpub->acc = cpub->ix;
            break;
        case '2':
            cpub->acc = cpub->mem[cpub->pc];
            cpub->pc++;
            break;
        case '4':
            obj = cpub->mem[cpub->pc];//2語目のアドレスを取得
            cpub->pc++;
            cpub->acc = cpub->mem[obj];
            break;
        case '5':
            obj = cpub->mem[cpub->pc];//2語目のアドレスを取得
            cpub->pc++;
            cpub->acc = cpub->mem[obj + 256];
            break;
        case '6':
            obj = cpub->mem[cpub->pc];//2語目のアドレスを取得
            cpub->pc++;
            cpub->acc = cpub->mem[cpub->ix + obj];
            break;
        case '7':
            obj = cpub->mem[cpub->pc];//2語目のアドレスを取得
            cpub->pc++;
            cpub->acc = cpub->mem[cpub->ix + obj + 256];
            break;
        case '8':
            cpub->ix = cpub->acc;
            break;
        case '9':
            cpub->ix = cpub->ix;
            break;
        case 'A':
            cpub->ix = cpub->mem[cpub->pc];
            cpub->pc++;
            break;
        case 'C':
            obj = cpub->mem[cpub->pc];//2語目のアドレスを取得
            cpub->pc++;
            cpub->ix = cpub->mem[obj];
            break;
        case 'D':
            obj = cpub->mem[cpub->pc];//2語目のアドレスを取得
            cpub->pc++;
            cpub->ix = cpub->mem[obj + 256];
            break;
        case 'E':
            obj = cpub->mem[cpub->pc];//2語目のアドレスを取得
            cpub->pc++;
            cpub->ix = cpub->mem[cpub->ix + obj];
            break;
        case 'F':
            obj = cpub->mem[cpub->pc];//2語目のアドレスを取得
            cpub->pc++;
            cpub->ix = cpub->mem[cpub->ix + obj + 256];
            break;

    }
}

void ST(char obj2, Cpub *cpub) {
    Uword obj;
    obj = cpub->mem[cpub->pc]; //2語目のアドレスを取得
    cpub->pc++;
    switch (obj2) {
        case '4':
            cpub->mem[obj] = cpub->acc;
            break;
        case '5':
            cpub->mem[obj + 256] = cpub->acc;
            break;
        case '6':
            cpub->mem[cpub->ix + obj] = cpub->acc;
            break;
        case '7':
            cpub->mem[cpub->ix + obj + 256] = cpub->acc;
            break;
        case 'C':
            cpub->mem[obj] = cpub->ix;
            break;
        case 'D':
            cpub->mem[obj + 256] = cpub->ix;
            break;
        case 'E':
            cpub->mem[cpub->ix + obj] = cpub->ix;
            break;
        case 'F':
            cpub->mem[cpub->ix + obj + 256] = cpub->ix;
            break;
    }
}

void ADD(char obj2, Cpub *cpub) {
    Uword obj;
    obj = cpub->mem[cpub->pc];
    //snprintf(&obj,4,"%02X",cpub->mem[cpub->pc]);//2語目のアドレスを取得


    Bit A, B, C;
    int is_acc = 0, is_ix = 0;
    switch (obj2) {
        case '0':
            A = (cpub->acc >> 7) & 1;
            B = (cpub->acc >> 7) & 1;
            cpub->acc = cpub->acc + cpub->acc;
            C = (cpub->acc >> 7) & 1;
            is_acc++;
            break;
        case '1':
            A = (cpub->acc >> 7) & 1;
            B = (cpub->ix >> 7) & 1;
            cpub->acc = cpub->acc + cpub->ix;
            C = (cpub->acc >> 7) & 1;
            is_acc++;
            break;

        case '2':
            A = (cpub->acc >> 7) & 1;
            B = (cpub->mem[cpub->pc] >> 7) & 1;
            cpub->acc = cpub->acc + cpub->mem[cpub->pc];
            C = (cpub->acc >> 7) & 1;
            cpub->pc++;
            is_acc++;
            break;
        case '4':
            obj = cpub->mem[cpub->pc]; //2語目のアドレスを取得
            A = (cpub->acc >> 7) & 1;
            B = (cpub->mem[obj] >> 7) & 1;
            cpub->pc++;
            cpub->acc = cpub->acc + cpub->mem[obj];
            C = (cpub->acc >> 7) & 1;
            is_acc++;
            break;

        case '5':
            obj = cpub->mem[cpub->pc]; //2語目のアドレスを取得
            A = (cpub->acc >> 7) & 1;
            B = (cpub->mem[obj + 256] >> 7) & 1;
            cpub->pc++;
            cpub->acc = cpub->acc + cpub->mem[obj + 256];
            C = (cpub->acc >> 7) & 1;
            is_acc++;
            break;
        case '6':
            obj = cpub->mem[cpub->pc]; //2語目のアドレスを取得
            A = (cpub->acc >> 7) & 1;
            B = (cpub->mem[cpub->ix + obj] >> 7) & 1;
            cpub->pc++;
            cpub->acc = cpub->acc + cpub->mem[cpub->ix + obj];
            C = (cpub->acc >> 7) & 1;
            is_acc++;
            break;
        case '7':
            obj = cpub->mem[cpub->pc]; //2語目のアドレスを取得
            A = (cpub->acc >> 7) & 1;
            B = (cpub->mem[cpub->ix + obj + 256] >> 7) & 1;
            cpub->pc++;
            cpub->acc = cpub->acc + cpub->mem[cpub->ix + obj + 256];
            C = (cpub->acc >> 7) & 1;
            is_acc++;
            break;
        case '8':
            A = (cpub->ix >> 7) & 1;
            B = (cpub->acc >> 7) & 1;
            cpub->ix = cpub->ix + cpub->acc;
            C = (cpub->ix >> 7) & 1;
            is_ix++;
            break;
        case '9':
            A = (cpub->ix >> 7) & 1;
            B = (cpub->ix >> 7) & 1;
            cpub->ix = cpub->ix + cpub->ix;
            C = (cpub->ix >> 7) & 1;
            is_ix++;
            break;
        case 'A':
            A = (cpub->ix >> 7) & 1;
            B = (cpub->mem[cpub->pc] >> 7) & 1;
            cpub->ix = cpub->ix + cpub->mem[cpub->pc];
            C = (cpub->ix >> 7) & 1;
            cpub->pc++;
            is_ix++;
            break;
        case 'C':
            obj = cpub->mem[cpub->pc]; //2語目のアドレスを取得
            A = (cpub->ix >> 7) & 1;
            B = (cpub->mem[obj] >> 7) & 1;
            cpub->pc++;
            cpub->ix = cpub->ix + cpub->mem[obj];
            C = (cpub->ix >> 7) & 1;
            is_ix++;
            break;
        case 'D':
            obj = cpub->mem[cpub->pc]; //2語目のアドレスを取得
            A = (cpub->ix >> 7) & 1;
            B = (cpub->mem[obj + 256] >> 7) & 1;
            cpub->pc++;
            cpub->ix = cpub->ix + cpub->mem[obj + 256];
            C = (cpub->ix >> 7) & 1;
            is_ix++;
            break;
        case 'E':
            obj = cpub->mem[cpub->pc]; //2語目のアドレスを取得
            A = (cpub->ix >> 7) & 1;
            B = (cpub->mem[cpub->ix + obj] >> 7) & 1;
            cpub->pc++;
            cpub->ix = cpub->ix + cpub->mem[cpub->ix + obj];
            C = (cpub->ix >> 7) & 1;
            is_ix++;
            break;
        case 'F':
            obj = cpub->mem[cpub->pc]; //2語目のアドレスを取得
            A = (cpub->ix >> 7) & 1;
            B = (cpub->mem[cpub->ix + obj + 256] >> 7) & 1;
            cpub->pc++;
            cpub->ix = cpub->ix + cpub->mem[cpub->ix + obj + 256];
            C = (cpub->ix >> 7) & 1;
            is_ix++;
            break;
    }

    if (is_acc == 1) {
        cpub->nf = (cpub->acc >> 7) & 1;//NF
        if (cpub->acc == 0x00)//ZF
        {
            cpub->zf = 1;
        } else {
            cpub->zf = 0;
        }
    } else if (is_ix == 1) {
        cpub->nf = (cpub->ix >> 7) & 1;//NF
        if (cpub->ix == 0x00)//ZF
        {
            cpub->zf = 1;
        } else {
            cpub->zf = 0;
        }
    }
    cpub->vf = (A & B & (~C)) | ((~A) & (~B) & C);//オーバーフロー
}

void ADC(char obj2, Cpub *cpub) {
    Uword obj;
    obj = cpub->mem[cpub->pc]; //2語目のアドレスを取得
    Bit A, B, C;
    int is_acc = 0, is_ix = 0;
    switch (obj2) {
        case '0':
            A = (cpub->acc >> 7) & 1;
            B = (cpub->acc >> 7) & 1;
            cpub->acc = cpub->acc + cpub->acc + cpub->cf;
            C = (cpub->acc >> 7) & 1;
            is_acc++;
            break;
        case '1':
            A = (cpub->acc >> 7) & 1;
            B = (cpub->ix >> 7) & 1;
            cpub->acc = cpub->acc + cpub->ix + cpub->cf;
            C = (cpub->acc >> 7) & 1;
            is_acc++;
            break;

        case '2':
            A = (cpub->acc >> 7) & 1;
            B = (cpub->mem[cpub->pc] >> 7) & 1;
            cpub->acc = cpub->acc + cpub->mem[cpub->pc] + cpub->cf;
            C = (cpub->acc >> 7) & 1;
            cpub->pc++;
            is_acc++;
            break;
        case '4':
            obj = cpub->mem[cpub->pc]; //2語目のアドレスを取得
            A = (cpub->acc >> 7) & 1;
            B = (cpub->mem[obj] >> 7) & 1;
            cpub->pc++;
            cpub->acc = cpub->acc + cpub->mem[obj] + cpub->cf;
            C = (cpub->acc >> 7) & 1;
            is_acc++;
            break;

        case '5':
            obj = cpub->mem[cpub->pc]; //2語目のアドレスを取得
            A = (cpub->acc >> 7) & 1;
            B = (cpub->mem[obj + 256] >> 7) & 1;
            cpub->pc++;
            cpub->acc = cpub->acc + cpub->mem[obj + 256] + cpub->cf;
            C = (cpub->acc >> 7) & 1;
            is_acc++;
            break;
        case '6':
            obj = cpub->mem[cpub->pc]; //2語目のアドレスを取得
            A = (cpub->acc >> 7) & 1;
            B = (cpub->mem[cpub->ix + obj] >> 7) & 1;
            cpub->pc++;
            cpub->acc = cpub->acc + cpub->mem[cpub->ix + obj] + cpub->cf;
            C = (cpub->acc >> 7) & 1;
            is_acc++;
            break;
        case '7':
            obj = cpub->mem[cpub->pc]; //2語目のアドレスを取得
            A = (cpub->acc >> 7) & 1;
            B = (cpub->mem[cpub->ix + obj + 256] >> 7) & 1;
            cpub->pc++;
            cpub->acc = cpub->acc + cpub->mem[cpub->ix + obj + 256] + cpub->cf;
            C = (cpub->acc >> 7) & 1;
            is_acc++;
            break;
        case '8':
            A = (cpub->ix >> 7) & 1;
            B = (cpub->acc >> 7) & 1;
            cpub->ix = cpub->ix + cpub->acc + cpub->cf;
            C = (cpub->ix >> 7) & 1;
            is_ix++;
            break;
        case '9':
            A = (cpub->ix >> 7) & 1;
            B = (cpub->ix >> 7) & 1;
            cpub->ix = cpub->ix + cpub->ix + cpub->cf;
            C = (cpub->ix >> 7) & 1;
            is_ix++;
            break;
        case 'A':
            A = (cpub->ix >> 7) & 1;
            B = (cpub->mem[cpub->pc] >> 7) & 1;
            cpub->ix = cpub->ix + cpub->mem[cpub->pc] + cpub->cf;
            C = (cpub->ix >> 7) & 1;
            cpub->pc++;
            is_ix++;
            break;
        case 'C':
            obj = cpub->mem[cpub->pc]; //2語目のアドレスを取得
            A = (cpub->ix >> 7) & 1;
            B = (cpub->mem[obj] >> 7) & 1;
            cpub->pc++;
            cpub->ix = cpub->ix + cpub->mem[obj] + cpub->cf;
            C = (cpub->ix >> 7) & 1;
            is_ix++;
            break;
        case 'D':
            obj = cpub->mem[cpub->pc]; //2語目のアドレスを取得
            A = (cpub->ix >> 7) & 1;
            B = (cpub->mem[obj + 256] >> 7) & 1;
            cpub->pc++;
            cpub->ix = cpub->ix + cpub->mem[obj + 256] + cpub->cf;
            C = (cpub->ix >> 7) & 1;
            is_ix++;
            break;
        case 'E':
            obj = cpub->mem[cpub->pc]; //2語目のアドレスを取得
            A = (cpub->ix >> 7) & 1;
            B = (cpub->mem[cpub->ix + obj] >> 7) & 1;
            cpub->pc++;
            cpub->ix = cpub->ix + cpub->mem[cpub->ix + obj] + cpub->cf;
            C = (cpub->ix >> 7) & 1;
            is_ix++;
            break;
        case 'F':
            obj = cpub->mem[cpub->pc]; //2語目のアドレスを取得
            A = (cpub->ix >> 7) & 1;
            B = (cpub->mem[cpub->ix + obj + 256] >> 7) & 1;
            cpub->pc++;
            cpub->ix = cpub->ix + cpub->mem[cpub->ix + obj + 256] + cpub->cf;
            C = (cpub->ix >> 7) & 1;
            is_ix++;
            break;
    }

    if (is_acc == 1) {
        cpub->nf = (cpub->acc >> 7) & 1; //NF
        if (cpub->acc == 0x00)                     //ZF
        {
            cpub->zf = 1;
        } else {
            cpub->zf = 0;
        }
    } else if (is_ix == 1) {
        cpub->nf = (cpub->ix >> 7) & 1; //NF
        if (cpub->ix == 0x00)                        //ZF
        {
            cpub->zf = 1;
        } else {
            cpub->zf = 0;
        }
    }
    cpub->vf = (A & B & (~C)) | ((~A) & (~B) & C); //オーバーフロー
    cpub->cf = (A & B) | (A & C) | (B & C);//キャリーフロー
}

void SUB(char obj2, Cpub *cpub) {
    Uword obj;
    obj = cpub->mem[cpub->pc]; //2語目のアドレスを取得
    Bit A, B, C;
    int is_acc = 0, is_ix = 0;
    switch (obj2) {
        case '0':
            A = (cpub->acc >> 7) & 1;
            B = (cpub->acc >> 7) & 1;
            cpub->acc = cpub->acc - cpub->acc;
            C = (cpub->acc >> 7) & 1;
            is_acc++;
            break;
        case '1':
            A = (cpub->acc >> 7) & 1;
            B = (cpub->ix >> 7) & 1;
            cpub->acc = cpub->acc - cpub->ix;
            C = (cpub->acc >> 7) & 1;
            is_acc++;
            break;

        case '2':
            A = (cpub->acc >> 7) & 1;
            B = (cpub->mem[cpub->pc] >> 7) & 1;
            cpub->acc = cpub->acc - cpub->mem[cpub->pc];
            C = (cpub->acc >> 7) & 1;
            cpub->pc++;
            is_acc++;
            break;
        case '4':
            obj = cpub->mem[cpub->pc]; //2語目のアドレスを取得
            A = (cpub->acc >> 7) & 1;
            B = (cpub->mem[obj] >> 7) & 1;
            cpub->pc++;
            cpub->acc = cpub->acc - cpub->mem[obj];
            C = (cpub->acc >> 7) & 1;
            is_acc++;
            break;

        case '5':
            obj = cpub->mem[cpub->pc]; //2語目のアドレスを取得
            A = (cpub->acc >> 7) & 1;
            B = (cpub->mem[obj + 256] >> 7) & 1;
            cpub->pc++;
            cpub->acc = cpub->acc - cpub->mem[obj + 256];
            C = (cpub->acc >> 7) & 1;
            is_acc++;
            break;
        case '6':
            obj = cpub->mem[cpub->pc]; //2語目のアドレスを取得
            A = (cpub->acc >> 7) & 1;
            B = (cpub->mem[cpub->ix + obj] >> 7) & 1;
            cpub->pc++;
            cpub->acc = cpub->acc - cpub->mem[cpub->ix + obj];
            C = (cpub->acc >> 7) & 1;
            is_acc++;
            break;
        case '7':
            obj = cpub->mem[cpub->pc]; //2語目のアドレスを取得
            A = (cpub->acc >> 7) & 1;
            B = (cpub->mem[cpub->ix + obj + 256] >> 7) & 1;
            cpub->pc++;
            cpub->acc = cpub->acc - cpub->mem[cpub->ix + obj + 256];
            C = (cpub->acc >> 7) & 1;
            is_acc++;
            break;
        case '8':
            A = (cpub->ix >> 7) & 1;
            B = (cpub->acc >> 7) & 1;
            cpub->ix = cpub->ix - cpub->acc;
            C = (cpub->ix >> 7) & 1;
            is_ix++;
            break;
        case '9':
            A = (cpub->ix >> 7) & 1;
            B = (cpub->ix >> 7) & 1;
            cpub->ix = cpub->ix - cpub->ix;
            C = (cpub->ix >> 7) & 1;
            is_ix++;
            break;
        case 'A':
            A = (cpub->ix >> 7) & 1;
            B = (cpub->mem[cpub->pc] >> 7) & 1;
            cpub->ix = cpub->ix - cpub->mem[cpub->pc];
            C = (cpub->ix >> 7) & 1;
            cpub->pc++;
            is_ix++;
            break;
        case 'C':
            obj = cpub->mem[cpub->pc]; //2語目のアドレスを取得
            A = (cpub->ix >> 7) & 1;
            B = (cpub->mem[obj] >> 7) & 1;
            cpub->pc++;
            cpub->ix = cpub->ix - cpub->mem[obj];
            C = (cpub->ix >> 7) & 1;
            is_ix++;
            break;
        case 'D':
            obj = cpub->mem[cpub->pc];//2語目のアドレスを取得
            A = (cpub->ix >> 7) & 1;
            B = (cpub->mem[obj + 256] >> 7) & 1;
            cpub->pc++;
            cpub->ix = cpub->ix - cpub->mem[obj + 256];
            C = (cpub->ix >> 7) & 1;
            is_ix++;
            break;
        case 'E':
            obj = cpub->mem[cpub->pc]; //2語目のアドレスを取得
            A = (cpub->ix >> 7) & 1;
            B = (cpub->mem[cpub->ix + obj] >> 7) & 1;
            cpub->pc++;
            cpub->ix = cpub->ix - cpub->mem[cpub->ix + obj];
            C = (cpub->ix >> 7) & 1;
            is_ix++;
            break;
        case 'F':
            obj = cpub->mem[cpub->pc]; //2語目のアドレスを取得
            A = (cpub->ix >> 7) & 1;
            B = (cpub->mem[cpub->ix + obj + 256] >> 7) & 1;
            cpub->pc++;
            cpub->ix = cpub->ix - cpub->mem[cpub->ix + obj + 256];
            C = (cpub->ix >> 7) & 1;
            is_ix++;
            break;
    }

    if (is_acc == 1) {
        cpub->nf = (cpub->acc >> 7) & 1; //NF
        if (cpub->acc == 0x00)                     //ZF
        {
            cpub->zf = 1;
        } else {
            cpub->zf = 0;
        }
    } else if (is_ix == 1) {
        cpub->nf = (cpub->ix >> 7) & 1; //NF
        if (cpub->ix == 0x00)                        //ZF
        {
            cpub->zf = 1;
        } else {
            cpub->zf = 0;
        }
    }
    cpub->vf = (A & B & (~C)) | ((~A) & (~B) & C); //オーバーフロー
}

void SBC(char obj2, Cpub *cpub) {
    Uword obj;
    obj = cpub->mem[cpub->pc]; //2語目のアドレスを取得
    Bit A, B, C;
    int is_acc = 0, is_ix = 0;
    switch (obj2) {
        case '0':
            A = (cpub->acc >> 7) & 1;
            B = (cpub->acc >> 7) & 1;
            cpub->acc = cpub->acc - cpub->acc - cpub->cf;
            C = (cpub->acc >> 7) & 1;
            is_acc++;
            break;
        case '1':
            A = (cpub->acc >> 7) & 1;
            B = (cpub->ix >> 7) & 1;
            cpub->acc = cpub->acc - cpub->ix - cpub->cf;
            C = (cpub->acc >> 7) & 1;
            is_acc++;
            break;

        case '2':
            A = (cpub->acc >> 7) & 1;
            B = (cpub->mem[cpub->pc] >> 7) & 1;
            cpub->acc = cpub->acc - cpub->mem[cpub->pc] - cpub->cf;
            C = (cpub->acc >> 7) & 1;
            cpub->pc++;
            is_acc++;
            break;
        case '4':
            obj = cpub->mem[cpub->pc]; //2語目のアドレスを取得
            A = (cpub->acc >> 7) & 1;
            B = (cpub->mem[obj] >> 7) & 1;
            cpub->pc++;
            cpub->acc = cpub->acc - cpub->mem[obj] - cpub->cf;
            C = (cpub->acc >> 7) & 1;
            is_acc++;
            break;

        case '5':
            obj = cpub->mem[cpub->pc]; //2語目のアドレスを取得
            A = (cpub->acc >> 7) & 1;
            B = (cpub->mem[obj + 256] >> 7) & 1;
            cpub->pc++;
            cpub->acc = cpub->acc - cpub->mem[obj + 256] - cpub->cf;
            C = (cpub->acc >> 7) & 1;
            is_acc++;
            break;
        case '6':
            obj = cpub->mem[cpub->pc]; //2語目のアドレスを取得
            A = (cpub->acc >> 7) & 1;
            B = (cpub->mem[cpub->ix + obj] >> 7) & 1;
            cpub->pc++;
            cpub->acc = cpub->acc - cpub->mem[cpub->ix + obj] - cpub->cf;
            C = (cpub->acc >> 7) & 1;
            is_acc++;
            break;
        case '7':
            obj = cpub->mem[cpub->pc]; //2語目のアドレスを取得
            A = (cpub->acc >> 7) & 1;
            B = (cpub->mem[cpub->ix + obj + 256] >> 7) & 1;
            cpub->pc++;
            cpub->acc = cpub->acc - cpub->mem[cpub->ix + obj + 256] - cpub->cf;
            C = (cpub->acc >> 7) & 1;
            is_acc++;
            break;
        case '8':
            A = (cpub->ix >> 7) & 1;
            B = (cpub->acc >> 7) & 1;
            cpub->ix = cpub->ix - cpub->acc - cpub->cf;
            C = (cpub->ix >> 7) & 1;
            is_ix++;
            break;
        case '9':
            A = (cpub->ix >> 7) & 1;
            B = (cpub->ix >> 7) & 1;
            cpub->ix = cpub->ix - cpub->ix - cpub->cf;
            C = (cpub->ix >> 7) & 1;
            is_ix++;
            break;
        case 'A':
            A = (cpub->ix >> 7) & 1;
            B = (cpub->mem[cpub->pc] >> 7) & 1;
            cpub->ix = cpub->ix - cpub->mem[cpub->pc] - cpub->cf;
            C = (cpub->ix >> 7) & 1;
            cpub->pc++;
            is_ix++;
            break;
        case 'C':
            obj = cpub->mem[cpub->pc]; //2語目のアドレスを取得
            A = (cpub->ix >> 7) & 1;
            B = (cpub->mem[obj] >> 7) & 1;
            cpub->pc++;
            cpub->ix = cpub->ix - cpub->mem[obj] - cpub->cf;
            C = (cpub->ix >> 7) & 1;
            is_ix++;
            break;
        case 'D':
            obj = cpub->mem[cpub->pc]; //2語目のアドレスを取得
            A = (cpub->ix >> 7) & 1;
            B = (cpub->mem[obj + 256] >> 7) & 1;
            cpub->pc++;
            cpub->ix = cpub->ix - cpub->mem[obj + 256] - cpub->cf;
            C = (cpub->ix >> 7) & 1;
            is_ix++;
            break;
        case 'E':
            obj = cpub->mem[cpub->pc]; //2語目のアドレスを取得
            A = (cpub->ix >> 7) & 1;
            B = (cpub->mem[cpub->ix + obj] >> 7) & 1;
            cpub->pc++;
            cpub->ix = cpub->ix - cpub->mem[cpub->ix + obj] - cpub->cf;
            C = (cpub->ix >> 7) & 1;
            is_ix++;
            break;
        case 'F':
            obj = cpub->mem[cpub->pc]; //2語目のアドレスを取得
            A = (cpub->ix >> 7) & 1;
            B = (cpub->mem[cpub->ix + obj + 256] >> 7) & 1;
            cpub->pc++;
            cpub->ix = cpub->ix - cpub->mem[cpub->ix + obj + 256] - cpub->cf;
            C = (cpub->ix >> 7) & 1;
            is_ix++;
            break;
    }

    if (is_acc == 1) {
        cpub->nf = (cpub->acc >> 7) & 1; //NF
        if (cpub->acc == 0x00)                     //ZF
        {
            cpub->zf = 1;
        } else {
            cpub->zf = 0;
        }
    } else if (is_ix == 1) {
        cpub->nf = (cpub->ix >> 7) & 1; //NF
        if (cpub->ix == 0x00)                        //ZF
        {
            cpub->zf = 1;
        } else {
            cpub->zf = 0;
        }
    }
    cpub->vf = (A & B & (~C)) | ((~A) & (~B) & C); //オーバーフロー
    cpub->cf = (A & B) | (A & C) | (B & C);                 //キャリーフロー
}

void CMP(char obj2, Cpub *cpub) {
    Uword obj;
    obj = cpub->mem[cpub->pc]; //2語目のアドレスを取得
    Bit A, B, C;
    int is_acc = 0, is_ix = 0;
    Uword tmp;
    switch (obj2) {
        case '0':
            A = (cpub->acc >> 7) & 1;
            B = (cpub->acc >> 7) & 1;
            tmp = cpub->acc - cpub->acc;
            C = (cpub->acc >> 7) & 1;
            is_acc++;
            break;
        case '1':
            A = (cpub->acc >> 7) & 1;
            B = (cpub->ix >> 7) & 1;
            tmp = cpub->acc - cpub->ix;
            C = (cpub->acc >> 7) & 1;
            is_acc++;
            break;

        case '2':
            A = (cpub->acc >> 7) & 1;
            B = (cpub->mem[cpub->pc] >> 7) & 1;
            tmp = cpub->acc - cpub->mem[cpub->pc];
            C = (cpub->acc >> 7) & 1;
            cpub->pc++;
            is_acc++;
            break;
        case '4':
            obj = cpub->mem[cpub->pc]; //2語目のアドレスを取得
            A = (cpub->acc >> 7) & 1;
            B = (cpub->mem[obj] >> 7) & 1;
            cpub->pc++;
            tmp = cpub->acc - cpub->mem[obj];
            C = (cpub->acc >> 7) & 1;
            is_acc++;
            break;

        case '5':
            obj = cpub->mem[cpub->pc]; //2語目のアドレスを取得
            A = (cpub->acc >> 7) & 1;
            B = (cpub->mem[obj + 256] >> 7) & 1;
            cpub->pc++;
            tmp = cpub->acc - cpub->mem[obj + 256];
            C = (cpub->acc >> 7) & 1;
            is_acc++;
            break;
        case '6':
            obj = cpub->mem[cpub->pc]; //2語目のアドレスを取得
            A = (cpub->acc >> 7) & 1;
            B = (cpub->mem[cpub->ix + obj] >> 7) & 1;
            cpub->pc++;
            tmp = cpub->acc - cpub->mem[cpub->ix + obj];
            C = (cpub->acc >> 7) & 1;
            is_acc++;
            break;
        case '7':
            obj = cpub->mem[cpub->pc]; //2語目のアドレスを取得
            A = (cpub->acc >> 7) & 1;
            B = (cpub->mem[cpub->ix + obj + 256] >> 7) & 1;
            cpub->pc++;
            tmp = cpub->acc - cpub->mem[cpub->ix + obj + 256];
            C = (cpub->acc >> 7) & 1;
            is_acc++;
            break;
        case '8':
            A = (cpub->ix >> 7) & 1;
            B = (cpub->acc >> 7) & 1;
            tmp = cpub->ix - cpub->acc;
            C = (cpub->ix >> 7) & 1;
            is_ix++;
            break;
        case '9':
            A = (cpub->ix >> 7) & 1;
            B = (cpub->ix >> 7) & 1;
            tmp = cpub->ix - cpub->ix;
            C = (cpub->ix >> 7) & 1;
            is_ix++;
            break;
        case 'A':
            A = (cpub->ix >> 7) & 1;
            B = (cpub->mem[cpub->pc] >> 7) & 1;
            tmp = cpub->ix - cpub->mem[cpub->pc];
            C = (cpub->ix >> 7) & 1;
            cpub->pc++;
            is_ix++;
            break;
        case 'C':
            obj = cpub->mem[cpub->pc]; //2語目のアドレスを取得
            A = (cpub->ix >> 7) & 1;
            B = (cpub->mem[obj] >> 7) & 1;
            cpub->pc++;
            tmp = cpub->ix - cpub->mem[obj];
            C = (cpub->ix >> 7) & 1;
            is_ix++;
            break;
        case 'D':
            obj = cpub->mem[cpub->pc]; //2語目のアドレスを取得
            A = (cpub->ix >> 7) & 1;
            B = (cpub->mem[obj + 256] >> 7) & 1;
            cpub->pc++;
            tmp = cpub->ix - cpub->mem[obj + 256];
            C = (cpub->ix >> 7) & 1;
            is_ix++;
            break;
        case 'E':
            obj = cpub->mem[cpub->pc]; //2語目のアドレスを取得
            A = (cpub->ix >> 7) & 1;
            B = (cpub->mem[cpub->ix + obj] >> 7) & 1;
            cpub->pc++;
            tmp = cpub->ix - cpub->mem[cpub->ix + obj];
            C = (cpub->ix >> 7) & 1;
            is_ix++;
            break;
        case 'F':
            obj = cpub->mem[cpub->pc]; //2語目のアドレスを取得
            A = (cpub->ix >> 7) & 1;
            B = (cpub->mem[cpub->ix + obj + 256] >> 7) & 1;
            cpub->pc++;
            tmp = cpub->ix - cpub->mem[cpub->ix + obj + 256];
            C = (cpub->ix >> 7) & 1;
            is_ix++;
            break;
    }

    if (is_acc == 1) {
        cpub->nf = (tmp >> 7) & 1; //NF
        if (tmp == 0x00)                     //ZF
        {
            cpub->zf = 1;
        } else {
            cpub->zf = 0;
        }
    } else if (is_ix == 1) {
        cpub->nf = (tmp >> 7) & 1; //NF
        if (tmp == 0x00)                        //ZF
        {
            cpub->zf = 1;
        } else {
            cpub->zf = 0;
        }
    }
    cpub->vf = (A & B & (~C)) | ((~A) & (~B) & C); //オーバーフロー
}

void AND(char obj2, Cpub *cpub) {
    Uword obj;
    obj = cpub->mem[cpub->pc];
    //snprintf(&obj,4,"%02X",cpub->mem[cpub->pc]);//2語目のアドレスを取得

    Bit A, B, C;
    int is_acc = 0, is_ix = 0;
    switch (obj2) {
        case '0':
            A = (cpub->acc >> 7) & 1;
            B = (cpub->acc >> 7) & 1;
            cpub->acc = cpub->acc & cpub->acc;
            C = (cpub->acc >> 7) & 1;
            is_acc++;
            break;
        case '1':
            A = (cpub->acc >> 7) & 1;
            B = (cpub->ix >> 7) & 1;
            cpub->acc = cpub->acc & cpub->ix;
            C = (cpub->acc >> 7) & 1;
            is_acc++;
            break;

        case '2':
            A = (cpub->acc >> 7) & 1;
            B = (cpub->mem[cpub->pc] >> 7) & 1;
            cpub->acc = cpub->acc & cpub->mem[cpub->pc];
            C = (cpub->acc >> 7) & 1;
            cpub->pc++;
            is_acc++;
            break;
        case '4':
            obj = cpub->mem[cpub->pc]; //2語目のアドレスを取得
            A = (cpub->acc >> 7) & 1;
            B = (cpub->mem[obj] >> 7) & 1;
            cpub->pc++;
            cpub->acc = cpub->acc & cpub->mem[obj];
            C = (cpub->acc >> 7) & 1;
            is_acc++;
            break;

        case '5':
            obj = cpub->mem[cpub->pc]; //2語目のアドレスを取得
            A = (cpub->acc >> 7) & 1;
            B = (cpub->mem[obj + 256] >> 7) & 1;
            cpub->pc++;
            cpub->acc = cpub->acc & cpub->mem[obj + 256];
            C = (cpub->acc >> 7) & 1;
            is_acc++;
            break;
        case '6':
            obj = cpub->mem[cpub->pc]; //2語目のアドレスを取得
            A = (cpub->acc >> 7) & 1;
            B = (cpub->mem[cpub->ix + obj] >> 7) & 1;
            cpub->pc++;
            cpub->acc = cpub->acc & cpub->mem[cpub->ix + obj];
            C = (cpub->acc >> 7) & 1;
            is_acc++;
            break;
        case '7':
            obj = cpub->mem[cpub->pc]; //2語目のアドレスを取得
            A = (cpub->acc >> 7) & 1;
            B = (cpub->mem[cpub->ix + obj + 256] >> 7) & 1;
            cpub->pc++;
            cpub->acc = cpub->acc & cpub->mem[cpub->ix + obj + 256];
            C = (cpub->acc >> 7) & 1;
            is_acc++;
            break;
        case '8':
            A = (cpub->ix >> 7) & 1;
            B = (cpub->acc >> 7) & 1;
            cpub->ix = cpub->ix & cpub->acc;
            C = (cpub->ix >> 7) & 1;
            is_ix++;
            break;
        case '9':
            A = (cpub->ix >> 7) & 1;
            B = (cpub->ix >> 7) & 1;
            cpub->ix = cpub->ix & cpub->ix;
            C = (cpub->ix >> 7) & 1;
            is_ix++;
            break;
        case 'A':
            A = (cpub->ix >> 7) & 1;
            B = (cpub->mem[cpub->pc] >> 7) & 1;
            cpub->ix = cpub->ix & cpub->mem[cpub->pc];
            C = (cpub->ix >> 7) & 1;
            cpub->pc++;
            is_ix++;
            break;
        case 'C':
            obj = cpub->mem[cpub->pc]; //2語目のアドレスを取得
            A = (cpub->ix >> 7) & 1;
            B = (cpub->mem[obj] >> 7) & 1;
            cpub->pc++;
            cpub->ix = cpub->ix & cpub->mem[obj];
            C = (cpub->ix >> 7) & 1;
            is_ix++;
            break;
        case 'D':
            obj = cpub->mem[cpub->pc]; //2語目のアドレスを取得
            A = (cpub->ix >> 7) & 1;
            B = (cpub->mem[obj + 256] >> 7) & 1;
            cpub->pc++;
            cpub->ix = cpub->ix & cpub->mem[obj + 256];
            C = (cpub->ix >> 7) & 1;
            is_ix++;
            break;
        case 'E':
            obj = cpub->mem[cpub->pc]; //2語目のアドレスを取得
            A = (cpub->ix >> 7) & 1;
            B = (cpub->mem[cpub->ix + obj] >> 7) & 1;
            cpub->pc++;
            cpub->ix = cpub->ix & cpub->mem[cpub->ix + obj];
            C = (cpub->ix >> 7) & 1;
            is_ix++;
            break;
        case 'F':
            obj = cpub->mem[cpub->pc]; //2語目のアドレスを取得
            A = (cpub->ix >> 7) & 1;
            B = (cpub->mem[cpub->ix + obj + 256] >> 7) & 1;
            cpub->pc++;
            cpub->ix = cpub->ix & cpub->mem[cpub->ix + obj + 256];
            C = (cpub->ix >> 7) & 1;
            is_ix++;
            break;
    }

    if (is_acc == 1) {
        cpub->nf = (cpub->acc >> 7) & 1; //NF
        if (cpub->acc == 0x00)                     //ZF
        {
            cpub->zf = 1;
        } else {
            cpub->zf = 0;
        }
    } else if (is_ix == 1) {
        cpub->nf = (cpub->ix >> 7) & 1; //NF
        if (cpub->ix == 0x00)                        //ZF
        {
            cpub->zf = 1;
        } else {
            cpub->zf = 0;
        }
    }
    cpub->vf = 0; //オーバーフロー
}

void OR(char obj2, Cpub *cpub) {
    Uword obj;
    obj = cpub->mem[cpub->pc];
    //snprintf(&obj,4,"%02X",cpub->mem[cpub->pc]);//2語目のアドレスを取得

    Bit A, B, C;
    int is_acc = 0, is_ix = 0;
    switch (obj2) {
        case '0':
            A = (cpub->acc >> 7) & 1;
            B = (cpub->acc >> 7) & 1;
            cpub->acc = cpub->acc | cpub->acc;
            C = (cpub->acc >> 7) & 1;
            is_acc++;
            break;
        case '1':
            A = (cpub->acc >> 7) & 1;
            B = (cpub->ix >> 7) & 1;
            cpub->acc = cpub->acc | cpub->ix;
            C = (cpub->acc >> 7) & 1;
            is_acc++;
            break;

        case '2':
            A = (cpub->acc >> 7) & 1;
            B = (cpub->mem[cpub->pc] >> 7) & 1;
            cpub->acc = cpub->acc | cpub->mem[cpub->pc];
            C = (cpub->acc >> 7) & 1;
            cpub->pc++;
            is_acc++;
            break;
        case '4':
            obj = cpub->mem[cpub->pc]; //2語目のアドレスを取得
            A = (cpub->acc >> 7) & 1;
            B = (cpub->mem[obj] >> 7) & 1;
            cpub->pc++;
            cpub->acc = cpub->acc | cpub->mem[obj];
            C = (cpub->acc >> 7) & 1;
            is_acc++;
            break;

        case '5':
            obj = cpub->mem[cpub->pc]; //2語目のアドレスを取得
            A = (cpub->acc >> 7) & 1;
            B = (cpub->mem[obj + 256] >> 7) & 1;
            cpub->pc++;
            cpub->acc = cpub->acc | cpub->mem[obj + 256];
            C = (cpub->acc >> 7) & 1;
            is_acc++;
            break;
        case '6':
            obj = cpub->mem[cpub->pc]; //2語目のアドレスを取得
            A = (cpub->acc >> 7) & 1;
            B = (cpub->mem[cpub->ix + obj] >> 7) & 1;
            cpub->pc++;
            cpub->acc = cpub->acc | cpub->mem[cpub->ix + obj];
            C = (cpub->acc >> 7) & 1;
            is_acc++;
            break;
        case '7':
            obj = cpub->mem[cpub->pc]; //2語目のアドレスを取得
            A = (cpub->acc >> 7) & 1;
            B = (cpub->mem[cpub->ix + obj + 256] >> 7) & 1;
            cpub->pc++;
            cpub->acc = cpub->acc | cpub->mem[cpub->ix + obj + 256];
            C = (cpub->acc >> 7) & 1;
            is_acc++;
            break;
        case '8':
            A = (cpub->ix >> 7) & 1;
            B = (cpub->acc >> 7) & 1;
            cpub->ix = cpub->ix | cpub->acc;
            C = (cpub->ix >> 7) & 1;
            is_ix++;
            break;
        case '9':
            A = (cpub->ix >> 7) & 1;
            B = (cpub->ix >> 7) & 1;
            cpub->ix = cpub->ix | cpub->ix;
            C = (cpub->ix >> 7) & 1;
            is_ix++;
            break;
        case 'A':
            A = (cpub->ix >> 7) & 1;
            B = (cpub->mem[cpub->pc] >> 7) & 1;
            cpub->ix = cpub->ix | cpub->mem[cpub->pc];
            C = (cpub->ix >> 7) & 1;
            cpub->pc++;
            is_ix++;
            break;
        case 'C':
            obj = cpub->mem[cpub->pc]; //2語目のアドレスを取得
            A = (cpub->ix >> 7) & 1;
            B = (cpub->mem[obj] >> 7) & 1;
            cpub->pc++;
            cpub->ix = cpub->ix | cpub->mem[obj];
            C = (cpub->ix >> 7) & 1;
            is_ix++;
            break;
        case 'D':
            obj = cpub->mem[cpub->pc]; //2語目のアドレスを取得
            A = (cpub->ix >> 7) & 1;
            B = (cpub->mem[obj + 256] >> 7) & 1;
            cpub->pc++;
            cpub->ix = cpub->ix | cpub->mem[obj + 256];
            C = (cpub->ix >> 7) & 1;
            is_ix++;
            break;
        case 'E':
            obj = cpub->mem[cpub->pc]; //2語目のアドレスを取得
            A = (cpub->ix >> 7) & 1;
            B = (cpub->mem[cpub->ix + obj] >> 7) & 1;
            cpub->pc++;
            cpub->ix = cpub->ix | cpub->mem[cpub->ix + obj];
            C = (cpub->ix >> 7) & 1;
            is_ix++;
            break;
        case 'F':
            obj = cpub->mem[cpub->pc]; //2語目のアドレスを取得
            A = (cpub->ix >> 7) & 1;
            B = (cpub->mem[cpub->ix + obj + 256] >> 7) & 1;
            cpub->pc++;
            cpub->ix = cpub->ix | cpub->mem[cpub->ix + obj + 256];
            C = (cpub->ix >> 7) & 1;
            is_ix++;
            break;
    }

    if (is_acc == 1) {
        cpub->nf = (cpub->acc >> 7) & 1; //NF
        if (cpub->acc == 0x00)                     //ZF
        {
            cpub->zf = 1;
        } else {
            cpub->zf = 0;
        }
    } else if (is_ix == 1) {
        cpub->nf = (cpub->ix >> 7) & 1; //NF
        if (cpub->ix == 0x00)                        //ZF
        {
            cpub->zf = 1;
        } else {
            cpub->zf = 0;
        }
    }
    cpub->vf = 0; //オーバーフロー
}

void EOR(char obj2, Cpub *cpub) {
    Uword obj;
    obj = cpub->mem[cpub->pc];
    //snprintf(&obj,4,"%02X",cpub->mem[cpub->pc]);//2語目のアドレスを取得

    Bit A, B, C;
    int is_acc = 0, is_ix = 0;
    switch (obj2) {
        case '0':
            A = (cpub->acc >> 7) & 1;
            B = (cpub->acc >> 7) & 1;
            cpub->acc = cpub->acc ^ cpub->acc;
            C = (cpub->acc >> 7) & 1;
            is_acc++;
            break;
        case '1':
            A = (cpub->acc >> 7) & 1;
            B = (cpub->ix >> 7) & 1;
            cpub->acc = cpub->acc ^ cpub->ix;
            C = (cpub->acc >> 7) & 1;
            is_acc++;
            break;

        case '2':
            A = (cpub->acc >> 7) & 1;
            B = (cpub->mem[cpub->pc] >> 7) & 1;
            cpub->acc = cpub->acc ^ cpub->mem[cpub->pc];
            C = (cpub->acc >> 7) & 1;
            cpub->pc++;
            is_acc++;
            break;
        case '4':
            obj = cpub->mem[cpub->pc]; //2語目のアドレスを取得
            A = (cpub->acc >> 7) & 1;
            B = (cpub->mem[obj] >> 7) & 1;
            cpub->pc++;
            cpub->acc = cpub->acc ^ cpub->mem[obj];
            C = (cpub->acc >> 7) & 1;
            is_acc++;
            break;

        case '5':
            obj = cpub->mem[cpub->pc]; //2語目のアドレスを取得
            A = (cpub->acc >> 7) & 1;
            B = (cpub->mem[obj + 256] >> 7) & 1;
            cpub->pc++;
            cpub->acc = cpub->acc ^ cpub->mem[obj + 256];
            C = (cpub->acc >> 7) & 1;
            is_acc++;
            break;
        case '6':
            obj = cpub->mem[cpub->pc]; //2語目のアドレスを取得
            A = (cpub->acc >> 7) & 1;
            B = (cpub->mem[cpub->ix + obj] >> 7) & 1;
            cpub->pc++;
            cpub->acc = cpub->acc ^ cpub->mem[cpub->ix + obj];
            C = (cpub->acc >> 7) & 1;
            is_acc++;
            break;
        case '7':
            obj = cpub->mem[cpub->pc]; //2語目のアドレスを取得
            A = (cpub->acc >> 7) & 1;
            B = (cpub->mem[cpub->ix + obj + 256] >> 7) & 1;
            cpub->pc++;
            cpub->acc = cpub->acc ^ cpub->mem[cpub->ix + obj + 256];
            C = (cpub->acc >> 7) & 1;
            is_acc++;
            break;
        case '8':
            A = (cpub->ix >> 7) & 1;
            B = (cpub->acc >> 7) & 1;
            cpub->ix = cpub->ix ^ cpub->acc;
            C = (cpub->ix >> 7) & 1;
            is_ix++;
            break;
        case '9':
            A = (cpub->ix >> 7) & 1;
            B = (cpub->ix >> 7) & 1;
            cpub->ix = cpub->ix ^ cpub->ix;
            C = (cpub->ix >> 7) & 1;
            is_ix++;
            break;
        case 'A':
            A = (cpub->ix >> 7) & 1;
            B = (cpub->mem[cpub->pc] >> 7) & 1;
            cpub->ix = cpub->ix ^ cpub->mem[cpub->pc];
            C = (cpub->ix >> 7) & 1;
            cpub->pc++;
            is_ix++;
            break;
        case 'C':
            obj = cpub->mem[cpub->pc]; //2語目のアドレスを取得
            A = (cpub->ix >> 7) & 1;
            B = (cpub->mem[obj] >> 7) & 1;
            cpub->pc++;
            cpub->ix = cpub->ix ^ cpub->mem[obj];
            C = (cpub->ix >> 7) & 1;
            is_ix++;
            break;
        case 'D':
            obj = cpub->mem[cpub->pc]; //2語目のアドレスを取得
            A = (cpub->ix >> 7) & 1;
            B = (cpub->mem[obj + 256] >> 7) & 1;
            cpub->pc++;
            cpub->ix = cpub->ix ^ cpub->mem[obj + 256];
            C = (cpub->ix >> 7) & 1;
            is_ix++;
            break;
        case 'E':
            obj = cpub->mem[cpub->pc]; //2語目のアドレスを取得
            A = (cpub->ix >> 7) & 1;
            B = (cpub->mem[cpub->ix + obj] >> 7) & 1;
            cpub->pc++;
            cpub->ix = cpub->ix ^ cpub->mem[cpub->ix + obj];
            C = (cpub->ix >> 7) & 1;
            is_ix++;
            break;
        case 'F':
            obj = cpub->mem[cpub->pc]; //2語目のアドレスを取得
            A = (cpub->ix >> 7) & 1;
            B = (cpub->mem[cpub->ix + obj + 256] >> 7) & 1;
            cpub->pc++;
            cpub->ix = cpub->ix ^ cpub->mem[cpub->ix + obj + 256];
            C = (cpub->ix >> 7) & 1;
            is_ix++;
            break;
    }

    if (is_acc == 1) {
        cpub->nf = (cpub->acc >> 7) & 1; //NF
        if (cpub->acc == 0x00)                     //ZF
        {
            cpub->zf = 1;
        } else {
            cpub->zf = 0;
        }
    } else if (is_ix == 1) {
        cpub->nf = (cpub->ix >> 7) & 1; //NF
        if (cpub->ix == 0x00)                        //ZF
        {
            cpub->zf = 1;
        } else {
            cpub->zf = 0;
        }
    }
    cpub->vf = 0; //オーバーフロー
}
