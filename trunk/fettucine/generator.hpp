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
#include <sstream>
#include <string>

template <class T>
inline std::string makeString(const T& in)
{
    std::stringstream out;
    out << in;
    return out.str();
}

template <class T>
inline T max(const T& x, const T& y)
{
    if (x>y) return x;
    else return y;
}


class Transposer
{
private:
    /* transpose order indices */
    int a, b, c, d;
    /* loop order indices */
    int p, q, r, s;

    void printIndices(std::ostream& ofile)
    {
        ofile << "Transposer("
                << a << "," << b << "," << c << "," << d << ","
                << p << "," << q << "," << r << "," << s << ")" << std::endl;
    }

    void generateCode(std::ostream& ofile, std::string& function);
    void generateUnrolled(std::ostream& ofile, std::string& function,int unrolling[]);

    void generateFor(std::ostream& ofile, std::string index, int begin, std::string bound, int jump);

    Transposer(std::ostream& ofile);

public:
    /* explicit constructor */
    Transposer(std::ostream& ofile, std::string& function,
                int _a, int _b, int _c, int _d,
                int _p, int _q, int _r, int _s)
    {
        a = _a; b = _b; c = _c; d = _d;
        p = _p; q = _q; r = _r; s = _s;

        //printIndices(std::cout);
        //generateCode(ofile,function);
        int u[4] = {1,1,1,1};
        generateUnrolled(ofile,function,u);
    }

    /* constructor which assumes loop order (most likely bad) */
    Transposer(std::ostream ofile, std::string& function,
                int _a, int _b, int _c, int _d) :
                p(_a), q(_b), r(_c), s(_d)
    {
        a = _a; b = _b; c = _c; d = _d;

        //printIndices(std::cout);
        //generateCode(ofile,function);
        int u[4] = {1,1,1,1};
        generateUnrolled(ofile,function,u);
    }

    /* default constructure is banned
        Transposer() : a(1), b(2), c(3), d(4),
                        p(1), q(2), r(3), s(4)
        {
            printIndices();
        } */
};


void Transposer::generateCode(std::ostream& ofile, std::string& function)
{
    //std::cerr << "generateCode(ofile)" << std::endl;

    ofile << "void " << "foo" << "(int dim1, int dim2, int dim3, int dim4, "
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

void Transposer::generateUnrolled(std::ostream& ofile, std::string& function, int unrolling[])
{
    //std::cerr << "generateUnrolled(ofile,";
    //for (int i=0; i<4;i++) std::cerr << unrolling[i];
    //std::cerr  << ")" << std::endl;

    ofile << "void " << function << "(int iMax, int jMax, int kMax, int lMax, "
            << "double* in, double* out)" << "\n"
            << "{" << "\n";

    std::string iInd[4], iMax[4];
    std::string oInd[4], oMax[4];
    std::string lInd[4], lMax[4];

    iInd[0] = makeString("i");
    iInd[1] = makeString("j");
    iInd[2] = makeString("k");
    iInd[3] = makeString("l");

    iMax[0] = makeString("iMax");
    iMax[1] = makeString("jMax");
    iMax[2] = makeString("kMax");
    iMax[3] = makeString("lMax");

    oInd[0] = (a==0) ? iInd[3] : iInd[a-1];
    oInd[1] = (b==0) ? iInd[3] : iInd[b-1];
    oInd[2] = (c==0) ? iInd[3] : iInd[c-1];
    oInd[3] = (d==0) ? iInd[3] : iInd[d-1];

    oMax[0] = (a==0) ? iMax[3] : iMax[a-1];
    oMax[1] = (b==0) ? iMax[3] : iMax[b-1];
    oMax[2] = (c==0) ? iMax[3] : iMax[c-1];
    oMax[3] = (d==0) ? iMax[3] : iMax[d-1];

    lInd[0] = (p==0) ? iInd[3] : iInd[p-1];
    lInd[1] = (q==0) ? iInd[3] : iInd[q-1];
    lInd[2] = (r==0) ? iInd[3] : iInd[r-1];
    lInd[3] = (s==0) ? iInd[3] : iInd[s-1];

    lMax[0] = (p==0) ? iMax[3] : iMax[p-1];
    lMax[1] = (q==0) ? iMax[3] : iMax[q-1];
    lMax[2] = (r==0) ? iMax[3] : iMax[r-1];
    lMax[3] = (s==0) ? iMax[3] : iMax[s-1];

    generateFor(ofile,lInd[0], 0, lMax[0], unrolling[0]);
    generateFor(ofile,lInd[1], 0, lMax[1], unrolling[1]);
    generateFor(ofile,lInd[2], 0, lMax[2], unrolling[2]);
    generateFor(ofile,lInd[3], 0, lMax[3], unrolling[3]);
    ofile << "  {" << "\n";

    ofile << "       out[";
    ofile << iInd[0] << "*" << iMax[1] << "*" << iMax[2] << "*" << iMax[3] << " + ";
    ofile << iInd[1] << "*" << iMax[2] << "*" << iMax[3] << " + ";
    ofile << iInd[2] << "*" << iMax[3] << " + ";
    ofile << iInd[3] << "] = \n";

    ofile << "        in[";
    ofile << oInd[0] << "*" << oMax[1] << "*" << oMax[2] << "*" << oMax[3] << " + ";
    ofile << oInd[1] << "*" << oMax[2] << "*" << oMax[3] << " + ";
    ofile << oInd[2] << "*" << oMax[3] << " + ";
    ofile << oInd[3] << "];\n";

    ofile << "  }" << "\n";

    ofile << "  return;" << "\n" << "} \n" << std::endl;
    return;
}

void Transposer::generateFor(std::ostream& ofile, std::string index, int begin, std::string bound, int jump)
{
    //std::cerr << "generateFor(ofile," << jump << ")" << std::endl;

    if (jump>0)
        ofile << "  for(int " << index << "=" << begin << ";" << index << "<" << bound << ";" << index << "+=" << jump << ")" << "\n";
    else
        ofile << "jump = " << jump << " does not make sense" << std::endl;
}
