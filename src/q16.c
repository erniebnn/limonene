#include "q16.h"

const q16 Q16_PI = 0x3243F;

static q16 q16_sin_lut[] = {
    0x00000000,
    0xFFFFFCDB,
    0xFFFFF9B5,
    0xFFFFF690,
    0xFFFFF36B,
    0xFFFFF046,
    0xFFFFED22,
    0xFFFFE9FF,
    0xFFFFE6DC,
    0xFFFFE3BB,
    0xFFFFE09B,
    0xFFFFDD7B,
    0xFFFFDA5E,
    0xFFFFD741,
    0xFFFFD427,
    0xFFFFD10E,
    0xFFFFCDF6,
    0xFFFFCAE1,
    0xFFFFC7CE,
    0xFFFFC4BD,
    0xFFFFC1AE,
    0xFFFFBEA2,
    0xFFFFBB98,
    0xFFFFB891,
    0xFFFFB58C,
    0xFFFFB28B,
    0xFFFFAF8C,
    0xFFFFAC91,
    0xFFFFA999,
    0xFFFFA6A4,
    0xFFFFA3B2,
    0xFFFFA0C5,
    0xFFFF9DDA,
    0xFFFF9AF4,
    0xFFFF9812,
    0xFFFF9533,
    0xFFFF9259,
    0xFFFF8F83,
    0xFFFF8CB1,
    0xFFFF89E4,
    0xFFFF871C,
    0xFFFF8458,
    0xFFFF8198,
    0xFFFF7EDE,
    0xFFFF7C29,
    0xFFFF7979,
    0xFFFF76CE,
    0xFFFF7428,
    0xFFFF7188,
    0xFFFF6EED,
    0xFFFF6C58,
    0xFFFF69C9,
    0xFFFF673F,
    0xFFFF64BB,
    0xFFFF623E,
    0xFFFF5FC6,
    0xFFFF5D55,
    0xFFFF5AEA,
    0xFFFF5885,
    0xFFFF5627,
    0xFFFF53CF,
    0xFFFF517E,
    0xFFFF4F34,
    0xFFFF4CF1,
    0xFFFF4AB4,
    0xFFFF487F,
    0xFFFF4651,
    0xFFFF442A,
    0xFFFF420A,
    0xFFFF3FF1,
    0xFFFF3DE0,
    0xFFFF3BD7,
    0xFFFF39D5,
    0xFFFF37DA,
    0xFFFF35E8,
    0xFFFF33FD,
    0xFFFF321A,
    0xFFFF303F,
    0xFFFF2E6D,
    0xFFFF2CA2,
    0xFFFF2ADF,
    0xFFFF2925,
    0xFFFF2773,
    0xFFFF25CA,
    0xFFFF2429,
    0xFFFF2290,
    0xFFFF2100,
    0xFFFF1F78,
    0xFFFF1DFA,
    0xFFFF1C84,
    0xFFFF1B17,
    0xFFFF19B2,
    0xFFFF1857,
    0xFFFF1704,
    0xFFFF15BB,
    0xFFFF147B,
    0xFFFF1343,
    0xFFFF1215,
    0xFFFF10F1,
    0xFFFF0FD5,
    0xFFFF0EC3,
    0xFFFF0DBA,
    0xFFFF0CBA,
    0xFFFF0BC4,
    0xFFFF0AD7,
    0xFFFF09F4,
    0xFFFF091A,
    0xFFFF084A,
    0xFFFF0783,
    0xFFFF06C6,
    0xFFFF0613,
    0xFFFF056A,
    0xFFFF04CA,
    0xFFFF0433,
    0xFFFF03A7,
    0xFFFF0324,
    0xFFFF02AB,
    0xFFFF023C,
    0xFFFF01D7,
    0xFFFF017B,
    0xFFFF012A,
    0xFFFF00E2,
    0xFFFF00A4,
    0xFFFF0070,
    0xFFFF0046,
    0xFFFF0026,
    0xFFFF0010,
    0xFFFF0003,
    0xFFFF0001,
    0xFFFF0008,
    0xFFFF001A,
    0xFFFF0035,
    0xFFFF005A,
    0xFFFF0089,
    0xFFFF00C2,
    0xFFFF0105,
    0xFFFF0151,
    0xFFFF01A8,
    0xFFFF0208,
    0xFFFF0273,
    0xFFFF02E7,
    0xFFFF0364,
    0xFFFF03EC,
    0xFFFF047D,
    0xFFFF0518,
    0xFFFF05BD,
    0xFFFF066C,
    0xFFFF0724,
    0xFFFF07E6,
    0xFFFF08B1,
    0xFFFF0986,
    0xFFFF0A64,
    0xFFFF0B4C,
    0xFFFF0C3E,
    0xFFFF0D39,
    0xFFFF0E3D,
    0xFFFF0F4B,
    0xFFFF1062,
    0xFFFF1182,
    0xFFFF12AB,
    0xFFFF13DE,
    0xFFFF151A,
    0xFFFF165F,
    0xFFFF17AD,
    0xFFFF1903,
    0xFFFF1A63,
    0xFFFF1BCC,
    0xFFFF1D3E,
    0xFFFF1EB8,
    0xFFFF203B,
    0xFFFF21C7,
    0xFFFF235B,
    0xFFFF24F8,
    0xFFFF269D,
    0xFFFF284B,
    0xFFFF2A01,
    0xFFFF2BC0,
    0xFFFF2D86,
    0xFFFF2F55,
    0xFFFF312C,
    0xFFFF330B,
    0xFFFF34F2,
    0xFFFF36E0,
    0xFFFF38D7,
    0xFFFF3AD5,
    0xFFFF3CDA,
    0xFFFF3EE8,
    0xFFFF40FD,
    0xFFFF4319,
    0xFFFF453C,
    0xFFFF4767,
    0xFFFF4999,
    0xFFFF4BD2,
    0xFFFF4E12,
    0xFFFF5058,
    0xFFFF52A6,
    0xFFFF54FA,
    0xFFFF5755,
    0xFFFF59B7,
    0xFFFF5C1E,
    0xFFFF5E8D,
    0xFFFF6101,
    0xFFFF637C,
    0xFFFF65FC,
    0xFFFF6883,
    0xFFFF6B10,
    0xFFFF6DA2,
    0xFFFF703A,
    0xFFFF72D7,
    0xFFFF757A,
    0xFFFF7823,
    0xFFFF7AD0,
    0xFFFF7D83,
    0xFFFF803B,
    0xFFFF82F7,
    0xFFFF85B9,
    0xFFFF887F,
    0xFFFF8B4A,
    0xFFFF8E1A,
    0xFFFF90ED,
    0xFFFF93C6,
    0xFFFF96A2,
    0xFFFF9982,
    0xFFFF9C67,
    0xFFFF9F4F,
    0xFFFFA23B,
    0xFFFFA52B,
    0xFFFFA81E,
    0xFFFFAB14,
    0xFFFFAE0E,
    0xFFFFB10B,
    0xFFFFB40B,
    0xFFFFB70E,
    0xFFFFBA14,
    0xFFFFBD1C,
    0xFFFFC028,
    0xFFFFC335,
    0xFFFFC645,
    0xFFFFC957,
    0xFFFFCC6B,
    0xFFFFCF82,
    0xFFFFD29A,
    0xFFFFD5B4,
    0xFFFFD8CF,
    0xFFFFDBEC,
    0xFFFFDF0B,
    0xFFFFE22B,
    0xFFFFE54B,
    0xFFFFE86D,
    0xFFFFEB90,
    0xFFFFEEB4,
    0xFFFFF1D8,
    0xFFFFF4FD,
    0xFFFFF822,
    0xFFFFFB48,
    0xFFFFFE6E,
    0x00000192,
    0x000004B8,
    0x000007DE,
    0x00000B03,
    0x00000E28,
    0x0000114C,
    0x00001470,
    0x00001793,
    0x00001AB5,
    0x00001DD5,
    0x000020F5,
    0x00002414,
    0x00002731,
    0x00002A4C,
    0x00002D66,
    0x0000307E,
    0x00003395,
    0x000036A9,
    0x000039BB,
    0x00003CCB,
    0x00003FD8,
    0x000042E4,
    0x000045EC,
    0x000048F2,
    0x00004BF5,
    0x00004EF5,
    0x000051F2,
    0x000054EC,
    0x000057E2,
    0x00005AD5,
    0x00005DC5,
    0x000060B1,
    0x00006399,
    0x0000667E,
    0x0000695E,
    0x00006C3A,
    0x00006F13,
    0x000071E6,
    0x000074B6,
    0x00007781,
    0x00007A47,
    0x00007D09,
    0x00007FC5,
    0x0000827D,
    0x00008530,
    0x000087DD,
    0x00008A86,
    0x00008D29,
    0x00008FC6,
    0x0000925E,
    0x000094F0,
    0x0000977D,
    0x00009A04,
    0x00009C84,
    0x00009EFF,
    0x0000A173,
    0x0000A3E2,
    0x0000A649,
    0x0000A8AB,
    0x0000AB06,
    0x0000AD5A,
    0x0000AFA8,
    0x0000B1EE,
    0x0000B42E,
    0x0000B667,
    0x0000B899,
    0x0000BAC4,
    0x0000BCE7,
    0x0000BF03,
    0x0000C118,
    0x0000C326,
    0x0000C52B,
    0x0000C729,
    0x0000C920,
    0x0000CB0E,
    0x0000CCF5,
    0x0000CED4,
    0x0000D0AB,
    0x0000D27A,
    0x0000D440,
    0x0000D5FF,
    0x0000D7B5,
    0x0000D963,
    0x0000DB08,
    0x0000DCA5,
    0x0000DE39,
    0x0000DFC5,
    0x0000E148,
    0x0000E2C2,
    0x0000E434,
    0x0000E59D,
    0x0000E6FD,
    0x0000E853,
    0x0000E9A1,
    0x0000EAE6,
    0x0000EC22,
    0x0000ED55,
    0x0000EE7E,
    0x0000EF9E,
    0x0000F0B5,
    0x0000F1C3,
    0x0000F2C7,
    0x0000F3C2,
    0x0000F4B4,
    0x0000F59C,
    0x0000F67A,
    0x0000F74F,
    0x0000F81A,
    0x0000F8DC,
    0x0000F994,
    0x0000FA43,
    0x0000FAE8,
    0x0000FB83,
    0x0000FC14,
    0x0000FC9C,
    0x0000FD19,
    0x0000FD8D,
    0x0000FDF8,
    0x0000FE58,
    0x0000FEAF,
    0x0000FEFB,
    0x0000FF3E,
    0x0000FF77,
    0x0000FFA6,
    0x0000FFCB,
    0x0000FFE6,
    0x0000FFF8,
    0x0000FFFF,
    0x0000FFFD,
    0x0000FFF0,
    0x0000FFDA,
    0x0000FFBA,
    0x0000FF90,
    0x0000FF5C,
    0x0000FF1E,
    0x0000FED6,
    0x0000FE85,
    0x0000FE29,
    0x0000FDC4,
    0x0000FD55,
    0x0000FCDC,
    0x0000FC59,
    0x0000FBCD,
    0x0000FB36,
    0x0000FA96,
    0x0000F9ED,
    0x0000F93A,
    0x0000F87D,
    0x0000F7B6,
    0x0000F6E6,
    0x0000F60C,
    0x0000F529,
    0x0000F43C,
    0x0000F346,
    0x0000F246,
    0x0000F13D,
    0x0000F02B,
    0x0000EF0F,
    0x0000EDEB,
    0x0000ECBD,
    0x0000EB85,
    0x0000EA45,
    0x0000E8FC,
    0x0000E7A9,
    0x0000E64E,
    0x0000E4E9,
    0x0000E37C,
    0x0000E206,
    0x0000E088,
    0x0000DF00,
    0x0000DD70,
    0x0000DBD7,
    0x0000DA36,
    0x0000D88D,
    0x0000D6DB,
    0x0000D521,
    0x0000D35E,
    0x0000D193,
    0x0000CFC1,
    0x0000CDE6,
    0x0000CC03,
    0x0000CA18,
    0x0000C826,
    0x0000C62B,
    0x0000C429,
    0x0000C220,
    0x0000C00F,
    0x0000BDF6,
    0x0000BBD6,
    0x0000B9AF,
    0x0000B781,
    0x0000B54C,
    0x0000B30F,
    0x0000B0CC,
    0x0000AE82,
    0x0000AC31,
    0x0000A9D9,
    0x0000A77B,
    0x0000A516,
    0x0000A2AB,
    0x0000A03A,
    0x00009DC2,
    0x00009B45,
    0x000098C1,
    0x00009637,
    0x000093A8,
    0x00009113,
    0x00008E78,
    0x00008BD8,
    0x00008932,
    0x00008687,
    0x000083D7,
    0x00008122,
    0x00007E68,
    0x00007BA8,
    0x000078E4,
    0x0000761C,
    0x0000734F,
    0x0000707D,
    0x00006DA7,
    0x00006ACD,
    0x000067EE,
    0x0000650C,
    0x00006226,
    0x00005F3B,
    0x00005C4E,
    0x0000595C,
    0x00005667,
    0x0000536F,
    0x00005074,
    0x00004D75,
    0x00004A74,
    0x0000476F,
    0x00004468,
    0x0000415E,
    0x00003E52,
    0x00003B43,
    0x00003832,
    0x0000351F,
    0x0000320A,
    0x00002EF2,
    0x00002BD9,
    0x000028BF,
    0x000025A2,
    0x00002285,
    0x00001F65,
    0x00001C45,
    0x00001924,
    0x00001601,
    0x000012DE,
    0x00000FBA,
    0x00000C95,
    0x00000970,
    0x0000064B,
    0x00000325,
    0x00000000,
};
u32 q16_sin_lut_len = sizeof(q16_sin_lut) / sizeof(q16_sin_lut[0]);

