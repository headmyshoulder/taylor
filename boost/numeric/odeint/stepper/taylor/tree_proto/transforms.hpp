/*
 * transforms.hpp
 *
 *  Created on: May 17, 2012
 *      Author: karsten
 */

#ifndef TRANSFORMS_HPP_
#define TRANSFORMS_HPP_


#include <cmath>
#include <boost/array.hpp>


// general boost includes
#include <boost/static_assert.hpp>

// proto includes
#include <boost/proto/proto.hpp>



namespace boost {
namespace numeric {
namespace odeint {
namespace taylor_detail {
namespace proto_transform {

	namespace proto = boost::proto;

	template< class State , class Derivs , class Temporaries , size_t MaxOrder >
	struct taylor_context
	{
		typedef State state_type;
		typedef Derivs deriv_type;
		typedef Temporaries temporaries_type;

		size_t which; // order of derivative
		size_t index; // equation index
		const state_type &x;
		deriv_type &derivs;
		temporaries_type &temporaries;
		double &dt_fac;

		taylor_context( size_t _which , const state_type &_x , deriv_type &_derivs , temporaries_type &_temp , double &_dt_fac )
		: which( _which ) , x( _x ) , derivs( _derivs ) , temporaries( _temp ) , dt_fac( _dt_fac ) { }
	};



	template< typename Grammar >
	struct plus_transform : proto::transform< plus_transform< Grammar > >
	{
		template< typename Expr , typename State , typename Data >
		struct impl : proto::transform_impl< Expr , State , Data >
		{
			typedef double result_type;

			result_type operator ()(
					typename impl::expr_param expr ,
					typename impl::state_param state ,
					typename impl::data_param data ) const
			{
				// cout << "Plus transform" << endl;
				return Grammar()( proto::left( expr ) , state , data )
                     + Grammar()( proto::right( expr ) , state , data );
			}
		};
	};


	template< typename Grammar >
	struct minus_transform : proto::transform< minus_transform< Grammar > >
	{
		template< typename Expr , typename State , typename Data >
		struct impl : proto::transform_impl< Expr , State , Data >
		{
			typedef double result_type;

			result_type operator ()(
					typename impl::expr_param expr ,
					typename impl::state_param state ,
					typename impl::data_param data ) const
			{
				// cout << "Minus transform" << endl;
				return Grammar()( proto::left( expr ) , state , data )
                     - Grammar()( proto::right( expr ) , state , data );
			}
		};
	};



	template< typename Grammar >
	struct multiplies_transform_optim : proto::transform< multiplies_transform_optim< Grammar > >
	{
		template< typename Expr , typename State , typename Data >
		struct impl : proto::transform_impl< Expr , State , Data >
		{
			typedef double result_type;

			result_type operator()(
					typename impl::expr_param expr ,
					typename impl::state_param state ,
					typename impl::data_param data ) const
			{
				// cout << "Multiplies transform optim" << endl;
				typedef typename impl::data data_type;

				// insert code for the temporaries here!!!
				// d[k] = sum_i dr i dl (n-1)
				size_t &mult_index = data.temporaries.indices[data.index];

				data.temporaries.values_left[data.which][mult_index] = Grammar()( proto::left( expr ) , state , data );
				data.temporaries.values_right[data.which][mult_index] = Grammar()( proto::right( expr ) , state , data );

//				cout << "abc " << data.index << tab << mult_index << endl;

//				for( size_t i=0 ; i<=data.which ; ++i )
//				{
//					double l = data.temporaries.values_left[data.index][i][mult_index];
//					double r = data.temporaries.values_right[data.index][i][mult_index];
//					cout << tab << i << tab << l << tab << r << endl;
//				}

				double tmp = 0.0;
				for( size_t k=0 ; k<=data.which ; ++k )
				{
					double l = data.temporaries.values_left[k][mult_index];
					double r = data.temporaries.values_right[data.which - k ][mult_index];
					tmp += l * r;
//					cout << tab << k << tab << tmp << tab << l << tab << r << endl;

//					tmp += data.temporaries.values_left[data.index][k][mult_index] * data.temporaries.values_right[data.index][data.which - k ][mult_index];

//					data_type data1( k ,  data.x , data.derivs , data.temporaries , data.dt_fac );
//					data_type data2( data.which - k ,  data.x , data.derivs , data.temporaries , data.dt_fac );
//
//					tmp += Grammar()( proto::left( expr ) , state , data1 )
//						 * Grammar()( proto::right( expr ) , state , data2 );

				}
//				cout << endl;

				++mult_index;

				return tmp;
			}
		};
	};



