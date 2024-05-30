#include <iostream>
#include <vector>
#include <windows.h>
#include <cstdlib>
#include <algorithm>

using namespace std;

void vymazat()
{
    Sleep(2000);
    system("CLS");
}

class monster
{
public:
    string jméno;
    int damage;
    int životy;
    int xpReward;
    int goldReward;

    monster(string name, int dmg, int hp, int xp, int gold) : jméno(name), damage(dmg), životy(hp), xpReward(xp), goldReward(gold) {}

    void StatyMonster() const
    {
        cout << "\nJméno: " << jméno << "\n";
        cout << "Životy: " << životy << "\n";
        cout << "Damage: " << damage << "\n\n";
    }

    [[nodiscard]] bool IsAlive() const
    {
        return životy > 0;
    }

    void attack() const
    {
        cout << jméno << " útočí a způsobuje " << damage << " poškození!\n";
    }

    void takeDamage(int dmg)
    {
        životy -= dmg;
        if (životy < 0) {životy = 0;}
        cout << jméno << " dostává " << dmg << " poškození. Zbývající životy: " << životy << ".\n";
    }
};

class player
{
public:
    string name;
    int hp{};
    int maxhp{};
    int energie{};
    int maxenergie{};
    int level{};
    int zkušenosti{};
    int damage{};
    int gold{};
    string className;

    void StatyPlayer() const
    {
        cout << "jméno: " << name << "\n";
        cout << "hp/max hp: " << hp << "/" << maxhp << "\n";
        cout << "energie/max energie: " << energie << "/" << maxenergie << "\n";
        cout << "damage: " << damage << "\n";
        cout << "gold: " << gold << "\n";
    }

    [[nodiscard]] bool IsAlive() const
    {
        return hp > 0;
    }

    void gainExperience(int xp)
    {
        zkušenosti += xp;
        cout << "Získal jsi " << xp << " zkušeností.\n";
        Sleep(3000);
        levelUp();
    }

    void gainGold(int amount)
    {
        if (rand() % 2 == 0)
        {
            gold += amount;
            cout << "Získal jsi " << amount << " zlaťáků.\n";
        }
        else
        {
            cout << "Tentokrát jsi nezískal žádné zlaťáky.\n";
        }
    }

    void useAbility(int abilityIndex, auto &target) {
        if (className == "Warrior") {
            if (abilityIndex == 1) {
                bash(target);
            } else if (abilityIndex == 2) {
                heal();
            }
        } else if (className == "Mage") {
            if (abilityIndex == 1) {
                fireball(target);
            } else if (abilityIndex == 2) {
                heal();
            }
        } else if (className == "Rogue") {
            if (abilityIndex == 1) {
                backstab(target);
            } else if (abilityIndex == 2) {
                heal();
            }
        } else {
            cout << "Neplatná volba schopnosti.\n";
        }
    }

private:
    void levelUp()
    {
        while (zkušenosti >= level * 10)
        {
            zkušenosti -= level * 10;
            level++;
            maxhp += 10;
            hp = maxhp;
            maxenergie += 5;
            energie = maxenergie;
            damage += 5;
            cout << "Gratulujeme! Postoupil jsi na úroveň " << level << "!\n";
            cout << "Tvé statistiky byly vylepšeny.\n";
            vymazat();
        }
    }

     void bash(monster &target) {
        if (energie >= 10) {
            energie -= 10;
            int abilityDamage = damage + 5;
            cout << "Používáš Bash na " << target.jméno << " a způsobuješ " << abilityDamage << " poškození!\n";
            target.takeDamage(abilityDamage);
        } else {
            cout << "Nemáš dostatek energie pro použití Bash.\n";
        }
    }

    void heal() {
        if (energie >= 10) {
            energie -= 10;
            int healAmount = 20;
            hp += healAmount;
            if (hp > maxhp) hp = maxhp;
            cout << "Používáš Heal a obnovuješ " << healAmount << " HP!\n";
        } else {
            cout << "Nemáš dostatek energie pro použití Heal.\n";
        }
    }

    void fireball(monster &target) {
        if (energie >= 20) {
            energie -= 20;
            int abilityDamage = damage + 15;
            cout << "Používáš Fireball na " << target.jméno << " a způsobuješ " << abilityDamage << " poškození!\n";
            target.takeDamage(abilityDamage);
        } else {
            cout << "Nemáš dostatek energie pro použití Fireball.\n";
        }
    }

    void backstab(monster &target) {
        if (energie >= 15) {
            energie -= 15;
            int abilityDamage = damage + 20;
            cout << "Používáš Backstab na " << target.jméno << "a způsobuješ " << abilityDamage << " poškození!\n";
            target.takeDamage(abilityDamage);
        } else {
            cout << "Nemáš dostatek energie pro použití Backstab.\n";
        }
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
            } else
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
            } else
            {
                cout << "Nemáš dostatek zlaťáků na tento nákup.\n";
            }
            break;

        case 3:
            if (gold >= 10)
            {
                životy = maxživoty;
                cout << "Byl jsi vyléčen na maximum.\n";
            } else
            {
                cout << "Nemáš dostatek zlaťáků na tento nákup.\n";
            }
            break;

        case 4:
           if (gold >= 10)
            {
            energie = maxenergie;
            cout << "Tvá mana byla doplněna na maximum.\n";
            } else
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

