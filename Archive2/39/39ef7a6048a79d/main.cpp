    class EventLoopException_CalledFromNonActiveThread : public ks::Exception
    {
        static ErrorLevel lvl = ErrorLevel::FATAL;

        static std::string msg = "EventLoop: ProcessEvents/Run should only "
                                 "be called from the thread that called Start";
    };

    class EventLoopException_EventLoopStopped : public ks::Exception
    {
        static ErrorLevel lvl = ErrorLevel::WARN;

        static std::string msg = "EventLoop: ProcessEvents called but "
                                 "event loop has not been started";
    };
    
    ///// OR /////

    class EventLoopException : public ks::Exception
    {
        enum class Error : u8 {
            EventLoopNotStarted = 0,
            CalledFromNonActiveThread = 1
        };

        static std::vector<ErrorLevel> s_list_errlvl {
            ErrorLevel::WARN,
            ErrorLevel::FATAL
        };

        static std::vector<std::string> s_list_msgs {
            "EventLoop: ProcessEvents called but "
            "event loop has not been started",

            "EventLoop: ProcessEvents/Run should only "
            "be called from the thread that called Start"
        };
    };