#include <iostream>
#include <string>
#include <ctime>
#include <fstream>
#include <cstdlib>


struct person {
    std::string name;
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
    int len_e = ene.flag.length();
    save.write((char*) &len_e, sizeof(len_e));
    save.write(ene.flag.c_str(), len_e);
    save.write((char*)&ene.e_name, sizeof(ene.e_name));
    save.write((char*)&ene.e_hp, sizeof(ene.e_hp));
    save.write((char*)&ene.e_armor, sizeof(ene.e_armor));
    save.write((char*)&ene.e_attack, sizeof(ene.e_attack));
    save.write((char*)&ene.ene_x, sizeof(ene.ene_x));
    save.write((char*)&ene.ene_y, sizeof(ene.ene_y));
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
    std::cout << "Let's create a character:\n";

    std::cout << "Enter a name:";
    std::cin >> pers.name;
    std::string name = pers.name;
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
                std::cout << "The " << name << " made a move on the coordinates x = " << pers.pers_x - 1 << " and y = " << pers.pers_y << " and he struck the enemy who was there " << pers.attack << " damage.\n";
                if(ene[num_ene].e_armor > 0) {
                    std::cout << "The enemy's armor withstood, but it remained " << ene[num_ene].e_armor << "\n";
                }
                if (ene[num_ene].e_armor < 0) {
                    ene[num_ene].e_hp += ene[num_ene].e_armor;
                    ene[num_ene].e_armor = 0;
                    std::cout << "The damage inflicted penetrated the enemy's armor and all fell on HP! Health is left " << ene[num_ene].e_hp << "\n";
                }
                if (ene[num_ene].e_hp <= 0) {
                    map[pers.pers_x - 1][pers.pers_y] = '.';
                    std::cout << "Opponent number " << ene[num_ene].e_name << " killed!\n";
                    ene[num_ene].flag = "Dead";
                }
            } else {
                map[pers.pers_x][pers.pers_y] = '.';
                map[pers.pers_x -= 1][pers.pers_y] = 'P';
                std::cout << "The " << name << " switched to the coordinates x = " << pers.pers_x << " and y = " << pers.pers_y << "\n";
            }
        }
        if (game_logic == "s") {
            if (map[pers.pers_x + 1][pers.pers_y] == "E") {
                std::string tempo_str = (std::to_string(pers.pers_x + 1) + std::to_string(pers.pers_y));
                check_ene(ene, tempo_str, num_ene);
                ene[num_ene].e_armor -= pers.attack;
                std::cout << "The " << name << " made a move on the coordinates x = " << pers.pers_x + 1 << " and y = " << pers.pers_y << " and he struck the enemy who was there " << pers.attack << " damage.\n";
                if(ene[num_ene].e_armor > 0) {
                    std::cout << "The enemy's armor withstood, but it remained " << ene[num_ene].e_armor << "\n";
                }
                if (ene[num_ene].e_armor < 0) {
                    ene[num_ene].e_hp += ene[num_ene].e_armor;
                    ene[num_ene].e_armor = 0;
                    std::cout << "The damage inflicted penetrated the enemy's armor and all fell on HP! Health is left " << ene[num_ene].e_hp << "\n";
                }
                if (ene[num_ene].e_hp <= 0) {
                    map[pers.pers_x + 1][pers.pers_y] = '.';
                    std::cout << "Opponent number " << ene[num_ene].e_name << " killed!\n";
                    ene[num_ene].flag = "Dead";
                }
            } else {
                map[pers.pers_x][pers.pers_y] = '.';
                map[pers.pers_x += 1][pers.pers_y] = 'P';
                std::cout << "The " << name << " switched to the coordinates x = " << pers.pers_x << " and y = " << pers.pers_y << "\n";
            }
        }
        if (game_logic == "a") {
            if (map[pers.pers_x][pers.pers_y - 1] == "E") {
                std::string tempo_str = (std::to_string(pers.pers_x) + std::to_string(pers.pers_y - 1));
                check_ene(ene, tempo_str, num_ene);
                ene[num_ene].e_armor -= pers.attack;
                std::cout << "The " << name << " made a move on the coordinates x = " << pers.pers_x << " and y = " << pers.pers_y - 1 << " and he struck the enemy who was there " << pers.attack << " damage.\n";
                if(ene[num_ene].e_armor > 0) {
                    std::cout << "The enemy's armor withstood, but it remained " << ene[num_ene].e_armor << "\n";
                }
                if (ene[num_ene].e_armor < 0) {
                    ene[num_ene].e_hp += ene[num_ene].e_armor;
                    ene[num_ene].e_armor = 0;
                    std::cout << "The damage inflicted penetrated the enemy's armor and all fell on HP! Health is left " << ene[num_ene].e_hp << "\n";
                }
                if (ene[num_ene].e_hp <= 0) {
                    map[pers.pers_x][pers.pers_y - 1] = '.';
                    std::cout << "Opponent number " << ene[num_ene].e_name << " killed!\n";
                    ene[num_ene].flag = "Dead";
                }
            } else {
            map[pers.pers_x][pers.pers_y] = '.';
            map[pers.pers_x][pers.pers_y -= 1] = 'P';
            std::cout << "The " << name << " switched to the coordinates x = " << pers.pers_x << " and y = " << pers.pers_y << "\n";
            }
        }
        if (game_logic == "d") {
            if (map[pers.pers_x][pers.pers_y + 1] == "E") {
                std::string tempo_str = (std::to_string(pers.pers_x) + std::to_string(pers.pers_y + 1));
                check_ene(ene, tempo_str, num_ene);
                ene[num_ene].e_armor -= pers.attack;
                std::cout << "The " << name << " made a move on the coordinates x = " << pers.pers_x << " and y = " << pers.pers_y + 1 << " and he struck the enemy who was there " << pers.attack << " damage.\n";
                if(ene[num_ene].e_armor > 0) {
                    std::cout << "The enemy's armor withstood, but it remained " << ene[num_ene].e_armor << "\n";
                }
                if (ene[num_ene].e_armor < 0) {
                    ene[num_ene].e_hp += ene[num_ene].e_armor;
                    ene[num_ene].e_armor = 0;
                    std::cout << "The damage inflicted penetrated the enemy's armor and all fell on HP! Health is left " << ene[num_ene].e_hp << "\n";
                }
                if (ene[num_ene].e_hp <= 0) {
                    map[pers.pers_x][pers.pers_y + 1] = '.';
                    std::cout << "Opponent number " << ene[num_ene].e_name << " killed!\n";
                    ene[num_ene].flag = "Dead";
                }
            } else {
                map[pers.pers_x][pers.pers_y] = '.';
                map[pers.pers_x][pers.pers_y += 1] = 'P';
                std::cout << "The " << name << " switched to the coordinates x = " << pers.pers_x << " and y = " << pers.pers_y << "\n";
            }
        }
        // Now the enemies are walking
        for(int step_ene = 0; step_ene < 5; step_ene++) {
            switch (rand() % 4) {
                case 0:
                    if (ene[step_ene].ene_x < 19 && ene[step_ene].flag != "Dead" && map[ene[step_ene].ene_x + 1][ene[step_ene].ene_y] != "E") {
                        if (map[ene[step_ene].ene_x + 1][ene[step_ene].ene_y] == "P") {
                            pers.armor -= ene[step_ene].e_attack;
                            std::cout << "Opponent number " << ene[step_ene].e_name << " switched to coordinates x = " << ene[step_ene].ene_x + 1 << " and y = " << ene[step_ene].ene_y << " and struck the player who was there " << ene[step_ene].e_attack << " damage!\n";
                            if (pers.armor > 0) {
                                std::cout << "The player's armor withstood the blow, but it remained " << pers.armor << "\n";
                            }
                            if (pers.armor < 0) {
                                pers.hp += pers.armor;
                                pers.armor = 0;
                                std::cout << "The player's armor could not withstand the blow, and all the damage came to HP! Health is left " << pers.hp << "\n";
                            }
                            if (pers.hp <= 0) {
                                std::cout << "The player is defeated, the enemies have won!\n";
                                game_logic = "Fin";
                            }
                        } else {
                            map[ene[step_ene].ene_x][ene[step_ene].ene_y] = ".";
                            map[ene[step_ene].ene_x += 1][ene[step_ene].ene_y] = "E";
                            ene[step_ene].flag =
                                    std::to_string(ene[step_ene].ene_x) + std::to_string(ene[step_ene].ene_y);
                            std::cout << "The enemy " << ene[step_ene].e_name << " switched to the coordinates x = " << ene[step_ene].ene_x << " and y = " << ene[step_ene].ene_y << "\n";
                        }
                    }
                    break;
                case 1:
                    if (ene[step_ene].ene_y < 19 && ene[step_ene].flag != "Dead" && map[ene[step_ene].ene_x][ene[step_ene].ene_y + 1] != "E") {
                        if (map[ene[step_ene].ene_x][ene[step_ene].ene_y + 1] == "P") {
                            pers.armor -= ene[step_ene].e_attack;
                            std::cout << "Opponent number " << ene[step_ene].e_name << " switched to coordinates x = " << ene[step_ene].ene_x << " and y = " << ene[step_ene].ene_y + 1 << " and struck the player who was there " << ene[step_ene].e_attack << " damage!\n";
                            if (pers.armor > 0) {
                                std::cout << "The player's armor withstood the blow, but it remained " << pers.armor << "\n";
                            }
                            if (pers.armor < 0) {
                                pers.hp += pers.armor;
                                pers.armor = 0;
                                std::cout << "The player's armor could not withstand the blow, and all the damage came to HP! Health is left " << pers.hp << "\n";
                            }
                            if (pers.hp <= 0) {
                                std::cout << "The player is defeated, the enemies have won!\n";
                                game_logic = "Fin";
                            }
                        } else {
                            map[ene[step_ene].ene_x][ene[step_ene].ene_y] = ".";
                            map[ene[step_ene].ene_x][ene[step_ene].ene_y += 1] = "E";
                            ene[step_ene].flag =
                                    std::to_string(ene[step_ene].ene_x) + std::to_string(ene[step_ene].ene_y);
                            std::cout << "The enemy " << ene[step_ene].e_name << " switched to the coordinates x = " << ene[step_ene].ene_x << " and y = " << ene[step_ene].ene_y << "\n";
                        }
                    }
                    break;
                case 2:
                    if (ene[step_ene].ene_x > 0 && ene[step_ene].flag != "Dead" && map[ene[step_ene].ene_x - 1][ene[step_ene].ene_y] != "E") {
                        if (map[ene[step_ene].ene_x - 1][ene[step_ene].ene_y] == "P") {
                            pers.armor -= ene[step_ene].e_attack;
                            std::cout << "Opponent number " << ene[step_ene].e_name << " switched to coordinates x = " << ene[step_ene].ene_x - 1 << " and y = " << ene[step_ene].ene_y << " and struck the player who was there " << ene[step_ene].e_attack << " damage!\n";
                            if (pers.armor > 0) {
                                std::cout << "The player's armor withstood the blow, but it remained " << pers.armor << "\n";
                            }
                            if (pers.armor < 0) {
                                pers.hp += pers.armor;
                                pers.armor = 0;
                                std::cout << "The player's armor could not withstand the blow, and all the damage came to HP! Health is left " << pers.hp << "\n";
                            }
                            if (pers.hp <= 0) {
                                std::cout << "The player is defeated, the enemies have won!\n";
                                game_logic = "Fin";
                            }
                        } else {
                            map[ene[step_ene].ene_x][ene[step_ene].ene_y] = ".";
                            map[ene[step_ene].ene_x -= 1][ene[step_ene].ene_y] = "E";
                            ene[step_ene].flag =
                                    std::to_string(ene[step_ene].ene_x) + std::to_string(ene[step_ene].ene_y);
                            std::cout << "The enemy " << ene[step_ene].e_name << " switched to the coordinates x = " << ene[step_ene].ene_x << " and y = " << ene[step_ene].ene_y << "\n";
                        }
                    }
                    break;
                case 3:
                    if (ene[step_ene].ene_y > 0 && ene[step_ene].flag != "Dead" && map[ene[step_ene].ene_x][ene[step_ene].ene_y - 1] != "E") {
                        if (map[ene[step_ene].ene_x][ene[step_ene].ene_y - 1] == "P") {
                            pers.armor -= ene[step_ene].e_attack;
                            std::cout << "Opponent number " << ene[step_ene].e_name << " switched to coordinates x = " << ene[step_ene].ene_x << " and y = " << ene[step_ene].ene_y - 1 << " and struck the player who was there " << ene[step_ene].e_attack << " damage!\n";
                            if (pers.armor > 0) {
                                std::cout << "The player's armor withstood the blow, but it remained " << pers.armor << "\n";
                            }
                            if (pers.armor < 0) {
                                pers.hp += pers.armor;
                                pers.armor = 0;
                                std::cout << "The player's armor could not withstand the blow, and all the damage came to HP! Health is left " << pers.hp << "\n";
                            }
                            if (pers.hp <= 0) {
                                std::cout << "The player is defeated, the enemies have won!\n";
                                game_logic = "Fin";
                            }
                        } else {
                            map[ene[step_ene].ene_x][ene[step_ene].ene_y] = ".";
                            map[ene[step_ene].ene_x][ene[step_ene].ene_y -= 1] = "E";
                            ene[step_ene].flag =
                                    std::to_string(ene[step_ene].ene_x) + std::to_string(ene[step_ene].ene_y);
                            std::cout << "The enemy " << ene[step_ene].e_name << " switched to the coordinates x = " << ene[step_ene].ene_x << " and y = " << ene[step_ene].ene_y << "\n";
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
        if (game_logic == "load") {
            std::ifstream l_person ("Save_pers.bin", std::ios::binary);
            std::ifstream l_enemy ("Save_enemy.bin", std::ios::binary);
            load_game_pers(l_person, pers);
            for (int ld = 0; ld < 5; ld++) {
                load_games_enemy(l_enemy, ene[ld]);
            }
            l_person.close(), l_enemy.close();
            map_load(map);
            map[pers.pers_x][pers.pers_y] = "P";
            for (int mp = 0; mp < 5; mp++) {
                if (ene[mp].flag != "Dead") {
                    map[ene[mp].ene_x][ene[mp].ene_y] = "E";
                    ene[mp].flag = std::to_string(ene[mp].ene_x) + std::to_string(ene[mp].ene_y);
                }
            }
        }
        //Check the presence of characters on the map, and if someone is not there, then we will determine the winner!
        int count_e = 0, count_p = 0;
        for (int check_map = 0; check_map < 20; check_map++) {
            for (int check_map2 = 0; check_map2 < 20; check_map2++) {
                if (map[check_map][check_map2] == "E") {
                    count_e++;
                }
                if (map[check_map][check_map2] == "P") {
                    count_p++;
                }
            }
        }
        if (count_e == 0) {
            std::cout << "Player win!!!";
            game_logic = "Fin";
        }
        else if (count_p == 0) {
            std::cout << "Player louse!!!";
            game_logic = "Fin";
        }

    }
    return 0;
}
