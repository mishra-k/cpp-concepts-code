#include<iostream>


using namespace std;

class RC{

public:
void add_ref(){
    ++count;
}

int release_ref(){
    return --count;
}

private:
    int count;
};

template<typename T>
class my_shared_ptr{

    public:
    my_shared_ptr():ptr_(nullptr), ref_(new RC()) {
        ref_->add_ref();
    }
    my_shared_ptr(T* ptr):ptr_(ptr), ref_(new RC()){ 
        ref_->add_ref();
    }

    my_shared_ptr(const my_shared_ptr& old): ptr_(old.ptr_), ref_(old.ref_){
        
        ref_->add_ref(); 
    }

    my_shared_ptr& operator = (const my_shared_ptr&old){

        if(this != &old){
            cleanup();

            this->ptr_ = old->ptr_;
            this->ref_ = old->ref_;

            ref_->add_ref();
        }

        return *this;

    }

    T* operator ->(){return ptr_;}
    T& operator *(){return *ptr_;}

    ~my_shared_ptr(){ 
        
        cleanup();
    }
    
    private:
    T *ptr_;
    RC *ref_;

    void cleanup(){
        if(ref_->release_ref() == 0){
            delete ptr_;
            delete ref_;
        }
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

    my_shared_ptr<Test>up(new Test(10));

    //scoped block to show the ref is working
    {
        my_shared_ptr<Test>sp_2 = up;
        sp_2->setData(120);
    }
    cout<<"data is: "<<up->getData()<<endl;
    up->setData(100);
    cout<<"data is: "<<up->getData()<<endl;
    return 0;
}