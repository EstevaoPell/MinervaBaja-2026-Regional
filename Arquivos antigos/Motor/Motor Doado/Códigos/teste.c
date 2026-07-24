#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char *hex_to_bin(char hexNum[100]);
void funcao(char *tp0, char *tp1, char *tp2, char *tp3, char *tp4, char *tp5, char *tp6, char *tp7);

int main()
{
    char binNum[8];
    printf("\nO VALOR ESTA ABAIXO:");
    //printf(hex_to_bin("6a"));
    //strcpy(binNum, hex_to_bin("8f"));
    //printf("NUMERO BIN: %s", binNum);

    funcao("6a", "8f", "75", "9a", "5b", "7d", "0b", "3b");

    // char *numBIN = hex_to_bin("8e");
    // printf("\nNUMERO BINARIO --------- %s", numBIN);
    // int num = string_to_int(numBIN);

    // printf("\nVALOR CONVERTIDO:%d", num);

    // int *convertedNum = dec_to_bin(113);
    // printf("O NUMERO CONVERTIDO BINARIO ---------- %d", convertedNum);

    return 0;
}

const char *hex_to_bin(char hexNum[100])
{
    char valorConv[8] = "";
    char *buffer = malloc(sizeof(char) * 6);
    long int count = 0;
    printf("\nVALORES DO ARRAY:%c", hexNum[0]);
    printf("\nVALORES DO ARRAY:%c", hexNum[1]);
    while (count < 2)
    {
        switch (hexNum[count])
        {
        case '0':
            //printf("0000");

            if (!strcmp(valorConv, ""))
            {
                strcat(valorConv, "0000");
            }
            else
            {
                strcat(strcpy(buffer, valorConv), "0000");
            }
            break;
        case '1':
            //printf("0001");
            if (!strcmp(valorConv, ""))
            {
                strcat(valorConv, "0001");
            }
            else
            {
                strcat(strcpy(buffer, valorConv), "0001");
            }
            break;
        case '2':
            //printf("0010");
            if (!strcmp(valorConv, ""))
            {
                strcat(valorConv, "0010");
            }
            else
            {
                strcat(strcpy(buffer, valorConv), "0010");
            }
            break;
        case '3':
            //printf("0011");
            if (!strcmp(valorConv, ""))
            {
                strcat(valorConv, "0011");
            }
            else
            {
                strcat(strcpy(buffer, valorConv), "0011");
            }
            break;
        case '4':
            //printf("0100");
            if (!strcmp(valorConv, ""))
            {
                strcat(valorConv, "0100");
            }
            else
            {
                strcat(strcpy(buffer, valorConv), "0100");
            }
            break;
        case '5':
            //printf("0101");
            if (!strcmp(valorConv, ""))
            {
                strcat(valorConv, "0101");
            }
            else
            {
                strcat(strcpy(buffer, valorConv), "0101");
            }
            break;
        case '6':
            //printf("0110");
            if (!strcmp(valorConv, ""))
            {
                strcat(valorConv, "0110");
            }
            else
            {
                strcat(strcpy(buffer, valorConv), "0110");
            }
            break;
        case '7':
            //printf("0111");
            if (!strcmp(valorConv, ""))
            {
                strcat(valorConv, "0111");
            }
            else
            {
                strcat(strcpy(buffer, valorConv), "0111");
            }
            break;
        case '8':
            //printf("1000");
            if (!strcmp(valorConv, ""))
            {
                strcat(valorConv, "1000");
            }
            else
            {
                strcat(strcpy(buffer, valorConv), "1000");
            }
            break;
        case '9':
            //printf("1001");
            if (!strcmp(valorConv, ""))
            {
                strcat(valorConv, "1111");
            }
            else
            {
                strcat(strcpy(buffer, valorConv), "1111");
            }
            break;
        case 'A':
            // printf("1010");
            if (!strcmp(valorConv, ""))
            {
                strcat(valorConv, "1010");
            }
            else
            {
                strcat(strcpy(buffer, valorConv), "1010");
            }
            break;
        case 'B':
            //printf("1011");
            if (!strcmp(valorConv, ""))
            {
                strcat(valorConv, "1011");
            }
            else
            {
                strcat(strcpy(buffer, valorConv), "1011");
            }
            break;
        case 'C':
            //printf("1100");
            if (!strcmp(valorConv, ""))
            {
                strcat(valorConv, "1100");
            }
            else
            {
                strcat(strcpy(buffer, valorConv), "1100");
            }
            break;
        case 'D':
            //printf("1101");
            if (!strcmp(valorConv, ""))
            {
                strcat(valorConv, "1101");
            }
            else
            {
                strcat(strcpy(buffer, valorConv), "1101");
            }
            break;
        case 'E':
            //printf("1110");
            if (!strcmp(valorConv, ""))
            {
                strcat(valorConv, "1110");
            }
            else
            {
                strcat(strcpy(buffer, valorConv), "1110");
            }
            break;
        case 'F':
            //printf("1111");
            if (!strcmp(valorConv, ""))
            {
                strcat(valorConv, "1111");
            }
            else
            {
                strcat(strcpy(buffer, valorConv), "1111");
            }
            break;
        case 'a':
            //printf("1010");
            if (!strcmp(valorConv, ""))
            {
                strcat(valorConv, "1010");
            }
            else
            {
                strcat(strcpy(buffer, valorConv), "1010");
            }
            break;
        case 'b':
            //printf("1011");
            if (!strcmp(valorConv, ""))
            {
                strcat(valorConv, "1011");
            }
            else
            {
                strcat(strcpy(buffer, valorConv), "1011");
            }
            break;
        case 'c':
            //printf("1100");
            if (!strcmp(valorConv, ""))
            {
                strcat(valorConv, "1100");
            }
            else
            {
                strcat(strcpy(buffer, valorConv), "1100");
            }
            break;
        case 'd':
            //printf("1101");
            if (!strcmp(valorConv, ""))
            {
                strcat(valorConv, "1101");
            }
            else
            {
                strcat(strcpy(buffer, valorConv), "1101");
            }
            break;
        case 'e':
            //printf("1110");
            if (!strcmp(valorConv, ""))
            {
                strcat(valorConv, "1110");
            }
            else
            {
                strcat(strcpy(buffer, valorConv), "1110");
            }
            break;
        case 'f':
            // printf("1111");

            if (!strcmp(valorConv, ""))
            {
                strcat(valorConv, "1111");
            }
            else
            {
                strcat(strcpy(buffer, valorConv), "1111");
            }
            //printf("\n%s\n", buffer);
            //printf("\n\n\n%s\n\n\n", valorConv);
            break;
        default:
            printf("\nInvalid Entry, Please Try Again  %c", hexNum[count]);
        }

        count++;
        //printf("\n\n\n%d", count);
    }

    free(buffer);
    //strcpy(valorConv, "0000");
    return buffer;
}

