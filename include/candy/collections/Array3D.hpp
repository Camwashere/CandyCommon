#pragma once
#include <cstdint>
#include <array>
namespace Candy::Collections
{
  /**
   * @brief A fixed size, 3-dimensional array.
   * @details Data is internally stored as a single, contiguous array.
   * The multidimensional subscript operator is used to access the data with the following formula: x + y * WIDTH + z * WIDTH*HEIGHT to access the element at (x, y, z).
   * Using singular arguments for the subscript operator accesses the data as if it were a single dimensional array.
   * This means that calling Array3D[x] will NOT return a second array at index x, but rather a single element at that index in the internal, 1D array.
   * @tparam T The generic data type the array holds
   * @tparam WIDTH The width of the array
   * @tparam HEIGHT The height of the array (By default is equal to the width, making it a square array)
   * @tparam DEPTH The depth of the array (By default is equal to the height, making it a cube array)
   */
  template<typename T, std::size_t WIDTH, std::size_t HEIGHT=WIDTH, std::size_t DEPTH=HEIGHT>
  class Array3D
  {
    static constexpr std::size_t WIDTH_TIMES_HEIGHT = WIDTH*HEIGHT;
    static constexpr std::size_t SIZE = WIDTH * HEIGHT * DEPTH;
    static constexpr std::size_t LAST_INDEX = SIZE - 1;
    static constexpr bool IS_SQUARE = WIDTH==HEIGHT && HEIGHT==DEPTH;
  
  private:
    std::array<T, SIZE> data;
  
  public:
    Array3D()=default;
    Array3D(const Array3D& other)=default;
    explicit Array3D(const std::array<T, SIZE>& arr) : data(arr){}
    ~Array3D()=default;
  
  public:
    inline T& operator[](std::size_t index)
    {
      return data[index];
    }
    inline const T& operator[](std::size_t index)const
    {
      return data[index];
    }
    inline T& operator[](std::size_t x, std::size_t y, std::size_t z)
    {
      return data[x + y * WIDTH + z * WIDTH_TIMES_HEIGHT];
    }
    inline const T& operator[](std::size_t x, std::size_t y, std::size_t z)const
    {
      return data[x + y * WIDTH + z * WIDTH_TIMES_HEIGHT];
    }
    
    bool operator==(const Array3D<T, WIDTH, HEIGHT, DEPTH>& other)const
    {
      return data == other.data;
    }
    bool operator!=(const Array3D<T, WIDTH, HEIGHT, DEPTH>& other)const
    {
      return data != other.data;
    }
    bool operator < (const Array3D<T, WIDTH, HEIGHT, DEPTH>& other)const
    {
      return data < other.data;
    }
    bool operator <= (const Array3D<T, WIDTH, HEIGHT, DEPTH>& other)const
    {
      return data <= other.data;
    }
    bool operator > (const Array3D<T, WIDTH, HEIGHT, DEPTH>& other)const
    {
      return data > other.data;
    }
    bool operator >= (const Array3D<T, WIDTH, HEIGHT, DEPTH>& other)const
    {
      return data >= other.data;
    }
    bool operator <=> (const Array3D<T, WIDTH, HEIGHT, DEPTH>& other)const
    {
      return data <=> other.data;
    }
    
    auto begin()const noexcept {return data.begin();}
    auto end()const noexcept {return data.end();}
    auto rbegin()const noexcept{return data.rbegin();}
    auto rend()const noexcept{return data.rend();}
    auto cbegin()const noexcept{return data.cbegin();}
    auto cend()const noexcept{return data.cend();}
    auto crbegin()const noexcept{return data.crbegin();}
    auto crend()const noexcept{return data.crend();}
  
  public:
    inline T& First(){return data[0];}
    inline const T& First()const{return data[0];}
    inline T& Last(){return data[LAST_INDEX];}
    inline const T& Last()const{return data[LAST_INDEX];}
    
    template<std::size_t INDEX>
    inline T& Get(){return data[INDEX];}
    
    template<std::size_t INDEX>
    inline const T& Get()const{return data[INDEX];}
    
    template<std::size_t X, std::size_t Y, std::size_t Z>
    inline T& Get(){return data[X + Y * WIDTH + Z * WIDTH_TIMES_HEIGHT];}
    
    template<std::size_t X, std::size_t Y, std::size_t Z>
    inline const T& Get()const{return data[X + Y * WIDTH + Z * WIDTH_TIMES_HEIGHT];}
    
    inline void Fill(const T& value){data.fill(value);}
    
    [[nodiscard]] inline bool IsEmpty()const{return data.empty();}
    
    /**
     * @brief Is the array square (WIDTH == HEIGHT == DEPTH) or not?
     * @return True if the array is square, false otherwise.
     */
    [[nodiscard]] inline bool IsSquare()const{return IS_SQUARE;}
    
    /**
     * @brief Convert the array to a std::array.
     * @details Internally, data is stored as a 1D std::array, this simply returns a copy of that array
     * @return The std::array
     */
    std::array<T, SIZE> ToStdArray()const{return data;}
    
    /**
     * @brief Get the raw data of the array
     * @return A pointer to the internal 1D array's internal data
     */
    auto Data()const{return data.data();}
    
    [[nodiscard]] inline std::size_t GetWidth()const{return WIDTH;}
    [[nodiscard]] inline std::size_t GetHeight()const{return HEIGHT;}
    [[nodiscard]] inline std::size_t GetDepth()const{return DEPTH;}
    [[nodiscard]] inline std::size_t GetWidthTimesHeight()const{return WIDTH_TIMES_HEIGHT;}
    
    /**
     * @brief Get the size of the array (WIDTH * HEIGHT * DEPTH)
     * @return The size of the internal 1D array
     */
    [[nodiscard]] inline std::size_t GetSize()const{return SIZE;}
    
    /**
     * @brief Get the last index of the array (SIZE - 1) where SIZE = WIDTH * HEIGHT * DEPTH
     * @return The last index (or back) of the internal 1D array
     */
    [[nodiscard]] inline std::size_t GetLastIndex()const{return LAST_INDEX;}
  };
}