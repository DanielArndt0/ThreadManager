#pragma once
#include "DataTypes/SystemDuet.h"
#include "DataTypes/SystemVector.h"

namespace System
{
  namespace Data
  {
    template <typename T1, typename T2>
    class Map
    {
    public:
      T2 &operator[](T1 key) { return _exist_or_create_(key); }

      Map &operator=(Map &map) { return _copy_(map); }

    private:
      Vector<Duet<T1, T2>> m_vector;
      T1 *m_t1_error_case;
      T2 *m_t2_error_case;

    private:
      Map &_copy_(Map &map)
      {
        _delete_();
        this->m_vector = map.m_vector;
        this->m_t1_error_case = new T1;
        this->m_t2_error_case = new T2;
        *this->m_t1_error_case = *map.m_t1_error_case;
        *this->m_t2_error_case = *map.m_t2_error_case;
        return *this;
      }

      bool _is_empty_() const { return m_vector.isEmpty(); }

      unsigned long _size_() const { return m_vector.Size(); }

      Duet<T1, T2> &_at_(unsigned long key) const { return m_vector.Get(key); }

      bool _exist_(T1 &key) const
      {
        for (unsigned long i = 0; i < m_vector.Size(); i++)
          if (m_vector.Get(i).getFirst() == key)
            return true;
        return false;
      }

      bool _exist_(T2 &value) const
      {
        for (unsigned long i = 0; i < m_vector.Size(); i++)
          if (m_vector.Get(i).getSecond() == value)
            return true;
        return false;
      }

      bool _insert_(Duet<T1, T2> map)
      {
        if (!_exist_(map.getFirst()))
          return m_vector.Push(map);
        return 0;
      }

      bool _remove_(T1 &key)
      {
        for (unsigned long i = 0; i < m_vector.Size(); i++)
          if (m_vector.Get(i).getFirst() == key)
            return m_vector.Pop(i);
        return false;
      }

      T2 &_find_(T1 &key)
      {
        for (unsigned long i = 0; i < m_vector.Size(); i++)
          if (m_vector.Get(i).getFirst() == key)
            return m_vector.Get(i).getSecond();
        return *m_t2_error_case;
      }

      T2 &_exist_or_create_(T1 key)
      {
        if (_exist_(key))
          return _find_(key);
        T2 tmp;
        m_vector.Push(Duet<T1, T2>::CreateDuet(key, tmp));
        return m_vector.Last().getSecond();
      }

      Map &_swap_(Map &map)
      {
        this->m_vector.Swap(map.m_vector);
        T1 t1_tmp = this->m_t1_error_case;
        T2 t2_tmp = this->m_t2_error_case;
        this->m_t1_error_case = map.m_t1_error_case;
        this->m_t2_error_case = map.m_t2_error_case;
        map.m_t1_error_case = t1_tmp;
        map.m_t2_error_case = t2_tmp;
        return *this;
      }

      bool _reset_()
      {
        delete m_t1_error_case;
        delete m_t2_error_case;
        m_t1_error_case = new T1;
        m_t2_error_case = new T2;
        return m_vector.Reset();
      }

      bool _delete_()
      {
        delete m_t1_error_case;
        delete m_t2_error_case;
        m_t1_error_case = nullptr;
        m_t2_error_case = nullptr;
        return m_vector.Delete();
      }

    public:
      Map()
      {
        m_t1_error_case = new T1;
        m_t2_error_case = new T2;
      }

      Map(Map &map) { _copy_(map); }

      ~Map()
      {
        m_vector.Delete();
        delete m_t1_error_case;
        delete m_t2_error_case;
      }

    public:
      bool isEmpty() const { return _is_empty_(); }

      unsigned long Size() const { return _size_(); }

      Duet<T1, T2> &At(unsigned long i) const { return _at_(i); }

      T2 getErrorValue() const { return m_t2_error_case; }

      bool Exist(T1 key) const { return _exist_(key); }

      bool Exist(T2 value) const { return _exist_(value); }

      bool Insert(Duet<T1, T2> map) { return _insert_(map); }

      bool Insert(T1 key, T2 value) { return _insert_(Duet<T1, T2>(key, value)); }

      bool Remove(T1 key) { return _remove_(key); }

      T2 &Find(T1 key) { return _find_(key); }

      Map &Swap(Map &map) { return _swap_(); }

      Map &Copy(Map &map) { return _copy_(map); }

      bool Reset() { return _reset_(); }

      bool Delete() { return _delete_(); }
    };
  }
}