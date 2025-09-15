#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() {
    
    // abre o arquivo de trace para leitura
    ifstream trace("./codigos_teste/multithreading/main.trace", ios::in);
    ofstream arq("./codigos_teste/multithreading/reference_string.txt", ios::out);

    string ref_string;
    char c;

    if (arq.is_open()) {
        cout << "Arquivo ref_string.txt aberto com sucesso!" << endl;    
    }
    if (trace.is_open()) {
        cout << "Arquivo main.trace aberto com sucesso!" << endl;    
    }

    // lendo o arquivo de trace linha por linha
    while (getline(trace, ref_string)) {

        if (ref_string.empty() || ref_string[0] == '=') continue; // pula linhas vazias ou que começam com '='

        int i = 0;
        
        c = ref_string[i];

        while(c == 'I' || c == 'S' || c == 'L' || c == 'M' || c == ' '){
            i++; // passa o próximo caractere
            c = ref_string[i];
        }

        for(; ref_string[i+3] != ','; i++){
            c = ref_string[i];
            arq << c; // escreve o caractere no arquivo ref_string.txt
        }

        arq << endl; 

        continue; // pula linhas que começam com '='
        
    }

    trace.close();
    arq.close();
    
    return 0;
}
