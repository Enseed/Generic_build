/*******************************************************************************
 Copyright 2007 Enseed inc.
 
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

 Author: Gaspard Petit
*******************************************************************************/
#ifndef __GENERIC_IMAGE_PIXMAP__
#define __GENERIC_IMAGE_PIXMAP__

//==============================================================================
//	EXTERNAL DECLARATIONS
//==============================================================================
#include "../Math/Rational.h"
#include "ImageUtils/PixMapResample.h"
#include "../Geometry/Rect.h"
#include "../Base/Types.h"
#include "ColorProfiles.h"

#ifdef GENERIC_NAMESPACE
namespace GENERIC_NAMESPACE {
#endif

//==============================================================================
//	CLASS PixMap
//==============================================================================
template<typename PixelT>
class PixMap
{
public:
	typedef typename PixelT::Component 	Component;
	typedef typename PixelT::ConstPixel 	ConstPixel;
	typedef PixelT 				Pixel;

	class ConstRow
	{
	public:
		typedef typename PixMap::Component	 	Component;
		typedef typename PixMap::ConstPixel 	ConstPixel;
		typedef typename PixMap::Pixel			Pixel;

		ConstRow()
		:
			mBegin(),
			mEnd(),
			mRowLength()
		{}
			
		ConstRow(const Component *rowBegin, int componentsPerRow, int componentsToNextRow)
		:
			mBegin(const_cast<Component*>(rowBegin)),
			mEnd(const_cast<Component*>(rowBegin + componentsPerRow)),
			mRowLength(componentsToNextRow)
		{}
		
		ConstRow(const ConstRow &rhs)
		:
			mBegin(rhs.mBegin),
			mEnd(rhs.mEnd),
			mRowLength(rhs.mRowLength)
		{}
		
		ConstRow& operator = (const ConstRow &rhs)
		{	
			mBegin = rhs.mBegin;
			mEnd = rhs.mEnd;
			mRowLength = rhs.mRowLength;
			return *this;
		}

		virtual ~ConstRow() {}
		
		ConstPixel begin() const
		{	return ConstPixel(mBegin);	}

		ConstPixel end() const
		{	return ConstPixel(mEnd);	}

		int32 componentsPerRow() const
		{	return static_cast<int32>(mEnd - mBegin);	}

		int32 pixelPerRow() const
		{	return componentsPerRow() / pixelLength();	}

		ConstRow operator + (int i) const
		{	return ConstRow(mBegin + i * mRowLength, componentsPerRow(), mRowLength);	}

		ConstRow operator - (int i) const
		{	return ConstRow(mBegin - i * mRowLength, componentsPerRow(), mRowLength);	}

		ConstRow& operator += (int i)
		{	mBegin += i * mRowLength;	mEnd += i * mRowLength;	return *this;	}

		ConstRow& operator -= (int i)
		{	mBegin -= i * mRowLength;	mEnd -= i * mRowLength;	return *this;	}

		ConstRow& operator ++ ()
		{	mBegin += mRowLength;	mEnd += mRowLength;		return *this;	}

		ConstRow& operator -- ()
		{	mBegin -= mRowLength;	mEnd -= mRowLength;	return *this;	}

		ConstRow operator ++ (int)
		{	ConstRow copy(*this);	mBegin += mRowLength;	mEnd += mRowLength;		return copy;	}

		ConstRow operator -- (int)
		{	ConstRow copy(*this); 	mBegin -= mRowLength;	mEnd -= mRowLength;	return copy;	}

		ConstPixel operator * () const
		{	return ConstPixel(mBegin);	}
		
		ConstPixel operator [] (int i) const
		{	return ConstPixel(mBegin) + i;	}
		
		bool operator < (const ConstRow& rhs) const
		{	return mBegin < rhs.mBegin;		}

		bool operator <= (const ConstRow& rhs) const
		{	return mBegin <= rhs.mBegin;		}

		bool operator > (const ConstRow& rhs) const
		{	return mBegin > rhs.mBegin;		}

