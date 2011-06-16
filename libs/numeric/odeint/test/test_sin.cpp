/*
 * test_sin.cpp
 *
 *  Created on: Jun 16, 2011
 *      Author: karsten
 */

#include <ostream>
#include <boost/proto/proto.hpp>

#include <boost/mpl/size_t.hpp>

namespace proto = boost::proto;
namespace mpl = boost::mpl;



template< typename I > struct placeholder : I {};

proto::terminal< placeholder< mpl::size_t< 0 > > >::type const arg1 = {};
proto::terminal< placeholder< mpl::size_t< 1 > > >::type const arg2 = {};
proto::terminal< placeholder< mpl::size_t< 2 > > >::type const arg3 = {};

template< typename I >
std::ostream& operator<<( std::ostream &s , const placeholder< I > &p )
{
	s << "placeholder<" << I::value << ">";
	return s;
}


struct sin_tag {};

std::ostream& operator<<( std::ostream &s , const sin_tag &tag )
{
	s << "sin";
	return s;
}

struct SinTag : proto::terminal< sin_tag > {};
SinTag::type const sin = {{}};




int main( int argc , char **argv )
{
	proto::display_expr( arg1 * sin( arg2 * ( 1.0 + arg3 ) ) );
	return 0;
}
