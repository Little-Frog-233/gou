#include <iostream>
#include <eigen3/Eigen/Dense>
#include <time.h>
#include <math.h>
#include "dataio.h"
#include "linerSolver.h"

#define DEBUG 0
#define DEBUG1 1

using namespace std;
using namespace Eigen;

const double _time_to_1970_ = (double)((30*365+7)*24*60*60+8*60*60);



void linearSolver(TPNode * head, double * sigma)
{
    // 目前定义分潮数J=4
    unsigned int J = 4;

    TPNode * t = head;
    t = t->next;
    while(t)
    {
        if(t->data.coor[2] < (2*J+1))
        {
            t = t->next;
        }
        else 
        {
            coeff(t,sigma,J);
            t = t->next;
        }
    }

}

/*
 * J 是分潮数量,后面需要加上
 *
 *
 * */
void coeff(TPNode * t, double * sigma, unsigned int J)
{
    unsigned int length = (int)t->data.coor[2];
    struct tm * timer = NULL;
    time_t sec = 0;
    unsigned int _hour[length] = {0};
#if 0
    printf("length = %u\n",length);
#endif

    double M2_g = 0.0;
    double M2_H = 0.0;
    double S2_g = 0.0;
    double S2_H = 0.0;
    double K1_g = 0.0;
    double K1_H = 0.0;
    double O1_g = 0.0;
    double O1_H = 0.0;

    double * Para = (double*)malloc((2*J+1)*length*sizeof(double));
    t->data.founier = (double*)malloc((2*J)*sizeof(double));
    double * tw_array = (double*)malloc(length*sizeof(double));




    // time variable is here
    for(int i = 0; i < length; i++)
    {
        sec = t->data.tw[2*i] + _time_to_1970_;
        timer = localtime(&sec);
        _hour[i] = timer->tm_hour;
//        _hour[i] = timer->tm_hour + 24 * timer->tm_yday;
    }

    for(int i = 0; i < length; i++)
    {
        Para[(2*J+1)*i+0] = 1.0;
    

    // get the data for M2
        Para[(2*J+1)*i+1] = (t->data.M2_f[i]) * cos(sigma[0]*_hour[i] + t->data.M2 + t->data.M2_u[i]);
        Para[(2*J+1)*i+2] = (t->data.M2_f[i]) * sin(sigma[0]*_hour[i] + t->data.M2 + t->data.M2_u[i]);
    

    // get the data for S2
        //Para[(2*J+1)*i+3] = (t->data.S2_f) * cos(sigma[1]*_hour[i] + t->data.S2[i] + t->data.S2_u);
        Para[(2*J+1)*i+3] = (t->data.S2_f) * cos(sigma[1]*_hour[i] + t->data.S2 + t->data.S2_u);
#if 0
//    printf("sigma[1]*_hour[i] + t->data.S2[i] + t->data.S2_u) = %lf\n",sigma[1]*_hour[i] + t->data.S2[i] + t->data.S2_u);
//    printf("cos(sigma[1]*_hour[i] + t->data.S2[i] + t->data.S2_u)) = %lf\n",cos(sigma[1]*_hour[i] + t->data.S2[i] + t->data.S2_u));
//    printf("sin(sigma[1]*_hour[i] + t->data.S2[i] + t->data.S2_u)) = %lf\n",sin(sigma[1]*_hour[i] + t->data.S2[i] + t->data.S2_u));
//    printf("sigma[1] = %lf\t hour[i] = %d\t t->data.S2[i] = %lf, t->data.S2_u = %lf\n",sigma[1], _hour[i], t->data.S2[i], t->data.S2_u);
#endif
        Para[(2*J+1)*i+4] = (t->data.S2_f) * sin(sigma[1]*_hour[i] + t->data.S2 + t->data.S2_u);


#if 0
        printf("Para[(2*J+1)*i+3] = %lf\n",Para[(2*J+1)*i+3]);
        printf("Para[(2*J+1)*i+4] = %lf\n",Para[(2*J+1)*i+4]);
//        printf("(t->data.S2_f) * cos(sigma[1]*_hour[i] + t->data.S2[i] + t->data.S2_u) = %f\n ",(t->data.S2_f) * cos(sigma[1]*_hour[i] + t->data.S2[i] + t->data.S2_u));
//        printf("(t->data.S2_f) * sin(sigma[1]*_hour[i] + t->data.S2[i] + t->data.S2_u) = %f\n ",(t->data.S2_f) * sin(sigma[1]*_hour[i] + t->data.S2[i] + t->data.S2_u));
#endif

#if DEBUG
        static int test_1 = 0;
        if(test_1 < 10)
        {
            printf("t->data.S2[i] = %lf\n",t->data.S2[test_1]);
    printf("Para = %lf\t Para = ",Para[(2*J+1)*test_1+3]);
        }

#endif
    

    // get the data for K1
        Para[(2*J+1)*i+5] = (t->data.K1_f[i]) * cos(sigma[2]*_hour[i] + t->data.K1 + t->data.K1_u[i]);
        Para[(2*J+1)*i+6] = (t->data.K1_f[i]) * sin(sigma[2]*_hour[i] + t->data.K1 + t->data.K1_u[i]);
    

    // get the data for O1
        Para[(2*J+1)*i+7] = (t->data.O1_f[i]) * cos(sigma[3]*_hour[i] + t->data.O1 + t->data.O1_u[i]);
        Para[(2*J+1)*i+8] = (t->data.O1_f[i]) * sin(sigma[3]*_hour[i] + t->data.O1 + t->data.O1_u[i]);
    
    }

#if 0
    printf("Here Success!");
#endif


    if(length == 2*J+1)
    {
        //
        Map<MatrixXd,0,OuterStride<> > A_temp(Para,(2*J+1),(2*J+1),OuterStride<>(2*J+1));
        MatrixXd A = A_temp.transpose();
        
#if DEBUG
    cout<<"A = "<<endl<<fixed<<A<<endl;

#endif

        double count = 0.0;
        for(int ii = 0; ii < length; ii++)
        {
            tw_array[ii] = t->data.tw[2*ii+1];
        }
        Map<VectorXd> B(tw_array,2*J+1);
//        for(int h = 0; h < 2*J; h++)
//        {
//            B(h+1) = B(0);
//        }



#if DEBUG1 
    cout <<"B = "<<endl<< B<<endl;
#endif

        // the result of the linear equation
        VectorXd X(2*J+1);

        // ATTENTION:!! 这里求出来的结果并不是最终的调和常数，分别是(Hj)i*cos(gj)(对应于xi)与(Hj)sin(gj)(对应于yi)
        X = A.colPivHouseholderQr().solve(B);

#if DEBUG1
    cout<<"X = "<<endl<< X<<endl;

#endif

        M2_g = atan2(X(2),X(1));
        M2_H = X(1)/cos(M2_g);

        S2_g = atan2(X(4),X(3));
        S2_H = X(3)/cos(S2_g);

        K1_g = atan2(X(6),X(5));
        K1_H = X(5)/cos(K1_g);

        O1_g = atan2(X(8),X(7));
        O1_H = X(7)/cos(O1_g);
        // this place is for storage in heap space

        t->data.founier[0] = M2_H;
        t->data.founier[1] = M2_g;

        t->data.founier[2] = S2_H;
        t->data.founier[3] = S2_g;

        t->data.founier[4] = K1_H;
        t->data.founier[5] = K1_g;

        t->data.founier[6] = O1_H;
        t->data.founier[7] = O1_g;

#if DEBUG1
        for(int mm = 0; mm < 2*J; mm++)
        {
            printf("t->data.founier[%d] = %.12lf\n",mm,t->data.founier[mm]);
            if(mm%2 == 0)
                printf("\n");
        }
        printf("\n\n");
#endif



    }else{
        Map<MatrixXd,0,OuterStride<> > ParaEigen_temp(Para,(2*J+1),length,OuterStride<>(2*J+1));
        MatrixXd ParaEigen = ParaEigen_temp.transpose();
#if DEBUG
    cout<<endl<<"ParaEigen = "<< endl<<ParaEigen<<endl;

#endif

        MatrixXd M(2*J+1,2*J+1);
        M = ParaEigen.transpose() * ParaEigen;
#if DEBUG
    cout<<endl<<"M = "<<endl<< M<<endl;

#endif

//        VectorXd N_eigen(2*J+1);
        double count = 0.0;
        for(int ii = 0; ii < length; ii++)
        {
            count += t->data.tw[2*ii+1];
        }
        double tmp[2*J+1]= {count};
        Map<VectorXd> N_eigen(tmp,2*J+1);
        for(int h = 0; h < 2*J; h++)
        {
            N_eigen(h+1) = N_eigen(0);
        }
#if DEBUG
    cout<<endl<<"N_eigen = "<<endl<< N_eigen<<endl;

#endif

        VectorXd X(2*J+1);
        X = M.colPivHouseholderQr().solve(N_eigen);
#if DEBUG
    cout<<"X = "<< X<<endl;

#endif

        M2_g = atan2(X(2),X(1));
        M2_H = X(1)/cos(M2_g);

        S2_g = atan2(X(4),X(3));
        S2_H = X(3)/cos(S2_g);

        K1_g = atan2(X(6),X(5));
        K1_H = X(5)/cos(K1_g);

        O1_g = atan2(X(8),X(7));
        O1_H = X(7)/cos(O1_g);

        // this place is for storage in heap space
         

        t->data.founier[0] = M2_H;
        t->data.founier[1] = M2_g;

        t->data.founier[2] = S2_H;
        t->data.founier[3] = S2_g;

        t->data.founier[4] = K1_H;
        t->data.founier[5] = K1_g;

        t->data.founier[6] = O1_H;
        t->data.founier[7] = O1_g;
    }

#if DEBUG
    static int i = 10;
    if(i > 0)
    {
        for(int mm = 0; mm < 2*J; mm++)
        {
            printf("t->data.founier[%d] = %.12lf\n",mm,t->data.founier[mm]);
            if(mm%2 ==0)
            {
                printf("\n");
            }
        }
        printf("\n\n");
        i--;
    }
#endif

#if 0
    if(length == 176)
    {
        printf("(%lf,%lf)\n",t->data.coor[0],t->data.coor[1]);
        for(int mm = 0; mm < 2*J; mm++)
        {
            printf("t->data.founier[%d] = %.12lf\n",mm,t->data.founier[mm]);
        }
        printf("\n\n");
    }
#endif

    free(tw_array);
    free(Para);
}






