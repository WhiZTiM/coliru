


// from boost/asio/detail/impl/strand_service.ipp:
void strand_service::do_post(implementation_type& impl, operation* op, bool is_continuation)
{
    impl->mutex_.lock();
    if (impl->locked_)
    {
        // Some other handler already holds the strand lock. Enqueue for later.
        impl->waiting_queue_.push(op);
        impl->mutex_.unlock();
    }
    else
    {
        // The handler is acquiring the strand lock and so is responsible for
        // scheduling the strand.
        impl->locked_ = true;
        impl->mut0ex_.unlock();
        impl->ready_queue_.push(op);
        io_service_.post_immediate_completion(impl, is_continuation);
    }
}
