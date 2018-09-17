#include "dataio.h"
#include "parameterCal.h"
#include "linerSolver.h"
#define DEBUG 0

const double TRANS = 3.141592653589/180.0;
const double _tao_dot = 14.49205211;
const double _s_dot = 0.54901653;
const double _h_prime_dot = 0.04106864;
const double _p_dot = 0.00464183;
const double _N_prime_dot = 0.00220641;
const double _p_prime_dot = 0.00000196;
// C语言的tm以1970年一月一日上午8点为0开始计数，这样的话就需要把时间从2000年一月一日转到1970年一月一日上午八点
// 闰年: 1972, 1976, 1980, 1984, 1988, 1992, 1996
const double _time_to_1970_ = (double)((30*365+7)*24*60*60+8*60*60);

// _rou sequence: M2 -> S2 -> K1 -> O1
// no S2
double _rmM2[4] = {0.0005, 1.0, 0.0006, 0.0002};
double _miuM2[8] = {0, -2, 0, 0, 2, 0, 2, 1};
double _rmK1[4] = {0.0002, 0.0001, 1.0, 0.1356};
double _miuK1[8] = {-2, -1, 0, -2, 0, 0, 0, 1};
double _rmO1[3] = {0.1885, 1.0, 0.0002};
double _miuO1[6] = {0, -1, 0, 0, 2, -1};

void parameterCal(TPNode * head)
{
    // _miu sequence:M2 -> S2 -> K1 -> O1
    int _miu[7*4] = {2, 0, 0, 0, 0, 0, 0,
        2, 2, -2, 0, 0, 0, 0,
        1, 1, 0, 0, 0, 0, 1,
        1, -1, 0, 0, 0, 0, -1};
    double sigma[4] = {0.0};
    // calculate the angle speed sigma 
    // sigma sequence: M2 -> S2 -> K1 -> O1
    sigma_calc(_miu, sigma);

#if DEBUG

    for(int i = 0; i < 4; i++)
        printf("2, sigma[%d] = %.10lf\n",i,sigma[i]);

#endif

    // calculate the phase position
    // calculate the f and u
    phasePositionFU(head, _miu);

#if 0
    PRINTFU(head);
#endif
    linearSolver(head, sigma);

}

void PRINTFU(TPNode * head)
{
    head = head->next;
    int count = 0;
    int space = 0;
    while(count<3)
    {
        space = (int)head->data.coor[2];
        for(int i = 0; i < space; i++)
        {
            printf("M2 = %f\n",head->data.M2);
            printf("S2 = %f\n",head->data.S2);
            printf("K1 = %f\n",head->data.K1);
            printf("O1 = %f\n",head->data.O1);
        }
        head = head->next;
        count++;
    }
}

void sigma_calc(int * miu, double * sigma)
{
    for(int i = 0; i < 4; i++)
    {
        // 这里的单位是角度
        sigma[i] = TRANS*(miu[7*i+0]*_tao_dot + miu[7*i+1]*_s_dot + miu[7*i+2]*_h_prime_dot + miu[7*i+3]*_p_dot + miu[7*i+4]*_N_prime_dot + miu[7*i+5]*_p_prime_dot);
#if DEBUG
        printf("sigma[%d] = %.10lf\n",i,sigma[i]);
#endif
    }
}

