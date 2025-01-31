// ===========================================================================
// Program.cpp // std::variant
// ===========================================================================

// function prototypes
void main_variant();


class A
{
public:
    void func() {};
};

class Base
{
public:
    virtual void func() {};
};

class Derived : public Base
{
public:
    virtual void func() override {};
};

static void frage()
{
    A a;
    a.func();

    Base *bp;
    bp = new Derived();
    bp ->func();
}

int main()
{
    frage();
    main_variant();
    return 0;
}

// ===========================================================================
// End-of-File
// ===========================================================================
