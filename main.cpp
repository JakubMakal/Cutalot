#include <iostream>
#include <vector>
#include <cmath>
#include <windows.h>
#include <cstdlib>
#include <algorithm>

using namespace std;

void vymazat()
{
    Sleep(3000);
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

    void staty() const
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

class miniboss : public monster {
public:
    miniboss(string name, int dmg, int hp, int xp, int gold) : monster(name, dmg, hp, xp, gold) {}
};

class cutalot : public monster {
public:
    int turnCount;
    int leftHandDamage;
    int rightHandDamage;

    cutalot(string name, int hp, int xp, int gold) : monster(name, 0, hp, xp, gold), turnCount(0), leftHandDamage(1), rightHandDamage(2) {}

    void attack(auto &player)
    {
        if (turnCount % 10 == 0)
        {
            cout << jméno << " útočí oběma rukama naráz" << endl;
            player.hp -= player.hp / 2;
        }else if (turnCount % 2 == 1)
        {
            cout << jméno << " útočí levou rukou" << endl;
            player.hp -= leftHandDamage;
            životy += leftHandDamage / 6;
            leftHandDamage += 2;
        } else {
            cout << jméno << " útočí pravou rukou" << endl;
            player.hp -= rightHandDamage;
            životy += rightHandDamage / 4;
            rightHandDamage += 2;
        }

        turnCount++;

        cout << "Cutalot způsobuje " << damage << " poškození.\n";
        player.hp -= damage;

        if (turnCount % 2 == 1)
        {
            životy += round(damage / 6);
        } else {
            životy += round(damage / 4);
        }
        if (životy > 600) životy = 600;
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
    int healAmount{};
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
            healAmount += 3;
            cout << "Gratulujeme! Postoupil jsi na úroveň " << level << "!\n";
            cout << "Tvé statistiky byly vylepšeny.\n";
            vymazat();
        }
    }

     void bash(monster &target) {
        if (energie >= 10) {
            energie -= 10;
            int abilityDamage = round(damage * 1.5);
            cout << "Používáš Bash na " << target.jméno << " a způsobuješ " << abilityDamage << " poškození!\n";
            target.takeDamage(abilityDamage);
        } else {
            cout << "Nemáš dostatek energie pro použití Bash.\n";
        }
    }

    void heal() {
        if (energie >= 10) {
            energie -= 10;
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
            int abilityDamage = round(damage * 1.8);
            cout << "Používáš Fireball na " << target.jméno << " a způsobuješ " << abilityDamage << " poškození!\n";
            target.takeDamage(abilityDamage);
        } else {
            cout << "Nemáš dostatek energie pro použití Fireball.\n";
        }
    }

    void backstab(monster &target) {
        if (energie >= 15) {
            energie -= 15;
            int abilityDamage = round(damage * 2.1);
            cout << "Používáš Backstab na " << target.jméno << "a způsobuješ " << abilityDamage << " poškození!\n";
            target.takeDamage(abilityDamage);
        } else {
            cout << "Nemáš dostatek energie pro použití Backstab.\n";
        }
    }
};

