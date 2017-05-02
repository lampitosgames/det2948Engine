#include "HandleManager.h"
//NOTE: I modified their code a lot, mostly to change things to my coding style but also to remove asserts (not a fan of those).  Games should fail silently - Daniel
//I also commented all the code myself because the original code was not commented at all.

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

HandleManager::HandleManager() {
	//Initialize all member data
	Clear();
}

//Initialize all values.  Also clears the entire handle manager for re-use
void HandleManager::Clear() {
	//No more active entries
	activeEntryCount = 0;
	//The first free entry becomes the first entry in the list
	firstFreeEntry = 0;

	//Initialize all handle entries.  Each entry points to the next one as the 'next free handle'
	for (int i = 0; i < maxEntries - 1; ++i) {
		entries[i] = HandleEntry(i + 1);
	}

	//Create the last entry
	entries[maxEntries - 1] = HandleEntry();
	entries[maxEntries - 1].endOfList = 1;
}

//Add a new item to the manager and return its handle
Handle HandleManager::Add(int pointerIndex, unsigned type) {
	//Set the index of this handle, get the next free one, clear the old.
	int index = firstFreeEntry;
	firstFreeEntry = entries[index].nextFreeIndex;
	entries[index].nextFreeIndex = 0;

	//Invalidate any lingering handles that point to this location
	entries[index].counter += 1;
	//Set this handle to active and give it a value
	entries[index].active = 1;
	entries[index].entry = pointerIndex;
	//Increment the number of active entries in the handle manager
	activeEntryCount += 1;
	//Return a new handle that can be passed around and duplicated without worrying about pointers!
	return Handle(index, entries[index].counter, type);
}

//Removes a handle from the manager
bool HandleManager::Remove(Handle handle) {
	//Valid handle check
	if (entries[handle.index].counter == handle.counter && entries[handle.index].active == 1) {
		//Get the old 'first free entry' and give it to the now-empty handle
		entries[handle.index].nextFreeIndex = firstFreeEntry;
		//Set this handle to the next free index.  This forms a 'chain' of free handles
		firstFreeEntry = handle.index;

		//Deactivate this handle. Decriment the number of active handles
		entries[handle.index].active = false;
		activeEntryCount -= 1;
		return true;
	}
	//Invalid handle
	return false;
}

//Simply pass a new pointer to an existing handle
bool HandleManager::Update(Handle handle, int newPointerIndex) {
	//Valid handle check
	if (entries[handle.index].counter == handle.counter && entries[handle.index].active == 1) {
		entries[handle.index].entry = newPointerIndex;
		return true;
	}
	//Invalid handle
	return false;
}

//If this is a valid handle, return the contained pointer (or null)
int HandleManager::Get(Handle handle) {
	int p = -1;
	if (!Get(handle, p)) {
		return -1;
	}
	return p;
}

//A much more elegant get that does a valid handle check before returning the pointer.
//Instead of returning the void*, it returns a bool for success, instead passing the void* into a provided out variable
bool HandleManager::Get(Handle handle, int &out) {
	//Valid handle check
	if (entries[handle.index].counter == handle.counter && entries[handle.index].active == 1) {
		out = entries[handle.index].entry;
		return true;
	}
	//Invalid handle
	return false;
}

//How many active handles are there?
int HandleManager::GetCount() {
	return activeEntryCount;
}
