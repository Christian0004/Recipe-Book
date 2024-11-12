#ifndef SLLIST_HPP
#define SLLIST_HPP

template <class T>
class SLList {
    class Node;

    public:

        typedef Node* Position;

        class Exception : public std::exception {
            private:
            std::string msg;

            public:
                Exception() noexcept : msg("Error indefinido") {}
                Exception(const Exception& ex) noexcept : msg(ex.msg) {}
                Exception(const std::string& m) : msg(m) {}
                Exception& operator=(const Exception& ex) noexcept {
                    msg = ex.msg;
                    return *this;
                }
                virtual ~Exception() {}
                virtual const char* what() const noexcept { return msg.c_str(); }
        };

        SLList();
        SLList(const SLList&);

        ~SLList();

        void initialize();

        bool isEmpty() const;

        void insertData(const Position&, const T&);

        void deleteData(Position&);

        Position getFirstPos() const;
        Position getLastPos() const;
        Position getPrevPos(Position&) const;
        Position getNextPos(Position&) const;

        Position findData(const T&) const;

        T retrieve(Position&) const;

        std::string toString() const;

        void deleteAll();

        SLList<T>& operator = (const SLList&);

        Position getIndex(const int&) const;

        Position linealSearch(T&, int(const T&, const T&));

        void quickSort(int(const T&, const T&));
        void quickSort(const Position&, const Position&, int(const T&, const T&));

    private:

        class Node {

            public:

                class Exception : public SLList::Exception {
                    public:
                        using SLList::Exception::Exception;
                };

                Node();
                Node(const T&);

                T* getDataPtr();
                T& getData() const;
                Position& getNext();

                void setDataPtr(T*);
                void setData(const T&);
                void setNext(const Position&);

            private:

                T* dataPtr;
                Position next;
        };

        Position anchor;

        void copyAll(const SLList&);

        bool isValidPos(const Position&) const;

        void swapPtr(const Position&, const Position&);

};

//Implementacion

using namespace std;

//Nodo

template<class T>
SLList<T>::Node::Node(): dataPtr(nullptr), next(nullptr) { }

template<class T>
SLList<T>::Node::Node(const T& e) : dataPtr(new T(e)), next(nullptr) {
    if (dataPtr == nullptr) {
        throw Exception("Memoria no disponible");
    }
}

template<class T>
T* SLList<T>::Node::getDataPtr() {
    return dataPtr;
}

template<class T>
T& SLList<T>::Node::getData() const {
    return *dataPtr;
}

template<class T>
typename SLList<T>::Position& SLList<T>::Node::getNext() {
    return next;
}

template<class T>
void SLList<T>::Node::setDataPtr(T* p) {
    dataPtr = p;
}

template<class T>
void SLList<T>::Node::setData(const T& e) {
    if (dataPtr == nullptr) {
        if (dataPtr = new T(e) == nullptr) {
            throw Exception("Memoria no disponible");
        }
    } else {
        *dataPtr = e;
    }
}

template<class T>
void SLList<T>::Node::setNext(const Position& p) {
    next = p;
}

//Lista

template <class T>
void SLList<T>::copyAll(const SLList& l) {

    Position aux(l.anchor);
    Position lastInserted(nullptr);
    Position newNode;

    while(aux != nullptr){

        if ((newNode = new Node(aux->getData())) == nullptr) {
            throw Exception("Memoria no disponible");
        }
        if(lastInserted == nullptr){
            anchor = newNode;
        }
        else{
            lastInserted->setNext(newNode);
        }

        lastInserted = newNode;

        aux = aux->getNext();
    }

}

template <class T>
bool SLList<T>::isValidPos(const Position& p) const {

    Position aux(anchor);

    while(aux != nullptr){
        if(aux == p){
            return true;
        }
        aux = aux->getNext();
    }
    return false;
}

template <class T>
void SLList<T>::swapPtr(const Position& a, const Position& b) {

    if (a != b) {
        T* aux(a->getDataPtr());
        a->setDataPtr(b->getDataPtr());
        b->setDataPtr(aux);
    }
}

template <class T>
SLList<T>::SLList() : anchor(nullptr) { }

template <class T>
SLList<T>::SLList(const SLList& l) : SLList() {
    copyAll(l);
}

template <class T>
SLList<T>::~SLList() {

    deleteAll();

    delete anchor;
}

template <class T>
void SLList<T>::initialize() {

    anchor = nullptr;
}

template <class T>
bool SLList<T>::isEmpty() const {

    return this->anchor == nullptr;
}

