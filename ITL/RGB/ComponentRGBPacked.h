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
#ifndef __ITL_COMPONENTRGBPACKED_H__
#define __ITL_COMPONENTRGBPACKED_H__

//==============================================================================
//	FILE ComponentRGBPacked.h
//==============================================================================
// Special storage for RGB packed (e.g. 16 bit 5:6:5 RGB)
// In this case, we cannot use the ComponentArray object
//------------------------------------------------------------------------------

//==============================================================================
//	CLASS ComponentRGBPackedDefinitions
//==============================================================================
template<typename STORAGE_TYPE, typename COMPONENT_TYPE, typename STORAGE_MANIPULATOR, typename COMPONENT_ORDERING, typename COLOR_SPACE>
class ComponentRGBPackedDefinitions
{
public:
	typedef COLOR_SPACE ColorSpace;
	typedef COMPONENT_TYPE ComponentType;
	typedef STORAGE_MANIPULATOR StorageManipulatorType;
	typedef STORAGE_TYPE ComponentStorage;
};

//==============================================================================
//	CLASS ComponentRGBPacked
//==============================================================================
// Compute offsets based on the sizes and paddings
template<int INDEX, typename STORAGE_TYPE, int PAD0_SIZE, int COMPONENT0_SIZE, int PAD1_SIZE, int COMPONENT1_SIZE, int PAD2_SIZE, int COMPONENT2_SIZE>
struct ComponentDefinition3;

template<typename STORAGE_TYPE, int PAD0_SIZE, int COMPONENT0_SIZE, int PAD1_SIZE, int COMPONENT1_SIZE, int PAD2_SIZE, int COMPONENT2_SIZE>
struct ComponentDefinition3<0, STORAGE_TYPE, PAD0_SIZE, COMPONENT0_SIZE, PAD1_SIZE, COMPONENT1_SIZE, PAD2_SIZE, COMPONENT2_SIZE>
{ enum { SIZE = COMPONENT0_SIZE, OFFSET = 8*sizeof(STORAGE_TYPE) - PAD0_SIZE - COMPONENT0_SIZE }; };

template<typename STORAGE_TYPE, int PAD0_SIZE, int COMPONENT0_SIZE, int PAD1_SIZE, int COMPONENT1_SIZE, int PAD2_SIZE, int COMPONENT2_SIZE>
struct ComponentDefinition3<1, STORAGE_TYPE, PAD0_SIZE, COMPONENT0_SIZE, PAD1_SIZE, COMPONENT1_SIZE, PAD2_SIZE, COMPONENT2_SIZE>
{ enum { SIZE = COMPONENT1_SIZE, OFFSET = ComponentDefinition3<0, STORAGE_TYPE, PAD0_SIZE, COMPONENT0_SIZE, PAD1_SIZE, COMPONENT1_SIZE, PAD2_SIZE, COMPONENT2_SIZE>::OFFSET - PAD1_SIZE - COMPONENT1_SIZE }; };

template<typename STORAGE_TYPE, int PAD0_SIZE, int COMPONENT0_SIZE, int PAD1_SIZE, int COMPONENT1_SIZE, int PAD2_SIZE, int COMPONENT2_SIZE>
struct ComponentDefinition3<2, STORAGE_TYPE, PAD0_SIZE, COMPONENT0_SIZE, PAD1_SIZE, COMPONENT1_SIZE, PAD2_SIZE, COMPONENT2_SIZE>
{ enum { SIZE = COMPONENT2_SIZE, OFFSET = ComponentDefinition3<1, STORAGE_TYPE, PAD0_SIZE, COMPONENT0_SIZE, PAD1_SIZE, COMPONENT1_SIZE, PAD2_SIZE, COMPONENT2_SIZE>::OFFSET - PAD2_SIZE - COMPONENT2_SIZE }; };

template<typename STORAGE_TYPE, typename COMPONENT_TYPE, int PAD0_SIZE, int COMPONENT0_SIZE, int PAD1_SIZE, int COMPONENT1_SIZE, int PAD2_SIZE, int COMPONENT2_SIZE, typename STORAGE_MANIPULATOR, typename COMPONENT_ORDERING, typename COLOR_SPACE>
class ComponentRGBPacked: public ComponentRGBPackedDefinitions<STORAGE_TYPE, COMPONENT_TYPE, STORAGE_MANIPULATOR, COMPONENT_ORDERING, COLOR_SPACE>
{
private:
	typedef ComponentRGBPackedDefinitions<STORAGE_TYPE, COMPONENT_TYPE, STORAGE_MANIPULATOR, COMPONENT_ORDERING, COLOR_SPACE> _Super;

