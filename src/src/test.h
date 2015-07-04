#include <cstdlib>
#include <cstdio>

#include "../RGB/RGBPixel.h"
#include "../XYZ/XYZPixel.h"
#include "../YCbCr/YCbCr422Pixel.h"
#include "../PixelConvert/PixelConverter.h"
#include "../PixMap/PixMap.h"
#include <algorithm>

#include <iostream>
using namespace std;


typedef unsigned char uint8;

typedef enum { PASSED = 0, FAILED, SKIPPED } TestResult;

template<int NB, class PIXELPACKET, typename COLORSPACE=typename PIXELPACKET::ColorSpace>
class PixelTest
{
public:
	enum { END = true };
};

class TestBase
{
public:
	enum { END = false };
	static const char *name() { return ""; }
};
#define FAILCHECK(_expr) { if (!(_expr)) { printf("[%s] FAILED (%s: %d)\n", #_expr, __FILE__, __LINE__); return FAILED; } }
#define EXPECTINT(_name, _value, _expect) { int _v = _value, _e = _expect; printf("  - %s: %d (%d)\n", #_name, (int)_v, (int)_e); FAILCHECK(_v == _e); }

template<class PIXELPACKET, typename COLORSPACE>
struct PixelTest<0, PIXELPACKET, COLORSPACE>: public TestBase
{
	static const char *name() { return "Basic Pixmap"; }

	TestResult operator()(const char *name)
	{ 
		const int WIDTH = 10, HEIGHT = 20;
		printf("Creating a PixMap<%s>\n", name);
		PixMap<PIXELPACKET> pm(WIDTH, HEIGHT);
		printf("size of structure: %d\n", (int)sizeof(pm));
		printf("size of data: %d\n", (int)pm.surface().size());

		printf("Checking attributes\n", name);
		EXPECTINT(width, pm.width(), WIDTH);
		EXPECTINT(height, pm.height(), HEIGHT);
		EXPECTINT(planes, pm.planes(), PIXELPACKET::PLANE_COUNT);

		return PASSED;
	}
};

template<class PIXELPACKET, typename COLORSPACE>
struct PixelTest<1, PIXELPACKET, COLORSPACE>: public TestBase
{
	static const char *name() { return "PixMapRef"; }

	TestResult operator()(const char *name)
	{ 
		const int WIDTH = 4, HEIGHT = 4;
		printf("Creating a PixMap<%s>\n", name);
		PixMap<PIXELPACKET> pm(WIDTH, HEIGHT);

		printf("Taking a reference: PixMapRef<%s>\n", name);
		PixMapRef<PIXELPACKET> ref = pm.ref();

		printf("size of pixmap: %d\n", (int)sizeof(pm));
		printf("size of pixmapref: %d\n", (int)sizeof(ref));

		printf("Checking attributes\n", name);
		EXPECTINT(width, ref.width(), WIDTH);
		EXPECTINT(height, ref.height(), HEIGHT);
		EXPECTINT(planes, ref.planes(), PIXELPACKET::PLANE_COUNT);

		return PASSED;
	}
};

template<class PIXELPACKET, int PLANECOUNT=PIXELPACKET::PLANE_COUNT>
struct RowAddressPrinter;

template<class PIXELPACKET>
struct RowAddressPrinter<PIXELPACKET, 1>
{
	static void print(const PixRowRef<PIXELPACKET> &row) 
	{
		printf("[%p]", row.plane0());
	}
};

template<class PIXELPACKET>
struct RowAddressPrinter<PIXELPACKET, 3>
{
	static void print(const PixRowRef<PIXELPACKET> &row)
	{
		printf("[%p, %p, %p]", row.plane0(), row.plane1(), row.plane2());
	}
};

template<class PIXELPACKET>
struct RowAddressPrinter<PIXELPACKET, 4>
{
	static void print(const PixRowRef<PIXELPACKET> &row)
	{
		printf("[%p, %p, %p, %p]", row.plane0(), row.plane1(), row.plane2(), row.plane3());
	}
};





