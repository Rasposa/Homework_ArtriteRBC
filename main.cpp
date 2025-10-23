#include <iostream>
#include <regex>
#include "RBC.hpp"

int main() {

    /* lê a base de dados */
    RBC rbc("casosArtrite.txt");


    bool exit_program = false;
    do{

        /* interage com usuário */
        std::cout << "\n# # # # # MENU# # # # # #\n 1 - Mostrar tabela de casos\n 2 - Analizar um caso\n Escolha uma opcao: ";
        int opcao;

        switch (std::cin >> opcao, opcao) {
            case 1: { // mostrar tabela
                rbc.show_table();
                std::cin.get();
                break;
            }
            case 2: { // analisar caso
                std::string novo_caso;
                std::cout << "insira um caso separado por ';' (com id) \n";
                std::cin >> novo_caso;
                std::string diagnostico = rbc.do_diagnosis(novo_caso);

                std::cout << "\n\nVocê quer inserir esse caso no banco de dados? (s/n): ";
                char resposta;
                std::cin >> resposta;
                if (resposta == 's' || resposta == 'S') {

                    // Coloca o ID correto
                    std::regex re("^[^;]*;?");
                    
                    diagnostico = std::regex_replace(diagnostico, re, std::to_string(rbc.get_cases().size() + 1)+";");
                    
                    // Insere o caso
                    try{rbc.insert_case(diagnostico);} catch(...){
                        std::cout << "Erro ao inserir o caso!\n";
                        break;
                    }
                    std::cout << "\nCaso inserido com sucesso!\n";
                } else {
                    std::cout << "\nok.\n";
                }
                break;
            }
            default:
                std::cout << "Opcao invalida!\n";
                break;
        }

    }while(exit_program == false);

    return 0;
}