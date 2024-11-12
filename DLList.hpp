#ifndef DLLIST_HPP
#define DLLIST_HPP

#include <fstream>
#include <iostream>

template <class T>
class DLList {
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

    private:
        class Node {
            private:
                T* dataPtr;
                Position prev;
                Position next;

        public:
            class Exception : public DLList::Exception {
                public:
                    using DLList::Exception::Exception;
            };
        Node();
        Node(const T&);

        T* getDataPtr();
        T getData() const;
        Position getPrev() const;
        Position getNext() const;

        void setDataPtr(T*);
        void setData(const T&);
        void setPrev(const Position&);
        void setNext(const Position&);
  };

    Position header;

    void copyAll(const DLList&);

    bool isValidPos(Position) const;

    void swapPtr(const Position&, const Position&);

    public:

        DLList();
        DLList(const DLList&);

        ~DLList();

        bool isEmpty() const;

        void insertData(const Position&, const T&);

        void deleteData(Position);

        Position getFirstPos() const;
        Position getLastPos() const;
        Position getPrevPos(const Position&) const;
        Position getNextPos(const Position&) const;

        Position findData(const T&);

        T retrieve(const Position&) const;

        std::string toString() const;

        void deleteAll();

        DLList& operator=(const DLList&);

        Position getIndex(const int&);

        Position linealSearch(T&, int(const T&, const T&));

        void quickSort(int(const T&, const T&));
        void quickSort(const Position&, const Position&, int(const T&, const T&));

        void writeToDisk(const std::string&);
        void readFromDisk(const std::string&);
};

// IMPLEMENTACION

using namespace std;

// NODE *******************************************

template <class T>
DLList<T>::Node::Node() : dataPtr(nullptr), prev(nullptr), next(nullptr) {}

template <class T>
DLList<T>::Node::Node(const T& e): dataPtr(new T(e)), prev(nullptr), next(nullptr) {

    if (dataPtr == nullptr) {
        throw Exception("Memoria no disponible");
    }
}

template <class T>
T* DLList<T>::Node::getDataPtr() {
    return dataPtr;
}

template <class T>
T DLList<T>::Node::getData() const {
    return *dataPtr;
}

template <class T>
typename DLList<T>::Position DLList<T>::Node::getPrev() const {
    return prev;
}

template <class T>
typename DLList<T>::Position DLList<T>::Node::getNext() const {
    return next;
}

template <class T>
void DLList<T>::Node::setDataPtr(T* p) {
    dataPtr = p;
}

template <class T>
void DLList<T>::Node::setData(const T& e) {

    if (dataPtr == nullptr) {
        if ((dataPtr = new T(e)) == nullptr) {
            throw Exception("Memoria no disponible");
        };
    } else {
        *dataPtr = e;
    }
}

template <class T>
void DLList<T>::Node::setPrev(const Position& p) {
    prev = p;
}

template <class T>
void DLList<T>::Node::setNext(const Position& p) {
    next = p;
}

// LIST *********************************************

template <class T>
void DLList<T>::copyAll(const DLList& l) {

    Position aux(l.header->getNext()), newNode;

    while (aux != l.header) {
        try {
            if ((newNode = new Node(aux->getData())) == nullptr) {
                throw Exception("Memoria no disponible");
            }
        } catch (const typename Node::Exception& ex) {
            throw Exception(ex.what());
        }

        newNode->setPrev(header->getPrev());
        newNode->setNext(header);

        header->getPrev()->setNext(newNode);
        header->setPrev(newNode);

        aux = aux->getNext();
    }
}

template <class T>
bool DLList<T>::isValidPos(Position p) const {

    Position aux(header->getNext());

    while (aux != header) {

        if (aux == p) {
            return true;
        }

        aux = aux->getNext();
    }

    return false;
}

template <class T>
void DLList<T>::swapPtr(const Position& a, const Position& b) {

    if (a != b) {
        T* aux(a->getDataPtr());
        a->setDataPtr(b->getDataPtr());
        b->setDataPtr(aux);
    }
}

template <class T>
DLList<T>::DLList() : header(new Node) {

    if (header == nullptr) {
        throw Exception("Memoria no disponible");
    }

    header->setPrev(header);
    header->setNext(header);
}

template <class T>
DLList<T>::DLList(const DLList& l) : DLList() {
    copyAll(l);
}

template <class T>
DLList<T>::~DLList() {

    deleteAll();

    delete header;
}

template <class T>
bool DLList<T>::isEmpty() const {
    return header->getNext() == header;
}

