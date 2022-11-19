#include <iostream>
#include <string>
#include <ctime>
#include <vector>

struct person {
    std::string name;
    int hp;
    int armor;
    int attack;
    int pers_x;
    int pers_y;
};
struct enemy {
    int e_name = 0;
    int e_hp;
    int e_armor;
    int e_attack;
    int ene_x;
    int ene_y;
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
//char step_ene (struct st_ene) {

//};


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
    map[pers.pers_x][pers.pers_y] = 'P';
    for (int mp = 0; mp < 5; mp++) {
        map[ene[mp].ene_x][ene[mp].ene_y] = "E" + std::to_string(mp + 1);
    }

    //And now it's time to implement the game itself!
    std::string game_logic;
    for (int game = 0; game_logic != "Fin"; game++) {
        for (int game_x = 0; game_x < 20; game_x++) {
            for (int game_y = 0; game_y < 20; game_y++) {
                std::cout << map[game_x][game_y] << "  ";
            }
            std::cout << std::endl;
        }
        //The first move is up to the player.
        std::cout << "Make a move:(w,a,s,d)";
        std::cin >> game_logic;
        if (game_logic == "w") {
            map[pers.pers_x][pers.pers_y] = '.';
            pers.pers_x -= 1;
            map[pers.pers_x][pers.pers_y] = 'P';
        }
        if (game_logic == "s") {
            map[pers.pers_x][pers.pers_y] = '.';
            pers.pers_x += 1;
            map[pers.pers_x][pers.pers_y] = 'P';
        }
        if (game_logic == "a") {
            map[pers.pers_x][pers.pers_y] = '.';
            pers.pers_y -= 1;
            map[pers.pers_x][pers.pers_y] = 'P';
        }
        if (game_logic == "d") {
            map[pers.pers_x][pers.pers_y] = '.';
            pers.pers_y += 1;
            map[pers.pers_x][pers.pers_y] = 'P';
        }

    }
    return 0;
}
