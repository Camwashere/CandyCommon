#pragma once
#include <cstdint>
namespace Candy
{
  /**
   * @brief Unique 64-bit unsigned integer.
   * @note This is not a universally unique identifier (UUID) as it is not guaranteed to be unique across multiple machines. However, it is astronomically unlikely that two UUIDs will be the same.
   *
   */
  class UUID
  {
  private:
    std::uint64_t value;
  
  public:
    /**
     * @brief Construct a new UUID with a unique value
     *
     */
    UUID();
    UUID(std::uint64_t uuid);
    UUID(const UUID&)=default;
    
    operator std::uint64_t() const{return value;}
  };
}

namespace std {
  template <typename T> struct hash;
  
  template<>
  struct hash<Candy::UUID>
  {
    std::size_t operator()(const Candy::UUID& uuid) const
    {
      return (std::uint64_t)uuid;
    }
  };
  
}