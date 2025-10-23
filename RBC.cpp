#include "RBC.hpp"

#include <fstream>
#include <sstream>
#include <algorithm>
#include <map>


/// @brief Cria uma instância da classe RBC carregando casos de um arquivo.
/// @param filename 
RBC::RBC(std::string filename) {
  
  /* abre arquivo*/
  this->file.open(filename);
  if (!this->file.is_open()) {
    std::cerr << "Error opening file: " << filename << std::endl;
  }

  /* cria um caso para cada linha */
  std::string line;
  std::getline(this->file, line); // pula o cabeçalho
  while (std::getline(this->file, line)) {
    Case new_case(line);
    cases.push_back(new_case);
  }

  this->file.close();
}


/// @brief Mostra a tabela de casos carregados.
/// @return true se a operação for bem-sucedida.
bool RBC::show_table() {
  std::cout << "ID\tDL\tRC\tDC\tMOB\tDTS\tIL\tER\tTCSE\tART\tRM\tBUR\tTOF\tSIN\tATG\tNR\tHLA_B27\tDJ\tDIAGNÓSTICO\n";
  for (const Case c : cases) {
    std::cout << c.index << "\t" << c.dl << "\t" << c.rc << "\t" << c.dc << "\t" << c.mob << "\t"
              << c.dts << "\t" << c.il << "\t" << c.er << "\t" << c.tcse << "\t"
              << c.art << "\t" << c.rm << "\t" << c.bur << "\t" << c.tof << "\t"
              << c.sin << "\t" << c.atg << "\t" << c.nr << "\t" << c.hla_b27 << "\t"
              << c.dj << "\t\t" << c.diagnos << "\n";
  }
  return true;
}


/// @brief Insere um novo caso na base de casos.
/// @param line 
/// @return Caso inserido.
Case RBC::insert_case(std::string line) {
  Case new_case = Case(line);
  cases.push_back(new_case);

  this->file.open("casosArtrite.txt", std::ios::app);
  if (!this->file.is_open()) {
    std::cerr << "Error opening file for appending." << std::endl;
  }
  this->file << "\n" << line;
  this->file.close();
  
  return new_case;
}

/// @brief Insere um novo caso em uma nova linha no arquivo base
/// @param line 
/// @return uma string com o novo caso diagnosticado
std::string RBC::do_diagnosis(std::string line) {
  Case query_case = Case(line);
  std::vector<std::pair<int, float>> differences;
  std::cout << "\n\n#### PESOS ####\n";
  std::cout << "\tDL\tRC\tDC\tMOB\tDTS\tIL\tER\tTCSE\tART\tRM\tBUR\tTOF\tSIN\tATG\tNR\tHLA_B27\tDJ\n";
  std::cout << "\t" << "0.6\t" << "0.5\t" << "0.5\t" << "0.2\t"
            << "0.6\t" << "0.1\t" << "0.1\t" << "0.1\t"
            << "0.3\t" << "0.6\t" << "0.4\t" << "0.9\t"
            << "0.9\t" << "0.7\t" << "0.9\t"
            << "0.9\t" << "0.1\n";


  std::cout << "\n\n#### ENTRADA ####\n";
  std::cout << "\tDL\tRC\tDC\tMOB\tDTS\tIL\tER\tTCSE\tART\tRM\tBUR\tTOF\tSIN\tATG\tNR\tHLA_B27\tDJ\n";
  std::cout << "\t" << query_case.dl << "\t" << query_case.rc << "\t" << query_case.dc << "\t" << query_case.mob << "\t"
            << query_case.dts << "\t" << query_case.il << "\t" << query_case.er << "\t" << query_case.tcse << "\t"
            << query_case.art << "\t" << query_case.rm << "\t" << query_case.bur << "\t" << query_case.tof << "\t"
            << query_case.sin << "\t" << query_case.atg << "\t" << query_case.nr << "\t" << query_case.hla_b27 << "\t"
            << query_case.dj << "\n";


  std::cout << "\n\n#### LISTA DO MAIS PARECIDA PARA A MENOS ####\n";
  std::cout << "ID\tDL\tRC\tDC\tMOB\tDTS\tIL\tER\tTCSE\tART\tRM\tBUR\tTOF\tSIN\tATG\tNR\tHLA_B27\tDJ\tSIMILARIDADE\tDIAGNÓSTICO\n";

  float soma_dos_pesos = 0.6f + 0.5f + 0.5f + 0.2f + 0.6f + 0.1f + 0.1f + 0.1f + 0.3f + 0.6f + 0.4f + 0.9f + 0.9f + 0.7f + 0.9f + 0.9f + 0.1f;
  for(Case c : cases) {
    float diff = 0.0f;

    /* somatório do produto dos pessos pelas similaridades*/
    diff += std::abs(c.dl - query_case.dl)           * 0.6f;
    diff += std::abs(c.rc - query_case.rc)           * 0.5f;
    diff += std::abs(c.dc - query_case.dc)           * 0.5f;
    diff += std::abs(c.mob - query_case.mob)         * 0.2f;
    diff += std::abs(c.dts - query_case.dts)         * 0.6f;
    diff += std::abs(c.il - query_case.il)           * 0.1f;
    diff += std::abs(c.er - query_case.er)           * 0.1f;
    diff += std::abs(c.tcse - query_case.tcse)       * 0.1f;
    diff += std::abs(c.art - query_case.art)         * 0.3f;
    diff += std::abs(c.rm - query_case.rm)           * 0.6f;
    diff += std::abs(c.bur - query_case.bur)         * 0.4f;
    diff += std::abs(c.tof - query_case.tof)         * 0.9f;
    diff += std::abs(c.sin - query_case.sin)         * 0.9f;
    diff += std::abs(c.atg - query_case.atg)         * 0.7f;
    diff += std::abs(c.nr - query_case.nr)           * 0.9f;
    diff += std::abs(c.hla_b27 - query_case.hla_b27) * 0.9f;
    diff += std::abs(c.dj - query_case.dj)           * 0.1f;

    /* divisão pelo somatório dos pesos*/
    diff = (diff / soma_dos_pesos) * 100.0f;

    diff = 100.0f - diff; // traz a similaridade, não a diferença
    differences.push_back(std::pair(c.index, diff));
  }

  std::sort(differences.begin(), differences.end(),
   [](std::pair<int, float>& a, std::pair<int, float>& b) {
    return a.second > b.second;
  });


  /* imprime a lista ordenada pelo grau de similaridade */
  for (std::pair<int, float> l_case : differences) {
    Case c = cases[l_case.first - 1]; // -1 porque o index começa em 1
    std::cout << c.index << "\t" << c.dl << "\t" << c.rc << "\t" << c.dc << "\t" << c.mob << "\t"
              << c.dts << "\t" << c.il << "\t" << c.er << "\t" << c.tcse << "\t"
              << c.art << "\t" << c.rm << "\t" << c.bur << "\t" << c.tof << "\t"
              << c.sin << "\t" << c.atg << "\t" << c.nr << "\t" << c.hla_b27 << "\t"
              << c.dj << "\t" << l_case.second << "%     \t" << c.diagnos << "\n";
  }


  /* cria string do caso diagnosticado */
  return line + ";" + cases[differences[0].first - 1].diagnos;
}



