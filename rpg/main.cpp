#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <limits>

using namespace std;

struct Hero {
    string name;
    int hp_max;
    int hp;
    int attack;
    int xp;
};

void clear_screen() {
    #ifdef WINDOWS
    system("CLS");
    #else
    system("clear");
    #endif
}

void wait_to_continue() {
    cout << "Pressione ENTER para continuar..." << endl;
    cin.ignore();
    cin.get();
}

void status(Hero hero) {
    int hp = hero.hp < 0 ? 0 : hero.hp;
    cout << "-----------------------------" << endl << endl;
    cout << hero.name << ": " << "HP " << hp << "/" << hero.hp_max << " | XP " << hero.xp << " | ATK " << hero.attack << endl;
    cout << "-----------------------------" << endl << endl;
}

int chooseDoor() {
    clear_screen();

    cout << "Escolha a proxima porta (1, 2):" << endl;
    cout << "     ______            ______       " << endl;
    cout << "  ,-' ;  ! `-.       -' ;  ! `-.    " << endl;
    cout << " / :  !  :  . \    / :  !  :  . \   " << endl;
    cout << "|_ ;   __:  ;  |  |_ ;   __:  ;  |  " << endl;
    cout << ")| .  :)(.  !  |  )| .  :)(.  !  |  " << endl;
    cout << "|'    (##)  _  |  |'    (##)  _  |  " << endl;
    cout << "|  :  ;`'  (_) (  |  :  ;`'  (_) (  " << endl;
    cout << "|  :  :  .     |  |  :  :  .     |  " << endl;
    cout << ")_ !  ,  ;  ;  |  )_ !  ,  ;  ;  |  " << endl;
    cout << "|| .  .  :  :  |  || .  .  :  :  |  " << endl;
    cout << "|' .  |  :  .  |  |' .  |  :  .  |  " << endl;
    cout << "|___--;----.___|  |___--;----.___|  " << endl;

    int door;
    cin >> door;
    return door;
}

Hero receivePotion(Hero hero) {
    clear_screen();

    cout << "Voce achou uma pocao! Recuperou 40 HP." << endl << endl;
    cout << " __ " << endl;
    cout << " )( " << endl;
    cout << "(__)" << endl;

    if(hero.hp < hero.hp_max && hero.hp + 30 > hero.hp_max) {
        hero.hp = hero.hp_max;
    } else if(hero.hp < hero.hp_max) {
        hero.hp += 30;
    }

    status(hero);

    wait_to_continue();

    return hero;
}

bool died(Hero hero) {
    return hero.hp <= 0;
}

Hero fightMonster(Hero hero) {
    clear_screen();

    cout << "A wild Ogro appears! Ele te desafia para um par ou impar! Voce eh par!" << endl << endl;
    cout << "                       __,='`````'=/__                      " << endl;
    cout << "                      '//  (o) \(o) \ `'         _,-,       " << endl;
    cout << "                      //|     ,_)   (`\      ,-'`_,-\       " << endl;
    cout << "                    ,-~~~\  `'==='  /-,      \==```` \__    " << endl;
    cout << "                   /        `----'     `\     \       \/    " << endl;
    cout << "                ,-`                  ,   \  ,.-\       \    " << endl;
    cout << "               /      ,               \,-`\`_,-`\_,..--'\   " << endl;
    cout << "              ,`    ,/,              ,>,   )     \--`````\  " << endl;
    cout << "              (      `\`---'`  `-,-'`_,<   \      \_,.--'`  " << endl;
    cout << "               `.      `--. _,-'`_,-`  |    \               " << endl;
    cout << "                [`-.___   <`_,-'`------(    /               " << endl;
    cout << "                (`` _,-\   \ --`````````|--`                " << endl;
    cout << "                 >-`_,-`\,-` ,          |                   " << endl;
    cout << "               <`_,'     ,  /\          /                   " << endl;
    cout << "                `  \/\,-/ `/  \/`\_/V\_/                    " << endl;
    cout << "                   (  ._. )    ( .__. )                     " << endl;
    cout << "                   |      |    |      |                     " << endl;
    cout << "                    \,---_|    |_---./                      " << endl;
    cout << "                    ooOO(_)    (_)OOoo                      " << endl;

    Hero ogro = { "Ogro", 30 + hero.xp, 30 + hero.xp, 10 + hero.xp, 0 };

    while(true) {
        wait_to_continue();
        clear_screen();

        int result = rand() % 100;

        cout << "Resultado: " << result << "." << endl;

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
            cout << "==========" << endl;
            cout << "Game over!" << endl;
            cout << "==========" << endl;

            exit(0);
        } else if(died(ogro)) {
            cout << "===================================================" << endl;
            cout << "Voce venceu! Ganhou 5 XP e subiu 1 level (ATK + 2)!" << endl;
            cout << "===================================================" << endl;

            hero.attack += 2;
            hero.xp += 5;
            status(hero);
            break;
        }
    }

    wait_to_continue();

    return hero;
}

int main() {
    srand(time(NULL));

    cout << "=================" << endl;
    cout << "Final Fantasy -1" << endl;
    cout << "=================" << endl << endl;

    string name;
    cout << "Digite seu nome:" << endl;
    cin >> name;

    Hero hero = { name, 100, 100, 10, 0 };

    status(hero);

    clear_screen();

    cout << hero.name << " acorda em uma masmorra, e a sua frente existem 2 portas..." << endl;
    wait_to_continue();

    while(true) {
        int door = chooseDoor();
        door += rand();
        door = door % 3;

        if(door == 1) {
            hero = receivePotion(hero);
        } else if (door == 2) {
            hero = fightMonster(hero);
        } else {
            clear_screen();
            cout << "Nao tinha nada!" << endl;
            wait_to_continue();
        }
    }
}
