#pragma once

#include "types.h"
#include "b_bind.h"

//void safeStrset(char* & buffer, const uint32_t max_length, const char * str);

/**
 * Universal class for reference counting.
 * 
 * Requires object to have "void toString()" method which returns object
 * description.
 */
template <class T>
class p
{
protected:
	/**
	 * Pointer to referenced object
	 */
	T* obj;
	/**
	 * Pointer to number of references for this object
	 */
	uint32_t * refs;
	/**
	 * notify function will be called when refs DECREASES to the number
	 * specified in notifyRefs
	 */
	uint32_t * notifyRefs;
	/**
	 * Function called when number of referenced decreases to
	 * notifyRefs.
	 */
	boost::function<void (T*)> * notifyRefsFunction;
	/**
	 * Initialize this instance for specified object
	 * 
	 * Note: does not check if current instace contains an object
	 */
	void newRef(T* obj);
	/**
	 * Initialize this instance for specified object with callback function
	 * 
	 * Note: does not check if current instace contains an object
	 */
	void newRef(T* obj, uint32_t nRefs, boost::function<void (T*)> nRefsFunction);
	/**
	 * Decrease reference count, with option to delete stored object
	 * if count reaches 0
	 */
	void unref(bool nodelete);
	/**
	 * Initialize instance from another, existing instance with the same object
	 * 
	 * Note: does not check if current instace contains an object
	 */
	void copyFrom(const p<T> & other);
public:
	/**
	 * Assign object from another instance, and increase ref count
	 */
    p<T> & operator = (const p<T> & other);
    /**
	 * Initialize object by copying reference to it from another instance
	 */
	p(const p<T> & other);
	/**
	 * Initialize empty instance, without any object
	 */
	p(); 
	/**
	 * Get reference to the same object casted to another type. Reference count
	 * still remains the same for both objects.
	 */
	template <class Other>
	p<Other> as();
	/**
	 * Initialize new reference to an object
	 */
	p(T* obj);
	/**
	 * Initialize new reference to an object with callback funtion when object 
	 * references decrease to specified amount
	 */
	p(T* obj, uint32_t notifyRefs, boost::function<void (T*)> notifyRefsFunction);
	/**
	 * Instance descructor. Automatically decreases reference count and
	 * deletes object if reference count reaches 0
	 */
	~p();
	/**
	 * Return reference to stored object. It should not be deleted, copied or
	 * assigned to ensure safety of p<>. Always access your object over o(),
	 * unless you know what you are doing.
	 */
	T* o() const;
	/**
	 * Return reference of stored object, if that is what you need.
	 * 
	 * Note that it still should not be deleted, copied or
	 * assigned to ensure safety of p<>.
	 */
	T& oRef();
	/**
	 * Take object from p<> container. Note that 
	 * 
	 * 1) You take object only from this instance, it remains in other instances.
	 * 2) Do not delete it unless you removed it from ALL instances
	 */
	T* take();
	/**
	 * Return description of contained object (returned by "toString" function from object itself)
	 */
	std::string objInfo() const;
	/**
	 * Put new object by replacing existing object.
	 */
	void put(T* obj);
	/*
	 * UNDOCUMENTED. Not sure what this does, do not use.
	void autoRemove(T* obj);
	*/
	/**
	 * Check if p<> contains an object (if obj is not null, returns true)
	 */
	bool empty();
	/**
	 * Set p<> data from outside. Used to initialize reference of casted type.
	 */
	void setData(T * obj, uint32_t * refs, uint32_t * notifyRefs, boost::function<void (T*)> * notifyRefsFunction)
	{
		this->obj = obj;
		this->refs = refs;
		this->notifyRefs = notifyRefs;
		this->notifyRefsFunction = notifyRefsFunction;
	};
};

#include "safep.inline.hpp"