template <class T>
void DLList<T>::insertData(const Position& p, const T& e) {

    if (p != nullptr and !isValidPos(p)) {
        throw Exception("Posicion invalida, insertData");
    }

    Position aux;

    try {
        aux = new Node(e);
    } catch (const typename Node::Exception& ex) {
        throw Exception(ex.what());
    }

    if (aux == nullptr) {
        throw Exception("Memoria no disponible, insertData");
    }

    Position insPos(p == nullptr ? header : p);

    aux->setPrev(insPos);
    aux->setNext(insPos->getNext());

    insPos->getNext()->setPrev(aux);
    insPos->setNext(aux);
}

template <class T>
void DLList<T>::deleteData(Position p) {

    if (!isValidPos(p)) {
        throw Exception("Posicion invalida, deleteData");
    }

    p->getPrev()->setNext(p->getNext());
    p->getNext()->setPrev(p->getPrev());

    delete p;
}

template <class T>
typename DLList<T>::Position DLList<T>::getFirstPos() const {

    if (isEmpty()) {
        return nullptr;
    }

    return header->getNext();
}

template <class T>
typename DLList<T>::Position DLList<T>::getLastPos() const {

    if (isEmpty()) {
        return nullptr;
    }

    return header->getPrev();
}

template <class T>
typename DLList<T>::Position DLList<T>::getPrevPos(const Position& p) const {

    if (p == header->getNext() and !isValidPos(p)) {
        return nullptr;
    }

    return p->getPrev();
}

template <class T>
typename DLList<T>::Position DLList<T>::getNextPos(const Position& p) const {

    if (p == header->getPrev() || !isValidPos(p)) {
        return nullptr;
    }

    return p->getNext();
}

template <class T>
typename DLList<T>::Position DLList<T>::findData(const T& e) {

    Position aux(header->getNext());

    while (aux != header) {
        if (e == aux->getData()) {
            return aux;
    }

    aux = aux->getNext();
  }

  return nullptr;
}

template <class T>
T DLList<T>::retrieve(const Position& p) const {

    if (!isValidPos(p)) {
        throw Exception("Posicion invalida, retrieve");
    }

    return p->getData();
}

template <class T>
string DLList<T>::toString() const {

    string result;

    Position aux(header->getNext());

    while (aux != header) {
        result += aux->getData().toString() + '\n';
        aux = aux->getNext();
    }

    return result;
}

template <class T>
void DLList<T>::deleteAll() {

    Position aux;

    while (header->getNext() != header) {
        aux = header->getNext();
        header->setNext(aux->getNext());
        delete aux;
    }

    header->setPrev(header);
}

template <class T>
DLList<T>& DLList<T>::operator=(const DLList& l) {

    deleteAll();
    copyAll(l);
    return *this;
}

template <class T>
typename DLList<T>::Position DLList<T>::getIndex(const int& i) {

    if (i < 0){
        throw Exception("Indice invalido, getIndex");
    }

    Position aux = getFirstPos();
    int j = 0;

    while (aux != nullptr and j < i) {
        aux = aux->getNext();
        j++;
    }

    if (aux == nullptr) {
        throw Exception("Indice invalido, getIndex");
    }

    return aux;
}

template <class T>
typename DLList<T>::Position DLList<T>::linealSearch(T& e, int comp(const T&, const T&)) {

    Position aux(header->getNext());

    while (aux != header) {

        if (comp(e, aux->getData()) == 0) {
            return aux;
        }

        aux = aux->getNext();
    }

    return nullptr;
}


template <class T>
void DLList<T>::quickSort(int comp(const T&, const T&)) {
    quickSort(header->getNext(), header->getPrev(), comp);
}

template <class T>
void DLList<T>::quickSort(const Position& leftEdge, const Position& rightEdge, int comp(const T&, const T&)) {

    if (leftEdge == rightEdge) {
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
            j = j->getPrev();
        }

        swapPtr(i, j);
    }

    swapPtr(i, rightEdge);

    if (i != leftEdge) {
        quickSort(leftEdge, i->getPrev(), comp);
    }

    if (i != rightEdge) {
        quickSort(i->getNext(), rightEdge, comp);
    }
}

template <class T>
void DLList<T>::writeToDisk(const string &fileName) {

	ofstream file;

	file.open(fileName, ios_base::trunc);

	if (!file.is_open()) {
		throw Exception("No se pudo abrir el archivo para escritura, writeToDisk");
	}

    DLList<T>::Position pos = this->getFirstPos();
	while (pos != nullptr) {
		file << pos->getData() << endl;
        pos = this->getNextPos(pos);
	}
	file.close();
}

template <class T>
void DLList<T>::readFromDisk(const string& fileName) {
	ifstream myFile;

    myFile.open(fileName);

	if (!myFile.is_open()) {
        throw Exception("No se pudo abrir el archivo para lectura, readFromDisk");
    }

    deleteAll();

    T data;

    while (myFile >> data) {
        insertData(nullptr, data);
    }

    myFile.close();
}

#endif // DLLIST_HPP
