#include <iostream>
#include "RBC.hpp"

int main() {
    std::string novo_caso;
    RBC rbc("casosArtrite.txt");
    std::cout << "insira um caso separado por ;\n";
    std::cin >> novo_caso;
    rbc.do_diagnosis(novo_caso);

    return 0;
}