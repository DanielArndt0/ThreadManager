#pragma once

#define offset 1

typedef unsigned long index;
template <typename T, unsigned long pool>
class ContainerAllocator
{
protected:
  unsigned long m_buffer_length;
  unsigned long m_length;
  unsigned long m_pool_init;
  T *m_data_struct;

public:
  ContainerAllocator()
  {
    m_pool_init = pool;
    m_buffer_length = m_pool_init;
    m_length = 0x00;
    Alloc();
  }

  ~ContainerAllocator() { Del(); }

protected:
  void Alloc() { m_data_struct = new T[m_buffer_length]; }

  T *Realloc(T *temp)
  {
    for (index i = 0; i < m_buffer_length; i++)
      temp[i] = m_data_struct[i];
    delete[] m_data_struct;
    m_data_struct = temp;
    return m_data_struct;
  }

  void reallocUp()
  {
    if ((m_buffer_length - m_length) <= offset)
    {
      T *temp = new T[(m_buffer_length * 2)];
      Realloc(temp);
      m_buffer_length *= 2;
    }
    m_length += 0x01;
  }

  void reallocDown()
  {
    if (((m_buffer_length - m_length) > (m_buffer_length / 2) - offset) && m_length > (m_pool_init - offset))
    {
      T *temp = new T[(m_buffer_length /= 2)];
      Realloc(temp);
    }
    if (m_length > 0x00)
      m_length -= 0x01;
  }

  void shiftPush(unsigned long cursor)
  {
    for (index i = m_length; i > cursor; i--)
      m_data_struct[i] = m_data_struct[i - 1];
  }

  void shiftPop(unsigned long cursor)
  {
    for (index i = cursor; i < m_length; i++)
      m_data_struct[i] = m_data_struct[i + 1];
  }

  void Del()
  {
    if (this->m_data_struct)
    {
      this->m_buffer_length = this->m_pool_init;
      this->m_length = 0x00;
      delete[] this->m_data_struct;
    }
  }
};