//Борин Павел
#include "CFormula.h"

// CEquation 

CEquation::CEquation( char name, IOperator* root ) : root( root ), result( name )
{

}

double CEquation::Calculate( const std::map<char, double>& variables ) const
{
	return root->Calculate( variables );
}

char CEquation::GetResultVariableName() const
{
	return result;
}

// CFormula

CFormula::CFormula( int spaceDimension, int plotDimension, const std::vector<char> variables )
	: spaceDimension( spaceDimension ), plotDimension( plotDimension ), variables( variables.begin(), variables.end() )
{

}

std::map<char, double> CFormula::Calculate( const std::map<char, double>& variables ) const
{
	std::map<char, double> res;
	for( int i = 0; i < static_cast<int>( equations.size() ); ++i ) {
		res.insert( std::make_pair( equations[i].GetResultVariableName(), equations[i].Calculate( variables ) ) );
	}
	std::string dimensions = "xyz";
	
	for( int i = 0; i < static_cast<int>( dimensions.size() ); ++i ) {
		if( res.find( dimensions[i] ) == res.end() ) {
			if( variables.find( dimensions[i] ) == variables.end() ) {
				res[dimensions[i]] = static_cast< double >( 0 );
			} else {
				res[dimensions[i]] = variables.find( dimensions[i] )->second;
			}
		}
	}

	return res;
}

int CFormula::GetSpaceDimensions() const
{
	return spaceDimension;
}

int CFormula::GetPlotDimension() const
{
	return plotDimension;
}

std::vector<char> CFormula::GetVariables() const
{
	return variables;
}

void CFormula::AddEquation( CEquation equation )
{
	equations.push_back( equation );
}