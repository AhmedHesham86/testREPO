#include <iostream>
#include <memory>

/*

Proxy protocol is used for data hiding and also to authenticate the access to the protocol itself

*/


class Ibox
{
    public:

    virtual void open() = 0;
    virtual ~Ibox() = default;

};

class Simplebox : public Ibox
{
    public:
    void open()
    {
        std::cout<<"Simple box opened\n";
    }
};

/* Extend the protocol like below in Simplebox2 */

// class Simplebox2 : public Ibox
// {
//     public:
//     void open()
//     {
//         std::cout<<"Simple box2 opened\n";
//     }
// };

class Proxy : public Ibox
{
    public:

    //for authentication make Proxy accept user & password in the constructor for example:


    /*
    using initializer list in the parametrized constructor, also using explicit to make sure that the only way to access the protocol
    is by using user & password

    explicit Proxy(string user , string password) : m_Ibox(new Simplebox()), this->user(user) , this->password(password){}
    */

    explicit Proxy() : m_Ibox(new Simplebox()) 
    {
        /*
        for authentication:

        this-> user = user;
        this-> password = password;

        */
    }

    void open()
    {
        //do some authentication before accessing the protocol for example:

        //if(authintecated){
        m_Ibox->open();
        //}
        //else
        //{
        //  cout<<"Access denied!\n";
        //}
    }

    ~Proxy() {m_Ibox->~Ibox();}


    private:

    //write here authentication function!!
    /*
    bool authintecated()
    {
        if(user == "Admin" && password == "Admin123")
        {
            return true;
        }
        else
        {
            return false;
        }
    }



    */
    //private memebers to add (user & password).

    //string user,password;
    std::shared_ptr<Ibox> m_Ibox; // aggregation of Ibox class

};

//using a function to create a shared pointer of the Proxy instead of creating it in main

std::shared_ptr<Proxy> makeShared()
{
    return std::make_shared<Proxy>();
}

int main()
{
    auto object = makeShared();
    std::cout<<"obejct 1 box: ";
    object->open();
    Proxy somebox;
    std::cout<<"Somebox : " ;
    somebox.open();

    return 0;
}