#include "Image.h"


//definition of static member variable
real Image::_gamma = 2.2;

Image::Image(unsigned int width, unsigned int height){

	_data = std::vector<std::vector<Color> >( width, std::vector<Color>( height, Color(0,0,0) ) );
}


Image::Image(const std::string file){
	/*	
	img.readfromfile( file.c_str() );

	_data = std::vector<std::vector<Color> >( img.getwidth() ,std::vector<Color>( img.getheight(), Color(0,0,0) ) );	
	
	
	for(unsigned int i=0; i<_data.size();++i){
		for(unsigned int j=0; j<_data.at(i).size();++j){
			Color c(real(img.read(i+1,j+1,1))/65536.,
					real(img.read(i+1,j+1,2))/65536.,
					real(img.read(i+1,j+1,3))/65536. );
			_data.at(i).at(j) = c;
		}
	}
	*/
}


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

Image Image::createLinearGradient(unsigned int n, unsigned int m, unsigned int x1, unsigned int y1, 
					unsigned int x2, unsigned int y2, const Color &c1, const Color &c2){
	Image img = Image(n,m);
	for(unsigned int i=0; i<img._data.size();++i)
		for(unsigned int j=0; j<img._data.at(i).size();++j){
			img.at(i,j) = c1;
		}
	return img;
}
	
/*****------------- Mask Factory Methods -----------------------------------*****/
std::vector<std::vector<float> > Image::createSolidColorMask(unsigned int n, unsigned int m, real alpha){
	std::vector<std::vector<float> > mask; 	
	for(unsigned int i=0; i<n;++i){
		std::vector<float> v(m,alpha);
		mask.push_back(v);	
	}
	return mask;
}


