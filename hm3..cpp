#include <iostream>
#include <vector>
#include <fstream>
#include <set>
int main(int argc, char *argv[]) {
    //передача имени файла с входными данными в кчестве аргумента командной строки
    std::string filename = argv[1];
    std::ifstream fin(filename);
    std::ofstream answer("answer.txt");
    std::string buf;
    // вспомогательный вектор количества вещей
    std::vector<int> number_of_clothes;
    //двумерный массив для вещей и их характеристи
    std::vector<std::vector<std::string>> set(4);

    std::getline(fin, buf);
    int d = std::stoi(buf);
    //заполнение вспомогательного массива
    while (std::getline(fin, buf)) {
        if (buf.empty()) {
            break;
        }
        number_of_clothes.emplace_back(std::stoi(buf));
    }
    int counter;
    //заполнение двумерного массива
    for (int j = 0; j < set.size(); ++j) {
        counter = number_of_clothes[j];
        while (counter > 0) {
            std::getline(fin, buf);
            set[j].emplace_back(buf);
            counter--;
        }
    }
    std::swap(set[2], set[3]);
    std::set<std::string> ans;
    std::string s;
    //перебор вариантов
    for (int i = 0; i < number_of_clothes[0]; i++) {
        int c = std::stoi(set[0][i]);
        if (c > d) {
            break;
        }
        for (int j = 0; j < number_of_clothes[1]; j++) {
            c = std::stoi(set[0][i]) + std::stoi(set[1][j]);
            if (c > d) {
                break;
            }
            for (int x = 0; x < number_of_clothes[3]; x++) {
                c = std::stoi(set[0][i]) + std::stoi(set[1][j]);
                c += std::stoi(set[2][x]);
                if (c > d) {
                    break;
                }

                for (int k = 0; k < number_of_clothes[2]; ++k) {
                    c = std::stoi(set[0][i]) + std::stoi(set[1][j]) + std::stoi(set[2][x]) ;
                    s = set[0][i] + "+" + set[1][j]  + "+" + set[2][x];;
                    if (s.contains('K')) {
                        ans.insert(s);
                        break;
                    }
                    if (c < d){
                        ans.insert(s);
                    }
                    c += std::stoi(set[3][k]);
                    if (c > d) {
                        ans.insert(s);
                        continue;
                    }
                    s += "+" + set[3][k];
                    ans.insert(s);
                }
            }
        }
    }
    for (auto &an : ans) {
        if ((std::count(an.begin(), an.end(), 'R') == 1
            && std::count(an.begin(), an.end(), 'G') == 1
            && std::count(an.begin(), an.end(), 'B') == 1)) {
            continue;
        }
        answer << an << "\n";
    }

}