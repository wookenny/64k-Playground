#include "Image.h"
#include <cmath>
#include <cassert>
#include <random>

//definition of static member variable
real Image::_gamma = 2.2;
const real Image::PI  = 3.1415926535897932384626433832795028;

Image::Image(unsigned int width, unsigned int height){
	_data = std::vector<std::vector<Color> >( width, std::vector<Color>( height, Color(0,0,0) ) );
}

Image::~Image(){ }

void Image::gammaCorrection(){
	for(unsigned int i=0; i<_data.size();++i)
		for(unsigned int j=0; j<_data.at(i).size();++j)
			_data.at(i).at(j).gammaCorrection(_gamma);
}

void Image::exposureCorrection(){
	for(unsigned int i=0; i<_data.size();++i)
		for(unsigned int j=0; j<_data.at(i).size();++j)
			_data.at(i).at(j).exposureCorrection();
}


void Image::save(const std::string& filename){
	/** shift colors **/
	exposureCorrection();  //not quite good, somethiong has to be done
	gammaCorrection();
	/*
	pngwriter writer(getWidth(), getHeight(), 0.0, filename.c_str());
	for(unsigned int i=0; i<_data.size();++i)
		for(unsigned int j=0; j<_data.at(i).size();++j){
			Color c = _data.at(i).at(j);
			writer.plot(i+1,getHeight()-j, c.getRed(), c.getGreen(), c.getBlue());
		}
	writer.write_png();
	*/
}


void Image::crop(uint x1, uint y1, uint x2, uint y2){
	assert(x1<x2);
	assert(y1<y2);
	assert(x2 < getWidth());
	assert(y2 < getHeight());

	std::vector<std::vector<Color> > newData( x2-x1 , std::vector<Color>( y2-y1, Color(0,0,0) ) );
	//copy data in image
	for(uint i=0;i<x2-x1;++i)
		for(uint j=0;j<y2-y1;++j)
			newData.at(i).at(j) = _data.at(x1+i).at(y1+j);
	//save the new image
	_data = newData;
}

//help function for rotation or scaling:
Color interpolate(const std::vector<std::vector<Color> > &img, real x, real y){
	//out of bounds?
	if(x<0 or y<0 or x>=img.size() or y>=img.at(0).size())
		return Color::BLACK;

	//interpolate the image
	//nearest neighbor
	uint i = x;
	uint j = y;
	return img.at(i).at(j);
	//bilinear

}

void Image::rotate(float angle){
	real centerX = getWidth()/2., centerY = getHeight()/2.;
	std::vector<std::vector<Color> >  copy = _data;
	for(uint i=0; i<getWidth(); ++i)
		for(uint j=0; j<getHeight(); ++j){
			float new_x = cos(angle)*(i-centerX)-sin(angle)*(j-centerY)+centerX;
			float new_y = sin(angle)*(i-centerX)+cos(angle)*(j-centerY)+centerY;
			_data.at(i).at(j) = interpolate(copy, new_x,new_y);
		}
}


void Image::scale(float s){
	std::vector<std::vector<Color> > newData( s*getWidth() , std::vector<Color>( s*getHeight(), Color(0,0,0) ) );
	//interpolate each pixel
	for(uint i=0; i<newData.size(); ++i)
		for(uint j=0; j<newData.at(0).size(); ++j){
			newData.at(i).at(j) = interpolate(_data, i/s, j/s);
		}
	//copy it
	_data = newData;
}


std::vector<std::vector<bool> > Image::findEdges() const{
	std::vector<std::vector<bool> > edges(_data.size(),std::vector<bool>(_data.at(0).size(),false));
	// apply laplce operator
	unsigned int n,m;
	real thresh = 0.05;
	n = edges.size()-1; m = edges.at(0).size()-1;
	for(unsigned int i = 0; i <= n; ++i){
		for(unsigned int j = 0; j <= m; ++j){
			if(i==0 && j==0)
				edges.at(0).at(0) = ( (_data.at(0).at(1)+_data.at(1).at(0)-2*_data.at(0).at(0)).max() > thresh  );
			else if(i==0 && j==m)
				edges.at(0).at(m) = ( (_data.at(0).at(m-1)+_data.at(1).at(m)-2*_data.at(0).at(m)).max() > thresh  );
			else if(i==n && j==0)
				edges.at(n).at(0) = ( (_data.at(n).at(1)+_data.at(n-1).at(0)-2*_data.at(n).at(0)).max() > thresh  );
			else if(i==n && j==m)
				edges.at(n).at(m) = ( (_data.at(n).at(m-1)+_data.at(n-1).at(m)-2*_data.at(n).at(m)).max() > thresh  );
			else if(i==0)
				edges.at(0).at(j) = ( (_data.at(0).at(j-1)+_data.at(0).at(j+1)-2*_data.at(0).at(j)).max() > thresh  );
			else if(j==0)
				edges.at(i).at(0) = ( (_data.at(i-1).at(0)+_data.at(i+1).at(0)-2*_data.at(i).at(0)).max() > thresh  );
			else if(i==n)
				edges.at(n).at(j) = ( (_data.at(n).at(j-1)+_data.at(n).at(j+1)-2*_data.at(n).at(j)).max() > thresh  );
			else if(j==m)
				edges.at(i).at(m) = ( (_data.at(i-1).at(m)+_data.at(i+1).at(m)-2*_data.at(i).at(m)).max() > thresh  );
			else
				edges.at(i).at(j) = ( (_data.at(i-1).at(j)+_data.at(i+1).at(j)+_data.at(i).at(j-1)+_data.at(i).at(j+1)-4*_data.at(i).at(j)).max() > 2*thresh  );

			//for debugging: set all to 1
			//edges.at(i).at(j)=true;
		}
	}
	//widen selection
	std::vector<std::vector<bool> > additional(_data.size(),std::vector<bool>(_data.at(0).size(),false));
	for(unsigned int i = 1; i <= n-1; ++i)
		for(unsigned int j = 1; j <= m-1; ++j)
			if( edges.at(i).at(j+1) or edges.at(i).at(j-1) or edges.at(i+1).at(j) or edges.at(i+1).at(j)
			   or edges.at(i+1).at(j+1) or edges.at(i-1).at(j-1) or edges.at(i-1).at(j+1) or edges.at(i+1).at(j-1))
				additional.at(i).at(j) = true;


	for(unsigned int i = 1; i <= n-1; ++i)
		for(unsigned int j = 1; j <= m-1; ++j)
			if( additional.at(i).at(j) )
				edges.at(i).at(j) = true;

	return edges;
}

