#include "cpuboard.h"
#include <stdlib.h>
#include <stdio.h>

/* Bbc (谷垣担当分) */
void Bbc(char obj2, Cpub *cpub) {
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
void Ssm_Rsm(char obj2, Cpub *cpub) {
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

            if (cpub->acc == 0x00) {
                cpub->zf = 1;           // ZF = 1
            } else {
                cpub->zf = 0;
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

            if (cpub->ix == 0x00) {
                cpub->zf = 1;           // ZF = 1
            } else {
                cpub->zf = 0;
            }
            cpub->nf = (cpub->ix >> 7) & 1;    // NF = b7

            break;

        case '1':
            /* SLA ACC */
            cpub->cf = (cpub->acc >> 7) & 1; // CF = b7

            cpub->acc = cpub->acc << 1;     // 左シフト
            cpub->acc &= ~0x01;             // b0 = 0

            if (cpub->cf != ((cpub->acc >> 7) & 1)) {
                cpub->vf = 1;               // 異符号ならVF = 1
            }
            if (cpub->acc == 0x00) {
                cpub->zf = 1;           // ZF = 1
            } else {
                cpub->zf = 0;
            }
            cpub->nf = (cpub->acc >> 7) & 1;    // NF = b7

            break;
        case '9':
            /* SLA IX */
            cpub->cf = (cpub->ix >> 7) & 1; // CF = b7

            cpub->ix = cpub->ix << 1;     // 左シフト
            cpub->ix &= ~0x01;             // b0 = 0

            if (cpub->cf != ((cpub->ix >> 7) & 1)) {
                cpub->vf = 1;               // 異符号ならVF = 1
            }
            if (cpub->ix == 0x00) {
                cpub->zf = 1;           // ZF = 1
            } else {
                cpub->zf = 0;
            }
            cpub->nf = (cpub->ix >> 7) & 1;    // NF = b7

            break;
        case '2':
            /* SRL ACC */
            cpub->cf = cpub->acc & 1;        // CF = b0
            cpub->vf = 0;                   // VF = 0


            cpub->acc = cpub->acc >> 1;     // 右シフト
            cpub->acc &= ~0x80;             // b7 = 0

            if (cpub->acc == 0x00) {
                cpub->zf = 1;           // ZF = 1
            } else {
                cpub->zf = 0;
            }
            cpub->nf = (cpub->acc >> 7) & 1;    // NF = b7

            break;
        case 'A':
            /* SRL IX */
            cpub->cf = cpub->ix & 1;        // CF = b0
            cpub->vf = 0;                   // VF = 0


            cpub->ix = cpub->ix >> 1;     // 右シフト
            cpub->ix &= ~0x80;             // b7 = 0

            if (cpub->ix == 0x00) {
                cpub->zf = 1;           // ZF = 1
            } else {
                cpub->zf = 0;
            }
            cpub->nf = (cpub->ix >> 7) & 1;    // NF = b7

            break;
        case '3':
            /* SLL ACC */
            cpub->cf = (cpub->acc >> 7) & 1; // CF = b7
            cpub->vf = 0;                   // VF = 0

            cpub->acc = cpub->acc << 1;     // 左シフト
            cpub->acc &= ~0x01;             // b0 = 0

            if (cpub->acc == 0x00) {
                cpub->zf = 1;           // ZF = 1
            } else {
                cpub->zf = 0;
            }
            cpub->nf = (cpub->acc >> 7) & 1;    // NF = b7

            break;
        case 'B':
            /* SLL IX */
            cpub->cf = (cpub->ix >> 7) & 1; // CF = b7
            cpub->vf = 0;                   // VF = 0

            cpub->ix = cpub->ix << 1;     // 左シフト
            cpub->ix &= ~0x01;             // b0 = 0

            if (cpub->ix == 0x00) {
                cpub->zf = 1;           // ZF = 1
            } else {
                cpub->zf = 0;
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

            if (cpub->acc == 0x00) {
                cpub->zf = 1;           // ZF = 1
            } else {
                cpub->zf = 0;
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

            if (cpub->ix == 0x00) {
                cpub->zf = 1;           // ZF = 1
            } else {
                cpub->zf = 0;
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

            if (cpub->cf != ((cpub->acc >> 7) & 1)) {
                cpub->vf = 1;               // 異符号ならVF = 1
            }
            if (cpub->acc == 0x00) {
                cpub->zf = 1;           // ZF = 1
            } else {
                cpub->zf = 0;
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

            if (cpub->cf != ((cpub->ix >> 7) & 1)) {
                cpub->vf = 1;               // 異符号ならVF = 1
            }
            if (cpub->ix == 0x00) {
                cpub->zf = 1;           // ZF = 1
            } else {
                cpub->zf = 0;
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

            if (cpub->acc == 0x00) {
                cpub->zf = 1;           // ZF = 1
            } else {
                cpub->zf = 0;
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

            if (cpub->ix == 0x00) {
                cpub->zf = 1;           // ZF = 1
            } else {
                cpub->zf = 0;
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

            if (cpub->acc == 0x00) {
                cpub->zf = 1;           // ZF = 1
            } else {
                cpub->zf = 0;
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

            if (cpub->ix == 0x00) {
                cpub->zf = 1;           // ZF = 1
            } else {
                cpub->zf = 0;
            }
            cpub->nf = (cpub->ix >> 7) & 1;    // NF = b7

            break;
    }
}

/* 以下黛担当分 */
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
    Uword X;
    obj = cpub->mem[cpub->pc]; //2語目のアドレスを取得
    Bit A, B, C, CY;
    int is_acc = 0, is_ix = 0;
    switch (obj2) {
        case '0':
            A = (cpub->acc >> 7) & 1;
            B = (cpub->acc >> 7) & 1;
            X = cpub->acc;
            cpub->acc = cpub->acc + cpub->acc + cpub->cf;
            C = (cpub->acc >> 7) & 1;
            is_acc++;
            break;
        case '1':
            A = (cpub->acc >> 7) & 1;
            B = (cpub->ix >> 7) & 1;
            X = cpub->acc;
            cpub->acc = cpub->acc + cpub->ix + cpub->cf;
            C = (cpub->acc >> 7) & 1;
            is_acc++;
            break;

        case '2':
            A = (cpub->acc >> 7) & 1;
            B = (cpub->mem[cpub->pc] >> 7) & 1;
            X = cpub->acc;
            cpub->acc = cpub->acc + cpub->mem[cpub->pc] + cpub->cf;
            C = (cpub->acc >> 7) & 1;
            cpub->pc++;
            is_acc++;
            break;
        case '4':
            obj = cpub->mem[cpub->pc]; //2語目のアドレスを取得
            A = (cpub->acc >> 7) & 1;
            B = (cpub->mem[obj] >> 7) & 1;
            X = cpub->acc;
            cpub->pc++;
            cpub->acc = cpub->acc + cpub->mem[obj] + cpub->cf;
            C = (cpub->acc >> 7) & 1;
            is_acc++;
            break;

        case '5':
            obj = cpub->mem[cpub->pc]; //2語目のアドレスを取得
            A = (cpub->acc >> 7) & 1;
            B = (cpub->mem[obj + 256] >> 7) & 1;
            X = cpub->acc;
            cpub->pc++;
            cpub->acc = cpub->acc + cpub->mem[obj + 256] + cpub->cf;
            C = (cpub->acc >> 7) & 1;
            is_acc++;
            break;
        case '6':
            obj = cpub->mem[cpub->pc]; //2語目のアドレスを取得
            A = (cpub->acc >> 7) & 1;
            B = (cpub->mem[cpub->ix + obj] >> 7) & 1;
            X = cpub->acc;
            cpub->pc++;
            cpub->acc = cpub->acc + cpub->mem[cpub->ix + obj] + cpub->cf;
            C = (cpub->acc >> 7) & 1;
            is_acc++;
            break;
        case '7':
            obj = cpub->mem[cpub->pc]; //2語目のアドレスを取得
            A = (cpub->acc >> 7) & 1;
            B = ((cpub->mem[cpub->ix + obj + 256] + cpub->cf) >> 7) & 1;
            X = cpub->acc;
            cpub->pc++;
            cpub->acc = cpub->acc + cpub->mem[cpub->ix + obj + 256] + cpub->cf;
            C = (cpub->acc >> 7) & 1;
            is_acc++;
            break;
        case '8':
            A = (cpub->ix >> 7) & 1;
            B = (cpub->acc >> 7) & 1;
            X = cpub->ix;
            cpub->ix = cpub->ix + cpub->acc + cpub->cf;
            C = (cpub->ix >> 7) & 1;
            is_ix++;
            break;
        case '9':
            A = (cpub->ix >> 7) & 1;
            B = (cpub->ix >> 7) & 1;
            X = cpub->ix;
            cpub->ix = cpub->ix + cpub->ix + cpub->cf;
            C = (cpub->ix >> 7) & 1;
            is_ix++;
            break;
        case 'A':
            A = (cpub->ix >> 7) & 1;
            B = (cpub->mem[cpub->pc] >> 7) & 1;
            X = cpub->ix;
            cpub->ix = cpub->ix + cpub->mem[cpub->pc] + cpub->cf;
            C = (cpub->ix >> 7) & 1;
            cpub->pc++;
            is_ix++;
            break;
        case 'C':
            obj = cpub->mem[cpub->pc]; //2語目のアドレスを取得
            A = (cpub->ix >> 7) & 1;
            B = (cpub->mem[obj] >> 7) & 1;
            X = cpub->ix;
            cpub->pc++;
            cpub->ix = cpub->ix + cpub->mem[obj] + cpub->cf;
            C = (cpub->ix >> 7) & 1;
            is_ix++;
            break;
        case 'D':
            obj = cpub->mem[cpub->pc]; //2語目のアドレスを取得
            A = (cpub->ix >> 7) & 1;
            B = (cpub->mem[obj + 256] >> 7) & 1;
            X = cpub->ix;
            cpub->pc++;
            cpub->ix = cpub->ix + cpub->mem[obj + 256] + cpub->cf;
            C = (cpub->ix >> 7) & 1;
            is_ix++;
            break;
        case 'E':
            obj = cpub->mem[cpub->pc]; //2語目のアドレスを取得
            A = (cpub->ix >> 7) & 1;
            B = (cpub->mem[cpub->ix + obj] >> 7) & 1;
            X = cpub->ix;
            cpub->pc++;
            cpub->ix = cpub->ix + cpub->mem[cpub->ix + obj] + cpub->cf;
            C = (cpub->ix >> 7) & 1;
            is_ix++;
            break;
        case 'F':
            obj = cpub->mem[cpub->pc]; //2語目のアドレスを取得
            A = (cpub->ix >> 7) & 1;
            B = (cpub->mem[cpub->ix + obj + 256] >> 7) & 1;
            X = cpub->ix;
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
        if (cpub->acc < X){
            cpub->cf = 1;
        }else{
            cpub->cf = 0;
        }
    } else if (is_ix == 1) {
        cpub->nf = (cpub->ix >> 7) & 1; //NF
        if (cpub->ix == 0x00)                        //ZF
        {
            cpub->zf = 1;
        } else {
            cpub->zf = 0;
        }
        if (cpub->ix < X){
            cpub->cf = 1;
        }else{
            cpub->cf = 0;
        }
    }
    cpub->vf = (A & B & (~C)) | ((~A) & (~B) & C); //オーバーフロー
    //cpub->cf = (A & B) | (A & CY) | (B & CY);//キャリーフロー

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
    Uword obj,X;
    obj = cpub->mem[cpub->pc]; //2語目のアドレスを取得
    Bit A, B, C;
    int is_acc = 0, is_ix = 0;
    switch (obj2) {
        case '0':
            A = (cpub->acc >> 7) & 1;
            B = (cpub->acc >> 7) & 1;
            X = cpub->acc;
            cpub->acc = cpub->acc - cpub->acc - cpub->cf;
            C = (cpub->acc >> 7) & 1;
            is_acc++;
            break;
        case '1':
            A = (cpub->acc >> 7) & 1;
            B = (cpub->ix >> 7) & 1;
            X = cpub->acc;
            cpub->acc = cpub->acc - cpub->ix - cpub->cf;
            C = (cpub->acc >> 7) & 1;
            is_acc++;
            break;

        case '2':
            A = (cpub->acc >> 7) & 1;
            B = (cpub->mem[cpub->pc] >> 7) & 1;
            X = cpub->acc;
            cpub->acc = cpub->acc - cpub->mem[cpub->pc] - cpub->cf;
            C = (cpub->acc >> 7) & 1;
            cpub->pc++;
            is_acc++;
            break;
        case '4':
            obj = cpub->mem[cpub->pc]; //2語目のアドレスを取得
            A = (cpub->acc >> 7) & 1;
            B = (cpub->mem[obj] >> 7) & 1;
            X = cpub->acc;
            cpub->pc++;
            cpub->acc = cpub->acc - cpub->mem[obj] - cpub->cf;
            C = (cpub->acc >> 7) & 1;
            is_acc++;
            break;

        case '5':
            obj = cpub->mem[cpub->pc]; //2語目のアドレスを取得
            A = (cpub->acc >> 7) & 1;
            B = (cpub->mem[obj + 256] >> 7) & 1;
            X = cpub->acc;
            cpub->pc++;
            cpub->acc = cpub->acc - cpub->mem[obj + 256] - cpub->cf;
            C = (cpub->acc >> 7) & 1;
            is_acc++;
            break;
        case '6':
            obj = cpub->mem[cpub->pc]; //2語目のアドレスを取得
            A = (cpub->acc >> 7) & 1;
            B = (cpub->mem[cpub->ix + obj] >> 7) & 1;
            X = cpub->acc;
            cpub->pc++;
            cpub->acc = cpub->acc - cpub->mem[cpub->ix + obj] - cpub->cf;
            C = (cpub->acc >> 7) & 1;
            is_acc++;
            break;
        case '7':
            obj = cpub->mem[cpub->pc]; //2語目のアドレスを取得
            A = (cpub->acc >> 7) & 1;
            B = (cpub->mem[cpub->ix + obj + 256] >> 7) & 1;
            X = cpub->acc;
            cpub->pc++;
            cpub->acc = cpub->acc - cpub->mem[cpub->ix + obj + 256] - cpub->cf;
            C = (cpub->acc >> 7) & 1;
            is_acc++;
            break;
        case '8':
            A = (cpub->ix >> 7) & 1;
            B = (cpub->acc >> 7) & 1;
            X = cpub->ix;
            cpub->ix = cpub->ix - cpub->acc - cpub->cf;
            C = (cpub->ix >> 7) & 1;
            is_ix++;
            break;
        case '9':
            A = (cpub->ix >> 7) & 1;
            B = (cpub->ix >> 7) & 1;
            X = cpub->ix;
            cpub->ix = cpub->ix - cpub->ix - cpub->cf;
            C = (cpub->ix >> 7) & 1;
            is_ix++;
            break;
        case 'A':
            A = (cpub->ix >> 7) & 1;
            B = (cpub->mem[cpub->pc] >> 7) & 1;
            X = cpub->ix;
            cpub->ix = cpub->ix - cpub->mem[cpub->pc] - cpub->cf;
            C = (cpub->ix >> 7) & 1;
            cpub->pc++;
            is_ix++;
            break;
        case 'C':
            obj = cpub->mem[cpub->pc]; //2語目のアドレスを取得
            A = (cpub->ix >> 7) & 1;
            B = (cpub->mem[obj] >> 7) & 1;
            X = cpub->ix;
            cpub->pc++;
            cpub->ix = cpub->ix - cpub->mem[obj] - cpub->cf;
            C = (cpub->ix >> 7) & 1;
            is_ix++;
            break;
        case 'D':
            obj = cpub->mem[cpub->pc]; //2語目のアドレスを取得
            A = (cpub->ix >> 7) & 1;
            B = (cpub->mem[obj + 256] >> 7) & 1;
            X = cpub->ix;
            cpub->pc++;
            cpub->ix = cpub->ix - cpub->mem[obj + 256] - cpub->cf;
            C = (cpub->ix >> 7) & 1;
            is_ix++;
            break;
        case 'E':
            obj = cpub->mem[cpub->pc]; //2語目のアドレスを取得
            A = (cpub->ix >> 7) & 1;
            B = (cpub->mem[cpub->ix + obj] >> 7) & 1;
            X = cpub->ix;
            cpub->pc++;
            cpub->ix = cpub->ix - cpub->mem[cpub->ix + obj] - cpub->cf;
            C = (cpub->ix >> 7) & 1;
            is_ix++;
            break;
        case 'F':
            obj = cpub->mem[cpub->pc]; //2語目のアドレスを取得
            A = (cpub->ix >> 7) & 1;
            B = (cpub->mem[cpub->ix + obj + 256] >> 7) & 1;
            X = cpub->ix;
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
        if (cpub->acc > X){
            cpub->cf = 1;
        }else{
            cpub->cf = 0;
        }
    } else if (is_ix == 1) {
        cpub->nf = (cpub->ix >> 7) & 1; //NF
        if (cpub->ix == 0x00)                        //ZF
        {
            cpub->zf = 1;
        } else {
            cpub->zf = 0;
        }
        if (cpub->ix > X){
            cpub->cf = 1;
        }else{
            cpub->cf = 0;
        }
    }
    cpub->vf = (A & B & (~C)) | ((~A) & (~B) & C); //オーバーフロー
    //cpub->cf = (A & B) | (A & C) | (B & C);                 //キャリーフロー
    if (cpub->acc < X){
        cpub->cf = 1;
    }
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
