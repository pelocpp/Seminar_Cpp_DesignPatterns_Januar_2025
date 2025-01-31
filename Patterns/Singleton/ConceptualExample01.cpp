// ===========================================================================
// ConceptualExample01.cpp
// ===========================================================================

#include <iostream>
#include <thread>
#include <mutex>

namespace ConceptualExample01 {

    class Singleton final
    {
    private:
        static Singleton* m_instance;
        static std::mutex m_mutex;

    private:
        Singleton() = default;

        // no copying
        Singleton(const Singleton&) = delete;
        Singleton& operator=(const Singleton&) = delete;

        // no moving
        Singleton(Singleton&&) noexcept = delete;
        Singleton& operator=(Singleton&&) noexcept = delete;

    public:
        static Singleton* getInstance()   // easy
        {
            if (m_instance == nullptr) {
                m_instance = new Singleton{};   // Heap
            }

            return m_instance;
        }

        static Singleton* getInstanceThreadSafe()
        {
            // klassisch
            m_mutex.lock();

            if (m_instance == nullptr) {
                // thread wechsel
                m_instance = new Singleton{};  // std::bad_alloc
            }
            
            m_mutex.unlock();

            // versus

            {
                // Sperre   // RAII Idiom  // Hüllenobjekt
                std::lock_guard<std::mutex> lock{ m_mutex };  // .lock()

                if (m_instance == nullptr) {
                    // thread wechsel
                    m_instance = new Singleton{};
                }
            }   // mutex.unlock();

            return m_instance;
        }

        static Singleton* getInstanceThreadSafe_Cpp17()
        {
            if (std::lock_guard<std::mutex> lock{ m_mutex }; m_instance == nullptr) {
                m_instance = new Singleton{};
            }

            return m_instance;
        }

        void doThis() const
        {
            std::cout << "doing this on singleton instance (" << this << ")." << std::endl;
        }

        void doThat() const
        {
            std::cout << "doing that on singleton instance (" << this << ")." << std::endl;
        }
    };

    Singleton* Singleton::m_instance{ nullptr };
    std::mutex Singleton::m_mutex{};
}

void test_singleton_01()
{
    using namespace ConceptualExample01;

    Singleton::getInstance()->doThis();
    Singleton::getInstance()->doThat();
}

void test_singleton_02()
{
    using namespace ConceptualExample01;

    auto singleton1 { Singleton::getInstance() };
    auto singleton2 { Singleton::getInstance() };

    std::cout << std::boolalpha << (singleton1 == singleton2) << std::endl;

    auto singleton3 { Singleton::getInstanceThreadSafe() };
    auto singleton4 { Singleton::getInstanceThreadSafe() };

    std::cout << std::boolalpha << (singleton3 == singleton4) << std::endl;
}

// ===========================================================================
// End-of-File
// ===========================================================================