/* objeto de dados para os casos */

float get_string_value(std::string& str) {
  if (str == "sim") {
    return 1.0f;
  }
  if (str == "nao") {
    return 0.0f;
  }
  if (str == "limitado") {
    return 1.0f;
  }
  if (str == "normal") {
    return 0.0f;
  }
  if(str == "ausente"){
    return 0.2f;
  }
  if(str == "leve"){
    return 0.4f;
  }
  if(str == "moderado"){
    return 0.6f;
  }
  if(str == "importante"){
    return 0.8f;
  }
  if(str == "muito_importante"){
    return 1.0f;
  }
  std::replace(str.begin(), str.end(), ',', '.');
  return std::stof(str);
}

Case::Case(std::string line) {

  line += ";;;;;;;;;;;;;;;;;";
  std::stringstream ss(line);
  std::string token;
  
  std::getline(ss, token, ';'); this->index   = stoi(token) ; // index
  std::getline(ss, token, ';'); this->dl      = get_string_value(token); // dl
  std::getline(ss, token, ';'); this->rc      = get_string_value(token); // rc
  std::getline(ss, token, ';'); this->dc      = get_string_value(token); // dc
  std::getline(ss, token, ';'); this->mob     = get_string_value(token); // mob
  std::getline(ss, token, ';'); this->dts     = get_string_value(token); // dts
  std::getline(ss, token, ';'); this->il      = get_string_value(token); // il
  std::getline(ss, token, ';'); this->er      = get_string_value(token); // er
  std::getline(ss, token, ';'); this->tcse    = get_string_value(token); // tcse
  std::getline(ss, token, ';'); this->art     = get_string_value(token); // art
  std::getline(ss, token, ';'); this->rm      = get_string_value(token); // tm
  std::getline(ss, token, ';'); this->bur     = get_string_value(token); // bur
  std::getline(ss, token, ';'); this->tof     = get_string_value(token); // tof
  std::getline(ss, token, ';'); this->sin     = get_string_value(token); // sin
  std::getline(ss, token, ';'); this->atg     = get_string_value(token); // atg
  std::getline(ss, token, ';'); this->nr      = get_string_value(token); // nr
  std::getline(ss, token, ';'); this->hla_b27 = get_string_value(token); // hla_b27
  std::getline(ss, token, ';'); this->dj      = get_string_value(token); // dj
  std::getline(ss, token, ';'); this->diagnos = token;                   // diagnostico
}
