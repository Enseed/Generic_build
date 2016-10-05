#ifndef __ITL_ALGO_RESAMPLE_NEAREST_H__
#define __ITL_ALGO_RESAMPLE_NEAREST_H__

template<typename PIXMAP, typename SAMPLER>
class PixRowSampler
{
public:
	PixRowSampler(const SAMPLER &sampler, const PIXMAP &pixMap, float row) : _sampler(sampler), _pixMap(pixMap), _row(row) {}

	typename SAMPLER::SampleType operator[](float x)
	{
		SAMPLER::template sample(_pixMap, _row, x);
	}

private:
	SAMPLER &_sampler;
	PIXMAP _pixMap;
	float _row;
};

template<typename PIXMAP, typename SAMPLER>
class PixMapSampler
{
public:
	PixMapSampler(const SAMPLER &sampler, const PIXMAP &pixMap) : _sampler(sampler), _pixMap(pixMap) {}

	PixRowSampler operator[](float y)
	{	return RowSampler<PIXMAP, PIXELTYPE>(_pixMap, y); }

private:
	PIXMAP _pixMap;
	SAMPLER _sampler;
};

#endif // __ITL_ALGO_RESAMPLE_NEAREST_H__