	// Compute offsets based on the sizes and paddings

//	Apparently, template specialization is not allowed for member classes, so we have to do this outside...
//	(what a shame, this was much easier to read...)
//	template<int INDEX>
//	struct ComponentDefinition;
//	template<>	struct ComponentDefinition<0> { enum { SIZE = COMPONENT0_SIZE, OFFSET = 8*sizeof(STORAGE_TYPE) - PAD0_SIZE - COMPONENT0_SIZE }; };
//	template<>	struct ComponentDefinition<1> { enum { SIZE = COMPONENT1_SIZE, OFFSET = ComponentDefinition<0>::OFFSET - PAD1_SIZE - COMPONENT1_SIZE }; };
//	template<>	struct ComponentDefinition<2> { enum { SIZE = COMPONENT2_SIZE, OFFSET = ComponentDefinition<1>::OFFSET - PAD2_SIZE - COMPONENT2_SIZE }; };
	
public:
	typedef typename _Super::ComponentType ComponentType;
	typedef typename _Super::StorageManipulatorType StorageManipulatorType;
	typedef typename _Super::ComponentStorage ComponentStorage;
	
	enum { BYTES_PER_PACKET = sizeof(STORAGE_TYPE) };

public:
	ComponentRGBPacked() : _storage() {}
	
	ComponentType red() const { return component<COMPONENT_ORDERING::RED>(); }
	ComponentType green() const { return component<COMPONENT_ORDERING::GREEN>(); }
	ComponentType blue() const { return component<COMPONENT_ORDERING::BLUE>(); }

	void setRed(const ComponentType &val) { return setComponent<COMPONENT_ORDERING::RED>(val); }
	void setGreen(const ComponentType &val) { return setComponent<COMPONENT_ORDERING::GREEN>(val); }
	void setBlue(const ComponentType &val) { return setComponent<COMPONENT_ORDERING::BLUE>(val); }
	
	template<int INDEX>
	ComponentType component() const
	{
		return StorageManipulatorType::template readBits<ComponentStorage, ComponentType, ComponentDefinition3<INDEX, STORAGE_TYPE, PAD0_SIZE, COMPONENT0_SIZE, PAD1_SIZE, COMPONENT1_SIZE, PAD2_SIZE, COMPONENT2_SIZE>::OFFSET, ComponentDefinition3<INDEX, STORAGE_TYPE, PAD0_SIZE, COMPONENT0_SIZE, PAD1_SIZE, COMPONENT1_SIZE, PAD2_SIZE, COMPONENT2_SIZE>::SIZE>(&_storage); 
	}

	template<int INDEX>
	void setComponent(const ComponentType &val)
	{
		return StorageManipulatorType::template writeBits<ComponentStorage, ComponentType, ComponentDefinition3<INDEX, STORAGE_TYPE, PAD0_SIZE, COMPONENT0_SIZE, PAD1_SIZE, COMPONENT1_SIZE, PAD2_SIZE, COMPONENT2_SIZE>::OFFSET, ComponentDefinition3<INDEX, STORAGE_TYPE, PAD0_SIZE, COMPONENT0_SIZE, PAD1_SIZE, COMPONENT1_SIZE, PAD2_SIZE, COMPONENT2_SIZE>::SIZE>(&_storage, val);
	}

private:
	STORAGE_TYPE _storage;
};

template<int INDEX, typename STORAGE_TYPE, int PAD0_SIZE, int COMPONENT0_SIZE, int PAD1_SIZE, int COMPONENT1_SIZE, int PAD2_SIZE, int COMPONENT2_SIZE, int PAD3_SIZE, int COMPONENT3_SIZE>
struct ComponentDefinition4;