/*****------------- Image Factory Methods -----------------------------------*****/
Image Image::createSolidColor(unsigned int n, unsigned int m, const Color &c){
	Image img = Image(n,m);
	for(unsigned int i=0; i<img._data.size();++i)
		for(unsigned int j=0; j<img._data.at(i).size();++j)
			img.at(i,j) =  c;
	return img;
}

Image Image::createCheckersBoard(unsigned int n, unsigned int m,
					const Color &c1, const Color &c2,
					unsigned int period1, unsigned int period2){
	Image img = Image(n,m);
	for(unsigned int i=0; i<img._data.size();++i)
		for(unsigned int j=0; j<img._data.at(i).size();++j){
			unsigned int color = ((int)(1.*i/period1)+(int)(1.*j/period2))%2;
			img.at(i,j) = (color==0)?c1:c2;
		}
	return img;
}

//this is the simple version: gradient from a to b, where a = x1,y and b = x2,y
Image Image::createLinearGradient(unsigned int n, unsigned int m, unsigned int x1, unsigned int x2,
					const Color &c1, const Color &c2){
	Image img = Image(n,m);
	for(unsigned int i=0; i<img._data.size();++i){
		Color act_col = c1;
		if(i>=x2) act_col = c2;
		if( x1<i and i<x2)//linear gradient
			act_col	= c1*(1-(i-x1)/(x2-x1)) + c2*((i-x1)/(x2-x1));
		for(unsigned int j=0; j<img._data.at(i).size();++j){
			img.at(i,j) = act_col;
		}
	}
	return img;
}

//TODO: FILL THIOS METHOD!!!!!
Image Image::createLinearGradient(unsigned int n, unsigned int m, unsigned int x1, unsigned int y1,
					unsigned int x2, unsigned int y2, const Color &c1, const Color &c2){
	//TODO: call the simpler method in a bigger version, rotate it, and crop a desired snapshot
	Image img = Image(n,m);
	float dirx = x2 - x1, diry = y2 - y1;
	float len = sqrt(dirx*dirx + diry*diry);
	dirx/=len; diry/=len;

	//float normalx = diry, normaly = -dirx;

	for(unsigned int i=0; i<img._data.size();++i)
		for(unsigned int j=0; j<img._data.at(i).size();++j){
			//intersectionpoints of lines: current+direction
		    // and two point +normal

			img.at(i,j) = c1;
		}
	return img;
}


Image Image::createRandomBicolorNoise(unsigned int n, unsigned int m, const Color &c1, const Color &c2){

	Image img = Image(n,m);
	std::mt19937_64 e(time(0));
	std::uniform_real_distribution<real> d(0,1);

	for(unsigned int i=0; i<img._data.size();++i)
		for(unsigned int j=0; j<img._data.at(i).size();++j){
			real lambda = d(e);
			img.at(i,j) = lambda*c1 + (1-lambda)*c2;
		}
	return img;
}

Image Image::createRandomColorNoise(unsigned int n, unsigned int m){

	Image img = Image(n,m);
	std::mt19937_64 e(time(0));
	std::uniform_real_distribution<real> d(0,255);

	for(unsigned int i=0; i<img._data.size();++i)
		for(unsigned int j=0; j<img._data.at(i).size();++j)
			img.at(i,j) = Color(d(e),d(e),d(e));

	return img;
}

/*****------------- Mask Factory Methods -----------------------------------*****/
std::vector<std::vector<float> > Image::createMaskFromImage(const Image& img, real x, real y, real z){
	uint n = img.getWidth(), m = img.getHeight();
	std::vector<std::vector<float> > mask;
	for(unsigned int i=0; i<n;++i){
		std::vector<float> v(m,0.);
		mask.push_back(v);
	}
	//fill in color
	for(unsigned int i=0; i<n;++i)
		for(unsigned int j=0; j<m;++j){
			mask[n][m]  = x*img.at(i,j).getRed() + y*img.at(i,j).getGreen() + z*img.at(i,j).getBlue();
			mask[n][m] /= (x+y+z)!=0?x+y+z:1.;//maybe they sum up to one.....
			mask[n][m] /= 255;
		}
	return mask;
}

std::vector<std::vector<float> > Image::createSolidColorMask(unsigned int n, unsigned int m, real alpha){
	std::vector<std::vector<float> > mask;
	for(unsigned int i=0; i<n;++i){
		std::vector<float> v(m,alpha);
		mask.push_back(v);
	}
	return mask;
}

