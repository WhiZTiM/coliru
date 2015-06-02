    
    class RenderManager {
    public:

        // Temporary duration: 1/240th of a second
        using min_frame_duration = std::chrono::duration<uint32_t, std::ratio<1,240>>; 

    private:
        D3D11Device& device_;
        Stage& stage_;
        
        gthread::task_queue task_queue_;

        std::thread thread_;
        std::atomic_flag quit_flag_;
        std::condition_variable condition_var_;
        std::mutex mutex_;
        std::atomic_bool thread_started_;
        std::atomic<ID3D11CommandList*> command_list_{}; 

        game_utils::Ticker t; // debugging       

        //void thread_func();
        std::unique_lock<std::mutex> clear_waiting_frame();

    public:

        RenderManager(D3D11Device& device_, Stage& stage_);

        ~RenderManager();
        
        void execute_waiting_tasks();
        void present_frame();

        void toggle_fullscreen() {
            //task_queue_.add_task([this](){ scene_.toggle_fullscreen(); });
        }

        void thread_func();

        
    };
