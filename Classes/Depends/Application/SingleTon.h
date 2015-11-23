
#ifndef __SingleTon__
#define __SingleTon__


//模板单例基类
template<class T>
class SingleTon
{
public:
    virtual ~SingleTon()
    {
    }
    static T* getInstance()
    {
        static T instance;
        return &instance;
    }
};
#endif /* defined(__SingleTon__) */
