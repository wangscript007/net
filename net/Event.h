//
// Created by lg on 18-3-16.
//

#pragma once
#include<functional>
#include <sys/epoll.h>
#include"CallBack.h"

namespace net {
    class EventLoop;

    class Event {
    public:
        Event(EventLoop*loop,int fd,bool r=false, bool w=false)noexcept;
        ~Event()noexcept ;

        static constexpr uint32_t NoneEvent=0;
        static constexpr uint32_t ReadEvent=EPOLLIN|EPOLLPRI;
        static constexpr uint32_t WriteEvent=EPOLLOUT;

        void set_read_cb(const ReadEventCallback &cb) { _read_cb = cb; }
        void set_write_cb(const EventCallback &cb) { _write_cb = cb; }
        void set_error_cb(const EventCallback &cb){_error_cb=cb;}

        void enable_read();
        void enable_write();
        void enable_all();

        void disable_read();
        void disable_write();
        void disable_all();

        int get_fd()const{return _fd;}
        uint32_t get_events()const{return _events;}

        void attach_to_loop();
        void detach_from_loop();
        void handle_event(uint32_t event);

        bool is_add_to_loop()const noexcept {return _add_to_loop;}

        void set_fd(int fd) {_fd=fd;}
    private:
        void update();

        bool is_write() const { return (_events & WriteEvent)!=0; }
        bool is_read() const { return (_events & ReadEvent)!=0; }
        bool is_none()const{return _events==NoneEvent;}


    private:
        int _fd;
        EventLoop* _loop;
        uint32_t _events;

        bool _add_to_loop;
        ReadEventCallback _read_cb;
        EventCallback _write_cb;
        EventCallback _error_cb;
    };
}

