#include <iostream>
#include <algorithm>
#include <vector>
#include <array>
#include "particle_set.h"
#include "euclidean.h"

static const unsigned NUMDIM = 3;
static const unsigned NUMATTRACTORS = 10;
static const unsigned NUMGRIDSTEPS=100;

typedef pso::CPoint<NUMDIM> CState;

struct CEval
{
  double operator()(const std::array<CState,NUMATTRACTORS> &pAttractors,
                    const std::array<double,NUMATTRACTORS> &pVars,
                    const CState &pP)
  {
    double lValue = 0;
    for(unsigned i=0;i<NUMATTRACTORS;++i)
      for(unsigned j=0;j<NUMDIM;++j)
        lValue -= exp(-(pAttractors[i][j]-pP[j])*(pAttractors[i][j]-pP[j])/(2*pVars[i]));
        //lValue += fabs(pAttractors[i][j]-pP[j]);
    return lValue;
  }
};
static CEval gEval;
static std::array<CState,NUMATTRACTORS> gAttractors;
static std::array<double,NUMATTRACTORS> gVars;

double run()
{

  for(unsigned i=0;i<NUMATTRACTORS;++i)
  {
    gVars[i] = pso::getRnd();
    std::cout << gAttractors[i] << ":" << gVars[i] << ",";
  }
  std::cout << std::endl;

  pso::CParticleSet<CState> lParticleSet(std::bind<double>(gEval,gAttractors,gVars,std::placeholders::_1));

  auto lBestX = lParticleSet.run();

  std::cout << lBestX << std::endl;


  return lBestX.value();
}

double inspect_grid(CState &pTest,CState &pBest,double &pMin,unsigned pDim)
{
  if(pDim==NUMDIM)
  {
    double lEval = gEval(gAttractors,gVars,pTest);
    if(lEval<pMin)
    {
      pMin = lEval;
      pBest = pTest;
    }
    return lEval;
  }
  pDim++;
  for(unsigned i=0;i<NUMGRIDSTEPS;++i)
  {
    pTest[pDim-1] = double(i)/double(NUMGRIDSTEPS);
    inspect_grid(pTest,pBest,pMin,pDim);
  }
}

double run_grid()
{
  double lMin = 10000;
  CState lTest;
  CState lBest(lTest);
  inspect_grid(lTest,lBest,lMin,0);
  std::cout << "best: " << lBest << ":" << lMin << std::endl;
}

int main(int argc,char* argv[])
{
  std::cout << run() << std::endl;
  run_grid();
}
