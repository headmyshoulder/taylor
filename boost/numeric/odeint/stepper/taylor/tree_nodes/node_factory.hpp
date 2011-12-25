/*
 * node_factory.hpp
 *
 *  Created on: Dec 25, 2011
 *      Author: karsten
 */

#ifndef NODE_FACTORY_HPP_
#define NODE_FACTORY_HPP_

#include <boost/numeric/odeint/taylor/tree_nodes/minus_node.hpp>
#include <boost/numeric/odeint/taylor/tree_nodes/plus_node.hpp>
#include <boost/numeric/odeint/taylor/tree_nodes/multiplies_node.hpp>
#include <boost/numeric/odeint/taylor/tree_nodes/scalar_multiplies_node.hpp>
#include <boost/numeric/odeint/taylor/tree_nodes/scalar_plus_node.hpp>
#include <boost/numeric/odeint/taylor/tree_nodes/variable_node.hpp>
#include <boost/numeric/odeint/taylor/tree_nodes/const_node.hpp>


namespace boost {
namespace numeric {
namespace odeint {
namespace taylor_detail {

struct node_v1_factory
{
    typedef double value_type;


    template< class Left , class Right >
    struct minus_factory
    {
        typedef minus_node< Left , Right , value_type > type;
    };


    template< class Left , class Right >
    struct plus_factory
    {
        typedef plus_node< Left , Right , value_type > type;
    };

    template< class Left , class Right >
    struct multiplies_factory
    {
        typedef multiplies_node< Left , Right , value_type > type;
    };

    template< class Child >
    struct scalar_multiplies_factory
    {
        typedef scalar_multiplies_node< Child , value_type > type;
    };

    template< class Child >
    struct scalar_plus_factory
    {
        typedef scalar_plus_node< Child , value_type > type;
    };

    struct constant_factory
    {
        typedef constant_node< value_type > type;
    };

    template< size_t Index >
    struct variable_factory
    {
        typedef variable_node< Index , value_type > type;
    };
};


}
}
}
}

#endif /* NODE_FACTORY_HPP_ */