void funcao(char *tp0, char *tp1, char *tp2, char *tp3, char *tp4, char *tp5, char *tp6, char *tp7)
{
    char *tps[8];
    tps[0] = tp0;
    tps[1] = tp1;
    tps[2] = tp2;
    tps[3] = tp3;
    tps[4] = tp4;
    tps[5] = tp5;
    tps[6] = tp6;
    tps[7] = tp7;

    struct signalCan
    {
        char nameArray[30];
        char signalName[30];
        int startBit;
        int lenght;
        int scale;
        float offset;
        float minValue;
        float maxValue;
        char unit[10];
    };

    struct signalCan Edrv_Act_1_msg[8];

    //Primeiro sinal
    //Edrv_Act_1_msg[0].nameArray = "Edrv_nrChksAct";
    strcpy(Edrv_Act_1_msg[0].nameArray, "Edrv_nrChksAct");
    //Edrv_Act_1_msg[0].signalName = "Checksum actual torque";
    strcpy(Edrv_Act_1_msg[0].signalName, "Checksum actual torque");
    Edrv_Act_1_msg[0].startBit = 0;
    Edrv_Act_1_msg[0].lenght = 8;
    Edrv_Act_1_msg[0].scale = 1;
    Edrv_Act_1_msg[0].offset = 0;
    Edrv_Act_1_msg[0].minValue = 0;
    Edrv_Act_1_msg[0].maxValue = 255;
    //Edrv_Act_1_msg[0].unit = "";
    strcpy(Edrv_Act_1_msg[0].unit, "");

    //Segundo Sinal
    //Edrv_Act_1_msg[1].nameArray = "Edrv_nrAlvCntrAct";
    strcpy(Edrv_Act_1_msg[1].nameArray, "Edrv_nrAlvCntrAct");
    //Edrv_Act_1_msg[1].signalName = "Alive counter actual torque";
    strcpy(Edrv_Act_1_msg[1].nameArray, "Alive counter actual torque");
    Edrv_Act_1_msg[1].startBit = 8;
    Edrv_Act_1_msg[1].lenght = 4;
    Edrv_Act_1_msg[1].scale = 1;
    Edrv_Act_1_msg[1].offset = 0;
    Edrv_Act_1_msg[1].minValue = 0;
    Edrv_Act_1_msg[1].maxValue = 15;
    //Edrv_Act_1_msg[1].unit = "";
    strcpy(Edrv_Act_1_msg[1].unit, "");

    //     //Terceiro Sinal
    //     Edrv_Act_1_msg[2].nameArray = "Edrv_stRunAct";
    //     Edrv_Act_1_msg[2].signalName = "Actual run state ";
    //     Edrv_Act_1_msg[2].startBit = 12;
    //     Edrv_Act_1_msg[2].lenght = 2;
    //     Edrv_Act_1_msg[2].scale = 1;
    //     Edrv_Act_1_msg[2].offset = 0;
    //     Edrv_Act_1_msg[2].minValue = 0;
    //     Edrv_Act_1_msg[2].maxValue = 3;
    //     Edrv_Act_1_msg[2].unit = "";

    //     //Quarto Sinal
    //     Edrv_Act_1_msg[3].nameArray = "Edrv_stOperModAct";
    //     Edrv_Act_1_msg[3].signalName = "Actual operation mode";
    //     Edrv_Act_1_msg[3].startBit = 14;
    //     Edrv_Act_1_msg[3].lenght = 4;
    //     Edrv_Act_1_msg[3].scale = 1;
    //     Edrv_Act_1_msg[3].offset = 0;
    //     Edrv_Act_1_msg[3].minValue = 0;
    //     Edrv_Act_1_msg[3].maxValue = 15;
    //     Edrv_Act_1_msg[3].unit = "";

    //     //Quinto Sinal
    //     Edrv_Act_1_msg[4].nameArray = "Edrv_tqAct";
    //     Edrv_Act_1_msg[4].signalName = "Actual torque";
    //     Edrv_Act_1_msg[4].startBit = 18;
    //     Edrv_Act_1_msg[4].lenght = 12;
    //     Edrv_Act_1_msg[4].scale = 0.1;
    //     Edrv_Act_1_msg[4].offset = -200;
    //     Edrv_Act_1_msg[4].minValue = -200;
    //     Edrv_Act_1_msg[4].maxValue = 209.5;
    //     Edrv_Act_1_msg[4].unit = "Nm";

    //     //Sexto Sinal
    //     Edrv_Act_1_msg[5].nameArray = "Edrv_nAct";
    //     Edrv_Act_1_msg[5].signalName = "Actual speed";
    //     Edrv_Act_1_msg[5].startBit = 30;
    //     Edrv_Act_1_msg[5].lenght = 13;
    //     Edrv_Act_1_msg[5].scale = 6;
    //     Edrv_Act_1_msg[5].offset = -24000;
    //     Edrv_Act_1_msg[5].minValue = -24000;
    //     Edrv_Act_1_msg[5].maxValue = 25146;
    //     Edrv_Act_1_msg[5].unit = "rpm";

    //     //Sétimo Sinal
    //     Edrv_Act_1_msg[6].nameArray = "Edrv_uAct";
    //     Edrv_Act_1_msg[6].signalName = "Actual DC voltage";
    //     Edrv_Act_1_msg[6].startBit = 44;
    //     Edrv_Act_1_msg[6].lenght = 10;
    //     Edrv_Act_1_msg[6].scale = 0.0625;
    //     Edrv_Act_1_msg[6].offset = 0;
    //     Edrv_Act_1_msg[6].minValue = 0;
    //     Edrv_Act_1_msg[6].maxValue = 63.9375;
    //     Edrv_Act_1_msg[6].unit = "V";

    //     //Oitavo Sinal
    //     Edrv_Act_1_msg[7].nameArray = "Edrv_iAct";
    //     Edrv_Act_1_msg[7].signalName = "Actual DC current";
    //     Edrv_Act_1_msg[7].startBit = 54;
    //     Edrv_Act_1_msg[7].lenght = 10;
    //     Edrv_Act_1_msg[7].scale = 1;
    //     Edrv_Act_1_msg[7].offset = -500;
    //     Edrv_Act_1_msg[7].minValue = -500;
    //     Edrv_Act_1_msg[7].maxValue = 523;
    //     Edrv_Act_1_msg[7].unit = "A";

    //     printf("OLHE A STRING:\n");
    //     printf("%s\n", tps[1]);

    char *parbin[8];
    char *buffer = (char *)malloc(sizeof(buffer) * 6);

    if (buffer == NULL)
    {
        printf("A MEMORIA NAO FOI ALOCADA\n");
    }
    int count = 0;
    while (count < 8)
    {
        //printf("JONATAS SDFSFDSF");
        //char *bufferTps = tps[count];
        //parbin[count] = hex_to_bin(bufferTps);
        parbin[count] = (char *)malloc(sizeof(parbin[count]) * 2);
        if (parbin[count] == NULL)
        {
            printf("NULOOOOOOO\n");
        }
        buffer = hex_to_bin(tps[count]);
        parbin[count] = malloc(strlen(buffer) + 1);
        strcpy(parbin[count], buffer);
        //printf("\n____________%d_____________\n", count);
        printf("\n___________________%s_________________\n", parbin[count]);
        // if (count > 1)
        // {
        //     printf("\n-------------------%s-----------------------\n", parbin[count - 1]);
        //     printf("\n==============%s================",parbin[0]);
        // }
        free(buffer);
        free(parbin[count]);
        count++;
    }

    free(buffer);

    for (int i = 0; i < 8; i++)
    {
        printf("\nPARBIN[%d] ---------------- %s", i, parbin[i]);
    }
    int aux = 0;
    for (int i = 0; i < 3; i++)
    {
        printf("\nLKFDLKFJSKLFJDKLS ----- %i -------- %i\n", i, aux);
        aux = aux + 10;
    }

    // char *can_frame_matrix;
    // int index = 0;
    // for (int i = 0; i < 8; i++)
    // {
    //     for (int j = 0; j < 8; j++)
    //     {
    //         //printf("\nLINHAS:%d\nCOLUNAS:%d\n", i, j);
    //         //strcpy(can_frame_matrix[index],parbin[i][j];
    //         //printf("\nPARBIN[%d][%d] = %c\n", i, j, parbin[i][0]);
    //         printf("\nLKDFJASKLDFJKLSDJFKLDSJFLKJDSFLKJ\n");
    //         //printf("\n%c", can_frame_matrix[index]);
    //         // index++;
    //     }
    // }

    //     //Converte a base de dados de binario para valores físicos
    //     char can_bin_data[10];
    //     index = 0;
    //     for (int i = 0; i < 8; i++)
    //     {
    //         char bin_data[10] = "";
    //         int startbit = Edrv_Act_1_msg[i].startBit;
    //         int finalbit = (startbit + Edrv_Act_1_msg[i].lenght);
    //         for (int j = startbit; j < finalbit; j++)
    //         {
    //             //bin_data = bin_data + can_frame_matrix[j];
    //             strcat(bin_data, can_frame_matrix[j]);
    //         }
    //         can_bin_data[index++] = bin_data;
    //         bin_data = "";
    //     }

    //     //Converte a base de dados de binario para valores físicos
    //     can_physval_data[8];

    //     for (int i = 0; i < 8; i++)
    //     {
    //     }
    // }

    // void funcao1(){

    //   int can_frame_matrix[10];
    //   int index = 0;
    //   for(int i = 0; i< 8; i++){
    //     for(int j = -1; j <-9; j--){

    //       can_frame_matrix[index++] = par_bin[i][j];

    //       }

    //     }

    //   //Converte a base de dados de binario para valores físicos
    //   can_bin_data[10];
    //   index = 0;
    //   for(int i =0; i < 8; i++){
    //     char bin_data[10] = "";
    //     int startbit = Edrv_Act_1_msg[i].startBit;
    //     int finalbit = (startbit + Edrv_Act_1_msg[i].lenght);
    //     for(int j = startbit; j<finalbit;j++){
    //       bin_data = bin_data + can_frame_matrix[j];
    //       }
    //     can_bin_data[index++] = bin_data;
    //     bin_data = "";
    //     }
}

int string_to_int(char *string)
{
    char *buffer;
    strcpy(buffer, string);
n = p

    unsigned int number = 0;
    unsigned int power = 1;
    const int LEN = strlen(buffer) - 1;
    const int BASE = 10;

    printf("\nAs letras para converter sao: %s\n", buffer);

    for (int i = 0; i <= LEN; i++)
    {
        number = number + (buffer[LEN - i] - '0') * power;
        power = power * BASE;
    }

    return number;
}

// int *dec_to_bin(int dec)
// {
//     int binNumber[8];
//     for (int i = 0; dec > 0; i++)
//     {
//         binNumber[i] = dec % 2;
//         dec = dec / 2;
//     }

//     return binNumber;
// }