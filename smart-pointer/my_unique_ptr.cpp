#include<iostream>


using namespace std;


template<typename T>
class my_unique_ptr{

    public:
    my_unique_ptr():ptr_(nullptr){}
    my_unique_ptr(T* ptr):ptr_(ptr){}

    my_unique_ptr(const my_unique_ptr&& old){
        cleanup();

        this->ptr_ = old.ptr_;
    }
    my_unique_ptr& operator = (const my_unique_ptr&&old){
        cleanup();

        this->ptr_ = old.ptr_;
        return *this;
    }



    T* operator ->(){return ptr_;}
    T& operator *(){return *ptr_;}

    ~my_unique_ptr(){ delete ptr_;}
    
    my_unique_ptr(const my_unique_ptr& ) = delete;
    my_unique_ptr& operator = (const my_unique_ptr&) = delete;

    private:
    T *ptr_;

    void cleanup(){
        if(ptr_) delete ptr_;
        ptr_ = nullptr;
    }
};

class Test{

    public:
    Test(int data):data(data){}
    int getData(){return data;}
    void setData(int data){this->data = data;}
    private:
    int data;
};

int main(){

    my_unique_ptr<Test>up(new Test(10));

    cout<<"data is: "<<up->getData()<<endl;
    up->setData(100);
    cout<<"data is: "<<up->getData()<<endl;
    return 0;
}