template <class T>
void SLList<T>::insertData(const Position& p, const T& e) {

    if(p != nullptr and !isValidPos(p)) {
        throw Exception("Posicion invalida, insertData");
    }

    Position aux(new Node(e));

    if(aux == nullptr){
        throw Exception("Memoria no disponible, insertData");
    }

    if(p == nullptr){ //Al principio
        aux->setNext(anchor);
        anchor = aux;
    }
    else{
        aux->setNext(p->getNext());
        p->setNext(aux);
    }
}

template <class T>
void SLList<T>::deleteData(Position& p) {

    if(!isValidPos(p)) {
        throw Exception("Posicion invalida, deleteData");
    }

    if(p == anchor) {
        anchor = p->getNext();
    }
    else {
        getPrevPos(p)->setNext(p->getNext());
    }
}

template <class T>
typename SLList<T>::Position SLList<T>::getFirstPos() const {
    return anchor;
}

template <class T>
typename SLList<T>::Position SLList<T>::getLastPos() const {

    if(isEmpty()){
        return nullptr;
    }

    Position aux(anchor);

    while(aux->getNext() != nullptr){
        aux = aux->getNext();
    }

    return aux;

}

template <class T>
typename SLList<T>::Position SLList<T>::getPrevPos(Position& p) const {

    if(isEmpty() or p == anchor){
        return nullptr;
    }

    Position aux(anchor);

    while(aux != nullptr and aux->getNext() != p){
        aux = aux->getNext();
    }

    return aux;
}

template <class T>
typename SLList<T>::Position SLList<T>::getNextPos(Position& p) const {

    if(!isValidPos(p)){
        return nullptr;
    }
    return p->getNext();
}

template <class T>
typename SLList<T>::Position SLList<T>::findData(const T& e) const {

    Position aux(anchor);

    while(aux != nullptr and aux->getData() != e){
        aux = aux->getNext();
    }
    return aux;
}

template <class T>
T SLList<T>::retrieve(Position& p) const {

    if(!isValidPos(p)){
        throw Exception("Posicion invalida, retrieve");
    }
    return p->getData();
}

template <class T>
string SLList<T>::toString() const {

    string result;

    Position aux(anchor);

    while(aux != nullptr) {
        result += aux->getData().toString();

        aux = aux->getNext();
    }

    return result;
}

template <class T>
void SLList<T>::deleteAll() {

    Position aux;

    while(anchor != nullptr){
        aux = anchor;

        anchor = anchor->getNext();

        delete aux;
    }
}

template <class T>
SLList<T>& SLList<T>::operator = (const SLList& l) {
    deleteAll();

    copyAll(l);

    return *this;
}

template <class T>
typename SLList<T>::Position SLList<T>::getIndex(const int& i) const {

    if (i < 0){
        throw Exception("Indice invalido, getIndex");
    }

    Position aux(anchor);
    int j = 0;

    while (aux != nullptr and j < i) {
        aux = aux->getNext();
        j++;
    }

    if (i != j) {
        throw Exception("Indice invalido, getIndex");
    }

    return aux;
}

template <class T>
typename SLList<T>::Position SLList<T>::linealSearch(T& e, int comp(const T&, const T&)) {

    Position aux(anchor);

    while (aux != nullptr) {

        if (comp(e, aux->getData()) == 0) {
            return aux;
        }

        aux = aux->getNext();
    }

    return nullptr;
}

template <class T>
void SLList<T>::quickSort(int comp(const T&, const T&)) {

    if(isEmpty()){
        return;
    }

    quickSort(anchor, getLastPos(), comp);
}

template <class T>
void SLList<T>::quickSort(const Position& leftEdge, const Position& rightEdge, int comp(const T&, const T&)) {

    if (leftEdge == rightEdge) {
        return;
    }

    if(leftEdge == nullptr or rightEdge == nullptr){
        return;
    }

    if (leftEdge->getNext() == rightEdge) {

        if (comp(leftEdge->getData(), rightEdge->getData()) == 1) {
            swapPtr(leftEdge, rightEdge);
        }

        return;
    }

    Position i(leftEdge), j(rightEdge);

    while (i != j) {

        while (i != j and comp(i->getData(), rightEdge->getData()) <= 0) {
            i = i->getNext();
        }

        while (i != j and comp(j->getData(), rightEdge->getData()) >= 0) {
            j = getPrevPos(j);
        }

        swapPtr(i, j);
    }

    swapPtr(i, rightEdge);

    if (i != leftEdge) {
        quickSort(leftEdge, getPrevPos(i), comp);
    }

    if (i != rightEdge) {
        quickSort(i->getNext(), rightEdge, comp);
    }
}

#endif // SLLIST_HPP
