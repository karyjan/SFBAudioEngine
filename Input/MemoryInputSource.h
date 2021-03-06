/*
 *  Copyright (C) 2010, 2011, 2012, 2013, 2014, 2015 Stephen F. Booth <me@sbooth.org>
 *  All Rights Reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions are
 *  met:
 *
 *  1. Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *
 *  2. Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *  HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#pragma once

#include <memory>

#include "InputSource.h"

namespace SFB {

	// ========================================
	// InputSource serving bytes from a region of memory
	// ========================================
	class MemoryInputSource : public InputSource
	{

	public:

		// Creation
		MemoryInputSource(const void *bytes, SInt64 byteCount, bool copyBytes = true);

	private:

		// Bytestream access
		virtual bool _Open(CFErrorRef *error);
		virtual bool _Close(CFErrorRef *error);

		// Functionality
		virtual SInt64 _Read(void *buffer, SInt64 byteCount);
		virtual bool _AtEOF() const								{ return ((mCurrentPosition - mMemory.get()) == mByteCount); }

		inline virtual SInt64 _GetOffset() const				{ return (mCurrentPosition - mMemory.get()); }
		inline virtual SInt64 _GetLength() const				{ return mByteCount; }

		// Seeking support
		inline virtual bool _SupportsSeeking() const			{ return true; }
		virtual bool _SeekToOffset(SInt64 offset);

		using unique_mem_ptr = std::unique_ptr<int8_t, void (*)(int8_t *)>;

		// Data members
		SInt64							mByteCount;
		unique_mem_ptr					mMemory;
		const int8_t					*mCurrentPosition;
	};

}
