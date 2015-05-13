#ifndef MUDUO_NET_TCPCONNECTION_H
#define MUDUO_NET_TCPCONNECTION_H

#include <muduo/base/Mutex.h>
#include <muduo/base/StringPiece.h>
#include <muduo/base/Types.h>
#include <muduo/net/Callbacks.h>
#include <muduo/net/Buffer.h>
#include <muduo/net/InetAddress.h>

#include <boost/any.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/noncopyable.hpp>
#include <boost/scoped_ptr.hpp>
#include <boost/shared_ptr.hpp>

namespace muduo
{
    namespace net
    {
        class Channel ;
        class EventLoop ;
        class Socket ;
        
        // TCP connection , for both client and server usage
        // this is an interface class , so do not expose too much details
        
        class TcpConnection : boost::noncopyable , 
                              public boost::enable_shared_from_this<TcpConnection>
        {
            public :
                    // constructors a TcpConnection with a connected sockfd
                        
                    // user should not create this object
                    
                    TcoConnection ( EventLoop *loop ,
                        const string &name ,
                        int sockfd ,
                        const InetAddress & localAddr ,
                        const InetAddress & peerAddr ) ;
                    
                    
                    ~TcpConnection() ;
                    
                    
                    EventLoop* getLoop () const 
                    {
                        return loop_ ;
                    }
                    
                    const string & name () const
                    {
                        return name_ ;
                    }
                    
                    const InetAddress & localAddress()
                    {
                        return localAddr_ ;
                    }
                    
                    const InetAddress & peerAddress ()
                    {
                        return peerAddr_ ;
                    }
                    
                    bool connected() const
                    {
                        return state_ == kConnected ;
                    }
                    
                    
                    
                    // void send( string && message ) ; C++11
                    void send ( const void * message , size_t len ) ;
                    void send ( const StringPiece & message ) ;
                    
                    // void send( Buffer && message ) ; // C++ 11
                    void send( Buffer *message ) ; // this one will swap data
                    void shutdown () ; 
                    // NOT thread safe , no simultaneous calling
                    void setTcoNoDelay ( bool on ) ;
                    
                    
                    void setContext ( const boost::any & context )
                    {
                        context_ = context ;
                    }
                    
                    const boost::any & getContext ()
                    {
                        return context_ ;
                    }
                    
                    
                    boost::any * getMutableContext ()
                    {
                        return &context_ ;
                    }
                    
                    
                    void setConnectionCallback ( const ConnectionCallback &cb )
                    {
                        connectionCallback_ = cb ;
                    }
                    
                    void setMessageCallback ( const MessageCallback &cb )
                    {
                        messageCallback_ = cb ;
                    }
                    
                    void setWriteCompleteCallback ( const WriteCompleteCallback &cb )
                    {
                        writeCompleteCallback_ = cb ;
                    }
                    
                    
                    void setHighWaterMarkCallback ( const HighWaterMarkCallback &cb ,
                                size_t highWaterMark )
                    {
                        highWaterMarkCallback_ =
                        cb ;
                        
                        highWaterMark_ = highWaterMark ;
                    }
                    
                    
                    Buffer *inputBuffer ()
                    {
                        return &inputBuffer ;
                    }
                    
                    // internal use only
                    void setCloseCallback ( const CloseCallback &cb )
                    {
                        closeCallback_ = cb ;
                    }
                    
                    
                    /// called when TcpServer accepted a new connection 
                    
                    void connectEstablished () ; 
                    // should be called only once
                    
                    // called when TcpServer has removed me fromthis map
                    void connectDestoryed () ;
                    // shoudl be called only once
                    
                    private :
                     enum StateE
                     {
                        kDisconnected ,
                        kConnecting , 
                        kConnected ,
                        kDisconnecting  
                    } ;
                    
                    
                    void handleRead ( Timestamp receiveTime ) ;
                    void handleWrite () ;
                    void handleClose () ;
                    void handleError () ;
                    void sendInLoop ( const StringPiece &message ) ;
                    void sendInLoop ( const void *message , size_t len ) ;
                    void shutdownInLoop () ;
                    void setState ( StateE s )
                    {
                        state_ = s ;
                    }
                    
                    EventLoop * loop_ ; 
                    string name_ ; // name of the conenction 
                    StateE state_ ;
                    // FIXME: use atomic variable
                    
                    boost::scoped_ptr<Socket> socket_t ;
                    boost::scoped_ptr<Channel> channel_ ;
                    
                    InetAddress localAddr_ ;
                    InetAddress peerAddr_ ;
                    
                    ConnectionCallback connectionCallback_ ;
                    MessageCallback messageCallback_ ;
                    WriteCompleteCallback writeCompleteCallback_t ;
                    // data sending finished callback method
                    // the so-called finsih sending means that 
                    // all user data already copied into kernel space
                    
                    HighWaterMarkCallback highWaterMarkCallback_ ;
                    // high water call back method
                    CloseCallback closeCallback_ ;
                    size_t highWaterMark_ ;
                    Buffer inputBuffer_ ;
                    Buffer outputBuffer_ ;
                    boost::any context_ ;
                    // to bind unknown context object
                    
                    
                    
        } ;
        
        typedef boost::shared_ptr<TcpConnection> TcpConenctionPtr ;
    }
}

#endif 


//-----------------------------------
// here is the test file 
// ----------------------------------------

#include <muduo/net/TcpServer.h>
#include <muduo/net/EventLoop.h>
#include <muduo/net/InetAddress.h>

#include <boost/bind.hpp>

#include <stdio.h>


using namespace muduo ;
using namespace muduo::net ;

class TestServer
{
public :
    TestServer (EventLoop *loop ,
            const InetAddress & listenAddr ) : loop_ (loop ) ,     server_(loop, listenAddr , "TestServer)
    {
        server_.setConnectionCallback(
            boost::bind(&TestServer::onConnection , this , _1 ) ;
    }                           
                                
                                
                                
                                
} ;
























