#include <iostream>
#include <string>
#include <vector>
#include <queue>
using namespace std;

class QNS { 
    int powerLevel;
    int durability;
    int energyStorage;
    int heatLevel;

public:

    QNS (int P=1000, int D=500, int E=300, int H=0): powerLevel(P), durability(D), energyStorage(E), heatLevel(H) {}
    QNS (const QNS& QNSCopy): powerLevel(QNSCopy.powerLevel), durability(QNSCopy.durability), energyStorage(QNSCopy.energyStorage), heatLevel(QNSCopy.heatLevel) {}
    void operator +(const QNS& Q2) {
        set_powerLevel(powerLevel+Q2.energyStorage);
        set_durability(durability+Q2.durability);
        set_energyStorage(energyStorage+Q2.powerLevel);
    }
    void operator -(int X) {
        set_durability(durability-X);
        set_energyStorage(energyStorage+X);
        set_heatLevel(heatLevel+X);
    }
    void operator *(int X) {
        set_powerLevel(powerLevel+((powerLevel*X)/100));
        set_energyStorage(energyStorage+5*X);
        set_heatLevel(heatLevel+X);
    }
    void operator /(int X) {
        set_durability(durability+X);
        set_heatLevel(heatLevel-X);
    }
    void boostPower(int factor) {
        (*this)*factor;
    }
    void boostPower(QNS otherSuit) {
        *this+otherSuit;
    }
    bool operator ==(const QNS& Q2) {
        if (powerLevel==Q2.powerLevel && durability==Q2.durability)
            return true;
        return false;
    }
    bool operator <(const QNS& Q2) {
        if (powerLevel+durability<Q2.powerLevel+Q2.durability)
            return true;
        return false;
    }
    int get_powerLevel() {
        return powerLevel;
    }
    int get_durability() {
        return durability;
    }
    int get_energyStorage() {
        return energyStorage;
    }
    int get_heatLevel() {
        return heatLevel;
    }
    void set_powerLevel(int P) {
        if (P<5000)
            powerLevel=P;
        else
            powerLevel=5000;
    }
    void set_durability(int D) {
        durability=D;
    }
    void set_energyStorage(int E) {
        energyStorage=E;
    }
    void set_heatLevel(int H) {
        if (H>0)
            heatLevel=H;
        else
            heatLevel=0;
    }
    friend void operator >>(istream& stream,QNS &suit) {
        int P,D,E,H;
        stream >> P >> D >> E >> H;
        if (D<=0)
            return;
        suit.set_powerLevel(P);
        suit.set_durability(D);
        suit.set_energyStorage(E);
        suit.set_heatLevel(H);
    }
};

class Avenger {
    string name;
    QNS suit;
    int attackStrength;

public:
    Avenger(string avName, QNS avSuit, int strength): name(avName), suit(avSuit), attackStrength(strength) {}
    void attack(Avenger* enemy) {
        enemy->suit-attackStrength;
    }
    void upgradeSuit(QNS extra_suit) {
        suit+extra_suit;
    }
    void repair(int x) {
        suit/x;
    }
    void printStatus() {
        cout << name << " " << suit.get_powerLevel() << " " << suit.get_durability() << " " << suit.get_energyStorage() << " " << suit.get_heatLevel() << endl;
    }
    string get_name() {
        return name;
    }
    QNS& getSuit() {
        return suit;
    }
    QNS* operator ->() {
        return &suit;
    }
};

class Battle {
    vector<Avenger> heroes;
    vector<Avenger> enemies;
    vector<string> battleLog;
    queue<QNS> suits;

public:

