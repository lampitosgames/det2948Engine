#pragma once
#include "Handle.h"

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

class HandleManager {
public:
	//Maximum number of entries into this manager
	const static int maxEntries = 8192;

	//Constructor is just a wrapper for Clear()
	HandleManager();
	//Clear and re-initialize all member data
	void Clear();

	//Add a handle
	Handle Add(void* pointer, unsigned type);
	//Remove a handle.  Returns false if passed handle is invalid/expired
	bool Remove(Handle handle);
	//Update a handle.  Returns false if passed handle is invalid/expired
	bool Update(Handle handle, void* newPointer);
	
	//Get the pointer from the handle
	void* Get(Handle handle);
	//Get the pointer and put it in a variable.  This is better since it returns the validity of the handle (prevents null pointers)
	bool Get(Handle handle, void* &out);
	//Gets a handle as a type
	template<typename T> bool Get(Handle handle, T& out);

	//Number of active handles
	int GetCount();
private:
	//Number of active handles
	int activeEntryCount;
	//This lets us quickly find a free location for new handles without having to traverse the array
	unsigned firstFreeEntry;

	//Struct for storing handles in the handle array
	struct HandleEntry {
		//The next handle that isn't in use. Allows us to remove the need for handle array traversal when we want to add an item (O(1) instead of O(n) for item entry)
		unsigned nextFreeIndex : 12;
		//Any time this handle is updated, the counter will be incremented.  This is used to validate handles.
		//Say a handle gets updated but an old handle pointing to this location is stored somewhere else.  This allows us to validate the handle.
		unsigned counter : 15;
		//Is the handle active
		unsigned active : 1;
		//Does this handle mark the end of the list?
		unsigned endOfList : 1;
		//Void pointer to the actual entry
		void* entry;
		//Default all values
		HandleEntry() {
			nextFreeIndex = 0;
			counter = 1;
			active = 0;
			endOfList = 0;
			entry = nullptr;
		}
		//Default all values, but pass in the next free index
		HandleEntry(unsigned inNextFreeIndex) {
			nextFreeIndex = inNextFreeIndex;
			counter = 1;
			active = 0;
			endOfList = 0;
			entry = nullptr;
		}
	};

	//The list of all handles
	HandleEntry entries[maxEntries];
};

//Wrapper function for Get(handle, out) that typecasts the void pointer.
template<typename T>
inline bool HandleManager::Get(Handle handle, T& out) {
	void* voidOut;
	bool validPointer = Get(handle, voidOut);
	//Typecast the void pointer
	out = (T)(voidOut);

	return validPointer;
}