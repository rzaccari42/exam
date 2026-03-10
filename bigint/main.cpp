#include <iostream>
#include <ostream>
#include "bigint.hpp"

// int	main() {
// 	bigint num1("42"), num2("10");
// 	num1 >>= 10;
// 	std::cout << num1 << std::endl;
// }

int main() {
    // Création de bigints
    bigint num1("242"), num2("10"), num3, num4(100);
    num3 = num2;
    const bigint numC(60);

    // Test des opérateurs arithmétiques
    std::cout << num1 << num2 << num3 << num4 << numC << std::endl;
    std::cout << "num1 + num2 = " << (num1 + num2) << std::endl;
    num3 = num1;
    num3 += num2;
    std::cout << "num3 += num2: " << num3 << std::endl;

    bigint num8("999"), num9("999");
    
    // Test des comparaisons
    std::cout << "num8 == num9: " << (num8 == num9) << std::endl;
    std::cout << "num8 != num9: " << (num8 != num9) << std::endl;
    std::cout << "num8 < num9: " << (num8 < num9) << std::endl;
    std::cout << "num8 <= num9: " << (num8 <= num9) << std::endl;
    std::cout << "num8 > num9: " << (num8 > num9) << std::endl;
    std::cout << "num8 >= num9: " << (num8 >= num9) << std::endl;

    bigint num10("4254");
    // Test des décalages avec entiers
    std::cout << "num1 << 2 = " << (num10 << 2) << std::endl;
    std::cout << "num1 >> 2 = " << (num10 >> 2) << std::endl;

    bigint num11("2");
    // Test des décalages avec bigint
    std::cout << "num1 << num5 = " << (num10 << num11) << std::endl;
    std::cout << "num1 >> num5 = " << (num10 >> num11) << std::endl;

    bigint num12("2");
    // Test des incrementations
    std::cout << "num12++ = " << (num12++) << std::endl;
    std::cout << "++num12 = " << (++num12) << std::endl;

    // Test des décalages avec bigint constant
    std::cout << "num1 << numC = " << (num1 << numC) << std::endl;
    std::cout << "num1 >> numC = " << (num1 >> numC) << std::endl;

    // Test des affectations combinées avec décalages
    num3 <<= 2;
    std::cout << "num3 <<= 2: " << num3 << std::endl;
    num3 >>= 1;
    std::cout << "num3 >>= 1: " << num3 << std::endl;

    // Test des affectations combinées avec bigint
    num3 <<= num2;
    std::cout << "num3 <<= num5: " << num3 << std::endl;
    num3 >>= num2;
    std::cout << "num3 >>= num5: " << num3 << std::endl;

    return 0;
}
