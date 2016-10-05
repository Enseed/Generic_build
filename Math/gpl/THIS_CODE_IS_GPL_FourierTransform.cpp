/*******************************************************************************
 Copyright 2008 Enseed inc.

 This code wraps FFTW for comparison purposes. It is licensed under the same 
 GPL license as the code it refers to. For futher details, visit 
 http://www.fftw.org/
 
*******************************************************************************/
//==============================================================================
//	EXTERNAL DECLARATIONS
//==============================================================================
#include "../FourierTransform.fftw3.h"
#include <cmath>
#include <fftw3.h>	//	implemented with Fastest Fourier Transform in the West
					//	(see http://www.fftw.org/)
#include <cassert>

#ifdef GENERIC_LAYER_NAMESPACE
namespace GENERIC_LAYER_NAMESPACE {
#endif
//==============================================================================
//	CLASS FTBase
//==============================================================================
class FTBase
{
public:
	FTBase(int width, int height, int depth)
	:
		mWidth(width),
		mHeight(height),
		mDepth(depth),
		mRank(depth ? 3 : height ? 2 : 1),
		mFPlan(NULL),
		mRPlan(NULL)
	{}
	
	virtual ~FTBase()
	{
		if (mFPlan) fftw_destroy_plan(mFPlan);
		if (mRPlan)	fftw_destroy_plan(mRPlan);
	}

	//--------------------------------------------------------------------------
	//
	virtual int spatialWidth()	 {	return mWidth;		}
	virtual int spatialHeight()	 {	return mHeight;		}
	virtual int spatialDepth()	 {	return mDepth;		}
	virtual int spectralWidth()  {	return mWidth;		}
	virtual int spectralHeight() {	return mHeight;		}
	virtual int spectralDepth()	 {	return mDepth;		}
	virtual int spatialLength()  = 0;
	virtual int spectralLength() = 0;

	virtual void forward(double *spat, double *spec) = 0;
	virtual void reverse(double *spat, double *spec) = 0;

	//--------------------------------------------------------------------------
	//
	void forwardNormalized(double *spat, double *spec)
	{
		forward(spat, spec);

		double scale = 1/sqrt(spatialLength());
		for (int i = 0 ; i < spectralLength(); ++i)
			spec[i] *= scale;
	}
	
	//--------------------------------------------------------------------------
	//
	void reverseNormalized(double *spec, double *spat)
	{
		reverse(spec, spat);

		double scale = 1/sqrt(spatialLength());
		for (int i = 0 ; i < spatialLength(); ++i)
			spat[i] *= scale;
	}

public:
	int mWidth;
	int mHeight;
	int mDepth;
	int mRank;
	fftw_plan mFPlan;
	fftw_plan mRPlan;
private:
	FTBase(const FTBase&);
	FTBase& operator=(const FTBase&);
};

//==============================================================================
//	CLASS FTR2C
//==============================================================================
//	Used as a template argument for the FourierTransform (performs the
//	real to complex transforms
class FTR2C: public FTBase
{
public:
	//--------------------------------------------------------------------------
	//
	FTR2C(int width, int height, int depth)
	:
		FTBase(width, height, depth)
	{}

	virtual int spectralWidth()  {	return mWidth/2+1;	}	// need only half width
	virtual int spatialLength()  {	return spatialWidth()*(spatialHeight() ? spatialHeight() : 1)*(spatialDepth() ? spatialDepth() : 1);	}	
	virtual int spectralLength() {	return 2*spectralWidth()*(spectralHeight() ? spectralHeight() : 1)*(spectralDepth() ? spectralDepth() : 1);	}	

	//--------------------------------------------------------------------------
	//
	void forward(double *spat, double *spec)
	{
		if (!mFPlan)
		{
			int dim[3], i = 0;
			switch(mRank)
			{
				case(3):	dim[i++] = mDepth;
				case(2):	dim[i++] = mHeight;
				case(1):	dim[i++] = mWidth;
				break;
				
				default:
					assert(0);
			}

			mFPlan = fftw_plan_dft_r2c(
				mRank, dim,
				spat, reinterpret_cast<fftw_complex*>(spec), 
				FFTW_ESTIMATE
			);
		}
	
		fftw_execute_dft_r2c(
			mFPlan, 
			spat,
			reinterpret_cast<fftw_complex*>(spec)
		);
	}
	
	//--------------------------------------------------------------------------
	//
	void reverse(double *spec, double *spat)
	{
		if (!mRPlan)
		{
			int dim[3], i = 0;
			switch(mRank)
			{
				case(3):	dim[i++] = mDepth;
				case(2):	dim[i++] = mHeight;
				case(1):	dim[i++] = mWidth;
				break;
				
				default:
					assert(0);
			}

			mRPlan = fftw_plan_dft_c2r(
				mRank, dim,
				reinterpret_cast<fftw_complex*>(spec), spat, 
				FFTW_ESTIMATE
			);
		}
			
	
		fftw_execute_dft_c2r(
			mRPlan, 
			reinterpret_cast<fftw_complex*>(spec), 
			spat
		);
	}
		
private:
	FTR2C(const FTR2C&);
	FTR2C& operator=(const FTR2C&);
};

//==============================================================================
//	CLASS FTC2C
//==============================================================================
//	Used as a template argument for the FourierTransform (performs the
//	complex to complex transforms
class FTC2C: public FTBase
{
public:
	//--------------------------------------------------------------------------
	//
	FTC2C(int width, int height, int depth)
	:
		FTBase(width, height, depth)
	{}