void multifight(player &hráč, vector<monster> &monsters)
{
    while (hráč.IsAlive() && !monsters.empty())
    {
        cout << "\nKolo začíná!\n";
        cout << "Stav monster:\n";

        for (int i = 0; i < monsters.size(); i++)
        {
            cout << 1 + i << ": ";
            monsters[i].StatyMonster();
        }

        cout << "\nVyber si akci:\n1. Útok\n2. Použití schopnosti\n";
        int akce;
        cin >> akce;

        switch (akce) {
            case 1: {
                int targetIndex;

                cout << "Vyber si cíl útoku (1-" << monsters.size() << "): ";
                cin >> targetIndex;
                targetIndex--;

                if (targetIndex >= 0 && targetIndex < monsters.size()) {
                    monster& target = monsters[targetIndex];
                    cout << "Útočíš na " << target.jméno << " a způsobuješ " << hráč.damage << " poškození.\n";
                    target.takeDamage(hráč.damage);

                    if (!target.IsAlive()) {
                        if(target.životy <= 0) target.životy = 0;
                        cout << target.jméno << " byl poražen!\n";
                        vymazat();
                        hráč.gainExperience(target.xpReward);
                        hráč.gainGold(target.goldReward);
                    }
                } else {
                    cout << "Neplatný cíl.\n";
                }
                break;
            }
            case 2: {
                int abilityIndex;
                cout << "Vyber si schopnost \n1 - útočná schopnost\n2 - vyléčení\n";
                cin >> abilityIndex;
                if (abilityIndex == 1 || abilityIndex == 2) {
                    int targetIndex;

                    cout << "Vyber si cíl schopnosti (1-" << monsters.size() << "): ";

                    cin >> targetIndex;
                    targetIndex--;

                    if (targetIndex >= 0 && targetIndex < monsters.size())
                    {
                        monster &target = monsters[targetIndex];
                        hráč.useAbility(abilityIndex, target);

                        if (!target.IsAlive())
                        {
                            if(target.životy <= 0) target.životy = 0;
                            cout << target.jméno << " byl poražen!\n";

                            hráč.gainExperience(target.xpReward);
                            hráč.gainGold(target.goldReward);
                        }
                    } else {
                        cout << "Neplatný cíl. Trefil jsi vzduch, monstra se smějí.\n";
                    }
                } else {
                    cout << "Neplatná volba schopnosti. Udělal sis ostudu bojovníku.\n";
                }
                break;
            }
            default:
                cout << "Neplatná akce. Ztrácíš kolo.\n";
                break;
        }
        vymazat();
        for(auto &monster: monsters)
        {
            if (monster.IsAlive())
            {
                monster.attack();
                hráč.hp -= monster.damage;
                if (hráč.hp < 0) hráč.hp = 0;
                cout << "Zbývající životy hráče: " << hráč.hp << "\n";
                if (!hráč.IsAlive())
                {
                    cout << "Byl jsi poražen...\n";
                    Sleep(2000);
                    exit(0);
                }
            }
        }
        monsters.erase(remove_if(monsters.begin(), monsters.end(), [](monster &m) { return !m.IsAlive(); }), monsters.end());
    }

    if (hráč.IsAlive() && !monsters.empty())
    {
        cout << "Všechny monstra byly poraženy! Vyhrál jsi!\n";
    }

}

void miniBossFight()
{

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
    warrior.damage = 100;
    warrior.level = 1;
    warrior.zkušenosti = 0;
    warrior.className = "Warrior";

    player mage;
    mage.name = "Ranni Shadowcaster";
    mage.hp = 15;
    mage.maxhp = 15;
    mage.energie = 25;
    mage.maxenergie = 25;
    mage.gold = 5;
    mage.damage = 30;
    mage.level = 1;
    mage.zkušenosti = 0;
    mage.className = "Mage";

    player rogue;
    rogue.name = "Ezio Silentblade";
    rogue.hp = 10;
    rogue.maxhp = 10;
    rogue.energie = 30;
    rogue.maxenergie = 30;
    rogue.gold = 5;
    rogue.damage = 30;
    rogue.level = 1;
    rogue.zkušenosti = 0;
    rogue.className = "Rogue";

    player hráč;
    hráč.name = "";
    hráč.hp = 0;
    hráč.maxhp = 0;
    hráč.energie = 0;
    hráč.maxenergie = 0;
    hráč.gold = 0;
    hráč.damage = 0;
    hráč.level = 1;
    hráč.zkušenosti = 0;
    hráč.className = "";

    cout << "Zdravím poutníku! ";

    do
    {
        cout << "Vyber si svou postavu (1-3):\n";
        cout << "1. Warrior\n2. Mage\n3. Rogue\n";
        cin >> VýběrPostavy;

        switch (VýběrPostavy)
        {
        case 1:
            hráč = warrior;
            hráč.StatyPlayer();
            cout << "ability: \n- 1.Shield Bash\n- 2. Heal\n\n";
            break;

        case 2:
            hráč = mage;
            hráč.StatyPlayer();
            cout << "ability: \n- 1. Fireball\n- 2. Heal\n\n";
            break;

        case 3:
            hráč = rogue;
            hráč.StatyPlayer();
            cout << "ability: \n- 1. Backstab\n- 2. Heal\n\n";
            break;

            default:
                cout << "Špatná volba. Musíte 1-3.";
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
            vymazat();
        }

    } while (!potvrdit);

    vymazat();

    vector<monster> monsters = {
        monster("Goblin", 1, 30, 50, 10),
        monster("Orc", 1, 40, 70, 15),
        monster("Dragon", 1, 50, 100, 50)
    };

    multifight(hráč, monsters);
}
