#include <iostream>

using namespace std;

// Lo de la clase lista más bien es una implementación de una lista enlazada con iteradores
template <class T>
class Lista
{
    class Nodo;
    int size;

public:
    Lista<T>() noexcept
    {
        size = 0;
        raiz = nullptr;
    }

    int get_size()
    {
        return size;
    }

    class Iterador;
    Iterador begin()
    {
        return Iterador(raiz);
    }

    Iterador end()
    {
        return Iterador(nullptr);
    }

    void insertar(T dato)
    {
        Nodo *nuevo_nodo = nuevo(dato);
        if (!get_raiz())
        {
            get_raiz() = nuevo_nodo;
        }

        else
        {
            Nodo *itr = get_raiz();
            while (itr->next)
            {
                itr = itr->next;
            }
            itr->next = nuevo_nodo;
        }
        size++;
    }

    class Iterador
    {
    public:
        Iterador() noexcept : actual(raiz) {}

        Iterador(const Nodo *pNodo) noexcept : actual(pNodo) {}

        Iterador &operator=(Nodo *pNodo)
        {
            this->actual = pNodo;
            return *this;
        }

        // Prefix ++ overload
        Iterador &operator++()
        {
            if (actual)
                actual = actual->next;
            return *this;
        }

        Iterador operator++(int)
        {
            Iterador iterator = *this;
            ++*this;
            return iterator;
        }

        bool operator!=(const Iterador &iterator)
        {
            return actual != iterator.actual;
        }

        int operator*()
        {
            return actual->dato;
        }

    private:
        const Nodo *actual;
    };

private:
    class Nodo
    {
        T dato;
        Nodo *next;
        friend class Lista;
    };

    Nodo *&get_raiz()
    {
        return raiz;
    }

    Nodo *nuevo(T dato)
    {
        Nodo *n = new Nodo;
        n->dato = dato;
        n->next = nullptr;
        return n;
    }
    static Nodo *raiz;
};

template <class T>
class Lista<T>::Nodo *Lista<T>::raiz = nullptr;
