
#include <iastream>
#include <string>
#include <>

class IOperand {
public:
virtual int getPrecision( void ) const = 0; // Precision of the type of the instance
virtual eOperandType getType( void ) const = 0; // Type of the instance
virtual IOperand const * operator+( IOperand const & rhs ) const = 0; // Sum
virtual IOperand const * operator-( IOperand const & rhs ) const = 0; // Difference
virtual IOperand const * operator*( IOperand const & rhs ) const = 0; // Product
virtual IOperand const * operator/( IOperand const & rhs ) const = 0; // Quotient
virtual IOperand const * operator%( IOperand const & rhs ) const = 0; // Modulo
virtual std::string const & toString( void ) const = 0; // String representation of the instance
virtual ~IOperand( void ) {}
private:
	IOperand const * createInt8( std::string const & value ) const;
	IOperand const * createInt16( std::string const & value ) const;
	IOperand const * createInt32( std::string const & value ) const;
	IOperand const * createFloat( std::string const & value ) const;
	IOperand const * createDouble( std::string const & value ) const;
};


IOperand const * createOperand( eOperandType type, std::string const & value ) const