void phasePositionFU(TPNode * head, int * miu)
{
    head = head->next;

    // use the struct tm to convert the time to year(from 1990), day and other
    unsigned int space = 0;
    struct tm * timer = NULL;
    // time_t is seconds
    time_t sec = 0;
    unsigned int _year = 0;
    unsigned int _n = 0;
    unsigned int _t = 0;
    unsigned int _i = 0;

    double _s = 0.0;
    double _h_prime = 0.0;
    double _p = 0.0;
    double _N_prime = 0.0;
    double _p_prime = 0.0;
    double _tao = 0.0;

    double equ_1 = 0.0;
    double equ_2 = 0.0;

    while(head)
    {
        space = (int)head->data.coor[2];
        for(int i = 0; i < space; i++)
        {
            sec = head->data.tw[2*i] + _time_to_1970_;
            // get the seconds from the list
            timer = localtime(&sec);
            // the _year = Y - 1900
            _year = timer->tm_year;
            _n = timer->tm_yday;
            _t =timer->tm_hour;
            //        _t = 24*_n+_t;

#if 0
            printf("%d year\t%d callum_day\t%d hour\t\n",_year,_n,_t);
#endif
            _i = (_year-1)/4;

            // 下面的单位均转成弧度
            _s = TRANS*(277.02 + 129.3848*_year + 13.1764*(_n+_i+_t/24.0));
            _h_prime = TRANS*(280.19 - 0.2387*_year + 0.9857*(_n+_i+_t/24.0));
            _p = TRANS*(334.39 + 40.6625*_year + 0.1114*(_n+_i+_t/24.0));
            _N_prime = TRANS*(100.84 + 19.3282*_year + 0.0530*(_n+_i+_t/24.0));
            _p_prime = TRANS*(281.22 + 0.0172*_year + 0.00005*(_n+_i+_t/24.0));
            _tao = TRANS*(15.0*_t - _s + _h_prime);
#if 0
            printf("_i = %u, _s = %lf, _h_prime = %lf, _p = %lf, _N_prime = %lf, _p_prime = %lf, _tao = %lf\n\n",_i,_s,_h_prime,_p,_N_prime,_p_prime,_tao);
#endif



            // 下面得出来的结果都是弧度
            if(i == 0)
            {
                head->data.M2 = _tao*miu[0] + _s*miu[1] + _h_prime*miu[2] + _p*miu[3] + _N_prime*miu[4] + _p_prime*miu[5] + TRANS*90.0*miu[6];

                head->data.S2 = _tao*miu[7] + _s*miu[8] + _h_prime*miu[9] + _p*miu[10] + _N_prime*miu[11] + _p_prime*miu[12] + TRANS*90*miu[13];

                head->data.K1 = _tao*miu[14] + _s*miu[15] + _h_prime*miu[16] + _p*miu[17] + _N_prime*miu[18] + _p_prime*miu[19] + TRANS*90*miu[20];

                head->data.O1 = _tao*miu[21] + _s*miu[22] + _h_prime*miu[23] + _p*miu[24] + _N_prime*miu[25] + _p_prime*miu[26] + TRANS*90*miu[27];
            }

            head->data.M2_f = (double*)malloc(space*sizeof(double));
            head->data.M2_u = (double*)malloc(space*sizeof(double));
            head->data.K1_f = (double*)malloc(space*sizeof(double));
            head->data.K1_u = (double*)malloc(space*sizeof(double));
            head->data.O1_f = (double*)malloc(space*sizeof(double));
            head->data.O1_u = (double*)malloc(space*sizeof(double));




            // 下面所有的equ_1与equ_2的计算结果都是以弧度进行计算的，下面的f求解使用的equ_1无需转换成弧度了
            equ_1 = _rmM2[0]*cos(_miuM2[0]*_p + _miuM2[1]*_N_prime)
                + _rmM2[1]*cos(_miuM2[2]*_p + _miuM2[3]*_N_prime)
                + _rmM2[2]*cos(_miuM2[4]*_p + _miuM2[5]*_N_prime)
                + _rmM2[3]*cos(_miuM2[6]*_p + _miuM2[7]*_N_prime);

            equ_2 = _rmM2[0]*sin(_miuM2[0]*_p+_miuM2[1]*_N_prime)
                + _rmM2[1]*sin(_miuM2[2]*_p + _miuM2[3]*_N_prime)
                + _rmM2[2]*sin(_miuM2[4]*_p + _miuM2[5]*_N_prime)
                + _rmM2[3]*sin(_miuM2[6]*_p + _miuM2[7]*_N_prime);
            head->data.M2_u[i] = atan2(equ_2,equ_1);
            head->data.M2_f[i] = equ_1/cos(head->data.M2_u[i]);

            head->data.S2_u = 0.0;
            head->data.S2_f = 1.0;


            equ_1 = _rmK1[0]*cos(_miuK1[0]*_p+_miuK1[1]*_N_prime)
                + _rmK1[1]*cos(_miuK1[2]*_p + _miuK1[3]*_N_prime)
                + _rmK1[2]*cos(_miuK1[4]*_p + _miuK1[5]*_N_prime)
                + _rmK1[3]*cos(_miuK1[6]*_p + _miuK1[7]*_N_prime);

            equ_2 = _rmK1[0]*sin(_miuK1[0]*_p+_miuK1[1]*_N_prime)
                + _rmK1[1]*sin(_miuK1[2]*_p + _miuK1[3]*_N_prime)
                + _rmK1[2]*sin(_miuK1[4]*_p + _miuK1[5]*_N_prime)
                + _rmK1[3]*sin(_miuK1[6]*_p + _miuK1[7]*_N_prime);
            head->data.K1_u[i] = atan2(equ_2,equ_1);
            head->data.K1_f[i] = equ_1/cos(head->data.K1_u[i]);

            equ_1 = _rmO1[0]*cos(_miuO1[0]*_p+_miuO1[1]*_N_prime)
                + _rmO1[1]*cos(_miuO1[2]*_p + _miuO1[3]*_N_prime)
                + _rmO1[2]*cos(_miuO1[4]*_p + _miuO1[5]*_N_prime);

            equ_2 = _rmO1[0]*sin(_miuO1[0]*_p+_miuO1[1]*_N_prime)
                + _rmO1[1]*sin(_miuO1[2]*_p + _miuO1[3]*_N_prime)
                + _rmO1[2]*sin(_miuO1[4]*_p + _miuO1[5]*_N_prime);
            head->data.O1_u[i] = atan2(equ_2,equ_1);
            head->data.O1_f[i] = equ_1/cos(head->data.O1_u[i]);

        }
        head = head->next;
    }
}
