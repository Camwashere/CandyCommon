#pragma once
#include <candy/base/Base.hpp>
#include <candy/math/Math.hpp>
namespace Candy::Noise
{
    class PerlinNoise
    {
    private:
        Math::Random<float> random;
        int period;
        int period2;
        int periodMinusOne;
        UniquePtr<int[]> perm;
    
    private:
        void BuildPermutations();
        static inline constexpr float Grad(int hash, float x)
        {
            return (hash & 1) == 0 ? x : -x;
        }
        
        static inline constexpr float Grad(int hash, float x, float y)
        {
            return ((hash & 1) == 0 ? x : -x) + ((hash & 2) == 0 ? y : -y);
        }
        
        static inline constexpr float Grad(int hash, float x, float y, float z)
        {
            int h = hash & 15;                      // CONVERT LO 4 BITS OF HASH CODE
            float u = h<8 ? x : y,                 // INTO 12 GRADIENT DIRECTIONS.
            v = h<4 ? y : h==12||h==14 ? x : z;
            return ((h&1) == 0 ? u : -u) + ((h&2) == 0 ? v : -v);
        }
    
    public:
        PerlinNoise();
        explicit PerlinNoise(long seed, int periodValue=256);
    
    
    public:
        [[nodiscard]] int GetPeriod()const;
        void Set(long seed, int periodValue);
        void SetPeriod(int periodValue);
        void SetSeed(long seed);
    
    
    public:
        [[nodiscard]] float Evaluate(float x)const;
        [[nodiscard]] float Evaluate(float x, float y)const;
        [[nodiscard]] float Evaluate(float x, float y, float z)const;
        
        [[nodiscard]] float Evaluate(const Math::Vector2& vec)const;
        [[nodiscard]] float Evaluate(const Math::Vector3& vec)const;
        
    };
}