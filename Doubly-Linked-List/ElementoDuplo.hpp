// "Copyright [2016] <Gustavo Olegário>"
#ifndef ElementoDuplo_HPP
#define ElementoDuplo_HPP

template<typename T>
class ElementoDuplo {
 private:
	T *info;
	ElementoDuplo<T> *_next;
	ElementoDuplo<T> *_previous;

 public:
	ElementoDuplo(const T& info, ElementoDuplo<T>* next,
	ElementoDuplo<T>* previous)	: info(new T(info)), _next(next),
	_previous(previous) {}

	~ElementoDuplo() {
		delete info;
	}

	ElementoDuplo<T>* getProximo() const {
		return _next;
	}

	ElementoDuplo<T>* getAnterior() const {
		return _previous;
	}

	T getInfo() const {
		return *info;
	}

	void setProximo(ElementoDuplo<T>* next) {
		_next = next;
	}

	void setAnterior(ElementoDuplo<T>* previous) {
		_previous = previous;
	}
};

#endif
