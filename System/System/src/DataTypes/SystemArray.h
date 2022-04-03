#pragma once

namespace System
{
  namespace Data
  {
    template <typename T, long unsigned int N>
    class Array
    {
    public:
      void operator=(Array &cpy) { _copy_constructor_(cpy); }
      void operator=(Array &&move) { _move_constructor_(move); }
      T &operator[](unsigned long pos) { return __array__[pos]; }

    private:
      T __array__[N];

    private:
      void _copy_constructor_(Array &cpy)
      {
        for (long unsigned int i = 0; i < N; i++)
          *this->__array__[i] = cpy.__array__[i];
      }

      void _move_constructor_(Array &&move)
      {
        for (long unsigned int i = 0; i < N; i++)
          *this->__array__[i] = move.__array__[i];
      }

      void _fill_(T data)
      {
        for (long unsigned int i = 0; i < N; i++)
          __array__[i] = data;
      }

      void _swap_(Array<T, N> &swap)
      {
        Array<T, N> temp;
        temp.__array__ = this->__array__;
        this->__array__ = swap.__array__;
        swap.__array__ = temp;
      }

    public:
      Array() {}
      Array(Array &cpy) { *this = cpy; }
      Array(Array &&move) { *this = move; }

    public:
      /**
       * @brief Returns the size of the array in bytes.
       */
      size_t Bytes() const { return sizeof(T) * N; }

      /**
       * @brief Returns the size of the array.
       */
      unsigned long Size() const { return N; }

      /**
       * @return Returns the first content.
       */
      T First() const { return __array__[0]; }

      /**
       * @return Returns the last content.
       */
      T Last() const { return __array__[N - 1]; }

      /**
       * @param pos Array position.
       *
       * @return Returns data at the given position.
       */
      T At(unsigned long pos) const { return __array__[pos]; }

      /**
       * @brief Sets the data at the given position of the array.
       *
       * @param data Data to be defined.
       *
       * @param pos Array position.
       */
      void Set(T data, unsigned long pos) { __array__[pos] = data; }

      /**
       * @brief Fill array with value
       */
      void Fill(T data) { _fill_(data); }

      /**
       * @brief Swap contents.
       */
      void Swap(Array<T, N> &swap) { _swap_(swap); }
    };
  }
}