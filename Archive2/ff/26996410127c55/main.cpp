void testtt(unsigned *image, unsigned *buf, unsigned length, unsigned count)
{
        const unsigned height=1080;
        const unsigned width=1920;//length/height;//width=1920; height=1080
        for(unsigned n=0; n<count; n++){//count=500
            for(unsigned y=1; y<height-1; y++){
                const unsigned p=width*y;
                for(unsigned x=1; x<width-1; x++) if(image[p+x]!=0xffffff)
                    buf[p+x]=(image[p-width+x]+image[p+x-1]+image[p-width+x-1]+image[p-width+x+1]+image[p+width+x-1]+image[p+width+x]+image[p+x+1]+image[p+width+x+1])>>3;
            }
            for(unsigned y=1; y<height-1; y++){
                const unsigned p=width*y;
                for(unsigned x=1; x<width-1; x++) if(buf[p+x]!=0xffffff)
                    image[p+x]=(buf[p-width+x]+buf[p+x-1]+buf[p-width+x-1]+buf[p-width+x+1]+buf[p+width+x-1]+buf[p+width+x]+buf[p+x+1]+buf[p+width+x+1])>>3;
            }
        }
}