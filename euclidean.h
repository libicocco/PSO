#ifndef __PSO_EUCLIDEAN_H__
#define __PSO_EUCLIDEAN_H__

#include <iostream>
#include <array>
#include <utility>
#include "particle_set.h"

static unsigned gPointCount;

namespace pso
{
  template <unsigned DIM>
    struct CPoint
    {
      public:
        CPoint()
        {
          for(auto lDimIt=mX.begin();lDimIt!=mX.end();++lDimIt)
            *lDimIt=getRnd();
          std::cout << "point " << gPointCount++ << std::endl;
        }
        CPoint(const CPoint &pP): mX(pP.mX){}

        CPoint(const CPoint &&pP): mX(std::move(pP.mX)){}

        CPoint operator= (const CPoint &pP)
        {
          return CPoint(pP);
        }
        CPoint operator= (const CPoint &&pP)
        {
          //swap(const_cast<CPoint &>(pP));
          mX = std::move(pP.mX);
          return *this;
        }

        std::array<double,DIM> mX;
    };

  template <unsigned DIM>
    CPoint<DIM> operator -(const CPoint<DIM> &pP0,const CPoint<DIM> &pP1)
    {
      CPoint<DIM> lResult;
      for(unsigned i=0;i<DIM;++i)
        lResult.mX[i]=pP0.mX[i]-pP1.mX[i]; 
      return lResult;
    }

  template <unsigned DIM>
    CPoint<DIM> operator +(const CPoint<DIM> &pP0,const CPoint<DIM> &pP1)
    {
      CPoint<DIM> lResult;
      for(unsigned i=0;i<DIM;++i)
        lResult.mX[i]=pP0.mX[i]+pP1.mX[i]; 
      return lResult;
    }

  template <unsigned DIM>
    CPoint<DIM> operator +(const CPoint<DIM> &pP0,const CPoint<DIM> &&pP1)
    {
      CPoint<DIM> &lResult = const_cast<CPoint<DIM>&>(pP1);
      for(unsigned i=0;i<DIM;++i)
        lResult.mX[i]+=pP0.mX[i]; 
      return lResult;
    }

  template <unsigned DIM>
    CPoint<DIM> operator *(const double pS,const CPoint<DIM> &pP1)
    {
      CPoint<DIM> lResult;
      for(unsigned i=0;i<DIM;++i)
        lResult.mX[i]=pS*pP1.mX[i]; 
      return lResult;
    }

  template <unsigned DIM>
    CPoint<DIM> operator *(const double pS,const CPoint<DIM> &&pP1)
    {
      CPoint<DIM> &lResult = const_cast<CPoint<DIM>&>(pP1);
      for(unsigned i=0;i<DIM;++i)
        lResult.mX[i]*=pS; 
      return lResult;
    }

  template <unsigned DIM>
    std::ostream& operator<< (std::ostream& pOS,const CPoint<DIM> &pP)
    {
      pOS << "(";
      for(unsigned i=0;i<DIM-1;++i)
        pOS << pP.mX[i] << ",";
      pOS << pP.mX[DIM-1] << ")";
      return pOS;
    }
}//namespace pso
#endif// __PSO_EUCLIDEAN_H__
