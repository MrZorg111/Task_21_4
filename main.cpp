#include <iostream>
#include <string>
#include <ctime>
#include <vector>

struct person {
    std::string name = " ";
    int hp = 0;
    int armor = 0;
    int attack = 0;
    int pers_x = 0;
    int pers_y = 0;
};
struct enemy {
    int e_name = 0;
    int e_hp = 0;
    int e_armor = 0;
    int e_attack = 0;
    int ene_x = 0;
    int ene_y = 0;
    std::string flag = " ";
};
void map_load (std::string m[][20]) {
    for (int i = 0; i < 20; i++) {
        for (int t = 0; t < 20; t++) {
            m[i][t] = '.';
        }
    }
}
int randomize (int& a, int b, int c) {
    a = rand() % b + c;
    return a;
}
void total_rand(int* a) {
    int num;
    bool good = true;
    for(int s = 0; s < 12;) {
        num = rand() % 20;
        if (s == 0) {
            a[0] = num;
            s++;
        }
        else {
            for (int c = 0; c < s; c++) {
                if (a[c] != num) {
                    good = true;
                }
                else {
                    good = false;
                    break;
                }
            }
            if (good) {
                a[s] = num;
                s++;
            }
        }
    }
}
void check_ene(struct std::vector<enemy>& e, std::string& f, int num) {
    for(int check = 0; check < 5; check++) {
        if (e[check].flag == f) {
            num += check;
        }
    }
}