    void startBattle() {
        string command;
        cin >> command;
        while (command!="End") {
            if (command=="Attack") {
                string Avenger1,Avenger2;
                cin >> Avenger1 >> Avenger2;
                if (findAvenger(Avenger1)==nullptr || findAvenger(Avenger2)==nullptr || !(findAvenger(Avenger1)->getSuit().get_durability()>0 && findAvenger(Avenger1)->getSuit().get_heatLevel()<=500 && findAvenger(Avenger2)->getSuit().get_durability()>0))
                    continue;
                findAvenger(Avenger1)->attack(findAvenger(Avenger2));
                battleLog.push_back(Avenger1+" attacks "+Avenger2);
                if (findAvenger(Avenger2)->getSuit().get_durability()<=0) 
                    battleLog.push_back(Avenger2+" suit destroyed");
                else if (findAvenger(Avenger2)->getSuit().get_heatLevel()>500)
                    battleLog.push_back(Avenger2+" suit overheated");
            } else if (command=="Repair") {
                string AvengerName;
                int x;
                cin >> AvengerName >> x;
                if (findAvenger(AvengerName)==nullptr)
                    continue;
                findAvenger(AvengerName)->repair(x);
                battleLog.push_back(AvengerName+" repaired");
            } else if (command=="BoostPowerByFactor") {
                string AvengerName;
                int y;
                cin >> AvengerName >> y;
                if (findAvenger(AvengerName)==nullptr)
                    continue;
                findAvenger(AvengerName)->getSuit().boostPower(y);
                battleLog.push_back(AvengerName+" boosted");
                if (findAvenger(AvengerName)->getSuit().get_heatLevel()>500)
                    battleLog.push_back(AvengerName+" suit overheated");
            } 
            else if (command=="BoostPower") {
                string AvengerName; int P,D,E,H;
                cin >> AvengerName >> P >> D >> E >> H;
                if (findAvenger(AvengerName)==nullptr)
                    continue;
                findAvenger(AvengerName)->getSuit().boostPower(QNS(P,D,E,H));
                battleLog.push_back(AvengerName+" boosted");
                if (findAvenger(AvengerName)->getSuit().get_heatLevel()>500)
                    battleLog.push_back(AvengerName+" suit overheated");
            } 
            else if (command=="AvengerStatus") {
                string AvengerName;
                cin >> AvengerName;
                if (findAvenger(AvengerName)==nullptr)
                    continue;
                findAvenger(AvengerName)->printStatus();
            } 
            else if (command=="Upgrade") {
                string AvengerName;
                cin >> AvengerName;
                if (findAvenger(AvengerName)==nullptr)
                    continue;
                if (!suits.empty()) {
                    findAvenger(AvengerName)->upgradeSuit(suits.front());
                    suits.pop();
                    battleLog.push_back(AvengerName+" upgraded");
                } else 
                    battleLog.push_back(AvengerName+" upgrade Fail");
            } 
            else if (command=="PrintBattleLog") {
                printBattleLog();
            } 
            else if (command=="BattleStatus") {
                if (Result()==1)
                    cout << "heroes are winning" << endl;
                else if (Result()==-1)
                    cout << "enemies are winning" << endl;
                else    
                    cout << "tie" << endl;
            }
            cin >> command;
        }
    }
    Avenger* findAvenger(string avenger) {
        for (int i=0;i<heroes.size();i++) {
            if (heroes[i].get_name()==avenger)
                return &heroes[i];
        }
        for (int i=0;i<enemies.size();i++) {
            if (enemies[i].get_name()==avenger)
                return &enemies[i];
        }
        return nullptr;
    }
    void printBattleLog() {
        for (auto log:battleLog) {
            cout << log << endl;
        }
    }
    int Result() {
        int hero_count=0, enemy_count=0;
        for (int i=0;i<heroes.size();i++){
            if (heroes[i]->get_durability()>0)
                hero_count+=heroes[i]->get_powerLevel()+heroes[i]->get_durability();
        }
        for (int i=0;i<enemies.size();i++){
            if (enemies[i]->get_durability()>0)
                enemy_count+=enemies[i]->get_powerLevel()+enemies[i]->get_durability();
        }
        if (hero_count>enemy_count)
            return 1;
        else if (hero_count<enemy_count)
            return -1;
        else
            return 0;
    }
    void addSuit(QNS suit) {
        suits.push(suit);
    }
    void addHero(string name, int attackStrength) {
        if (suits.empty())
            cout << name << " is out of fight" << endl;
        else {
            QNS newsuit=suits.front();
            suits.pop();
            heroes.push_back(Avenger(name,newsuit,attackStrength));
        }
    }
    void addEnemy(string name, int attackStrength) {
        if (suits.empty())
            cout << name << " is out of fight" << endl;
        else {
            QNS newsuit=suits.front();
            suits.pop();
            enemies.push_back(Avenger(name,newsuit,attackStrength));
        }
    }
};

int main () {
    Battle battle;
    int k,n,m;
    cin >> k >> n >> m;
    QNS suit;
    for (int i=0;i<k;i++) {
        cin >> suit;
        battle.addSuit(suit);
    }
    for (int i=0;i<n;i++) {
        string Name; int attackstrength;
        cin >> Name >> attackstrength;
        battle.addHero(Name,attackstrength);
    }
    for (int i=0;i<m;i++) {
        string Name; int attackstrength;
        cin >> Name >> attackstrength;
        battle.addEnemy(Name,attackstrength);
    }
    string command;
    cin >> command;
    if (command=="BattleBegin")
        battle.startBattle();
    return 0;
}
