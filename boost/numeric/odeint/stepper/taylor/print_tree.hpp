/*
 * print_tree.hpp
 *
 *  Created on: Jun 9, 2011
 *      Author: karsten
 *
 *
 * Copyright Karsten Ahnert 2011.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef PRINT_TREE_HPP_
#define PRINT_TREE_HPP_

#include <ostream>

namespace boost {
namespace numeric {
namespace odeint {


namespace tree_nodes {


template< class RootNode >
void print_tree( std::ostream &out , const RootNode &root , size_t indent = 0 )
{
	print_node( out , root , indent );
	out << "\n";
}




} // namespace tree_nodes



} // namespace odeint
} // namespace numeric
} // namespace boost

#endif /* PRINT_TREE_HPP_ */
