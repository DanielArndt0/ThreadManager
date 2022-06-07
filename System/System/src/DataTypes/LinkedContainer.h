#pragma once

template <typename T>
class LinkedContainer
{
private:
  struct element
  {
    T m_data;
    element *m_next_element = nullptr;
  };

private:
  unsigned long m_length;
  element *m_first;
  T m_err;

public:
  LinkedContainer()
  {
    m_first = nullptr;
    m_length = 0x00;
  }

  ~LinkedContainer() { cDelete(); }

protected:
  bool cIsEmpty() const { return m_first == nullptr || !m_length; }

  unsigned long cSize() const { return m_length; }

  bool cExist(T value) const { return cGetIndex(value) ? true : false; }

  T cError() const { return m_err; }

  T cGet(index key) const
  {
    if (cIsEmpty() || key >= m_length)
      return m_err;
    element *tmp = m_first;
    for (index i = 0; i < key; i++)
      tmp = tmp->m_next_element;
    return tmp->m_data;
  }

  index cGetIndex(T value) const
  {
    for (index i = 0; i < m_length; i++)
      if (value == cGet(i))
        return i;
    return 0;
  }

  element *cSearch(index key)
  {
    if (cIsEmpty() || key >= m_length)
      return nullptr;
    element *tmp = m_first;
    for (index i = 0; i < key; i++)
      tmp = tmp->m_next_element;
    return tmp;
  }

  T cPut(index key, T value)
  {
    element *tmp = cSearch(key);
    if (tmp == nullptr)
      return m_err;
    return (tmp->m_data = value);
  }

  T cPushFront(T value) { return cPush(0x00, value); }

  T cPushBack(T value) { return cPush(m_length, value); }

  T cPush(index key, T value)
  {
    if (key > m_length)
      return m_err;
    element *newElement = new element;
    newElement->m_data = value;
    if (cIsEmpty() || !key)
    {
      newElement->m_next_element = this->m_first;
      this->m_first = newElement;
      m_length++;
      return newElement->m_data;
    }
    element *prev = cSearch(key - 1);
    newElement->m_next_element = prev->m_next_element;
    prev->m_next_element = newElement;
    m_length++;
    return newElement->m_data;
  }

  T cPopFront() { return cPop(0x00); }

  T cPopBack() { return cPop(m_length - 1); }

  T cPop(index key)
  {
    if (cIsEmpty() || key >= m_length)
      return m_err;
    element *previous = nullptr;
    element *current = nullptr;
    T current_data;

    if (!key)
    {
      current = m_first;
      current_data = m_first->m_data;
      m_first = m_first->m_next_element;
      m_length--;
      delete current;
      return current_data;
    }
    previous = cSearch(key - 1);
    current = previous->m_next_element;
    current_data = current->m_data;
    previous->m_next_element = previous->m_next_element->m_next_element;
    m_length--;
    delete current;
    return current_data;
  }

  void cReset() { cDelete(); }

  void cDelete()
  {
    unsigned long total = m_length;
    for (index i = 0; i < total; i++)
      cPop((index)0x00);
    m_first = nullptr;
  }
};