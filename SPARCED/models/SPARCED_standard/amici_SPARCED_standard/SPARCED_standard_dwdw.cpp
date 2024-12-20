#include "amici/symbolic_functions.h"
#include "amici/defines.h"
#include "sundials/sundials_types.h"

#include <array>

#include "tcl.h"
#include "p.h"
#include "k.h"
#include "w.h"
#include "h.h"
#include "x.h"
#include "dwdw.h"

namespace amici {
namespace model_SPARCED_standard {

void dwdw_SPARCED_standard(realtype *dwdw, const realtype t, const realtype *x, const realtype *p, const realtype *k, const realtype *h, const realtype *w, const realtype *tcl){
    dflux_r2_dm_TP53 = 1.75e-12*EIF4E*k3_1/(EIF4E + k3_2);  // dwdw[0]
    dflux_r3_dm_MDM2 = 1.75e-12*EIF4E*(MDM2pro*k4_2 + k4_1)/(EIF4E + k4_3);  // dwdw[1]
    dflux_r4_dm_PPM1D = 1.75e-12*EIF4E*Wip1pro*k5_1/(EIF4E + k5_2);  // dwdw[2]
    dflux_r5_dm_ATM = 5.2499999999999996e-12*EIF4E*k6_1/(EIF4E + k6_2);  // dwdw[3]
    dflux_r6_dm_ATR = 5.2499999999999996e-12*EIF4E*k7_1/(EIF4E + k7_2);  // dwdw[4]
    dflux_r7_dm_RB1 = 1.75e-12*k8_1;  // dwdw[5]
    dflux_r8_dm_E2F1 = 1.75e-12*k9_1;  // dwdw[6]
    dflux_r9_dm_E2F2 = 1.75e-12*k10_1;  // dwdw[7]
    dflux_r10_dm_E2F3 = 1.75e-12*k11_1;  // dwdw[8]
    dflux_r11_dm_CCND1 = 1.75e-12*EIF4E*(E2F*k12_2*k12_3*k12_4/((k12_3 + pRB)*(k12_4 + pRBp)) + k12_1)/(EIF4E + k12_5);  // dwdw[9]
    dflux_r12_dm_CCND2 = 1.75e-12*EIF4E*(E2F*k13_2*k13_3*k13_4/((k13_3 + pRB)*(k13_4 + pRBp)) + k13_1)/(EIF4E + k13_5);  // dwdw[10]
    dflux_r13_dm_CCND3 = 1.75e-12*EIF4E*(E2F*k14_2*k14_3*k14_4/((k14_3 + pRB)*(k14_4 + pRBp)) + k14_1)/(EIF4E + k14_5);  // dwdw[11]
    dflux_r14_dm_CCNE1 = 1.75e-12*E2F*k15_1*k15_2*k15_3/((k15_2 + pRB)*(k15_3 + pRBp));  // dwdw[12]
    dflux_r15_dm_CCNE2 = 1.75e-12*E2F*k16_1*k16_2*k16_3/((k16_2 + pRB)*(k16_3 + pRBp));  // dwdw[13]
    dflux_r16_dm_SKP2 = 1.75e-12*k17_1;  // dwdw[14]
    dflux_r17_dm_CDC25A = 1.75e-12*k18_1;  // dwdw[15]
    dflux_r18_dm_CDC25B = 1.75e-12*k19_1;  // dwdw[16]
    dflux_r19_dm_CDC25C = 1.75e-12*k20_1;  // dwdw[17]
    dflux_r20_dm_CCNA2 = 1.75e-12*E2F*k21_1*k21_2*k21_3/((k21_2 + pRB)*(k21_3 + pRBp));  // dwdw[18]
    dflux_r21_dm_CDKN1B = 1.75e-12*E2F*k22_2*k22_3*k22_4/((k22_3 + pRB)*(k22_4 + pRBp)) + 1.75e-12*k22_1;  // dwdw[19]
    dflux_r22_dm_CDH1 = 1.75e-12*k23_1;  // dwdw[20]
    dflux_r23_dm_CCNB1 = 1.75e-12*k24_1;  // dwdw[21]
    dflux_r24_dm_CDC20 = 1.75e-12*k25_1;  // dwdw[22]
    dflux_r25_dm_WEE1 = 1.75e-12*k26_1;  // dwdw[23]
    dflux_r26_dm_CHEK1 = 5.2499999999999996e-12*k27_1;  // dwdw[24]
    dflux_r27_dm_CDKN1A = 5.2499999999999996e-12*k28_1;  // dwdw[25]
    dflux_r28_dm_TNFSF10 = 5.2499999999999996e-12*EIF4E*k33_1/(EIF4E + k33_2);  // dwdw[26]
    dflux_r29_dm_TNFRSF10A = 5.2499999999999996e-12*EIF4E*k34_1/(EIF4E + k34_2);  // dwdw[27]
    dflux_r30_dm_TNFRSF10B = 5.2499999999999996e-12*EIF4E*k35_1/(EIF4E + k35_2);  // dwdw[28]
    dflux_r31_dm_CFLAR = 5.2499999999999996e-12*EIF4E*k36_1/(EIF4E + k36_2);  // dwdw[29]
    dflux_r32_dm_CASP8 = 5.2499999999999996e-12*EIF4E*k37_1/(EIF4E + k37_2);  // dwdw[30]
    dflux_r33_dm_CASP10 = 5.2499999999999996e-12*EIF4E*k38_1/(EIF4E + k38_2);  // dwdw[31]
    dflux_r34_dm_BFAR = 5.2499999999999996e-12*EIF4E*k39_1/(EIF4E + k39_2);  // dwdw[32]
    dflux_r35_dm_CASP3 = 5.2499999999999996e-12*EIF4E*k40_1/(EIF4E + k40_2);  // dwdw[33]
    dflux_r36_dm_CASP7 = 5.2499999999999996e-12*EIF4E*k41_1/(EIF4E + k41_2);  // dwdw[34]
    dflux_r37_dm_CASP6 = 5.2499999999999996e-12*EIF4E*k42_1/(EIF4E + k42_2);  // dwdw[35]
    dflux_r38_dm_XIAP = 5.2499999999999996e-12*EIF4E*k43_1/(EIF4E + k43_2);  // dwdw[36]
    dflux_r39_dm_PARP1 = 5.2499999999999996e-12*EIF4E*k44_1/(EIF4E + k44_2);  // dwdw[37]
    dflux_r40_dm_BID = 5.2499999999999996e-12*EIF4E*k45_1/(EIF4E + k45_2);  // dwdw[38]
    dflux_r41_dm_BCL2 = 5.2499999999999996e-12*EIF4E*k46_1/(EIF4E + k46_2);  // dwdw[39]
    dflux_r42_dm_BCL2L1 = 5.2499999999999996e-12*EIF4E*k47_1/(EIF4E + k47_2);  // dwdw[40]
    dflux_r43_dm_MCL1 = 5.2499999999999996e-12*EIF4E*k48_1/(EIF4E + k48_2);  // dwdw[41]
    dflux_r44_dm_BAX = 5.2499999999999996e-12*EIF4E*k49_1/(EIF4E + k49_2);  // dwdw[42]
    dflux_r45_dm_CYCS = 5.2499999999999996e-12*EIF4E*k50_1/(EIF4E + k50_2);  // dwdw[43]
    dflux_r46_dm_DIABLO = 5.2499999999999996e-12*EIF4E*k51_1/(EIF4E + k51_2);  // dwdw[44]
    dflux_r47_dm_APAF1 = 5.2499999999999996e-12*EIF4E*k52_1/(EIF4E + k52_2);  // dwdw[45]
    dflux_r48_dm_CASP9 = 5.2499999999999996e-12*EIF4E*k53_1/(EIF4E + k53_2);  // dwdw[46]
    dflux_r49_dm_BAD = 5.2499999999999996e-12*EIF4E*k54_1/(EIF4E + k54_2);  // dwdw[47]
    dflux_r50_dm_BBC3 = 5.2499999999999996e-12*EIF4E*k55_1/(EIF4E + k55_2);  // dwdw[48]
    dflux_r51_dm_PMAIP1 = 5.2499999999999996e-12*EIF4E*k56_1/(EIF4E + k56_2);  // dwdw[49]
    dflux_r52_dm_BCL2L11 = 5.2499999999999996e-12*EIF4E*k57_1/(EIF4E + k57_2);  // dwdw[50]
    dflux_r53_dm_EGF = 5.2499999999999996e-12*EIF4E*k58_1/(EIF4E + k58_2);  // dwdw[51]
    dflux_r54_dm_NRG1 = 5.2499999999999996e-12*EIF4E*k59_1/(EIF4E + k59_2);  // dwdw[52]
    dflux_r55_dm_EGFR = 5.2499999999999996e-12*EIF4E*k60_1/(EIF4E + k60_2);  // dwdw[53]
    dflux_r56_dm_ERBB2 = 5.2499999999999996e-12*EIF4E*k61_1/(EIF4E + k61_2);  // dwdw[54]
    dflux_r57_dm_ERBB3 = 5.2499999999999996e-12*EIF4E*k62_1/(EIF4E + k62_2);  // dwdw[55]
    dflux_r58_dm_ERBB4 = 5.2499999999999996e-12*EIF4E*k63_1/(EIF4E + k63_2);  // dwdw[56]
    dflux_r59_dm_EGFRvIII = 5.2499999999999996e-12*EIF4E*k64_1/(EIF4E + k64_2);  // dwdw[57]
    dflux_r60_dm_MET = 5.2499999999999996e-12*EIF4E*k65_1/(EIF4E + k65_2);  // dwdw[58]
    dflux_r61_dm_HGF = 5.2499999999999996e-12*EIF4E*k66_1/(EIF4E + k66_2);  // dwdw[59]
    dflux_r62_dm_PDGFRA = 5.2499999999999996e-12*EIF4E*k67_1/(EIF4E + k67_2);  // dwdw[60]
    dflux_r63_dm_PDGFRB = 5.2499999999999996e-12*EIF4E*k68_1/(EIF4E + k68_2);  // dwdw[61]
    dflux_r64_dm_PDGFB = 5.2499999999999996e-12*EIF4E*k69_1/(EIF4E + k69_2);  // dwdw[62]
    dflux_r65_dm_SPRY2 = 5.2499999999999996e-12*EIF4E*k70_1/(EIF4E + k70_2);  // dwdw[63]
    dflux_r66_dm_CBL = 5.2499999999999996e-12*EIF4E*k71_1/(EIF4E + k71_2);  // dwdw[64]
    dflux_r67_dm_GRB2 = 5.2499999999999996e-12*EIF4E*k72_1/(EIF4E + k72_2);  // dwdw[65]
    dflux_r68_dm_PLCG1 = 5.2499999999999996e-12*EIF4E*k73_1/(EIF4E + k73_2);  // dwdw[66]
    dflux_r69_dm_PLCG2 = 5.2499999999999996e-12*EIF4E*k74_1/(EIF4E + k74_2);  // dwdw[67]
    dflux_r70_dm_PIK3CA = 5.2499999999999996e-12*EIF4E*k75_1/(EIF4E + k75_2);  // dwdw[68]
    dflux_r71_dm_PIK3CB = 5.2499999999999996e-12*EIF4E*k76_1/(EIF4E + k76_2);  // dwdw[69]
    dflux_r72_dm_PIK3CG = 5.2499999999999996e-12*EIF4E*k77_1/(EIF4E + k77_2);  // dwdw[70]
    dflux_r73_dm_PIK3CD = 5.2499999999999996e-12*EIF4E*k78_1/(EIF4E + k78_2);  // dwdw[71]
    dflux_r74_dm_PIK3R1 = 5.2499999999999996e-12*EIF4E*k79_1/(EIF4E + k79_2);  // dwdw[72]
    dflux_r75_dm_PIK3R2 = 5.2499999999999996e-12*EIF4E*k80_1/(EIF4E + k80_2);  // dwdw[73]
    dflux_r76_dm_PIK3R3 = 5.2499999999999996e-12*EIF4E*k81_1/(EIF4E + k81_2);  // dwdw[74]
    dflux_r77_dm_PIK3R4 = 5.2499999999999996e-12*EIF4E*k82_1/(EIF4E + k82_2);  // dwdw[75]
    dflux_r78_dm_PIK3C2A = 5.2499999999999996e-12*EIF4E*k83_1/(EIF4E + k83_2);  // dwdw[76]
    dflux_r79_dm_RASGRP1 = 5.2499999999999996e-12*EIF4E*k84_1/(EIF4E + k84_2);  // dwdw[77]
    dflux_r80_dm_RASGRP3 = 5.2499999999999996e-12*EIF4E*k85_1/(EIF4E + k85_2);  // dwdw[78]
    dflux_r81_dm_NRAS = 5.2499999999999996e-12*EIF4E*k86_1/(EIF4E + k86_2);  // dwdw[79]
    dflux_r82_dm_KRAS = 5.2499999999999996e-12*EIF4E*k87_1/(EIF4E + k87_2);  // dwdw[80]
    dflux_r83_dm_HRAS = 5.2499999999999996e-12*EIF4E*k88_1/(EIF4E + k88_2);  // dwdw[81]
    dflux_r84_dm_NF1 = 5.2499999999999996e-12*EIF4E*k89_1/(EIF4E + k89_2);  // dwdw[82]
    dflux_r85_dm_RAF1 = 5.2499999999999996e-12*EIF4E*k90_1/(EIF4E + k90_2);  // dwdw[83]
    dflux_r86_dm_BRAF = 5.2499999999999996e-12*EIF4E*k91_1/(EIF4E + k91_2);  // dwdw[84]
    dflux_r87_dm_MAP2K1 = 5.2499999999999996e-12*EIF4E*k92_1/(EIF4E + k92_2);  // dwdw[85]
    dflux_r88_dm_MAP2K2 = 5.2499999999999996e-12*EIF4E*k93_1/(EIF4E + k93_2);  // dwdw[86]
    dflux_r89_dm_DUSP6 = 5.2499999999999996e-12*EIF4E*k94_1/(EIF4E + k94_2);  // dwdw[87]
    dflux_r90_dm_RPS6KA1 = 5.2499999999999996e-12*EIF4E*k95_1/(EIF4E + k95_2);  // dwdw[88]
    dflux_r91_dm_RPS6KA2 = 5.2499999999999996e-12*EIF4E*k96_1/(EIF4E + k96_2);  // dwdw[89]
    dflux_r92_dm_RPS6KA3 = 5.2499999999999996e-12*EIF4E*k97_1/(EIF4E + k97_2);  // dwdw[90]
    dflux_r93_dm_RPS6KA4 = 5.2499999999999996e-12*EIF4E*k98_1/(EIF4E + k98_2);  // dwdw[91]
    dflux_r94_dm_DUSP1 = 5.2499999999999996e-12*EIF4E*k99_1/(EIF4E + k99_2);  // dwdw[92]
    dflux_r95_dm_FOS = 5.2499999999999996e-12*EIF4E*k100_1/(EIF4E + k100_2);  // dwdw[93]
    dflux_r96_dm_JUN = 5.2499999999999996e-12*EIF4E*k101_1/(EIF4E + k101_2);  // dwdw[94]
    dflux_r97_dm_MYC = 5.2499999999999996e-12*EIF4E*k102_1/(EIF4E + k102_2);  // dwdw[95]
    dflux_r98_dm_CTNNB1 = 5.2499999999999996e-12*EIF4E*k103_1/(EIF4E + k103_2);  // dwdw[96]
    dflux_r99_dm_PTEN = 5.2499999999999996e-12*EIF4E*k104_1/(EIF4E + k104_2);  // dwdw[97]
    dflux_r100_dm_AKT1 = 5.2499999999999996e-12*EIF4E*k105_1/(EIF4E + k105_2);  // dwdw[98]
    dflux_r101_dm_AKT2 = 5.2499999999999996e-12*EIF4E*k106_1/(EIF4E + k106_2);  // dwdw[99]
    dflux_r102_dm_PDPK1 = 5.2499999999999996e-12*EIF4E*k107_1/(EIF4E + k107_2);  // dwdw[100]
    dflux_r103_dm_RICTOR = 5.2499999999999996e-12*EIF4E*k108_1/(EIF4E + k108_2);  // dwdw[101]
    dflux_r104_dm_MTOR = 5.2499999999999996e-12*EIF4E*k109_1/(EIF4E + k109_2);  // dwdw[102]
    dflux_r105_dm_GSK3B = 5.2499999999999996e-12*EIF4E*k110_1/(EIF4E + k110_2);  // dwdw[103]
    dflux_r106_dm_TSC1 = 5.2499999999999996e-12*EIF4E*k111_1/(EIF4E + k111_2);  // dwdw[104]
    dflux_r107_dm_TSC2 = 5.2499999999999996e-12*EIF4E*k112_1/(EIF4E + k112_2);  // dwdw[105]
    dflux_r108_dm_PRKCA = 5.2499999999999996e-12*EIF4E*k113_1/(EIF4E + k113_2);  // dwdw[106]
    dflux_r109_dm_PRKCB = 5.2499999999999996e-12*EIF4E*k114_1/(EIF4E + k114_2);  // dwdw[107]
    dflux_r110_dm_PRKCG = 5.2499999999999996e-12*EIF4E*k115_1/(EIF4E + k115_2);  // dwdw[108]
    dflux_r111_dm_PRKCD = 5.2499999999999996e-12*EIF4E*k116_1/(EIF4E + k116_2);  // dwdw[109]
    dflux_r112_dm_PEBP1 = 5.2499999999999996e-12*EIF4E*k117_1/(EIF4E + k117_2);  // dwdw[110]
    dflux_r113_dm_MAPK1 = 5.2499999999999996e-12*EIF4E*k118_1/(EIF4E + k118_2);  // dwdw[111]
    dflux_r114_dm_MAPK3 = 5.2499999999999996e-12*EIF4E*k119_1/(EIF4E + k119_2);  // dwdw[112]
    dflux_r115_dm_FOXO3 = 5.2499999999999996e-12*EIF4E*k120_1/(EIF4E + k120_2);  // dwdw[113]
    dflux_r116_dm_RHEB = 5.2499999999999996e-12*EIF4E*k121_1/(EIF4E + k121_2);  // dwdw[114]
    dflux_r117_dm_RPTOR = 5.2499999999999996e-12*EIF4E*k122_1/(EIF4E + k122_2);  // dwdw[115]
    dflux_r118_dm_RPS6KB1 = 5.2499999999999996e-12*EIF4E*k123_1/(EIF4E + k123_2);  // dwdw[116]
    dflux_r119_dm_RPS6KB2 = 5.2499999999999996e-12*EIF4E*k124_1/(EIF4E + k124_2);  // dwdw[117]
    dflux_r120_dm_EIF4EBP1 = 5.2499999999999996e-12*EIF4E*k125_1/(EIF4E + k125_2);  // dwdw[118]
    dflux_r121_dm_SOS1 = 5.2499999999999996e-12*EIF4E*k126_1/(EIF4E + k126_2);  // dwdw[119]
    dflux_r122_dm_CDKN2A = 5.2499999999999996e-12*EIF4E*k127_1/(EIF4E + k127_2);  // dwdw[120]
    dflux_r123_dm_MDM4 = 5.2499999999999996e-12*EIF4E*k128_1/(EIF4E + k128_2);  // dwdw[121]
    dflux_r124_dm_FGFR1 = 5.2499999999999996e-12*EIF4E*k129_1/(EIF4E + k129_2);  // dwdw[122]
    dflux_r125_dm_FGFR2 = 5.2499999999999996e-12*EIF4E*k130_1/(EIF4E + k130_2);  // dwdw[123]
    dflux_r126_dm_FGF1 = 5.2499999999999996e-12*EIF4E*k131_1/(EIF4E + k131_2);  // dwdw[124]
    dflux_r127_dm_FGF2 = 5.2499999999999996e-12*EIF4E*k132_1/(EIF4E + k132_2);  // dwdw[125]
    dflux_r128_dm_EIF4E = 5.2499999999999996e-12*EIF4E*k133_1/(EIF4E + k133_2);  // dwdw[126]
    dflux_r129_dm_IRS1 = 5.2499999999999996e-12*EIF4E*k134_1/(EIF4E + k134_2);  // dwdw[127]
    dflux_r130_dm_IRS2 = 5.2499999999999996e-12*EIF4E*k135_1/(EIF4E + k135_2);  // dwdw[128]
    dflux_r131_dm_IGF1 = 5.2499999999999996e-12*EIF4E*k136_1/(EIF4E + k136_2);  // dwdw[129]
    dflux_r132_dm_IGF2 = 5.2499999999999996e-12*EIF4E*k137_1/(EIF4E + k137_2);  // dwdw[130]
    dflux_r133_dm_IGF1R = 5.2499999999999996e-12*EIF4E*k138_1/(EIF4E + k138_2);  // dwdw[131]
    dflux_r134_dm_MSH6 = 5.2499999999999996e-12*EIF4E*k139_1/(EIF4E + k139_2);  // dwdw[132]
    dflux_r135_dm_BRCA2 = 5.2499999999999996e-12*EIF4E*k140_1/(EIF4E + k140_2);  // dwdw[133]
    dflux_r136_dm_MGMT = 5.2499999999999996e-12*EIF4E*k141_1/(EIF4E + k141_2);  // dwdw[134]
    dflux_r137_dm_INSR = 5.2499999999999996e-12*EIF4E*k142_1/(EIF4E + k142_2);  // dwdw[135]
    dflux_r138_dm_INS = 5.2499999999999996e-12*EIF4E*k143_1/(EIF4E + k143_2);  // dwdw[136]
}

} // namespace amici
} // namespace model_SPARCED_standard