template<typename STORAGE_TYPE, int PAD0_SIZE, int COMPONENT0_SIZE, int PAD1_SIZE, int COMPONENT1_SIZE, int PAD2_SIZE, int COMPONENT2_SIZE, int PAD3_SIZE, int COMPONENT3_SIZE>
struct ComponentDefinition4<0, STORAGE_TYPE, PAD0_SIZE, COMPONENT0_SIZE, PAD1_SIZE, COMPONENT1_SIZE, PAD2_SIZE, COMPONENT2_SIZE, PAD3_SIZE, COMPONENT3_SIZE>
{ enum { SIZE = COMPONENT0_SIZE, OFFSET = 8*sizeof(STORAGE_TYPE) - PAD0_SIZE - COMPONENT0_SIZE }; };

template<typename STORAGE_TYPE, int PAD0_SIZE, int COMPONENT0_SIZE, int PAD1_SIZE, int COMPONENT1_SIZE, int PAD2_SIZE, int COMPONENT2_SIZE, int PAD3_SIZE, int COMPONENT3_SIZE>
struct ComponentDefinition4<1, STORAGE_TYPE, PAD0_SIZE, COMPONENT0_SIZE, PAD1_SIZE, COMPONENT1_SIZE, PAD2_SIZE, COMPONENT2_SIZE, PAD3_SIZE, COMPONENT3_SIZE> { enum { SIZE = COMPONENT1_SIZE, OFFSET = ComponentDefinition4<0, STORAGE_TYPE, PAD0_SIZE, COMPONENT0_SIZE, PAD1_SIZE, COMPONENT1_SIZE, PAD2_SIZE, COMPONENT2_SIZE, PAD3_SIZE, COMPONENT3_SIZE>::OFFSET - PAD1_SIZE - COMPONENT1_SIZE }; };

template<typename STORAGE_TYPE, int PAD0_SIZE, int COMPONENT0_SIZE, int PAD1_SIZE, int COMPONENT1_SIZE, int PAD2_SIZE, int COMPONENT2_SIZE, int PAD3_SIZE, int COMPONENT3_SIZE>
struct ComponentDefinition4<2, STORAGE_TYPE, PAD0_SIZE, COMPONENT0_SIZE, PAD1_SIZE, COMPONENT1_SIZE, PAD2_SIZE, COMPONENT2_SIZE, PAD3_SIZE, COMPONENT3_SIZE> { enum { SIZE = COMPONENT2_SIZE, OFFSET = ComponentDefinition4<1, STORAGE_TYPE, PAD0_SIZE, COMPONENT0_SIZE, PAD1_SIZE, COMPONENT1_SIZE, PAD2_SIZE, COMPONENT2_SIZE, PAD3_SIZE, COMPONENT3_SIZE>::OFFSET - PAD2_SIZE - COMPONENT2_SIZE }; };

template<typename STORAGE_TYPE, int PAD0_SIZE, int COMPONENT0_SIZE, int PAD1_SIZE, int COMPONENT1_SIZE, int PAD2_SIZE, int COMPONENT2_SIZE, int PAD3_SIZE, int COMPONENT3_SIZE>
struct ComponentDefinition4<3, STORAGE_TYPE, PAD0_SIZE, COMPONENT0_SIZE, PAD1_SIZE, COMPONENT1_SIZE, PAD2_SIZE, COMPONENT2_SIZE, PAD3_SIZE, COMPONENT3_SIZE> { enum { SIZE = COMPONENT3_SIZE, OFFSET = ComponentDefinition4<2, STORAGE_TYPE, PAD0_SIZE, COMPONENT0_SIZE, PAD1_SIZE, COMPONENT1_SIZE, PAD2_SIZE, COMPONENT2_SIZE, PAD3_SIZE, COMPONENT3_SIZE>::OFFSET - PAD3_SIZE - COMPONENT3_SIZE }; };

//==============================================================================
//	CLASS ComponentRGBAPacked
//==============================================================================
template<typename STORAGE_TYPE, typename COMPONENT_TYPE, int PAD0_SIZE, int COMPONENT0_SIZE, int PAD1_SIZE, int COMPONENT1_SIZE, int PAD2_SIZE, int COMPONENT2_SIZE, int PAD3_SIZE, int COMPONENT3_SIZE, typename STORAGE_MANIPULATOR, typename COMPONENT_ORDERING, typename COLOR_SPACE>
class ComponentRGBAPacked: public ComponentRGBPackedDefinitions<STORAGE_TYPE, COMPONENT_TYPE, STORAGE_MANIPULATOR, COMPONENT_ORDERING, COLOR_SPACE>
{
private:
	typedef ComponentRGBPackedDefinitions<STORAGE_TYPE, COMPONENT_TYPE, STORAGE_MANIPULATOR, COMPONENT_ORDERING, COLOR_SPACE> _Super;
public:
	enum { BYTES_PER_PACKET = sizeof(STORAGE_TYPE) };

