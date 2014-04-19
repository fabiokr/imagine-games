#include <stdlib.h>
#include <time.h>
#include <iostream>

using namespace std;

struct Hero {
    string name;
    int hp_max;
    int hp;
    int attack;
    int xp;
};

void status(Hero hero) {
    cout << hero.name << ": " << "HP " << hero.hp << "/" << hero.hp_max << " | XP " << hero.xp << " | ATK " << hero.attack << endl;
    cout << "-----------------------------" << endl << endl;
}

int chooseDoor() {
    cout << "Escolha a proxima porta (1, 2 ou 3):" << endl;
    int door;
    cin >> door;
    return door;
}

Hero receivePotion(Hero hero) {
    cout << "Voce achou uma pocao! Recuperou 40 HP." << endl << endl;

    cout << "/---\\" << endl;
    cout << "|~~~|" << endl;
    cout << "|   |" << endl;
    cout << "\\___/" << endl << endl;

    if(hero.hp < hero.hp_max && hero.hp + 20 > hero.hp_max) {
        hero.hp = hero.hp_max;
    } else if(hero.hp < hero.hp_max) {
        hero.hp += 40;
    }

    status(hero);

    return hero;
}

bool died(Hero hero) {
    return hero.hp <= 0;
}

Hero fightMonster(Hero hero) {
    cout << "A wild Ogro appears! Ele te desafia para um par ou impar! Voce eh par!" << endl << endl;;
    Hero ogro = { "Ogro", 30 + hero.xp, 30 + hero.xp, 10 + hero.xp, 0 };

    cout << "  O  " << endl;
    cout << "__|_/" << endl;
    cout << "  |  " << endl;
    cout << " / \\ " << endl << endl;

    while(true) {
        cout << "Digite um numero:" << endl;
        int number;
        cin >> number;

        int ogro_number = rand() % 11;
        int result = ogro_number + number;

        cout << "Ogro jogou " << ogro_number << "! Total " << result << "." << endl;

        if(result % 2 == 0) {
            cout << "Voce acertou! Ogrou tomou " << hero.attack << " de dano!" << endl;
            ogro.hp -= hero.attack;
            status(ogro);
        } else {
            cout << "Voce errou! Tomou " << ogro.attack << " de dano!" << endl;
            hero.hp -= ogro.attack;
            status(hero);
        }

        if(died(hero)) {
            cout << "Game over!" << endl;
            exit(0);
        } else if(died(ogro)) {
            cout << "Voce venceu! Ganhou 5 XP e subiu 1 level (ATK + 2)!" << endl;
            hero.attack += 2;
            hero.xp += 5;
            status(hero);
            break;
        }
    }

    return hero;
}

int main()
{
    srand(time(NULL));

    cout << "=================" << endl;
    cout << "Final Fantasy -1" << endl;
    cout << "=================" << endl << endl;

    string name;
    cout << "Digite seu nome:" << endl;
    cin >> name;

    Hero hero = { name, 100, 100, 10, 0 };

    status(hero);

    cout << hero.name << " acorda em uma masmorra, e a sua frente existem 3 portas..." << endl;

    while(true) {
        int door = chooseDoor();

        int r = rand() % 10;
        door = (r + door) % 3;

        if(door == 1) {
            hero = receivePotion(hero);
        } else if (door == 2) {
            hero = fightMonster(hero);
        } else {
            cout << "Nao tinha nada!" << endl;
            status(hero);
        }
    }
}
