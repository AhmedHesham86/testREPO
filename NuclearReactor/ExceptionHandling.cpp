#include<iostream>
#include<exception>

void SCRAM()
{
    std::cout<< "The reactor is Not under control !! RUN"<<std::endl;
}

bool reactor_saftey_check()
{
    static int count = 0;
    
    if (count < 100)
    {
        count ++;
        std::cout<<"check Sensor readings! \n";
        if(count % 17 == 0)
        {
            throw std::runtime_error("Saftey check!");
        }
        else if (count % 91 == 0)
        {
            throw std::logic_error("thrown Exception is lgoical error!");
        }
        else if (count % 99 == 0)
        {
            return false;
        }
        else
        {
            return true;
        }
        
    }else{return false;}

}


int main()
{

    bool continue_flag;

    do{
       
        try
        {
           continue_flag= reactor_saftey_check();
        }
        catch(std::runtime_error& e)
        {
            std::cout<< "Exception caught from saftey check! "<<e.what()<<std::endl;
        }
        catch(std::exception& e)
        {
            std::cout<< "Warnning Exception ! "<<e.what()<<std::endl;
            SCRAM();
            break;
        }
        catch(...)
        {
            std::cout<< "Unknown exception is thrown !! "<<std::endl;
            SCRAM();
            break;
        }


    }while(continue_flag == true);

    
    std::cout<< "Nuclear Reactor terminated!"<<std::endl;




    return 0;
}