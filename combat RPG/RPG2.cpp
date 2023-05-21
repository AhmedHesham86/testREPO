#include<iostream>
#include<string>
#include<vector>
#include<queue>
#include<algorithm>


class attacks
{
public:

attacks()
{
    m_attackname="";
    m_attackstat=0;
}

attacks(std::string name , int32_t stat) : m_attackname(name),  m_attackstat(stat)
{}

std::string getname() const
{
    return m_attackname;
}

int32_t getStat() const
{
    return m_attackstat;
}

private:
std::string m_attackname;
int32_t m_attackstat;
};

class items
{
public:
items()
{
    m_itemname="";
    m_healstat=0;
}

items(std::string name, int32_t stat) : m_itemname(name), m_healstat(stat)
{}

std::string getItemname() const
{
    return m_itemname;
}

int32_t getHealstat() const
{
    return m_healstat;
}

private:

std::string m_itemname;
int32_t m_healstat;
};


class character
{

public:

character(std::string name,int32_t hp, std::vector<attacks> attack ,std::vector<items> item , int32_t strengthM , int32_t defenceM , int attackindex = 0)
{
    m_name=name;
    health=hp;
    strengthMultiplier=strengthM;
    defenceMultiplier=defenceM;
    m_attackindex = attackindex;

    m_attack.insert(m_attack.begin(),attack.begin(),attack.end());
    m_item.insert(m_item.begin(),item.begin(),item.end());
}

std::string getname() const
{
    return m_name;
}

int32_t getHealth() const
{
    return health;
}

int32_t getStrength() const
{
    return strengthMultiplier;
}

int32_t getdefence() const
{
    return defenceMultiplier;
}

void display()
{
    std::cout<<"The Character name is: " <<getname() << '\n';
    std::cout<<"The strength is: "<< strengthMultiplier<<'\n';
    std::cout<<"The defence is: "<< defenceMultiplier<<'\n';
    std::cout<< getname() << " "<< "HP is: "<< getHealth()<<'\n';
    std::cout<<"Attacks: \n";

    for(auto x : m_attack)
    {
        std::cout<< x.getname() <<" : "<<x.getStat()<<std::endl;
    }

    std::cout<<"Items: \n";

    for(auto x : m_item)
    {
        std::cout<< x.getItemname() << " : "<<x.getHealstat()<<std::endl;
    }




}

void Attackmove(std::string attackname , character& attacked) 
{   
    std::cout<< m_name << " Used: "<< attackname << " on: "<<attacked.getname()<<std::endl;
    attacked.dodefend(getattackvalue(attackname)* strengthMultiplier);

}

// overloading Attackmove function

void Attackmove(character&attacked)
{
    std::string attackname = m_attack[m_attackindex].getname();
    std::cout<< m_name <<" Used: "<< attackname << " on: "<<attacked.getname()<<std::endl;
    attacked.dodefend(getattackvalue(attackname)*strengthMultiplier);
    
}

void useitem(std::string itemname)
{
    
    int value = getitemvalue(itemname);
    std::cout<< m_name << " Used: "<< itemname << " And restored "<< value <<" HP " <<std::endl;
    health += value ;
    std::cout<< m_name << " Cuurent hp is: "<< health<<std::endl;
}

bool isdead()
{
    return health<=0;
}

private:

void dodefend(int attackval)
{
    int damage = attackval / defenceMultiplier ;
    health -= damage;

    std::cout<< m_name << " Takes damage: "<< damage << " Its current health is: "<<health <<std::endl;

}

int getattackvalue(std::string attakname)
{
    auto it = std::find_if(m_attack.begin(),m_attack.end(),[attakname](attacks& attack){return attakname==attack.getname();});

    return(it != m_attack.end()) ? (*it).getStat() : 0 ;
}

int getitemvalue (std::string Itemname)
{
    auto it = std::find_if(m_item.begin(),m_item.end(),[Itemname](items & itm){return itm.getItemname() == Itemname;});
    return (it != m_item.end()) ? (*it).getHealstat() : 0 ;

}

private:

std::vector<attacks> m_attack;
std::vector<items> m_item;
std::string m_name;
int32_t strengthMultiplier;
int32_t defenceMultiplier;
int32_t health;
int32_t m_attackindex;
};



int main()
{

    std::vector<attacks> char1attacks {{"sword attack",50}};
    std::vector<items> char1items {{"Healing potion",50}};
    character char1 ("Ahmed",100 , char1attacks, char1items , 2 ,4);

    std::vector<attacks> TrantulaAttacks {{"spider web",60}};
    std::vector<items> TrantulaItems {{"Healing spiderlings",60}};
    character Trantula ("Trantula", 100 ,TrantulaAttacks , TrantulaItems , 1 , 1);

    std::vector<attacks> WitchAttacks {{"spider web",55}};
    std::vector<items> WitchItems {{"Redemption",60}};
    character Witch ("Witch", 200 ,WitchAttacks , WitchItems , 2 , 2);

    std::vector<attacks> GhoulAttacks {{"spider web",50}};
    std::vector<items> GhoulItems {{"Healing souls",60}};
    character Ghoul ("Ghoul", 150 ,GhoulAttacks , GhoulItems , 3 , 3);

    std::vector<attacks> GoblinAttacks {{"spider web",55}};
    std::vector<items> GoblinItems {{"Corrupting potion",60}};
    character Goblin ("Goblin", 100 ,GoblinAttacks , GoblinItems , 3 , 4);

    std::queue<character> monsters;
    monsters.push(Trantula);
    monsters.push(Witch);
    monsters.push(Ghoul);
    monsters.push(Goblin);
    bool playerTurn=false;
    bool GameOver = false;
    while(!monsters.empty() && !GameOver)
    {
        std::cout<<char1.getname() <<" Finds himself surrounded by monsters! "<<std::endl;
        character currentMonster = monsters.front();
        std::cout<<"A monster Appeared ! "<<currentMonster.getname()<<std::endl;
     while(!currentMonster.isdead())
        {
            std::cout <<std::endl;
            if(playerTurn)
            {
                std::cout << "Ahmed's turn" <<std::endl;
                std::cout << "Ahmed can press 1 and enter to use an item and 2 and enter to attack the monster." <<std::endl;
                
                bool madeChoice = false;
                while(!madeChoice)
                {
                    int choice;
                    std::cin >> choice;
                    
                    switch(choice)
                    {
                        case 1:
                            char1.useitem("Healing potion");
                            madeChoice = true;
                            break;
                            
                        case 2:
                            char1.Attackmove(currentMonster);
                            madeChoice = true;
                            break;
                            
                        default:
                            break;
                    }
                }
            }
            else
            {
                std::cout << currentMonster.getname() << "'s turn" <<std::endl;
                currentMonster.Attackmove(char1);
            }
            
            std::cout << "Ahmeds health is " << char1.getHealth() <<std::endl;
            std::cout << currentMonster.getname() << "'s health is " << currentMonster.getHealth() <<std::endl;
            
            if(currentMonster.isdead())
            {
                std::cout << currentMonster.getname() << " is defeated" <<std::endl;
                monsters.pop();
            }
                
            if(char1.isdead())
            {
                GameOver = true;
                break;
            }
            
            
            playerTurn = !playerTurn;
        }
    }
    
    if(monsters.empty())
    {
        std::cout << "You win";
    }
    
    if(GameOver)
    {
        std::cout << "You lose";
    }
    return 0;
}