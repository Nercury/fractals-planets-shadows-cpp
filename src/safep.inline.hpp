#pragma once

// enable safep logging to output stream
//#define SAFEP_LOGS_ENABLED

#include "safep.hpp"
#include <string.h>
#include <string>
#include <iostream>

/*void safeStrset(char* & buffer, const uint32_t max_length, const char * str)
{
	size_t len = strlen(str);
	if (len > (size_t)max_length)
		len = (size_t)max_length;
	for (size_t i = 0; i < len; i++)
		buffer[i] = str[i];
}*/

/**
 * Initialize empty instance, without any object
 */
template <class T>
p<T>::p()
{ 
	refs = NULL;
	notifyRefs = NULL;
	notifyRefsFunction = NULL;
	obj = NULL;
}

/**
 * Initialize object by copying reference to it from another instance
 */
template <class T>
p<T>::p(const p<T> & other)
{
	// copy object from another instance 
	copyFrom(other);
}

/**
 * Initialize new reference to an object
 */
template <class T>
p<T>::p(T* obj) 
{
	// create new instance
	newRef(obj);
}

/**
 * Initialize new reference to an object with callback funtion when object 
 * references decrease to specified amount
 */
template <class T>
p<T>::p(T* obj, uint32_t notifyRefs, boost::function<void (T*)> notifyRefsFunction) 
{ 
	// create new instance
	newRef(obj, notifyRefs, notifyRefsFunction);
}

/**
 * Instance descructor. Automatically decreases reference count and
 * deletes object if reference count reaches 0
 */
template <class T>
p<T>::~p() 
{
	if (obj != NULL)
	{
		unref(false); // does not check if this instance contains an object
	}
}

/**
 * Assign object from another instance, and increase ref count
 */
template <class T>
p<T> & p<T>::operator = (const p<T> & other)
{
    if (this != &other) // protect against invalid self-assignment
    {
		// make sure there is no object before copying
		if (obj != NULL)
		{
			// unref and delete is necessary
			unref(false); // does not check if this instance contains an object
		}
		// when obj is null, copy
		copyFrom(other); // does not check if this instance contains an object
    }
    return *this;
}

/**
 * Get reference to the same object casted to another type. Reference count
 * still remains the same for both objects.
 */
template <class T>
template <class Other>
p<Other> p<T>::as()
{
	p<Other> other;
	if (obj != NULL)
	{
		(*refs)++;
		// set data will only be successfull of object can be casted
		other.setData(obj, refs, notifyRefs, (boost::function<void (Other*)> *)notifyRefsFunction);
#ifdef SAFEP_LOGS_ENABLED
		std::cout << "Copy and cast " << objInfo() << " to " << other.objInfo() << std::endl;
		std::cout << "Refs of " << objInfo() << " += " << (*refs) << std::endl;
#endif
	}
	else
	{
		// make sure we are able to set null object too
		other.setData(NULL, refs, notifyRefs, (boost::function<void (Other*)> *)notifyRefsFunction);
	}
	return other;
};

/**
 * Return reference to stored object. It should not be deleted, copied or
 * assigned to ensure safety of p<>. Always access your object over o(),
 * unless you know what you are doing.
 */
template <class T>
T* p<T>::o() const 
{
	return obj;
}

/**
 * Return reference of stored object, if that is what you need.
 * 
 * Note that it still should not be deleted, copied or
 * assigned to ensure safety of p<>.
 */
template <class T>
T& p<T>::oRef() 
{
	return *obj;
}

/**
 * Take object from p<> container. Note that 
 * 
 * 1) You take object only from this instance, it remains in other instances.
 * 2) Do not delete it unless you removed it from ALL instances
 * 3) If you take last object, you have to delete it yourself
 * 
 * Best thing to do is not to take the object.
 */
template <class T>
T* p<T>::take() 
{
	if (obj == NULL)
	{
		return NULL; 
	} else {
		T* object = obj;
		unref(true); // do not delete the object if it is last
		return object;
	}
}

/*
 *  * UNDOCUMENTED. Not sure what this does, do not use.

template <class T>
void p<T>::autoRemove(T* obj) {
	put(obj);
	if (notifyRefs != NULL)
		delete notifyRefs;
	if (notifyRefsFunction != NULL)
		delete notifyRefsFunction;
	notifyRefsFunction = NULL;
	(*refs) = 1;
	notifyRefs = NULL;
	notifyRefsFunction = NULL;
}*/

