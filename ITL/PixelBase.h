/*******************************************************************************
 Copyright 2009 Enseed Inc. & Gaspard Petit <gaspardpetit@enseed.com>
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
*******************************************************************************/
#ifndef __ITL_PIXELBASE_H__
#define __ITL_PIXELBASE_H__

#include "Storage/PixelManipulation.h"
#include <cstddef>

//==============================================================================
// CLASS ConstPixelBase
//==============================================================================
template<typename COMPONENT_STORAGE, typename DERIVED>
class ConstPixelBase
{
protected:
	typedef PixelManipulation _Manip;
	typedef DERIVED _DerivedType;

public:
	typedef DERIVED ConstType;
	typedef COMPONENT_STORAGE PacketStorageType;
	typedef typename PacketStorageType::ColorSpace ColorSpace;
	typedef typename PacketStorageType::ComponentModel ComponentModel;
	typedef typename PacketStorageType::ComponentType ComponentType;

	enum { PIXEL_PER_PACKET = 1 };
	static size_t size() { return COMPONENT_STORAGE::size(); }

	typedef _DerivedType Plane0Type;
	typedef PacketStorageType Plane0Storage;
	enum { PLANE_COUNT = 1 };

public:
	ConstPixelBase() : _storage() {}

public:
	const PacketStorageType& storage() const { return _storage; }

protected:
	ConstPixelBase(const ConstPixelBase &rhs) : _storage(rhs._storage) {}
	DERIVED& operator=(const ConstPixelBase &rhs) { _storage = rhs._storage; return *static_cast<DERIVED*>(this); }

protected:
	PacketStorageType _storage;
};



//==============================================================================
// CLASS PixelBase
//==============================================================================
template<typename COMPONENT_STORAGE, typename DERIVED, typename CONST_DERIVED>
class PixelBase: public ConstPixelBase<COMPONENT_STORAGE, CONST_DERIVED>
{
private:
	typedef ConstPixelBase<COMPONENT_STORAGE, CONST_DERIVED> _Super;

public:
	typedef typename _Super::ComponentType	ComponentType;
	typedef typename _Super::PacketStorageType 	PacketStorageType;

public:
	PixelBase() {}
	
public:
	PixelBase(const PixelBase &rhs) : _Super(rhs) {}
	PixelBase& operator=(const PixelBase &rhs) { _Super::operator=(rhs); return *this; }

public:
	using _Super::storage;
	PacketStorageType& storage() { return _Super::_storage; }

protected:
	template<typename PIXELSRC>
	void convert(const PIXELSRC &fromPixel)
	{}
};





//==============================================================================
// CLASS ConstPixelFamilyBase
//==============================================================================
#define ITL_DECLARE_PIXEL_CONST_BASE_TYPE(_NAME_, _name_)						\
template<typename PARENT, typename COMPONENT_SPEC>								\
class Const##_NAME_##PixelFamilyBase: public PARENT								\
{																				\
private: 	typedef PARENT _Super;												\
protected: 	typedef typename _Super::_Manip	_Manip;								\
																				\
public:																			\
	typedef COMPONENT_SPEC _NAME_##StorageType;								\
	typedef typename _NAME_##StorageType::ComponentType _NAME_##ComponentType;	\
	typedef typename _Super::PacketStorageType 	PacketStorageType;				\
																				\
public:																			\
	Const##_NAME_##PixelFamilyBase() {}											\
																				\
public:																			\
	Const##_NAME_##PixelFamilyBase(const Const##_NAME_##PixelFamilyBase &rhs)	\
	:																			\
		_Super(rhs)																\
	{}																			\
																				\
public:																			\
	static const _NAME_##ComponentType _name_ (const PacketStorageType &storage)	\
	{ return _Manip::template _name_<PacketStorageType>(storage);   }			\
																				\
	const _NAME_##ComponentType _name_() const									\
	{ return _name_(_Super::_storage);   }										\
};