		bool operator >= (const ConstRow& rhs) const
		{	return mBegin >= rhs.mBegin;		}

		bool operator == (const ConstRow& rhs) const
		{	return mBegin == rhs.mBegin;		}

		bool operator != (const ConstRow& rhs) const
		{	return mBegin != rhs.mBegin;		}
		
		operator ConstPixel* () const
		{	return ConstPixel(mBegin);	}
		
		int rowLength() const
		{
			return mRowLength;
		}

	protected:
		Component *mBegin;
		Component *mEnd;
		int mRowLength;
	};


	class Row: public ConstRow
	{
		
	public:
		Row()
		:
			ConstRow()
		{}
			
		Row(Component *rowBegin, int componentsPerRow, int componentsToNextRow)
		:
			ConstRow(rowBegin, componentsPerRow, componentsToNextRow)
		{}
		
		Row(const Row &rhs)
		:
			ConstRow(rhs)
		{}
		
		Row& operator = (const Row &rhs)
		{	ConstRow::operator=(rhs);	return *this;	}

		~Row() {}
		
		template <typename RHS>
		Row& copy(const RHS &rhs)
		{
			Pixel pix;
			typename RHS::ConstPixel srcPix;
			ASSERT(this->pixelPerRow() == rhs.pixelPerRow());
			for (pix = begin(), srcPix = rhs.begin(); pix != end(); ++pix, ++srcPix)
			{
				pix.copy(srcPix);
			}
			return *this;
		}
		
		Pixel begin() const
		{	return Pixel(ConstRow::mBegin);	}

		Pixel end() const
		{	return Pixel(ConstRow::mEnd);	}

		Row operator + (int i) const
		{	return Row(ConstRow::mBegin + i * ConstRow::mRowLength, ConstRow::componentsPerRow(), ConstRow::mRowLength);	}

		Row operator - (int i) const
		{	return Row(ConstRow::mBegin - i * ConstRow::mRowLength, ConstRow::componentsPerRow(), ConstRow::mRowLength);	}

		Row& operator += (int i)
		{	ConstRow::mBegin += i * ConstRow::mRowLength;	ConstRow::mEnd += i * ConstRow::mRowLength;	return *this;	}

		Row& operator -= (int i)
		{	ConstRow::mBegin -= i * ConstRow::mRowLength;	ConstRow::mEnd -= i * ConstRow::mRowLength;	return *this;	}

		Row& operator ++ ()
		{	ConstRow::mBegin += ConstRow::mRowLength;	ConstRow::mEnd += ConstRow::mRowLength;		return *this;	}

		Row& operator -- ()
		{	ConstRow::mBegin -= ConstRow::mRowLength;	ConstRow::mEnd -= ConstRow::mRowLength;	return *this;	}

		Row operator ++ (int)
		{	Row copy(*this);	ConstRow::mBegin += ConstRow::mRowLength;	ConstRow::mEnd += ConstRow::mRowLength;		return copy;	}

		Row operator -- (int)
		{	Row copy(*this); 	mBegin -= mRowLength;	mEnd -= mRowLength;	return copy;	}

		Pixel operator * () const
		{	return Pixel(ConstRow::mBegin);	}
		
		Pixel operator [] (int i) const
		{	return Pixel(ConstRow::mBegin) + i;	}
		
		operator Pixel* () const
		{	return Pixel(ConstRow::mBegin);	}
	};
	
	PixMap()
	:
		mWidth(0),
		mHeight(0),
		mRowLength(0),
		mIsDataOwner(false),
		mBaseAddr(NULL),
		mPixelRatio(1,1),
		mColorProfile(Pixel::defaultColorProfile())
	{}
	
	PixMap(int32 width, int32 height, const seed::Rational &ratio, ColorProfile profile)
	:
		mWidth(width),
		mHeight(height),
		mRowLength(width*Pixel::pixelLength()),
		mIsDataOwner(true),
		mBaseAddr(new Component[height*mRowLength]),
		mBegin(Row(mBaseAddr, mWidth * pixelLength(), mRowLength)),
		mEnd(Row(mBaseAddr + mHeight * mRowLength, mWidth * pixelLength(), mRowLength)),
		mPixelRatio(ratio),
		mColorProfile(profile)
	{}

