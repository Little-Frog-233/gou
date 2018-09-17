#include <iostream>
#include <stdio.h>

const double _tao = 14.49205211;
const double _s = 0.54901653;
const double _h_prime = 0.04106864;
const double _p = 0.00464183;
const double _N_prime = 0.00220641;
const double _p_prime = 0.00000196;

int main(void)
{
    char flag;
    double sigma = 0.0;
    int miu[6] = {0};
    while(1)
    {
        printf("enter the number:\n");
        for(int i = 0; i < 6; i++)
        {
        scanf("%d",&miu[i]);
        }
        getchar();

        sigma = miu[0]*_tao + miu[1]*_s + miu[2]*_h_prime + miu[3]*_p + miu[4]*_N_prime + miu[5]*_p_prime;

        printf("sigma = %.10lf\n",sigma);
        printf("go on?\n");
        scanf("%c",&flag);
        if(flag != 'y')
            break;
    }

    printf("END!\n");
    return 0;
}