	// Compute offsets based on the sizes and paddings

	//	Apparently, template specialization is not allowed for member classes, so we have to do this outside...
	//	struct ComponentDefinition;
	//	template<>	struct ComponentDefinition<0> { enum { SIZE = COMPONENT0_SIZE, OFFSET = 8*sizeof(STORAGE_TYPE) - PAD0_SIZE - COMPONENT0_SIZE }; };
	//	template<>	struct ComponentDefinition<1> { enum { SIZE = COMPONENT1_SIZE, OFFSET = ComponentDefinition<0>::OFFSET - PAD1_SIZE - COMPONENT1_SIZE }; };
	//	template<>	struct ComponentDefinition<2> { enum { SIZE = COMPONENT2_SIZE, OFFSET = ComponentDefinition<1>::OFFSET - PAD2_SIZE - COMPONENT2_SIZE }; };
	//	template<>	struct ComponentDefinition<3> { enum { SIZE = COMPONENT3_SIZE, OFFSET = ComponentDefinition<2>::OFFSET - PAD3_SIZE - COMPONENT3_SIZE }; };
	
	typedef typename _Super::ComponentType ComponentType;
	typedef typename _Super::StorageManipulatorType StorageManipulatorType;
	typedef typename _Super::ComponentStorage ComponentStorage;

public:
	ComponentRGBAPacked() : _storage() 	{}
	
	ComponentType red() const { return component<COMPONENT_ORDERING::RED>(); }
	ComponentType green() const { return component<COMPONENT_ORDERING::GREEN>(); }
	ComponentType blue() const { return component<COMPONENT_ORDERING::BLUE>(); }
	ComponentType alpha() const { return component<COMPONENT_ORDERING::ALPHA>(); }

	void setRed(const ComponentType &val) { return setComponent<COMPONENT_ORDERING::RED>(val); }
	void setGreen(const ComponentType &val) { return setComponent<COMPONENT_ORDERING::GREEN>(val); }
	void setBlue(const ComponentType &val) { return setComponent<COMPONENT_ORDERING::BLUE>(val); }
	void setAlpha(const ComponentType &val) { return setComponent<COMPONENT_ORDERING::ALPHA>(val); }
	
	template<int INDEX>
	ComponentType component() const
	{
		return StorageManipulatorType::template readBits<ComponentStorage, ComponentType, ComponentDefinition4<INDEX, STORAGE_TYPE, PAD0_SIZE, COMPONENT0_SIZE, PAD1_SIZE, COMPONENT1_SIZE, PAD2_SIZE, COMPONENT2_SIZE, PAD3_SIZE, COMPONENT3_SIZE>::OFFSET, ComponentDefinition4<INDEX, STORAGE_TYPE, PAD0_SIZE, COMPONENT0_SIZE, PAD1_SIZE, COMPONENT1_SIZE, PAD2_SIZE, COMPONENT2_SIZE, PAD3_SIZE, COMPONENT3_SIZE>::SIZE>(&_storage); 
	}

	template<int INDEX>
	void setComponent(const ComponentType &val)
	{
		return StorageManipulatorType::template writeBits<ComponentStorage, ComponentType, ComponentDefinition4<INDEX, STORAGE_TYPE, PAD0_SIZE, COMPONENT0_SIZE, PAD1_SIZE, COMPONENT1_SIZE, PAD2_SIZE, COMPONENT2_SIZE, PAD3_SIZE, COMPONENT3_SIZE>::OFFSET, ComponentDefinition4<INDEX, STORAGE_TYPE, PAD0_SIZE, COMPONENT0_SIZE, PAD1_SIZE, COMPONENT1_SIZE, PAD2_SIZE, COMPONENT2_SIZE, PAD3_SIZE, COMPONENT3_SIZE>::SIZE>(&_storage, val);
	}

private:
	STORAGE_TYPE _storage;
};

#endif // __ITL_COMPONENTRGBPACKED_H__
