#ifndef __PSO_PARTICLE_H__
#define __PSO_PARTICLE_H__

#include <functional>

namespace pso
{
  template <typename tState>
    struct CParticle
    {
      CParticle(const std::function<double(tState)> &pEval,double pW,double pWp,double pWg):
        mX()
        ,mBestX(mX)
        ,mV()
        ,mW(pW)
        ,mWp(pWp)
        ,mWg(pWg)
        ,mEval(pEval)
        ,mBestValue(mEval(mBestX))
      {
      }

      void update(tState &pGlobalBestX,double pRp, double pRg)
      {
        mV = mW*mV + mWp*pRp*(mBestX-mX) + mWg*pRg*(pGlobalBestX-mX);
        mX = mX+mV;
        double lValue = mEval(mX);
        if ( lValue < mBestValue)
        {
          mBestX = mX;
          mBestValue = lValue;
        }
      }

      double value() const {return mBestValue;}

      tState mX;
      const std::function<double(tState)> mEval;

      tState mBestX;
      tState mV;
      const double mW,mWp,mWg;
      double mBestValue;
    };

  template <typename tState>
    bool operator < (CParticle<tState> pP0, CParticle<tState> pP1)
    {
      return pP0.value() < pP1.value();
    }

  template <typename tState>
    std::ostream& operator<< (std::ostream& pOS,const CParticle<tState> &pP)
    {
      pOS << "[c:" << pP.mBestX << ";b:" << pP.mX << ";v:" << pP.value() << "]";
      return pOS;
    }
}//namespace pso
#endif// __PSO_PARTICLE_H__
