#include <vector>
#include <iostream>
#include <functional>

template<class T>
struct GoldbachResult
{
    T val1;
    T val2;
    T val3;

    GoldbachResult(T inVal1, T inVal2, T inVal3)
    {
        val1 = inVal1;
        val2 = inVal2;
        val3 = inVal3;
    }

    void print()
    {
        std::cout << "[";
        std::cout << val1;
        std::cout << " + ";
        std::cout << val2;
        std::cout << " + ";
        std::cout << val3;
        std::cout << "]";

    }
};

bool isPrime(const int n)
{
    bool prime = true;

    for (int i = 2; i < n && prime; i++)
    {
        if (n % i == 0)
            prime = false;
    }

    return prime;

}

bool isPrimeSchoolMethod(const int n)
{
    if (n <= 1)  return false;
    if (n <= 3)  return true;

    if (n % 2 == 0 || n % 3 == 0) return false;

    for (int i = 5; i * i <= n; i = i + 6)
        if (n % i == 0 || n % (i + 2) == 0)
            return false;

    return true;

}

std::vector< GoldbachResult<int> > getResult(const int inValue, std::function<bool(int)> primeMethod = &isPrime)
{

    // Obtenemos los numeros primos
    std::vector<int> primos;
    for (int i = inValue; i > 0; i--)
    {
        if (primeMethod(i) && (i % 2 != 0))
            primos.push_back(i);
    }

    // Comprobamos las sumas
    std::vector< GoldbachResult<int> > result;
    for (size_t i = 0; i < primos.size(); i++)
    {
        for (size_t j = i; j < primos.size(); j++)
        {

            for (size_t k = j; k < primos.size(); k++)
            {
                if (primos[i] + primos[j] + primos[k] == inValue)
                {
                    result.push_back(GoldbachResult<int>(primos[j], primos[i], primos[k]));
                }
            }
            
        }
    }

    return result;
}


// Conjetura debil de Goldbach
// Todo número impar mayor que 5 puede escribirse como suma de 3 números primos impares.
int main()
{
    for (size_t j = 9; j < 100; j += 2)
    {        
        std::cout << "NUMERO " << j << ": ";
        //auto result = getResult(100);
        auto result = getResult(j, &isPrimeSchoolMethod);

        for (size_t i = 0; i < result.size(); i++)
        {
            std::cout << " ";
            result[i].print();

            if (i + 1 < result.size())
                std::cout << " - ";
        }

        std::cout << std::endl;

    }
    
    system("pause");

}
