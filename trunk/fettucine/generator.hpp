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

#include <iostream>
#include <fstream>

class Transposer
{
    private:
        /* transpose order indices */
        int a, b, c, d;
        /* loop order indices */
        int p, q, r, s;

        void printIndices()
        {
            std::cout << "Transposer("
                      << a << "," << b << "," << c << "," << d << ","
                      << p << "," << q << "," << r << "," << s << ")" << std::endl;
        }

        void generateCode();
        void generateUnrolled1(int unrolling);

        void generateFor(int unrolling);

        Transposer();

    public:
        /* explicit constructor */
        Transposer(int _a, int _b, int _c, int _d,
                    int _p, int _q, int _r, int _s)
        {
            a = _a; b = _b; c = _c; d = _d;
            p = _p; q = _q; r = _r; s = _s;

            printIndices();
            //generateCode();
            generateUnrolled1(2);
        }

        /* constructor which assumes loop order (most likely bad) */
        Transposer(int _a, int _b, int _c, int _d) :
                    p(1), q(2), r(3), s(4)
        {
            a = _a; b = _b; c = _c; d = _d;

            printIndices();
            //generateCode();
            generateUnrolled1(2);
        }

        /* default constructure is banned
        Transposer() : a(1), b(2), c(3), d(4),
                        p(1), q(2), r(3), s(4)
        {
            printIndices();
        } */
};


void Transposer::generateCode()
{
    std::cout << "generateCode()" << std::endl;

    std::cout << "void " << "foo" << "(int dim1, int dim2, int dim3, int dim4, "
              << "double factor, double* in, double* out)" << "\n"
              << "{" << "\n"
              << "  unsigned int j1,j2,j3,j4;" << "\n"
              << "  for( j" << p << " = 0; j" << p << "<dim" << p << "; j" << p << "++)" << "\n"
              << "    for( j" << q << " = 0; j" << q << "<dim" << q << "; j" << q << "++)" << "\n"
              << "      for( j" << r << " = 0; j" << r << "<dim" << r << "; j" << r << "++)" << "\n"
              << "        for( j" << s << " = 0; j" << s << "<dim" << s << "; j" << s << "++)" << "\n"
              << "        {" << "\n"
              << "          out[j" << d << "+dim" << d << "*(j" << c << "+dim" << c << "*(j" << b << "+dim" << b << "*(j" << a << ")))]"
              <<         " = factor*in[j4+dim4*(j3+dim3*(j2+dim2*(j1)))];\n"
              << "        }" << "\n"
              << "  return;" << "\n"
              << "};" << std::endl;
    return;
}

void Transposer::generateUnrolled1(int unrolling)
{
    int u;

    std::cout << "generateUnrolled1(" << unrolling << ")" << std::endl;

        std::cout << "void " << "foo" << "(int dim1, int dim2, int dim3, int dim4, "
                  << "double factor, double* in, double* out)" << "\n"
                  << "{" << "\n"
                  << "  unsigned int j1,j2,j3,j4;" << "\n";

    if (p==1)
        std::cout << "  for( j" << p << " = 0; j" << p << "<dim" << p << "; j" << p << "+=" << unrolling << ")" << "\n";
    else
        std::cout << "  for( j" << p << " = 0; j" << p << "<dim" << p << "; j" << p << "++)" << "\n";

    if (q==1)
        std::cout << "  for( j" << q << " = 0; j" << q << "<dim" << q << "; j" << q << "+=" << unrolling << ")" << "\n";
    else
        std::cout << "  for( j" << q << " = 0; j" << q << "<dim" << q << "; j" << q << "++)" << "\n";

    if (r==1)
        std::cout << "  for( j" << r << " = 0; j" << r << "<dim" << r << "; j" << r << "+=" << unrolling << ")" << "\n";
    else
        std::cout << "  for( j" << r << " = 0; j" << r << "<dim" << r << "; j" << r << "++)" << "\n";

    if (s==1)
        std::cout << "  for( j" << s << " = 0; j" << s << "<dim" << s << "; j" << s << "+=" << unrolling << ")" << "\n";
    else
        std::cout << "  for( j" << s << " = 0; j" << s << "<dim" << s << "; j" << s << "++)" << "\n";

        std::cout << "  {" << "\n";

    for (u=0; u<unrolling; u++)
    {
        if (a==1)
            std::cout << "          out[j" << d << "+dim" << d << "*(j" << c << "+dim" << c << "*(j" << b << "+dim" << b << "*(" << u << "+j" << a << ")))]";
        else if (b==1)
            std::cout << "          out[j" << d << "+dim" << d << "*(j" << c << "+dim" << c << "*(" << u << "+j" << b << "+dim" << b << "*(j" << a << ")))]";
        else if (c==1)
            std::cout << "          out[j" << d << "+dim" << d << "*(" << u << "+j" << c << "+dim" << c << "*(j" << b << "+dim" << b << "*(j" << a << ")))]";
        else if (d==1)
            std::cout << "          out[" << u << "+j" << d << "+dim" << d << "*(j" << c << "+dim" << c << "*(j" << b << "+dim" << b << "+" << u << "*(j" << a << ")))]";
        else
            std::cout << "something is wrong" << std::endl;

        std::cout <<         " = factor*in[j4+dim4*(j3+dim3*(j2+dim2*(j1+" << u << ")))];\n";
    }

        std::cout << "  }" << "\n"
                  << "  return;" << "\n"
                  << "};" << std::endl;
    return;
}

