#include "ImageStack.h"
#include <cassert>
#include <boost/foreach.hpp>

#define foreach         BOOST_FOREACH
#define reverse_foreach BOOST_REVERSE_FOREACH

typedef std::tuple<ImageProducer_ptr,  std::vector<std::vector<float> > >  NastyStackElement;

void ImageStack::push(ImageProducer_ptr img, const std::vector<std::vector<float> > &mask){
	//check if the mask dimensions are matching and mask is in range[0,1]
	if( mask.size() != img->getWidth() )
		assert(false);//mask and image doesn't fit
	for(unsigned int i = 0;  i < mask.size(); ++i ){
		if( mask.at(i).size() != img->getHeight() ) 
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
		ImageProducer_ptr currImg = std::get<0>(elem);
		const std::vector<std::vector<float> >& currMask = std::get<1>(elem);
		Image pImg = currImg->produceImage();
	
		//crop to the right dimension:
		//TODO: sehr genau aufpassen: was wenn beide bilder je einmal das groessere/kleinere ist?
		uint w = _condensedImage.getWidth(),h = _condensedImage.getHeight();
		w = std::min(w,pImg.getWidth());
		h = std::min(h,pImg.getHeight());
		uint x_offset = (_condensedImage.getWidth()-w)/2;
		uint y_offset = (_condensedImage.getHeight()-h)/2;
		_condensedImage.crop(x_offset, y_offset, w +x_offset-1, h+y_offset-1);

		x_offset = (pImg.getWidth() - w)/2;
		y_offset = (pImg.getHeight() - h)/2;
		for(unsigned int i = 0; i < _condensedImage.getWidth(); ++i)
			for(unsigned int j = 0; j < _condensedImage.getHeight(); ++j){
				//add the color with the current alphamask
				_condensedImage.at(i,j) =  currMask[i+x_offset][j+y_offset] * 
											pImg.at(i+x_offset,j+y_offset) 
												+  (1-currMask[i+x_offset][j+y_offset])
											* _condensedImage.at(i,j) ;
			
			}
	}

	//all done, get ready
	_condensed = true;
}
