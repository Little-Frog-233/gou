#include <eigen3/Eigen/Dense>
#include <iostream>

using namespace std;
using namespace Eigen;

int main(void)
{

    int a[12] = {1,2,3,4,5,6,7,8,9,10,11,12};
    Map<VectorXi> B(a,12);
    cout<<"B = "<<B<<endl;


    Map<MatrixXi,0,OuterStride<> > MM(a,3,4,OuterStride<>(3));

    MatrixXi KK = MM.transpose();

    cout<<"MM = "<<endl<<MM<<endl;
    cout<<"KK = "<<endl<<KK<<endl;

    cout<<endl<<endl;

    int k = 3;
    MatrixXd K(k,k);
    K<<1,2,3,4,5,6,7,8,9;
    for(int i = 0; i < 3; i++)
    {
        K(0,i) = K(1,i);
        K(0,i) = K(2,i);
    }
    cout<<K<<endl<<endl;


    Matrix3d m = Matrix3d::Random();
    cout<<"m[0][1]="<<m(0,1)<<endl;
    Vector3d y = Vector3d::Random();
    cout<<"y[1]="<<y(1)<<endl;

    cout << "Here is the matrix m:" << endl << m << endl;
    cout << "Here is the vector y:" << endl << y << endl;

    Vector3d x;
    x = m.colPivHouseholderQr().solve(y);
    cout<<"Here is the solution of x"<<endl<<x<<endl;

    cout<<"M * X ="<<endl<<m*x<<endl;
}