void vesnice(player &hráč) {
    int volba;
    bool opakovat = true;
    srand(time(nullptr));

    do {
        cout << "--------------------------------------\n";
        cout << "Vítej ve vesnici!\n";
        cout << "Co si přeješ udělat?\n";
        cout << "1. Mluvit s obchodníkem\n";
        cout << "2. Prozkoumat vesnici\n";
        cout << "3. Odejd z vesnice\n";
        cout << "--------------------------------------\n";

        cin >> volba;
        vymazat();

        switch (volba) {
            case 1:
                cout << "Vaše staty:\n";
                hráč.StatyPlayer();
                cout << "Obchodník: \"Zdravím tě, dobrodruhu! Co ti mohu nabídnout?\"\n";
                cout << "1. Zvýšení životů (+10 HP) - 10 zlaťáků\n";
                cout << "2. Zvýšení many (+10 MP) - 10 zlaťáků\n";
                cout << "3. Vyléčení na maximum - 10 zlaťáků\n";
                cout << "4. Doplnění many na maximum - 10 zlaťáků\n";
                cout << "5. Koupit zbraň (+5 damage) - 30 zlaťáků\n";
                cout << "6. Zpět\n";
                int obchodnikVolba;
                cin >> obchodnikVolba;
                vymazat();

                switch (obchodnikVolba) {
                    case 1:
                        if (hráč.gold >= 10) {
                            hráč.gold -= 10;
                            hráč.maxhp += 10;
                            cout << "Koupil jsi zvýšení životů (+10 HP).\n";
                        } else {
                            cout << "Nemáš dostatek zlaťáků na tento nákup.\n";
                        }
                        break;
                    case 2:
                        if (hráč.gold >= 10) {
                            hráč.gold -= 10;
                            hráč.maxenergie += 10;
                            cout << "Koupil jsi zvýšení many (+10 MP).\n";
                        } else {
                            cout << "Nemáš dostatek zlaťáků na tento nákup.\n";
                        }
                        break;
                    case 3:
                        if (hráč.gold >= 10) {
                            hráč.gold -= 10;
                            hráč.hp = hráč.maxhp;
                            cout << "Byl jsi vyléčen na maximum.\n";
                        } else {
                            cout << "Nemáš dostatek zlaťáků na tento nákup.\n";
                        }
                        break;
                    case 4:
                        if (hráč.gold >= 10) {
                            hráč.gold -= 10;
                            hráč.energie = hráč.maxenergie;
                            cout << "Tvá mana byla doplněna na maximum.\n";
                        } else {
                            cout << "Nemáš dostatek zlaťáků na tento nákup.\n";
                        }
                        break;
                    case 5:
                        if (hráč.gold >= 30) {
                            hráč.gold -= 30;
                            hráč.damage += 5;
                            cout << "Koupil jsi novou zbraň (+5 damage).\n";
                        } else {
                            cout << "Nemáš dostatek zlaťáků na tento nákup.\n";
                        }
                        break;
                    case 6:
                        cout << "Obchodník: \"Nashledanou, dobrodruhu!\"\n";
                        break;
                    default:
                        cout << "Neplatná volba.\n";
                        break;
                }
                vymazat();
                break;

            case 2:
                int nahodnaUdalost;
                nahodnaUdalost = rand() % 4;
                if (nahodnaUdalost == 0) {
                    cout << "Našel jsi zlaťák na zemi! (+5 zlaťáků)\n";
                    hráč.gold += 5;
                } else if (nahodnaUdalost == 1) {
                    cout << "Potkal jsi starého známého, který ti dal lektvar zdraví (+10 MAX HP).\n";
                    hráč.maxhp += 10;
                } else if (nahodnaUdalost == 2) {
                    cout << "Byl jsi napaden bandity! Utekl jsi, ale ztratil jsi 5 zlaťáků.\n";
                    if (hráč.gold >= 5) hráč.gold -= 5;
                } else {
                    cout << "Naletěl jsi na past a ztratil jsi 5 HP!\n";
                    hráč.hp -= 5;
                    if (hráč.hp < 0) hráč.hp = 0;
                    cout << "Zbývající životy hráče: " << hráč.hp << "\n";
                    if (!hráč.IsAlive())
                    {
                        cout << "Byl jsi poražen...\n";
                        Sleep(2000);
                        exit(0);
                    }
                }
                vymazat();
                break;

            case 3:
                cout << "Opouštíš vesnici.\n";
                opakovat = false;
                vymazat();
                break;

            default:
                cout << "Neplatná volba, zkus to znovu.\n";
                vymazat();
                break;
        }

    } while (opakovat);
}

