#include <bits/stdc++.h>
using namespace std ;
float spcialDefend = 1;
// Weapons for Batman and Joker
//Weapon class
class character{
    private:
        int health;
        int energy;
        int reduc;
        string name;
    public:
        character(string n):health(100),energy(500),name(n){}
        virtual void attack(character* defender) = 0;
        virtual int defend(int damage) = 0;
        virtual void useShield() = 0;
        void redHealth(int blood) {health -= blood;}
        void redEnergy(int drain) {energy -= drain;}
        int getHealth() {return health;}
        int getEnergy() {return energy;}
        float getRed() {return (float)reduc/100.0;}
        void setRed(int red) {reduc = red;}
        bool isAlive() { return health > 0; }
        string getName() { return name; }
};
class weapon{
    private:
        int damage;
        int energyCost;
        int uses;
        string name;
    public:
        weapon(int damage,string name,int uses,int energyCost):name(name),uses(uses),energyCost(energyCost),damage(damage){}
        virtual void use(character* user,character* opponent) = 0;
        int haveEnergy(character* user){return user->getEnergy() >= energyCost;}
        int getDamage(){return damage;}
        int getEnergyCost(){return energyCost;}
        string getName(){return name;}
        void Used(){uses -= 1;}
        bool couldUse(){return uses > 0 || uses == -1; }
};
class NoneWp : public weapon{
    public:
        NoneWp():weapon(0,"None",-1,0){}
        void Used (){}
        void use(character* user,character* opponent){
            cout << user->getName() << " attacks with " << getName() << " causing " << getDamage()<< " damage." << endl;
            Used();
        }
};
//Batman Weapons classes
class Batarang : public weapon{
    public:
        Batarang():weapon(11,"Batarang",-1,50){}
        void Used (){}
        void use(character* user,character* opponent){
            user->redEnergy(getEnergyCost());
            opponent->redHealth(getDamage()-opponent->defend(getDamage()));
            cout << user->getName() << " attacks with " << getName() << " causing " << getDamage()-opponent->defend(getDamage()) << " damage." << endl;
            Used();
        }
};
class GrappleGun : public weapon{
    public:
        GrappleGun():weapon(18,"GrappleGun",5,88){}
        void use(character* user,character* opponent){
            user->redEnergy(getEnergyCost());
            opponent->redHealth(getDamage()-opponent->defend(getDamage()));
            cout << user->getName() << " attacks with " << getName() << " causing " << getDamage()-opponent->defend(getDamage()) << " damage." << endl;
            Used();
        }
};
class ExplosiveGel : public weapon{
    public:
        ExplosiveGel():weapon(10,"ExplosiveGel",3,92){}
        void use(character* user,character* opponent){
            user->redEnergy(getEnergyCost());
            opponent->redHealth(getDamage()-opponent->defend(getDamage()));
            spcialDefend = 0.2;
            cout << user->getName() << " attacks with " << getName() << " causing " << getDamage()-opponent->defend(getDamage()) << " damage." << endl;
            Used();
        }
};
class Batclaw : public weapon{
    public:
        Batclaw():weapon(20,"Batclaw",1,120){}
        void use(character* user,character* opponent){
            user->redEnergy(getEnergyCost());
            opponent->redHealth(getDamage());
            cout << user->getName() << " attacks with " << getName() << " causing " << getDamage() << " damage." << endl;
            Used();
        }
};
//Joker Weapons classes
class JoyBuzzer : public weapon{
    public:
        JoyBuzzer():weapon(8,"JoyBuzzer",-1,40){}
        void Used (){}
        void use(character* user,character* opponent){
            user->redEnergy(getEnergyCost());
            opponent->redHealth(getDamage()-opponent->defend(getDamage()));
            cout << user->getName() << " attacks with " << getName() << " causing " << getDamage()-opponent->defend(getDamage()) << " damage." << endl;
            Used();
        }
};
class LaughingGas : public weapon{
    public:
        LaughingGas():weapon(13,"LaughingGas",8,56){}
        void use(character* user,character* opponent){
            user->redEnergy(getEnergyCost());
            opponent->redHealth(getDamage()-opponent->defend(getDamage()));
            cout << user->getName() << " attacks with " << getName() << " causing " << getDamage()-opponent->defend(getDamage()) << " damage." << endl;
            Used();
        }
};
class AcidFlower : public weapon{
    public:
        AcidFlower():weapon(22,"AcidFlower",3,100){}
        void use(character* user,character* opponent){
            user->redEnergy(getEnergyCost());
            opponent->redHealth(getDamage()-opponent->defend(getDamage()));
            cout << user->getName() << " attacks with " << getName() << " causing " << getDamage()-opponent->defend(getDamage()) << " damage." << endl;
            Used();
        }
};
class shield {
    private:
        int damageReduction;
        int energyCost;
        int uses;
        string name;
    public:
        shield(int damageReduction,string name,int uses,int energyCost):name(name),uses(uses),energyCost(energyCost),damageReduction(damageReduction){}
        int haveEnergy(character* user){return user->getEnergy() >= energyCost;}
        int getDamageReduction(){return damageReduction;}
        int getEnergyCost(){return energyCost;}
        void use(character* user){user->redEnergy(getEnergyCost());};
        string getName(){return name;}
        void Used(){uses -= 1;}
        bool couldUse(){return uses > 0 || uses == -1; }
};
//difine weapon variables
Batarang batarang;
GrappleGun grappleGun;
ExplosiveGel explosiveGel;
Batclaw batclaw;
JoyBuzzer joyBuzzer;
LaughingGas laughingGas;
AcidFlower acidFlower;
NoneWp noneWp;
shield CapeGlide = shield(40,"CapeGlide",-1,20);
shield SmokePellet = shield(90,"SmokePellet",2,50);
shield TrickShield = shield(32,"TrickShield",-1,15);
shield RubberChicken = shield(80,"RubberChicken",3,40);
shield NoneSH = shield(0,"None",-1,0);
//Batman the dark Night
class Batman : public character{
    public:
        Batman():character("Batman"){}
        void attack(character* defender) {
            spcialDefend =1;
            cout << "Choose Batman's weapon:\n1. Batarang\n2. Grapple Gun\n3. Explosive Gel\n4. Batclaw\n";
            int choice;
            weapon* Weapon;
            while(true){
                cin >> choice;
                switch (choice) {
                    case 1: Weapon = &batarang; break;
                    case 2: Weapon = &grappleGun; break;
                    case 3: Weapon = &explosiveGel; break;
                    case 4: Weapon = &batclaw; break;
                    default: Weapon = &noneWp; break;//fiXXXXXXXXXXX
                }
                if(Weapon->haveEnergy(this)&&Weapon->couldUse())
                {
                    break;
                }
                else if(Weapon->haveEnergy(this))
                {
                    cout<<"zero uses left!"<<endl;
                }
                else{
                    cout<<"no enough energy"<<endl;
                }
                cout << "pick again"<<endl; 
            }
            defender->useShield();
            Weapon->use(this, defender);
        }
        int defend(int damage) {
            return (int)((float)damage*getRed());
        }
        void useShield() {
            cout << "Choose Batman's shield:\n1. Cape Glide\n2. Smoke Pellet\n";
            int choice;
            shield* Shield;
            while(true){
                cin >> choice;

                switch (choice) {
                    case 1: Shield = &CapeGlide; break;
                    case 2: Shield = &SmokePellet; break;
                    default: Shield = &NoneSH; break;
                }
                if(Shield ->haveEnergy(this)&&Shield->couldUse())
                {
                    break;
                }
                else if(Shield->haveEnergy(this))
                {
                    cout<<"zero uses left!"<<endl;
                }
                else{
                    cout<<"no enough energy"<<endl;
                }
                cout << "pick again"<<endl; 
            }
            Shield->use(this);
            setRed(Shield->getDamageReduction());
        }
};
class Joker : public character{
    public:
        Joker():character("Joker"){}
        void attack(character* defender) {
            cout << "Choose Joker's weapon:\n1. Joy Buzzer\n2. Laughing Gas\n3. Acid Flower\n";
            int choice;
            weapon* Weapon;
            while(true){
                cin >> choice;
                switch (choice) {
                    case 1: Weapon = &joyBuzzer; break;
                    case 2: Weapon = &laughingGas; break;
                    case 3: Weapon = &acidFlower; break; 
                    default: Weapon = &noneWp; break;
                }
                if(Weapon->haveEnergy(this)&&Weapon->couldUse())
                {
                    break;
                }
                else if(Weapon->haveEnergy(this))
                {
                    cout<<"zero uses left!"<<endl;
                }
                else{
                    cout<<"no enough energy"<<endl;
                }
                cout << "pick again"<<endl; 
            }
            defender->useShield();
            Weapon->use(this, defender);
        }
        int defend(int damage) {
            return (int)((float)damage*getRed()*spcialDefend);
        }
        void useShield() {
            cout << "Choose Joker's shield:\n1. Trick Shield\n2. Rubber Chicken\n";
            int choice;
            shield* Shield;
            while(true){
                cin >> choice;

                switch (choice) {
                    case 1: Shield =&TrickShield; break;
                    case 2: Shield = &RubberChicken; break;
                    default: Shield = &NoneSH; break;
                }
                if(Shield ->haveEnergy(this)&&Shield->couldUse())
                {
                    break;
                }
                else if(Shield->haveEnergy(this))
                {
                    cout<<"zero uses left!"<<endl;
                }
                else{
                    cout<<"no enough energy"<<endl;
                }
                cout << "pick again"<<endl; 
            }
            Shield->use(this);
            setRed(Shield->getDamageReduction());
        }
};

// main function ===================================
int main()
{
    Batman batman;
    Joker joker;
    character *currentAttacker = &batman;
    character *currentDefender = &joker;
    
    while (batman.isAlive() && joker.isAlive() && (batman.getEnergy()>= 20 || joker.getEnergy()>= 15)) {
        cout << "Batman Health: " << batman.getHealth() << ", Energy: " << batman.getEnergy() << endl;
        cout << "Joker Health: " << joker.getHealth() << ", Energy: " << joker.getEnergy() << endl;
        currentAttacker->attack(currentDefender);
        swap(currentAttacker, currentDefender);
    }
    if(batman.isAlive() && joker.isAlive())
    {
        cout << "Draw!!" << endl;
    }
    else if (batman.isAlive() ) {
        cout << "Batman wins!" << endl;
    } else {
        cout << "Joker wins!" << endl;
    }
    
    cout << "Final State: " << endl;
    cout << "Batman Health: " << batman.getHealth() << ", Energy: " << batman.getEnergy() << endl;
    cout << "Joker Health: " << joker.getHealth() << ", Energy: " << joker.getEnergy() << endl;
    
    return 0;                    
}                                                            
  
  
  
