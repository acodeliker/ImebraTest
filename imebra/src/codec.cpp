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

/*! \file codec.cpp
    \brief Implementation of the base class for the codecs.

*/

#include "../../base/include/exception.h"
#include "../../base/include/streamReader.h"
#include "../../base/include/streamWriter.h"
#include "../include/codec.h"
#include "../include/dataSet.h"
#include "../include/codecFactory.h"


namespace puntoexe
{

namespace imebra
{

namespace codecs
{

///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Read a stream and write it into a dataset.
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
ptr<dataSet> codec::read(ptr<streamReader> pSourceStream, imbxUint32 maxSizeBufferLoad /* = 0xffffffff */)
{
	PUNTOEXE_FUNCTION_START(L"codec::read");

	// Reset the codec's bits buffer
	///////////////////////////////////////////////////////////
	pSourceStream->resetInBitsBuffer();

	// Store the stream's position
	///////////////////////////////////////////////////////////
	imbxUint32 position=pSourceStream->position();

	// Create a new dataset
	///////////////////////////////////////////////////////////
	ptr<dataSet> pDestDataSet(new dataSet);

	// Read the stream
	///////////////////////////////////////////////////////////
	try
	{
		readStream(pSourceStream, pDestDataSet, maxSizeBufferLoad);
	}
	catch(codecExceptionWrongFormat&)
	{
		pSourceStream->seek((imbxInt32)position);
		PUNTOEXE_RETHROW("Detected a wrong format. Rewinding file");
	}

	// Update the charsets in the tags
	///////////////////////////////////////////////////////////
	pDestDataSet->updateTagsCharset();

	return pDestDataSet;

	PUNTOEXE_FUNCTION_END();
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Write a dataset into a stream.
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
void codec::write(ptr<streamWriter> pDestStream, ptr<dataSet> pSourceDataSet)
{
	PUNTOEXE_FUNCTION_START(L"codec::write");

	// Update charsets tag
	///////////////////////////////////////////////////////////
	pSourceDataSet->updateCharsetTag();

	pDestStream->resetOutBitsBuffer();
	writeStream(pDestStream, pSourceDataSet);
	pDestStream->flushDataBuffer();

	PUNTOEXE_FUNCTION_END();
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Allocate a channel's memory
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
void channel::allocate(imbxUint32 sizeX, imbxUint32 sizeY)
{
	PUNTOEXE_FUNCTION_START(L"channel::allocate");

	m_sizeX = sizeX;
	m_sizeY = sizeY;
	m_bufferSize = sizeX * sizeY;
	m_memory = ptr<memory>(memoryPool::getMemoryPool()->getMemory(m_bufferSize * sizeof(imbxInt32) ));
	m_pBuffer = (imbxInt32*)(m_memory->data());

	::memset(m_pBuffer, 0, m_bufferSize * sizeof(imbxInt32));

	PUNTOEXE_FUNCTION_END();
}



///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Register a codec
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
registerCodec::registerCodec(ptr<codec> newCodec)
{
	PUNTOEXE_FUNCTION_START(L"registerCodec::registerCodec");

	ptr<codecFactory> pFactory(codecFactory::getCodecFactory());
	pFactory->registerCodec(newCodec);

	PUNTOEXE_FUNCTION_END();
}

} // namespace codecs

} // namespace imebra

} // namespace puntoexe

