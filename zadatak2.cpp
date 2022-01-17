#include <iostream>
#include <initializer_list>
#include <algorithm>
#include <functional>

class mojNizInt{
    public:

        mojNizInt() : p_{new int[1]}, kapacitet_{1} {}

        mojNizInt( std::initializer_list<int> a ) : p_{new int[n_]}, n_{a.size()}, kapacitet_{n_} { std::copy(begin(a), end(a), p_); }

        mojNizInt(const mojNizInt& a) : p_{new int[kapacitet_]}, n_{a.n_}, kapacitet_{a.kapacitet_} { kopi(*this, a); }

        mojNizInt(mojNizInt&& a) : p_{a.p_}, n_{std::move(a.n_)}, kapacitet_{std::move(a.n_)} { a.p_ = nullptr; }

        mojNizInt& operator=(const mojNizInt& a) {
            p_ = new int[a.kapacitet_];
            n_ = a.n_;
            kapacitet_ = a.kapacitet_;
            kopi(*this, a);
        }

        mojNizInt& operator=(mojNizInt&& a){
            p_ = a.p_;
            n_ = a.n_;
            kapacitet_ = a.kapacitet_;
            a.p_ = nullptr;
        }

        ~mojNizInt() {delete [] p_;}
        
        int size() const {return n_;}

        int& at(int a){
            if(a>n_-1) throw std::invalid_argument{"Index is out of range"};
            auto l = p_+a;
            return *l;
        }

        int& operator[](int a){
            return at(a);
        }

        void print() {
            for(int i = 0; i < n_; ++i)
                std::cout << this->at(i) << ", ";
            std::cout << "\b\b;" << std::endl;
        }

        mojNizInt operator*(int a){
            mojNizInt temp{*this};
            auto plusplus = [a](int q){ return a*q;};
            kopi(temp, *this, plusplus);
            return std::move(temp);
        }

        mojNizInt operator+(const mojNizInt& a){
            if(n_ != a.n_) throw std::invalid_argument{"Razlicite velicine!"};
            mojNizInt temp{*this};
            for(int i = 0; i < n_; ++i)
                temp.p_[i] += a.p_[i];
            return std::move(temp); 
        }

        mojNizInt& operator++(){
            auto lamb = [](int a){ return ++a; };
            kopi(*this, *this, lamb);
        }

        mojNizInt operator++(int){
            auto lamb = [](int a){ return ++a; };
            kopi(*this, *this, lamb);
            return *this;
        }

        //kopira iz a u b po definisanoj transformaciji :
        void kopi(mojNizInt& b, const mojNizInt& a, std::function<int(int)>&& l = [](int a){ return a;}){
            size_t broj = 0;
            while(broj < b.n_ && broj < a.n_){
                b.p_[broj] = l(a.p_[broj]);
                ++broj;
            }
        }

        void push_back(int a){
            if(n_==kapacitet_) reloc(); 
            p_[n_] = a;
            ++n_;
        }

        void reloc(){
            mojNizInt temp{std::move(*this)};
            kapacitet_*=2;
            p_ = new int[kapacitet_];
            kopi(*this, temp);
        }

        void pop_back() { --n_; }

        int& front() const { return p_[0]; }
        int& back() const { return p_[n_-1]; }


    private:

        size_t n_{0};
        size_t kapacitet_{0};
        int* p_{nullptr};
};

mojNizInt foo(){
    mojNizInt a{2,4,6,8};
    return a;
}

int main(){

    mojNizInt niz{1,2,3,4,5,6};

    mojNizInt niz2{-1,-2,5,-4,-5,10};

    niz.push_back(10);
    niz2.push_back(-10);

    mojNizInt r = niz + niz2;

    ++niz2;
    niz2++;
    niz2++;

    mojNizInt o{niz};

    niz.push_back(125);
    niz.push_back(100);
    niz.push_back(976);

    niz[4] = 95;

    mojNizInt u = o*3;

    niz.print();
    o.print();
    u.print();
    r.print();
    niz2.print();

    return 0;
}