template<class PIXELPACKET, int PLANECOUNT=PIXELPACKET::PLANE_COUNT>
struct PelAddressPrinter;

template<class PIXELPACKET>
struct PelAddressPrinter<PIXELPACKET, 1>
{
	static void print(const PIXELPACKET &pel) 
	{
		printf("[%p]", &pel);
	}
};

template<class PIXELPACKET>
struct PelAddressPrinter<PIXELPACKET, 3>
{
	static void print(const PIXELPACKET &pel)
	{
		printf("[%p, %p, %p]", pel.plane0Ptr(), pel.plane1Ptr(), pel.plane2Ptr());
	}
};

template<class PIXELPACKET>
struct PelAddressPrinter<PIXELPACKET, 4>
{
	static void print(const PIXELPACKET &pel)
	{
		printf("[%p, %p, %p, %p]", pel.plane0Ptr(), pel.plane1Ptr(), pel.plane2Ptr(), pel.plane3Ptr());
	}
};


template<class PIXELPACKET, int PLANECOUNT=PIXELPACKET::PLANE_COUNT>
struct Plane0AddressGetter
{
	static char* get(const PIXELPACKET &pel)
	{
		return (char*)pel.plane0Ptr();
	}
};

template<class PIXELPACKET>
struct Plane0AddressGetter<PIXELPACKET, 1>
{
	static char* get(const PIXELPACKET &pel) 
	{
		return (char*)&pel;
	}
};


template<class PIXELPACKET, typename COLORSPACE>
struct PixelTest<2, PIXELPACKET, COLORSPACE>: public TestBase
{
	static const char *name() { return "Row Iteration"; }

	TestResult operator()(const char *name)
	{ 
		const int WIDTH = 4, HEIGHT = 4;
		printf("Creating a PixMap<%s>\n", name);
		PixMap<PIXELPACKET> pm(WIDTH, HEIGHT);

		printf("Taking a reference: PixMapRef<%s>\n", name);
		PixMapRef<PIXELPACKET> ref = pm.ref();

		
		{
			printf("Testing the PixMapRef<%s>::RowIterator\n", name);
			int i = 0;
			for (typename PixMapRef<PIXELPACKET>::RowIterator iter = ref.begin(); iter != ref.end(); ++iter, ++i)
			{
				PixRowRef<PIXELPACKET> row = *iter;
				RowAddressPrinter<PIXELPACKET>::print(row);
				EXPECTINT(row_width, row.width(), WIDTH);
			}
			printf("\n");
			EXPECTINT(row_count, i, HEIGHT);
		}

		{
			printf("Testing the PixMapRef<%s>::ReverseRowIterator\n", name);
			int i = 0;
			for (typename PixMapRef<PIXELPACKET>::ReverseRowIterator iter = ref.rbegin(); iter != ref.rend(); ++iter, ++i)
			{
				PixRowRef<PIXELPACKET> row = *iter;
				RowAddressPrinter<PIXELPACKET>::print(row);
				EXPECTINT(row_width, row.width(), WIDTH);
			}
			printf("\n");
			EXPECTINT(row_count, i, HEIGHT);
		}

		{
			printf("Testing the PixMapRef<%s>::TopToBottomIterator\n", name);
			int i = 0;
			for (typename PixMapRef<PIXELPACKET>::TopToBottomIterator iter = ref.beginFromTop(); iter != ref.endFromTop(); ++iter, ++i)
			{
				PixRowRef<PIXELPACKET> row = *iter;
				RowAddressPrinter<PIXELPACKET>::print(row);
				EXPECTINT(row_width, row.width(), WIDTH);
			}
			printf("\n");
			EXPECTINT(row_count, i, HEIGHT);
		}

		{
			printf("Testing the PixMapRef<%s>::BottomToTopIterator\n", name);
			int i = 0;
			for (typename PixMapRef<PIXELPACKET>::BottomToTopIterator iter = ref.beginFromBottom(); iter != ref.endFromBottom(); ++iter, ++i)
			{
				PixRowRef<PIXELPACKET> row = *iter;
				RowAddressPrinter<PIXELPACKET>::print(row);
				EXPECTINT(row_width, row.width(), WIDTH);
			}
			printf("\n");
			EXPECTINT(row_count, i, HEIGHT);
		}

		{
			printf("Testing random access\n", name);
			for (int i = 0; i < ref.height(); ++i)
			{
				PixRowRef<PIXELPACKET> row = ref[i];
				RowAddressPrinter<PIXELPACKET>::print(row);
				EXPECTINT(row_width, row.width(), WIDTH);
			}
			printf("\n");
		}

		return PASSED;
	}
};