	virtual int spatialLength()  {	return 2*spatialWidth()*(spatialHeight() ? spatialHeight() : 1)*(spatialDepth() ? spatialDepth() : 1);	}	
	virtual int spectralLength() {	return 2*spectralWidth()*(spectralHeight() ? spectralHeight() : 1)*(spectralDepth() ? spectralDepth() : 1);	}	

	//--------------------------------------------------------------------------
	//
	void forward(double *spat, double *spec)
	{
		if (!mFPlan)
		{
			int dim[3], i = 0;
			switch(mRank)
			{
				case(3):	dim[i++] = mDepth;
				case(2):	dim[i++] = mHeight;
				case(1):	dim[i++] = mWidth;
				break;
				
				default:
					assert(0);
			}

			mFPlan = fftw_plan_dft(
				mRank, dim,
				reinterpret_cast<fftw_complex*>(spat), 
				reinterpret_cast<fftw_complex*>(spec), 
				FFTW_FORWARD,
				FFTW_ESTIMATE
			);
		}
	
		fftw_execute_dft(
			mFPlan, 
			reinterpret_cast<fftw_complex*>(spat), 
			reinterpret_cast<fftw_complex*>(spec)
		);
		
		double scale = 1/sqrt(mWidth*mHeight);
		for (int i = 0 ; i < (mWidth/2+1)*mHeight*2; ++i)
			spec[i] *= scale;
	}
	
	//--------------------------------------------------------------------------
	//
	void reverse(double *spec, double *spat)
	{
		if (!mRPlan)
		{
			int dim[3], i = 0;
			switch(mRank)
			{
				case(3):	dim[i++] = mDepth;
				case(2):	dim[i++] = mHeight;
				case(1):	dim[i++] = mWidth;
				break;
				
				default:
					assert(0);
			}

			mRPlan = fftw_plan_dft(
				mRank, dim,
				reinterpret_cast<fftw_complex*>(spec),
				reinterpret_cast<fftw_complex*>(spat),
				FFTW_BACKWARD,
				FFTW_ESTIMATE
			);
		}
	
		fftw_execute_dft(
			mRPlan,
			reinterpret_cast<fftw_complex*>(spec),
			reinterpret_cast<fftw_complex*>(spat)
		);
	
		double scale = 1/sqrt(mWidth*mHeight);
		for (int i = 0 ; i < mWidth*mHeight; ++i)
			spat[i] *= scale;
	}

private:
	FTC2C(const FTC2C&);
	FTC2C& operator=(const FTC2C&);
};

//==============================================================================
//	CLASS: FourierTransform
//==============================================================================

//------------------------------------------------------------------------------
//
template <typename T>
FourierTransform<T>::FourierTransform(int width, int height, int depth)
:
	mImp(new T(width, height, depth))
{}

//------------------------------------------------------------------------------
//
template <typename T>
FourierTransform<T>::~FourierTransform()
{
	delete mImp;
}

//------------------------------------------------------------------------------
//
template <typename T>
int FourierTransform<T>::spatialWidth()
{
	return mImp->spatialWidth();
}

//------------------------------------------------------------------------------
//
template <typename T>
int FourierTransform<T>::spatialHeight()
{
	return mImp->spatialHeight();
}

//------------------------------------------------------------------------------
//
template <typename T>
int FourierTransform<T>::spectralWidth()
{
	return mImp->spectralWidth();
}

//------------------------------------------------------------------------------
//
template <typename T>
int FourierTransform<T>::spectralHeight()
{
	return mImp->spectralHeight();
}	

//------------------------------------------------------------------------------
//
template <typename T>
void FourierTransform<T>::forward(double *spat, double *spec)
{
	mImp->forward(spat, spec);
}

//------------------------------------------------------------------------------
//
template <typename T>
void FourierTransform<T>::reverse(double *spec, double *spat)
{
	mImp->reverse(spec, spat);
}

//------------------------------------------------------------------------------
//
template <typename T>
void FourierTransform<T>::forwardNormalized(double *spat, double *spec)
{
	mImp->forwardNormalized(spat, spec);
}

//------------------------------------------------------------------------------
//
template <typename T>
void FourierTransform<T>::reverseNormalized(double *spec, double *spat)
{
	mImp->reverseNormalized(spec, spat);
}

//==============================================================================
//	EXPLICIT INSTANTIATION
//==============================================================================
template class FourierTransform<FTC2C>;
template class FourierTransform<FTR2C>;

#ifdef GENERIC_LAYER_NAMESPACE
}
#endif
