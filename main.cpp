#include <iostream>
#include <cmath>
#include <stdio.h>
#include <cmath>
#define PI 3.14159265

using namespace std;



int main()
{
    static double dospi = 3.14159265*2;
    FILE * pIn;
    FILE * pOut;
    pIn = fopen("C:\\aud.kau", "rb");
    pOut = fopen("C:\\out_aud.raw", "wb");
    int numwaves;
    fread(&numwaves, sizeof(numwaves), 1, pIn);
    short cur_ampli[numwaves], cur_freq[numwaves], cur_repeat[numwaves];
    int total;
    short output;
    short new_freq;
    cout << "Working.";
    // counters
    int counter[numwaves];
    for (int i=0; i<numwaves; i++) counter[i] = 0;
    do {
        total = 0;
        for (int i=0; i<numwaves; i++) {
            fread(&new_freq, sizeof(output), 1, pIn);
            fread(&(cur_ampli[i]), sizeof(output), 1, pIn);
            counter[i] = (int)((double)(new_freq * counter[i]) / cur_freq[i]);
            cur_freq[i] = new_freq;
            cur_repeat[i] = (double)44100 / cur_freq[i];
            //cur_freq[i] = ;
        }
        for (int samp=0; samp<1024; samp++) {
            for (int i=0; i<numwaves; i++) {
                total += cur_ampli[i]*(sin(cur_freq[i]*dospi*counter[i]/44100));
                counter[i]++;
                if (counter[i]>cur_repeat[i]) counter[i] = 1;
            }
            total = (double)total / (double)1.5;
            output = total / numwaves;
            fwrite(&output, sizeof(output), 1, pOut);

        }
    } while (!feof(pIn));
    fclose(pIn);
    fclose(pOut);
    cout << "Work is done.";
    return 0;
}