int main() {
    std::srand(std::time(nullptr));
    std::string map [20][20];
    map_load(map);

    std::cout << "Let's create a character:\n";
    person pers;
    std::cout << "Enter a name:";
    std::cin >> pers.name;
    std::cout << "Enter the number of health points:\n";
    std::cin >> pers.hp;
    std::cout << "Enter the number of armor points:\n";
    std::cin >> pers.armor;
    std::cout << "Enter the number of attack points:\n";
    std::cin >> pers.attack;

    //Here we will collect enemy characters
    std::vector<enemy> ene(5);
    for (int i = 0; i < 5; i++) {
        ene[i].e_name += (i + 1);
        randomize(ene[i].e_hp, 101, 50);
        randomize(ene[i].e_armor, 51, 0);
        randomize(ene[i].e_attack, 16, 15);
    }

    //Here we will make the initial placement of the characters:
    int rand_coordinate[12];
    total_rand(rand_coordinate);
    pers.pers_x = rand_coordinate[0];
    pers.pers_y = rand_coordinate[1];
    for (int v = 2, e = 0; v < 12; v++) {
        ene[e].ene_x = rand_coordinate[v];
        v++, e++;
        ene[e].ene_y = rand_coordinate[v];
    }

    // Let's place the participants on the map:
    map[pers.pers_x][pers.pers_y] = "P";
    for (int mp = 0; mp < 5; mp++) {
        map[ene[mp].ene_x][ene[mp].ene_y] = "E";
        ene[mp].flag = std::to_string(ene[mp].ene_x) + std::to_string(ene[mp].ene_y);
    }

    //And now it's time to implement the game itself!
    std::string game_logic;
    for (int game = 0; game_logic != "Fin"; game++) {
        for (int game_x = 0; game_x < 20; game_x++) {
            for (int game_y = 0; game_y < 20; game_y++) {
                std::cout << map[game_x][game_y] << "   ";
            }
            std::cout << std::endl;
        }
        //The first move is up to the player.
        int num_ene = 0;
        std::cout << "Make a move:(w, a, s, d, save, load)";
        std::cin >> game_logic;
        if (game_logic == "w") {
            if (map[pers.pers_x - 1][pers.pers_y] == "E") {
                std::string tempo_str = (std::to_string(pers.pers_x - 1) + std::to_string(pers.pers_y));
                check_ene(ene, tempo_str, num_ene);
                ene[num_ene].e_armor -= pers.attack;
                if (ene[num_ene].e_armor < 0) {
                    ene[num_ene].e_hp += ene[num_ene].e_armor;
                    ene[num_ene].e_armor = 0;
                }
                if (ene[num_ene].e_hp <= 0) {
                    map[pers.pers_x - 1][pers.pers_y] = '.';
                    std::cout << "Opponent number " << ene[num_ene].e_name << " killed!\n";
                }
            } else {
                map[pers.pers_x][pers.pers_y] = '.';
                map[pers.pers_x -= 1][pers.pers_y] = 'P';
            }
        }
        if (game_logic == "s") {
            if (map[pers.pers_x + 1][pers.pers_y] == "E") {
                std::string tempo_str = (std::to_string(pers.pers_x - 1) + std::to_string(pers.pers_y));
                check_ene(ene, tempo_str, num_ene);
                ene[num_ene].e_armor -= pers.attack;
                if (ene[num_ene].e_armor < 0) {
                    ene[num_ene].e_hp += ene[num_ene].e_armor;
                    ene[num_ene].e_armor = 0;
                }
                if (ene[num_ene].e_hp <= 0) {
                    map[pers.pers_x + 1][pers.pers_y] = '.';
                    std::cout << "Opponent number " << ene[num_ene].e_name << " killed!\n";
                }
            } else {
                map[pers.pers_x][pers.pers_y] = '.';
                pers.pers_x += 1;
                map[pers.pers_x][pers.pers_y] = 'P';
            }
        }
        if (game_logic == "a") {
            if (map[pers.pers_x][pers.pers_y - 1] == "E") {
                std::string tempo_str = (std::to_string(pers.pers_x - 1) + std::to_string(pers.pers_y));
                check_ene(ene, tempo_str, num_ene);
                ene[num_ene].e_armor -= pers.attack;
                if (ene[num_ene].e_armor < 0) {
                    ene[num_ene].e_hp += ene[num_ene].e_armor;
                    ene[num_ene].e_armor = 0;
                }
                if (ene[num_ene].e_hp <= 0) {
                    map[pers.pers_x][pers.pers_y - 1] = '.';
                    std::cout << "Opponent number " << ene[num_ene].e_name << " killed!\n";
                }
            } else {
            map[pers.pers_x][pers.pers_y] = '.';
            pers.pers_y -= 1;
            map[pers.pers_x][pers.pers_y] = 'P';
            }
        }
        if (game_logic == "d") {
            if (map[pers.pers_x][pers.pers_y + 1] == "E") {
                std::string tempo_str = (std::to_string(pers.pers_x - 1) + std::to_string(pers.pers_y));
                check_ene(ene, tempo_str, num_ene);
                ene[num_ene].e_armor -= pers.attack;
                if (ene[num_ene].e_armor < 0) {
                    ene[num_ene].e_hp += ene[num_ene].e_armor;
                    ene[num_ene].e_armor = 0;
                }
                if (ene[num_ene].e_hp <= 0) {
                    map[pers.pers_x][pers.pers_y + 1] = '.';
                    std::cout << "Opponent number " << ene[num_ene].e_name << " killed!\n";
                }
            } else {
                map[pers.pers_x][pers.pers_y] = '.';
                pers.pers_y += 1;
                map[pers.pers_x][pers.pers_y] = 'P';
            }
        }
        for(int step_ene = 0; step_ene < 5; step_ene++) {
            switch (rand() % 4) {
                case 0:
                    map[ene[step_ene].ene_x][ene[step_ene].ene_y] = ".";
                    map[ene[step_ene].ene_x += 1][ene[step_ene].ene_y] = "E";
                    ene[step_ene].flag = std::to_string(ene[step_ene].ene_x) + std::to_string(ene[step_ene].ene_y);
                    break;
                case 1:
                    map[ene[step_ene].ene_x][ene[step_ene].ene_y] = ".";
                    map[ene[step_ene].ene_x][ene[step_ene].ene_y += 1] = "E";
                    ene[step_ene].flag = std::to_string(ene[step_ene].ene_x) + std::to_string(ene[step_ene].ene_y);
                    break;
                case 2:
                    map[ene[step_ene].ene_x][ene[step_ene].ene_y] = ".";
                    map[ene[step_ene].ene_x -= 1][ene[step_ene].ene_y] = "E";
                    ene[step_ene].flag = std::to_string(ene[step_ene].ene_x) + std::to_string(ene[step_ene].ene_y);
                    break;
                case 3:
                    map[ene[step_ene].ene_x][ene[step_ene].ene_y] = ".";
                    map[ene[step_ene].ene_x][ene[step_ene].ene_y -= 1] = "E";
                    ene[step_ene].flag = std::to_string(ene[step_ene].ene_x) + std::to_string(ene[step_ene].ene_y);
                    break;
                }
        }
    }
    return 0;
}
