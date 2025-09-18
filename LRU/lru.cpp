#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <list>

using namespace std;

// verifica se uma página já está nos quadros
bool isPageInFrames(int page, const vector<int>& frames) {
    for (int frame_page : frames) {
        if (frame_page == page) {
            return true;
        }
    }
    return false;
}

// algoritmo LRU
void lru_page_replacement(const vector<int>& pages, int max_frames) {
    // vetor que armazena as páginas que atualmente estão nos quadros de memória
    vector<int> frames;
    // lista para rastrear a ordem de uso (mais recentes = mais a ofinal)
    list<int> lru_list;
    int misses = 0;
    int hits = 0;

    for (int page : pages) {
        // se a página já está na memória (hit)
        if (isPageInFrames(page, frames)) {
            hits++;
            // move a página para o final da lista, marcando-a como a mais recentemente usada
            lru_list.remove(page);
            lru_list.push_back(page);
        } else {
            // se a página não está na memória (miss)
            misses++;
            // se ainda há espaço livre
            if (frames.size() < max_frames) {
                frames.push_back(page);
                lru_list.push_back(page);
            } else {
                // se não há espaço, remove a página menos recentemente usada
                // a página menos usada é a que está no início da lista
                int lru_page = lru_list.front();
                lru_list.pop_front();
                lru_list.push_back(page);

                // encontra a página a ser substituída e substitui
                for (size_t i = 0; i < frames.size(); ++i) {
                    if (frames[i] == lru_page) {
                        frames[i] = page;
                        break;
                    }
                }
            }
        }
    }

    cout << "Acessos: " << pages.size() << endl;
    cout << "Hits: " << hits << endl;
    cout << "Misses:: " << misses << endl;
    cout << "Hit Ratio: " << (double)hits / pages.size() << endl;
    cout << "Fault Ratio: " << (double)misses / pages.size() << endl << endl;
}

int main() {
    // abrindo arquivo de reference string para leitura
    ifstream ref_string("../codigos_teste/multithreading/reference_string.txt", ios::in);
    
    string page_ref_str;
    vector<int> pages;
    
    if(ref_string.is_open()){
        cout << "Arquivo reference_string.txt aberto com sucesso!" << endl << endl;    
    }

    // lendo arquivo de reference string linha por linha
    while (getline(ref_string, page_ref_str)) {
        if (page_ref_str.empty()) continue;
        
        // converte string para inteiro (interpretando como hexadecimal)
        try {
            int page = stoi(page_ref_str, nullptr, 16);
            pages.push_back(page);
        } catch (const std::exception& e) {
            cerr << "Erro ao converter página: " << page_ref_str << " - " << e.what() << endl;
        }
    }

    ref_string.close();

    // executa a simulação para diferentes tamanhos de quadros
    vector<int> frame_sizes = {4, 8, 16, 32, 64, 128};

    for (int size : frame_sizes) {
        lru_page_replacement(pages, size);
    }

    return 0;
}
