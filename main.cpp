#include <iostream>
#include <thread>
#include <vector>
#include <functional>

// Создание динамического массива
int** create (int x, int y){
    int** array = new int*[x];
    for(int i = 0; i < x; ++i){
        array[i] = new int[y];
        for(int j = 0; j < y; ++j) {
            array[i][j] = rand() % 5;
        }
    }
    std:: cout << "Динамический массив создан." << std:: endl;
    return array;
}

// Вывод на экран динамического массива
void printInfo(int** array, int x, int y){
    for(int i = 0; i < x; ++i){
        for(int j = 0; j < y; ++j){
            std::cout << array[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

// Очищение памяти при удалении динамического массива
void remove(int** array, int x, int y){
    for(int i = 0; i < x; ++i){
        delete[] array[i];
    }
    delete[] array;
}

// Подсчитывание суммы для элементов строки

int sum(int* array, int y){
    int s = 0;
    for(int i = 0; i < y; ++i){
        s += array[i];
    }
    return s;
}

// Подсчитывание эллементов для всего массива массивов

int summa(int** array, int x, int y, int first, int& s){
    s = 0;
    for(int i = first; i < x; i += 4){
        s += sum(array[i], y);
    } 
}

int main(){
    int num;
    num = std::thread::hardware_concurrency();
    std::cout << num << std::endl;

    int x = 100;
    int y = 100;
    int** array = create(x, y);
    printInfo(array, x, y);   

    std::vector <std::thread> threadVec;
    std::vector <int> sumVec(num);

    for(int i = 0; i < num; ++i){
        std::thread thr([&array, x, y, &sumVec, i](){summa(array, x, y, i, sumVec[i]);});
        threadVec.push_back(std::move(thr));        
    }

    for(auto& t : threadVec){
        t.join();
    }

    int fSumma = 0;
    for(int i = 0; i < num; ++i){
        fSumma += sumVec[i];
    }

    std::cout << "Сумма элементов матрицы равна: " << fSumma << std::endl;

    for(int i = 0; i < num; ++i){
        std::cout << sumVec[i] << std::endl;
    }
    
    remove(array, x, y);

    return 0;
}