	PixMap(int32 width, int32 height, int32 rowLength, const seed::Rational &ratio, ColorProfile profile)
	:
		mWidth(width),
		mHeight(height),
		mRowLength(rowLength),
		mIsDataOwner(true),
		mBaseAddr(new Component[height*mRowLength]),
		mBegin(Row(mBaseAddr, mWidth * pixelLength(), mRowLength)),
		mEnd(Row(mBaseAddr + mHeight * mRowLength, mWidth * pixelLength(), mRowLength)),
		mPixelRatio(ratio),
		mColorProfile(profile)
	{}

	PixMap(Component *data, int32 width, int32 height, int32 rowLength, const seed::Rational &ratio, ColorProfile profile)
	:
		mWidth(0),
		mHeight(0),
		mRowLength(0),
		mIsDataOwner(false),
		mBaseAddr(NULL),
		mBegin(Row(mBaseAddr, mWidth * pixelLength(), mRowLength)),
		mEnd(Row(mBaseAddr + mHeight * mRowLength, mWidth * pixelLength(), mRowLength)),
		mPixelRatio(ratio),
		mColorProfile(profile)
	{
		setPixelsNoCopy(data, width, height, rowLength, profile);	
	}


private:
	//	use "copy" instead
	PixMap& operator = (const PixMap &rhs);

public:
	PixMap(const PixMap& rhs)
	:
		mWidth(rhs.width()),
		mHeight(rhs.height()),
		mRowLength(rhs.rowLength()),
		mIsDataOwner(false),
		mBaseAddr(const_cast<Component*>(rhs.baseAddr())), // fixme
		mBegin(Row(mBaseAddr, mWidth * pixelLength(), mRowLength)),
		mEnd(Row(mBaseAddr + mHeight * mRowLength, mWidth * pixelLength(), mRowLength)),
		mPixelRatio(rhs.pixelRatio()),
		mColorProfile(rhs.colorProfile())
	{}
	
	template<class RHS>
	PixMap(PixMap<RHS> &rhs)
	:
		mWidth(rhs.width()),
		mHeight(rhs.height()),
		mRowLength(rhs.rowLength()),
		mIsDataOwner(false),
		mBaseAddr(rhs.baseAddr()),
		mBegin(Row(mBaseAddr, mWidth * pixelLength(), mRowLength)),
		mEnd(Row(mBaseAddr + mHeight * mRowLength, mWidth * pixelLength(), mRowLength)),
		mPixelRatio(rhs.pixelRatio()),
		mColorProfile(rhs.colorProfile())
	{}
		

	template<class RHS>
	PixMap& copy(const RHS &rhs)
	{
		bool resized = resize(rhs.width(), rhs.height(), rhs.width()*Pixel::pixelLength());
		ASSERT(resized);
		if (!resized)	return *this;
		
		Row row;
		typename RHS::ConstRow srcRow;

		for (row = begin(), srcRow = rhs.begin(); row != end(); ++row, ++srcRow)
		{
			row.copy(srcRow);
		}

		setColorProfile(rhs.colorProfile());
		return *this;
	}

	template<class RHS>
	PixMap& resample(const RHS &rhs)
	{		
		// this should not be here...
		return PixMapResample::nearestNeighbor_hasChanged(rhs, *this);
	}

	PixMap subImageReference(const seed::Recti &bounds)
	{
		PixMap subImage((*this)[bounds.pos.y][bounds.pos.x], bounds.size.x, bounds.size.y, mRowLength, mPixelRatio, mColorProfile);
		return subImage;
	}

public:
	~PixMap()
	{
		if (mIsDataOwner)	delete [] mBaseAddr;
	}
	
