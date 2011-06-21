#pragma once
#include <vector>
#include <utility>
#include <tuple>
#include "Image.h"

class ImageStack{
		
	private:
		
		std::vector< std::tuple<Image,  std::vector<std::vector<float> > > > _stack;
		Image _baseImage;
		
	
		mutable bool _condensed;
		mutable Image _condensedImage;

		void _condense() const;
	public: 
		
		ImageStack(const Image& base):_baseImage(base),_condensed(false){ }

		//getter
		unsigned int getWidth() const{ return _baseImage.getWidth(); }	
		unsigned int getHeight() const{ return _baseImage.getHeight(); }

		const Color& at(unsigned int i, unsigned int j) const{ _condense(); return _condensedImage.at(i,j);}
	
		const Color& relAt(double i, double j) const{
				_condense();
				int ni  = (int)(i*getWidth()) % getWidth();
				int nj  =  (int)(j*getHeight()) % getHeight();
				return _condensedImage.at(ni,nj);}

		void push(const Image& img, const std::vector<std::vector<float> > &mask);		
		
		const Image& getCondensedImage() const {
			_condense(); 
			return _condensedImage; 
		}
};