q16 itoq(i32 p_i0) {
    return p_i0 << 16;
}

i32 qtoi(q16 p_q0) {
    return (i32) p_q0 >> 16;
}

q16 utoq(u32 p_u0) {
    return p_u0 << 16;
}

u32 qtou(q16 p_q0) {
    return (u32) p_q0 >> 16;
}

q16 qabs(q16 p_q0) {
    return (p_q0 > 0) ? p_q0 : -p_q0;
}

q16 qfloor(q16 p_q0) {
    return p_q0 & 0xFFFF0000;
}

q16 qceil(q16 p_q0) {
    return (p_q0 | 0xFFFF) + 1;
}

q16 qround(q16 p_q0) {
    return (p_q0 & 0x8000) ? (p_q0 | 0xFFFF) + 1 : p_q0 & 0xFFFF0000;
}

q16 qmul(q16 p_q0, q16 p_q1) {
    q16 res = 0;
    for (u32 i = 0; i < 31; i++) {
        if (p_q0 >> i & 0b1) {
            if (i < 16) {
                res += p_q1 >> (16 - i);
            }
            else {
                res += p_q1 << (i - 16);
            }
        }
    }
    if (p_q0 >> 31 & 0b1) {
        res -= p_q1 << 15;
    }
    return res;
}

