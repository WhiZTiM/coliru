#include <libswscale/swscale.h>
#include <libavutil/avutil.h>
#include <libavcodec/avcodec.h>

#include <stdio.h>

int main()
{
    int width = 640;
	int height = 480;
	struct SwsContext * convertContext = sws_getCachedContext(0,
		width, height, PIX_FMT_RGB24,
		width, height, AV_PIX_FMT_YUV420P,
		SWS_LANCZOS, NULL, NULL, NULL);
	uint8_t * outputData = malloc(width*height);
	uint8_t * inputData = malloc(width*height*3);
	AVPicture inputPicture = {};
	inputPicture.data[0] = inputData;
	inputPicture.linesize[0] = width*3;
	AVPicture outputPicture = {};
	outputPicture.data[0] = outputData;
	outputPicture.data[1] = outputData;
	outputPicture.data[2] = outputData;
	outputPicture.linesize[0] = width;
	outputPicture.linesize[1] = width/2;
	outputPicture.linesize[2] = width/2;
	printf("Input Start: %p, End: %p\n", (void*)inputPicture.data[0], (void*)(inputPicture.data[0] + inputPicture.linesize[0]*height));
	printf("Output Start: %p, End: %p\n", (void*)outputPicture.data[0], (void*)(outputPicture.data[0] + outputPicture.linesize[0]*height));
	sws_scale(convertContext,
		inputPicture.data, inputPicture.linesize, 0, height,
		outputPicture.data, outputPicture.linesize);
	printf("Done");
	printf("Out of bounds byte: %i\n", (int)inputData[width*height*3]);
}
