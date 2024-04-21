#include <iostream>
#include <windows.h>

using namespace std;

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
    int vitality; // warrior
    int mana; // mage
    int agility; // rogue
    int gold;

};

int main()
{
    SetConsoleOutputCP(CP_UTF8);

    int VýběrPostavy;
   
    player warrior;
    warrior.name = "Darius Ironfist";
    warrior.hp = 20;
    warrior.maxhp = 20;
    warrior.energie = 50;
    warrior.maxenergie = 50;
    warrior.gold = 5;
    warrior.vitality = 10;

    player mage;
    mage.name = "Ranni Shadowcaster";
    mage.hp = 15;
    mage.maxhp = 15;
    mage.energie = 20;
    mage.maxenergie = 25;
    mage.gold = 5;
    mage.mana = 30;

    player rogue;
    rogue.name = "Ezio Silentblade";
    rogue.hp = 10;
    rogue.maxhp = 10;
    rogue.energie = 25;
    rogue.maxenergie = 30;
    rogue.gold = 5;
    rogue.agility = 30;
    

    player hráč;

    cout << "Zdravím poutníku vyber si svou postavu:\n1. Warrior\n2. Mage\n3. Rogue\n";

    do
    {
    cin >> VýběrPostavy;

    switch (VýběrPostavy)
    {
    case 1:
        hráč = warrior;
        cout << "jméno: " << hráč.name << "\n";
        cout << "hp/max hp: " << hráč.hp << hráč.maxhp << "\n";
        break;
    
    case 2:
        hráč = mage;
        cout << "jméno: " << hráč.name << "\n";
        cout << "hp/max hp: " << hráč.hp << hráč.maxhp << "\n";
        break;

    case 3:
        hráč = rogue;
        cout << "jméno: " << hráč.name << "\n";
        cout << "hp/max hp: " << hráč.hp << hráč.maxhp << "\n";

        break;

    default:
        cout << "Neplatná volba, vyber si prosím znovu.\n";
        break;
    }
    }while (VýběrPostavy != (1 || 2 || 3));


}