#ifndef STATE_CONTEXT_HPP
#define STATE_CONTEXT_HPP

#include <cstdint>
#include <functional>
#include <string>


struct StateContext {

    uint32_t state_change_count = 0;
    std::function<void(const std::string&)> publish_log = [](const std::string&) {};
};


#endif // STATE_CONTEXT_HPP
