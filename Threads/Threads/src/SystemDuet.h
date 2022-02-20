#pragma once

namespace System
{
  namespace Data
  {
    template <typename T1, typename T2>
    class Duet
    {
    public:
      Duet &operator=(Duet &data)
      {
        _copy_(data);
        return *this;
      }

    private:
      T1 __data1__;
      T2 __data2__;

    private:
      void _copy_(Duet &data)
      {
        this->setFirst(data.getFirst());
        this->setSecond(data.getSecond());
      }

    public:
      Duet() {}
      Duet(T1 data1, T2 data2) : __data1__(data1), __data2__(data2) {}
      Duet(Duet &data) { *this = data; }

      T1 &getFirst() { return __data1__; }
      void setFirst(T1 data) { __data1__ = data; }

      T2 &getSecond() { return __data2__; }
      void setSecond(T2 data) { __data2__ = data; }
    };
  }
}
/*
template <class _T1, class _T2>
inline pair<_T1, _T2> make_pair(T1 x, T2 y) { return pair<T1, T2>(x, y); }
*/