template<class PIXELPACKET, typename COLORSPACE>
struct PixelTest<3, PIXELPACKET, COLORSPACE>: public TestBase
{
	static const char *name() { return "Row Iteration"; }

	TestResult operator()(const char *name)
	{ 
		const int WIDTH = 4, HEIGHT = 4;
		printf("Creating a PixMap<%s>\n", name);
		PixMap<PIXELPACKET> pm(WIDTH, HEIGHT);

		printf("Taking a reference: PixMapRef<%s>\n", name);
		PixMapRef<PIXELPACKET> ref = pm.ref();

		printf("Fetching the first row\n");
		PixRowRef<PIXELPACKET> row = ref[0];

		
		{
			printf("Testing the PixRowRef<%s>::Iterator\n", name);

			int bytePerPlane0 = PIXELPACKET::Plane0Type::BYTES_PER_PACKET;
			char *p0 = Plane0AddressGetter<PIXELPACKET>::get(*row.begin());
			char *p1 = Plane0AddressGetter<PIXELPACKET>::get(*(row.begin()+1));
			char *p1e = p0 + bytePerPlane0;
			EXPECTINT(ptr_offset, (intptr_t)p1e, (intptr_t)p1);

			int i = 0;
			for (typename PixRowRef<PIXELPACKET>::Iterator iter = row.begin(); iter != row.end(); ++iter, ++i)
			{
				PelAddressPrinter<PIXELPACKET>::print(*iter);
				printf("\n");
			}
			printf("\n");
			EXPECTINT(pix_count, i, ref.width());
		}

		{
			printf("Testing the PixRowRef<%s>::ReverseIterator\n", name);

			int bytePerPlane0 = PIXELPACKET::Plane0Type::BYTES_PER_PACKET;
			char *p0 = Plane0AddressGetter<PIXELPACKET>::get(*row.rbegin());
			char *p1 = Plane0AddressGetter<PIXELPACKET>::get(*(row.rbegin()+1));
			char *p1e = p0 - bytePerPlane0;
			EXPECTINT(ptr_offset, (intptr_t)p1e, (intptr_t)p1);

			int i = 0;
			for (typename PixRowRef<PIXELPACKET>::ReverseIterator iter = row.rbegin(); iter != row.rend(); ++iter, ++i)
			{
				PelAddressPrinter<PIXELPACKET>::print(*iter);
				printf("\n");
			}
			printf("\n");
			EXPECTINT(pix_count, i, ref.width());
		}


		{
			printf("Testing random access\n", name);

			int bytePerPlane0 = PIXELPACKET::Plane0Type::BYTES_PER_PACKET;
			char *p0 = Plane0AddressGetter<PIXELPACKET>::get(row[0]);
			char *p1 = Plane0AddressGetter<PIXELPACKET>::get(row[1]);
			char *p1e = p0 + bytePerPlane0;
			EXPECTINT(ptr_offset, (intptr_t)p1e, (intptr_t)p1);

			for (int i = 0; i < row.width(); ++i)
			{
				PelAddressPrinter<PIXELPACKET>::print(row[i]);
				printf("\n");
			}
			printf("\n");
		}




		return PASSED;
	}
};






