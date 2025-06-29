#ifndef IOOBJECT_H
#define IOOBJECT_H


class IObject
{
    public:
        virtual void Draw()=0;
        virtual void Update(float dt)=0;
        virtual void Clean()=0;
};

#endif // IOOBJECT_H
