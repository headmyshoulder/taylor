/*
 * placeholders.hpp
 *
 *  Created on: Jun 16, 2011
 *      Author: karsten
 *
 *
 * Copyright Karsten Ahnert 2011.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef PLACEHOLDERS_HPP_
#define PLACEHOLDERS_HPP_

#include <boost/numeric/odeint/stepper/taylor/tree_generator/variable_generator.hpp>

namespace boost {
namespace numeric {
namespace odeint {

boost::proto::terminal< taylor_detail::placeholder< boost::mpl::size_t< 0 > > >::type const arg1 = {};
boost::proto::terminal< taylor_detail::placeholder< boost::mpl::size_t< 1 > > >::type const arg2 = {};
boost::proto::terminal< taylor_detail::placeholder< boost::mpl::size_t< 2 > > >::type const arg3 = {};
boost::proto::terminal< taylor_detail::placeholder< boost::mpl::size_t< 3 > > >::type const arg4 = {};
boost::proto::terminal< taylor_detail::placeholder< boost::mpl::size_t< 4 > > >::type const arg5 = {};
boost::proto::terminal< taylor_detail::placeholder< boost::mpl::size_t< 5 > > >::type const arg6 = {};
boost::proto::terminal< taylor_detail::placeholder< boost::mpl::size_t< 6 > > >::type const arg7 = {};
boost::proto::terminal< taylor_detail::placeholder< boost::mpl::size_t< 7 > > >::type const arg8 = {};
boost::proto::terminal< taylor_detail::placeholder< boost::mpl::size_t< 8 > > >::type const arg9 = {};
boost::proto::terminal< taylor_detail::placeholder< boost::mpl::size_t< 9 > > >::type const arg10 = {};


} // namespace odeint
} // namespace numeric
} // namespace odeint



#endif /* PLACEHOLDERS_HPP_ */