template<class PIXELPACKET, typename COLORSPACE>
struct PixelTest<4, PIXELPACKET, COLORSPACE>: public TestBase
{
	static const char *name() { return "Row Iteration"; }

	TestResult operator()(const char *name)
	{ 
		const int WIDTH = 4, HEIGHT = 4;
		printf("Creating a PixMap<%s>\n", name);
		PixMap<PIXELPACKET> pm(WIDTH, HEIGHT);

		printf("Taking a reference: PixMapRef<%s>\n", name);
		PixMapRef<PIXELPACKET> ref = pm.ref();

		
		printf("Full Iterator access\n");
		for (typename PixMapRef<PIXELPACKET>::RowIterator rowIter = ref.begin(); rowIter != ref.end(); ++rowIter)
		{
			for (typename PixRowRef<PIXELPACKET>::Iterator pIter = rowIter->begin(); pIter != rowIter->end(); ++pIter)
			{
				PelAddressPrinter<PIXELPACKET>::print(*pIter);
			}
			printf("\n");
		}

		printf("Full random access\n");
		for (int y = 0; y < ref.height(); ++y)
		{
			for (int x = 0; x < ref.width(); ++x)
			{
				PelAddressPrinter<PIXELPACKET>::print(ref[y][x]);
			}
			printf("\n");
		}

		return PASSED;
	}
};

template<typename PIXELPACKET, typename COLORSPACE=typename PIXELPACKET::ColorSpace>
class ClearPixel;

template<typename PIXELPACKET>
class ClearPixel<PIXELPACKET, ColorSpace_sRGB>
{
public:
	void operator()(PIXELPACKET &pixel) const
	{
		pixel.setRGB(0, 0, 0);
	}
};

template<typename PIXELPACKET>
class ClearPixel<PIXELPACKET, ColorSpace_YCbCr_ITU601>
{
public:
	void operator()(PIXELPACKET &pixel) const
	{
		pixel.setYCbCr(0, 0, 0);
	}
};


template<class PIXELPACKET, typename COLORSPACE=typename PIXELPACKET::ColorSpace>
class PrintRGB;

template<class PIXELPACKET>
class PrintRGB<PIXELPACKET, ColorSpace_sRGB>
{
public:
	void operator()(PIXELPACKET &pixel) const
	{
		printf("rgb: %d,%d,%d\n", pixel.red(), pixel.green(), pixel.blue());
	}
};


template<class PIXELPACKET>
class PrintRGB<PIXELPACKET, ColorSpace_YCbCr_ITU601>
{
public:
	void operator()(PIXELPACKET &pixel) const
	{
		printf("ycbcr: %d,%d,%d\n", pixel.luminance(), pixel.chromaBlue(), pixel.chromaRed());
	}
};

template<class PIXELPACKET, typename COLORSPACE>
struct PixelTest<5, PIXELPACKET, COLORSPACE>: public TestBase
{
	static const char *name() { return "For Each"; }

	TestResult operator()(const char *name)
	{ 
		const int WIDTH = 4, HEIGHT = 4;
		printf("Creating a PixMap<%s>\n", name);
		PixMap<PIXELPACKET> pm(WIDTH, HEIGHT);

		printf("Taking a reference: PixMapRef<%s>\n", name);
		PixMapRef<PIXELPACKET> ref = pm.ref();

		printf("Clearing all RGB to 0\n");
		ref.forEachPacket(ClearPixel<PIXELPACKET>());

		printf("Printing result\n");
		ref.forEachPacket(PrintRGB<PIXELPACKET>());
		return PASSED;
	}
};

template<typename PIXELPACKET, typename COLORSPACE=typename PIXELPACKET::ColorSpace>
class BlendRGB;

