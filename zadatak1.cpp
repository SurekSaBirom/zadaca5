#include <iostream>
#include <initializer_list>
#include <algorithm>
#include <functional>

class mojNizInt{
    public:

        mojNizInt() : p_{nullptr} {}

        mojNizInt( std::initializer_list<int> a ) : p_{new int[n_]}, n_{a.size()} { std::copy(begin(a), end(a), p_); }

        mojNizInt(const mojNizInt& a) : p_{new int[a.n_]}, n_{a.n_} { kopi(a); }

        mojNizInt(mojNizInt&& a) : p_{a.p_}, n_{std::move(a.n_)} { a.p_ = nullptr; }

        mojNizInt& operator=(const mojNizInt& a) {
            p_ = new int[a.n_];
            n_ = a.n_;
            kopi(a);
        }

        mojNizInt& operator=(mojNizInt&& a){
            p_ = a.p_;
            n_ = a.n_;
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

        void kopi(const mojNizInt& a){ // kopira drugi niz u trenutni
            auto nista = [](int a){ return a;};
            transform(*this, a, nista);
        }

        mojNizInt operator*(int a){
            mojNizInt temp{*this};
            auto plusplus = [a](int q){ return a*q;};
            transform(temp, *this, plusplus);
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
            transform(*this, *this, lamb);
        }

        mojNizInt operator++(int){
            auto lamb = [](int a){ return ++a; };
            transform(*this, *this, lamb);
            return *this;
        }

        void push_back(int a){
            ++n_;
            auto temp = new int[n_];
            for(int i = 0; i < n_-1; ++i)
                temp[i] = p_[i];
            temp[n_-1] = a;
            delete [] p_;
            p_ = temp;
        }

    private:

        //kopira iz a u b po definisanoj transformaciji : 
        void transform(mojNizInt& b, const mojNizInt& a, std::function<int(int)>&& l){
            size_t broj = 0;
            while(broj < b.n_ && broj < a.n_){
                b.p_[broj] = l(a.p_[broj]);
                ++broj;
            }
        }

        size_t n_{0};
        int* p_{nullptr};
};

mojNizInt foo(){
    mojNizInt a{2,4,6,8};
    return a;
}

int main(){

    mojNizInt niz{1,2,3,4,5,6};
    mojNizInt niz2{-1,-2,5,-4,-5,10};

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