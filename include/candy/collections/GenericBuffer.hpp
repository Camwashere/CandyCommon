#pragma once
#include <vector>
#include <candy/base/Assert.hpp>
namespace Candy::Collections
{
  /**
   * @brief A generic buffer that can be used to store data of any type.
   * @details Internally, data is stored as a vector of chars. The buffer does not track the sizes/locations of unique data stored inside it. If tracking of the data is needed, that must be implemented externally
   */
  class GenericBuffer
  {
  private:
    std::vector<char> buffer;
    
  public:
    template<typename T>
    void Add(const T& value)
    {
      const char* start = reinterpret_cast<const char*>(std::addressof(value));
      buffer.insert(buffer.end(), start, start + sizeof(T));
    }
    
    void AddBuffer(const GenericBuffer& value)
    {
      buffer.insert(buffer.end(), value.buffer.begin(), value.buffer.end());
    }
    
    void Add(const char* data, size_t size)
    {
      CANDY_CORE_ASSERT(size > 0);
      buffer.insert(buffer.end(), data, data + size);
    }
    [[nodiscard]] const char* Data()const
    {
      return buffer.data();
    }
    char* Data()
    {
      return buffer.data();
    }
    
    [[nodiscard]] size_t Size()const
    {
      return buffer.size();
    }
  };
  
 
}