	template< typename Grammar >
	struct multiplies_transform : proto::transform< multiplies_transform< Grammar > >
	{
		template< typename Expr , typename State , typename Data >
		struct impl : proto::transform_impl< Expr , State , Data >
		{
			typedef double result_type;

			result_type operator()(
					typename impl::expr_param expr ,
					typename impl::state_param state ,
					typename impl::data_param data ) const
			{
				typedef typename impl::data data_type;

				// cout << "Multiplies transform" << endl;

				double tmp = 0.0;
				for( size_t k=0 ; k<=data.which ; ++k )
				{
					data_type data1( k ,  data.x , data.derivs , data.temporaries , data.dt_fac );
					data_type data2( data.which - k ,  data.x , data.derivs , data.temporaries , data.dt_fac );

					tmp += Grammar()( proto::left( expr ) , state , data1 )
						 * Grammar()( proto::right( expr ) , state , data2 );

				}
				return tmp;
			}
		};
	};



	struct terminal_double_transform : proto::transform< terminal_double_transform >
	{
		template< typename Expr , typename State , typename Data >
		struct impl : proto::transform_impl< Expr , State , Data >
		{
			typedef double result_type;

			result_type operator()(
					typename impl::expr_param expr ,
					typename impl::state_param state ,
					typename impl::data_param data ) const
			{
				// cout << "Terminal double transform" << endl;
				return ( data.which == 0 ) ? proto::value( expr ) : 0.0;
			}
		};
	};


	template< typename Index >
	struct terminal_placeholder_transform : proto::transform< terminal_placeholder_transform< Index > >
	{
		template< typename Expr , typename State , typename Data >
		struct impl : proto::transform_impl< Expr , State , Data >
		{
			typedef double result_type;

			result_type operator()(
					typename impl::expr_param expr ,
					typename impl::state_param state ,
					typename impl::data_param data ) const
			{
				// cout << "Terminal placeholder transform" << endl;
				typedef typename impl::expr expr_type;
				typedef typename expr_type::proto_args args_type;
				typedef typename args_type::child0 index_type;
				const size_t index = index_type::value;

				return ( data.which == 0 ) ? data.x[ index ] : data.derivs[ data.which - 1 ][ index ];
			}
		};
	};

	template< typename Grammar >
	struct right_shift_transform : proto::transform< right_shift_transform< Grammar > >
	{
		template< typename Expr , typename State , typename Data >
		struct impl : proto::transform_impl< Expr , State , Data >
		{
			typedef double result_type;

			result_type operator ()(
					typename impl::expr_param expr ,
					typename impl::state_param state ,
					typename impl::data_param data ) const
			{
				// cout << "Right shift transform" << endl;
				return Grammar()( proto::left( expr ) , state , data )
						+ ( ( data.which == 0 ) ? proto::value( proto::right( expr ) ) : 0.0 );
			}
		};
	};

	template< typename Grammar >
	struct left_shift_transform : proto::transform< left_shift_transform< Grammar > >
	{
		template< typename Expr , typename State , typename Data >
		struct impl : proto::transform_impl< Expr , State , Data >
		{
			typedef double result_type;

			result_type operator ()(
					typename impl::expr_param expr ,
					typename impl::state_param state ,
					typename impl::data_param data ) const
			{
				// cout << "Right shift transform" << endl;
				return Grammar()( proto::right( expr ) , state , data )
						+ ( ( data.which == 0 ) ? proto::value( proto::left( expr ) ) : 0.0 );
			}
		};
	};


	template< typename Grammar >
	struct right_scalar_multiplies_transform : proto::transform< right_scalar_multiplies_transform< Grammar > >
	{
		template< typename Expr , typename State , typename Data >
		struct impl : proto::transform_impl< Expr , State , Data >
		{
			typedef double result_type;

			result_type operator ()(
					typename impl::expr_param expr ,
					typename impl::state_param state ,
					typename impl::data_param data ) const
			{
				// cout << "Right scalar multiplies transform" << endl;
				return Grammar()( proto::left( expr ) , state , data ) * proto::value( proto::right( expr ) );
			}
		};
	};

	template< typename Grammar >
	struct left_scalar_multiplies_transform : proto::transform< left_scalar_multiplies_transform< Grammar > >
	{
		template< typename Expr , typename State , typename Data >
		struct impl : proto::transform_impl< Expr , State , Data >
		{
			typedef double result_type;

