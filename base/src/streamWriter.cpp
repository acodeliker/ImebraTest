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

/*! \file streamWriter.cpp
    \brief Implementation of the streamWriter class.

*/

#include "../include/streamWriter.h"

namespace puntoexe
{

///////////////////////////////////////////////////////////
//
// Constructor
//
///////////////////////////////////////////////////////////
streamWriter::streamWriter(ptr<baseStream> pControlledStream, imbxUint32 virtualStart /* =0 */, imbxUint32 virtualLength /* =0 */):
	streamController(pControlledStream, virtualStart, virtualLength),
	m_outBitsBuffer(0),
	m_outBitsNum(0)
{
}


///////////////////////////////////////////////////////////
//
// Destructor
//
///////////////////////////////////////////////////////////
streamWriter::~streamWriter()
{
	flushDataBuffer();
}


///////////////////////////////////////////////////////////
//
// Flush the data buffer
//
///////////////////////////////////////////////////////////
void streamWriter::flushDataBuffer()
{
	imbxUint32 writeLength = (imbxUint32)(m_pDataBufferCurrent - m_pDataBufferStart);
	if(writeLength == 0)
	{
		return;
	}
	m_pControlledStream->write(m_dataBufferStreamPosition + m_virtualStart, m_pDataBufferStart, writeLength);
	m_pDataBufferCurrent = m_pDataBufferEnd = m_pDataBufferStart;
	m_dataBufferStreamPosition += writeLength;
}


///////////////////////////////////////////////////////////
//
// Write into the stream
//
///////////////////////////////////////////////////////////
void streamWriter::write(imbxUint8* pBuffer, imbxUint32 bufferLength)
{
	while(bufferLength != 0)
	{
		if(m_pDataBufferCurrent == m_pDataBufferMaxEnd)
		{
			flushDataBuffer();
		}
		imbxUint32 copySize = (imbxUint32)(m_pDataBufferMaxEnd - m_pDataBufferCurrent);
		if(copySize > bufferLength)
		{
			copySize = bufferLength;
		}
		::memcpy(m_pDataBufferCurrent, pBuffer, copySize);
		pBuffer += copySize;
		bufferLength -= copySize;
		m_pDataBufferCurrent += copySize;
		m_pDataBufferEnd = m_pDataBufferCurrent;
	}
}


} // namespace puntoexe
