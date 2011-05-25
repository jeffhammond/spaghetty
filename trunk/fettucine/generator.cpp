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

int main(int argc,char* argv[])
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

    return 0;
}

















