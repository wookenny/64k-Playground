#include "ImageStack.h"
#include <cassert>
#include <boost/foreach.hpp>

#define foreach         BOOST_FOREACH
#define reverse_foreach BOOST_REVERSE_FOREACH

typedef std::tuple<ImageProducer,  std::vector<std::vector<float> > >  NastyStackElement;

void ImageStack::push(const ImageProducer& imgp, const std::vector<std::vector<float> > &mask){
	//check if the dimensions are matching ans mask is in range[0,1]
	if( img.getWidth() != _baseImage.getWidth() or img.getHeight() != _baseImage.getHeight() or mask.size() != _baseImage.getWidth() )
		assert(false);//new Image does not fit to the base image!
	for(unsigned int i = 0;  i < mask.size(); ++i ){
		if( mask.at(i).size() != _baseImage.getHeight() ) 
			assert(false);//new mask does not fit to the base image!	
		for(unsigned int j = 0;  j < mask.at(i).size(); ++j ){
			if( mask.at(i).at(j) < 0 or 1 < mask.at(i).at(j) )
				assert(false); //mask is not in the right range!			
		}	
	}
	
	//add image to the stack, 'cause everything seems to be ok!
	_stack.push_back( std::make_tuple(img,mask) );
	_condensed = false;
}



void ImageStack::_condense() const{
	//don't do it twice
	if (_condensed) return;

	//copy image 
	_condensedImage = _baseImage->produceImage();

	//add all 
	foreach( const NastyStackElement& elem, _stack ){
		const ImageProducer& currImg = std::get<0>(elem);
		const std::vector<std::vector<float> >& currMask = std::get<1>(elem);
		Image pImg = currImg.produceImage();
		for(unsigned int i = 0; i < _condensedImage.getWidth(); ++i)
			for(unsigned int j = 0; j < _condensedImage.getHeight(); ++j){
				//add the color with the current alphamask
				_condensedImage.at(i,j) =  currMask[i][j] * pImg.at(i,j) 
							+  (1-currMask[i][j]) * _condensedImage.at(i,j) ;
			
			}
	}

	//all done, get ready
	_condensed = true;
}
