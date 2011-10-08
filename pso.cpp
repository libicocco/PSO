#include <iostream>
#include <algorithm>
#include <vector>
#include "particle_set.h"
#include "euclidean.h"

static const unsigned NUMDIM = 2;
static const unsigned NUMATTRACTORS = 1;

typedef pso::CPoint<NUMDIM> CState;

struct CEval
{
  double operator()(const std::array<std::array<double,NUMDIM>,NUMATTRACTORS> &pAttractors,
                    const std::array<double,NUMATTRACTORS> &pVars,
                    const CState &pP)
  {
    double lValue = 0;
    for(unsigned i=0;i<NUMATTRACTORS;++i)
      for(unsigned j=0;j<NUMDIM;++j)
        lValue += fabs(pAttractors[i][j]-pP.mX[j]);
        //lValue += exp(-(pAttractors[i][j]-pP.mX[j])*(pAttractors[i][j]-pP.mX[j])/(2*pVars[i]));
    //std::cout << "(" << pAttractors[0][0] << "," << pAttractors[0][1] << "),(" << pP.mX[0] << "," << pP.mX[1] << "):" << lValue << std::endl;
    return lValue;
  }
};
static CEval gEval;

double run()
{

  std::array<std::array<double,NUMDIM>,NUMATTRACTORS> lAttractors;
  std::array<double,NUMATTRACTORS> lVars;
  for(unsigned i=0;i<NUMATTRACTORS;++i)
  {
    lVars[i] = pso::getRnd();
    std::cout << "(";
    for(unsigned j=0;j<NUMDIM;++j)
    {
      lAttractors[i][j] = pso::getRnd();
      std::cout << lAttractors[i][j] << ",";
    }
    std::cout << "):" << lVars[i] << ",";
  }
  std::cout << std::endl;

  pso::CParticleSet<CState> lParticleSet(std::bind<double>(gEval,lAttractors,lVars,std::placeholders::_1));

  auto lBestX = lParticleSet.run();

  std::cout << lBestX << std::endl;

  return lBestX.value();
}

int main(int argc,char* argv[])
{
  gPointCount = 0;
  std::cout << run() << std::endl;
}