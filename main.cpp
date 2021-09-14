#include <iostream>
#include <vector>
#include <memory>
#include <typeinfo>
#include <cxxabi.h>
#include <glog/logging.h>
using namespace std;

/**
 *
 */

class TypeName{
public:
    template<class T>
            TypeName(T const t):real_name(
                    abi::__cxa_demangle(typeid(T).name(),0,0,&status)
                    )
    {
                DLOG(INFO)<< " real name: "<<real_name<<endl;
    }
    ~TypeName(){
        free(real_name);
    }

private:
    int status;
    char* real_name;
#define TypeName(i) TypeName(std::move(i));
};

void ArrayCopy(std::vector<double>& t){
    DLOG(INFO)<<"ArrayCopy: "<<t.at(0)<<std::endl;

}

void Test(const shared_ptr<std::vector<std::vector<int>>>& p){
    DLOG(INFO)<<" p address: "<<p.get() << " p count "<<p.use_count()<< endl;
    p->at(0)[0] = 8888;
    DLOG(INFO)<<" p address "<<p.get()<<endl;

}
shared_ptr<std::vector<std::vector<double>>> Test(shared_ptr<std::vector<std::vector<double>>>& p){
    DLOG(INFO)<<" p address: "<<p.get() << " p count "<<p.use_count()<< endl;
    p->at(0)[0] = 8888;
    DLOG(INFO)<<" p address "<<p.get()<<endl;

    return p;

}
int main(int argc, char *argv[]) {
    google::InitGoogleLogging(argv[0]);
    FLAGS_logtostderr = true;
    FLAGS_colorlogtostderr = true;

#if 0
    const int N = 2;
    const int M = 3;
    const int K = 99;

    shared_ptr<std::vector<double>> p1 = nullptr;
    shared_ptr<std::vector<std::vector<double>>> p2 = nullptr;
    shared_ptr<std::vector<std::vector<double>>> p3  =nullptr;

    p1 = shared_ptr<std::vector<double>>(new std::vector<double>(M));
    p2 = shared_ptr<std::vector<std::vector<double>>>(new std::vector<std::vector<double>>(M,std::vector<double>(N,K)));
    DLOG(INFO)<< " p1 length: "<<p1->size()<<endl;
    DLOG(INFO)<< " p2 Raw length: "<<p2->size()<<endl;
    DLOG(INFO)<< " p2 Col length: "<<(*p2)[0].size()<<endl;

    DLOG(INFO)<< " p2 address: "<<p2.get()<< " p2 count: "<<p2.use_count()<<endl;
    DLOG(INFO)<< " p3 address: "<<p3.get()<< " p3 count: "<<p3.use_count()<<endl;

    p2->at(0)[0] = 77;
    DLOG(INFO)<< "p2->at(0)[0]: "<<p2->at(0)[0]<<endl;
    ArrayCopy(p2->at(0));
#else
    const int N  = 2;
    const int M  = 4;
    const int K  = 99;

    std::vector<std::vector<int>>* p = new std::vector<std::vector<int>>(M,std::vector<int>(N,K));
    shared_ptr<std::vector<std::vector<int>>> p1(new std::vector<std::vector<int>>(M,std::vector<int>(N,0)));
    std::shared_ptr<int> p3 = std::shared_ptr<int>(new int);

    shared_ptr<std::vector<std::vector<int>>> p2 = nullptr;
    p2 = shared_ptr<std::vector<std::vector<int>>>(new std::vector<std::vector<int>>(M,std::vector<int>(N,0)));

    DLOG(INFO)<< " p[0].size(): " <<p[0].size()<<endl;
    DLOG(INFO)<< " p[0][0].size(): "<<p[0][0].size()<<endl;
    DLOG(INFO)<< " p->at(0)[0]: "<<p->at(0)[0]<<endl;

    DLOG(INFO)<< " p1->size: "<<p1->size()<<endl;
    DLOG(INFO)<< "(*p1)[0].size(): "<<(*p1)[0].size()<<endl;
    (*p)[0].push_back(100);

    DLOG(INFO)<<" p1 address "<<p1.get()<<endl;
    DLOG(INFO)<< " test[+++] "<<p1->at(0)[0]<<endl;
    Test(p1);
    DLOG(INFO)<<" test[---] "<<p1->at(0)[0]<<endl;

    delete p;

#endif

    return 0;
}
