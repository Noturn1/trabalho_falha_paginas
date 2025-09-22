#include <iostream> 
#include <vector>
#include <queue>

using namespace std 
    
// Função para saber se página está nos frames  
bool isPageInFrames(int page, const vector<int>& frames) {
    for (int frame_page : frames) {
        if (frame_page == page) {
            return true;
        }
    }
    return false;
}

// Lógica do FIFO 
void fifo_page_replacement(const vector<int>& pages, int max_frames){

    vector<int> frames;

    queue<int> fifo_queue;

    int hits = 0; 
    int misses = 0; 

    for (int page : pages){

        if (isPageInFrames(page, frames)){
            // Página está na memória (hit)
            hits++;

        } else {
            // Página não está na memória (miss)
            misses++;
        
            // Se tiver espaço livre
            if (frames.size() < max_frames){
                frames.push_back(page);
                fifo_queue.push(page); // Entra no final da fila

            // Se não tiver espaço, remove a página mais antiga 
            } else {
                int victim_page = fifo_queue.front() // A página na frente da lista 
                fifo_queue.pop(); // Remove da fila 
                fifo_queue.push(page); // Adiciona nova página no final da lista 

                for (size_t i = 0; i < frames.size(); i++){
                    if (frames[i] == victim_page){
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
        fifo_page_replacement(pages, size);
    }

    return 0;
}
