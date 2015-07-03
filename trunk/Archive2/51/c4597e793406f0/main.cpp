
void AggregatePocedure(context_ptr const context) {
   buffer_pool_ptr const bufferPool = context->agregateStep->bufferPool;   
   concurrent_queue_ptr * const inputQueues = context->agregateStep->inputQueues;
   concurrent_queue_ptr const outputQueue = context->agregateStep->outputQueue;
   semaphore_t & postSemaphore = context->agregateStepPostSemaphore;
   semaphore_t & getSemaphore  = context->agregateStepGetSemaphore;
   
   std::vector<image_ptr> inputImages(context->imageNumber);
   
   while (!context->quit) {
      for (std::size_t i = 0; i != inputBuffers.size(); ++i) {
         inputQueues[i]->pop(inputImages, TIMEOUT_INFINITE);    
      }
      
      if (context->quit) {
         break;    
      }             
      
      image_buffer_ptr imageBuffer;
      bufferPool->pop(imageBuffer, TIMEOUT_INFINITE);
            
      {
         // agregate and write to `imageBuffer->image`
      }
      
      if (!postSemaphore.try_aquire()) {
         bufferPool->push(imageBuffer, TIMEOUT_INFINITE);
          
         continue;    
      }
      
      NvMediaEglStreamProducerPostImage(context->eglProducer, imageBuffer->image, 0);
      
      getSemaphore.release();
   }
}

void GetImageProcedure(context_ptr const context) {
    buffer_pool_ptr const bufferPool = context->agregateStep->bufferPool;
    semaphore_t & postSemaphore = context->agregateStepPostSemaphore;
    semaphore_t & getSemaphore  = context->agregateStepGetSemaphore;
    
    while (!context->quit || !bufferPool->full()) {
        getSemaphore.acquire();
        
        image_ptr image;
        NvMediaEglStreamProducerGetImage(context->eglProducer, &image, NVMEDIA_EGL_STREAM_TIMEOUT_INFINITE);
        
        postSemaphore.release();
        
        bufferPool->push(image, TIMEOUT_INFINITE);       
    }
    
    context->agregateStep->finished = true;
}
