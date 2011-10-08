#ifndef __PSO_PARTICLE_SET_H__
#define __PSO_PARTICLE_SET_H__

#include <random>
#include <ctime>
#include "particle.h"

namespace pso
{
  static std::mt19937 gRndEngine(time(0));
  static std::uniform_real_distribution<> gRndDist(0,1.0);

  double getRnd() {return gRndDist(gRndEngine);}

  template<typename tState>
    class CParticleSet
    {
      public:
        CParticleSet(const std::function<double(tState)> &pEval,double pW=0.6,double pWp=0.6,double pWg=0.6,unsigned pNumParticles=10,double pTargetValue=0.00001,double pMaxIter=2):
          mParticles(pNumParticles,CParticle<tState>(pEval,pW,pWp,pWg))
          ,mTargetValue(pTargetValue)
          ,mMaxIter(pMaxIter)
          ,mCount(0)
      {}
        // XXX: cannot use auto or pointer!
        CParticle<tState> run()
        {
          auto lBestX = std::min_element(mParticles.begin(),mParticles.end());

          mCount = 0;
          while (lBestX->value() > mTargetValue && mCount < mMaxIter)
          {
            mCount++;
            std::cout << *this << std::endl;
            for(auto lPart=mParticles.begin();lPart!=mParticles.end();++lPart)
            {
              lPart->update(lBestX->mX,getRnd(),getRnd());
            }

            lBestX = std::min_element(mParticles.begin(),mParticles.end());
          }
          return *lBestX;
        }

        friend std::ostream& operator<< (std::ostream& pOS,const CParticleSet<tState> &pPS)
        {
          std::cout << "==Particle set for iteration " << pPS.mCount << "==" << std::endl;
          for(auto lPit=pPS.mParticles.begin();lPit!=pPS.mParticles.end();++lPit)
            pOS << *lPit << std::endl;
          return pOS;
        }

      private:
        std::vector<CParticle<tState>> mParticles;
        const double mTargetValue,mMaxIter;
        unsigned mCount;
    };

}//namespace pso
#endif// __PSO_PARTICLE_SET_H__