/**
 * Put new object by replacing existing object.
 */
template <class T>
void p<T>::put(T* obj) {
	if (this->obj != NULL) // if we have object already
	{
		unref(false); // unref and delete if necessary
	}
	newRef(obj); // create new ref (does not check if instance already has an object)
}

/**
 * Check if p<> contains an object (if obj is not null, returns true)
 */
template <class T>
bool p<T>::empty() 
{
	return obj == NULL;
}

/**
 * Return description of contained object (returned by "toString" function from object itself)
 */
template <class T>
std::string p<T>::objInfo() const
{
	return obj->toString();
}

/**
 * Initialize this instance for specified object
 * 
 * Note: does not check if current instace contains an object
 */
template <class T>
void p<T>::newRef(T* obj)
{
	refs = new uint32_t; // create reference to reference count
	notifyRefs = NULL;
	notifyRefsFunction = NULL;
	(*refs) = 1; // set refcount to 1
	this->obj = obj; // set object
#ifdef SAFEP_LOGS_ENABLED
	std::cout << "Assign " << this->objInfo() << std::endl;
	std::cout << "Refs of " << objInfo() << " += " << (*refs) << std::endl;
#endif
}

/**
 * Initialize this instance for specified object with callback function
 * 
 * Note: does not check if current instace contains an object
 */
template <class T>
void p<T>::newRef(T* obj, uint32_t nRefs, boost::function<void (T*)> nRefsFunction)
{
	refs = new uint32_t; // create reference to reference count
	notifyRefs = new uint32_t; // create reference to notifyRefs
	notifyRefsFunction = new boost::function<void (T*)>(); // and reference to notification function
	(*refs) = 1;
	(*notifyRefs) = nRefs;
	(*notifyRefsFunction) = nRefsFunction;
	this->obj = obj;
#ifdef SAFEP_LOGS_ENABLED
	std::cout << "Assign " << this->objInfo() << std::endl;
	std::cout << "Refs of " << objInfo() << " += " << (*refs) << std::endl;
#endif
}

/**
 * Decrease reference count, with option to delete stored object
 * if count reaches 0
 *
 * Note: Does not check if instance already contains an object
 */
template <class T>
void p<T>::unref(bool nodelete)
{
	(*refs)--; // decrease references
#ifdef SAFEP_LOGS_ENABLED
	std::cout << "Refs of " << objInfo() << " -= " << (*refs) << std::endl;
#endif
	if (*refs == 0) // if this instance was last one that holded this object
	{
		if (!nodelete) // if not nodelete, delete the object
		{
#ifdef SAFEP_LOGS_ENABLED
			std::cout << "Del " << this->objInfo() << std::endl;
#endif
			delete this->obj;
		}
		// delete everything else too (instance is last)
		delete refs;
		if (notifyRefs != NULL)
			delete notifyRefs;
		if (notifyRefsFunction != NULL)
			delete notifyRefsFunction;
	}
	else // otherwise, check if we need to fire notification on reference decrease
	{
		if (notifyRefs != NULL && notifyRefsFunction != NULL)
			if ((*refs) == (*notifyRefs))
				(*notifyRefsFunction)(obj);
	}
	// even when instance count does not reach 0, unref means that this instance should
	// not contain object anymore
	this->obj = NULL;
	this->refs = NULL;
	this->notifyRefs = NULL;
	this->notifyRefsFunction = NULL;
}

/**
 * Initialize instance from another, existing instance with the same object
 * 
 * Note: does not check if current instace contains an object
 */
template <class T>
void p<T>::copyFrom(const p<T> & other)
{
	this->obj = other.obj;
	this->refs = other.refs;
	this->notifyRefs = other.notifyRefs;
	this->notifyRefsFunction = other.notifyRefsFunction;
	if (this->obj != NULL) // if object was copied, increase references to it
	{
		(*refs)++;
#ifdef SAFEP_LOGS_ENABLED
		std::cout << "Copy " << other.objInfo() << std::endl;
		std::cout << "Refs of " << objInfo() << " += " << (*refs) << std::endl;
#endif
	}
}
