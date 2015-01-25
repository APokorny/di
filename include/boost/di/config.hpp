//
// Copyright (c) 2014 Krzysztof Jusiak (krzysztof at jusiak dot net)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef BOOST_DI_CONFIG_HPP
#define BOOST_DI_CONFIG_HPP

#include "boost/di/aux_/utility.hpp"
#include "boost/di/core/pool.hpp"
#include "boost/di/providers/stack_over_heap.hpp"

#if defined(BOOST_DI_CFG)
    class BOOST_DI_CFG;
#else
    #define BOOST_DI_CFG boost::di::config
#endif

namespace boost { namespace di {

struct arg {
    using type = int;
    using name = no_name;
    using is_root = std::false_type;

    template<class T_, class TName_, class TDefault_>
    struct resolve;
};

template<class... TArgs>
    //REQUIRES are callable
inline auto make_policies(const TArgs&... args) noexcept ->
std::enable_if_t<
    aux::always<decltype(args(arg{}))...>{}, core::pool<aux::type_list<TArgs...>>>
{
    return core::pool<aux::type_list<TArgs...>>(args...);
}

class config {
public:
    auto provider() const noexcept {
        return providers::stack_over_heap{};
    }

    auto policies() noexcept {
        return make_policies();
    }
};

}} // boost::di

#endif

