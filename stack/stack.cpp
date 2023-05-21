#include<iostream>
#include<memory>

template<class T>
class stack
{
public:
//constructors
//default
    stack()

    {
        init();
    }
//parameteraized constructor ... takes the size of elements and initialize them with an initial value.
    explicit stack(size_t NumElements, const T& initialValue = T())
    {
        init(NumElements,initialValue);
    }

//methods user can use in the stack.

    T* top()
    {
        return stackData;
    }

    const T* top() const
    {
        return stackData;
    }

    T* bottom()
    {
        return {stackEndData -1} ;
    }

    const T* bottom() const
    {
        return {stackEndData - 1} ;
    } 

    size_t size() const
    {
        return (stackEndData - stackData);
    }

    bool empty() const
    {
        return  size() == 0; 
    }

    void pop()
    {
        if (bottom() !=0)
        {
            alloc.destroy(bottom());
            stackEndData -= 1;
        }
    }

    void push(const T& value)
    {
        if (stackEndData == memlimit)
        {
            resize();
        }
        append(value);
    }

//for the copy constructor and copy assignment opertator
    stack (const stack& S)
    {
        init(S.top(),S.bottom());
    }

    stack& operator= (const stack& rhs)
    {
        if ( this != &rhs)
        {
            destroy();
            init(rhs.top(),rhs.bottom());
        }
        return *this ;
    }


void print()
{
    for(auto it=stackData ; it != stackEndData ; it++)
    {
        std::cout<< *it << " ";
    }
    std::cout<<std::endl;
}

//class destructor
    ~stack()
    {
        destroy();
    }
private: //functions
    void append(const T& value)
    {
        alloc.construct(stackEndData++ , value);
    }
    void resize()
    {
        size_t newsize = std::max (2 * (stackEndData - stackData),ptrdiff_t(1));
        T* newData = alloc.allocate(newsize);
        T* newDataEnd = std::uninitialized_copy(stackData , stackEndData , newData);
        destroy();
        stackData = newData;
        stackEndData = newDataEnd;
        memlimit = stackData + newsize; 
    }
    void init (T* front , T* back)
    {
        stackData = alloc.allocate(back - front);
        stackEndData = memlimit = std::uninitialized_copy(front,back,stackData);
    }
    void init()
    {
        stackData = stackEndData = memlimit = 0;
    }
    void init(size_t NumElements , const T& initialValue)
    {
        stackData = alloc.allocate(NumElements);
        stackEndData = memlimit = stackData + NumElements;
        std::uninitialized_fill (stackData,stackEndData,initialValue);
    }
    void destroy()
    {
        if(stackData != 0)
        {
            T* it = stackEndData;
            while(it != stackData)
            {
                alloc.destroy(--it);
            }

            alloc.deallocate(stackData,memlimit - stackData);
        }
        else
        {
            stackData = memlimit = stackEndData = 0 ;
        }
        
    }
    
private: // members
    T* stackData;
    T* stackEndData;
    T* memlimit; // points to a place of one past last element. if last element is 7 then memlimit points to 8!.
    //allocator object (to allocate uninitialized places in memory / deallocate / construct / destroy / copy needs memory header to be used)
    std::allocator<T> alloc;
};




int main()
{
    
    stack<int> mystk;
    for (int i = 1 ; i<11 ; i ++)
    {
        mystk.push(i);
    }
    
    mystk.print();
    std::cout<<"stack has this no. of elements: "<<mystk.size()<<std::endl;
    std::cout<<"stack after popping: "<<std::endl;
    mystk.pop();
    mystk.print();
    std::cout<<"stack has this no. of elements: "<<mystk.size()<<std::endl;
    std::cout<<"stack has this no. of elements: "<<mystk.size()<<std::endl;
    std::cout<<"stack after popping: "<<std::endl;
    mystk.pop();
    mystk.print();
    std::cout<<"stack has this no. of elements: "<<mystk.size()<<std::endl;
    std::cout<<"stack has this no. of elements: "<<mystk.size()<<std::endl;
    std::cout<<"stack after popping: "<<std::endl;
    mystk.pop();
    mystk.print();
    std::cout<<"stack has this no. of elements: "<<mystk.size()<<std::endl;
    std::cout<<"stack has this no. of elements: "<<mystk.size()<<std::endl;
    std::cout<<"stack after popping: "<<std::endl;
    mystk.pop();
    mystk.print();
    std::cout<<"stack has this no. of elements: "<<mystk.size()<<std::endl;
    std::cout<<"stack has this no. of elements: "<<mystk.size()<<std::endl;
    std::cout<<"stack after popping: "<<std::endl;
    mystk.pop();
    mystk.print();
    std::cout<<"stack has this no. of elements: "<<mystk.size()<<std::endl;
    std::cout<<"stack has this no. of elements: "<<mystk.size()<<std::endl;
    std::cout<<"stack after popping: "<<std::endl;
    mystk.pop();
    mystk.print();
    std::cout<<"stack has this no. of elements: "<<mystk.size()<<std::endl;
    std::cout<<"stack has this no. of elements: "<<mystk.size()<<std::endl;
    std::cout<<"stack after popping: "<<std::endl;
    mystk.pop();
    mystk.print();
    std::cout<<"stack has this no. of elements: "<<mystk.size()<<std::endl;
    std::cout<<"stack has this no. of elements: "<<mystk.size()<<std::endl;
    std::cout<<"stack after popping: "<<std::endl;
    mystk.pop();
    mystk.print();
    std::cout<<"stack has this no. of elements: "<<mystk.size()<<std::endl;

    std::cout<<"is mystk empty?"<<std::endl;
    std::cout<<(mystk.empty()==1 ? "YES" : "NO")<<std::endl;

    std::cout<<"the top of the stack: " << *mystk.bottom()<<std::endl;
    std::cout<<"the bottom of the stack: "<<*mystk.top()<<std::endl;
    return 0;
}