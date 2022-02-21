#pragma once

namespace Model
{
  template <typename T>
  class Containers
  {
  protected:
  /*
    virtual T *_alloc_(T *_dptr, unsigned long &_bufflen) { return _dptr = new T[_bufflen]; }

    virtual void _relocation_copy_(T *_dptr, T *temp, unsigned long &_bufflen)
    {
      for (unsigned long i = 0; i < _bufflen; i++)
        temp[i] = _dptr[i];
      delete[] _dptr;
      _dptr = temp;
    }

    virtual void _realloc_up_(T *_dptr, unsigned long &_dsize, unsigned long &_bufflen)
    {
      T *temp = new T[_bufflen + 0x01];
      _relocation_copy_(_dptr, temp, _bufflen);
      _bufflen += 0x01;
      _dsize += 0x01;
    }

    virtual void _realloc_down_(T *_dptr, unsigned long &_dsize, unsigned long &_bufflen)
    {
      T *temp = new T[_bufflen - 0x01];
      _relocation_copy_(_dptr, temp, _bufflen);
      if (_bufflen > 0x00)
        _bufflen -= 0x01;
      if (_dsize > 0x00)
        _dsize -= 0x01;
    }

    virtual void _shift_vector_left_(T *_dptr, unsigned long &_dsize, unsigned long cursor)
    {
      for (register unsigned long i = cursor; i < _dsize; i++)
        _dptr[i] = _dptr[i + 1];
    }

  protected:
    virtual size_t _bytes_(unsigned long &_bufflen) const { return sizeof(T) * _bufflen; }

    virtual unsigned long _size_(unsigned long &_dsize) const { return _dsize; }

    virtual bool _empty_(unsigned long &_dsize) const { return _dsize < 0x01 ? true : false; }

    virtual T _get_(T *_dptr, unsigned long pos) const { return _dptr[pos]; }

    virtual void _push_(T *_dptr, T _data, unsigned long &_dsize, unsigned long &_bufflen)
    {
      if (_dptr)
      {
        _dptr[_dsize] = _data;
        _realloc_up_(_dptr, _dsize, _bufflen);
      }
    }

    virtual void _pop_(T *_dptr, unsigned long &_dsize, unsigned long &_bufflen)
    {
      if (_dptr)
      {
        _shift_vector_left_(_dptr, _dsize, _dsize - 0x01);
        _realloc_down_(_dptr, _dsize, _bufflen);
      }
    }

    virtual void _reset_(T *_dptr, unsigned long &_dsize, unsigned long &_bufflen)
    {
      if (_dptr)
      {
        _dsize = 0x00;
        _bufflen = 0x01;
        delete[] _dptr;
        _alloc_(_dptr, _bufflen);
      }
    }
  */

  protected:
    // Capacity
    virtual size_t Bytes() const = 0;

    virtual unsigned long Size() const = 0;

    virtual bool Empty() const = 0;

    // Element Access
    virtual T First() const = 0;

    virtual T Last() const = 0;

    virtual T At(unsigned long pos) const = 0;

    // Modifiers
    virtual void Push(T data) = 0;

    virtual void Pop() = 0;

    virtual void Reset() = 0;
  };
}