struct _divres { q16 q; q16 r; };

static struct _divres qdiv_impl(q16 p_q0, q16 p_q1) {
    if (p_q1 == 0) { return (struct _divres) { .q = -1, .r = p_q0 }; }
    i32 a = (i32) qabs(p_q0);
    i32 b = (i32) qabs(p_q1);
    u32 s0 = (u32) p_q0 >> 31, s1 = (u32) p_q1 >> 31;
    u32 r = a >> 16;
    u32 q = a << 16;
    u32 s, c;
    for (u32 i = 0; i < 32; i++) {
        s = r >> 31;
        c = q >> 31;
        q = q << 1;
        r = r << 1 | c;
        r += s ? b : -b;
        s = r >> 31;
        q = q | 1 - s;
    }
    if (s) {
        r += b;
    }
    struct _divres res;
    res.q = s0 ^ s1 ? -(q16)q : (q16)q;
    res.r = s0      ? -(q16)r : (q16)r;
    return res;
}

q16 qdiv(q16 p_q0, q16 p_q1) {
    return qdiv_impl(p_q0, p_q1).q;
}

q16 qrem(q16 p_q0, q16 p_q1) {
    return qdiv_impl(p_q0, p_q1).r;
}

q16 qsin(q16 p_q0) {
    const q16 m = 0x515403;
    const q16 b = 0xFF8000;
    p_q0 = qrem(p_q0, Q16_PI);
    u32 idx = qtou(qround(qmul(m, p_q0) + b)); // check it maybe if in bounds?
    return q16_sin_lut[idx];
}

q16 qcos(q16 p_q0) {
    return qsin(p_q0 + (Q16_PI >> 2));
}

q16 qtan(q16 p_q0) {
    return qdiv(qsin(p_q0), qcos(p_q0));
}

void qmatmul4(q16 p_qmd[4][4], q16 p_qm0[4][4], q16 p_qm1[4][4]) {
    for (u32 i = 0; i < 4; i++) {
        for (u32 j = 0; j < 4; j++) {
            p_qmd[i][j] = 0;
            for (u32 k = 0; k < 4; k++) {
                p_qmd[i][j] += qmul(p_qm0[k][j], p_qm1[i][k]);
            }
        }
    }
}

void qmatvecmul4(q16 p_qvd[4], q16 p_qm0[4][4], q16 p_qv0[4]) {
    for (u32 i = 0; i < 4; i++) {
        p_qvd[i] = 0;
        for (u32 j = 0; j < 4; j++) {
            p_qvd[i] += qmul(p_qm0[j][i], p_qv0[j]);
        }
    }
}