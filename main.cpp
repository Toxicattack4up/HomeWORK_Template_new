#include "Arraytemplate.h"
#include <iostream>
#include <exception>

int main()
{
    try
    {
        IntegerArray<unsigned long> arr1(10);
        IntegerArray<unsigned long> arr2 = arr1;
        IntegerArray<unsigned long> arr3(std::move(arr1));

        arr2[0] = 1;
        arr2[4] = 2;
        std::cout << arr2[0] << " " << arr2[4] << std::endl;

        try
        {
            std::cout << arr2[10] << std::endl;
        }
        catch (const bad_range& e)
        {
            std::cerr << "Range error: " << e.what() << std::endl;
        }

        arr2.resize(5);
        arr2.resize(15);

        arr2.insert(2, 10);
        arr2.remove(3);
    }
    catch (const bad_length& e)
    {
        std::cerr << "Length error: " << e.what() << std::endl;
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
