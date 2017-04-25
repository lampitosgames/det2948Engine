#pragma once

//NOTE: I modified their code a lot, mostly to change things to my coding style but also to remove asserts (not a fan of those).  Games should fail silently - Daniel

/*
* Copyright (c) 2008, Power of Two Games LLC
* All rights reserved.
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions are met:
*     * Redistributions of source code must retain the above copyright
*       notice, this list of conditions and the following disclaimer.
*     * Redistributions in binary form must reproduce the above copyright
*       notice, this list of conditions and the following disclaimer in the
*       documentation and/or other materials provided with the distribution.
*     * Neither the name of Power of Two Games LLC nor the
*       names of its contributors may be used to endorse or promote products
*       derived from this software without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY POWER OF TWO GAMES LLC ``AS IS'' AND ANY
* EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
* DISCLAIMED. IN NO EVENT SHALL POWER OF TWO GAMES LLC BE LIABLE FOR ANY
* DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
* (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
* LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
* ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
* (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
* SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/


struct Handle {
	//Member data.
	//The index is where this handle is stored in the handle array
	unsigned index : 13;
	//The counter changes when the handle does
	unsigned counter : 14;
	//The type specifies what kind of pointer the handle holds
	unsigned type : 5;
	//Default constructor
	Handle() {
		index = 0;
		counter = 0;
		type = 0;
	}
	//Parameterized Constructor
	Handle(unsigned inIndex, unsigned inCounter, unsigned inType) {
		index = inIndex;
		counter = inCounter;
		type = inType;
	}

	//Implicit conversion to a 32 bit integer
	operator unsigned() const {
		//First 5 bits hold type, next 14 hold the counter, last 13 hold the index
		return type << 27 | counter << 13 | index;
	}
};