void multifight(player &hráč, vector<monster> &monsters)
{
    while (hráč.IsAlive() && !monsters.empty())
    {
        cout << "\nKolo začíná!\n";
        cout << "Stav hráče:\n";
        hráč.StatyPlayer();

        cout << "Stav monster:\n";

        for (int i = 0; i < monsters.size(); i++)
        {
            cout << 1 + i << ": ";
            monsters[i].staty();
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

void fightMiniboss(player &hrac, miniboss &boss)
{
    cout << "Zaútočil na tebe " << boss.jméno << "!\n";
    if (boss.IsAlive()) {
        boss.attack();
        hrac.hp -= boss.damage;
        if (hrac.hp < 0) hrac.hp = 0;
        cout << "Zbývající životy hráče: " << hrac.hp << "\n";
        if (!hrac.IsAlive()) {
            cout << hrac.name << " byl poražen minibossem! Konec hry.\n";
            exit(0);
        }
    }

    vymazat();

    while (hrac.IsAlive() && boss.IsAlive())
    {
        cout << "\nStav hráče:\n";
        hrac.StatyPlayer();

        cout << "Stav minibosse:\n";
        cout << "Miniboss: " << boss.jméno << " - Životy: " << boss.životy << "\n";

        cout << "\nTvůj tah, vyber si akci:\n1. Útok\n2. Použít schopnost\n";
        int akce;
        cin >> akce;

        switch (akce) {
            case 1:
                cout << "Útočíš na minibosse " << boss.jméno << " a způsobuješ " << hrac.damage << " poškození.\n";
                boss.takeDamage(hrac.damage);
                if (!boss.IsAlive()) {
                    cout << boss.jméno << " byl poražen!\n";
                    hrac.gainExperience(boss.xpReward);
                    hrac.gainGold(boss.goldReward);
                }
                break;
            case 2: {
                int abilityIndex;
                cout << "Vyber si schopnost \n1 - útočná schopnost\n2 - vyléčení\n";
                cin >> abilityIndex;
                if (abilityIndex == 1 || abilityIndex == 2) {
                    hrac.useAbility(abilityIndex, boss);
                    if (!boss.IsAlive()) {
                        cout << boss.jméno << " byl poražen!\n";
                        hrac.gainExperience(boss.xpReward);
                        hrac.gainGold(boss.goldReward);
                    }
                } else {
                    cout << "Neplatná volba schopnosti.\n";
                }
                break;
            }
            default:
                cout << "Neplatná akce.\n";
                break;
        }

        if (boss.IsAlive()) {
            boss.attack();
            hrac.hp -= boss.damage;
            if (hrac.hp < 0) {hrac.hp = 0;}
            cout << "Zbývající životy hráče: " << hrac.hp << "\n";
            if (!hrac.IsAlive()) {
                cout << hrac.name << " byl poražen minibossem! Konec hry.\n";
                exit(0);
            }
        }
    }
}

void fightCutalot(player &hrac, cutalot &boss) {
    while (hrac.IsAlive() && boss.IsAlive()) {

        boss.attack(hrac);

        if (!hrac.IsAlive()) {
            cout << hrac.name << " byl poražen Cutalotem! Konec hry.\n";
            exit(0);
        }

        cout << "Stav Cutalota:\n";
        cout << "Cutalot: " << boss.jméno << " - Životy: " << boss.životy << "/" << "400" << "\n";

        cout << "\nTvoje tah, vyber si akci:\n1. Útok\n2. Použít schopnost\n";
        int akce;
        cin >> akce;

        switch (akce) {
            case 1:
                cout << "Útočíš na Cutalota " << boss.jméno << " a způsobuješ " << hrac.damage << " poškození.\n";
                boss.takeDamage(hrac.damage);
                break;
            case 2: {
                int abilityIndex;
                cout << "Vyber si schopnost (1-2): ";
                cin >> abilityIndex;
                if (abilityIndex == 1 || abilityIndex == 2) {
                    hrac.useAbility(abilityIndex, boss);
                    if (!boss.IsAlive()) {
                        cout << boss.jméno << " byl poražen!\n";
                        hrac.gainExperience(boss.xpReward);
                        hrac.gainGold(boss.goldReward);
                        break;
                    }
                } else {
                    cout << "Neplatná volba schopnosti.\n";
                }
                break;
            }
            default:
                cout << "Neplatná akce.\n";
                break;
        }

        if (!boss.IsAlive()) {
            cout << boss.jméno << " byl poražen!\n";
            cout << "VYHRÁL JSI HRU A ZLO BYLO ZAHNÁNO!\n";
            vymazat();
            break;
        }
    }
}

int main()
{
    SetConsoleOutputCP(CP_UTF8);

    int VýběrPostavy;
    char potvrzení;
    bool potvrdit;

    vector<monster> monsters1 =
    {
        monster("Bludička", 5, 40, 15, 10)
    };

    vector<monster> monsters2 =
    {
        monster("Vlk", 10, 60, 20, 15)
    };

    vector<monster> monsters3 =
    {
        monster("Kamený golem", 15, 120, 30, 10),
        monster("Dřevěný golem", 12, 100, 25, 12)
    };

    vector<monster> monsters4 =
    {
        monster("Banshee", 12, 50, 35, 15)
    };

    vector<monster> monsters5 =
    {
        monster("Rudý pavouk", 8, 35, 18, 10),
        monster("Zelený pavouk", 6, 30, 15, 8)
    };

    vector<monster> monsters6 =
    {
        monster("Ent", 14, 110, 28, 12),
        monster("Živý keř", 9, 50, 20, 10)
    };

    vector<monster> monsters7 =
    {
        monster("Ohnivý Elementál", 18, 80, 35, 15),
        monster("Vodní Elementál", 18, 80, 35, 15)
    };

    vector<monster> monsters8 =
    {
        monster("Vlkodlak", 20, 90, 28, 20),
        monster("Krysí mutant", 12, 55, 22, 15)
    };

    vector<monster> monsters9 =
    {
        monster("Obr", 30, 200, 50, 20),
        monster("Ork", 20, 100, 35, 15),
        monster("Goblin", 12, 60, 25, 10)
    };

    player warrior;
    warrior.name = "Darius Ironfist";
    warrior.hp = 50;
    warrior.maxhp = 50;
    warrior.energie = 50;
    warrior.maxenergie = 50;
    warrior.gold = 5;
    warrior.damage = 15;
    warrior.level = 1;
    warrior.zkušenosti = 0;
    warrior.healAmount = 10;
    warrior.className = "Warrior";

    player mage;
    mage.name = "Ranni Shadowcaster";
    mage.hp = 40;
    mage.maxhp = 40;
    mage.energie = 25;
    mage.maxenergie = 25;
    mage.gold = 5;
    mage.damage = 20;
    mage.level = 1;
    mage.zkušenosti = 0;
    mage.healAmount = 15;
    mage.className = "Mage";

    player rogue;
    rogue.name = "Ezio Silentblade";
    rogue.hp = 30;
    rogue.maxhp = 30;
    rogue.energie = 30;
    rogue.maxenergie = 30;
    rogue.gold = 5;
    rogue.damage = 25;
    rogue.level = 1;
    rogue.zkušenosti = 0;
    rogue.healAmount = 20;
    rogue.className = "Rogue";

    player hráč;

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
            cout << "ability: \n- 1. Shield Bash\n- 2. Heal\n\n";
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

        cout << "Potvrďte výběr postavy stiskem 'y', odmítněte klávesou 'n': ";
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

    cout << "Nacházíš se v malé vesnici obklopené hustým temným lesem. \nVesnice, která se jmenuje Zelený Háj, žije v míru a klidu díky ochraně kouzelného artefaktu ukrytého v místním chrámu.\nTento artefakt má moc udržovat zlo a temnotu na pokraji lesa.";
    Sleep(15000);
    system("CLS");
    cout << "Jednoho dne se však začnou dít neobvyklé věci.\n Monstra začnou útočit na vesnici z okolního lesa, což přivádí obyvatele do obav.\nTy jsi zde od toho aby si příčinu těchto útoků";
    Sleep(8000);
    system("CLS");
    vesnice(hráč);

    cout << "Vydáváš se do temného lesa a potkáváš bludičku!";
    Sleep(3000);
    system("CLS");
    multifight(hráč, monsters1);

    cout << "Po poražení bludičky na tebe vyskočí vlk. POZOR!";
    multifight(hráč, monsters2);

    cout << "Jdeš dále temným lesem...";
    Sleep(3000);
    system("CLS");
    cout << "Potkáš temného druida, který na tebe vyvolá 2 golemy!";
    multifight(hráč, monsters3);

    cout << "Teď je čas na Druida.";
    Sleep(3000);
    system("CLS");
    miniboss druid("Druid", 20, 150, 50, 30);
    fightMiniboss(hráč, druid);

    cout << "Zjevuje se ti stinná postava která povídá,\nže za útoky stojí stinná bytost, která chce získat kouzelný artefakt.\nTuto zprávu poté sděluješ ve vesnici.";
    Sleep(8000);
    system("CLS");
    vesnice(hráč);

    cout << "Jdeš na další zase prozkoumat les a najít další vodítka.\n";
    cout << "Potkáváš banshee a útočí na tebe\n";
    Sleep(8000);
    system("CLS");
    multifight(hráč, monsters4);

    cout << "Při prozkoumávání temného údolí narazí na dva Obří pavouky!";
    Sleep(3000);
    system("CLS");
    multifight(hráč, monsters5);

    cout << "Pokračuješ v cestě a narazíš na enta a živý keř.";
    Sleep(3000);
    system("CLS");
    multifight(hráč, monsters6);

    cout << "Nyní musíš čelit obří harpyji která se snesla z nebe!";
    Sleep(3500);
    system("CLS");
    miniboss harpije("Harpyje", 25, 180, 60, 35);

    cout << "Po poražení harpije si všimneš svitku s runami a mapou na její hrudi.\nVezmeš si ho a ukážeš stařešinovi, který rozpoznává symbol na mapě jako ztracený chrám v srdci lesa.\nStařešina vysvětluje, že tento chrám byl kdysi sídlem mocného Cutalota, démona z dávných dob.\n";
    Sleep(15000);
    system("CLS");
    vesnice(hráč);

    cout << "Předtím než se chceš vidat do Cutalotova chrámu, tak začnou utočit monstra na vesnici.\n";
    Sleep(4000);
    system("CLS");
    multifight(hráč, monsters7);
    multifight(hráč, monsters8);
    multifight(hráč, monsters9);
    cout << "Úspěšně si ochránil vesnici!\n";
    Sleep(3000);
    system("CLS");
    vesnice(hráč);

    cout << "Vydáváš se do Cutalotova chrámu...\n";
    Sleep(3000);
    system("CLS");

    cutalot Cutalot("Cutalot", 600, 0, 0);
    fightCutalot(hráč, Cutalot);
}