void Transposer::generateFor(int unrolling)
{
    int u;

    std::cout << "generateFor(" << unrolling << ")" << std::endl;

    if (p==1)
        std::cout << "  for( j" << p << " = 0; j" << p << "<dim" << p << "; j" << p << "+=" << unrolling << ")" << "\n";
    else
        std::cout << "  for( j" << p << " = 0; j" << p << "<dim" << p << "; j" << p << "++)" << "\n";
}


//        subroutine_name = 'transpose_'+A+B+C+D+'_loop_'+a+b+c+d+factor_version+'_'
//        source_name = subroutine_name+'.c'
//        source_file = open(source_name,'w')
//        source_file.write(cind+'void '+subroutine_name+'( double *unsorted, double *sorted,\n')
//        if (factor_version == '_plus') or (factor_version == '_minus'):
//            source_file.write(cind+8*ctab+'int *p_dim1, int *p_dim2, int *p_dim3, int *p_dim4 ) {\n\n')
//        elif (factor_version == '_phalf') or (factor_version == '_mhalf'):
//            source_file.write(cind+8*ctab+'int *p_dim1, int *p_dim2, int *p_dim3, int *p_dim4 ) {\n\n')
//        else:
//            source_file.write(cind+8*ctab+'int *p_dim1, int *p_dim2, int *p_dim3, int *p_dim4, double *p_factor ) {\n\n')
//            source_file.write(cind+'double factor = *p_factor;\n\n')
//        source_file.write(cind+'int dim1,dim2,dim3,dim4;\n')
//        source_file.write(cind+'unsigned int old_offset,new_offset;\n')
//        source_file.write(cind+'unsigned int j1,j2,j3,j4;\n')
//        source_file.write(cind+'dim1 = *p_dim1;\n')
//        source_file.write(cind+'dim2 = *p_dim2;\n')
//        source_file.write(cind+'dim3 = *p_dim3;\n')
//        source_file.write(cind+'dim4 = *p_dim4;\n\n')
//        #source_file.write(cind+'/* pluto start (dim1,dim2,dim3,dim4) */\n')
//        source_file.write(cind+0*ctab+'#pragma ivdep\n')
//        source_file.write(cind+0*ctab+'#pragma prefetch\n')
//        source_file.write(cind+0*ctab+'#pragma parallel\n')
//        source_file.write(cind+0*ctab+'#pragma loop count min(10) max(80) avg(40)\n')
//        source_file.write(cind+0*ctab+'#pragma unroll\n')
//        source_file.write(cind+0*ctab+'for( j'+a+' = 0; j'+a+'<dim'+a+'; j'+a+'++) {\n')
//        source_file.write(cind+1*ctab+'#pragma loop count min(10) max(80) avg(40)\n')
//        source_file.write(cind+1*ctab+'#pragma unroll\n')
//        source_file.write(cind+1*ctab+'for( j'+b+' = 0; j'+b+'<dim'+b+'; j'+b+'++) {\n')
//        source_file.write(cind+2*ctab+'#pragma loop count min(10) max(80) avg(40)\n')
//        source_file.write(cind+2*ctab+'#pragma unroll\n')
//        source_file.write(cind+2*ctab+'#pragma vector always\n')
//        source_file.write(cind+2*ctab+'for( j'+c+' = 0; j'+c+'<dim'+c+'; j'+c+'++) {\n')
//        source_file.write(cind+3*ctab+'#pragma loop count min(10) max(80) avg(40)\n')
//        source_file.write(cind+3*ctab+'#pragma unroll\n')
//        source_file.write(cind+3*ctab+'#pragma vector always\n')
//        source_file.write(cind+3*ctab+'for( j'+d+' = 0; j'+d+'<dim'+d+'; j'+d+'++) {\n')
//        source_file.write(cind+4*ctab+'old_offset = j4+dim4*(j3+dim3*(j2+dim2*(j1)));\n')
//        source_file.write(cind+4*ctab+'new_offset = j'+D+'+dim'+D+'*(j'+C+'+dim'+C+'*(j'+B+'+dim'+B+'*(j'+A+')));\n')
//        if (factor_version == '_plus'):
//            source_file.write(cind+4*ctab+'sorted[new_offset] = unsorted[old_offset];\n')
//        elif (factor_version == '_minus'):
//            source_file.write(cind+4*ctab+'sorted[new_offset] = -unsorted[old_offset];\n')
//        elif (factor_version == '_phalf'):
//            source_file.write(cind+4*ctab+'sorted[new_offset] = 0.5*unsorted[old_offset];\n')
//        elif (factor_version == '_mhalf'):
//            source_file.write(cind+4*ctab+'sorted[new_offset] = -0.5*unsorted[old_offset];\n')
//        else:
//            source_file.write(cind+4*ctab+'sorted[new_offset] = factor*unsorted[old_offset];\n')
//        source_file.write(cind+3*ctab+'}\n')
//        source_file.write(cind+2*ctab+'}\n')
//        source_file.write(cind+1*ctab+'}\n')
//        source_file.write(cind+'}\n')
//        #source_file.write(cind+'/* pluto end */\n')
//        source_file.write(cind+'return;\n')
//        source_file.write(cind+'}\n\n')
//        source_file.close()
