#ifndef __PSO_EUCLIDEAN_H__
#define __PSO_EUCLIDEAN_H__

#include <iostream>
#include <vector>
#include <utility>
#include "particle_set.h"


namespace pso
{
  namespace operators
  {
    class CDummy{}; // Dummy class to enable the operators for CPoint

    template<typename tLH,typename tRH>
      // SFINAE
      //typename std::enable_if<
      // return type is _2 unless if _1; otherwise this class is not defined
      // std::is_base_of<CDummy,typename std::decay<tLH>::type>::value, //
      // true if CDummy is a base of tLH (without references or cv qualifiers)
      // typename std::decay<tLH>::type>::type operator-(tLH &&pLH,tRH &&pRH)
      // return type
      typename std::enable_if<std::is_base_of<CDummy,typename std::decay<tLH>::type>::value, typename std::decay<tLH>::type>::type operator-(tLH &&pLH,tRH &&pRH)
      {
        typename std::decay<tLH>::type lRet(std::forward<tLH>(pLH));
        lRet-=pRH;
        return lRet;
      }

    template<typename tLH,typename tRH>
      typename std::decay<tLH>::type operator+(tLH &&pLH,tRH &&pRH)
      {
        typename std::decay<tLH>::type lRet(std::forward<tLH>(pLH));
        lRet+=pRH;
        return lRet;
      }

  }//namespace operators

  template <unsigned DIM>
    class CPoint : public operators::CDummy
  {
    public:
      CPoint()
      {
        mX.reserve(DIM);
        for(unsigned i=0;i<DIM;++i)
          mX.emplace_back(getRnd());
      }
      CPoint(const CPoint &pP): mX(pP.mX){}

      CPoint(const CPoint &&pP): mX(std::move(pP.mX)){}

      CPoint& operator= (const CPoint &pP) {mX=pP.mX; return *this;}

      CPoint& operator= (const CPoint &&pP)
      {
        mX = std::move(pP.mX);
        return *this;
      }

      double operator[] (unsigned pI) const{return mX[pI];}
      double& operator[] (unsigned pI) {return mX[pI];}

    private:
      std::vector<double> mX;
  };

  template <unsigned DIM>
    CPoint<DIM>& operator -= (CPoint<DIM> &pP0,const CPoint<DIM> &pP1)
    {
      for(unsigned i=0;i<DIM;++i)
        pP0[i]-=pP1[i]; 
      return pP0;
    }

  template <unsigned DIM>
    CPoint<DIM>& operator += (CPoint<DIM> &pP0,const CPoint<DIM> &pP1)
    {
      for(unsigned i=0;i<DIM;++i)
        pP0[i]+=pP1[i]; 
      return pP0;
    }

  template <unsigned DIM>
    CPoint<DIM> operator *(const double pS,const CPoint<DIM> &pP1)
    {
      CPoint<DIM> lResult;
      for(unsigned i=0;i<DIM;++i)
        lResult[i]=pS*pP1[i]; 
      return lResult;
    }

  template <unsigned DIM>
    CPoint<DIM> operator *(const double pS,const CPoint<DIM> &&pP1)
    {
      CPoint<DIM> &lResult = const_cast<CPoint<DIM>&>(pP1);
      for(unsigned i=0;i<DIM;++i)
        lResult[i]*=pS; 
      return lResult;
    }

  template <unsigned DIM>
    CPoint<DIM>& operator *=(CPoint<DIM> &pP1,const double pS)
    {
      for(unsigned i=0;i<DIM;++i)
        pP1[i]*=pS; 
      return pP1;
    }

  template <unsigned DIM>
    std::ostream& operator<< (std::ostream& pOS,const CPoint<DIM> &pP)
    {
      pOS << "(";
      for(unsigned i=0;i<DIM-1;++i)
        pOS << pP[i] << ",";
      pOS << pP[DIM-1] << ")";
      return pOS;
    }

}//namespace pso
#endif// __PSO_EUCLIDEAN_H__
