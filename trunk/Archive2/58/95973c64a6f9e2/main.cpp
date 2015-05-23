

// trying to enable per-segment processing instead of per-packet
// dig deep in to the legacy code where packets are still in segments
// but it turned out the segments had to be destroyed
// by the same thread that acquired them.

// this hack actually seems to work pretty well


void segment_processing_thread()
{
    // list of previous segments which have not yet been destroyed
    std::deque<std::shared_ptr<Segments>> previous_segments;

    auto cleanup_segments = [&]
    {
        for (;;)
        {
            if (previous_segments.empty())
            {
                return;
            }
      
            // we are now the sole owner, so we can safely release it
            if (previous_segments.front().unique())
            {
                previous_segments.pop_front();
                continue;
            }
            
            break;
        }
    };
    
    
    // main loop of the thread
    while (running)
    {   
        // cleanup any unused segments
        cleanup_segments();        
        
        // fetch new segment
        std::shared_ptr<Segment> segment(queue.pop());
        
        // it's not yet a previous segment, but it will soon be
        previous_segments.push_back(segment);
        
        // send off to some other thread for processing
        process(segment); 
    }
    
    // thread exit: must wait until all segments have been cleared
    while (!previous_segments.empty())
    {
        if (previous_segments.front().unique())
        {
            previous_segments.pop_front();
        }
        else
        {
            sched_yield();
        }
    }
}
