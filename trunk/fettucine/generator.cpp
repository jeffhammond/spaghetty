/***************************************************************************

                  COPYRIGHT

The following is a notice of limited availability of the code, and disclaimer
which must be included in the prologue of the code and in all source listings
of the code.

Copyright Notice
 + 2009 University of Chicago

Permission is hereby granted to use, reproduce, prepare derivative works, and
to redistribute to others.  This software was authored by:

Jeff R. Hammond
Leadership Computing Facility
Argonne National Laboratory
Argonne IL 60439 USA
phone: (630) 252-5381
e-mail: jhammond@mcs.anl.gov

                  GOVERNMENT LICENSE

Portions of this material resulted from work developed under a U.S.
Government Contract and are subject to the following license: the Government
is granted for itself and others acting on its behalf a paid-up, nonexclusive,
irrevocable worldwide license in this computer software to reproduce, prepare
derivative works, and perform publicly and display publicly.

                  DISCLAIMER

This computer code material was prepared, in part, as an account of work
sponsored by an agency of the United States Government.  Neither the United
States, nor the University of Chicago, nor any of their employees, makes any
warranty express or implied, or assumes any legal liability or responsibility
for the accuracy, completeness, or usefulness of any information, apparatus,
product, or process disclosed, or represents that its use would not infringe
privately owned rights.

 ***************************************************************************/

#include "generator.hpp"

void generateSource()
{
    for (int a=1;a<=4;a++)
        for (int b=1;b<=4;b++)
            for (int c=1;c<=4;c++)
                for (int d=1;d<=4;d++)
                    if (a!=b && a!=c && a!=d && b!=c && b!=d && c!=d)
                    {
                        std::filebuf fb;
                        std::stringstream filename;
                        filename << "permute_" << a << b << c << d << ".c";
                        fb.open (filename.str().c_str(),std::ios::out);
                        std::ostream os(&fb);

                        for (int i=1;i<=4;i++)
                            for (int j=1;j<=4;j++)
                                for (int k=1;k<=4;k++)
                                    for (int l=1;l<=4;l++)
                                        if (i!=j && i!=k && i!=l && j!=k && j!=l && k!=l)
                                        {
                                            std::stringstream function;
                                            function << "permute_" << a << b << c << d << "_"<< i << j << k << l;
                                            std::string fname = function.str();
                                            //std::cout << fname << std::endl;
                                            Transposer tr(os,fname,a,b,c,d,i,j,k,l);
                                        }
                        fb.close();
                    }
    return;
}

void generateTest(int dim1, int dim2, int dim3, int dim4)
{
    std::filebuf fb;
    std::stringstream filename;
    filename << "test.c";
    fb.open (filename.str().c_str(),std::ios::out);
    std::ostream os(&fb);

    const int count = 100;

    os << "#include <stdio.h>\n";
    os << "#include <stdlib.h>\n";
    os << "#include <math.h>\n";
    //os << "#include <omp.h>\n";
    os << "\n";
    os << "unsigned long long getticks(void);\n";
    os << "void init4d(int dim1, int dim2, int dim3, int dim4, double * ptr);\n";
    os << "void zero4d(int dim1, int dim2, int dim3, int dim4, double * ptr);\n";
    os << "void rand4d(int dim1, int dim2, int dim3, int dim4, double * ptr);\n";
    os << "double diff4d(int dim1, int dim2, int dim3, int dim4, double * a, double * b);\n";
    os << "void print4d(int dim1, int dim2, int dim3, int dim4, double * ptr);\n";
    os << "void print4d2(int dim1, int dim2, int dim3, int dim4, double * a, double * b);\n";
    os << "\n";
    os << "int main()\n{\n";
    //os << "    double t0, t1;\n";
    os << "    unsigned long long t0, t1;\n";
    os << "\n";
    os << "    double * iptr = (double*) malloc(" << dim1 << "*" << dim2 << "*" << dim3 << "*" << dim4 << "*sizeof(double));\n";
    os << "    double * optr = (double*) malloc(" << dim1 << "*" << dim2 << "*" << dim3 << "*" << dim4 << "*sizeof(double));\n";
    os << "\n";
    os << "    rand4d(" << dim1 << "," << dim2 << "," << dim3 << "," << dim4 << ",iptr);\n";
    os << "    zero4d(" << dim1 << "," << dim2 << "," << dim3 << "," << dim4 << ",optr);\n";
    os << "\n";

    int a=4, b=3, c=2, d=1;
    int i=2, j=3, k=4, l=1;

    //    for (int a=1;a<=4;a++)
//        for (int b=1;b<=4;b++)
//            for (int c=1;c<=4;c++)
//                for (int d=1;d<=4;d++)

                    if (a!=b && a!=c && a!=d && b!=c && b!=d && c!=d)
                    {
                        os << "    printf(\"===========================================\\n\");\n";

//                        for (int i=1;i<=4;i++)
//                            for (int j=1;j<=4;j++)
//                                for (int k=1;k<=4;k++)
//                                    for (int l=1;l<=4;l++)

                                        if (i!=j && i!=k && i!=l && j!=k && j!=l && k!=l)
                                        {
                                            //os << "    t0 = omp_get_wtime();\n";
                                            os << "    t0 = getticks();\n";
                                            std::stringstream function;
                                            function << "permute_" << a << b << c << d << "_"<< i << j << k << l;
                                            std::string fname = function.str();
                                            os << "    for (int t=0;t<" << count << ";t++)" << fname << "(";
                                            os << dim1 << "," << dim2 << "," << dim3 << "," << dim4 << ",";
                                            os << "iptr" << "," << "optr";
                                            os << ");\n";
                                            //os << "    t1 = omp_get_wtime();\n";
                                            os << "    t1 = getticks();\n";
                                            //os << "    printf(\"" << fname << " took %lf seconds\\n\",(t1-t0)/" << count << ");\n";
                                            os << "    printf(\"" << fname << " took %12llu cycles\\n\",(t1-t0)/" << count << ");\n";
                                        }
                    }

    os << "    printf(\"===========================================\\n\");\n";
    os << "\n";
    os << "    print4d2(" << dim1 << "," << dim2 << "," << dim3 << "," << dim4 << ",iptr,optr);\n";
    os << "\n";
    os << "    free(iptr);\n";
    os << "    free(optr);\n";
    os << "\n";
    os << "    return 0;\n}\n";
    fb.close();

    return;
}

int main(int argc,char* argv[])
{
    generateSource();
    generateTest(3,3,3,3);

    return 0;
}

















