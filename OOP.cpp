#include <bits/stdc++.h>
using namespace std ;
int turn = 0;
class weapon{
    private:
        int uses;
        int energy;
        string name;
    public:
        weapon(string name,int uses,int energy):name(name),uses(uses),energy(energy){
        }
        void setUses(int uses){
            if(this->uses < uses || uses < -1)
            {
                cout << "error";
                return;
            }
            this->uses = uses;
        }
        int getUses(){
            return uses;
        }
        int getEnergy(){
            return energy;
        }
        string getName(){
            return name;
        }
};
class attackWeapon : public weapon{
    private:
        int damage;
    public:
        attackWeapon(int damage,string name,int uses,int energy):damage(damage),weapon(name,uses,energy){
        }
        int getDamage(){
            return damage;
        }

};
class shield : public weapon{
    private:
        int shieldValue;
    public:
        shield(int shieldValue,string name,int uses,int energy):shieldValue(shieldValue),weapon(name,uses,energy){
        }
        int getShieldValue(){
            return shieldValue;
        }
};

class character{
    private:
        int health;
        int energy;
        attackWeapon* atWeapon;
        shield* dfWeapon;
    public:
        character(){
            health = 100;
            energy = 500;
        }
        void attack(character* defender)
        {
            if(atWeapon->getUses() != -1 && defender->dfWeapon->getUses() != -1){
                atWeapon->setUses(atWeapon->getUses()-1);
                defender->dfWeapon->setUses(defender->dfWeapon->getUses()-1);
            }
            else if(atWeapon->getUses() != -1){
                atWeapon->setUses(atWeapon->getUses());
                defender->dfWeapon->setUses(defender->dfWeapon->getUses()-1);
            }
            else if(defender->dfWeapon->getUses() != -1){
                atWeapon->setUses(atWeapon->getUses()-1);
                defender->dfWeapon->setUses(defender->dfWeapon->getUses());
            }
            else{
                atWeapon->setUses(atWeapon->getUses());
                defender->dfWeapon->setUses(defender->dfWeapon->getUses());
            }
            energy -= atWeapon->getEnergy();
            defender->setEnergy(defender->getEnergy()-defender->dfWeapon->getEnergy());
            if(atWeapon->getName() != "Batclaw")
            {
                defender->setHealth(defender->getHealth()-atWeapon->getDamage()+defender->defend(atWeapon->getDamage()));
            }
            else{
                defender->setHealth(defender->getHealth()-atWeapon->getDamage());
            }

        }
        int defend(int damage)
        {
            return (damage*((float)dfWeapon->getShieldValue()/100.0));
        }
        void setHealth(int health){
            if (health > this->health)
            {
                cout << "error health cant increase!!";
                return;
            }
            this->health = health;
        }
        void setEnergy(int energy){
            if (energy > this->energy)
            {
                cout << "error energy cant increase!!";
                return;
            }
            this->energy = energy;
        }
        void setDfWeapon(shield* dfWeapon){
            if (!dfWeapon->getUses())
            {
                cout << "error you cant use this weapon";
                return;
            }
            this->dfWeapon = dfWeapon;
        }
        void setAtWeapon(attackWeapon* atWeapon ){
            if (!atWeapon->getUses())
            {
                cout << "error you cant use this weapon";
                return;
            }
            this->atWeapon = atWeapon;
        }
        int getHealth(){
            return health;
        }
        int getEnergy(){
            return energy;
        }
        string getDfWeaponName(){
            return dfWeapon->getName();
        }
        string getAtWeaponName(){
            return atWeapon->getName();
        }
};

attackWeapon Batman_weapon[] = {attackWeapon(11,"Batarang",-1,50),attackWeapon(18,"GrappleGun",5,88),attackWeapon(10,"ExplosiveGel",3,92),attackWeapon(20,"Batclaw",1,120)};
attackWeapon joker_weapon[] = {attackWeapon(8,"JoyBuzzer",-1,40),attackWeapon(13,"LaughingGas",8,56),attackWeapon(22,"AcidFlower",3,100)};
shield Batman_shield[] = {shield(40,"CapeGlide",-1,20),shield(90,"SmokePellet",2,50)};
shield joker_shield[] = {shield(32,"TrickShield",-1,15),shield(80,"RubberChicken",3,40)};
void WeaponChoosing(character* batman , character* joker)
{
    int n1 = 0 ;
    int n2 = 0 ;
    do
    {
        cout << "choose your weapon batman" << endl;
        cin >> n1;
        if(!turn){
            if(n1 < 4 && batman->getEnergy()>Batman_weapon[n1].getEnergy() && Batman_weapon[n1].getUses() != 0){
                batman->setAtWeapon(&Batman_weapon[n1]);
            }
            else{
                cout << "pick again" << endl;
                continue;
            }
        }
        else{
            if(n1 < 2 && batman->getEnergy()>Batman_shield[n1].getEnergy() && Batman_shield[n1].getUses() != 0){
                batman->setDfWeapon(&Batman_shield[n1]);
            }
            else{
                cout << "pick again" << endl;
                continue;
            }
        }
        cout << "choose your weapon joker" << endl;
        cin >> n2;
        if(turn){
            if(n2 < 3 && joker->getEnergy()>joker_weapon[n2].getEnergy() && joker_weapon[n2].getUses() != 0){
                joker->setAtWeapon(&joker_weapon[n2]);
                break;
            }
            else{
                cout << "pick again" << endl;
                continue;
            }
        }
        else{
            if(n2 < 2 &&joker->getEnergy()>joker_shield[n2].getEnergy() && joker_shield[n2].getUses() != 0){
                joker->setDfWeapon(&joker_shield[n2]);
                break;
            }
            else{
                cout << "pick again" << endl;
                continue;
            }
        }
    } while (1);
    
}
int main()
{
    character batman ;
    character joker ;
    while(1){
    WeaponChoosing(&batman , &joker);
    if(!turn){
        cout << "The character performing the attack." << endl;
        cout << "batman using " << batman.getAtWeaponName() << endl;
        cout << "joker using " << joker.getDfWeaponName() << endl;
        batman.attack(& joker);
        cout << "joker HP is " << joker.getHealth() << endl;
        cout << "batman HP is " << batman.getHealth() << endl;
    }
    else if(turn){
        cout << "The character performing the attack." << endl;
        cout << "joker using " << joker.getAtWeaponName() << endl;
        cout << "batman using " << batman.getDfWeaponName() << endl;
        joker.attack(& batman);
        cout << "joker HP is " << joker.getHealth() << endl;
        cout << "batman HP is " << batman.getHealth() << endl;
    }
    if(batman.getHealth() <= 0 )
    {
        cout <<"joker win";
        break;
    }
    else if (joker.getHealth() <= 0)
    {
        cout <<"batman win";
        break;
    }
    turn = !turn;
    }

    return 0;
}