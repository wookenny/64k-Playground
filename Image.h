#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <string>
#include <memory>
#include "Color.h"

class Image;

class ImageProducer{
	public:
		virtual ~ImageProducer() {};
		virtual Image produceImage() = 0;
		virtual uint getWidth() const = 0;
		virtual uint getHeight() const = 0;
};	

typedef std::shared_ptr<ImageProducer> ImageProducer_ptr;
typedef std::shared_ptr<Image> Image_ptr;

class Image: public ImageProducer{

private:
	std::vector<std::vector<Color> > _data;	
	
	void gammaCorrection();
	void exposureCorrection();

public:	

	static const real PI;
	static real _gamma;

	//constructors
	Image(unsigned int width = 800,unsigned int height = 600);
	Image(const Image& img){ _data = img._data; }

	virtual ~Image();

	//getter
	unsigned int getWidth() const{ return _data.size(); }	
	unsigned int getHeight() const{ return _data[0].size(); }
	static real getGamma() { return _gamma;}	

	//setter
	static void setGamma(real g){ _gamma = g;}

	//setter+getter:
	const Color& at(unsigned int i, unsigned int j) const{ return _data[i][j];}
	Color& at(unsigned int i, unsigned int j){ return _data[i][j];}
	
	const Color& relAt(real i, real j) const{
			int ni  = (int)(i*_data.size())%_data.size();
			int nj  =  (int)(j*_data[0].size())%_data[0].size();
			return _data[ni][nj];}

	Color& relAt(real i, real j){
			int ni  = (int)(i*_data.size())%_data.size();
			int nj  =  (int)(j*_data[0].size())%_data[0].size();
			return _data[ni][nj];}

	//interface method:
	Image produceImage(){ return *this; }

	//misc methods	
	void save(const std::string& filename);
	std::vector<std::vector<bool> > findEdges() const;

	//crop, rotate, scale
	void crop(uint x1, uint y1, uint x2, uint y2);
	void rotate(float angle);
	void scale(float s);

	//static image factory methods:
	//solid, gradient, random, simplex noise, perlin noise, circles, rectangles, 
	//checker board, sinus(linear, radial)	
	static Image createSolidColor(unsigned int n = 800, unsigned int m = 600, const Color &c = Color::BLACK);
	static Image createCheckersBoard(unsigned int n = 800, unsigned int m = 600, 
					const Color &c1 = Color(0,0,0), const Color &c2 = Color::WHITE,
					unsigned int period1 = 100, unsigned int period2 = 100 );
	static Image createLinearGradient(unsigned int n = 800, unsigned int m = 600, 
					unsigned int x1 = 0, unsigned int x2 = 0,
					const Color &c1 = Color::WHITE, const Color &c2 = Color::BLACK);	
	static Image createLinearGradient(unsigned int n = 800, unsigned int m = 600, 
					unsigned int x1 = 0, unsigned int y1 = 0, 
					unsigned int x2 = 0, unsigned int y2 = 100,
					const Color &c1 = Color::WHITE, const Color &c2 = Color::BLACK);
	//static mask factory methods:
	static std::vector<std::vector<float> > createSolidColorMask(unsigned int n = 800, unsigned int m = 600, real alpha = 0.5);

};

//TODO: factory should return a pointer!!