template<typename PIXELPACKET>
class BlendRGB<PIXELPACKET, ColorSpace_sRGB>
{
	float _weight;
public:
	BlendRGB(float v) : _weight(v) {}
	void operator()(const PIXELPACKET &src0, const PIXELPACKET &src1, PIXELPACKET *dst) const
	{	
		dst->setRGB(
			typename PIXELPACKET::RedComponentType(src0.red() * _weight + src1.red() * (1 - _weight)),
			typename PIXELPACKET::RedComponentType(src0.green() * _weight + src1.green() * (1 - _weight)),
			typename PIXELPACKET::RedComponentType(src0.blue() * _weight + src1.blue() * (1 - _weight))
			);
	}
};

template<typename PIXELPACKET>
class BlendRGB<PIXELPACKET, ColorSpace_YCbCr_ITU601>
{
	float _weight;
public:
	BlendRGB(float v) : _weight(v) {}
	void operator()(const PIXELPACKET &src0, const PIXELPACKET &src1, PIXELPACKET *dst) const
	{	
		dst->setYCbCr(
			typename PIXELPACKET::YComponentType(src0.luminance() * _weight + src1.luminance() * (1 - _weight)),
			typename PIXELPACKET::YComponentType(src0.chromaBlue() * _weight + src1.chromaBlue() * (1 - _weight)),
			typename PIXELPACKET::YComponentType(src0.chromaRed() * _weight + src1.chromaRed() * (1 - _weight))
			);
	}
};

template<typename PIXELPACKET, typename COLORSPACE=typename PIXELPACKET::ColorSpace>
class SetValue;

template<typename PIXELPACKET>
class SetValue<PIXELPACKET, ColorSpace_sRGB>
{
	typename PIXELPACKET::Plane0Type::ComponentType _v;
public:
	SetValue(typename PIXELPACKET::Plane0Type::ComponentType v) : _v(v) {}
	void operator()(PIXELPACKET &dst) const
	{	
		dst.setRGB(_v, _v, _v);
	}
};

template<typename PIXELPACKET>
class SetValue<PIXELPACKET, ColorSpace_YCbCr_ITU601>
{
	typename PIXELPACKET::Plane0Type::ComponentType _v;
public:
	SetValue(typename PIXELPACKET::Plane0Type::ComponentType v) : _v(v) {}
	void operator()(PIXELPACKET &dst) const
	{	
		dst.setYCbCr(_v, _v, _v);
	}
};

template<class PIXELPACKET, typename COLORSPACE>
struct PixelTest<6, PIXELPACKET, COLORSPACE>: public TestBase
{
	static const char *name() { return "Duplicate"; }

	TestResult operator()(const char *name)
	{ 
		const int WIDTH = 4, HEIGHT = 4;
		printf("Creating a PixMap<%s>\n", name);
		PixMap<PIXELPACKET> pm(WIDTH, HEIGHT);

		printf("Taking a reference: PixMapRef<%s>\n", name);
		PixMapRef<PIXELPACKET> ref = pm.ref();

		ref.forEachPacket(ClearPixel<PIXELPACKET>());
		ref.forEachPacket(PrintRGB<PIXELPACKET>());

		PixMap<PIXELPACKET> *dup = ref.duplicate();
		dup->ref().forEachPacket(PrintRGB<PIXELPACKET>());


		PixMap<PIXELPACKET> pm2(WIDTH, HEIGHT);
		pm.ref().forEachPacket(SetValue<PIXELPACKET>(0));
		pm2.ref().forEachPacket(SetValue<PIXELPACKET>(2));
		PixMapComposer2In1Out::forEach(pm.ref(), pm2.ref(), dup->ref(), BlendRGB<PIXELPACKET>(0.5));
		dup->ref().forEachPacket(PrintRGB<PIXELPACKET>());

		delete dup;
		return PASSED;
	}
};
