#include <iostream>
#include <string>
#include <ctime>
#include <fstream>
#include <cstdlib>


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
void total_rand (int* a) {
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
void check_ene (enemy e[], std::string& f, int& num) {
    for(int check = 0; check < 5; check++) {
        if (e[check].flag == f) {
            num = check;
        }
    }
}
void save_game_pers (std::ofstream& save, person& save_pers) {
    int len = save_pers.name.length();
    save.write((char*)&len, sizeof(len));
    save.write(save_pers.name.c_str(), len);
    save.write((char*)&save_pers.hp, sizeof(save_pers.hp));
    save.write((char*)&save_pers.armor, sizeof(save_pers.armor));
    save.write((char*)&save_pers.attack, sizeof(save_pers.attack));
    save.write((char*)&save_pers.pers_x, sizeof(save_pers.pers_x));
    save.write((char*)&save_pers.pers_y, sizeof(save_pers.pers_y));
}
void save_game_enemy(std::ofstream& save, enemy& ene) {
    for (int s_e = 0; s_e < 5; s_e++) {
        int len_e = ene.flag.length();
        save.write((char *) &len_e, sizeof(len_e));
        save.write(ene.flag.c_str(), len_e);
        save.write((char*)&ene.e_name, sizeof(ene.e_name));
        save.write((char*)&ene.e_hp, sizeof(ene.e_hp));
        save.write((char*)&ene.e_armor, sizeof(ene.e_armor));
        save.write((char*)&ene.e_attack, sizeof(ene.e_attack));
        save.write((char*)&ene.ene_x, sizeof(ene.ene_x));
        save.write((char*)&ene.ene_y, sizeof(ene.ene_y));
    }
}
void load_game_pers (std::ifstream& load, person& load_pers) {
    int len;
    load.read((char*)&len, sizeof(len));
    load_pers.name.resize(len);
    load.read((char*)load_pers.name.c_str(), len);
    load.read((char*)&load_pers.hp, sizeof(load_pers.hp));
    load.read((char*)&load_pers.armor, sizeof(load_pers.armor));
    load.read((char*)&load_pers.attack, sizeof(load_pers.attack));
    load.read((char*)&load_pers.pers_x, sizeof(load_pers.pers_x));
    load.read((char*)&load_pers.pers_y, sizeof(load_pers.pers_y));
}
void load_games_enemy (std::ifstream& load, enemy& ene) {
    int len;
    load.read((char*)&len, sizeof(len));
    ene.flag.resize(len);
    load.read((char*)ene.flag.c_str(), len);
    load.read((char*)&ene.e_name, sizeof(ene.e_name));
    load.read((char*)&ene.e_hp, sizeof(ene.e_hp));
    load.read((char*)&ene.e_armor, sizeof(ene.e_armor));
    load.read((char*)&ene.e_attack, sizeof(ene.e_attack));
    load.read((char*)&ene.ene_x, sizeof(ene.ene_x));
    load.read((char*)&ene.ene_y, sizeof(ene.ene_y));

}
int main() {
    std::srand(std::time(nullptr));
    std::string map [20][20], game_logic;
    map_load(map);
    person pers;
    enemy ene[5];
    std::cout << "Start a new game, or download a walk-through?(new/load)";
    std::cin >> game_logic;
    if (game_logic == "new") {
        std::cout << "Let's create a character:\n";

        std::cout << "Enter a name:";
        std::cin >> pers.name;
        std::cout << "Enter the number of health points:\n";
        std::cin >> pers.hp;
        std::cout << "Enter the number of armor points:\n";
        std::cin >> pers.armor;
        std::cout << "Enter the number of attack points:\n";
        std::cin >> pers.attack;

        //Here we will collect enemy characters

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
    }
    /*else {
        //load games
    }*/

    //And now it's time to implement the game itself!

    for (int game = 0; game_logic != "Fin"; game++) {
        for (int game_x = 0; game_x < 20; game_x++) {
            for (int game_y = 0; game_y < 20; game_y++) {
                std::cout << map[game_x][game_y] << "   ";
            }
            std::cout << std::endl;
        }

        //The first move is up to the player.
        int num_ene;
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
                    ene[num_ene].flag = "Dead";
                }
            } else {
                map[pers.pers_x][pers.pers_y] = '.';
                map[pers.pers_x -= 1][pers.pers_y] = 'P';
            }
        }
        if (game_logic == "s") {
            if (map[pers.pers_x + 1][pers.pers_y] == "E") {
                std::string tempo_str = (std::to_string(pers.pers_x + 1) + std::to_string(pers.pers_y));
                check_ene(ene, tempo_str, num_ene);
                ene[num_ene].e_armor -= pers.attack;
                if (ene[num_ene].e_armor < 0) {
                    ene[num_ene].e_hp += ene[num_ene].e_armor;
                    ene[num_ene].e_armor = 0;
                }
                if (ene[num_ene].e_hp <= 0) {
                    map[pers.pers_x + 1][pers.pers_y] = '.';
                    std::cout << "Opponent number " << ene[num_ene].e_name << " killed!\n";
                    ene[num_ene].flag = "Dead";
                }
            } else {
                map[pers.pers_x][pers.pers_y] = '.';
                map[pers.pers_x += 1][pers.pers_y] = 'P';
            }
        }
        if (game_logic == "a") {
            if (map[pers.pers_x][pers.pers_y - 1] == "E") {
                std::string tempo_str = (std::to_string(pers.pers_x) + std::to_string(pers.pers_y - 1));
                check_ene(ene, tempo_str, num_ene);
                ene[num_ene].e_armor -= pers.attack;
                if (ene[num_ene].e_armor < 0) {
                    ene[num_ene].e_hp += ene[num_ene].e_armor;
                    ene[num_ene].e_armor = 0;
                }
                if (ene[num_ene].e_hp <= 0) {
                    map[pers.pers_x][pers.pers_y - 1] = '.';
                    std::cout << "Opponent number " << ene[num_ene].e_name << " killed!\n";
                    ene[num_ene].flag = "Dead";
                }
            } else {
            map[pers.pers_x][pers.pers_y] = '.';
            map[pers.pers_x][pers.pers_y -= 1] = 'P';
            }
        }
        if (game_logic == "d") {
            if (map[pers.pers_x][pers.pers_y + 1] == "E") {
                std::string tempo_str = (std::to_string(pers.pers_x) + std::to_string(pers.pers_y + 1));
                check_ene(ene, tempo_str, num_ene);
                ene[num_ene].e_armor -= pers.attack;
                if (ene[num_ene].e_armor < 0) {
                    ene[num_ene].e_hp += ene[num_ene].e_armor;
                    ene[num_ene].e_armor = 0;
                }
                if (ene[num_ene].e_hp <= 0) {
                    map[pers.pers_x][pers.pers_y + 1] = '.';
                    std::cout << "Opponent number " << ene[num_ene].e_name << " killed!\n";
                    ene[num_ene].flag = "Dead";
                }
            } else {
                map[pers.pers_x][pers.pers_y] = '.';
                map[pers.pers_x][pers.pers_y += 1] = 'P';
            }
        }
        // Now the enemies are walking
        for(int step_ene = 0; step_ene < 5; step_ene++) {
            switch (rand() % 4) {
                case 0:
                    if (ene[step_ene].ene_x < 19 && ene[step_ene].flag != "Dead" && map[ene[step_ene].ene_x + 1][ene[step_ene].ene_y] != "E") {
                        if (map[ene[step_ene].ene_x + 1][ene[step_ene].ene_y] == "P") {
                            pers.armor -= ene[step_ene].e_attack;
                            if (pers.armor < 0) {
                                pers.hp += pers.armor;
                                pers.armor = 0;
                            }
                            if (pers.hp <= 0) {
                                std::cout << "The player is defeated, the enemies have won!";
                                game_logic = "Fin";
                            }
                        } else {
                            map[ene[step_ene].ene_x][ene[step_ene].ene_y] = ".";
                            map[ene[step_ene].ene_x += 1][ene[step_ene].ene_y] = "E";
                            ene[step_ene].flag =
                                    std::to_string(ene[step_ene].ene_x) + std::to_string(ene[step_ene].ene_y);
                        }
                    }
                    break;
                case 1:
                    if (ene[step_ene].ene_y < 19 && ene[step_ene].flag != "Dead" && map[ene[step_ene].ene_x][ene[step_ene].ene_y + 1] != "E") {
                        if (map[ene[step_ene].ene_x][ene[step_ene].ene_y + 1] == "P") {
                            pers.armor -= ene[step_ene].e_attack;
                            if (pers.armor < 0) {
                                pers.hp += pers.armor;
                                pers.armor = 0;
                            }
                            if (pers.hp <= 0) {
                                std::cout << "The player is defeated, the enemies have won!";
                                game_logic = "Fin";
                            }
                        } else {
                            map[ene[step_ene].ene_x][ene[step_ene].ene_y] = ".";
                            map[ene[step_ene].ene_x][ene[step_ene].ene_y += 1] = "E";
                            ene[step_ene].flag =
                                    std::to_string(ene[step_ene].ene_x) + std::to_string(ene[step_ene].ene_y);
                        }
                    }
                    break;
                case 2:
                    if (ene[step_ene].ene_x > 0 && ene[step_ene].flag != "Dead" && map[ene[step_ene].ene_x - 1][ene[step_ene].ene_y] != "E") {
                        if (map[ene[step_ene].ene_x - 1][ene[step_ene].ene_y] == "P") {
                            pers.armor -= ene[step_ene].e_attack;
                            if (pers.armor < 0) {
                                pers.hp += pers.armor;
                                pers.armor = 0;
                            }
                            if (pers.hp <= 0) {
                                std::cout << "The player is defeated, the enemies have won!";
                                game_logic = "Fin";
                            }
                        } else {
                            map[ene[step_ene].ene_x][ene[step_ene].ene_y] = ".";
                            map[ene[step_ene].ene_x -= 1][ene[step_ene].ene_y] = "E";
                            ene[step_ene].flag =
                                    std::to_string(ene[step_ene].ene_x) + std::to_string(ene[step_ene].ene_y);

                        }
                    }
                    break;
                case 3:
                    if (ene[step_ene].ene_y > 0 && ene[step_ene].flag != "Dead" && map[ene[step_ene].ene_x][ene[step_ene].ene_y - 1] != "E") {
                        if (map[ene[step_ene].ene_x][ene[step_ene].ene_y - 1] == "P") {
                            pers.armor -= ene[step_ene].e_attack;
                            if (pers.armor < 0) {
                                pers.hp += pers.armor;
                                pers.armor = 0;
                            }
                            if (pers.hp <= 0) {
                                std::cout << "The player is defeated, the enemies have won!";
                                game_logic = "Fin";
                            }
                        } else {
                            map[ene[step_ene].ene_x][ene[step_ene].ene_y] = ".";
                            map[ene[step_ene].ene_x][ene[step_ene].ene_y -= 1] = "E";
                            ene[step_ene].flag =
                                    std::to_string(ene[step_ene].ene_x) + std::to_string(ene[step_ene].ene_y);
                        }
                    }
                    break;
                }
        }
        //Implementation of game saving.
        if (game_logic == "save") {
            std::ofstream save_ps;
            save_ps.open("Save_pers.bin", std::ios::binary);
            save_game_pers(save_ps, pers);
            save_ps.close();
            std::ofstream save_ene;
            save_ene.open("Save_enemy.bin", std::ios::binary);
            for(int i = 0; i < 5; i++) {
                save_game_enemy(save_ene, ene[i]);
            }
            save_ene.close();
        }
        //Implementation of game loading.
    }
    return 0;
}
/*
        std::cout << pers.hp << "\n";
        std::cout << pers.pers_x << "\n";
        std::cout << pers.pers_y << "\n";
        std::cout << std::endl;
        for (int ene_show = 0; ene_show < 5; ene_show++) {
            std::cout << ene[ene_show].e_name << "\n";
            std::cout << ene[ene_show].ene_x << "\n";
            std::cout << ene[ene_show].ene_y << "\n";
            std::cout << ene[ene_show].flag << "\n";
            std::cout << std::endl;
        }
        */