//==============================================================================
// CLASS PixelFamilyBase
//==============================================================================
#define ITL_DECLARE_PIXEL_BASE_TYPE(_NAME_, _name_)								\
template<typename PARENT, typename COMPONENT_SPEC>								\
class _NAME_##PixelFamilyBase: public Const##_NAME_##PixelFamilyBase<PARENT, COMPONENT_SPEC>	\
{																				\
private:	typedef Const##_NAME_##PixelFamilyBase<PARENT, COMPONENT_SPEC> _Super;	\
protected:	typedef typename _Super::_DerivedType _DerivedType;					\
protected:	typedef typename _Super::_Manip	_Manip;								\
																				\
public:																			\
	typedef COMPONENT_SPEC _NAME_##StorageType;								\
	typedef typename _NAME_##StorageType::ComponentType _NAME_##ComponentType;	\
	typedef typename _Super::PacketStorageType 	PacketStorageType;				\
																				\
public:																			\
	_NAME_##PixelFamilyBase() {}												\
																				\
public:																			\
	_NAME_##PixelFamilyBase(const _NAME_##PixelFamilyBase &rhs)					\
	:																			\
		_Super(rhs)																\
	{}																			\
	_NAME_##PixelFamilyBase(const PacketStorageType &_name_)					\
	:																			\
		 _Super()																\
	{																			\
		set##_NAME_(_name_);													\
	}																			\
	_NAME_##PixelFamilyBase& operator=(const _NAME_##PixelFamilyBase &rhs)		\
	{ _Super::operator=(rhs); return *this; }									\
																				\
public:																			\
	static void set##_NAME_(PacketStorageType &storage, const _NAME_##ComponentType &val)	\
	{ _Manip::template set##_NAME_<PacketStorageType>(storage, val);   }		\
																				\
	void set##_NAME_(const _NAME_##ComponentType &val)							\
	{ set##_NAME_(_Super::_storage, val);   }									\
																				\
	using _Super::storage;														\
	PacketStorageType& storage() { return _Super::_storage; }					\
																				\
public:																			\
	template<typename PIXELSRC>													\
	void convert(const PIXELSRC &fromPixel)										\
	{																			\
		_Super::convert(fromPixel);												\
		set##_NAME_(PixelConvertExtract##_NAME_<PIXELSRC, _DerivedType>::eval(fromPixel));	\
	}																			\
};

//==============================================================================
// CLASS ConstPixelFamily
//==============================================================================
#define ITL_DECLARE_PIXEL_CONST_TYPE(_NAME_, _name_)							\
template<typename COMPONENT_STORAGE>											\
class Const##_NAME_##PixelFamily: public Const##_NAME_##PixelFamilyBase<ConstPixelBase<COMPONENT_STORAGE, Const##_NAME_##PixelFamily<COMPONENT_STORAGE> >, COMPONENT_STORAGE>	\
{																				\
private:																		\
	typedef Const##_NAME_##PixelFamilyBase<ConstPixelBase<COMPONENT_STORAGE, Const##_NAME_##PixelFamily<COMPONENT_STORAGE> >, COMPONENT_STORAGE> _Super;	\
																				\
public:																			\
	Const##_NAME_##PixelFamily() {}												\
	Const##_NAME_##PixelFamily(const Const##_NAME_##PixelFamily &rhs)			\
	:																			\
		 _Super(rhs)															\
	{}																			\
};


//==============================================================================
// CLASS PixelFamily
//==============================================================================
#define ITL_DECLARE_PIXEL_TYPE(_NAME_, _name_)									\
template<typename COMPONENT_STORAGE>											\
class _NAME_##PixelFamily: public _NAME_##PixelFamilyBase<Const##_NAME_##PixelFamilyBase<PixelBase<COMPONENT_STORAGE, _NAME_##PixelFamily<COMPONENT_STORAGE>, Const##_NAME_##PixelFamily<COMPONENT_STORAGE> >, COMPONENT_STORAGE>, COMPONENT_STORAGE>	\
{																				\
private:																		\
	typedef _NAME_##PixelFamilyBase<Const##_NAME_##PixelFamilyBase<PixelBase<COMPONENT_STORAGE, _NAME_##PixelFamily<COMPONENT_STORAGE>, Const##_NAME_##PixelFamily<COMPONENT_STORAGE> >, COMPONENT_STORAGE>, COMPONENT_STORAGE> _Super;\
																				\
public:																			\
	typedef typename _Super::ComponentType ComponentType;						\
																				\
public:																			\
	_NAME_##PixelFamily() {}													\
	_NAME_##PixelFamily(const _NAME_##PixelFamily &rhs) : _Super(rhs) {}		\
	_NAME_##PixelFamily(const ComponentType &_name_) : _Super() { set##_NAME_(_name_); }		\
};

template<class COMPONENT_PACKET>
class ConstPlanarPixelBase
{
protected:
	COMPONENT_PACKET *_plane;

public:
	typedef COMPONENT_PACKET PacketType;
	typedef typename PacketType::PacketStorageType PacketStorageType;
	const PacketStorageType& storage() const { return _plane->storage(); }

public:
	bool operator==(const ConstPlanarPixelBase &rhs) const
	{	return _plane == rhs._plane; }
	
	ConstPlanarPixelBase(COMPONENT_PACKET *plane) : _plane(plane) {}
	
};


template<class COMPONENT_PACKET, typename PARENT>
class PlanarPixelBase: public PARENT
{
private:
	typedef PARENT _Super;

public:
	typedef typename _Super::PacketStorageType PacketStorageType;
	using _Super::storage;
	PacketStorageType& storage() { return _Super::_plane->storage(); }

public:
	template<typename PIXELSRC>
	void convert(const PIXELSRC &fromPixel)
	{
		_Super::_plane->convert(fromPixel);
	}

public:
	PlanarPixelBase(COMPONENT_PACKET *plane) : _Super(plane) {}
};


#define ITL_DECLARE_PLANAR_PIXEL_CONST(_NAME_, _name_)\
template<class COMPONENT_PACKET>\
class Const##_NAME_##PlanarPixel: public ConstPlanarPixelBase<COMPONENT_PACKET>\
{\
private:\
	typedef ConstPlanarPixelBase<COMPONENT_PACKET> _Super;\
\
public:\
	typedef typename COMPONENT_PACKET::_NAME_##StorageType _NAME_##StorageType;\
	typedef typename _NAME_##StorageType::ComponentType _NAME_##ComponentType;\
\
public:\
	_NAME_##ComponentType _name_() const { return _Super::_plane->_name_(); }\
	const COMPONENT_PACKET* _name_##PlanePtr() const { return _Super::_plane; }\
\
public:\
	Const##_NAME_##PlanarPixel(COMPONENT_PACKET *plane) : _Super(plane) {}\
};

#define ITL_DECLARE_PLANAR_PIXEL(_NAME_, _name_)\
template<class COMPONENT_PACKET>\
class _NAME_##PlanarPixel: public PlanarPixelBase<COMPONENT_PACKET, Const##_NAME_##PlanarPixel<COMPONENT_PACKET> >\
{\
private:\
	typedef PlanarPixelBase<COMPONENT_PACKET, Const##_NAME_##PlanarPixel<COMPONENT_PACKET> > _Super;\
\
public:\
	typedef typename _Super::_NAME_##ComponentType _NAME_##ComponentType;\
\
public:\
	void set##_NAME_(const _NAME_##ComponentType &r)  { return _Super::_plane->set##_NAME_(r); }\
\
\
	using _Super::_name_##PlanePtr;\
	COMPONENT_PACKET* _name_##PlanePtr() { return _Super::_plane; }\
\
public:\
	_NAME_##PlanarPixel(COMPONENT_PACKET *plane) : _Super(plane) {}\
};

#define ITL_DECLARE_PLANAR_PIXEL_FAMILY(_NAME_, _name_)\
ITL_DECLARE_PLANAR_PIXEL_CONST(_NAME_, _name_)\
ITL_DECLARE_PLANAR_PIXEL(_NAME_, _name_)


#define ITL_DECLARE_PIXEL_FAMILY_BASE(_NAME_, _name_)							\
ITL_DECLARE_PIXEL_CONST_BASE_TYPE(_NAME_, _name_)								\
ITL_DECLARE_PIXEL_BASE_TYPE(_NAME_, _name_)

#define ITL_DECLARE_SIMPLE_PIXEL_FAMILY(_NAME_, _name_)							\
ITL_DECLARE_PIXEL_FAMILY_BASE(_NAME_, _name_)									\
ITL_DECLARE_PIXEL_CONST_TYPE(_NAME_, _name_)									\
ITL_DECLARE_PIXEL_TYPE(_NAME_, _name_)											\
ITL_DECLARE_PLANAR_PIXEL_FAMILY(_NAME_, _name_)


#endif // __ITL_PIXELBASE_H__