			result_type operator ()(
					typename impl::expr_param expr ,
					typename impl::state_param state ,
					typename impl::data_param data ) const
			{
				// cout << "Left scalar multiplies transform" << endl;
				return Grammar()( proto::right( expr ) , state , data ) * proto::value( proto::left( expr ) );
			}
		};
	};





	struct taylor_double_terminal : proto::when< proto::terminal< double > , terminal_double_transform > { };

	template< typename Which >
	struct taylor_placeholder_terminal : proto::when< proto::terminal< placeholder< Which > > , terminal_placeholder_transform< Which > > { };

	template< typename Grammar >
	struct taylor_plus : proto::when< proto::plus< Grammar , Grammar > , plus_transform< Grammar > > { };

	template< typename Grammar >
	struct taylor_minus : proto::when< proto::minus< Grammar , Grammar > , minus_transform< Grammar > > { };

	template< typename Grammar >
	struct taylor_multiplies : proto::when< proto::multiplies< Grammar , Grammar > , multiplies_transform< Grammar > >  { };

	template< typename Grammar >
	struct taylor_shift :
		proto::or_<
			proto::when< proto::plus< Grammar , proto::terminal< double > > , right_shift_transform< Grammar > > ,
			proto::when< proto::plus< proto::terminal< double > , Grammar > , left_shift_transform< Grammar > >
		> { };

	template< typename Grammar >
	struct taylor_scalar_multiplies :
		proto::or_<
			proto::when< proto::multiplies< Grammar , proto::terminal< double > > , right_scalar_multiplies_transform< Grammar > > ,
			proto::when< proto::multiplies< proto::terminal< double > , Grammar > , left_scalar_multiplies_transform< Grammar > >
		> { };

	template< typename Grammar , typename Which1 , typename Which2 >
	struct taylor_simple_multiplies :
		proto::when<
			proto::multiplies< proto::terminal< placeholder< Which1 > > , proto::terminal< placeholder< Which2 > > > ,
			multiplies_transform< Grammar > > { };





	struct taylor_transform :
	proto::or_
	<
	    taylor_scalar_multiplies< taylor_transform > ,
	    taylor_simple_multiplies< taylor_transform , proto::_ , proto::_ > ,
		taylor_shift< taylor_transform > ,
		taylor_double_terminal ,
		taylor_placeholder_terminal< proto::_ > ,
		taylor_plus< taylor_transform > ,
		taylor_minus< taylor_transform > ,
		taylor_multiplies< taylor_transform >
	>
	{ };

} // namespace proto





	template< class System , class State , class Derivs , class Temporaries , size_t Order >
	struct proto_eval_derivs
	{
		typedef State state_type;
		typedef Derivs deriv_type;
		typedef Temporaries temporaries_type;
		typedef proto_transform::taylor_context< state_type , deriv_type , temporaries_type , Order > taylor_context_type;


		System m_sys;
		taylor_context_type m_data;

		proto_eval_derivs( System sys , const state_type  &x , deriv_type &derivs , temporaries_type &temp , double &dt_fac , size_t which )
		: m_sys( sys ) , m_data( which , x , derivs , temp , dt_fac ) { }

		template< class Index >
		void operator()( Index )
		{
			typedef typename fusion::result_of::at< System , Index >::type expr_type;
			m_data.index = Index::value;

			const expr_type &expr = boost::fusion::at< Index >( m_sys );
			double deriv = proto_transform::taylor_transform()( expr , 0.0 , m_data );
//			cout << m_data.x[0] << tab << m_data.dt_fac << tab << m_data.which << tab << deriv << endl;
			m_data.derivs[ m_data.which ][ Index::value ] = m_data.dt_fac / double( m_data.which + 1 ) * deriv;

//			cout << endl;
		}
	};

	template< size_t Order , class System , class State , class Derivs , class Temporaries >
	proto_eval_derivs< System , State , Derivs , Temporaries , Order >
	make_proto_eval_derivs( System sys , const State &x , Derivs &derivs , Temporaries &temp , double &dt_fac , size_t i )
	{
		return proto_eval_derivs< System , State , Derivs , Temporaries , Order >( sys , x , derivs , temp , dt_fac , i );
	}






} // namespace taylor_detail
} // namespace odeint
} // namespace numeric
} // namespace boost






#endif /* TRANSFORMS_HPP_ */
