#pragma once
#include <vector>
#include <queue>

template<typename T>
struct Handle {
	int index;

	Handle( int index = -1 ) : index{ index } {}

	T* operator->() {
		return &GCData<T>::at( index );
	}
	T* operator->() const{
		return &GCData<T>::at( index );
	}

	T& operator*() {
		return GCData<T>::at( index );
	}
	T operator*() const {
		return GCData<T>::at( index );
	}

	T* operator&() const {
		return &GCData<T>::at( index );
	}


	operator int() {
		return index;
	}
	operator int() const {
		return index;
	}
};

// Global Contiguous Data
// POD
template<typename T>
class GCData {
	int index;
	bool isVacant;
	static std::queue<int>& getQueue() {
		static std::queue<int> q; 
		return q;
	}
public:
	static std::vector<T>& getData() {
		static std::vector<T> d;
		return d;
	}
	static T& at( unsigned i ) {
		return getData()[i];
	}

	static void free( int i ) {
		if ( i > -1 && !at( i ).isVacant ) {
			at( i ).onFree();
			getQueue().push( i );
			at( i ).isVacant = true;
			at( i ).index = -1;
		}
	}

	static Handle<T> make() {
		int i = -1;

		if ( getQueue().size() > 0 ) {
			i = getQueue().front();
			getQueue().pop();
			Handle<T> handle = { i };
			*handle = T();
		}
		else {
			i = getData().size();
			getData().emplace_back();
		}
		at( i ).index = i;
		at( i ).isVacant = false;
		return Handle<T>{i};
	}

	int getIndex() {
		return index;
	}

	bool isValid() { return index > -1 && !isVacant && index < getData().size(); }

	virtual void onFree() {}
};

