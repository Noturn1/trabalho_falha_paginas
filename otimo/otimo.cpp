#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;


int search(int key, int frame_items[], int frames_occupied){
    for(int i = 0; i < frames_occupied; i++){
        if(frame_items[i] == key){
            return 1; // retorna 1 se a página for encontrada
        }
    }
    return 0; // retorna 0 se a página não for encontrada
}

int predict(vector<int> pages, int frame_items[], int n_pages, int index, int frames_occupied){
    int res = -1, farthest = index;

    for(int i = 0; i < frames_occupied; i++){
        int j;
        for(j = index; j < n_pages; j++){
            if(frame_items[i] == pages[j]){
                if(j > farthest){
                    farthest = j;
                    res = i;
                }
                break;
            }
        }
        if(j == n_pages){
            return i; // retorna o índice do quadro que não será usado no futuro
        }
    }

    return (res == -1) ? 0 : res; // se todas as páginas forem usadas no futuro, retorna o primeiro quadro
}


void optimal_page(vector<int> pages, int n_pages, int frame_items[], int max_frames){
    //** ALGORITMO ÓTIMO **/

    int frames_occupied = 0; // contador de quadros ocupados
    int hits = 0; // contador de acertos

    for(int i = 0; i < n_pages; i++){
        if(search(pages[i], frame_items, frames_occupied)){
            hits++;
            continue;
        }


        if(frames_occupied < max_frames){
            frame_items[frames_occupied] = pages[i];
            frames_occupied++;
        }else{
            int index = predict(pages, frame_items, n_pages, i+1, frames_occupied);
            frame_items[index] = pages[i];
        }

        cout << "Hits: " << hits << endl;
        cout << "Misses: " << i + 1 - hits << endl;
        cout << "Hit ratio: " << (float)hits / (i + 1) << endl << endl;
    }
}

int main(){

    // abre o arquivo de reference string para leitura
    ifstream ref_string("../codigos_teste/multithreading/reference_string.txt", ios::in);
    
    string page_ref;
    vector<int> pages; // vetor para armazenar as páginas referenciadas
    int max_frames = 4; // número máximo de quadros de página
    int frame_items[max_frames]; // array para armazenar as páginas nos quadros

    if(ref_string.is_open()){
        cout << "Arquivo reference_string.txt aberto com sucesso!" << endl << endl;    
    }

    //lendo o arquivo de reference string linha por linha
    while(getline(ref_string, page_ref)){
        
        if(page_ref.empty()) continue; // pula linhas vazias
        
        //tranformando string para inteiro (interpreta como hexadecimal)
        int page = stoi(page_ref, nullptr, 16);

        pages.push_back(page); // adiciona a página referenciada ao vetor
    }


    optimal_page(pages, pages.size(), frame_items, max_frames);


    return 0;
}
