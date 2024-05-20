#include <iostream>
#include <windows.h>

using namespace std;

/* Poznámky:

vesnice(gold, hp, maxhp, energie, maxenergie); <-- implementovat

udělat monstra -> vymyslet fight

přidat ability
*/

class player
{
public:
    string name;
    int hp;
    int maxhp;
    int energie;
    int maxenergie;
    int level;
    int zkušenosti;
    int damage;
    int gold;

    void StatyPlayer()
    {
        cout << "jméno: " << name << "\n";
        cout << "hp/max hp: " << hp << "/" << maxhp << "\n";
        cout << "energie/max energie: " << energie << "/" << maxenergie << "\n";
        cout << "damage: " << damage << "\n";
        cout << "gold: " << gold << "\n";
    }

    bool IsAlive()
    {
        return hp > 0;
    }
};

class monster
{
    public:
    string jméno;
    int damage;
    int životy;

    void StatyMonster()
    {
        cout << "Jméno: " << jméno << "\n";
        cout << "Životy" << životy << "\n";
        cout << "Damage: " << damage << "\n";
    }

    bool IsAlive()
    {
        return životy > 0;
    }

    void attack()
    {
        cout << jméno << " útočí a způsobuje " << damage << " poškození!\n";
    }
};

void vesnice(int &gold, int &životy, int &maxživoty, int &energie, int &maxenergie)
{
    int volba;
    bool opakovat = true;

    do
    {
        cout << "Vítej ve vesnici!\n";
        cout << "Co si přeješ udělat?\n";
        cout << "1. Koupit zvýšení životů (+10 HP)\n";
        cout << "2. Koupit zvýšení many (+10 MP)\n";
        cout << "3. Vyléčit se na maximum\n";
        cout << "4. Doplnit manu na maximum\n";
        cout << "5. Nic, odejít z vesnice\n";

        cin >> volba;

        switch (volba)
        {
        case 1:
            if (gold >= 10)
            {
                gold -= 10;
                maxživoty += 10;
                cout << "Koupil jsi zvýšení životů (+10 HP).\n";
            }
            else
            {
                cout << "Nemáš dostatek zlaťáků na tento nákup.\n";
            }
            break;

        case 2:
            if (gold >= 10)
            {
                gold -= 10;
                maxenergie += 10;
                cout << "Koupil jsi zvýšení many (+10 MP).\n";
            }
            else
            {
                cout << "Nemáš dostatek zlaťáků na tento nákup.\n";
            }
            break;

        case 3:
            if (gold >= 10)
            {
                životy = maxživoty;
                cout << "Byl jsi vyléčen na maximum.\n";
            }
            else
            {
                cout << "Nemáš dostatek zlaťáků na tento nákup.\n";
            }
            break;

        case 4:
           if (gold >= 10)
            {
            energie = maxenergie;
            cout << "Tvá mana byla doplněna na maximum.\n";
            }
            else
            {
                cout << "Nemáš dostatek zlaťáků na tento nákup.\n";
            }
            break;

        case 5:
            cout << "Opouštíš vesnici.\n";
            opakovat = false;
            break;

        default:
            cout << "Neplatná volba, zkus to znovu.\n";
            break;
        }

    } while (opakovat);
}

void fight()
{

}

void multifight(player &hrac, vector<monster> &monsters)
{
    while (hrac.IsAlive() && !monsters.empty())
    {
        cout << "\nTvůj tah! Vyber si monstrum k útoku:\n";
        for (size_t i = 0; i < monsters.size(); ++i)
        {
            if (monsters[i].IsAlive())
            {
                cout << i + 1 << ". " << monsters[i].jméno << " (Životy: " << monsters[i].životy << ")\n";
            }
        }
    

        int výběr;
        cin >> výběr;
        výběr--;

        if (výběr >= 0 && výběr < monsters.size() && monsters[výběr].IsAlive())
        {
            cout << "Útočíš na " << monsters[výběr].jméno << " a způsobuješ " << hrac.damage << " poškození!\n";
            monsters[výběr].takeDamage(hrac.damage);
        }
        else
        {
            cout << "Neplatná volba monstra. Přicházíš o tah!\n";
        }
        
        for(auto &monster : monsters)
        {
            if (monster.IsAlive())
            {
                monster.attack();
                hrac.hp -= monster.damage;
                if (hrac.hp < 0) hrac.hp = 0;
                cout << "Zbývající životy hráče: " << hrac.hp << "\n";
                if (!hrac.IsAlive())
                {
                    cout << "Byl jsi poražen...\n";
                    return;
                }
            }
        }
    }


}

int main()
{
    SetConsoleOutputCP(CP_UTF8);

    int VýběrPostavy;
    char potvrzení;
    bool potvrdit;

    player warrior;
    warrior.name = "Darius Ironfist";
    warrior.hp = 20;
    warrior.maxhp = 20;
    warrior.energie = 50;
    warrior.maxenergie = 50;
    warrior.gold = 5;
    warrior.damage = 10;

    player mage;
    mage.name = "Ranni Shadowcaster";
    mage.hp = 15;
    mage.maxhp = 15;
    mage.energie = 20;
    mage.maxenergie = 25;
    mage.gold = 5;
    mage.damage = 30;

    player rogue;
    rogue.name = "Ezio Silentblade";
    rogue.hp = 10;
    rogue.maxhp = 10;
    rogue.energie = 25;
    rogue.maxenergie = 30;
    rogue.gold = 5;
    rogue.damage = 30;

    player hráč;

    cout << "Zdravím poutníku vyber si svou postavu:\n";

    do
    {
        cout << "1. Warrior\n2. Mage\n3. Rogue\n";
        cin >> VýběrPostavy;

        switch (VýběrPostavy)
        {
        case 1:
            hráč = warrior;
            cout << "jméno: " << hráč.name << "\n";
            cout << "hp/max hp: " << hráč.hp << "/" << hráč.maxhp << "\n";
            cout << "energie/max energie: " << hráč.energie << "/" << hráč.maxenergie << "\n";
            cout << "gold: " << hráč.gold << "\n";
            cout << "damage: " << hráč.damage << "\n";
            break;

        case 2:
            hráč = mage;
            cout << "jméno: " << hráč.name << "\n";
            cout << "hp/max hp: " << hráč.hp << "/" << hráč.maxhp << "\n";
            cout << "energie/max energie: " << hráč.energie << "/" << hráč.maxenergie << "\n";
            cout << "gold: " << hráč.gold << "\n";
            cout << "damage: " << hráč.damage << "\n";
            break;

        case 3:
            hráč = rogue;
            cout << "jméno: " << hráč.name << "\n";
            cout << "hp/max hp: " << hráč.hp << "/" << hráč.maxhp << "\n";
            cout << "energie/max energie: " << hráč.energie << "/" << hráč.maxenergie << "\n";
            cout << "gold: " << hráč.gold << "\n";
            cout << "damage: " << hráč.damage << "\n";
            break;
        }

        cout << "Potvrďte výběr postavy stiskem 'y', odmítněte klávesou 'n':\n";
        cin >> potvrzení;

        if (potvrzení == 'y' || potvrzení == 'Y')
        {
            potvrdit = true;
        }
        else
        {
            potvrdit = false;
        }

    } while (!potvrdit);


}
