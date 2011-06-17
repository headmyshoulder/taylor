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
#include <iostream>

namespace boost {
namespace numeric {
namespace odeint {
namespace taylor_detail {


struct print_tree
{
	std::ostream &m_out;
	size_t m_indent;
	print_tree( std::ostream &out = std::cout , size_t indent = 0 ) : m_out( out ) , m_indent( indent ) { }

	typedef void result_type;

	template< class RootNode >
	void operator()( const RootNode &node ) const
	{
		print_node( m_out , node , m_indent );
		m_out << "\n";
	}
};




} // namespace taylor_detail
} // namespace odeint
} // namespace numeric
} // namespace boost

#endif /* PRINT_TREE_HPP_ */
