#pragma once
#include <vector>
#include <utility>
#include <tuple>
#include "Image.h"

class ImageStack : public ImageProducer{
		
	private:
		
		std::vector< std::tuple<ImageProducer,  std::vector<std::vector<float> > > > _stack;
		ImageProducer _baseImage;
		
	
		mutable bool _condensed;
		mutable Image _condensedImage;

		void _condense() const;
	public: 
		
		ImageStack(const Image& base):_baseImage(base),_condensed(false){ }
		~ImageStack(){}

		//getter
		unsigned int getWidth() const{ return _baseImage.getWidth(); }	
		unsigned int getHeight() const{ return _baseImage.getHeight(); }

		const Color& at(unsigned int i, unsigned int j) const{ _condense(); return _condensedImage.at(i,j);}
	
		const Color& relAt(double i, double j) const{
				_condense();
				int ni  = (int)(i*getWidth()) % getWidth();
				int nj  =  (int)(j*getHeight()) % getHeight();
				return _condensedImage.at(ni,nj);}

		void push(const ImageProducer& img, const std::vector<std::vector<float> > &mask);		
		
		const Image getCondensedImage() const {
			_condense(); 
			return _condensedImage; 
		}

		//interface method
		Image produceImage(){ return getCondensedImage(); }
};

//TODO: ImageStack Elemets can be imagesStacks itself!!! -> this builds trees immediateley
//TODO: crop to smaller size if two succsessive images are not fiotting!	
