#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

uint32_t reverser(uint32_t x);

typedef struct{
    int8_t starterChar[2];
    uint32_t Sizer, booked, offsetMinus;
}MainHead;

typedef struct{
    uint32_t headS, W, H1;
    uint16_t num_Planes, CountOfbitsOnOnePix;
    uint32_t compresser, picSize, horizontalFrameDotByMeter, verticalFrameDotByMeter, palittre, ImportantFromPalittre;
}AnotherInformationHeader;

int main(int argc, char **argv) {
    int MainPixels = 255, firstInpjumper = 0, lastInpjumper = -1, freqtion = 1, checker = 0;
    uint64_t Jumper = 1;
    // parsim vsyakoe
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--max_iter") == 0) {
            if (i < argc - 1) {
                Jumper = atoi(argv[i + 1]);
                if (Jumper < 1) {
                    Jumper = 1;
                    printf("Vnimanie:" "%llu - govno znachenie\n", Jumper);
                }
                i++;
            }
            else printf("Vnimanie:" " --max_iter ti vvel govno suda, znschit teper budet infinity\n");
        }
        else
            if (strcmp(argv[i], "--input") == 0){
                if (i < argc - 1){
                    firstInpjumper = i + 1;
                    i++;
                }
                else{
                    printf("Oshibka:" " we have no input...\n");
                    return 1;
                }
            }
            else
                if (strcmp(argv[i], "--output") == 0){
                    if (i < argc - 1) {
                        lastInpjumper = i + 1;
                        i++;
                    }
                }
                else
                    if (strcmp(argv[i], "--dump_freq") == 0){
                        if (i < argc - 1){
                            freqtion = atoi(argv[i + 1]);
                            if (freqtion < 1){
                                freqtion = 1;
                                printf("Vnimanie:" " %d govno znachenie\n", freqtion);
                            }
                            i++;
                        }
                        else{
                            freqtion = 1;
                            printf("Vnimanie:" " --dump_freq ti vvel govno suda, teper tut budet odin\n");
                        }
                    }
                }
    // otkrivaem file
    FILE* StarterInput = fopen(argv[firstInpjumper], "rb");
    if (StarterInput == NULL || firstInpjumper == 0){
        printf("Oshibka:" " we have no file...\n");
        return 1;
    }
    // chitaem header
    MainHead Header1;
    fread(&Header1.starterChar,sizeof(uint8_t ), 2, StarterInput);
    fread(&Header1.Sizer,sizeof(uint32_t), 1, StarterInput);
    fread(&Header1.booked,sizeof(uint32_t), 1, StarterInput);
    fread(&Header1.offsetMinus,sizeof(uint32_t), 1, StarterInput);
    if (Header1.starterChar[0] != 'B' || Header1.starterChar[1] != 'M') {
        printf("Oshibka:" " BMP header must to start from BM\n");
        return 1;
    }
    // chitaem dop inf iz headera
    AnotherInformationHeader overInformationinByte;
    fread(&overInformationinByte.headS,sizeof(uint32_t), 1, StarterInput);
    fread(&overInformationinByte.W,sizeof(uint32_t), 1, StarterInput);
    fread(&overInformationinByte.H1,sizeof(uint32_t), 1, StarterInput);
    fread(&overInformationinByte.num_Planes,sizeof(uint16_t), 1, StarterInput);
    fread(&overInformationinByte.CountOfbitsOnOnePix,sizeof(uint16_t), 1, StarterInput);
    fread(&overInformationinByte.compresser,sizeof(uint32_t), 1, StarterInput);
    fread(&overInformationinByte.picSize,sizeof(uint32_t), 1, StarterInput);
    fread(&overInformationinByte.verticalFrameDotByMeter,sizeof(uint32_t), 1, StarterInput);
    fread(&overInformationinByte.horizontalFrameDotByMeter,sizeof(uint32_t), 1, StarterInput);
    fread(&overInformationinByte.palittre,sizeof(uint32_t), 1, StarterInput);
    fread(&overInformationinByte.ImportantFromPalittre,sizeof(uint32_t), 1, StarterInput);
    overInformationinByte.W = abs(overInformationinByte.W);
    overInformationinByte.H1 = abs(overInformationinByte.H1);
    if (Header1.offsetMinus > 54) {
        uint8_t DontNeedIt;
        for (int i = 0; i < Header1.offsetMinus - 54; i++) {
            fread(&DontNeedIt, sizeof(uint8_t), 1, StarterInput);
        }
    }
    // suem dannie iz faila v massiv dlya logici igri
    int WidthOfByte = (overInformationinByte.W + 31) / 32;
    //printf("%d %d\n", WidthOfByte, overInformationinByte.H1);
    uint32_t MainArr[overInformationinByte.H1][WidthOfByte];
    if (overInformationinByte.CountOfbitsOnOnePix == 1) {
        for (int o = 0; o < overInformationinByte.H1; o++) {
            for (int l = 0; l < WidthOfByte; l++) fread(&(MainArr[o][l]), sizeof(uint32_t), 1, StarterInput);
        }
    }
        else
            if (overInformationinByte.CountOfbitsOnOnePix == 24){
                    uint8_t r;
                    uint8_t g;
                    uint8_t b;
                    int Jumperbit;
                    int Jumperbyte;
                    for (int h0 = 0; h0 < overInformationinByte.H1; h0++) {
                        for (int w0 = 0; w0 < overInformationinByte.W; w0++) {
                            fread(&b, sizeof(uint8_t), 1, StarterInput);
                            fread(&g, sizeof(uint8_t), 1, StarterInput);
                            fread(&r, sizeof(uint8_t), 1, StarterInput);
                            Jumperbyte = w0 / 32;
                            Jumperbit  = w0 % 32;
                            if (Jumperbit == 0) MainArr[h0][Jumperbyte] = 0;
                            MainArr[h0][Jumperbyte] = MainArr[h0][Jumperbyte] | ((((r + b + g) / 3 >= MainPixels) ? 1 : 0) << (31 - Jumperbit));
                        }
                    }
            }
            else
                if (overInformationinByte.CountOfbitsOnOnePix == 32) {
                    uint8_t r,g,b,a;
                    int Jumperbit;
                    int Jumperbyte;
                    for (int h = 0; h < overInformationinByte.H1; h++) {
                        for (int w = 0; w < overInformationinByte.W; w++) {
                            fread(&b, sizeof(uint8_t), 1, StarterInput);
                            fread(&g, sizeof(uint8_t), 1, StarterInput);
                            fread(&r, sizeof(uint8_t), 1, StarterInput);
                            fread(&a, sizeof(uint8_t), 1, StarterInput);
                            Jumperbyte = w / 32;
                            Jumperbit  = w % 32;
                            if (Jumperbit == 0) MainArr[h][Jumperbyte] = 0;
                            if (!checker) MainArr[h][Jumperbyte] = MainArr[h][Jumperbyte] | ((((r + b + g) / 3 >= MainPixels) ? 1 : 0) << (31-Jumperbit));
                        }
                    }
                }
                else{
                    printf("Oshibka:" " ur bmp must be 24 or 32 or 2 chromaticl\n", overInformationinByte.CountOfbitsOnOnePix);
                    return 1;
                }
    fclose(StarterInput);
    // logica igri
    uint32_t TLArray[overInformationinByte.H1][WidthOfByte];
    int nearGuy;
    int Jumperbit;
    int Jumperbyte;
    char OutputerArr[4096];
    for (int i = 0; i < Jumper; i++) {
        // delaem step
        for (int h0 = 0; h0 < overInformationinByte.H1; h0++) {
            for (int w0 = 0; w0 < overInformationinByte.W; w0++) {
                nearGuy = 0;
                Jumperbyte = w0 / 32;
                Jumperbit  = w0 % 32;
                if (Jumperbit == 0) {
                    TLArray[h0][Jumperbyte] = 0;
                }
                // sleva
                if (w0 > 0) {
                    // sleva v centre
                    nearGuy += (MainArr[h0][(w0-1)/32] & (0x80000000 >> ((w0 - 1)%32))) ? 1 : 0;
                    // sleva sverhu
                    if (h0 > 0) nearGuy += (MainArr[h0-1][(w0-1)/32] & (0x80000000 >> ((w0-1)%32))) ? 1 : 0;
                    // sleva snizu
                    if (h0 < overInformationinByte.H1-1) nearGuy += (MainArr[h0+1][(w0-1)/32] & (0x80000000 >> ((w0-1)%32))) ? 1 : 0;
                }
                // sprava
                if (w0 < overInformationinByte.W-1) {
                    // sprava v centre
                    nearGuy += (MainArr[h0][(w0+1)/32] & (0x80000000 >> ((w0+1)%32))) ? 1 : 0;
                    // sprava sverhu
                    if (h0 > 0) nearGuy += (MainArr[h0-1][(w0+1)/32] & (0x80000000 >> ((w0+1)%32))) ? 1 : 0;
                    // sprava snizu
                    if (h0 < overInformationinByte.H1-1) nearGuy += (MainArr[h0+1][(w0+1)/32] & (0x80000000 >> ((w0+1)%32))) ? 1 : 0;
                }
                // verh
                if (h0 > 0) nearGuy += (MainArr[h0-1][Jumperbyte] & (0x80000000 >> Jumperbit)) ? 1 : 0;
                // niz
                if (h0 < overInformationinByte.H1-1) nearGuy += (MainArr[h0+1][Jumperbyte] & (0x80000000 >> Jumperbit)) ? 1 : 0;
                if (((nearGuy == 2 || nearGuy == 3) && (MainArr[h0][Jumperbyte] & (0x80000000 >> Jumperbit))) || (nearGuy == 3)) TLArray[h0][Jumperbyte] = TLArray[h0][Jumperbyte] | (0x80000000 >> Jumperbit);
            }
        }

        if ((i+1) % freqtion == 0 || i == Jumper-1) {
            memset(OutputerArr, '\0', sizeof(OutputerArr));
            if (lastInpjumper > 0) strcpy(OutputerArr, argv[argc - 1]);
            else OutputerArr[0] = '/';
            sprintf(OutputerArr, "step-%d.bmp", i + 1);
            FILE* OUT = fopen(OutputerArr, "wb");
            if (OUT == NULL){
                printf("Oshibka:" " i cant create output file for step %d\n", (i+1));
                return 1;
            }
            // header
            // B and M v nachale
            fwrite(Header1.starterChar, sizeof(uint8_t), 2, OUT);
            // razmer faila
            uint32_t newStarter = sizeof(MainArr) + 54 + 8;
            fwrite(&newStarter, sizeof(uint32_t), 1, OUT);
            // musor vsyakiy
            newStarter = 0;
            fwrite(&newStarter, sizeof(uint32_t), 1, OUT);
            // razmer headera
            newStarter = 54+8;
            fwrite(&newStarter, sizeof(uint32_t), 1, OUT);
            // dop infa headera
            // razmer dop infi
            newStarter = 40;
            fwrite(&newStarter, sizeof(uint32_t), 1, OUT);
            // razmeri
            fwrite(&overInformationinByte.W, sizeof(uint32_t), 1, OUT);
            fwrite(&overInformationinByte.H1, sizeof(uint32_t), 1, OUT);
            // kolvo planov
            uint16_t newSterter1 = 1;
            fwrite(&newSterter1, sizeof(uint16_t), 1, OUT);
            // vse cveta
            fwrite(&newSterter1, sizeof(uint16_t), 1, OUT);
            newStarter = 0;
            fwrite(&newStarter, sizeof(uint32_t), 1, OUT);
            // pic size
            newStarter = sizeof(MainArr);
            fwrite(&newStarter, sizeof(uint32_t),1, OUT);
            // vivodim razmeri
            fwrite(&overInformationinByte.horizontalFrameDotByMeter, sizeof(uint32_t), 1, OUT);
            fwrite(&overInformationinByte.verticalFrameDotByMeter, sizeof(uint32_t), 1, OUT);
            newStarter = 0;
            fwrite(&newStarter, sizeof(uint32_t), 1, OUT);
            fwrite(&newStarter, sizeof(uint32_t), 1, OUT);
            // cveta
            newStarter = 0;
            fwrite(&newStarter, sizeof(uint32_t), 1, OUT);
            newStarter = 0x00FFFFFF;
            fwrite(&newStarter, sizeof(uint32_t), 1, OUT);
            uint32_t Result;
            for (int h = overInformationinByte.H1-1; h > -1; h--) {
                for (int w = 0; w < WidthOfByte; w++) {
                    Result = reverser(TLArray[h][w]);
                    fwrite(&Result, sizeof(uint32_t), 1, OUT);
                }
            }
            fclose(OUT);
            printf( "GREAT I GOT THAT:" " ur gens %d here: %s\n", i + 1, OutputerArr);
        }

        for (int h0 = 0; h0 < overInformationinByte.H1; h0++) {
            for (int w0 = 0; w0 < WidthOfByte; w0++) {
                MainArr[h0][w0] = TLArray[h0][w0];
            }
        }
    }
    printf("That shit was created by Korolev Daniil, ITMO, m3117, 25.12.2022");
}

uint32_t reverser(uint32_t x) {
    x = (x >> 24) | (((x >> 16) & 0xFF) << 8) | (((x >> 8) & 0xFF) << 16) | ((x & 0xFF) << 24);
    return x;
}