	bool resize(int32 width, int32 height)
	{
		int rowLength = width * pixelLength();
		return resize(width, height, rowLength);
	}

	bool resize(int32 width, int32 height, int32 rowLength)
	{
		if (mIsDataOwner)
		{
			if (height * rowLength > mHeight * mRowLength)
			{
				ASSERT(mIsDataOwner); // otherwise, it's probably a bug
				if (mIsDataOwner)	delete [] mBaseAddr;
				mBaseAddr = new Component[height * rowLength];
				mIsDataOwner = true;
			}

			mWidth = width;
			mHeight = height;
			mRowLength = rowLength;
			mBegin = Row(mBaseAddr, mWidth * pixelLength(), mRowLength);
			mEnd = Row(mBaseAddr + mHeight * mRowLength, mWidth * pixelLength(), mRowLength);
			return true;
		}
		else
			return (height == mHeight) && (width == mWidth) && (mRowLength >= rowLength);
	}
	
	const seed::Rational& pixelRatio() const
	{
		return mPixelRatio;
	}

	void setPixelRatio(const seed::Rational &ratio)
	{
		mPixelRatio = ratio;
	}

	void setPixels(
		const Component *data,
		int32 width,
		int32 height,
		int32 rowLength,
		ColorProfile profile
	)
	{
		bool resized = resize(width, height, rowLength);
		if (!resized)	{ ASSERT(0); return; }

		memcpy(mBaseAddr, data, height * rowLength);
		mColorProfile = profile;
	}
	
	void setPixelsNoCopy(
		Component *data,
		int32 width,
		int32 height,
		int32 rowLength,
		ColorProfile profile
	)
	{
		if (mIsDataOwner)	delete [] mBaseAddr;

		mBaseAddr = data;
		mIsDataOwner = false;

		mWidth = width;
		mHeight = height;
		mRowLength = rowLength;
		mBegin = Row(mBaseAddr, mWidth * pixelLength(), mRowLength);
		mEnd = Row(mBaseAddr + mHeight * mRowLength, mWidth * pixelLength(), mRowLength);
		mColorProfile = profile;
	}
	
	void setPixelsNoCopyConst(
		const Component *data,
		int32 width,
		int32 height,
		int32 rowLength
	)
	{
		if (mIsDataOwner)	delete [] mBaseAddr;

		mBaseAddr = const_cast<Component*>(data);
		mIsDataOwner = false;

		mWidth = width;
		mHeight = height;
		mRowLength = rowLength;
		mBegin = Row(mBaseAddr, mWidth * pixelLength(), mRowLength);
		mEnd = Row(mBaseAddr + mHeight * mRowLength, mWidth * pixelLength(), mRowLength);
	}
	
	int32 rowLength() const
	{	return mRowLength;	}

	int32 height() const
	{	return mHeight;		}

	int32	width() const
	{	return mWidth;		}

	Component*	baseAddr()
	{	return mBaseAddr;	}
	
	const Component* baseAddr() const
	{	return mBaseAddr;	}

	ConstRow begin() const
	{	return mBegin; 		}

	Row begin()
	{	return mBegin; 		}

	Row last()
	{	return mEnd-1;		}

	const Row& end() const
	{	return mEnd;		}

	Row operator [] (int i)
	{	return mBegin + i;	}

	ConstRow operator [] (int i) const
	{	return mBegin + i;	}

	static int pixelLength()
	{	return Pixel::pixelLength();	}

	ColorProfile colorProfile() const
	{	return mColorProfile;	}

	void setColorProfile(ColorProfile colorProfile)
	{	mColorProfile = colorProfile;	}

private:
	int32				mWidth;
	int32				mHeight;
	int32				mRowLength;
	bool				mIsDataOwner;
	Component			*mBaseAddr;
	Row					mBegin;
	Row					mEnd;
	seed::Rational			mPixelRatio;
	ColorProfile		mColorProfile;
};

#ifdef GENERIC_NAMESPACE
}
#endif

#endif // __GENERIC_IMAGE_PIXMAP__
