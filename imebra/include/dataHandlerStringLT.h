/*

Imebra: a C++ dicom library.
Copyright (C) 2003, 2004, 2005, 2006  by Paolo Brandoli

This program is free software; you can redistribute it and/or modify
 it under the terms of the GNU General Public License version 2 as published by
 the Free Software Foundation.

This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

You should have received a copy of the GNU General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

-------------------

If you want to use Imebra commercially then you have to buy the commercial
 support available at http://puntoexe.com
 
After you buy the commercial support then you can use Imebra according
 to the terms described in the Imebra Commercial License Version 1.
A copy of the Imebra Commercial License Version 1 is available in the 
 documentation pages.

Imebra is available at http://puntoexe.com

The author can be contacted by email at paolo@puntoexe.com or by mail at
 the following address:
 Paolo Brandoli
 Rjava Cesta 2/a
 1000 Ljubljana
 Slovenia


*/

/*! \file dataHandlerStringLT.h
    \brief Declaration of the class dataHandlerStringLT.

*/

#if !defined(imebraDataHandlerStringLT_367AAE47_6FD7_4107_AB5B_25A355C5CB6E__INCLUDED_)
#define imebraDataHandlerStringLT_367AAE47_6FD7_4107_AB5B_25A355C5CB6E__INCLUDED_

#include "dataHandlerStringUnicode.h"


///////////////////////////////////////////////////////////
//
// Everything is in the namespace puntoexe::imebra
//
///////////////////////////////////////////////////////////
namespace puntoexe
{

namespace imebra
{

namespace handlers
{

///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// dataHandlerStringLT
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
class dataHandlerStringLT : public dataHandlerStringUnicode
{
public:
	virtual imbxUint8 getPaddingByte();

	virtual imbxUint32 getUnitSize();

protected:
	// Return the maximum string's length
	///////////////////////////////////////////////////////////
	virtual imbxUint32 maxSize();

	// TRUE if \ is used as a separator
	///////////////////////////////////////////////////////////
	virtual wchar_t getSeparator();
};

} // namespace handlers

} // namespace imebra

} // namespace puntoexe

#endif // !defined(imebraDataHandlerStringLT_367AAE47_6FD7_4107_AB5B_25A355C5CB6E__INCLUDED_)
