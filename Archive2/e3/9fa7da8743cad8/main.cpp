#include <iostream>
#include <memory>
#include <cstring>
#include <string>
#include <sstream>
#include <stdint.h>
#include <map>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <atomic>
#include <map>
#include <vector>
#include <functional>
#include <string>
#include <algorithm>

namespace {
    template<class T, class Expected>
    using FailTest = typename std::enable_if<!std::is_convertible<T*, Expected*>::value>::type;

    template<class T, class Expected>
    using PassTest = typename std::enable_if<std::is_convertible<T*, Expected*>::value>::type;
    
    class PreUpdateService { 
    public:
        virtual ~PreUpdateService() = 0;
        virtual void OnPreUpdate() = 0;
    };
    PreUpdateService::~PreUpdateService() { }

    class PostUpdateService { 
    public:
        virtual ~PostUpdateService() = 0;
        virtual void OnPostUpdate() = 0;
    };
    PostUpdateService::~PostUpdateService() { }

    class Service {
    public:
        virtual ~Service() = 0;
    };
    Service::~Service() { }

    class BothService : public Service, public PreUpdateService, public PostUpdateService {
    public:
        BothService() { }
        ~BothService() { std::cout << "~BothService()" << std::endl; }

        void OnPreUpdate() { std::cout << "BothService::OnPreUpdate()\n"; }
        void OnPostUpdate() { std::cout << "BothService::OnPostUpdate()\n"; }
    };
    
    class PreService : public Service, public PreUpdateService {
    public:
        PreService() { }
        ~PreService() { std::cout << "~PreService()" << std::endl; }

        void OnPreUpdate() { std::cout << "PreService::OnPreUpdate()\n"; }
    };
    
    class PostService : public Service, public PostUpdateService {
    public:
        PostService() { }
        ~PostService() { std::cout << "~PostService()" << std::endl; }

        void OnPostUpdate() { std::cout << "PostService::OnPostUpdate()\n"; }
    };
    
    class Services {
    public: 
        Services() { }
        ~Services() { }
        
        template<class T, class...Args>
        T* AddService(const std::string& serviceId, Args...params) {
            static_assert(std::is_convertible<T*, Service*>::value, "AddService parameter must implement Service");
            
            if (HasService(serviceId)) {
                return nullptr;
            }
    
            T* service = new T(std::forward<Args>(params)...);
            PutService(serviceId, service);
            
            /*
            if (std::is_convertible<T*, PreUpdateService*>::value) {
                AddPreUpdateService(service);
            }
            if (std::is_convertible<T*, PostUpdateService*>::value) {
                AddPostUpdateService(service);
            }
            */
            PreAdd(service);
            //AddPre(service);
            //AddPost(service);
            //if (std::is_convertible<T*,)
    
            return service;
        }
        
        void DispatchPre() {
            for (PreUpdateService* s : mPreUpdateServices) {
                s->OnPreUpdate();
            }
        }
        
        void DispatchPost() {
            for (PostUpdateService* s : mPostUpdateServices) {
                s->OnPostUpdate();
            }
        }
        
    private:
        std::unordered_map<std::string, Service*> mServices;

        std::vector<PreUpdateService*> mPreUpdateServices;
        std::vector<PostUpdateService*> mPostUpdateServices;
        
        bool HasService(const std::string& id) {
            return mServices.find(id) != mServices.end();
        }
        
        void PutService(const std::string& id, Service* s) {
            mServices[id] = s;
        }
        
        template<class T, FailTest<T, PreUpdateService>* = nullptr>
        void PreAdd(T* s) {
            std::cout << "!Pre" << std::endl;
        }
 
        template<class T, class = PassTest<T, PreUpdateService>>
        void PreAdd(T* s) {
            mPreUpdateServices.push_back(static_cast<PreUpdateService*>(s));
        }
        
        /*
        template<class T, bool A = std::is_convertible<T*, PreUpdateService*>::value> 
        struct PreAdd { 
            static void Add(T* s) { } 
        };
        
        template<class T> 
        struct PreAdd<T, true> { 
            static void Add(T* s) { 
                mPreUpdateServices.push_back(static_cast<PreUpdateService*>(s)); 
            } 
        };
        */
    };
        
};

int main(int argc, const char* argv[]) {
    Services* services = new Services();
    
    BothService* both = services->AddService<BothService>("both");
    PreService* pre = services->AddService<PreService>("pre");
    PostService* post = services->AddService<PostService>("post");
    
    services->DispatchPre();
    services->DispatchPost();
    
    return 0;
}