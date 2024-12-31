#include <iostream>
#include <vector>
#include <fstream>
#include <chrono>

using namespace std;
using namespace chrono;

// Função para ler o arquivo e preencher o vetor
template <typename T>
void readFileToVector(const string &filename, vector<T> &vec) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Erro ao abrir o arquivo: " << filename << endl;
        exit(EXIT_FAILURE);
    }

    T value;
    while (file >> value) {
        vec.push_back(value);
    }

    file.close();
}

// Algoritmo SelectionSort
template <typename T>
void selectionSort(vector<T> &vec) {
    size_t n = vec.size();
    for (size_t i = 0; i < n - 1; ++i) {
        size_t minIdx = i;
        for (size_t j = i + 1; j < n; ++j) {
            if (vec[j] < vec[minIdx]) {
                minIdx = j;
            }
        }
        swap(vec[i], vec[minIdx]);
    }
}

// Algoritmo InsertionSort
template <typename T>
void insertionSort(vector<T> &vec) {
    size_t n = vec.size();
    for (size_t i = 1; i < n; ++i) {
        T key = vec[i];
        size_t j = i - 1;
        while (j < n && vec[j] > key) {
            vec[j + 1] = vec[j];
            if (j == 0) break;
            --j;
        }
        if (j < n && vec[j] <= key) vec[j + 1] = key;
    }
}

// Função para medir o tempo de execução de um algoritmo
template <typename T, typename Func>
long long measureExecutionTime(Func sortFunc, vector<T> vec) {
    auto start = high_resolution_clock::now();
    sortFunc(vec);
    auto stop = high_resolution_clock::now();
    return duration_cast<microseconds>(stop - start).count();
}

int main() {
    // Arquivo de teste
    string filename = "input.txt";
    vector<int> vec;

    // Ler dados do arquivo
    readFileToVector(filename, vec);

    // Fazer cópias do vetor original para os dois algoritmos
    vector<int> vecSelection = vec;
    vector<int> vecInsertion = vec;

    // Medir tempo de execução do SelectionSort
    long long timeSelection = measureExecutionTime(selectionSort<int>, vecSelection);

    // Medir tempo de execução do InsertionSort
    long long timeInsertion = measureExecutionTime(insertionSort<int>, vecInsertion);

    // Exibir resultados
    cout << "Tempo de execução (SelectionSort): " << timeSelection << " microsegundos" << endl;
    cout << "Tempo de execução (InsertionSort): " << timeInsertion << " microsegundos" << endl;

    // Comparar os tempos
    if (timeSelection < timeInsertion) {
        cout << "SelectionSort foi mais rápido." << endl;
    } else if (timeInsertion < timeSelection) {
        cout << "InsertionSort foi mais rápido." << endl;
    } else {
        cout << "Ambos os algoritmos tiveram o mesmo tempo de execução." << endl;
    }

    return 0;
}
