#include <iostream>
#include <initializer_list>
#include <algorithm>
#include <functional>

template<typename T>
class mojNiz{
    public:
        template<typename Other>
        friend class mojNiz;

        mojNiz() : p_{new T[1]}, kapacitet_{1} {}

        mojNiz( std::initializer_list<T> a ) : p_{new T[n_]}, n_{a.size()}, kapacitet_{n_} { std::copy(begin(a), end(a), p_); }

        mojNiz(const mojNiz<T>& a) : p_{new T[kapacitet_]}, n_{a.n_}, kapacitet_{a.kapacitet_} { 
            kopi(*this, a);
        }

        mojNiz(mojNiz&& a) : p_{a.p_}, n_{std::move(a.n_)}, kapacitet_{std::move(a.n_)} { a.p_ = nullptr; }

        template<typename o>
        mojNiz& operator=(const o& a) {
            delete [] p_;
            p_ = new T[a.kapacitet_];
            n_ = a.n_;
            kapacitet_ = a.kapacitet_;
            kopi(*this, a);
            int broj = 0;
            return *this;
        }

        mojNiz& operator=(const mojNiz<T>& a) {
            if( this == &a )
                return *this;
            delete [] p_;
            p_ = new T[a.kapacitet_];
            n_ = a.n_;
            kapacitet_ = a.kapacitet_;
            kopi(*this, a);
            return *this;
        }

        mojNiz& operator=(mojNiz<T>&& a){
            if( this == &a )
                return *this;
            delete [] p_;
            p_ = a.p_;
            n_ = a.n_;
            kapacitet_ = a.kapacitet_;
            a.p_ = nullptr;
            return *this;
        }

        ~mojNiz() {delete [] p_;}
        
        int size() const {return n_;}

        T& at(int a){
            if(a>n_-1) throw std::invalid_argument{"Index is out of range"};
            auto l = p_+a;
            return *l;
        }

        T& operator[](T a){
            return at(a);
        }

        void print() {
            for(T i = 0; i < n_; ++i)
                std::cout << this->at(i) << ", ";
            std::cout << "\b\b;" << std::endl;
        }

        mojNiz operator*(int a){
            mojNiz temp = *this ;
            for( int i = 0; i < temp.n_; ++i )
                temp.p_[i] = p_[i]*a;
            return temp;
        }

        template <typename u>
        mojNiz operator+(const u& a){
            mojNiz<T> temp{*this};
            if(temp.n_ != a.n_) throw std::invalid_argument{"Razlicite velicine!"};
            for(int i = 0; i < n_; ++i){
                temp.p_[i] = p_[i] + a.p_[i];
            }
            return temp;
        }

        mojNiz& operator++(){
            auto lamb = [](T a){ return ++a; };
            kopi(*this, *this, lamb);
            return *this;
        }

        mojNiz operator++(int){
            auto lamb = [](T a){ return ++a; };
            kopi(*this, *this, lamb);
            return *this;
        }

        //kopira iz a u b po definisanoj transformaciji :
        template<typename c1, typename c2>
        void kopi(c1& b, const c2& a, std::function<T(T)>&& l = [](T a){ return a;}){
            size_t broj = 0;
            while(broj < b.n_ && broj < a.n_){
                b.p_[broj] = l(a.p_[broj]);
                ++broj;
            }
        }

        void push_back(T a){
            if(n_==kapacitet_) reloc();
            p_[n_] = a;
            ++n_;
        }

        void reloc(){
            mojNiz temp{*this};
            kapacitet_*=2;
            delete [] p_;
            p_ = new T[kapacitet_];
            kopi(*this, temp);
        }

        void pop_back() { --n_; }

        T& front() const { return p_[0]; }
        T& back() const { return p_[n_-1]; }

    private:
        size_t n_{0};
        size_t kapacitet_{0};
        T* p_{nullptr};
};

mojNiz<int> foo(){
    mojNiz<int> a{2,4,6,8};
    return a;
}

int main(){

    mojNiz<int> nizi{5,5,5,5,5};
    mojNiz<double> nizd{5.0,5.1,5.2,5.3,5.4};
    mojNiz<double> niz{1.2,2.5,3.0,4.05,5.1,6.2};
    mojNiz<double> niz2{-1.7,-2.64,5.0,-4.0,-5.0,10.0};

    mojNiz<double> r; 
    r = nizd + nizi;

    // r.push_back(128);

    // r = niz;

    niz.push_back(512);

    niz2.push_back(10.5);
    niz2.push_back(50.2);

    // niz.push_back(10);
    // niz2.push_back(-10);

    // ++niz2;
    // niz[4] = 95;

    std::cout << "niz:\t\t"; niz.print();
    std::cout << "niz2:\t\t"; niz2.print();
    std::cout << "r:\t\t"; r.print();

    // mojNiz<double> k1; k1 = foo();
    // mojNiz<double> k2; k1 = foo();
    // mojNiz<double> k3; k3 = foo();

    // mojNiz<char> nizChar{'c', 'b', 'a'};
    // mojNiz<int> nizInt{1,2,3,4,5};
    // mojNiz<int> ll{3,-2,9,-1,0};
    // mojNiz<double> nizDouble{1.1,2.2,3.3,4.4,5.5};

    // nizInt = nizDouble;

    // nizDouble.push_back(20.3);
    // nizDouble.push_back(11);

    // nizInt = ll*3;

    // mojNiz<double> dd; dd = nizDouble*3;
    // nizDouble = dd*3;


    // nizInt.push_back(1);

    // std::cout << "nizInt:\t\t"; nizInt.print();
    // std::cout << "nizDouble:\t"; nizDouble.print();
    // std::cout << "nizDouble2:\t"; dd.print();
    // std::cout << "nizInt2:\t"; ll.print();
    // std::cout << "nizChar:\t"; nizChar.print();
    
    // return 0;
}